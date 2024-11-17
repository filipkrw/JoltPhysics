import os


def find_src_files(root_dir):
    src_files = []
    for dirpath, _, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename.endswith('.cpp'):
                src_files.append(os.path.join(dirpath, filename))
    return src_files


env = Environment()

# Set compiler flags
env.Append(CXXFLAGS=[
    '/Zc:__cplusplus', '/Gm-', '/MP', '/nologo', '/diagnostics:classic',
    '/FC', '/fp:except-', '/Zc:inline', '/Zi', '/GR-', '/EHsc-', '/wd4577',
    '/Wall', '/WX', '/GS-', '/Gy', '/O2', '/Oi', '/Ot', '/arch:AVX2'
])

# Set the C++17 standard
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

# Add Jolt header files to the include path
env.Append(CPPPATH=['.'])

# Collect all source files from the Jolt directory
src_files = find_src_files('Jolt')

# Add Hello World example source files
src_files.append('test_src/main.cpp')

# Build the static library
env.Program(target='out/test', source=src_files)
