#pragma once

#include "proto/cpp/Msg.pb.h"

using namespace google::protobuf;
using namespace proto;

namespace ProtoUtils {

static std::atomic<uint32_t> MsgSeq(0);
const Msg MsgNone;

template <Msg::Type type>
inline Msg CreateMsg(const Message& data = MsgNone, Msg::Cmd cmd = Msg::NONE, bool success = true) {
    Msg msg;
    msg.set_seq(MsgSeq++);
    msg.set_type(type);
    if (type == Msg::COMMAND) {
        msg.set_cmd(cmd);
    } else {
        msg.set_success(success);
    }
    if (&data != &MsgNone) {
        msg.mutable_data()->PackFrom(data);
    }
    return msg;
}

inline Msg CreateCmdMsg(Msg::Cmd cmd, const Message &data = MsgNone) {
    return CreateMsg<Msg::COMMAND>(data, cmd);
}

template <bool success = true>
inline Msg CreateRspMsg(const Message& data = MsgNone) {
    return CreateMsg<Msg::RESPONSE>(data, Msg::NONE, success);
}

inline std::string CreatePayload(const Msg& msg) {
    std::string payload;
    bool ret = msg.SerializeToString(&payload);
    assert(ret);
    return payload;
}

template <Msg::Cmd cmd>
inline std::string CreateCmdPayload(const Message &message = MsgNone) {
    std::string payload;
    bool ret = CreateMsg<Msg::COMMAND>(message, cmd).SerializeToString(&payload);
    assert(ret);
    return payload;
}

/**
 * 将Msg.data解析为指定类型的数据
 */
template <typename T>
inline T UnpackMsgData(const Msg& msg) {
    T data;
    bool ret = msg.data().UnpackTo(&data);
    assert(ret);
    return data;
}

inline Msg ParsePayload(const string& payload) {
    Msg msg;
    auto ret = msg.ParseFromString(payload);
    assert(ret);
    return msg;
}

}
