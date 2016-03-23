// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GameState.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "GameState.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* GameState_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GameState_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* GameState_PitchSize_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* GameState_MatchDuration_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_GameState_2eproto() {
  protobuf_AddDesc_GameState_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "GameState.proto");
  GOOGLE_CHECK(file != NULL);
  GameState_descriptor_ = file->message_type(0);
  static const int GameState_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GameState, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GameState, duration_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GameState, pitchsize_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GameState, bots_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GameState, running_),
  };
  GameState_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GameState_descriptor_,
      GameState::default_instance_,
      GameState_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GameState, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GameState, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GameState));
  GameState_PitchSize_descriptor_ = GameState_descriptor_->enum_type(0);
  GameState_MatchDuration_descriptor_ = GameState_descriptor_->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_GameState_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GameState_descriptor_, &GameState::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_GameState_2eproto() {
  delete GameState::default_instance_;
  delete GameState_reflection_;
}

void protobuf_AddDesc_GameState_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017GameState.proto\"\226\002\n\tGameState\022\014\n\004name\030"
    "\001 \001(\t\022*\n\010duration\030\002 \001(\0162\030.GameState.Matc"
    "hDuration\022\'\n\tpitchSize\030\003 \001(\0162\024.GameState"
    ".PitchSize\022\014\n\004bots\030\004 \001(\005\022\017\n\007running\030\005 \001("
    "\010\":\n\tPitchSize\022\016\n\nSIZE_SMALL\020\000\022\017\n\013SIZE_M"
    "EDIUM\020\001\022\014\n\010SIZE_BIG\020\002\"K\n\rMatchDuration\022\022"
    "\n\016DURATION_SHORT\020\000\022\023\n\017DURATION_MEDIUM\020\001\022"
    "\021\n\rDURATION_LONG\020\002", 298);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "GameState.proto", &protobuf_RegisterTypes);
  GameState::default_instance_ = new GameState();
  GameState::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_GameState_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_GameState_2eproto {
  StaticDescriptorInitializer_GameState_2eproto() {
    protobuf_AddDesc_GameState_2eproto();
  }
} static_descriptor_initializer_GameState_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* GameState_PitchSize_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GameState_PitchSize_descriptor_;
}
bool GameState_PitchSize_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const GameState_PitchSize GameState::SIZE_SMALL;
const GameState_PitchSize GameState::SIZE_MEDIUM;
const GameState_PitchSize GameState::SIZE_BIG;
const GameState_PitchSize GameState::PitchSize_MIN;
const GameState_PitchSize GameState::PitchSize_MAX;
const int GameState::PitchSize_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* GameState_MatchDuration_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GameState_MatchDuration_descriptor_;
}
bool GameState_MatchDuration_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const GameState_MatchDuration GameState::DURATION_SHORT;
const GameState_MatchDuration GameState::DURATION_MEDIUM;
const GameState_MatchDuration GameState::DURATION_LONG;
const GameState_MatchDuration GameState::MatchDuration_MIN;
const GameState_MatchDuration GameState::MatchDuration_MAX;
const int GameState::MatchDuration_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int GameState::kNameFieldNumber;
const int GameState::kDurationFieldNumber;
const int GameState::kPitchSizeFieldNumber;
const int GameState::kBotsFieldNumber;
const int GameState::kRunningFieldNumber;
#endif  // !_MSC_VER

GameState::GameState()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:GameState)
}

void GameState::InitAsDefaultInstance() {
}

GameState::GameState(const GameState& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:GameState)
}

void GameState::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  duration_ = 0;
  pitchsize_ = 0;
  bots_ = 0;
  running_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GameState::~GameState() {
  // @@protoc_insertion_point(destructor:GameState)
  SharedDtor();
}

void GameState::SharedDtor() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (this != default_instance_) {
  }
}

void GameState::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GameState::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GameState_descriptor_;
}

const GameState& GameState::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_GameState_2eproto();
  return *default_instance_;
}

GameState* GameState::default_instance_ = NULL;

GameState* GameState::New() const {
  return new GameState;
}

void GameState::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<GameState*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 31) {
    ZR_(duration_, running_);
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        name_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GameState::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:GameState)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string name = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_duration;
        break;
      }

      // optional .GameState.MatchDuration duration = 2;
      case 2: {
        if (tag == 16) {
         parse_duration:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::GameState_MatchDuration_IsValid(value)) {
            set_duration(static_cast< ::GameState_MatchDuration >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_pitchSize;
        break;
      }

      // optional .GameState.PitchSize pitchSize = 3;
      case 3: {
        if (tag == 24) {
         parse_pitchSize:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::GameState_PitchSize_IsValid(value)) {
            set_pitchsize(static_cast< ::GameState_PitchSize >(value));
          } else {
            mutable_unknown_fields()->AddVarint(3, value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_bots;
        break;
      }

      // optional int32 bots = 4;
      case 4: {
        if (tag == 32) {
         parse_bots:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &bots_)));
          set_has_bots();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_running;
        break;
      }

      // optional bool running = 5;
      case 5: {
        if (tag == 40) {
         parse_running:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &running_)));
          set_has_running();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:GameState)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:GameState)
  return false;
#undef DO_
}

void GameState::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:GameState)
  // optional string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->name(), output);
  }

  // optional .GameState.MatchDuration duration = 2;
  if (has_duration()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->duration(), output);
  }

  // optional .GameState.PitchSize pitchSize = 3;
  if (has_pitchsize()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      3, this->pitchsize(), output);
  }

  // optional int32 bots = 4;
  if (has_bots()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->bots(), output);
  }

  // optional bool running = 5;
  if (has_running()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(5, this->running(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:GameState)
}

::google::protobuf::uint8* GameState::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:GameState)
  // optional string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }

  // optional .GameState.MatchDuration duration = 2;
  if (has_duration()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->duration(), target);
  }

  // optional .GameState.PitchSize pitchSize = 3;
  if (has_pitchsize()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      3, this->pitchsize(), target);
  }

  // optional int32 bots = 4;
  if (has_bots()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->bots(), target);
  }

  // optional bool running = 5;
  if (has_running()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(5, this->running(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:GameState)
  return target;
}

int GameState::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // optional .GameState.MatchDuration duration = 2;
    if (has_duration()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->duration());
    }

    // optional .GameState.PitchSize pitchSize = 3;
    if (has_pitchsize()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->pitchsize());
    }

    // optional int32 bots = 4;
    if (has_bots()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->bots());
    }

    // optional bool running = 5;
    if (has_running()) {
      total_size += 1 + 1;
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GameState::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GameState* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GameState*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GameState::MergeFrom(const GameState& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_duration()) {
      set_duration(from.duration());
    }
    if (from.has_pitchsize()) {
      set_pitchsize(from.pitchsize());
    }
    if (from.has_bots()) {
      set_bots(from.bots());
    }
    if (from.has_running()) {
      set_running(from.running());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GameState::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GameState::CopyFrom(const GameState& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GameState::IsInitialized() const {

  return true;
}

void GameState::Swap(GameState* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(duration_, other->duration_);
    std::swap(pitchsize_, other->pitchsize_);
    std::swap(bots_, other->bots_);
    std::swap(running_, other->running_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GameState::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GameState_descriptor_;
  metadata.reflection = GameState_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)