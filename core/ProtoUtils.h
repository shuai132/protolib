#pragma once

#include "google/protobuf/wrappers.pb.h"
#include "proto/cpp/Msg.pb.h"
#include "MsgDispatcher.h"
#include "Type.h"

using namespace google::protobuf;
using namespace proto;
using RspCallback = MsgDispatcher::RspHandle;

namespace ProtoUtils {

// 消息的序列号 作为消息ID
static std::atomic<SeqType> MsgSeq(0);

// 默认空消息 方便接口设计
const StringValue DataNone; // NOLINT(cert-err58-cpp)

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
 * @param data Msg.data
 * @param success 成功/失败
 * @return
 */
template <typename T = Message>
inline Msg CreateRspMsg(SeqType seq, const T& data = DataNone, bool success = true) {
    //  data为Message类型 而不是Msg类型 防止误用
    static_assert(std::is_base_of<Message, T>(), "data should be a Message!");
    static_assert(!std::is_base_of<Msg, T>(), "data should not be a Msg!");

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
    assert(ret);
    return payload;
}

/**
 * 创建Cmd消息并转换成Payload方便传输
 * @tparam cmd
 * @param message
 * @param cb
 * @return
 */
template <CmdType cmd>
inline std::string CreateCmdPayload(const Message &data = DataNone, const RspCallback& cb = nullptr) {
    std::string payload;
    auto msg = CreateCmdMsg(cmd, data);
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
 * 将payload转换为Msg
 */
inline Msg ParsePayload(const string& payload) {
    Msg msg;
    auto ret = msg.ParseFromString(payload);
    assert(ret);
    return msg;
}

}
