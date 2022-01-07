// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

#include <Core/StaticArray.h>
#include <Core/LockFreeHashMap.h>
#include <Physics/Body/BodyPair.h>
#include <Physics/Collision/Shape/SubShapeIDPair.h>
#include <Physics/Collision/ManifoldBetweenTwoFaces.h>
#include <Physics/Constraints/ConstraintPart/AxisConstraintPart.h>
#include <Physics/Constraints/ConstraintPart/DualAxisConstraintPart.h>
#include <Core/HashCombine.h>
#include <Core/NonCopyable.h>
#include <atomic>

namespace JPH {

class PhysicsUpdateContext;

class ContactConstraintManager : public NonCopyable
{
public:
	/// Constructor
	explicit					ContactConstraintManager(const PhysicsSettings &inPhysicsSettings);
								~ContactConstraintManager();

	/// Initialize the system.
	/// @param inMaxBodyPairs Maximum amount of body pairs to process (anything else will fall through the world), this number should generally be much higher than the max amount of contact points as there will be lots of bodies close that are not actually touching
	/// @param inMaxContactConstraints Maximum amount of contact constraints to process (anything else will fall through the world)
	void						Init(uint inMaxBodyPairs, uint inMaxContactConstraints);

	/// Listener that is notified whenever a contact point between two bodies is added/updated/removed
	void						SetContactListener(ContactListener *inListener)						{ mContactListener = inListener; }
	ContactListener *			GetContactListener() const											{ return mContactListener; }

	/// Callback function to combine the restitution or friction of two bodies
	using CombineFunction = float (*)(const Body &inBody1, const Body &inBody2);

	/// Set the function that combines the friction of two bodies and returns it
	/// Default method is the geometric mean: sqrt(friction1 * friction2).
	void						SetCombineFriction(CombineFunction inCombineFriction)				{ mCombineFriction = inCombineFriction; }

	/// Set the function that combines the restitution of two bodies and returns it
	/// Default method is max(restitution1, restitution1)
	void						SetCombineRestitution(CombineFunction inCombineRestitution)			{ mCombineRestitution = inCombineRestitution; }

	/// Get the max number of contact constraints that are allowed
	uint32						GetMaxConstraints() const											{ return mMaxConstraints; }

	/// Check with the listener if inBody1 and inBody2 could collide, returns false if not
	inline ValidateResult		ValidateContactPoint(const Body &inBody1, const Body &inBody2, const CollideShapeResult &inCollisionResult) const	
	{ 
		if (mContactListener == nullptr) 
			return ValidateResult::AcceptAllContactsForThisBodyPair; 

		return mContactListener->OnContactValidate(inBody1, inBody2, inCollisionResult); 
	}

	/// Sets up the constraint buffer. Should be called before starting collision detection.
	void						PrepareConstraintBuffer(PhysicsUpdateContext *inContext);

	/// Max 4 contact points are needed for a stable manifold
	static const int			MaxContactPoints = 4;

	/// Contacts are allocated in a lock free hash map
	class ContactAllocator : public LFHMAllocatorContext
	{
	public:
		using LFHMAllocatorContext::LFHMAllocatorContext;

		uint					mNumBodyPairs = 0;													///< Total number of body pairs added using this allocator
		uint					mNumManifolds = 0;													///< Total number of manifolds added using this allocator
	};

	/// Get a new allocator context for storing contacts. Note that you should call this once and then add multiple contacts using the context.
	ContactAllocator			GetContactAllocator()												{ return mCache[mCacheWriteIdx].GetContactAllocator(); }

	/// Check if the contact points from the previous frame are reusable and if so copy them.
	/// When the cache was usable and the pair has been handled: outPairHandled = true.
	/// When a contact was produced: outContactFound = true.
	void						GetContactsFromCache(ContactAllocator &ioContactAllocator, Body &inBody1, Body &inBody2, bool &outPairHandled, bool &outContactFound);

	/// Handle used to keep track of the current body pair
	using BodyPairHandle = void *;

	/// Create a handle for a colliding body pair so that contact constraints can be added between them.
	/// Needs to be called once per body pair per frame before calling AddContactConstraint.
	BodyPairHandle				AddBodyPair(ContactAllocator &ioContactAllocator, const Body &inBody1, const Body &inBody2);

