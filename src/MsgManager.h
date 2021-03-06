#pragma once

#include "Connection.h"
#include "MsgDispatcher.h"
#include "coder/ProtoCoder.h"
#include "MsgUtils.h"
#include "noncopyable.h"

namespace protolib {

/**
 * 消息管理
 * 1. 封装操作细节以方便发送接收消息
 * 2. 持有一个连接 收发均基于此连接
 * 为了方便使用，消息注册和发送重载了多种形式。
 */
class MsgManager : noncopyable {
    using CmdHandle = MsgDispatcher::CmdHandle;
    using RspCallback = MsgDispatcher::RspHandle;
    using TimeoutCb = MsgDispatcher::TimeoutCb;

    using PingCallback = std::function<void(const std::string&)>;

public:
    explicit MsgManager(std::shared_ptr<Connection> conn, std::shared_ptr<coder::Coder> coder = std::make_shared<coder::ProtoCoder>());

public:
    std::shared_ptr<Connection> getConn() const;
    void setTimerFunc(const MsgDispatcher::SetTimeout&);

public:
    /**
     * 注册命令 接收消息 返回消息
     * @tparam T 接收消息的类型 这将决定解析行为 与发送时"发送参数类型"一致
     * @tparam U 返回消息结果的类型 与发送时"回调参数类型"一致
     * @param cmd
     * @param handle 接收T类型消息 返回RspType<T>类型消息作为回复 可使用R(Message, bool)构造 也可直接返回Message或bool
     */
    template <typename T, typename U, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T), ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(U)>
    void subscribe(CmdType cmd, const std::function<RspType<U>(T&&)>& handle) {
        dispatcher_.subscribeCmd(cmd, [handle](const Msg& msg) {
            RspType<U> rsp = handle(utils::UnpackMsgData<T>(msg));
            return utils::CreateRspMsg(
                    msg.seq(),
                    rsp.message,
                    rsp.success
            );
        });
    }

    /**
     * 注册命令 接收消息 返回bool
     * @tparam T 接收消息的类型
     * @param cmd
     * @param handle 接收数据 返回操作状态
     */
    template <typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
    void subscribe(CmdType cmd, const std::function<bool(T&&)>& handle) {
        dispatcher_.subscribeCmd(cmd, [handle](const Msg& msg) {
            bool success = handle(utils::UnpackMsgData<T>(msg));
            return utils::CreateRspMsg(
                    msg.seq(),
                    DataNone,
                    success
            );
        });
    }

    /**
     * 注册命令 不接收消息 返回bool
     * @param cmd
     * @param handle 不接收参数 返回操作状态
     */
    void subscribe(CmdType cmd, const std::function<bool()>& handle) {
        dispatcher_.subscribeCmd(cmd, [handle](const Msg& msg) {
            bool success = handle();
            return utils::CreateRspMsg(
                    msg.seq(),
                    DataNone,
                    success
            );
        });
    }

    /**
     * 注册命令 不接收消息 返回消息
     * @tparam T 返回给对方的数据类型
     * @param cmd
     * @param handle 不接收参数 返回R(msg, true)形式
     */
    template <typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
    void subscribe(CmdType cmd, const std::function<RspType<T>()>& handle) {
        dispatcher_.subscribeCmd(cmd, [handle](const Msg& msg) {
            RspType<T> rsp = handle();
            return utils::CreateRspMsg(
                    msg.seq(),
                    rsp.message,
                    rsp.success
            );
        });
    }

    /**
     * 取消注册的命令
     * @param cmd
     */
    inline void unsubscribe(CmdType cmd) {
        dispatcher_.unsubscribeCmd(cmd);
    }

    /**
     * 发送命令和消息 获取回复消息
     * @tparam T 消息回复数据载体的类型
     * @param cmd 消息类型
     * @param message 消息数据
     * @param cb 消息回调 参数类型RspType<T>
     * @param timeoutCb 超时回调
     * @param timeoutMs 超时时间
     */
    template <typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
    inline void send(CmdType cmd, const Message& message, const std::function<void(RspType<T>&&)>& cb, const TimeoutCb& timeoutCb = nullptr, uint32_t timeoutMs = 3000) {
        sendMessage(cmd, message, [cb](const Msg& msg) {
            cb(RspType<T>(msg.success() ? utils::UnpackMsgData<T>(msg) : T(), msg.success()));
        }, timeoutCb, timeoutMs);
    }

    /**
     * 发送命令 获取回复消息
     * @tparam T 接收消息的类型
     * @param cmd
     * @param cb 消息回调 参数类型RspType<T>
     * @param timeoutCb 超时回调
     * @param timeoutMs 超时时间
     */
    template <typename T, ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T)>
    inline void send(CmdType cmd, const std::function<void(RspType<T>&&)>& cb, const TimeoutCb& timeoutCb = nullptr, uint32_t timeoutMs = 3000) {
        sendMessage(cmd, DataNone, [cb](const Msg& msg) {
            cb(RspType<T>(msg.success() ? utils::UnpackMsgData<T>(msg) : T(), msg.success()));
        }, timeoutCb, timeoutMs);
    }

    /**
     * 发送命令和消息 获取是否成功
     * @param cmd
     * @param message
     * @param cb 消息回调 对方响应是否成功
     * @param timeoutCb 超时回调
     * @param timeoutMs 超时时间
     */
    inline void send(CmdType cmd, const Message& message, const std::function<void(bool)>& cb = nullptr, const TimeoutCb& timeoutCb = nullptr, uint32_t timeoutMs = 3000) {
        sendMessage(cmd, message, [cb](const Msg& msg) {
            if (cb != nullptr) {
                cb(msg.success());
            }
        }, timeoutCb, timeoutMs);
    }

    /**
     * 发送命令 获取是否成功
     * @param cmd
     * @param cb
     * @param timeoutCb 超时回调
     * @param timeoutMs 超时时间
     */
    inline void send(CmdType cmd, const std::function<void(bool)>& cb = nullptr, const TimeoutCb& timeoutCb = nullptr, uint32_t timeoutMs = 3000) {
        send(cmd, DataNone, cb, timeoutCb, timeoutMs);
    }

    /**
     * 可作为连通性的测试 会原样返回payload
     * @param payload 负载数据默认为空
     * @param cb 参数类型std::string
     * @param timeoutCb 超时回调
     * @param timeoutMs 超时时间
     */
    void sendPing(const std::string& payload = "", const PingCallback& cb = nullptr, const TimeoutCb& timeoutCb = nullptr, uint32_t timeoutMs = 3000);

private:
    /**
     * 发送消息并设定回调
     * @param cmd
     * @param message
     * @param cb
     * @param timeoutCb 超时回调
     * @param timeoutMs 超时时间
     */
    void sendMessage(CmdType cmd, const Message& message = DataNone, const RspCallback& cb = nullptr, const TimeoutCb& timeoutCb = nullptr, uint32_t timeoutMs = 3000);

    /**
     * 创建消息并设置回调 返回Payload用于传输
     * @param cmd
     * @param message
     * @param cb
     * @param timeoutCb 超时回调
     * @param timeoutMs 超时时间
     * @return
     */
    std::string CreateMessagePayload(CmdType cmd, const Message& message = DataNone, const RspCallback& cb = nullptr, const TimeoutCb& timeoutCb = nullptr, uint32_t timeoutMs = 3000);

private:
    std::shared_ptr<Connection> conn_;
    MsgDispatcher dispatcher_;
};

}
