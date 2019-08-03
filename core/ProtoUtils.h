#pragma once

#include "proto/cpp/Msg.pb.h"
#include "MsgDispatcher.h"
#include "Type.h"

using namespace google::protobuf;
using namespace proto;
using RspCallback = MsgDispatcher::RspHandle;

namespace ProtoUtils {

static std::atomic<SeqType> MsgSeq(0);
const Msg MsgNone;

inline Msg CreateCmdMsg(CmdType cmd, const Message& data = MsgNone) {
    Msg msg;
    msg.set_type(Msg::COMMAND);
    msg.set_cmd(cmd);
    msg.set_seq(MsgSeq++);
    if (&data != &MsgNone) {
        msg.mutable_data()->PackFrom(data);
    }
    return msg;
}

inline Msg CreateRspMsg(SeqType seq, const Message& data = MsgNone, bool success = true) {
    Msg msg;
    msg.set_type(Msg::RESPONSE);
    msg.set_success(success);
    msg.set_seq(seq);
    if (&data != &MsgNone) {
        msg.mutable_data()->PackFrom(data);
    }
    return msg;
}

inline std::string CreatePayload(const Msg& msg) {
    std::string payload;
    bool ret = msg.SerializeToString(&payload);
    assert(ret);
    return payload;
}

template <CmdType cmd>
inline std::string CreateCmdPayload(const Message &message = MsgNone, const RspCallback& cb = nullptr) {
    std::string payload;
    auto msg = CreateCmdMsg(cmd, message);
    auto ret = msg.SerializeToString(&payload);
    assert(ret);
    MsgDispatcher::getInstance()->registerRsp(msg.seq(), cb);
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

/**
 * 将Response解析为指定类型的数据
 */
template <typename T>
inline T UnpackRspData(const Msg& msg) {
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
