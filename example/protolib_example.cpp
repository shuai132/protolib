#include "core/MsgManager.h"
#include "proto/cpp/AppMsg.pb.h"
#include "log.h"

/**
 * 消息收发示例
 *
 * 自定义的AppMsg::HELLO命令 (此示例发送和响应的类型均为StringValue)
 * 发送 =======CmdMessageType=====> 接收
 * 响应 <======RspMessageType====== 回复
 */
int main() {
    // 回环的连接 用于测试 实际使用应为具体传输协议实现的Connection
    auto connection = std::make_shared<LoopbackConnection>();

    // 创建MsgManager 收发消息
    MsgManager msgManager(connection);

    // 测试所用payload
    const std::string HELLO_PAYLOAD("hello payload");

    // 注册消息
    {
        msgManager.registerCmd<StringValue, StringValue>(AppMsg::HELLO, [&](StringValue msg) {
            LOGI("get AppMsg::HELLO: %s", msg.value().c_str());
            assert(msg.value() == HELLO_PAYLOAD);
            return msg; // 原样返回
        });
    }

    // 发送消息并设置响应回调
    {
        // 构造消息
        StringValue message;
        message.set_value(HELLO_PAYLOAD);

        // 发送消息
        msgManager.sendMessage<StringValue>(AppMsg::HELLO, message, [&](const StringValue& msg) {
            LOGI("get resp from AppMsg::HELLO: %s", msg.value().c_str());
            assert(msg.value() == HELLO_PAYLOAD);
        });
    }

    // ping
    {
        msgManager.sendPing("ping payload", [&](const std::string& msg) {
            LOGI("get resp from ping: %s", msg.c_str());
        });
    }

    return 0;
}
