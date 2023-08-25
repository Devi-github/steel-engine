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
    core/material.cpp core/shader.cpp
    
    gameengine/primitives.cpp gameengine/lighting.cpp
    gameengine/camera.cpp gameengine/arrows.cpp
)

set(GLSL_VALIDATOR /usr/bin/glslangValidator)

set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(RESOURCES_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/resources)

file(GLOB GLSL_SOURCE_FILES
    ${RESOURCES_DIR}/*.frag
    ${RESOURCES_DIR}/*.vert
    ${RESOURCES_DIR}/*.comp
)

add_custom_command(
    COMMAND
        ${CMAKE_COMMAND} -E make_directory ${RESOURCES_BINARY_DIR}
    OUTPUT ${RESOURCES_BINARY_DIR}
    COMMENT "Creating ${RESOURCES_BINARY_DIR}"
)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

message("Shader source files: ${GLSL_SOURCE_FILES}")

foreach(source IN LISTS ${GLSL_SOURCE_FILES})
    get_filename_component(FILENAME ${source} NAME)
    add_custom_command(
        COMMAND
            ${GLSL_VALIDATOR}
            -V -G
            -o ${RESOURCES_BINARY_DIR}/${FILENAME}.spv
            ${source}
        OUTPUT ${RESOURCES_BINARY_DIR}/${FILENAME}.spv
        DEPENDS ${source} ${RESOURCES_BINARY_DIR}
        COMMENT "Compiling ${FILENAME}"
    )
    list(APPEND SPV_SHADERS ${RESOURCES_BINARY_DIR}/${FILENAME}.spv)
endforeach()

add_custom_target(SHADERS ALL DEPENDS ${SPV_SHADERS})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} glfw OpenGL imgui glm::glm)
