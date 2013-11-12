// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ws_addressing.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace trentino {
namespace bindingsca {
namespace csoap {

void protobuf_ShutdownFile_ws_5faddressing_2eproto() {
  delete Addressing::default_instance_;
  delete Addressing_EndpointReferenceType::default_instance_;
  delete Addressing_MultipleAny::default_instance_;
  delete Addressing_ServiceNameType::default_instance_;
}

void protobuf_AddDesc_ws_5faddressing_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  Addressing::default_instance_ = new Addressing();
  Addressing_EndpointReferenceType::default_instance_ = new Addressing_EndpointReferenceType();
  Addressing_MultipleAny::default_instance_ = new Addressing_MultipleAny();
  Addressing_ServiceNameType::default_instance_ = new Addressing_ServiceNameType();
  Addressing::default_instance_->InitAsDefaultInstance();
  Addressing_EndpointReferenceType::default_instance_->InitAsDefaultInstance();
  Addressing_MultipleAny::default_instance_->InitAsDefaultInstance();
  Addressing_ServiceNameType::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ws_5faddressing_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ws_5faddressing_2eproto {
  StaticDescriptorInitializer_ws_5faddressing_2eproto() {
    protobuf_AddDesc_ws_5faddressing_2eproto();
  }
} static_descriptor_initializer_ws_5faddressing_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int Addressing_EndpointReferenceType::kAddressFieldNumber;
const int Addressing_EndpointReferenceType::kReferencePropertiesFieldNumber;
const int Addressing_EndpointReferenceType::kReferenceParametersFieldNumber;
const int Addressing_EndpointReferenceType::kPortTypeFieldNumber;
const int Addressing_EndpointReferenceType::kServiceNameFieldNumber;
#endif  // !_MSC_VER

Addressing_EndpointReferenceType::Addressing_EndpointReferenceType()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void Addressing_EndpointReferenceType::InitAsDefaultInstance() {
  referenceproperties_ = const_cast< ::trentino::bindingsca::csoap::Addressing_MultipleAny*>(&::trentino::bindingsca::csoap::Addressing_MultipleAny::default_instance());
  referenceparameters_ = const_cast< ::trentino::bindingsca::csoap::Addressing_MultipleAny*>(&::trentino::bindingsca::csoap::Addressing_MultipleAny::default_instance());
  servicename_ = const_cast< ::trentino::bindingsca::csoap::Addressing_ServiceNameType*>(&::trentino::bindingsca::csoap::Addressing_ServiceNameType::default_instance());
}

Addressing_EndpointReferenceType::Addressing_EndpointReferenceType(const Addressing_EndpointReferenceType& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void Addressing_EndpointReferenceType::SharedCtor() {
  _cached_size_ = 0;
  address_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  referenceproperties_ = NULL;
  referenceparameters_ = NULL;
  porttype_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  servicename_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Addressing_EndpointReferenceType::~Addressing_EndpointReferenceType() {
  SharedDtor();
}

void Addressing_EndpointReferenceType::SharedDtor() {
  if (address_ != &::google::protobuf::internal::kEmptyString) {
    delete address_;
  }
  if (porttype_ != &::google::protobuf::internal::kEmptyString) {
    delete porttype_;
  }
  if (this != default_instance_) {
    delete referenceproperties_;
    delete referenceparameters_;
    delete servicename_;
  }
}

void Addressing_EndpointReferenceType::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const Addressing_EndpointReferenceType& Addressing_EndpointReferenceType::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ws_5faddressing_2eproto();  return *default_instance_;
}

Addressing_EndpointReferenceType* Addressing_EndpointReferenceType::default_instance_ = NULL;

Addressing_EndpointReferenceType* Addressing_EndpointReferenceType::New() const {
  return new Addressing_EndpointReferenceType;
}

void Addressing_EndpointReferenceType::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_address()) {
      if (address_ != &::google::protobuf::internal::kEmptyString) {
        address_->clear();
      }
    }
    if (has_referenceproperties()) {
      if (referenceproperties_ != NULL) referenceproperties_->::trentino::bindingsca::csoap::Addressing_MultipleAny::Clear();
    }
    if (has_referenceparameters()) {
      if (referenceparameters_ != NULL) referenceparameters_->::trentino::bindingsca::csoap::Addressing_MultipleAny::Clear();
    }
    if (has_porttype()) {
      if (porttype_ != &::google::protobuf::internal::kEmptyString) {
        porttype_->clear();
      }
    }
    if (has_servicename()) {
      if (servicename_ != NULL) servicename_->::trentino::bindingsca::csoap::Addressing_ServiceNameType::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool Addressing_EndpointReferenceType::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string address = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_address()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_referenceProperties;
        break;
      }
      
