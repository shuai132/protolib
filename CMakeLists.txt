cmake_minimum_required(VERSION 3.1)

project(protolib)

# common
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall)

# protobuf(3.9.0)
option(BUILD_PROTOBUF ON)
if (BUILD_PROTOBUF)
    message("build protobuf in protolib")
    option(protobuf_VERBOSE ON)
    option(protobuf_BUILD_TESTS OFF)
    option(protobuf_BUILD_PROTOC_BINARIES OFF)
    add_subdirectory(third_party/protobuf/cmake protobuf)
    link_libraries(libprotobuf)
endif()

# protolib
# 指定用户proto文件路径和生成目录
set(USER_PROTO_DIR ${CMAKE_CURRENT_LIST_DIR}/example/proto)
set(USER_PROTO_OUT ${CMAKE_CURRENT_LIST_DIR}/example/proto/cpp)

# build library
include_directories(.)
add_library(${PROJECT_NAME}
        STATIC
        proto/cpp/Msg.pb.cc
        core/ProtoUtils.cpp
        core/MsgDispatcher.cpp
        core/Connection.cpp
        core/MsgManager.cpp
        )
link_libraries(${PROJECT_NAME})

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

# 指定用户proto文件路径和生成目录
if (NOT EXISTS ${USER_PROTO_DIR} OR NOT EXISTS ${USER_PROTO_OUT})
    message(FATAL_ERROR "USER_PROTO_DIR and USER_PROTO_OUT must be set!")
endif()
add_custom_target(update_proto_user sh ${SCRIPTS_DIR}/update_proto.sh ${USER_PROTO_DIR} ${USER_PROTO_OUT})
