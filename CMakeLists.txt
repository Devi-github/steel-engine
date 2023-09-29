cmake_minimum_required(VERSION 3.20)

project(steel-engine)

set(STEEL_BUILD_WINDOWS ON)

if(${STEEL_BUILD_WINDOWS})
    find_package(OpenGL REQUIRED)

    include_directories(include)
    link_directories(libs)

    add_subdirectory(external/imgui)
    add_subdirectory(external/fmt)

    include_directories(
        external/imgui/
    )
else()
    find_package(OpenGL REQUIRED)
    find_package(glfw3)
    find_package(GLEW)
    find_package(glm)
    find_package(fmt)

    #add_subdirectory(external)

    if(TARGET glfw) # Works for some reason. GLFW_FOUND does not...
        include_directories(GLFW_INCLUDE_DIRS)
    else()
        # If GLFW not found, link from source
        add_subdirectory(external/glfw-3.3.8)
        include_directories(external/glfw-3.3.8/include)
    endif()

    if(GLEW_FOUND)
        include_directories(GLEW_INCLUDE_DIRS)
    else()
        add_subdirectory(external/glew-2.1.0/build/cmake)
        include_directories(external/glew-2.1.0/include)
    endif()

    add_subdirectory(external/imgui)

    include_directories(
        external/imgui/
    )
endif()

add_subdirectory(src)
