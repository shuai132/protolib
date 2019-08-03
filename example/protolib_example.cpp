#include "core/MsgDispatcher.h"
#include "core/ProtoUtils.h"
#include "core/Connection.h"
#include "proto/cpp/AppMsg.pb.h"
#include "log.h"

/**
 * 命令AppMsg::HELLO 对应数据类型为AppMsg::HelloPayload
 * 此示例演示消息的收发
 * 1. 发送payload(此处为hello_payload_string)
 * 2. 接收payload并原样返回它
 * 3. 此时发送者会受到消息回复也是payload
 */
int main() {
    // 回环的连接 用于测试 实际场景应为具体的传输协议实现的Connection
    LoopbackConnection connection;

    // 测试payload
    const std::string hello_payload_string("hello payload");

    // 初始化连接
    {
        connection.setPayloadHandle([&](const std::string& payload){
            MsgDispatcher::getInstance()->dispatcher(&connection, ProtoUtils::ParsePayload(payload));
        });
    }

    // 注册消息
    {
        auto dispatcher = MsgDispatcher::getInstance();

        dispatcher->registerCmd(AppMsg::HELLO, [&](const Msg& msg) {
            LOGI("get HELLO");
            auto helloPayload = ProtoUtils::UnpackMsgData<StringValue>(msg);
            LOGI("payload:%s", helloPayload.value().c_str());
            assert(helloPayload.value() == hello_payload_string);
            // 原样返回payload
            return ProtoUtils::CreateRspMsg(msg.seq(), helloPayload);
        });
    }

    // 发送消息和接收响应
    {
        // hello
        {
            // 构造消息
            StringValue helloPayload;
            helloPayload.set_value(hello_payload_string);

            // 指定消息类型创建payload
            auto payload = ProtoUtils::CreateCmdPayload<AppMsg::HELLO>(helloPayload, [&](const Msg& msg) {
                LOGI("get resp from HELLO");
                auto helloPayload = ProtoUtils::UnpackMsgData<StringValue>(msg);
                LOGI("payload:%s", helloPayload.value().c_str());
                assert(helloPayload.value() == hello_payload_string);
            });

            // 发送数据
            connection.sendPayload(payload);
        }

        // ping
        {
            StringValue ping;
            ping.set_value("ping payload");
            connection.sendPayload(ProtoUtils::CreateCmdPayload<Msg::PING>(ping, [](const Msg& msg) {
                auto rsp = ProtoUtils::UnpackMsgData<StringValue>(msg).value();
                LOGI("get resp from ping:%s", rsp.c_str());
            }));
        }
    }

    return 0;
}
