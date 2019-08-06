#include "MsgManager.h"

MsgManager::MsgManager(std::shared_ptr<Connection> conn)
        : conn_(conn) {
    conn->setPayloadHandle([&](const std::string& payload){
        MsgDispatcher::getInstance()->dispatch(conn.get(), ProtoUtils::ParsePayload(payload));
    });
}
