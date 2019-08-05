#include "core/MsgManager.h"
#include "proto/cpp/AppMsg.pb.h"
#include "log.h"

using namespace Type;

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
        // 注册消息 当接收到时原样返回
        msgManager.registerCmd<StringValue, StringValue>(AppMsg::HELLO, [&](StringValue msg) {
            LOGI("get AppMsg::HELLO: %s", msg.value().c_str());
            assert(msg.value() == HELLO_PAYLOAD);
            // 第一种方式: 直接返回特定信息类型 操作状态需在msg中判断 等效于第二种方式设置true
            // return msg;
            // 第二种方式: 顺带返回一个操作状态
            return R(msg, true);
        });
    }

    // 发送消息并设置响应回调
    {
        // 构造消息
        StringValue message;
        message.set_value(HELLO_PAYLOAD);

        // 发送消息
        msgManager.sendMessage<StringValue>(AppMsg::HELLO, message, [&](StringValue msg) {
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
