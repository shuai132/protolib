#pragma once

#include "proto/cpp/Msg.pb.h"
#include "Type.h"
#include "Exception.h"
#include "noncopyable.h"

namespace protolib {
namespace coder {

using namespace proto;

class Coder : noncopyable {
public:
    virtual ~Coder() = default;
public:
    /**
     * 用Msg创建payload
     * @param msg
     * @return
     */
    virtual std::string serialize(const Msg& msg) = 0;

    /**
     * 将payload转换为Msg
     */
    virtual Msg unserialize(const std::string& payload, bool& success) = 0;
};

}
}
