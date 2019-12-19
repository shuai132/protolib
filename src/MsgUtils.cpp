#include "MsgUtils.h"

namespace protolib {
namespace utils {

// 消息的序列号 作为消息ID
static std::atomic<SeqType> MsgSeq(0);

Msg CreateCmdMsg(CmdType cmd, const Message& data) {
    Msg msg;
    msg.set_type(Msg::COMMAND);
    msg.set_cmd(cmd);
    msg.set_seq(MsgSeq++);
    if (&data != &DataNone) {
        msg.mutable_data()->PackFrom(data);
    }
    return msg;
}
}
}