      // optional .trentino.bindingsca.csoap.Addressing.MultipleAny referenceProperties = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_referenceProperties:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_referenceproperties()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_referenceParameters;
        break;
      }
      
      // optional .trentino.bindingsca.csoap.Addressing.MultipleAny referenceParameters = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_referenceParameters:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_referenceparameters()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_portType;
        break;
      }
      
      // optional string portType = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_portType:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_porttype()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_serviceName;
        break;
      }
      
      // optional .trentino.bindingsca.csoap.Addressing.ServiceNameType serviceName = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_serviceName:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_servicename()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Addressing_EndpointReferenceType::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string address = 1;
  if (has_address()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->address(), output);
  }
  
  // optional .trentino.bindingsca.csoap.Addressing.MultipleAny referenceProperties = 2;
  if (has_referenceproperties()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      2, this->referenceproperties(), output);
  }
  
  // optional .trentino.bindingsca.csoap.Addressing.MultipleAny referenceParameters = 3;
  if (has_referenceparameters()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      3, this->referenceparameters(), output);
  }
  
  // optional string portType = 4;
  if (has_porttype()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->porttype(), output);
  }
  
  // optional .trentino.bindingsca.csoap.Addressing.ServiceNameType serviceName = 5;
  if (has_servicename()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      5, this->servicename(), output);
  }
  
}

int Addressing_EndpointReferenceType::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string address = 1;
    if (has_address()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->address());
    }
    
    // optional .trentino.bindingsca.csoap.Addressing.MultipleAny referenceProperties = 2;
    if (has_referenceproperties()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->referenceproperties());
    }
    
    // optional .trentino.bindingsca.csoap.Addressing.MultipleAny referenceParameters = 3;
    if (has_referenceparameters()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->referenceparameters());
    }
    
    // optional string portType = 4;
    if (has_porttype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->porttype());
    }
    
    // optional .trentino.bindingsca.csoap.Addressing.ServiceNameType serviceName = 5;
    if (has_servicename()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->servicename());
    }
    
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Addressing_EndpointReferenceType::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const Addressing_EndpointReferenceType*>(&from));
}

void Addressing_EndpointReferenceType::MergeFrom(const Addressing_EndpointReferenceType& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_address()) {
      set_address(from.address());
    }
    if (from.has_referenceproperties()) {
      mutable_referenceproperties()->::trentino::bindingsca::csoap::Addressing_MultipleAny::MergeFrom(from.referenceproperties());
    }
    if (from.has_referenceparameters()) {
      mutable_referenceparameters()->::trentino::bindingsca::csoap::Addressing_MultipleAny::MergeFrom(from.referenceparameters());
    }
    if (from.has_porttype()) {
      set_porttype(from.porttype());
    }
    if (from.has_servicename()) {
      mutable_servicename()->::trentino::bindingsca::csoap::Addressing_ServiceNameType::MergeFrom(from.servicename());
    }
  }
}

