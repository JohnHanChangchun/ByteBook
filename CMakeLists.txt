cmake_minimum_required(VERSION 3.10)

# 设置项目名
project(ByteBook)

# 设置源文件
set(SOURCES
    ByteBook.cpp
)

# 设置头文件目录（如果有其他头文件目录，可以添加到这个路径）
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 判断平台，设置动态库的编译选项
if(WIN32)
    # Windows平台的动态库
    add_library(ByteBook SHARED ${SOURCES})
    target_compile_definitions(ByteBook PRIVATE EXPORTS)  # 如果需要定义某些宏，导出动态库符号
    set_target_properties(ByteBook PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE)  # Windows平台导出所有符号（如果需要）
elseif(UNIX)
    # Linux平台的动态库
    add_library(ByteBook SHARED ${SOURCES})
endif()