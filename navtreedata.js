/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Jolt Physics", "index.html", [
    [ "Architecture of Jolt Physics", "index.html#architecture-jolt-physics", null ],
    [ "Bodies", "index.html#bodies", [
      [ "Types", "index.html#body-types", null ],
      [ "Creating Bodies", "index.html#creating-bodies", null ],
      [ "Multithreaded Access", "index.html#autotoc_md82", null ],
      [ "Single Threaded Access", "index.html#single-threaded-access", null ],
      [ "Shapes", "index.html#shapes", [
        [ "Dynamic Mesh Shapes", "index.html#dynamic-mesh-shapes", null ],
        [ "Creating Shapes", "index.html#creating-shapes", null ],
        [ "Saving Shapes", "index.html#saving-shapes", null ],
        [ "Convex Radius", "index.html#convex-radius", null ],
        [ "Center of Mass", "index.html#center-of-mass", null ],
        [ "Scaling Shapes", "index.html#scaling-shapes", null ],
        [ "Creating Custom Shapes", "index.html#creating-custom-shapes", null ]
      ] ],
      [ "Sensors", "index.html#sensors", null ],
      [ "Sleeping", "index.html#sleeping-bodies", null ],
      [ "Soft Bodies", "index.html#soft-bodies", [
        [ "Soft Body Contact Listeners", "index.html#soft-body-contact-listener", null ],
        [ "Skinning Soft Bodies", "index.html#skinning-soft-bodies", null ],
        [ "Soft Body Work In Progress", "index.html#soft-body-wip", null ]
      ] ]
    ] ],
    [ "Constraints", "index.html#constraints", [
      [ "Constraint Motors", "index.html#constraint-motors", null ],
      [ "Breakable Constraints", "index.html#breakable-constraints", null ]
    ] ],
    [ "Collision Detection", "index.html#collision-detection", [
      [ "Broad Phase", "index.html#broad-phase", null ],
      [ "Narrow Phase", "index.html#narrow-phase", null ],
      [ "Collision Filtering", "index.html#collision-filtering", null ],
      [ "Level of Detail", "index.html#level-of-detail", null ],
      [ "Continuous Collision Detection", "index.html#continuous-collision-detection", null ],
      [ "Ghost Collisions", "index.html#ghost-collisions", null ]
    ] ],
    [ "Character Controllers", "index.html#character-controllers", null ],
    [ "The Simulation Step", "index.html#the-simulation-step", null ],
    [ "Conventions and Limits", "index.html#conventions-and-limits", null ],
    [ "Big Worlds", "index.html#big-worlds", null ],
    [ "Deterministic Simulation", "index.html#deterministic-simulation", null ],
    [ "Rolling Back a Simulation", "index.html#rolling-back-a-simulation", null ],
    [ "Being Sloppy While Still Being Deterministic", "index.html#sloppy-determinism", null ],
    [ "Working With Multiple Physics Systems", "index.html#working-with-multiple-physics-systems", null ],
    [ "Debug Rendering", "index.html#debug-rendering", null ],
    [ "Memory Management", "index.html#memory-management", null ],
    [ "The Simulation Step in Detail", "index.html#the-simulation-step-in-detail", [
      [ "Broad Phase Update Prepare", "index.html#broad-phase-update-prepare", null ],
      [ "Broad Phase Update Finalize", "index.html#broad-phase-update-finalize", null ],
      [ "Step Listeners", "index.html#step-listeners-update", null ],
      [ "Apply Gravity", "index.html#apply-gravity-update", null ],
      [ "Determine Active Constraints", "index.html#determine-active-constraints", null ],
      [ "Build Islands from Constraints", "index.html#build-islands-from-constraints", null ],
      [ "Find Collisions", "index.html#find-collisions", null ],
      [ "Setup Velocity Constraints", "index.html#setup-velocity-constraints", null ],
      [ "Finalize Islands", "index.html#finalize-islands", null ],
      [ "Set Body Island Idx", "index.html#set-body-island-idx", null ],
      [ "Solve Velocity Constraints", "index.html#solve-velocity-constraints", null ],
      [ "Pre Integrate", "index.html#pre-integrate", null ],
      [ "Integrate & Clamp Velocities", "index.html#integrate-and-clamp-velocities", null ],
      [ "Post Integrate", "index.html#post-integrate", null ],
      [ "Find CCD Contacts", "index.html#find-ccd-contacts", null ],
      [ "Resolve CCD Contacts", "index.html#resolve-ccd-contacts", null ],
      [ "Finalize Contact Cache, Contact Removed Callbacks", "index.html#finalize-contact-cache", null ],
      [ "Solve Position Constraints, Update Bodies Broad Phase", "index.html#solve-position-constraints", null ],
      [ "Soft Body Prepare", "index.html#soft-body-prepare", null ],
      [ "Soft Body Collide", "index.html#soft-body-collide", null ],
      [ "Soft Body Simulate", "index.html#soft-body-simulate", null ],
      [ "Soft Body Finalize", "index.html#soft-body-finalize", null ]
    ] ],
    [ "Jolt Physics Samples", "md__docs_2_samples.html", [
      [ "General Controls", "md__docs_2_samples.html#autotoc_md5", null ],
      [ "The Tests", "md__docs_2_samples.html#autotoc_md6", [
        [ "Vehicles", "md__docs_2_samples.html#autotoc_md7", null ],
        [ "Rig (Ragdolls)", "md__docs_2_samples.html#autotoc_md8", null ],
        [ "Soft Body", "md__docs_2_samples.html#autotoc_md9", null ],
        [ "Character", "md__docs_2_samples.html#autotoc_md11", null ],
        [ "Water", "md__docs_2_samples.html#autotoc_md12", null ],
        [ "Constraints", "md__docs_2_samples.html#autotoc_md13", null ],
        [ "General", "md__docs_2_samples.html#autotoc_md15", null ],
        [ "Shapes & Scaled Shapes", "md__docs_2_samples.html#autotoc_md16", null ]
      ] ]
    ] ],
    [ "Performance Test", "md__docs_2_performance_test.html", [
      [ "Commandline options", "md__docs_2_performance_test.html#autotoc_md2", null ],
      [ "Output", "md__docs_2_performance_test.html#autotoc_md3", null ],
      [ "Results", "md__docs_2_performance_test.html#autotoc_md4", null ]
    ] ],
    [ "Release Notes", "md__docs_2_release_notes.html", [
      [ "v5.2.0", "md__docs_2_release_notes.html#autotoc_md18", [
        [ "New functionality", "md__docs_2_release_notes.html#autotoc_md20", null ],
        [ "Bug fixes", "md__docs_2_release_notes.html#autotoc_md21", null ]
      ] ],
      [ "v5.1.0", "md__docs_2_release_notes.html#autotoc_md23", [
        [ "New functionality", "md__docs_2_release_notes.html#autotoc_md24", [
          [ "Soft Body", "md__docs_2_release_notes.html#autotoc_md25", null ],
          [ "HeightField Shape", "md__docs_2_release_notes.html#autotoc_md26", null ],
          [ "Character", "md__docs_2_release_notes.html#autotoc_md29", null ],
          [ "Vehicles", "md__docs_2_release_notes.html#autotoc_md30", null ],
          [ "Various", "md__docs_2_release_notes.html#autotoc_md31", null ]
        ] ],
        [ "Bug fixes", "md__docs_2_release_notes.html#autotoc_md33", null ]
      ] ],
      [ "v5.0.0", "md__docs_2_release_notes.html#autotoc_md34", [
        [ "New Functionality", "md__docs_2_release_notes.html#autotoc_md36", [
          [ "Soft Body", "md__docs_2_release_notes.html#autotoc_md37", null ],
          [ "Vehicles", "md__docs_2_release_notes.html#autotoc_md38", null ],
          [ "Character", "md__docs_2_release_notes.html#autotoc_md41", null ],
          [ "Constraints", "md__docs_2_release_notes.html#autotoc_md42", null ],
          [ "Collision Detection", "md__docs_2_release_notes.html#autotoc_md43", null ],
          [ "Simulation", "md__docs_2_release_notes.html#autotoc_md44", null ],
          [ "Various", "md__docs_2_release_notes.html#autotoc_md45", null ]
        ] ],
        [ "Removed functionality", "md__docs_2_release_notes.html#autotoc_md46", null ],
        [ "Bug fixes", "md__docs_2_release_notes.html#autotoc_md47", null ]
      ] ],
      [ "v4.0.2", "md__docs_2_release_notes.html#autotoc_md48", [
        [ "New functionality", "md__docs_2_release_notes.html#autotoc_md49", null ],
        [ "Bug fixes", "md__docs_2_release_notes.html#autotoc_md50", null ]
      ] ],
      [ "v4.0.1", "md__docs_2_release_notes.html#autotoc_md51", [
        [ "New functionality", "md__docs_2_release_notes.html#autotoc_md52", null ],
        [ "Bug fixes", "md__docs_2_release_notes.html#autotoc_md53", null ]
      ] ],
      [ "v4.0.0", "md__docs_2_release_notes.html#autotoc_md54", [
        [ "New functionality", "md__docs_2_release_notes.html#autotoc_md55", null ],
        [ "Removed functionality", "md__docs_2_release_notes.html#autotoc_md56", null ],
        [ "New supported platforms", "md__docs_2_release_notes.html#autotoc_md57", null ],
        [ "Bug fixes", "md__docs_2_release_notes.html#autotoc_md58", null ]
      ] ],
      [ "v3.0.0", "md__docs_2_release_notes.html#autotoc_md59", null ],
      [ "v2.0.1", "md__docs_2_release_notes.html#autotoc_md60", null ],
      [ "v2.0.0", "md__docs_2_release_notes.html#autotoc_md61", [
        [ "Major new functionality", "md__docs_2_release_notes.html#autotoc_md62", null ],
        [ "New supported compilers", "md__docs_2_release_notes.html#autotoc_md63", null ],
        [ "New supported platforms", "md__docs_2_release_notes.html#autotoc_md64", null ]
      ] ],
      [ "v1.1.0", "md__docs_2_release_notes.html#autotoc_md65", null ],
      [ "v1.0.0", "md__docs_2_release_notes.html#autotoc_md66", null ]
    ] ],
    [ "Breaking API Changes", "md__docs_2_a_p_i_changes.html", [
      [ "Changes between v5.1.0 and v5.2.0", "md__docs_2_a_p_i_changes.html#autotoc_md17", null ],
      [ "Changes between v5.0.0 and v5.1.0", "md__docs_2_a_p_i_changes.html#autotoc_md19", null ],
      [ "Changes between v4.0.2 and v5.0.0", "md__docs_2_a_p_i_changes.html#autotoc_md22", null ],
      [ "Changes between v4.0.0 and v4.0.2", "md__docs_2_a_p_i_changes.html#autotoc_md27", null ],
      [ "Changes between v3.0.1 and v4.0.0", "md__docs_2_a_p_i_changes.html#autotoc_md28", null ],
      [ "Changes between v2.0.1 and v3.0.0", "md__docs_2_a_p_i_changes.html#autotoc_md32", null ],
      [ "Changes between v1.1.0 and v2.0.0", "md__docs_2_a_p_i_changes.html#autotoc_md35", null ],
      [ "Changes between v1.0.0 and v1.1.0", "md__docs_2_a_p_i_changes.html#autotoc_md39", null ],
      [ "Changes between v0.0.0 and v1.0.0", "md__docs_2_a_p_i_changes.html#autotoc_md40", null ]
    ] ],
    [ "Building and Using Jolt Physics", "md__build_2_r_e_a_d_m_e.html", [
      [ "Build Types", "md__build_2_r_e_a_d_m_e.html#autotoc_md69", null ],
      [ "Includes", "md__build_2_r_e_a_d_m_e.html#autotoc_md70", null ],
      [ "Defines", "md__build_2_r_e_a_d_m_e.html#autotoc_md71", null ],
      [ "Logging & Asserting", "md__build_2_r_e_a_d_m_e.html#autotoc_md72", null ],
      [ "Custom Memory Allocator", "md__build_2_r_e_a_d_m_e.html#autotoc_md73", null ],
      [ "Building", "md__build_2_r_e_a_d_m_e.html#autotoc_md74", null ],
      [ "Other Build Tools", "md__build_2_r_e_a_d_m_e.html#autotoc_md75", null ],
      [ "Errors", "md__build_2_r_e_a_d_m_e.html#autotoc_md76", [
        [ "Link Error: File Format Not Recognized", "md__build_2_r_e_a_d_m_e.html#autotoc_md77", null ],
        [ "Link Error: Unresolved External Symbol", "md__build_2_r_e_a_d_m_e.html#autotoc_md78", null ],
        [ "DirectX Error", "md__build_2_r_e_a_d_m_e.html#autotoc_md79", null ],
        [ "Illegal Instruction Error", "md__build_2_r_e_a_d_m_e.html#autotoc_md80", null ]
      ] ],
      [ "Doxygen on Windows", "md__build_2_r_e_a_d_m_e.html#autotoc_md81", null ]
    ] ],
    [ "Projects Using Jolt", "md__docs_2_projects_using_jolt.html", null ],
    [ "Namespaces", "namespaces.html", [
      [ "Namespace List", "namespaces.html", "namespaces_dup" ],
      [ "Namespace Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", null ],
        [ "Functions", "namespacemembers_func.html", null ],
        [ "Variables", "namespacemembers_vars.html", null ],
        [ "Typedefs", "namespacemembers_type.html", null ],
        [ "Enumerations", "namespacemembers_enum.html", null ],
        [ "Enumerator", "namespacemembers_eval.html", null ]
      ] ]
    ] ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", "functions_vars" ],
        [ "Typedefs", "functions_type.html", null ],
        [ "Enumerations", "functions_enum.html", null ],
        [ "Enumerator", "functions_eval.html", null ],
        [ "Related Symbols", "functions_rela.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", "globals_func" ],
        [ "Variables", "globals_vars.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", null ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"_a_a_b_b_tree_builder_8cpp.html",
"_constraint_8h.html#adfc8350888df0c3a51714b7f372baf2dad6af9c1eaff2a89ebd3f8d0c542be12b",
"_height_field_shape_8h.html#a37ca4958b8fd6b37a4982941ca479a85",
"_object_stream_text_in_8h.html",
"_scope_exit_8h.html#af3b6234fdd42f0f27a584738fb79b60a",
"_sub_shape_i_d_pair_8h.html",
"class_a_a_box.html#a8431a72347bfdb1a77ae45dcbba9c35b",
"class_body_creation_settings.html#a4bd85f028390274d79f291ea20f7c9f5",
"class_box_shape.html",
"class_character_base.html#a5c10220e06a8a5bb274a4b02c28cb0b6",
"class_collision_dispatch.html#a9b0ecb3f10cdac7c5cf648cb2fa0b8e8",
"class_convex_hull_builder.html#a3182f05659156aba23773cd1cdb5c0cd",
"class_d_vec3.html#a4841bd14fcbce5a9a03edde10d9c6b30",
"class_e_p_a_convex_hull_builder.html#a7095af90fda9266b9ae7258025623499",
"class_height_field_shape.html#ab850b5af741a24d3abc431d4b73d7caf",
"class_job_system_1_1_job_handle.html#a08f33876c4c56f09acc8447c68af002a",
"class_mesh_shape.html#a7c2e775c8d2691c71de1243732dc702a",
"class_object_stream_binary_in.html#aa74809f20beb6f9621abc3e2333c614e",
"class_physics_scene.html#afe41447c0b307d2844a16e288fd412af",
"class_quad_tree.html#a0f40b5da772779a14a6d6aedd28ae8a0",
"class_ref_const.html#a9d1007543402ab4cf1bde9945763d202",
"class_shape.html#a6abbf113475435c0c694d3199e352c3a",
"class_slider_constraint.html#a13363a2168538544705cff396e1eab28",
"class_soft_body_update_context.html#a19e196d17741280f4ba21d9b7bc4bb86",
"class_sub_shape_i_d.html#a1a908b7e19b2d792793830b751a66a27",
"class_tracked_vehicle_controller_settings.html#af67a8a4259f517164fb035582696dd6c",
"class_vec3.html#a1ef1f1ce4031e9ecd4545799525281d8",
"class_vehicle_constraint_settings.html#a90697fd39e19d071664f0fec05d75764",
"dir_581cdd6ad79c50f327179442908d53d5.html",
"md__docs_2_release_notes.html#autotoc_md44",
"struct_compound_shape_1_1_collide_compound_vs_shape_visitor.html#a10a2d8ac67f9978eeacf09dae77c894b",
"struct_physics_update_context_1_1_step.html#ad8016f86c45bb3092259e91ff0f6c426"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';