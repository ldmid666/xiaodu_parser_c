# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
set(OBJECT "parser_c")

# 项目信息
project (${OBJECT})

include_directories(
    ${PROJECT_SOURCE_DIR}/httpd
    ${PROJECT_SOURCE_DIR}/grpc_proto
    ${PROJECT_SOURCE_DIR}/dev_proto
    ${PROJECT_SOURCE_DIR}/aes/include
)
aux_source_directory(. DIR_SRCS)
# 添加 proto 子目录
add_subdirectory(grpc_proto)
add_subdirectory(dev_proto)
add_subdirectory(httpd)
add_subdirectory(aes)
set(CMAKE_C_FLAGS "-g -g3 -ggdb3 -gdwarf-2")

# 指定生成目标
add_executable(${OBJECT} ${DIR_SRCS})
# 添加链接库
target_link_libraries(${OBJECT} grpc_proto)
target_link_libraries(${OBJECT} dev_proto)
target_link_libraries(${OBJECT} httpd)
target_link_libraries(${OBJECT} aes)
target_link_libraries(${OBJECT} protobuf-c grpc grpc-c)



