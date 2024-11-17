import os

env = Environment()

# Set compiler flags
env.Append(CXXFLAGS=[
    '/Zc:__cplusplus', '/Gm-', '/MP', '/nologo', '/diagnostics:classic',
    '/FC', '/fp:except-', '/Zc:inline', '/Zi', '/GR-', '/EHsc-', '/wd4577',
    '/Wall', '/GS-', '/Gy', '/O2', '/Oi', '/Ot', '/arch:AVX2'
])

env.Append(CXXFLAGS=['/std:c++17'])

# Set preprocessor definitions
env.Append(CPPDEFINES=[
    'JPH_FLOATING_POINT_EXCEPTIONS_ENABLED=ON',
    'JPH_ENABLE_ASSERTS=OFF',
    'JPH_DOUBLE_PRECISION=OFF',
    'JPH_USE_SSE4_1=ON',
    'JPH_USE_SSE4_2=ON',
    'JPH_USE_AVX=ON',
    'JPH_USE_AVX2=ON',
    'JPH_USE_LZCNT=ON',
    'JPH_USE_TZCNT=ON',
    'JPH_USE_F16C=ON',
    'JPH_USE_FMADD=ON',
    'JPH_OBJECT_LAYER_BITS=16',
    'JPH_DEBUG_RENDERER',
    'JPH_ENABLE_PROFILING',
    'JPH_ENABLE_OBJECT_STREAM'
])

env.Append(CPPPATH=['.'])

# Collect all source files from the 'Jolt' directory
src_files = []
for dirpath, _, filenames in os.walk('Jolt'):
    for filename in filenames:
        if filename.endswith('.cpp'):
            src_files.append(os.path.join(dirpath, filename))

src_files.append('test_src/main.cpp')

# Build the static library
# env.StaticLibrary(target='joltey', source=src_files)
env.Program(target='out/test', source=src_files)
