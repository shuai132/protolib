# protolib

[![Build Status](https://github.com/shuai132/protolib/workflows/build/badge.svg)](https://github.com/shuai132/protolib/actions?workflow=build)

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
* 简单高效，数据零拷贝，可用于大数据量的传输。
* 可自定义连接层实现，支持多种连接方式。

## 使用方法
几个概念：
* [Connection](core/Connection.h): 消息连接 消息收发的接口
* [MsgManager](core/MsgManager.h): 消息管理 用于注册和发送消息

使用例子：
* [example/protolib_example.cpp](example/protolib_example.cpp)

## 消息格式/协议
消息格式基于Protobuf3，Msg类型供消息收发，基础结构如下：
```
message Msg {
    uint32 seq = 1; // 消息id 用于匹配消息响应
    Type type = 2;  // 消息类型 请求/响应
    Any data = 3;   // 消息数据
}
```
[完整协议](proto/Msg.proto)

本库即为上述协议的C++实现，并提供一些特性以方便使用。其他语言可参考实现。
