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

            auto iter = _cmdHandleMap.find(cmd);
            if (iter == _cmdHandleMap.cend()) {
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
            // todo: 实现消息回复回调
        } break;

        default:
            assert(false);
    }
}

void MsgDispatcher::regist(CmdType cmd, const CmdHandle& handle) {
    _cmdHandleMap[cmd] = handle;
}
