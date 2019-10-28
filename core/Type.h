#pragma once

#include "google/protobuf/wrappers.pb.h"

namespace protolib {
namespace Type {

using CmdType = int;
using SeqType = uint32_t;
using Message = google::protobuf::Message;

// 默认空消息 方便接口设计
const google::protobuf::StringValue DataNone; // NOLINT(cert-err58-cpp)

#define ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T) \
        typename std::enable_if<std::is_base_of<Message, T>::value && !std::is_base_of<Msg, T>::value, int>::type = 0

#define ENSURE_TYPE_IS_MESSAGE(T) \
        typename std::enable_if<std::is_base_of<Message, T>::value, int>::type = 0

template <typename T, ENSURE_TYPE_IS_MESSAGE(T)>
struct RspType {
    T message;
    bool success;

    RspType(T m, bool s) : message(std::move(m)), success(s) {}

    RspType(bool s) : message(T()), success(s) {} // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

    RspType(T m) : message(std::move(m)), success(true) {} // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
};

template <typename T, ENSURE_TYPE_IS_MESSAGE(T)>
inline
RspType<T>
R(T msg, bool success) {
    return RspType<T>(std::move(msg), success);
}

}
}
