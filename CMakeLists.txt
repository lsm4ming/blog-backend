cmake_minimum_required(VERSION 3.10)

project(blog-backend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(includes)

# 扫描src目录内所有cpp文件
file(GLOB_RECURSE CPP_SOURCES src/*.cpp)

message(STATUS "RECURSE FILE IS:" ${CPP_SOURCES})

# 添加三方库
add_subdirectory(third_party)

add_executable(blog-backend main.cpp ${CPP_SOURCES})

target_include_directories(blog-backend PRIVATE cpp-tools/includes)
target_link_directories(blog-backend PRIVATE cpp-tools)