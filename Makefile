profile:
	conan profile detect

install:
	conan install . --output-folder=cmake-build-debug --build=missing -s build_type=Debug

cmake:
	cd cmake-build-debug && cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

image:
	conan remote add conan-center "https://mirrors.tuna.tsinghua.edu.cn/artifactory/api/conan/conan-center"
	conan remote add conan-community "https://mirrors.tuna.tsinghua.edu.cn/artifactory/api/conan/conan-community"
	conan remote add bincrafters "https://mirrors.tuna.tsinghua.edu.cn/artifactory/api/conan/bincrafters"

build:
	cd cmake-build-debug && make

deploy: install cmake build
	@mv cmake-build-debug/blog-backend ./deploy
	echo "deploy completed successfully"

# clion记得添加Cmake选项参数
# -DCMAKE_TOOLCHAIN_FILE=./cmake-build-debug/conan_toolchain.cmake