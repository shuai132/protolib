#include "MsgDispatcher.h"
#include "log.h"
#include "ProtoUtils.h"

MsgDispatcher* MsgDispatcher::getInstance() {
    static MsgDispatcher dispatcher;
    return &dispatcher;
}

void MsgDispatcher::dispatcher(Connection* conn, const Msg& msg) {
    switch (msg.type()) {
        case Msg::COMMAND:
        {
            // COMMAND
            auto cmd = msg.cmd();
            LOGD("dispatcher cmd: seq=%d, cmd=%d", msg.seq(), cmd);

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
            LOGD("dispatcher rsp: seq=%d, success=%s", msg.seq(), msg.success() ? "true" : "false");
            auto iter = rspHandleMap_.find(msg.seq());
            if (iter == rspHandleMap_.cend()) {
                LOGD("not register callback for response");
                break;
            }
            auto cb = (*iter).second;
            assert(cb);
            cb(msg);
            rspHandleMap_.erase(iter);
            LOGD("rspHandleMap_.size=%ld", rspHandleMap_.size());
        } break;

        default:
            assert(false);
    }
}

void MsgDispatcher::registerCmd(CmdType cmd, const CmdHandle& handle) {
    cmdHandleMap_[cmd] = handle;
}

void MsgDispatcher::registerRsp(SeqType seq, const MsgDispatcher::RspHandle& handle) {
    if (handle == nullptr)
        return;
    rspHandleMap_[seq] = handle;
}

void MsgDispatcher::registerRsp(const Msg &msg, const MsgDispatcher::RspHandle &handle) {
    registerRsp(msg.seq(), handle);
}
