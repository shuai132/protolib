#pragma once

#include <stdexcept>

namespace protolib {

class Exception : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

template <typename T>
inline void throw_if(T b, const std::string& msg = "protolib exception") {
    if (b) {
        throw Exception(msg);
    }
}

}
