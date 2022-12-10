# Install script for directory: C:/Dev/OpenGL/M_Engine/engine/external/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/M_Engine")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/mingw64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.2.5-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Dev/OpenGL/M_Engine/build/engine/external/assimp/lib/libassimp.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/anim.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/aabb.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/ai_assert.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/camera.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/color4.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/color4.inl"
    "C:/Dev/OpenGL/M_Engine/build/engine/external/assimp/code/../include/assimp/config.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/ColladaMetaData.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/commonMetaData.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/defs.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/cfileio.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/light.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/material.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/material.inl"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/matrix3x3.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/matrix3x3.inl"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/matrix4x4.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/matrix4x4.inl"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/mesh.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/ObjMaterial.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/pbrmaterial.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/GltfMaterial.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/postprocess.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/quaternion.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/quaternion.inl"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/scene.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/metadata.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/texture.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/types.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/vector2.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/vector2.inl"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/vector3.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/vector3.inl"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/version.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/cimport.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/importerdesc.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Importer.hpp"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/DefaultLogger.hpp"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/ProgressHandler.hpp"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/IOStream.hpp"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/IOSystem.hpp"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Logger.hpp"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/LogStream.hpp"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/NullLogger.hpp"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/cexport.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Exporter.hpp"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/DefaultIOStream.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/DefaultIOSystem.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/SceneCombiner.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/fast_atof.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/qnan.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/BaseImporter.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Hash.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/ParsingUtils.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/StreamReader.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/StreamWriter.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/StringComparison.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/StringUtils.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/SGSpatialSort.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/GenericProperty.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/SpatialSort.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/SmallVector.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/SmoothingGroups.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/SmoothingGroups.inl"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/StandardShapes.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/RemoveComments.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Subdivision.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Vertex.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/LineSplitter.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/TinyFormatter.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Profiler.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/LogAux.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Bitmap.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/XMLTools.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/IOStreamBuffer.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/CreateAnimMesh.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/XmlParser.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/BlobIOSystem.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/MathFunctions.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Exceptional.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/ByteSwapper.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Compiler/poppack1.h"
    "C:/Dev/OpenGL/M_Engine/engine/external/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

