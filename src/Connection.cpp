#include "Connection.h"

#include <cassert>

namespace protolib {

void Connection::sendPayload(const std::string& payload) {
    if (sendPayloadFunc_) {
        sendPayloadFunc_(payload);
    }
}

void Connection::onPayload(const std::string& payload) {
    assert(onPayloadHandle_);
    onPayloadHandle_(payload);
}

void Connection::setOnPayloadHandle(const Connection::PayloadHandle& handle) {
    onPayloadHandle_ = handle;
}

void Connection::setSendPayloadFunc(const Connection::PayloadHandle& handle) {
    sendPayloadFunc_ = handle;
}

}
