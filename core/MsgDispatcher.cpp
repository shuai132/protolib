#include "MsgDispatcher.h"
#include "log.h"
#include "ProtoUtils.h"

namespace protolib {

MsgDispatcher::MsgDispatcher(std::shared_ptr<Connection> conn) : conn_(std::move(conn)) {
    conn_->setPayloadHandle([this](const std::string& payload){
        this->dispatch(ProtoUtils::ParsePayload(payload));
    });

    // 每一个连接要册一个PING消息，以便有PING到来时，给发送者回复PONG，PING/PONG可携带payload，会原样返回。
    subscribeCmd(Msg::PING, [](const Msg& param) {
        auto msg = static_cast<Msg>(param);
        msg.set_cmd(Msg::PONG);
        return ProtoUtils::CreateRspMsg(msg.seq(), ProtoUtils::UnpackMsgData<StringValue>(std::forward<Msg>(msg)));
    });
}

void MsgDispatcher::dispatch(const Msg& msg) {
    switch (msg.type()) {
        case Msg::COMMAND:
        {
            // COMMAND
            auto cmd = msg.cmd();
            LOGD("dispatch cmd: seq=%d, cmd=%d", msg.seq(), cmd);

            auto iter = cmdHandleMap_.find(cmd);
            if (iter == cmdHandleMap_.cend()) {
                LOGD("not register cmd for: %d", cmd);
                return;
            }
            auto fn = (*iter).second;
            auto resp = fn(msg);
            conn_->sendPayload(ProtoUtils::CreatePayload(resp));
        } break;

        case Msg::RESPONSE:
        {
            LOGD("dispatch rsp: seq=%d, success=%s", msg.seq(), msg.success() ? "true" : "false");
            auto iter = rspHandleMap_.find(msg.seq());
            if (iter == rspHandleMap_.cend()) {
                LOGD("not register callback for response");
                break;
            }
            auto cb = (*iter).second;
            throw_if(not cb, "rsp handle can not be null");
            cb(msg);
            rspHandleMap_.erase(iter);
            LOGD("rspHandleMap_.size=%ld", rspHandleMap_.size());
        } break;

        default:
            throw_if(true, "unknown message type");
    }
}

void MsgDispatcher::subscribeCmd(CmdType cmd, const CmdHandle& handle) {
    LOGD("subscribeCmd cmd:%d, handle:%p", cmd, &handle);
    cmdHandleMap_[cmd] = handle;
}

void MsgDispatcher::unsubscribeCmd(CmdType cmd) {
    auto iter = cmdHandleMap_.find(cmd);
    if (iter != cmdHandleMap_.cend()) {
        LOGD("erase cmd: %d", cmd);
        cmdHandleMap_.erase(iter);
    } else {
        LOGD("not register cmd for: %d", cmd);
    }
}

void MsgDispatcher::subscribeRsp(SeqType seq, const MsgDispatcher::RspHandle& handle) {
    LOGD("subscribeRsp seq:%d, handle:%p", seq, &handle);
    if (handle == nullptr)
        return;
    rspHandleMap_[seq] = handle;
}

void MsgDispatcher::subscribeRsp(const Msg& msg, const MsgDispatcher::RspHandle& handle) {
    subscribeRsp(msg.seq(), handle);
}

std::shared_ptr<Connection> MsgDispatcher::getConn() const {
    return conn_;
}

}
