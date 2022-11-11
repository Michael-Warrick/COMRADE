cmake_minimum_required(VERSION 3.0.0)
project(M_Engine VERSION 0.0.1 LANGUAGES CXX)

# Setting C++ Version to 2020
set(CMAKE_CXX_STANDARD 20)

# External library locations
add_subdirectory(engine/external/glad)
add_subdirectory(engine/external/glfw)
add_subdirectory(engine/external/glm)

set(IMGUI_DIR engine/external/imgui-docking)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ..)

# Adding all source files
add_executable(${PROJECT_NAME}
    # HEADER FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/definitions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/ui.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/shader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/camera.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/texture.hpp

    # STB_IMAGE HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/stb_image.h

    # SOURCE FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/ui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/texture.cpp

    # STB_IMAGE IMPLEMENTATION
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/stb_image_impl.cpp

    # IMGUI SOURCES + BACKENDS
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp 
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp 
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp 
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/engine/resources
    ${PROJECT_BINARY_DIR}/engine/resources
    COMMENT "Copying resources into binary directory"
)

add_dependencies(${PROJECT_NAME} copy_resources)

# Including added libraries
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/engine/include>
        glad
        glfw
        glm
)

# As of right now, static linking is only available on Windows
if(WIN32)
    # Linking statically
    target_link_libraries(${PROJECT_NAME}
        -static
        glad
        glfw
        glm
    )

    # Telling the compiler to not launch a console window when app is built
    target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
else()
    # Linking dynamically
    target_link_libraries(${PROJECT_NAME}
        glad
        glfw
        glm
    )
endif()