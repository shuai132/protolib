cmake_minimum_required(VERSION 3.1)

project(protolib_example)

add_executable(${PROJECT_NAME}
        protolib_example.cpp
        proto/cpp/AppMsg.pb.cc
        )
