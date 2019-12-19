#pragma once

#include "proto/cpp/Msg.pb.h"
#include "Type.h"
#include "Exception.h"
#include "noncopyable.h"

namespace protolib {
namespace utils {

using namespace google::protobuf;
using namespace proto;

/**
 * 创建Cmd消息
 * @param cmd
 * @param data
 * @return
 */
Msg CreateCmdMsg(CmdType cmd, const Message& data = DataNone);

/**
 * 创建Rsp消息
 * @param seq 对应Cmd的seq
 * @param data 将保存在Msg.data
 * @param success 成功/失败
 * @return
 */
template<typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
inline Msg CreateRspMsg(SeqType seq, const T& data = DataNone, bool success = true) {
    Msg msg;
    msg.set_type(Msg::RESPONSE);
    msg.set_success(success);
    msg.set_seq(seq);
    if ((intptr_t*) &data != (intptr_t*) &DataNone) {
        msg.mutable_data()->PackFrom(data);
    }
    return msg;
}

/**
 * 将Msg.data解析为指定类型的数据
 * T为Message类型 但认为不是Msg类型 防止误用
 */
template<typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
inline T UnpackMsgData(const Msg& msg) {
    T data;
    bool ret = msg.data().UnpackTo(&data);
    throw_if(not ret);
    return data;
}

}
}
