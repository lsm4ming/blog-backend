include(FetchContent)

# 下载cpp-tools
FetchContent_Declare(
        cpptools
        GIT_REPOSITORY https://gitee.com/lsm1998_admin/cpp-tools.git
        GIT_TAG main
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(cpptools)