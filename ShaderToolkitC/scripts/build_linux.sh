#!/bin/bash

export VCPKG_ROOT=/home/luka/Desktop/Development/vcpkg
export PATH=$VCPKG_ROOT:$PATH

# Build
cmake \
  -G Ninja \
  -B cmake-build-debug \
  -S . \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_TOOLCHAIN_FILE=/home/luka/Desktop/Development/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build cmake-build-debug
