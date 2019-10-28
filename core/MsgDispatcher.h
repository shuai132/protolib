#pragma once

#include "proto/cpp/Msg.pb.h"
#include "Connection.h"
#include "Type.h"
#include "ProtoUtils.h"
#include "noncopyable.h"

namespace protolib {

using namespace proto;
using namespace google::protobuf;

/**
 * 消息分发器
 * 注册消息到指定命令
 */
class MsgDispatcher : private noncopyable {
    using SeqType = Type::SeqType;
    using CmdType = Type::CmdType;

public:
    using CmdHandle = std::function<Msg(const Msg&)>;
    using RspHandle = std::function<void(const Msg&)>;

    using TimeoutCb = std::function<void()>;
    using SetTimeout = std::function<void(uint32_t ms, const TimeoutCb&)>;

public:
    explicit MsgDispatcher(std::shared_ptr<Connection> conn);
    ~MsgDispatcher() = default;

public:
    void dispatch(const Msg& msg);

    void subscribeCmd(CmdType cmd, const CmdHandle& handle);

    void unsubscribeCmd(CmdType cmd);

    void subscribeRsp(SeqType seq, const RspHandle& handle, const TimeoutCb& timeoutCb, uint32_t timeoutMs);

    std::shared_ptr<Connection> getConn() const;

    void setTimerFunc(const SetTimeout& timerFunc);

private:
    std::shared_ptr<Connection> conn_;
    std::map<CmdType, CmdHandle> cmdHandleMap_;
    std::map<SeqType, RspHandle> rspHandleMap_;
    SetTimeout setTimeout_;
};

}
