#pragma once

#include "proto/cpp/Msg.pb.h"
#include "Connection.h"
#include "Type.h"

namespace protolib {

using namespace proto;
using namespace google::protobuf;

/**
 * 消息分发器
 * 注册消息到指定命令
 */
class MsgDispatcher {
    using SeqType = Type::SeqType;
    using CmdType = Type::CmdType;

public:
    using CmdHandle = std::function<Msg(const Msg&)>;
    using RspHandle = std::function<void(const Msg&)>;

private:
    MsgDispatcher() = default;
    ~MsgDispatcher() = default;
public:
    MsgDispatcher(const MsgDispatcher&) = delete;
    MsgDispatcher& operator=(const MsgDispatcher&) = delete;

public:
    static MsgDispatcher& getInstance();

    void dispatch(Connection* conn, const Msg& msg);

    void subscribeCmd(CmdType cmd, const CmdHandle& handle);

    void unsubscribeCmd(CmdType cmd);

    void subscribeRsp(SeqType seq, const RspHandle& handle);

    void subscribeRsp(const Msg& msg, const RspHandle& handle);

private:
    std::map<CmdType, CmdHandle> cmdHandleMap_;
    std::map<SeqType, RspHandle> rspHandleMap_;
};

}
