cmake_minimum_required(VERSION 3.25)
project(opengl)

set(CMAKE_CXX_STANDARD 14)

include_directories(Dependencies)
include_directories(Dependencies/GLEW/include)
include_directories(Dependencies/GLFW/include)
include_directories(Dependencies/glm)
include_directories(src)

link_directories(Dependencies/GLEW/lib/Release/x64)
link_directories(Dependencies/GLFW/lib-vc2022)

add_executable(opengl
        src/3DTest.cpp
        src/importDepend.cpp
        src/Main.cpp
        src/review.cpp
        src/shaderSrc.cpp
        src/ShaderTest.cpp
        src/transformation.cpp
        src/Triangle.cpp)




target_link_libraries(opengl glew32s.lib glfw3.lib opengl32.lib)
