cmake_minimum_required(VERSION 3.25)
project(demo1)

set(CMAKE_CXX_STANDARD 14)

include_directories(Dependencies/GLEW/include)
include_directories(Dependencies)
include_directories(Dependencies/GLEW/include)
include_directories(Dependencies/GLFW/include)

add_executable(demo1
        src/3DTest.cpp
        src/importDepend.cpp
        src/Main.cpp
        src/shaders.h
        src/shaderSrc.cpp
        src/ShaderTest.cpp
        src/transformation.cpp
        src/Triangle.cpp src/CoordinateSystem.cpp src/Util.h src/Camera.cpp src/Util.cpp src/Camera.h src/Light.cpp)

target_link_libraries(demo1 ${CMAKE_SOURCE_DIR}/Dependencies/GLEW/lib/Release/x64/glew32s.lib ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib-vc2022/glfw3.lib opengl32.lib)
