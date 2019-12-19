#include "MsgManager.h"
#include "proto/cpp/AppMsg.pb.h"
#include "log.h"

using namespace protolib;
using namespace proto;

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
    msgManager.setTimerFunc([](uint32_t ms, const MsgDispatcher::TimeoutCb& cb){
        // 定时器实现 应当配合当前应用的事件循环 确保消息收发和超时在同一个线程
        // 此示例为回环的连接 不需要具体实现
    });

    // 测试所用payload
    const std::string TEST_PAYLOAD("hello world");

    // 注册和发送消息 根据使用场景不同 提供以下几种方式
    // 此处收发类型均为StringValue 实际场景可为其他自定义的protobuf的Message类型
    {
        // 待测试消息
        StringValue test_message;
        test_message.set_value(TEST_PAYLOAD);

        // 1. sender发送命令 subscriber返回操作状态
        {
            msgManager.subscribe(AppMsg::CMD1, [] {
                LOGI("get AppMsg::CMD1:");
                return true;
            });
            msgManager.send(AppMsg::CMD1, [](bool success) {
                LOGI("get rsp from AppMsg::CMD1: success=%s", success ? "true" : "false");
            });
        }

        // 2. sender发送数据 subscriber返回操作状态
        {
            msgManager.subscribe<StringValue>(AppMsg::CMD2, [&](const StringValue& msg) {
                LOGI("get AppMsg::CMD2: %s", msg.value().c_str());
                assert(msg.value() == TEST_PAYLOAD);
                return true;
            });
            msgManager.send(AppMsg::CMD2, test_message, [](bool success) {
                LOGI("get rsp from AppMsg::CMD2: success=%s", success ? "true" : "false");
            });
        }

        // 3. sender请求数据 subscriber返回数据操作状态
        {
            msgManager.subscribe<StringValue>(AppMsg::CMD3, [&]() {
                LOGI("get AppMsg::CMD3:");
                return R(test_message, true);  // 也可以直接返回message或者bool
            });
            msgManager.send<StringValue>(AppMsg::CMD3, [&](const RspType<StringValue>& rsp) {
                LOGI("get rsp from AppMsg::CMD3: success=%s", rsp.success ? "true" : "false");
                if (rsp.success) {
                    LOGI("msg=%s", rsp.message.value().c_str());
                    assert(rsp.message.value() == TEST_PAYLOAD);
                }
            });
        }

        // 4. 双端收发消息
        {
            msgManager.subscribe<StringValue, StringValue>(AppMsg::CMD4, [&](const StringValue& msg) {
                LOGI("get AppMsg::CMD4: %s", msg.value().c_str());
                assert(msg.value() == TEST_PAYLOAD);
                return R(test_message, true);    // 也可以直接返回msg或者bool
            });
            msgManager.send<StringValue>(AppMsg::CMD4, test_message, [&](const RspType<StringValue>& rsp) {
                LOGI("get rsp from AppMsg::CMD4: success=%s", rsp.success ? "true" : "false");
                if (rsp.success) {
                    LOGI("msg=%s", rsp.message.value().c_str());
                    assert(rsp.message.value() == TEST_PAYLOAD);
                }
            });
        }
    }

    // ping
    {
        msgManager.sendPing(TEST_PAYLOAD, [&](const std::string& payload) {
            LOGI("get rsp from ping: %s", payload.c_str());
            assert(payload == TEST_PAYLOAD);
        });
    }

    return 0;
}
