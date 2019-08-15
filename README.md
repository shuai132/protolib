# protolib

a simple RPC library for C++ based on Protobuf.

简单的C++ RPC库，基于Protobuf。

## Requirements
* C++11
* CMake 3.1
* Protobuf 3.9.0 (already included)

## 介绍
完善的RPC框架(如gRPC)的使用还是有一定复杂性和学习成本的。
在一些不需要复杂功能项目上，大多数只需要一个消息解析功能，尤其是嵌入式软件项目的方案。

## 功能和特点
* 实现了消息的订阅和发送。内部自动对消息进行封装、解析和分发。
* 提供了简单的调用方式，只需使用protobuf定义消息即可。
* 简单高效，零数据拷贝，可用于大数据量的传输。
* 不包含连接层实现，提供了自定义实现的接口。

## 待完善
* 消息超时机制
* 错误和异常处理

## 使用方法
[example/protolib_example.cpp](example/protolib_example.cpp)
