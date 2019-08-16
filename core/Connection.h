#pragma once

#include <string>
#include <functional>

namespace protolib {

/**
 * 消息连接器
 * 约定消息发送和接收的接口
 */
class Connection {
public:
    using PayloadHandle = std::function<void(const std::string& msg)>;

public:
    Connection();
    virtual ~Connection() = default;

public:
    virtual void sendPayload(const std::string& payload) = 0;

    inline void setPayloadHandle(const PayloadHandle& handle) {
        payloadHandle_ = handle;
    }

protected:
    void onPayload(const std::string& payload);

private:
    PayloadHandle payloadHandle_ = nullptr;
};


/**
 * 回环消息连接器
 * 多用于测试
 */
class LoopbackConnection : public Connection {
public:
    void sendPayload(const std::string& payload) override {
        onPayload(payload);
    }
};

}
