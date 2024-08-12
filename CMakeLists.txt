cmake_minimum_required(VERSION 3.10)

project(blog-backend)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(includes)

# 扫描src目录内所有cpp文件
file(GLOB_RECURSE CPP_SOURCES src/*.cpp)

message(STATUS "RECURSE FILE IS:" ${CPP_SOURCES})

# 添加三方库
add_subdirectory(third_party)

add_executable(blog-backend main.cpp ${CPP_SOURCES})

# 导入mongodb驱动
find_package(mongocxx REQUIRED)
# 导入mysql驱动
find_package(libmysqlclient REQUIRED)
# 导入redis驱动
find_package(redis++ REQUIRED)

target_link_libraries(blog-backend cpptools mongo::mongocxx_static libmysqlclient::libmysqlclient redis++::redis++_static)

add_executable(insert-data-test tests/insert_data.cpp ${CPP_SOURCES})

target_link_libraries(insert-data-test cpptools mongo::mongocxx_static libmysqlclient::libmysqlclient redis++::redis++_static)