	/// Add a contact constraint for this frame.
	///
	/// @param inBodyPair The handle for the contact cache for this body pair
	/// @param inBody1 The first body that is colliding
	/// @param inBody2 The second body that is colliding
	/// @param inManifold The manifold that describes the collision
	///
	/// This is using the approach described in 'Modeling and Solving Constraints' by Erin Catto presented at GDC 2009 (and later years with slight modifications).
	/// We're using the formulas from slide 50 - 53 combined.
	///
	/// Euler velocity integration: 
	///
	/// v1' = v1 + M^-1 P
	///
	/// Impulse:
	///
	/// P = J^T lambda
	///
	/// Constraint force:
	///
	/// lambda = -K^-1 J v1
	///
	/// Inverse effective mass:
	///
	/// K = J M^-1 J^T
	///
	/// Constraint equation (limits movement in 1 axis):
	///
	/// C = (p2 - p1) . n
	///
	/// Jacobian (for position constraint)
	///
	/// J = [-n, -r1 x n, n, r2 x n]
	/// 
	/// n = contact normal (pointing away from body 1).
	/// p1, p2 = positions of collision on body 1 and 2.
	/// r1, r2 = contact point relative to center of mass of body 1 and body 2 (r1 = p1 - x1, r2 = p2 - x2).
	/// v1, v2 = (linear velocity, angular velocity): 6 vectors containing linear and angular velocity for body 1 and 2.
	/// M = mass matrix, a diagonal matrix of the mass and inertia with diagonal [m1, I1, m2, I2].
	void						AddContactConstraint(ContactAllocator &ioContactAllocator, BodyPairHandle inBodyPair, Body &inBody1, Body &inBody2, const ContactManifold &inManifold);

	/// Finalizes the contact cache, the contact cache that was generated during the calls to AddContactConstraint in this update
	/// will be used from now on to read from.
	/// inExpectedNumBodyPairs / inExpectedNumManifolds are the amount of body pairs / manifolds found in the previous step and is used to determine the amount of buckets the contact cache hash map will use.
	void						FinalizeContactCache(uint inExpectedNumBodyPairs, uint inExpectedNumManifolds);

	/// Notifies the listener of any contact points that were removed. Needs to be callsed after FinalizeContactCache().
	void						ContactPointRemovedCallbacks();

	/// Get the number of contact constraints that were found
	uint32						GetNumConstraints() const											{ return min<uint32>(mNumConstraints, mMaxConstraints); }

	/// Sort contact constraints deterministically
	void						SortContacts(uint32 *inConstraintIdxBegin, uint32 *inConstraintIdxEnd) const;

	/// AddContactConstraint will also setup the velocity constraints for the first sub step. For subsequent sub steps this function must be called prior to warm starting the constraint.
	void						SetupVelocityConstraints(uint32 *inConstraintIdxBegin, uint32 *inConstraintIdxEnd, float inDeltaTime);

	/// Apply last frame's impulses as an initial guess for this frame's impulses
	void						WarmStartVelocityConstraints(const uint32 *inConstraintIdxBegin, const uint32 *inConstraintIdxEnd, float inWarmStartImpulseRatio);

	/// Solve velocity constraints, when almost nothing changes this should only apply very small impulses
	/// since we're warm starting with the total impulse applied in the last frame above.
	///
	/// Friction wise we're using the Coulomb friction model which says that:
	///
	/// |F_T| <= mu |F_N|
	///
	/// Where F_T is the tangential force, F_N is the normal force and mu is the friction coefficient
	///
	/// In impulse terms this becomes:
	///
	/// |lambda_T| <= mu |lambda_N|
	///
	/// And the constraint that needs to be applied is exactly the same as a non penetration constraint
	/// except that we use a tangent instead of a normal. The tangent should point in the direction of the 
	/// tangential velocity of the point:
	///
	/// J = [-T, -r1 x T, T, r2 x T]
	///
	/// Where T is the tangent.
	///
	/// See slide 42 and 43.
	///
	/// Restitution is implemented as a velocity bias (see slide 41):
	///
	/// b = e v_n^-
	///
	/// e = the restitution coefficient, v_n^- is the normal velocity prior to the collision
	///
	/// Restitution is only applied when v_n^- is large enough and the points are moving towards collision
	bool						SolveVelocityConstraints(const uint32 *inConstraintIdxBegin, const uint32 *inConstraintIdxEnd);

	/// Save back the lambdas to the contact cache for the next warm start
	void						StoreAppliedImpulses(const uint32 *inConstraintIdxBegin, const uint32 *inConstraintIdxEnd);

