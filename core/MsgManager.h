#pragma once

#include "core/Connection.h"
#include "core/MsgDispatcher.h"
#include "core/ProtoUtils.h"

/**
 * 消息管理
 * 1. 封装操作细节以方便发送接收消息
 * 2. 持有一个连接 收发均基于此连接
 */
class MsgManager {
public:
    using CmdHandle = MsgDispatcher::CmdHandle;
    using PingCallback = std::function<void(const std::string&)>;

public:
    explicit MsgManager(std::shared_ptr<Connection> conn);

public:
    /**
     * 注册命令并设置接收回调
     * @tparam T 接收消息的类型 这将决定解析行为 与发送时参数一致
     * @tparam U 返回消息结果的类型 与发送时回调参数一致
     * @param cmd
     * @param handle
     */
    template <typename T, typename U, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T), ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(U)>
    void registerCmd(CmdType cmd, const std::function<std::tuple<U, bool>(T&&)>& handle = nullptr) {
        dispatcher_->registerCmd(cmd, [&](const Msg& msg) {
            const auto& rsp = handle(std::forward<T>(ProtoUtils::UnpackMsgData<T>(msg)));
            return ProtoUtils::CreateRspMsg(
                    msg.seq(),
                    std::get<0>(rsp),
                    std::get<1>(rsp)
                    );
        });
    }
    template <typename T, typename U, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T), ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(U)>
    void registerCmd(CmdType cmd, const std::function<U(T&&)>& handle = nullptr) {
        dispatcher_->registerCmd(cmd, [&](const Msg& msg) {
            return ProtoUtils::CreateRspMsg(
                    msg.seq(),
                    handle(std::forward<T>(ProtoUtils::UnpackMsgData<T>(msg)))
                    );
        });
    }

    /**
     * 发送消息并设定回调
     */
    void sendMessage(CmdType cmd, const Message& message = ProtoUtils::DataNone, const RspCallback& cb = nullptr) {
        // 指定消息类型创建payload
        auto payload = ProtoUtils::CreateCmdPayload(cmd, message, cb);
        conn_->sendPayload(payload);
    }

    /**
     * 发送消息
     * @tparam T 消息回复数据载体的类型
     * @param cmd 消息类型
     * @param message 消息数据
     * @param cb 消息回复的回调
     */
    template <typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
    void sendMessage(CmdType cmd, const Message& message = ProtoUtils::DataNone,
            const std::function<void(T&&)>& cb = nullptr) {
        sendMessage(cmd, message, [&](const Msg& msg) {
            cb(std::forward<T>(ProtoUtils::UnpackMsgData<T>(msg)));
        });
    }

    /**
     * 发送string类型数据 将使用StringValue作为载体
     */
    void sendMessage(CmdType cmd, const std::string& message, const RspCallback& cb = nullptr) {
        StringValue stringValue;
        stringValue.set_value(message);
        sendMessage(cmd, stringValue, cb);
    }

    /**
     * 可作为连通性的测试 会原样返回payload 默认为空
     * @param payload
     * @param cb
     */
    void sendPing(const std::string& payload = "", const PingCallback& cb = nullptr) {
        sendMessage(Msg::PING, payload, [&](const Msg& msg) {
            cb(ProtoUtils::UnpackMsgData<StringValue>(msg).value());
        });
    }

private:
    MsgDispatcher* dispatcher_ = MsgDispatcher::getInstance();
    std::shared_ptr<Connection> conn_;
};
