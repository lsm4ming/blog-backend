#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$SCRIPT_DIR/../"

# 设置构建目录
BUILD_DIR="$PROJECT_DIR/build"

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