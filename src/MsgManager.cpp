#include "MsgManager.h"

namespace protolib {

MsgManager::MsgManager(std::shared_ptr<Connection> conn, std::shared_ptr<coder::Coder> coder)
        : conn_(conn), dispatcher_(std::move(conn), std::move(coder)) {
}

std::shared_ptr<Connection> MsgManager::getConn() const {
    return conn_;
}

void MsgManager::sendPing(const string& payload, const MsgManager::PingCallback& cb, const TimeoutCb& timeoutCb, uint32_t timeoutMs) {
    StringValue stringValue;
    stringValue.set_value(payload);
    sendMessage(Msg::PING, stringValue, [cb](const Msg& msg) {
        if (cb == nullptr) return;
        cb(utils::UnpackMsgData<StringValue>(msg).value());
    }, timeoutCb, timeoutMs);
}

void MsgManager::sendMessage(CmdType cmd, const Message& message, const MsgManager::RspCallback& cb, const TimeoutCb& timeoutCb, uint32_t timeoutMs) {
    // 指定消息类型创建payload
    conn_->sendPayload(CreateMessagePayload(cmd, message, cb, timeoutCb, timeoutMs));
}

std::string
MsgManager::CreateMessagePayload(CmdType cmd, const Message& message, const MsgManager::RspCallback& cb, const TimeoutCb& timeoutCb, uint32_t timeoutMs) {
    std::string payload;
    auto msg = utils::CreateCmdMsg(cmd, message);
    bool ret = msg.SerializeToString(&payload);
    throw_if(not ret);
    dispatcher_.subscribeRsp(msg.seq(), cb, timeoutCb, timeoutMs);
    return payload;
}

void MsgManager::setTimerFunc(const MsgDispatcher::SetTimeout& timerFunc) {
    dispatcher_.setTimerFunc(timerFunc);
}

}
