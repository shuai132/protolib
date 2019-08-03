#include "core/ProtoUtils.h"
#include "log.h"

int main() {
    std::string payload;

    // 包装数据
    {
        // 构造消息
        Msg::Payload ping;
        ping.set_payload("ping");

        // 指定消息类型创建payload
        payload = ProtoUtils::CreateCmdPayload<Msg::PING>(ping);
    }

    // NOTE: 发送payload
    // NOTE: 接收payload

    // 解析数据
    {
        auto msg = ProtoUtils::ParsePayload(payload);
        LOGF("seq:%d, type:%d\n", msg.seq(), msg.type());
        assert(msg.type() == Msg::COMMAND);

        switch (msg.cmd()) {
            case Msg::PING:
            {
                auto addr = ProtoUtils::UnpackMsgData<Msg::Payload>(msg);
                LOGF("payload:%s\n", addr.payload().c_str());
                break;
            }
            default:
            {
                LOGF("unknown cmd:%d\n", msg.cmd());
                break;
            }
        }
    }
    return 0;
}
