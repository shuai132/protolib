// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AppMsg.proto

#include "AppMsg.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace proto {
class AppMsgDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<AppMsg> _instance;
} _AppMsg_default_instance_;
}  // namespace proto
static void InitDefaultsscc_info_AppMsg_AppMsg_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::proto::_AppMsg_default_instance_;
    new (ptr) ::proto::AppMsg();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::proto::AppMsg::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_AppMsg_AppMsg_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_AppMsg_AppMsg_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_AppMsg_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_AppMsg_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_AppMsg_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_AppMsg_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::proto::AppMsg, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::proto::AppMsg)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::proto::_AppMsg_default_instance_),
};

const char descriptor_table_protodef_AppMsg_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014AppMsg.proto\022\005proto\"W\n\006AppMsg\"M\n\003Cmd\022\010"
  "\n\004NONE\020\000\022\014\n\010RESERVED\020\n\022\n\n\006HELLO1\020\013\022\n\n\006HE"
  "LLO2\020\014\022\n\n\006HELLO3\020\r\022\n\n\006HELLO4\020\016b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_AppMsg_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_AppMsg_2eproto_sccs[1] = {
  &scc_info_AppMsg_AppMsg_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_AppMsg_2eproto_once;
static bool descriptor_table_AppMsg_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_AppMsg_2eproto = {
  &descriptor_table_AppMsg_2eproto_initialized, descriptor_table_protodef_AppMsg_2eproto, "AppMsg.proto", 118,
  &descriptor_table_AppMsg_2eproto_once, descriptor_table_AppMsg_2eproto_sccs, descriptor_table_AppMsg_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_AppMsg_2eproto::offsets,
  file_level_metadata_AppMsg_2eproto, 1, file_level_enum_descriptors_AppMsg_2eproto, file_level_service_descriptors_AppMsg_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_AppMsg_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_AppMsg_2eproto), true);
namespace proto {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* AppMsg_Cmd_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_AppMsg_2eproto);
  return file_level_enum_descriptors_AppMsg_2eproto[0];
}
bool AppMsg_Cmd_IsValid(int value) {
  switch (value) {
    case 0:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr AppMsg_Cmd AppMsg::NONE;
constexpr AppMsg_Cmd AppMsg::RESERVED;
constexpr AppMsg_Cmd AppMsg::HELLO1;
constexpr AppMsg_Cmd AppMsg::HELLO2;
constexpr AppMsg_Cmd AppMsg::HELLO3;
constexpr AppMsg_Cmd AppMsg::HELLO4;
constexpr AppMsg_Cmd AppMsg::Cmd_MIN;
constexpr AppMsg_Cmd AppMsg::Cmd_MAX;
constexpr int AppMsg::Cmd_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

void AppMsg::InitAsDefaultInstance() {
}
class AppMsg::_Internal {
 public:
};

AppMsg::AppMsg()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:proto.AppMsg)
}
AppMsg::AppMsg(const AppMsg& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:proto.AppMsg)
}

void AppMsg::SharedCtor() {
}

AppMsg::~AppMsg() {
  // @@protoc_insertion_point(destructor:proto.AppMsg)
  SharedDtor();
}

void AppMsg::SharedDtor() {
}

void AppMsg::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const AppMsg& AppMsg::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_AppMsg_AppMsg_2eproto.base);
  return *internal_default_instance();
}


void AppMsg::Clear() {
// @@protoc_insertion_point(message_clear_start:proto.AppMsg)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* AppMsg::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      default: {
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool AppMsg::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:proto.AppMsg)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
  handle_unusual:
    if (tag == 0) {
      goto success;
    }
    DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
          input, tag, _internal_metadata_.mutable_unknown_fields()));
  }
success:
  // @@protoc_insertion_point(parse_success:proto.AppMsg)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:proto.AppMsg)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void AppMsg::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:proto.AppMsg)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:proto.AppMsg)
}

::PROTOBUF_NAMESPACE_ID::uint8* AppMsg::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:proto.AppMsg)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:proto.AppMsg)
  return target;
}

size_t AppMsg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:proto.AppMsg)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void AppMsg::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:proto.AppMsg)
  GOOGLE_DCHECK_NE(&from, this);
  const AppMsg* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<AppMsg>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:proto.AppMsg)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:proto.AppMsg)
    MergeFrom(*source);
  }
}

void AppMsg::MergeFrom(const AppMsg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:proto.AppMsg)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

}

void AppMsg::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:proto.AppMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AppMsg::CopyFrom(const AppMsg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:proto.AppMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AppMsg::IsInitialized() const {
  return true;
}

void AppMsg::InternalSwap(AppMsg* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::PROTOBUF_NAMESPACE_ID::Metadata AppMsg::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::proto::AppMsg* Arena::CreateMaybeMessage< ::proto::AppMsg >(Arena* arena) {
  return Arena::CreateInternal< ::proto::AppMsg >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
