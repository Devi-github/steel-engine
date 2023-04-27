cmake_minimum_required(VERSION 3.20)

project(steel-engine)

add_subdirectory(external)

include_directories(
    external/glfw-3.3.8/include/
    external/glew-2.1.0/include/
    external/imgui/
)

add_subdirectory(src)
