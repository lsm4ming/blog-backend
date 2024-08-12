#!/bin/bash

conan install conanfile.txt --output-folder=cmake-build-debug --build=missing -s build_type=Release

cmake . -B build -DCMAKE_TOOLCHAIN_FILE=cmake-build-debug/conan_toolchain.cmake

cmake --build build --target all

echo "Build completed successfully"