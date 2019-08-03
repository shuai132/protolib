#include <modules/log/log.h>
#include "Connection.h"
#include "MsgDispatcher.h"
#include "ProtoUtils.h"

void Connection::onPayload(const std::string& payload) {
    if (payloadHandle_) {
        payloadHandle_(payload);
    }
}

Connection::Connection() {
    // 每一个连接都应注册一个PING消息，以便有PING到来时，给发送者回复PONG，PING/PONG可携带payload，会原样返回。
    MsgDispatcher::getInstance()->registerCmd(Msg::PING, [](const Msg &param) {
        LOGD("get PING");
        auto msg = static_cast<Msg>(param);
        msg.set_cmd(Msg::PONG);
        return ProtoUtils::CreateRspMsg(msg.seq(), ProtoUtils::UnpackMsgData<Msg::Payload>(msg));
    });
}
