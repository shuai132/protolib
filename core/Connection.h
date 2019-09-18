#pragma once

#include <string>
#include <functional>

#include "noncopyable.h"

namespace protolib {

/**
 * 消息连接
 * 约定消息发送和接收的接口
 */
class Connection : public noncopyable {
public:
    using PayloadHandle = std::function<void(const std::string& payload)>;

public:
    Connection() = default;
    virtual ~Connection() = default;

public:
    virtual void sendPayload(const std::string& payload);

    void onPayload(const std::string& payload);

    void setOnPayloadHandle(const PayloadHandle& handle);

    void setSendPayloadFunc(const PayloadHandle& handle);

private:
    PayloadHandle onPayloadHandle_;
    PayloadHandle sendPayloadFunc_;
};


/**
 * 回环消息连接
 * 多用于测试
 */
class LoopbackConnection : public Connection {
public:
    void sendPayload(const std::string& payload) override {
        onPayload(payload);
    }
};

}
