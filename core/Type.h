#pragma once

#include "google/protobuf/wrappers.pb.h"

using CmdType = int;
using SeqType = uint32_t;

#define ENSURE_TYPE_IS_MESSAGE_AND_NOT_MSG(T) \
        typename std::enable_if<std::is_base_of<Message, T>::value && !std::is_base_of<Msg, T>::value, int>::type = 0

#define ENSURE_TYPE_IS_MESSAGE(T) \
        typename std::enable_if<std::is_base_of<Message, T>::value, int>::type = 0
