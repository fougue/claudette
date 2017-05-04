#!/bin/bash

# Make the script fails on any command error
set -e

# CMake options as environment variables
if [ -n "${TRAVIS_GCC_VERSION}" ]; then
    export CC=gcc-$TRAVIS_GCC_VERSION
    export CXX=g++-$TRAVIS_GCC_VERSION
fi

# Run CMake
mkdir build && cd build
cmake --version

cmake .. -G "Unix Makefiles"       \
         -DCMAKE_DEBUG_POSTFIX=_d  \
         -DCMAKE_BUILD_TYPE=$TRAVIS_BUILD_TYPE \
         -DCMAKE_INSTALL_PREFIX=../install

# Make
make -j4
make install

