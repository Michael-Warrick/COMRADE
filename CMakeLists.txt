cmake_minimum_required(VERSION 3.20.0)
project(COMRADE VERSION 0.0.1 LANGUAGES C CXX)

# Setting C++ Version to 2020
set(CMAKE_CXX_STANDARD 20)

# ASSIMP Configuration
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)

add_subdirectory(engine/vendor/assimp)

# Bullet3 Configuration
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_CPU_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET3_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_CPU_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL "" FORCE)

add_subdirectory(engine/vendor/bullet3)


add_subdirectory(engine/vendor/cmake-glad2)
add_subdirectory(engine/vendor/glfw)
add_subdirectory(engine/vendor/glm)
add_subdirectory(engine/vendor/nativefiledialog-extended)

set(BULLET_SRC_DIR engine/vendor/bullet3/src)
include_directories(${BULLET_SRC_DIR})

LINK_LIBRARIES(
 BulletDynamics BulletCollision LinearMath
)

set(IMGUI_DIR engine/vendor/imgui-docking)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ..)

set(IMGUIZMO_DIR engine/vendor/ImGuizmo)
include_directories(${IMGUIZMO_DIR})

# Adding all source files
add_executable(${PROJECT_NAME}
    # HEADER FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/definitions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/ui.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/shader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/camera.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/texture.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/mesh.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/framebuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/time.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/physics.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/entity.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/component.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/scripting.hpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/COMRADE.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/application.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/gameObject.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/scene.hpp

    # STB_IMAGE HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include/stb_image.h

    # SOURCE FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/ui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/framebuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/time.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/physics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/scripting.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/gameObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/scene.cpp

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

    # IMGUIZMO SOURCES
    ${IMGUIZMO_DIR}/ImGuizmo.cpp
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
        cmake-glad2
        glfw
        glm
        assimp
        nativefiledialog-extended
)

# As of right now, static linking is only available on Windows
if(WIN32)
    # Linking statically
    target_link_libraries(${PROJECT_NAME}
        -static
        cmake-glad2
        glfw
        glm
        assimp
        nfd
    )

    # Telling the compiler to not launch a console window when app is built
    target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
else()
    # Linking dynamically
    target_link_libraries(${PROJECT_NAME}
        cmake-glad2
        glfw
        glm
        assimp
        nfd
    )
endif()

target_compile_options(${PROJECT_NAME} PRIVATE -g)