void Addressing_EndpointReferenceType::CopyFrom(const Addressing_EndpointReferenceType& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Addressing_EndpointReferenceType::IsInitialized() const {
  
  return true;
}

void Addressing_EndpointReferenceType::Swap(Addressing_EndpointReferenceType* other) {
  if (other != this) {
    std::swap(address_, other->address_);
    std::swap(referenceproperties_, other->referenceproperties_);
    std::swap(referenceparameters_, other->referenceparameters_);
    std::swap(porttype_, other->porttype_);
    std::swap(servicename_, other->servicename_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string Addressing_EndpointReferenceType::GetTypeName() const {
  return "trentino.bindingsca.csoap.Addressing.EndpointReferenceType";
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Addressing_MultipleAny::kPropertyFieldNumber;
#endif  // !_MSC_VER

Addressing_MultipleAny::Addressing_MultipleAny()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void Addressing_MultipleAny::InitAsDefaultInstance() {
}

Addressing_MultipleAny::Addressing_MultipleAny(const Addressing_MultipleAny& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void Addressing_MultipleAny::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Addressing_MultipleAny::~Addressing_MultipleAny() {
  SharedDtor();
}

void Addressing_MultipleAny::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Addressing_MultipleAny::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const Addressing_MultipleAny& Addressing_MultipleAny::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ws_5faddressing_2eproto();  return *default_instance_;
}

Addressing_MultipleAny* Addressing_MultipleAny::default_instance_ = NULL;

Addressing_MultipleAny* Addressing_MultipleAny::New() const {
  return new Addressing_MultipleAny;
}

void Addressing_MultipleAny::Clear() {
  property_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool Addressing_MultipleAny::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated string property = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_property:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_property()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_property;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Addressing_MultipleAny::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated string property = 1;
  for (int i = 0; i < this->property_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->property(i), output);
  }
  
}

int Addressing_MultipleAny::ByteSize() const {
  int total_size = 0;
  
  // repeated string property = 1;
  total_size += 1 * this->property_size();
  for (int i = 0; i < this->property_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->property(i));
  }
  
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Addressing_MultipleAny::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const Addressing_MultipleAny*>(&from));
}

void Addressing_MultipleAny::MergeFrom(const Addressing_MultipleAny& from) {
  GOOGLE_CHECK_NE(&from, this);
  property_.MergeFrom(from.property_);
}

void Addressing_MultipleAny::CopyFrom(const Addressing_MultipleAny& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Addressing_MultipleAny::IsInitialized() const {
  
  return true;
}

void Addressing_MultipleAny::Swap(Addressing_MultipleAny* other) {
  if (other != this) {
    property_.Swap(&other->property_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string Addressing_MultipleAny::GetTypeName() const {
  return "trentino.bindingsca.csoap.Addressing.MultipleAny";
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Addressing_ServiceNameType::kPortNameFieldNumber;
#endif  // !_MSC_VER

Addressing_ServiceNameType::Addressing_ServiceNameType()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void Addressing_ServiceNameType::InitAsDefaultInstance() {
}

Addressing_ServiceNameType::Addressing_ServiceNameType(const Addressing_ServiceNameType& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void Addressing_ServiceNameType::SharedCtor() {
  _cached_size_ = 0;
  portname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Addressing_ServiceNameType::~Addressing_ServiceNameType() {
  SharedDtor();
}

void Addressing_ServiceNameType::SharedDtor() {
  if (portname_ != &::google::protobuf::internal::kEmptyString) {
    delete portname_;
  }
  if (this != default_instance_) {
  }
}

void Addressing_ServiceNameType::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const Addressing_ServiceNameType& Addressing_ServiceNameType::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ws_5faddressing_2eproto();  return *default_instance_;
}

Addressing_ServiceNameType* Addressing_ServiceNameType::default_instance_ = NULL;

Addressing_ServiceNameType* Addressing_ServiceNameType::New() const {
  return new Addressing_ServiceNameType;
}

void Addressing_ServiceNameType::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_portname()) {
      if (portname_ != &::google::protobuf::internal::kEmptyString) {
        portname_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool Addressing_ServiceNameType::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string portName = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_portname()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Addressing_ServiceNameType::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string portName = 1;
  if (has_portname()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->portname(), output);
  }
  
}

int Addressing_ServiceNameType::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string portName = 1;
    if (has_portname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->portname());
    }
    
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Addressing_ServiceNameType::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const Addressing_ServiceNameType*>(&from));
}

void Addressing_ServiceNameType::MergeFrom(const Addressing_ServiceNameType& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_portname()) {
      set_portname(from.portname());
    }
  }
}

void Addressing_ServiceNameType::CopyFrom(const Addressing_ServiceNameType& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Addressing_ServiceNameType::IsInitialized() const {
  
  return true;
}

void Addressing_ServiceNameType::Swap(Addressing_ServiceNameType* other) {
  if (other != this) {
    std::swap(portname_, other->portname_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string Addressing_ServiceNameType::GetTypeName() const {
  return "trentino.bindingsca.csoap.Addressing.ServiceNameType";
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Addressing::kEndpointReferenceFieldNumber;
const int Addressing::kMessageIDFieldNumber;
const int Addressing::kToFieldNumber;
const int Addressing::kActionFieldNumber;
const int Addressing::kFromFieldNumber;
const int Addressing::kReplyToFieldNumber;
const int Addressing::kFaultToFieldNumber;
#endif  // !_MSC_VER

Addressing::Addressing()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void Addressing::InitAsDefaultInstance() {
  endpointreference_ = const_cast< ::trentino::bindingsca::csoap::Addressing_EndpointReferenceType*>(&::trentino::bindingsca::csoap::Addressing_EndpointReferenceType::default_instance());
  replyto_ = const_cast< ::trentino::bindingsca::csoap::Addressing_EndpointReferenceType*>(&::trentino::bindingsca::csoap::Addressing_EndpointReferenceType::default_instance());
  faultto_ = const_cast< ::trentino::bindingsca::csoap::Addressing_EndpointReferenceType*>(&::trentino::bindingsca::csoap::Addressing_EndpointReferenceType::default_instance());
}

Addressing::Addressing(const Addressing& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void Addressing::SharedCtor() {
  _cached_size_ = 0;
  endpointreference_ = NULL;
  messageid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  to_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  action_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  from_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  replyto_ = NULL;
  faultto_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Addressing::~Addressing() {
  SharedDtor();
}

void Addressing::SharedDtor() {
  if (messageid_ != &::google::protobuf::internal::kEmptyString) {
    delete messageid_;
  }
  if (to_ != &::google::protobuf::internal::kEmptyString) {
    delete to_;
  }
  if (action_ != &::google::protobuf::internal::kEmptyString) {
    delete action_;
  }
  if (from_ != &::google::protobuf::internal::kEmptyString) {
    delete from_;
  }
  if (this != default_instance_) {
    delete endpointreference_;
    delete replyto_;
    delete faultto_;
  }
}

void Addressing::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const Addressing& Addressing::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ws_5faddressing_2eproto();  return *default_instance_;
}

Addressing* Addressing::default_instance_ = NULL;

Addressing* Addressing::New() const {
  return new Addressing;
}

void Addressing::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_endpointreference()) {
      if (endpointreference_ != NULL) endpointreference_->::trentino::bindingsca::csoap::Addressing_EndpointReferenceType::Clear();
    }
    if (has_messageid()) {
      if (messageid_ != &::google::protobuf::internal::kEmptyString) {
        messageid_->clear();
      }
    }
    if (has_to()) {
      if (to_ != &::google::protobuf::internal::kEmptyString) {
        to_->clear();
      }
    }
    if (has_action()) {
      if (action_ != &::google::protobuf::internal::kEmptyString) {
        action_->clear();
      }
    }
    if (has_from()) {
      if (from_ != &::google::protobuf::internal::kEmptyString) {
        from_->clear();
      }
    }
    if (has_replyto()) {
      if (replyto_ != NULL) replyto_->::trentino::bindingsca::csoap::Addressing_EndpointReferenceType::Clear();
    }
    if (has_faultto()) {
      if (faultto_ != NULL) faultto_->::trentino::bindingsca::csoap::Addressing_EndpointReferenceType::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool Addressing::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .trentino.bindingsca.csoap.Addressing.EndpointReferenceType endpointReference = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_endpointreference()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_messageID;
        break;
      }
      
      // optional string messageID = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_messageID:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_messageid()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_to;
        break;
      }
      
      // optional string to = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_to:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_to()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_action;
        break;
      }
      
      // optional string action = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_action:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_action()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_from;
        break;
      }
      
      // optional string from = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_from:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_from()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_replyTo;
        break;
      }
      
      // optional .trentino.bindingsca.csoap.Addressing.EndpointReferenceType replyTo = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_replyTo:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_replyto()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(66)) goto parse_faultTo;
        break;
      }
      
      // optional .trentino.bindingsca.csoap.Addressing.EndpointReferenceType faultTo = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_faultTo:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_faultto()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Addressing::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .trentino.bindingsca.csoap.Addressing.EndpointReferenceType endpointReference = 1;
  if (has_endpointreference()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      1, this->endpointreference(), output);
  }
  
  // optional string messageID = 2;
  if (has_messageid()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->messageid(), output);
  }
  
  // optional string to = 4;
  if (has_to()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->to(), output);
  }
  
  // optional string action = 5;
  if (has_action()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->action(), output);
  }
  
  // optional string from = 6;
  if (has_from()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      6, this->from(), output);
  }
  
  // optional .trentino.bindingsca.csoap.Addressing.EndpointReferenceType replyTo = 7;
  if (has_replyto()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      7, this->replyto(), output);
  }
  
  // optional .trentino.bindingsca.csoap.Addressing.EndpointReferenceType faultTo = 8;
  if (has_faultto()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      8, this->faultto(), output);
  }
  
}

