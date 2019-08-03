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
    MsgDispatcher::getInstance()->regist(Msg::PING, [](const Msg& param) {
        LOGD("get PING");
        auto msg = static_cast<Msg>(param);
        msg.set_cmd(Msg::PONG);
        return ProtoUtils::CreateRspMsg(msg.seq(), msg);
    });
}
