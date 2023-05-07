find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(SOURCE_FILES main.cpp steel.hpp
    core/application.cpp core/steel_imgui.cpp
    core/scene_manager.cpp core/mesh.cpp
    core/object.cpp core/component.cpp
    core/components/transform.cpp
    core/material.cpp gameengine/camera.cpp
    core/shader.cpp
    gameengine/primitives.cpp gameengine/lighting.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} glew glfw OpenGL imgui glm::glm)
