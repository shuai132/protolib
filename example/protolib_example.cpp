#include "core/MsgDispatcher.h"
#include "core/ProtoUtils.h"
#include "core/Connection.h"
#include "proto/cpp/AppMsg.pb.h"
#include "log.h"

int main() {
    LoopbackConnection connection;

    const std::string hello_payload_string("hello payload");
    {
        auto dispatcher = MsgDispatcher::getInstance();

        dispatcher->regist(AppMsg::HELLO, [&](const Msg& param) {
            LOGF("get HELLO");
            auto helloPayload = ProtoUtils::UnpackMsgData<AppMsg::HelloPayload>(param);
            LOGF("payload:%s", helloPayload.payload().c_str());
            assert(helloPayload.payload() == hello_payload_string);
            return ProtoUtils::CreateRspMsg(param.seq());
        });
    }

    // 初始化连接
    {
        connection.setPayloadHandle([&](const std::string& payload){
            MsgDispatcher::getInstance()->dispatcher(&connection, ProtoUtils::ParsePayload(payload));
        });
    }

    // 包装数据
    {
        // hello
        {
            // 构造消息
            AppMsg::HelloPayload helloPayload;
            helloPayload.set_payload(hello_payload_string);

            // 指定消息类型创建payload
            auto payload = ProtoUtils::CreateCmdPayload<AppMsg::HELLO>(helloPayload);

            // 发送数据
            connection.sendPayload(payload);
        }

        // ping
        {
            Msg::Payload ping;
            ping.set_payload("ping payload");
            connection.sendPayload(ProtoUtils::CreateCmdPayload<Msg::PING>(ping));
        }
    }

    return 0;
}