	/// Solve position constraints.
	/// This is using the approach described in 'Modeling and Solving Constraints' by Erin Catto presented at GDC 2007.
	/// On slide 78 it is suggested to split up the Baumgarte stabilization for positional drift so that it does not
	/// actually add to the momentum. We combine an Euler velocity integrate + a position integrate and then discard the velocity
	/// change.
	///
	/// Constraint force:
	///
	/// lambda = -K^-1 b
	///
	/// Baumgarte stabilization:
	///
	/// b = beta / dt C
	///
	/// beta = baumgarte stabilization factor.
	/// dt = delta time.
	bool						SolvePositionConstraints(const uint32 *inConstraintIdxBegin, const uint32 *inConstraintIdxEnd);

	/// Recycle the constraint buffer. Should be called between collision simulation steps.
	void						RecycleConstraintBuffer();

	/// Terminate the constraint buffer. Should be called after simulation ends.
	void						FinishConstraintBuffer();

	/// Called by continuous collision detection to notify the contact listener that a contact was added
	/// @param inBody1 The first body that is colliding
	/// @param inBody2 The second body that is colliding
	/// @param inManifold The manifold that describes the collision
	/// @param outSettings The calculated contact settings (may be overridden by the contact listener)
	void						OnCCDContactAdded(ContactAllocator &ioContactAllocator, const Body &inBody1, const Body &inBody2, const ContactManifold &inManifold, ContactSettings &outSettings);

#ifdef JPH_DEBUG_RENDERER
	// Drawing properties
	static bool					sDrawContactPoint;
	static bool					sDrawSupportingFaces;
	static bool					sDrawContactPointReduction;
	static bool					sDrawContactManifolds;
#endif // JPH_DEBUG_RENDERER

	/// Saving state for replay
	void						SaveState(StateRecorder &inStream) const;

	/// Restoring state for replay. Returns false when failed.
	bool						RestoreState(StateRecorder &inStream);

private:
	/// Local space contact point, used for caching impulses
	class CachedContactPoint
	{
	public:
		/// Saving / restoring state for replay
		void					SaveState(StateRecorder &inStream) const;
		void					RestoreState(StateRecorder &inStream);

		/// Local space positions on body 1 and 2.
		/// Note: these values are read through sLoadFloat3Unsafe.
		Float3					mPosition1;
		Float3					mPosition2;

		/// Total applied impulse during the last update that it was used
		float					mNonPenetrationLambda;
		Vector<2>				mFrictionLambda;
	};

	static_assert(sizeof(CachedContactPoint) == 36, "Unexpected size");
	static_assert(alignof(CachedContactPoint) == 4, "Assuming 4 byte aligned");
	
	/// A single cached manifold
	class CachedManifold
	{
	public:
		/// Calculate size in bytes needed beyond the size of the class to store inNumContactPoints
		static int				sGetRequiredExtraSize(int inNumContactPoints)						{ return max(0, inNumContactPoints - 1) * sizeof(CachedContactPoint); }

		/// Calculate total class size needed for storing inNumContactPoints
		static int				sGetRequiredTotalSize(int inNumContactPoints)						{ return sizeof(CachedManifold) + sGetRequiredExtraSize(inNumContactPoints); }

		/// Saving / restoring state for replay
		void					SaveState(StateRecorder &inStream) const;
		void					RestoreState(StateRecorder &inStream);

		/// Handle to next cached contact points in ManifoldCache::mCachedManifolds for the same body pair
		uint32					mNextWithSameBodyPair;

		/// Contact normal in the space of 2.
		/// Note: this value is read through sLoadFloat3Unsafe.
		Float3					mContactNormal;

		/// Flags for this cached manifold
		enum class EFlags : uint16
		{
			ContactPersisted	= 1,																///< If this cache entry was reused in the next simulation update
			CCDContact			= 2																	///< This is a cached manifold reported by continuous collision detection and was only used to create a contact callback
		};

		/// @see EFlags
		mutable atomic<uint16>	mFlags { 0 };

		/// Number of contact points in the array below
		uint16					mNumContactPoints;

		/// Contact points that this manifold consists of
		CachedContactPoint		mContactPoints[1];
	};

	static_assert(sizeof(CachedManifold) == 56, "This structure is expect to not contain any waste due to alignment");
	static_assert(alignof(CachedManifold) == 4, "Assuming 4 byte aligned");

	/// Define a map that maps SubShapeIDPair -> manifold
	using ManifoldMap = LockFreeHashMap<SubShapeIDPair, CachedManifold>;
	using MKeyValue = ManifoldMap::KeyValue;
	using MKVAndCreated = pair<MKeyValue *, bool>;

