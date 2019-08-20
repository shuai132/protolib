#include "MsgDispatcher.h"
#include "log.h"
#include "ProtoUtils.h"

namespace protolib {

MsgDispatcher& MsgDispatcher::getInstance() {
    static MsgDispatcher dispatcher;
    return dispatcher;
}

void MsgDispatcher::dispatch(Connection* conn, const Msg& msg) {
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
            conn->sendPayload(ProtoUtils::CreatePayload(resp));
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

}
