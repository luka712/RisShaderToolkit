#!/bin/bash

export VCPKG_ROOT=/path/tp/vcpkg
export PATH=$VCPKG_ROOT:$PATH

# Build
cmake \
  -G Ninja \
  -B cmake-build-debug-linux-xcode \
  -S . \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_TOOLCHAIN_FILE=//path/tp/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build cmake-build-debug
