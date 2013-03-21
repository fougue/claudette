cmake_minimum_required(VERSION 2.6)
include(CheckIncludeFiles)

project(fougcoldet)

# Allow the user to build a static library
option(BUILD_SHARED_LIBS "Build shared libraries (DLL)" ON)

# Add source files
file(GLOB  ALL_SRC_FILES  src/*)

# Declare fougcoldet library
add_library(fougcoldet ${ALL_SRC_FILES})

# Specific flags depending on platform
if(WIN32)
  add_definitions(-DFOUG_OS_WINDOWS -DCOLDET_EXPORTS)
elseif(APPLE)
  add_definitions(-DFOUG_OS_MAC)
elseif(UNIX)
  add_definitions(-DFOUG_OS_UNIX)
endif()

#if(BUILD_SHARED_LIBS)
#  add_definitions(-DFOUG_LIB_DLL
#                  -DFOUG_LIB_MAKE_DLL)
#endif()

# Declare installs
install(FILES src/coldet.h DESTINATION include/fougcoldet)
install(TARGETS fougcoldet
          RUNTIME DESTINATION lib
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib)

# Examples:
#   cmake ../.. -DCMAKE_INSTALL_PREFIX=../../gcc-linux64 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_DEBUG_POSTFIX=.debug
#   cmake ../.. -DCMAKE_INSTALL_PREFIX=../../gcc-linux64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_RELEASE_POSTFIX=.release
# make VERBOSE=1  or  cmake -DCMAKE_VERBOSE_MAKEFILE=TRUE
