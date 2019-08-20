#pragma once

#include "proto/cpp/Msg.pb.h"
#include "Connection.h"
#include "Type.h"
#include "ProtoUtils.h"

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

public:
    explicit MsgDispatcher(std::shared_ptr<Connection> conn);
    ~MsgDispatcher() = default;
public:
    MsgDispatcher(const MsgDispatcher&) = delete;
    MsgDispatcher& operator=(const MsgDispatcher&) = delete;

public:
    void dispatch(const Msg& msg);

    void subscribeCmd(CmdType cmd, const CmdHandle& handle);

    void unsubscribeCmd(CmdType cmd);

    void subscribeRsp(SeqType seq, const RspHandle& handle);

    void subscribeRsp(const Msg& msg, const RspHandle& handle);

    std::shared_ptr<Connection> getConn() const;

private:
    std::shared_ptr<Connection> conn_;
    std::map<CmdType, CmdHandle> cmdHandleMap_;
    std::map<SeqType, RspHandle> rspHandleMap_;
};

}
