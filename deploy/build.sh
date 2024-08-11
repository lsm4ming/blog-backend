#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$SCRIPT_DIR/../"

# 设置构建目录
BUILD_DIR="$PROJECT_DIR/build"

# 创建构建目录（如果不存在）
mkdir -p "$BUILD_DIR"

# 进入构建目录
cd "$BUILD_DIR" || exit

# 运行 CMake 配置
cmake "$PROJECT_DIR" || { echo "CMake configuration failed"; exit 1; }

# 运行 CMake 构建
cmake --build . || { echo "Build failed"; exit 1; }

# 运行 make 构建
make || { echo "Build failed"; exit 1; }

# 输出构建成功消息
echo "Build completed successfully"

# 将构建的目标文件拷贝到输出目录
cp -r "$BUILD_DIR" "$PROJECT_DIR/deploy"
# 拷贝配置文件
cp "$PROJECT_DIR/config/config.ini" "$PROJECT_DIR/deploy"

# 执行deploy目录内的makefile
cd "$PROJECT_DIR/deploy" || exit

make stop

make clear

make build

make run