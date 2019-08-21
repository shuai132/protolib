#pragma once

#include "proto/cpp/Msg.pb.h"
#include "Type.h"
#include "Exception.h"

namespace protolib {
namespace ProtoUtils {

using namespace google::protobuf;
using namespace proto;
using namespace Type;

// 消息的序列号 作为消息ID
static std::atomic<SeqType> MsgSeq(0);

/**
 * 创建Cmd消息
 * @param cmd
 * @param data
 * @return
 */
inline Msg CreateCmdMsg(CmdType cmd, const Message& data = DataNone) {
    Msg msg;
    msg.set_type(Msg::COMMAND);
    msg.set_cmd(cmd);
    msg.set_seq(MsgSeq++);
    if (&data != &DataNone) {
        msg.mutable_data()->PackFrom(data);
    }
    return msg;
}

/**
 * 创建Rsp消息
 * @param seq 对应Cmd的seq
 * @param data 将保存在Msg.data
 * @param success 成功/失败
 * @return
 */
template <typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
inline Msg CreateRspMsg(SeqType seq, const T& data = DataNone, bool success = true) {
    Msg msg;
    msg.set_type(Msg::RESPONSE);
    msg.set_success(success);
    msg.set_seq(seq);
    if ((intptr_t*)&data != (intptr_t*)&DataNone) {
        msg.mutable_data()->PackFrom(data);
    }
    return msg;
}

/**
 * 用Msg创建payload
 * @param msg
 * @return
 */
inline std::string CreatePayload(const Msg& msg) {
    std::string payload;
    bool ret = msg.SerializeToString(&payload);
    throw_if(not ret);
    return payload;
}

/**
 * 将Msg.data解析为指定类型的数据
 * T为Message类型 但认为不是Msg类型 防止误用
 */
template <typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
inline T UnpackMsgData(const Msg& msg) {
    T data;
    bool ret = msg.data().UnpackTo(&data);
    throw_if(not ret);
    return data;
}

/**
 * 将payload转换为Msg
 */
inline Msg ParsePayload(const string& payload, bool& success) {
    Msg msg;
    success = msg.ParseFromString(payload);
    return msg;
}

}
}
