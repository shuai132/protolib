#include "MsgDispatcher.h"
#include "MsgUtils.h"
#include "log.h"

namespace protolib {

MsgDispatcher::MsgDispatcher(std::shared_ptr<Connection> conn, std::shared_ptr<coder::Coder> coder)
    : conn_(std::move(conn)), coder_(std::move(coder)) {
    conn_->setOnPayloadHandle([this](const std::string& payload){
        bool success;
        auto msg = coder_->unserialize(payload, success);
        if (success) {
            this->dispatch(msg);
        } else {
            LOGE("payload can not be parsed");
        }
    });

    // 每一个连接要册一个PING消息，以便有PING到来时，给发送者回复PONG，PING/PONG可携带payload，会原样返回。
    subscribeCmd(Msg::PING, [](const Msg& param) {
        auto msg = static_cast<Msg>(param);
        msg.set_cmd(Msg::PONG);
        return utils::CreateRspMsg(msg.seq(), utils::UnpackMsgData<StringValue>(std::forward<Msg>(msg)));
    });
}

void MsgDispatcher::dispatch(const Msg& msg) {
    switch (msg.type()) {
        case Msg::COMMAND:
        {
            // COMMAND
            auto cmd = msg.cmd();
            LOGD("dispatch cmd:%d, seq:%d, conn:%p", cmd, msg.seq(), conn_.get());

            auto iter = cmdHandleMap_.find(cmd);
            if (iter == cmdHandleMap_.cend()) {
                LOGD("not register cmd for: %d", cmd);
                return;
            }
            const auto& fn = (*iter).second;
            try {
                auto resp = fn(msg);
                conn_->sendPayload(coder_->serialize(resp));
            } catch (...) {
                LOGE("type error！please check your cmd and data type! cmd:%d", cmd);
            }

        } break;

        case Msg::RESPONSE:
        {
            LOGD("dispatch rsp: seq=%d, success=%d, conn:%p", msg.seq(), msg.success(), conn_.get());
            auto iter = rspHandleMap_.find(msg.seq());
            if (iter == rspHandleMap_.cend()) {
                LOGD("not register callback for response");
                break;
            }
            const auto& cb = (*iter).second;
            throw_if(not cb, "rsp handle can not be null");
            cb(msg);
            rspHandleMap_.erase(iter);
            LOGD("rspHandleMap_.size=%zu", rspHandleMap_.size());
        } break;

        default:
            LOGE("unknown message type, conn:%p", conn_.get());
    }
}

void MsgDispatcher::subscribeCmd(CmdType cmd, const CmdHandle& handle) {
    LOGD("subscribeCmd conn:%p, cmd:%d, handle:%p", conn_.get(), cmd, &handle);
    cmdHandleMap_[cmd] = handle;
}

void MsgDispatcher::unsubscribeCmd(CmdType cmd) {
    auto iter = cmdHandleMap_.find(cmd);
    if (iter != cmdHandleMap_.cend()) {
        LOGD("erase cmd: %d", cmd);
        cmdHandleMap_.erase(iter);
    } else {
        LOGD("not register cmd for: %d", cmd);
    }
}

void MsgDispatcher::subscribeRsp(SeqType seq, const MsgDispatcher::RspHandle& handle, const TimeoutCb& timeoutCb, uint32_t timeoutMs) {
    LOGD("subscribeRsp seq:%d, handle:%p", seq, &handle);
    if (handle == nullptr) return;
    rspHandleMap_[seq] = handle;

    throw_if(setTimeout_ == nullptr, "no timeout will cause memory leak");

    setTimeout_(timeoutMs, [=] {
        auto iter = rspHandleMap_.find(seq);
        if (iter != rspHandleMap_.cend()) {
            if (timeoutCb) {
                timeoutCb();
            }
            rspHandleMap_.erase(seq);
            LOGD("Timeout seq=%d, rspHandleMap_.size=%zu", seq, rspHandleMap_.size());
        }
    });
}

std::shared_ptr<Connection> MsgDispatcher::getConn() const {
    return conn_;
}

void MsgDispatcher::setTimerFunc(const MsgDispatcher::SetTimeout& timerFunc) {
    setTimeout_ = timerFunc;
}

}
