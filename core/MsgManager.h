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
    using SeqType = Type::SeqType;
    using CmdType = Type::CmdType;

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
     * @param handle handle需接收数据和返回数据时使用 如不需要接收或不需要返回等情况 使用其他的重载函数
     *               接收参数使用(const YourType& msg)或(YourType msg)均可 基于内部移动语义后者不会发生拷贝而影响效率
     *               返回值类型Type::RspType<T> 可使用Type::R(Message, bool)构造
     */
    template <typename T, typename U, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T), ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(U)>
    void registerCmd(CmdType cmd, const std::function<Type::RspType<U>(T&&)>& handle) {
        dispatcher_->registerCmd(cmd, [&](const Msg& msg) {
            Type::RspType<U> rsp = handle(std::forward<T>(ProtoUtils::UnpackMsgData<T>(msg)));
            return ProtoUtils::CreateRspMsg(
                    msg.seq(),
                    rsp.message,
                    rsp.success
            );
        });
    }
    // 同上 handle不需接收数据 只返回操作状态
    template <typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
    void registerCmd(CmdType cmd, const std::function<Type::RspType<StringValue>(T&&)>& handle) {
        dispatcher_->registerCmd(cmd, [&](const Msg& msg) {
            Type::RspType<StringValue> rsp = handle(std::forward<T>(ProtoUtils::UnpackMsgData<T>(msg)));
            return ProtoUtils::CreateRspMsg(
                    msg.seq(),
                    ProtoUtils::DataNone,
                    rsp.success
                    );
        });
    }
    // 同上 handle不需接收数据 只返回操作状态
    void registerCmd(CmdType cmd, const std::function<bool()>& handle) {
        dispatcher_->registerCmd(cmd, [&](const Msg& msg) {
            bool success = handle();
            return ProtoUtils::CreateRspMsg(
                    msg.seq(),
                    ProtoUtils::DataNone,
                    success
            );
        });
    }
    // 同上 handle不需接收数据 需返回数据时使用
    template <typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
    void registerCmd(CmdType cmd, const std::function<Type::RspType<T>()>& handle) {
        dispatcher_->registerCmd(cmd, [&](const Msg& msg) {
            Type::RspType<T> rsp = handle();
            return ProtoUtils::CreateRspMsg(
                    msg.seq(),
                    rsp.message,
                    rsp.success
            );
        });
    }

    /**
     * 发送消息
     * @tparam T 消息回复数据载体的类型
     * @param cmd 消息类型
     * @param message 消息数据
     * @param cb 消息回复的回调 参数可为(Message msg, bool success)或(Message msg)或(bool success)
     */
    template <typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
    inline void sendPost(CmdType cmd, const Message& message, const std::function<void(Type::RspType<T>&&)>& cb = nullptr) {
        if (cb == nullptr) {
            sendMessage(cmd, message);
            return;
        }
        sendMessage(cmd, message, [&](const Msg &msg) {
            cb(Type::RspType<T>(ProtoUtils::UnpackMsgData<T>(msg), msg.success()));
        });
    }
    template <typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
    inline void sendGet(CmdType cmd, const std::function<void(Type::RspType<T>&&)>& cb) {
        sendMessage(cmd, ProtoUtils::DataNone, [&](const Msg &msg) {
            cb(Type::RspType<T>(ProtoUtils::UnpackMsgData<T>(msg), msg.success()));
        });
    }
    inline void sendSet(CmdType cmd, const Message& message, const std::function<void(bool)>& cb = nullptr) {
        sendMessage(cmd, message, [&](const Msg &msg) {
            if (cb != nullptr) {
                cb(msg.success());
            }
        });
    }
    inline void sendCtrl(CmdType cmd, const std::function<void(bool)>& cb = nullptr) {
        sendSet(cmd, ProtoUtils::DataNone, cb);
    }

    /**
     * 可作为连通性的测试 会原样返回payload 默认为空
     * @param payload
     * @param cb
     */
    inline void sendPing(const std::string& payload = "", const PingCallback& cb = nullptr) {
        StringValue stringValue;
        stringValue.set_value(payload);
        sendMessage(Msg::PING, stringValue, [&](const Msg& msg) {
            cb(ProtoUtils::UnpackMsgData<StringValue>(msg).value());
        });
    }

private:
    /**
     * 发送消息并设定回调
     */
    inline void sendMessage(CmdType cmd, const Message& message = ProtoUtils::DataNone, const RspCallback& cb = nullptr) {
        // 指定消息类型创建payload
        auto payload = ProtoUtils::CreateCmdPayload(cmd, message, cb);
        conn_->sendPayload(payload);
    }

private:
    MsgDispatcher* dispatcher_ = MsgDispatcher::getInstance();
    std::shared_ptr<Connection> conn_;
};
