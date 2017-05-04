cmake_minimum_required(VERSION 2.6)

project(claudette)

include(CheckIncludeFiles)
include(scripts/enable_cxx11.cmake)

# Allow the user to build a static library
option(BUILD_SHARED_LIBS "Build shared libraries (DLL)" ON)

# Add source files
file(GLOB  ALL_SRC_FILES  src/*)

# Declare claudette library
add_library(claudette ${ALL_SRC_FILES})

# Specific flags depending on platform
if(WIN32)
    add_definitions(-DNOMINMAX -DFOUG_OS_WINDOWS)
elseif(APPLE)
    add_definitions(-DFOUG_OS_MAC)
elseif(UNIX)
    add_definitions(-DFOUG_OS_UNIX)
endif()

if(BUILD_SHARED_LIBS)
    add_definitions(-DCLAUDETTE_LIB_DLL
                    -DCLAUDETTE_LIB_MAKE_DLL)
endif()

# Declare installs
install(FILES src/collision_model_3d.h
              src/base_collision_test.h
              src/model_collision_test.h
              src/ray_collision_test.h
              src/sphere_collision_test.h
              src/global.h
        DESTINATION include/claudette)
install(TARGETS claudette
          RUNTIME DESTINATION lib
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib)

message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")

# Examples:
#   cmake ../.. -DCMAKE_INSTALL_PREFIX=../../gcc-linux64 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_DEBUG_POSTFIX=.debug
#   cmake ../.. -DCMAKE_INSTALL_PREFIX=../../gcc-linux64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_RELEASE_POSTFIX=.release
# make VERBOSE=1  or  cmake -DCMAKE_VERBOSE_MAKEFILE=TRUE
