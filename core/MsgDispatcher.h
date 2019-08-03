#pragma once

#include "proto/cpp/Msg.pb.h"
#include "Connection.h"
#include "Type.h"

using namespace proto;
using namespace google::protobuf;

/**
 * 消息分发器
 * 注册消息到指定命令
 */
class MsgDispatcher {
public:
    using CmdHandle = std::function<Msg(const Msg&)>;
    using CmdHandleMap = std::map<CmdType, CmdHandle>;

public:
    static MsgDispatcher* getInstance();

    void dispatcher(Connection* conn, const Msg& command);

    void regist(CmdType cmd, const CmdHandle& handle);

private:
    MsgDispatcher() = default;
    ~MsgDispatcher() = default;
    MsgDispatcher(const MsgDispatcher&) = delete;
    MsgDispatcher& operator=(const MsgDispatcher&) = delete;

private:
    CmdHandleMap _cmdHandleMap;
};
