cmake_minimum_required(VERSION 3.1)

project(protolib CXX)

# option
option(protolib_BUILD_PROTOBUF "build protobuf" ON)

option(protolib_USER_PROTO_ON "generate target for proc user proto files" OFF)
# set(protolib_USER_PROTO_DIR "proto files dir")
# set(protolib_USER_PROTO_OUT "proto output dir")

# protobuf(3.9.0)
if (protolib_BUILD_PROTOBUF)
    message("build protobuf in protolib")
    option(protobuf_VERBOSE ON)
    option(protobuf_BUILD_TESTS OFF)
    option(protobuf_BUILD_PROTOC_BINARIES OFF)
    add_subdirectory(third_party/protobuf/cmake protobuf)
    link_libraries(libprotobuf)
endif()

# common
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall)

# build library
add_library(${PROJECT_NAME}
        STATIC
        proto/cpp/Msg.pb.cc
        core/ProtoUtils.cpp
        core/MsgDispatcher.cpp
        core/Connection.cpp
        core/MsgManager.cpp
        )
link_libraries(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC . core)

# log
include_directories(modules/log)

# example
add_subdirectory(example)

# protoc
# 指定库的proto文件路径和生成目录
set(LIB_PROTO_DIR ${CMAKE_CURRENT_LIST_DIR}/proto)
set(LIB_PROTO_OUT ${CMAKE_CURRENT_LIST_DIR}/proto/cpp)
set(SCRIPTS_DIR ${CMAKE_CURRENT_LIST_DIR}/scripts)
add_custom_target(update_proto_lib sh ${SCRIPTS_DIR}/update_proto.sh ${LIB_PROTO_DIR} ${LIB_PROTO_OUT})

# 指定例子proto文件路径和生成目录
set(EXAMPLE_PROTO_DIR ${CMAKE_CURRENT_LIST_DIR}/example/proto)
set(EXAMPLE_PROTO_OUT ${CMAKE_CURRENT_LIST_DIR}/example/proto/cpp)
add_custom_target(update_proto_example sh ${SCRIPTS_DIR}/update_proto.sh ${EXAMPLE_PROTO_DIR} ${EXAMPLE_PROTO_OUT})

# 指定用户proto文件路径和生成目录
if (protolib_USER_PROTO_ON)
    if (NOT EXISTS ${protolib_USER_PROTO_DIR})
        message(FATAL_ERROR "protolib_USER_PROTO_DIR not set!")
    else()
        add_custom_target(update_proto_user sh ${SCRIPTS_DIR}/update_proto.sh ${protolib_USER_PROTO_DIR} ${protolib_USER_PROTO_OUT})
    endif()
endif()
