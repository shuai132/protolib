#pragma once

#include "Coder.h"

namespace protolib {
namespace coder {

class ProtoCoder : public Coder {
public:
    std::string serialize(const Msg& msg) override;

    Msg unserialize(const std::string& payload, bool& success) override;
};

}
}
