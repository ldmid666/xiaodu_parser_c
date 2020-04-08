# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
set(OBJECT "grpc_ser")

# 项目信息
project (${OBJECT})

include_directories(
    ${PROJECT_SOURCE_DIR}/httpd
    ${PROJECT_SOURCE_DIR}/proto
)
aux_source_directory(. DIR_SRCS)
# 添加 proto 子目录
add_subdirectory(proto)
add_subdirectory(httpd)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -g3 -ggdb3 -gdwarf-2")

# 指定生成目标 
add_executable(${OBJECT} ${DIR_SRCS})
# 添加链接库
target_link_libraries(${OBJECT} proto)
target_link_libraries(${OBJECT} httpd)
target_link_libraries(${OBJECT} protobuf-c grpc grpc-c)



