cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER C:/msys64/usr/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/msys64/usr/bin/g++.exe)
project(OPEN_MANDREL_PROJECT LANGUAGES C CXX)

# -O4 -DNDEBUG for release over -O0 and -g
# -Wall for warnings
add_compile_options(-std=c++17 -O0 -g -Wno-deprecated -mwin32)

file(GLOB_RECURSE OPEN_MANDREL_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(OpenMandrel ${OPEN_MANDREL_SRC})
target_include_directories(OpenMandrel PRIVATE ${PROJECT_SOURCE_DIR}/../../TundraEngine/include)
target_link_libraries(OpenMandrel -L"${PROJECT_SOURCE_DIR}/../../SSTSPP/libs" glew32.lib glew32s.lib SDL2.lib)
target_link_libraries(OpenMandrel user32.lib OpenGL32.lib stdc++)
