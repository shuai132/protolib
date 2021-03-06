// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Msg.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Msg_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Msg_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/any.pb.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Msg_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Msg_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Msg_2eproto;
namespace proto {
class Msg;
class MsgDefaultTypeInternal;
extern MsgDefaultTypeInternal _Msg_default_instance_;
}  // namespace proto
PROTOBUF_NAMESPACE_OPEN
template<> ::proto::Msg* Arena::CreateMaybeMessage<::proto::Msg>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace proto {

enum Msg_Type : int {
  Msg_Type_COMMAND = 0,
  Msg_Type_RESPONSE = 1,
  Msg_Type_Msg_Type_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  Msg_Type_Msg_Type_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool Msg_Type_IsValid(int value);
constexpr Msg_Type Msg_Type_Type_MIN = Msg_Type_COMMAND;
constexpr Msg_Type Msg_Type_Type_MAX = Msg_Type_RESPONSE;
constexpr int Msg_Type_Type_ARRAYSIZE = Msg_Type_Type_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Msg_Type_descriptor();
template<typename T>
inline const std::string& Msg_Type_Name(T enum_t_value) {
  static_assert(::std::is_same<T, Msg_Type>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function Msg_Type_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    Msg_Type_descriptor(), enum_t_value);
}
inline bool Msg_Type_Parse(
    const std::string& name, Msg_Type* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<Msg_Type>(
    Msg_Type_descriptor(), name, value);
}
enum Msg_Cmd : int {
  Msg_Cmd_NONE = 0,
  Msg_Cmd_PING = 1,
  Msg_Cmd_PONG = 2,
  Msg_Cmd_Msg_Cmd_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  Msg_Cmd_Msg_Cmd_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool Msg_Cmd_IsValid(int value);
constexpr Msg_Cmd Msg_Cmd_Cmd_MIN = Msg_Cmd_NONE;
constexpr Msg_Cmd Msg_Cmd_Cmd_MAX = Msg_Cmd_PONG;
constexpr int Msg_Cmd_Cmd_ARRAYSIZE = Msg_Cmd_Cmd_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Msg_Cmd_descriptor();
template<typename T>
inline const std::string& Msg_Cmd_Name(T enum_t_value) {
  static_assert(::std::is_same<T, Msg_Cmd>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function Msg_Cmd_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    Msg_Cmd_descriptor(), enum_t_value);
}
inline bool Msg_Cmd_Parse(
    const std::string& name, Msg_Cmd* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<Msg_Cmd>(
    Msg_Cmd_descriptor(), name, value);
}
// ===================================================================

class Msg :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto.Msg) */ {
 public:
  Msg();
  virtual ~Msg();

  Msg(const Msg& from);
  Msg(Msg&& from) noexcept
    : Msg() {
    *this = ::std::move(from);
  }

  inline Msg& operator=(const Msg& from) {
    CopyFrom(from);
    return *this;
  }
  inline Msg& operator=(Msg&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Msg& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Msg* internal_default_instance() {
    return reinterpret_cast<const Msg*>(
               &_Msg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Msg& a, Msg& b) {
    a.Swap(&b);
  }
  inline void Swap(Msg* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Msg* New() const final {
    return CreateMaybeMessage<Msg>(nullptr);
  }

  Msg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Msg>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Msg& from);
  void MergeFrom(const Msg& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Msg* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "proto.Msg";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_Msg_2eproto);
    return ::descriptor_table_Msg_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  typedef Msg_Type Type;
  static constexpr Type COMMAND =
    Msg_Type_COMMAND;
  static constexpr Type RESPONSE =
    Msg_Type_RESPONSE;
  static inline bool Type_IsValid(int value) {
    return Msg_Type_IsValid(value);
  }
  static constexpr Type Type_MIN =
    Msg_Type_Type_MIN;
  static constexpr Type Type_MAX =
    Msg_Type_Type_MAX;
  static constexpr int Type_ARRAYSIZE =
    Msg_Type_Type_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  Type_descriptor() {
    return Msg_Type_descriptor();
  }
  template<typename T>
  static inline const std::string& Type_Name(T enum_t_value) {
    static_assert(::std::is_same<T, Type>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function Type_Name.");
    return Msg_Type_Name(enum_t_value);
  }
  static inline bool Type_Parse(const std::string& name,
      Type* value) {
    return Msg_Type_Parse(name, value);
  }

  typedef Msg_Cmd Cmd;
  static constexpr Cmd NONE =
    Msg_Cmd_NONE;
  static constexpr Cmd PING =
    Msg_Cmd_PING;
  static constexpr Cmd PONG =
    Msg_Cmd_PONG;
  static inline bool Cmd_IsValid(int value) {
    return Msg_Cmd_IsValid(value);
  }
  static constexpr Cmd Cmd_MIN =
    Msg_Cmd_Cmd_MIN;
  static constexpr Cmd Cmd_MAX =
    Msg_Cmd_Cmd_MAX;
  static constexpr int Cmd_ARRAYSIZE =
    Msg_Cmd_Cmd_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  Cmd_descriptor() {
    return Msg_Cmd_descriptor();
  }
  template<typename T>
  static inline const std::string& Cmd_Name(T enum_t_value) {
    static_assert(::std::is_same<T, Cmd>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function Cmd_Name.");
    return Msg_Cmd_Name(enum_t_value);
  }
  static inline bool Cmd_Parse(const std::string& name,
      Cmd* value) {
    return Msg_Cmd_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kDataFieldNumber = 3,
    kSeqFieldNumber = 1,
    kTypeFieldNumber = 2,
    kCmdFieldNumber = 10,
    kSuccessFieldNumber = 20,
  };
  // .google.protobuf.Any data = 3;
  bool has_data() const;
  void clear_data();
  const PROTOBUF_NAMESPACE_ID::Any& data() const;
  PROTOBUF_NAMESPACE_ID::Any* release_data();
  PROTOBUF_NAMESPACE_ID::Any* mutable_data();
  void set_allocated_data(PROTOBUF_NAMESPACE_ID::Any* data);

  // uint32 seq = 1;
  void clear_seq();
  ::PROTOBUF_NAMESPACE_ID::uint32 seq() const;
  void set_seq(::PROTOBUF_NAMESPACE_ID::uint32 value);

  // .proto.Msg.Type type = 2;
  void clear_type();
  ::proto::Msg_Type type() const;
  void set_type(::proto::Msg_Type value);

  // uint32 cmd = 10;
  void clear_cmd();
  ::PROTOBUF_NAMESPACE_ID::uint32 cmd() const;
  void set_cmd(::PROTOBUF_NAMESPACE_ID::uint32 value);

  // bool success = 20;
  void clear_success();
  bool success() const;
  void set_success(bool value);

  // @@protoc_insertion_point(class_scope:proto.Msg)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  PROTOBUF_NAMESPACE_ID::Any* data_;
  ::PROTOBUF_NAMESPACE_ID::uint32 seq_;
  int type_;
  ::PROTOBUF_NAMESPACE_ID::uint32 cmd_;
  bool success_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Msg_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Msg

// uint32 seq = 1;
inline void Msg::clear_seq() {
  seq_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Msg::seq() const {
  // @@protoc_insertion_point(field_get:proto.Msg.seq)
  return seq_;
}
inline void Msg::set_seq(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  seq_ = value;
  // @@protoc_insertion_point(field_set:proto.Msg.seq)
}

// .proto.Msg.Type type = 2;
inline void Msg::clear_type() {
  type_ = 0;
}
inline ::proto::Msg_Type Msg::type() const {
  // @@protoc_insertion_point(field_get:proto.Msg.type)
  return static_cast< ::proto::Msg_Type >(type_);
}
inline void Msg::set_type(::proto::Msg_Type value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:proto.Msg.type)
}

// .google.protobuf.Any data = 3;
inline bool Msg::has_data() const {
  return this != internal_default_instance() && data_ != nullptr;
}
inline const PROTOBUF_NAMESPACE_ID::Any& Msg::data() const {
  const PROTOBUF_NAMESPACE_ID::Any* p = data_;
  // @@protoc_insertion_point(field_get:proto.Msg.data)
  return p != nullptr ? *p : *reinterpret_cast<const PROTOBUF_NAMESPACE_ID::Any*>(
      &PROTOBUF_NAMESPACE_ID::_Any_default_instance_);
}
inline PROTOBUF_NAMESPACE_ID::Any* Msg::release_data() {
  // @@protoc_insertion_point(field_release:proto.Msg.data)
  
  PROTOBUF_NAMESPACE_ID::Any* temp = data_;
  data_ = nullptr;
  return temp;
}
inline PROTOBUF_NAMESPACE_ID::Any* Msg::mutable_data() {
  
  if (data_ == nullptr) {
    auto* p = CreateMaybeMessage<PROTOBUF_NAMESPACE_ID::Any>(GetArenaNoVirtual());
    data_ = p;
  }
  // @@protoc_insertion_point(field_mutable:proto.Msg.data)
  return data_;
}
inline void Msg::set_allocated_data(PROTOBUF_NAMESPACE_ID::Any* data) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(data_);
  }
  if (data) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      data = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, data, submessage_arena);
    }
    
  } else {
    
  }
  data_ = data;
  // @@protoc_insertion_point(field_set_allocated:proto.Msg.data)
}

// uint32 cmd = 10;
inline void Msg::clear_cmd() {
  cmd_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Msg::cmd() const {
  // @@protoc_insertion_point(field_get:proto.Msg.cmd)
  return cmd_;
}
inline void Msg::set_cmd(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  cmd_ = value;
  // @@protoc_insertion_point(field_set:proto.Msg.cmd)
}

// bool success = 20;
inline void Msg::clear_success() {
  success_ = false;
}
inline bool Msg::success() const {
  // @@protoc_insertion_point(field_get:proto.Msg.success)
  return success_;
}
inline void Msg::set_success(bool value) {
  
  success_ = value;
  // @@protoc_insertion_point(field_set:proto.Msg.success)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::proto::Msg_Type> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto::Msg_Type>() {
  return ::proto::Msg_Type_descriptor();
}
template <> struct is_proto_enum< ::proto::Msg_Cmd> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto::Msg_Cmd>() {
  return ::proto::Msg_Cmd_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Msg_2eproto