	/// Start of list of contact points for a particular pair of bodies
	class CachedBodyPair
	{
	public:
		/// Saving / restoring state for replay
		void					SaveState(StateRecorder &inStream) const;
		void					RestoreState(StateRecorder &inStream);

		/// Local space position difference from Body A to Body B.
		/// Note: this value is read through sLoadFloat3Unsafe
		Float3					mDeltaPosition;

		/// Local space rotation difference from Body A to Body B, fourth component of quaternion is not stored but is guaranteed >= 0.
		/// Note: this value is read through sLoadFloat3Unsafe
		Float3					mDeltaRotation;

		/// Handle to first manifold in ManifoldCache::mCachedManifolds
		uint32					mFirstCachedManifold;
	};

	static_assert(sizeof(CachedBodyPair) == 28, "Unexpected size"); 
	static_assert(alignof(CachedBodyPair) == 4, "Assuming 4 byte aligned");

	/// Define a map that maps BodyPair -> CachedBodyPair
	using BodyPairMap = LockFreeHashMap<BodyPair, CachedBodyPair>;
	using BPKeyValue = BodyPairMap::KeyValue;

	/// Holds all caches that are needed to quickly find cached body pairs / manifolds
	class ManifoldCache
	{
	public:
		/// Initialize the cache
		void					Init(uint inMaxBodyPairs, uint inMaxContactConstraints, uint inCachedManifoldsSize);

		/// Reset all entries from the cache
		void					Clear();

		/// Prepare cache before creating new contacts. 
		/// inExpectedNumBodyPairs / inExpectedNumManifolds are the amount of body pairs / manifolds found in the previous step and is used to determine the amount of buckets the contact cache hash map will use.
		void					Prepare(uint inExpectedNumBodyPairs, uint inExpectedNumManifolds);

		/// Get a new allocator context for storing contacts. Note that you should call this once and then add multiple contacts using the context.
		ContactAllocator		GetContactAllocator()						{ return ContactAllocator(mAllocator, cAllocatorBlockSize); }

		/// Find / create cached entry for SubShapeIDPair -> CachedManifold
		const MKeyValue *		Find(const SubShapeIDPair &inKey, size_t inKeyHash) const;
		MKeyValue *				Create(ContactAllocator &ioContactAllocator, const SubShapeIDPair &inKey, size_t inKeyHash, int inNumContactPoints);
		MKVAndCreated			FindOrCreate(ContactAllocator &ioContactAllocator, const SubShapeIDPair &inKey, size_t inKeyHash, int inNumContactPoints);
		uint32					ToHandle(const MKeyValue *inKeyValue) const;
		const MKeyValue *		FromHandle(uint32 inHandle) const;

		/// Find / create entry for BodyPair -> CachedBodyPair
		const BPKeyValue *		Find(const BodyPair &inKey, size_t inKeyHash) const;
		BPKeyValue *			Create(ContactAllocator &ioContactAllocator, const BodyPair &inKey, size_t inKeyHash);
		void					GetAllBodyPairsSorted(vector<const BPKeyValue *> &outAll) const;
		void					GetAllManifoldsSorted(const CachedBodyPair &inBodyPair, vector<const MKeyValue *> &outAll) const;
		void					GetAllCCDManifoldsSorted(vector<const MKeyValue *> &outAll) const;
		void					ContactPointRemovedCallbacks(ContactListener *inListener);

#ifdef JPH_ENABLE_ASSERTS
		/// Get the amount of manifolds in the cache
		uint					GetNumManifolds() const						{ return mCachedManifolds.GetNumKeyValues(); }

		/// Get the amount of body pairs in the cache
		uint					GetNumBodyPairs() const						{ return mCachedBodyPairs.GetNumKeyValues(); }

		/// Before a cache is finalized you can only do Create(), after only Find() or Clear()
		void					Finalize();
#endif

		/// Saving / restoring state for replay
		void					SaveState(StateRecorder &inStream) const;
		bool					RestoreState(const ManifoldCache &inReadCache, StateRecorder &inStream);

	private:
		/// Block size used when allocating new blocks in the contact cache
		static constexpr uint32	cAllocatorBlockSize = 4096;

		/// Allocator used by both mCachedManifolds and mCachedBodyPairs, this makes it more likely that a body pair and its manifolds are close in memory
		LFHMAllocator			mAllocator;

