#include "MsgManager.h"

namespace protolib {

MsgManager::MsgManager(const std::shared_ptr<Connection>& conn)
        : conn_(conn) {
    conn->setPayloadHandle([conn](const std::string& payload){
        MsgDispatcher::getInstance().dispatch(conn.get(), ProtoUtils::ParsePayload(payload));
    });
}

}
