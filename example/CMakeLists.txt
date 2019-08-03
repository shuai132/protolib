cmake_minimum_required(VERSION 3.1)

project(protolib_example)

if (NOT EXISTS ${PROTOBUF_DIR})
    message(FATAL_ERROR
            "PROTOBUF_DIR must be set!"
            "git clone --branch=lib https://gitee.com/shuai132/protobuf"
            )
endif()

# common
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall)

# protobuf
option(protobuf_VERBOSE ON)
option(protobuf_BUILD_TESTS OFF)
option(protobuf_BUILD_PROTOC_BINARIES OFF)
add_subdirectory(${PROTOBUF_DIR}/cmake protobuf)
link_libraries(libprotobuf)

# protolib
set(PROTOLIB_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
# 指定用户proto文件路径和生成目录
set(USER_PROTO_DIR ${CMAKE_CURRENT_LIST_DIR}/proto)
set(USER_PROTO_OUT ${CMAKE_CURRENT_LIST_DIR}/proto/cpp)
add_subdirectory(${PROTOLIB_DIR} protolib)
include_directories(${PROTOLIB_DIR})
#link_libraries(protolib)

add_executable(${PROJECT_NAME} protolib_example.cpp)
