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

    // 注册和发送消息
    // 此处收发类型均为StringValue 实际场景可为其他自定义的protobuf的Message类型
    {
        // 待测试消息
        StringValue message_hello;
        message_hello.set_value(HELLO_PAYLOAD);

        // 有以下几种方式 标题描述是针对注册端
        // 1. 不接收参数 返回操作状态bool值
        // 用于简单控制
        {
            msgManager.registerCmd(AppMsg::HELLO1, []() {
                LOGI("get AppMsg::HELLO1:");
                return true;
            });

            // 发送消息
            // 1. 只发送不管返回
            msgManager.sendCtrl(AppMsg::HELLO1);
            // 2. 发送并获取返回状态
            msgManager.sendCtrl(AppMsg::HELLO1, [](bool success) {
                LOGI("get rsp from AppMsg::HELLO1: success=%s", success ? "true" : "false");
            });
        }

        // 2. 不接收参数 返回自定义消息和操作状态
        // 常用于GET行为
        {
            msgManager.registerCmd<StringValue>(AppMsg::HELLO2, [&]() {
                LOGI("get AppMsg::HELLO2:");
                return R(message_hello, true);
            });
            msgManager.sendGet<StringValue>(AppMsg::HELLO2, [&](RspType<StringValue> rsp) {
                LOGI("get rsp from AppMsg::HELLO2: success=%s, msg=%s", rsp.success ? "true" : "false",
                     rsp.message.value().c_str());
                assert(rsp.message.value() == HELLO_PAYLOAD);
            });
        }

        // 3. 接收参数 返回操作状态
        // 常用于SET行为
        {
            msgManager.registerCmd<StringValue>(AppMsg::HELLO3, [&](StringValue msg) {
                LOGI("get AppMsg::HELLO3: %s", msg.value().c_str());
                assert(msg.value() == HELLO_PAYLOAD);
                return R(true);
            });
            msgManager.sendSet(AppMsg::HELLO3, message_hello, [](bool success) {
                LOGI("get rsp from AppMsg::HELLO3: success=%s", success ? "true" : "false");
            });
        }
        // 4. 接收参数 且返回自定义消息和操作状态
        // 用于复杂操作场景 收发消息 类似POST行为
        {
            msgManager.registerCmd<StringValue, StringValue>(AppMsg::HELLO4, [&](StringValue msg) {
                LOGI("get AppMsg::HELLO4: %s", msg.value().c_str());
                assert(msg.value() == HELLO_PAYLOAD);
                return R(msg, true);
            });
            msgManager.sendPost<StringValue>(AppMsg::HELLO4, message_hello, [&](RspType<StringValue> rsp) {
                LOGI("get rsp from AppMsg::HELLO4: success=%s, msg=%s", rsp.success ? "true" : "false",
                     rsp.message.value().c_str());
                assert(rsp.message.value() == HELLO_PAYLOAD);
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
