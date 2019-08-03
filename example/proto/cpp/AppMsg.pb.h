// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AppMsg.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_AppMsg_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_AppMsg_2eproto

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
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_AppMsg_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_AppMsg_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_AppMsg_2eproto;
namespace proto {
class AppMsg;
class AppMsgDefaultTypeInternal;
extern AppMsgDefaultTypeInternal _AppMsg_default_instance_;
}  // namespace proto
PROTOBUF_NAMESPACE_OPEN
template<> ::proto::AppMsg* Arena::CreateMaybeMessage<::proto::AppMsg>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace proto {

enum AppMsg_Cmd : int {
  AppMsg_Cmd_NONE = 0,
  AppMsg_Cmd_RESERVED = 10,
  AppMsg_Cmd_HELLO = 11,
  AppMsg_Cmd_AppMsg_Cmd_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  AppMsg_Cmd_AppMsg_Cmd_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool AppMsg_Cmd_IsValid(int value);
constexpr AppMsg_Cmd AppMsg_Cmd_Cmd_MIN = AppMsg_Cmd_NONE;
constexpr AppMsg_Cmd AppMsg_Cmd_Cmd_MAX = AppMsg_Cmd_HELLO;
constexpr int AppMsg_Cmd_Cmd_ARRAYSIZE = AppMsg_Cmd_Cmd_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* AppMsg_Cmd_descriptor();
template<typename T>
inline const std::string& AppMsg_Cmd_Name(T enum_t_value) {
  static_assert(::std::is_same<T, AppMsg_Cmd>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function AppMsg_Cmd_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    AppMsg_Cmd_descriptor(), enum_t_value);
}
inline bool AppMsg_Cmd_Parse(
    const std::string& name, AppMsg_Cmd* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<AppMsg_Cmd>(
    AppMsg_Cmd_descriptor(), name, value);
}
// ===================================================================

class AppMsg :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto.AppMsg) */ {
 public:
  AppMsg();
  virtual ~AppMsg();

  AppMsg(const AppMsg& from);
  AppMsg(AppMsg&& from) noexcept
    : AppMsg() {
    *this = ::std::move(from);
  }

  inline AppMsg& operator=(const AppMsg& from) {
    CopyFrom(from);
    return *this;
  }
  inline AppMsg& operator=(AppMsg&& from) noexcept {
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
  static const AppMsg& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const AppMsg* internal_default_instance() {
    return reinterpret_cast<const AppMsg*>(
               &_AppMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(AppMsg& a, AppMsg& b) {
    a.Swap(&b);
  }
  inline void Swap(AppMsg* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline AppMsg* New() const final {
    return CreateMaybeMessage<AppMsg>(nullptr);
  }

  AppMsg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<AppMsg>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const AppMsg& from);
  void MergeFrom(const AppMsg& from);
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
  void InternalSwap(AppMsg* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "proto.AppMsg";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_AppMsg_2eproto);
    return ::descriptor_table_AppMsg_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  typedef AppMsg_Cmd Cmd;
  static constexpr Cmd NONE =
    AppMsg_Cmd_NONE;
  static constexpr Cmd RESERVED =
    AppMsg_Cmd_RESERVED;
  static constexpr Cmd HELLO =
    AppMsg_Cmd_HELLO;
  static inline bool Cmd_IsValid(int value) {
    return AppMsg_Cmd_IsValid(value);
  }
  static constexpr Cmd Cmd_MIN =
    AppMsg_Cmd_Cmd_MIN;
  static constexpr Cmd Cmd_MAX =
    AppMsg_Cmd_Cmd_MAX;
  static constexpr int Cmd_ARRAYSIZE =
    AppMsg_Cmd_Cmd_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  Cmd_descriptor() {
    return AppMsg_Cmd_descriptor();
  }
  template<typename T>
  static inline const std::string& Cmd_Name(T enum_t_value) {
    static_assert(::std::is_same<T, Cmd>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function Cmd_Name.");
    return AppMsg_Cmd_Name(enum_t_value);
  }
  static inline bool Cmd_Parse(const std::string& name,
      Cmd* value) {
    return AppMsg_Cmd_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:proto.AppMsg)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_AppMsg_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// AppMsg

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::proto::AppMsg_Cmd> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto::AppMsg_Cmd>() {
  return ::proto::AppMsg_Cmd_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_AppMsg_2eproto
