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
    using CmdHandle = std::function<Msg(Msg&&)>;
    using CmdHandleMap = std::map<CmdType, CmdHandle>;
    using RspHandle = std::function<void(Msg&&)>;
    using RspHandleMap = std::map<SeqType, RspHandle>;

public:
    static MsgDispatcher& getInstance();

    void dispatch(Connection* conn, Msg&& msg);

    void subscribeCmd(CmdType cmd, const CmdHandle& handle);

    void unsubscribeCmd(CmdType cmd);

    void subscribeRsp(SeqType seq, const RspHandle& handle);

    void subscribeRsp(const Msg& msg, const RspHandle& handle);

private:
    MsgDispatcher() = default;
    ~MsgDispatcher() = default;
public:
    MsgDispatcher(const MsgDispatcher&) = delete;
    MsgDispatcher& operator=(const MsgDispatcher&) = delete;

private:
    CmdHandleMap cmdHandleMap_;
    RspHandleMap rspHandleMap_;
};

}
