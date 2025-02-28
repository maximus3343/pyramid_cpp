cmake_minimum_required(VERSION 3.19) # Minimum version of CMake required

project(Triangle_Rendering) # Name of your project

# Set C++ standard (you can change this to any standard you prefer)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find the required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(SOURCES
    src/main.cpp
    src/shader.cpp
    src/pyramid.cpp
    src/input.cpp
    src/renderer.cpp)

# Add include directories to the root project
set(INCLUDE_DIRS
    src/include
)

# Create an executable from the source files
add_executable(main ${SOURCES})

target_include_directories(main PRIVATE ${INCLUDE_DIRS})

# Link the libraries    
target_link_libraries(main 
    ${OPENGL_LIBRARIES} 
    ${GLEW_LIBRARIES} 
    glfw
)