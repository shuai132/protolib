#include "MsgManager.h"

namespace protolib {

MsgManager::MsgManager(const std::shared_ptr<Connection>& conn)
        : conn_(conn), dispatcher_(conn) {
}

std::shared_ptr<Connection> MsgManager::getConn() const {
    return conn_;
}

void MsgManager::sendPing(const string& payload, const MsgManager::PingCallback& cb) {
    StringValue stringValue;
    stringValue.set_value(payload);
    sendMessage(Msg::PING, stringValue, [cb](const Msg& msg) {
        cb(ProtoUtils::UnpackMsgData<StringValue>(msg).value());
    });
}

void MsgManager::sendMessage(MsgManager::CmdType cmd, const Message& message, const MsgManager::RspCallback& cb) {
    // 指定消息类型创建payload
    conn_->sendPayload(CreateMessagePayload(cmd, message, cb));
}

std::string
MsgManager::CreateMessagePayload(MsgManager::CmdType cmd, const Message& message, const MsgManager::RspCallback& cb) {
    std::string payload;
    auto msg = ProtoUtils::CreateCmdMsg(cmd, message);
    bool ret = msg.SerializeToString(&payload);
    throw_if(not ret);
    dispatcher_.subscribeRsp(msg.seq(), cb);
    return payload;
}

}
