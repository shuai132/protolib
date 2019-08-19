#pragma once

#include <stdexcept>

namespace protolib {

const std::string DEFAULT_ERROR_MSG = "protolib error"; // NOLINT(cert-err58-cpp)

class Exception : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

template <typename T>
inline void throw_if(T b, const std::string& msg = DEFAULT_ERROR_MSG) {
    if (b) {
        throw Exception(msg);
    }
}

}
