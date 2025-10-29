#! /bin/bash

export VCPKG_ROOT=/Users/lerkapic/Desktop/Development/vcpkg
export PATH=$VCPKG_ROOT:$PATH

vcpkg install
cmake \
  -G Xcode \
  -B cmake-build-debug-macos-xcode \
  -S . \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_TOOLCHAIN_FILE=/Users/lerkapic/Desktop/Development/vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=arm64-osx
