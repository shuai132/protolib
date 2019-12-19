#include "ProtoCoder.h"

namespace protolib {
namespace coder {

std::string coder::ProtoCoder::serialize(const Msg& msg) {
    std::string payload;
    bool ret = msg.SerializeToString(&payload);
    throw_if(not ret);
    return payload;
}

Msg coder::ProtoCoder::unserialize(const std::string& payload, bool& success) {
    Msg msg;
    success = msg.ParseFromString(payload);
    return msg;
}

}
}