int Addressing::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .trentino.bindingsca.csoap.Addressing.EndpointReferenceType endpointReference = 1;
    if (has_endpointreference()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->endpointreference());
    }
    
    // optional string messageID = 2;
    if (has_messageid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->messageid());
    }
    
    // optional string to = 4;
    if (has_to()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->to());
    }
    
    // optional string action = 5;
    if (has_action()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->action());
    }
    
    // optional string from = 6;
    if (has_from()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->from());
    }
    
    // optional .trentino.bindingsca.csoap.Addressing.EndpointReferenceType replyTo = 7;
    if (has_replyto()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->replyto());
    }
    
    // optional .trentino.bindingsca.csoap.Addressing.EndpointReferenceType faultTo = 8;
    if (has_faultto()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->faultto());
    }
    
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Addressing::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const Addressing*>(&from));
}

void Addressing::MergeFrom(const Addressing& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_endpointreference()) {
      mutable_endpointreference()->::trentino::bindingsca::csoap::Addressing_EndpointReferenceType::MergeFrom(from.endpointreference());
    }
    if (from.has_messageid()) {
      set_messageid(from.messageid());
    }
    if (from.has_to()) {
      set_to(from.to());
    }
    if (from.has_action()) {
      set_action(from.action());
    }
    if (from.has_from()) {
      set_from(from.from());
    }
    if (from.has_replyto()) {
      mutable_replyto()->::trentino::bindingsca::csoap::Addressing_EndpointReferenceType::MergeFrom(from.replyto());
    }
    if (from.has_faultto()) {
      mutable_faultto()->::trentino::bindingsca::csoap::Addressing_EndpointReferenceType::MergeFrom(from.faultto());
    }
  }
}

void Addressing::CopyFrom(const Addressing& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Addressing::IsInitialized() const {
  
  return true;
}

void Addressing::Swap(Addressing* other) {
  if (other != this) {
    std::swap(endpointreference_, other->endpointreference_);
    std::swap(messageid_, other->messageid_);
    std::swap(to_, other->to_);
    std::swap(action_, other->action_);
    std::swap(from_, other->from_);
    std::swap(replyto_, other->replyto_);
    std::swap(faultto_, other->faultto_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string Addressing::GetTypeName() const {
  return "trentino.bindingsca.csoap.Addressing";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace csoap
}  // namespace bindingsca
}  // namespace trentino

// @@protoc_insertion_point(global_scope)