		/// Simple hash map for SubShapeIDPair -> CachedManifold
		ManifoldMap				mCachedManifolds { mAllocator };

		/// Simple hash map for BodyPair -> CachedBodyPair
		BodyPairMap				mCachedBodyPairs { mAllocator };

#ifdef JPH_ENABLE_ASSERTS
		bool					mIsFinalized = false;						///< Marks if this buffer is complete
#endif
	};

	ManifoldCache				mCache[2];									///< We have one cache to read from and one to write to
	int							mCacheWriteIdx = 0;							///< Which cache we're currently writing to

	/// World space contact point, used for solving penetrations
	class WorldContactPoint
	{
	public:
		/// Calculate constraint properties below
		void					CalculateNonPenetrationConstraintProperties(float inDeltaTime, const Body &inBody1, const Body &inBody2, Vec3Arg inWorldSpacePosition1, Vec3Arg inWorldSpacePosition2, Vec3Arg inWorldSpaceNormal);
		void					CalculateFrictionAndNonPenetrationConstraintProperties(float inDeltaTime, const Body &inBody1, const Body &inBody2, Vec3Arg inWorldSpacePosition1, Vec3Arg inWorldSpacePosition2, Vec3Arg inWorldSpaceNormal, Vec3Arg inWorldSpaceTangent1, Vec3Arg inWorldSpaceTangent2, float inCombinedRestitution, float inCombinedFriction, float inMinVelocityForRestitution);

		/// The constraint parts
		AxisConstraintPart		mNonPenetrationConstraint;
		AxisConstraintPart		mFrictionConstraint1;
		AxisConstraintPart		mFrictionConstraint2;
		
		/// Contact cache
		CachedContactPoint *	mContactPoint;
	};

	using WorldContactPoints = StaticArray<WorldContactPoint, MaxContactPoints>;

	/// Contact constraint class, used for solving penetrations
	class ContactConstraint
	{
	public:
	#ifdef JPH_DEBUG_RENDERER
		/// Draw the state of the contact constraint
		void					Draw(DebugRenderer *inRenderer, ColorArg inManifoldColor) const;
	#endif // JPH_DEBUG_RENDERER

		/// Get the tangents for this contact constraint
		JPH_INLINE void			GetTangents(Vec3 &outTangent1, Vec3 &outTangent2) const
		{
			outTangent1 = mWorldSpaceNormal.GetNormalizedPerpendicular();
			outTangent2 = mWorldSpaceNormal.Cross(outTangent1);
		}

		Vec3					mWorldSpaceNormal;
		Body *					mBody1;
		Body *					mBody2;
		size_t					mSortKey;
		ContactSettings			mSettings;
		WorldContactPoints		mContactPoints;
	};

	/// Internal helper function to warm start contact constraint. Templated to the motion type to reduce the amount of branches.
	template <EMotionType Type1, EMotionType Type2>
	JPH_INLINE static void		sWarmStartConstraint(ContactConstraint &ioConstraint, MotionProperties *ioMotionProperties1, MotionProperties *ioMotionProperties2, Vec3Arg inTangent1, Vec3Arg inTangent2, float inWarmStartImpulseRatio);

	/// Internal helper function to solve a single contact constraint. Templated to the motion type to reduce the amount of branches.
	template <EMotionType Type1, EMotionType Type2>
	JPH_INLINE static bool		sSolveVelocityConstraint(ContactConstraint &ioConstraint, MotionProperties *ioMotionProperties1, MotionProperties *ioMotionProperties2, Vec3Arg inTangent1, Vec3Arg inTangent2);

	/// The main physics settings instance
	const PhysicsSettings &		mPhysicsSettings;

	/// Listener that is notified whenever a contact point between two bodies is added/updated/removed
	ContactListener *			mContactListener = nullptr;

	/// Functions that are used to combine friction and restitution of 2 bodies
	CombineFunction				mCombineFriction = [](const Body &inBody1, const Body &inBody2) { return sqrt(inBody1.GetFriction() * inBody2.GetFriction()); };
	CombineFunction				mCombineRestitution = [](const Body &inBody1, const Body &inBody2) { return max(inBody1.GetRestitution(), inBody2.GetRestitution()); };

	/// The constraints that were added this frame
	ContactConstraint *			mConstraints = nullptr;
	uint32						mMaxConstraints = 0;
	atomic<uint32>				mNumConstraints { 0 };

	/// Context used for this physics update
	PhysicsUpdateContext *		mUpdateContext;
};

} // JPH