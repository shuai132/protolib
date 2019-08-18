#include "core/MsgManager.h"
#include "proto/cpp/AppMsg.pb.h"
#include "log.h"

using namespace protolib;
using namespace Type;

/**
 * 消息收发示例
 *
 * 自定义的几个命令 测试不同收发方式的使用方法
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

    // 注册和发送消息 根据使用场景不同 提供以下几种方式
    // 此处收发类型均为StringValue 实际场景可为其他自定义的protobuf的Message类型
    {
        // 待测试消息
        StringValue message_hello;
        message_hello.set_value(HELLO_PAYLOAD);

        // 1. sender发送命令 subscriber返回操作状态
        {
            msgManager.subscribe(AppMsg::HELLO1, [] {
                LOGI("get AppMsg::HELLO1:");
                return true;
            });
            msgManager.send(AppMsg::HELLO1, [](bool success) {
                LOGI("get rsp from AppMsg::HELLO1: success=%s", success ? "true" : "false");
            });
        }

        // 2. sender发送数据 subscriber返回操作状态
        {
            msgManager.subscribe<StringValue>(AppMsg::HELLO3, [&](StringValue msg) {
                LOGI("get AppMsg::HELLO3: %s", msg.value().c_str());
                assert(msg.value() == HELLO_PAYLOAD);
                return true;
            });
            msgManager.send(AppMsg::HELLO3, message_hello, [](bool success) {
                LOGI("get rsp from AppMsg::HELLO3: success=%s", success ? "true" : "false");
            });
        }

        // 3. sender请求数据 subscriber返回数据操作状态
        {
            msgManager.subscribe<StringValue>(AppMsg::HELLO2, [&]() {
                LOGI("get AppMsg::HELLO2:");
                return R(message_hello, true);  // 也可以直接返回message或者bool
            });
            msgManager.send<StringValue>(AppMsg::HELLO2, [&](RspType<StringValue> rsp) {
                LOGI("get rsp from AppMsg::HELLO2: success=%s", rsp.success ? "true" : "false");
                if (rsp.success) {
                    LOGI("msg=%s", rsp.message.value().c_str());
                    assert(rsp.message.value() == HELLO_PAYLOAD);
                }
            });
        }

        // 4. sender收发消息
        {
            msgManager.subscribe<StringValue, StringValue>(AppMsg::HELLO4, [&](StringValue msg) {
                LOGI("get AppMsg::HELLO4: %s", msg.value().c_str());
                assert(msg.value() == HELLO_PAYLOAD);
                return R(message_hello, true);    // 也可以直接返回msg或者bool
            });
            msgManager.send<StringValue>(AppMsg::HELLO4, message_hello, [&](RspType<StringValue> rsp) {
                LOGI("get rsp from AppMsg::HELLO4: success=%s", rsp.success ? "true" : "false");
                if (rsp.success) {
                    LOGI("msg=%s", rsp.message.value().c_str());
                    assert(rsp.message.value() == HELLO_PAYLOAD);
                }
            });
        }
    }

    // ping
    {
        msgManager.sendPing(HELLO_PAYLOAD, [&](const std::string& payload) {
            LOGI("get rsp from ping: %s", payload.c_str());
            assert(payload == HELLO_PAYLOAD);
        });
    }

    return 0;
}
