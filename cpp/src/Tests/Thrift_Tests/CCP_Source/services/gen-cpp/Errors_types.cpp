/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "Errors_types.h"

#include <algorithm>

namespace siemens { namespace bt { namespace error {

int _kErrorCodeValues[] = {
  ErrorCode::UNKNOWN,
  ErrorCode::BAD_DATA_FORMAT,
  ErrorCode::PERMISSION_DENIED,
  ErrorCode::INTERNAL_ERROR,
  ErrorCode::DATA_REQUIRED,
  ErrorCode::LIMIT_REACHED,
  ErrorCode::QUOTA_REACHED,
  ErrorCode::INVALID_AUTH,
  ErrorCode::AUTH_EXPIRED,
  ErrorCode::DATA_CONFLICT,
  ErrorCode::ENML_VALIDATION,
  ErrorCode::SHARD_UNAVAILABLE
};
const char* _kErrorCodeNames[] = {
  "UNKNOWN",
  "BAD_DATA_FORMAT",
  "PERMISSION_DENIED",
  "INTERNAL_ERROR",
  "DATA_REQUIRED",
  "LIMIT_REACHED",
  "QUOTA_REACHED",
  "INVALID_AUTH",
  "AUTH_EXPIRED",
  "DATA_CONFLICT",
  "ENML_VALIDATION",
  "SHARD_UNAVAILABLE"
};
const std::map<int, const char*> _ErrorCode_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(12, _kErrorCodeValues, _kErrorCodeNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

int _kBA_ERROR_CLASSValues[] = {
  BA_ERROR_CLASS::BA_ERR_CLASS_DEVICE,
  BA_ERROR_CLASS::BA_ERR_CLASS_OBJECT,
  BA_ERROR_CLASS::BA_ERR_CLASS_PROPERTY,
  BA_ERROR_CLASS::BA_ERR_CLASS_RESOURCES,
  BA_ERROR_CLASS::BA_ERR_CLASS_SECURITY,
  BA_ERROR_CLASS::BA_ERR_CLASS_SERVICES,
  BA_ERROR_CLASS::BA_ERR_CLASS_VT,
  BA_ERROR_CLASS::BA_ERR_CLASS_LAST_KNOWN,
  BA_ERROR_CLASS::BA_ERR_CLASS_ASHRAE_MAX,
  BA_ERROR_CLASS::BA_ERR_CLASS_FIRST_PROPRIETARY,
  BA_ERROR_CLASS::BA_ERR_CLASS_MAX
};
const char* _kBA_ERROR_CLASSNames[] = {
  "BA_ERR_CLASS_DEVICE",
  "BA_ERR_CLASS_OBJECT",
  "BA_ERR_CLASS_PROPERTY",
  "BA_ERR_CLASS_RESOURCES",
  "BA_ERR_CLASS_SECURITY",
  "BA_ERR_CLASS_SERVICES",
  "BA_ERR_CLASS_VT",
  "BA_ERR_CLASS_LAST_KNOWN",
  "BA_ERR_CLASS_ASHRAE_MAX",
  "BA_ERR_CLASS_FIRST_PROPRIETARY",
  "BA_ERR_CLASS_MAX"
};
const std::map<int, const char*> _BA_ERROR_CLASS_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(11, _kBA_ERROR_CLASSValues, _kBA_ERROR_CLASSNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

int _kBA_ERROR_CODEValues[] = {
  BA_ERROR_CODE::BA_ERR_CODE_OTHER,
  BA_ERROR_CODE::BA_ERR_CODE_AUTHENTICATION_FAILED,
  BA_ERROR_CODE::BA_ERR_CODE_CONFIG_IN_PROGRESS,
  BA_ERROR_CODE::BA_ERR_CODE_DEVICE_BUSY,
  BA_ERROR_CODE::BA_ERR_CODE_DYN_CREATION_NOT_SUPP,
  BA_ERROR_CODE::BA_ERR_CODE_FILE_ACCESS_DENIED,
  BA_ERROR_CODE::BA_ERR_CODE_WRONG_SECURITY_LEVELS,
  BA_ERROR_CODE::BA_ERR_CODE_INCONSISTENT_PARAMS,
  BA_ERROR_CODE::BA_ERR_CODE_INVALID_PARAMETERS,
  BA_ERROR_CODE::BA_ERR_CODE_INVALID_SELECTION_CRIT,
  BA_ERROR_CODE::BA_ERR_CODE_INVALID_DATA_TYPE,
  BA_ERROR_CODE::BA_ERR_CODE_INVALID_FILE_ACCESS,
  BA_ERROR_CODE::BA_ERR_CODE_INVALID_FILE_START_POS,
  BA_ERROR_CODE::BA_ERR_CODE_INVALID_OPERATOR_NAME,
  BA_ERROR_CODE::BA_ERR_CODE_INVALID_PARAMETER_TYPE,
  BA_ERROR_CODE::BA_ERR_CODE_INVALID_TIME_STAMP,
  BA_ERROR_CODE::BA_ERR_CODE_KEY_GENERATION_ERROR,
  BA_ERROR_CODE::BA_ERR_CODE_MISSING_PARAMETER,
  BA_ERROR_CODE::BA_ERR_CODE_NO_OBJS_OF_SPEC_TYPE,
  BA_ERROR_CODE::BA_ERR_CODE_OBJECT_NOT_FOUND,
  BA_ERROR_CODE::BA_ERR_CODE_NO_SPACE_FOR_OBJECT,
  BA_ERROR_CODE::BA_ERR_CODE_NO_SPACE_FOR_ELEMENT,
  BA_ERROR_CODE::BA_ERR_CODE_NO_SPACE_TO_WRITE_PROP,
  BA_ERROR_CODE::BA_ERR_CODE_NO_VT_SESSIONS_AVAIL,
  BA_ERROR_CODE::BA_ERR_CODE_PROP_IS_NOT_A_LIST,
  BA_ERROR_CODE::BA_ERR_CODE_OBJ_DELETION_DENIED,
  BA_ERROR_CODE::BA_ERR_CODE_OBJ_ID_ALREADY_EXISTS,
  BA_ERROR_CODE::BA_ERR_CODE_OPERATIONAL_PROBLEM,
  BA_ERROR_CODE::BA_ERR_CODE_PASSWORD_FAILURE,
  BA_ERROR_CODE::BA_ERR_CODE_READ_ACCESS_DENIED,
  BA_ERROR_CODE::BA_ERR_CODE_SECURITY_NOT_SUPPORTED,
  BA_ERROR_CODE::BA_ERR_CODE_SERVICE_REQUEST_DENIED,
  BA_ERROR_CODE::BA_ERR_CODE_TIMEOUT,
  BA_ERROR_CODE::BA_ERR_CODE_UNKNOWN_OBJECT,
  BA_ERROR_CODE::BA_ERR_CODE_UNKNOWN_PROPERTY,
  BA_ERROR_CODE::BA_ERR_CODE_UNKNOWN_VT_CLASS,
  BA_ERROR_CODE::BA_ERR_CODE_UNKNOWN_VT_SESSION,
  BA_ERROR_CODE::BA_ERR_CODE_UNSUPPORTED_OBJ_TYPE,
  BA_ERROR_CODE::BA_ERR_CODE_VALUE_OUT_OF_RANGE,
  BA_ERROR_CODE::BA_ERR_CODE_VT_SESSION_CLOSED,
  BA_ERROR_CODE::BA_ERR_CODE_VT_SESSION_TERM_FAILED,
  BA_ERROR_CODE::BA_ERR_CODE_WRITE_ACCESS_DENIED,
  BA_ERROR_CODE::BA_ERR_CODE_CHAR_SET_NOT_SUPPORTED,
  BA_ERROR_CODE::BA_ERR_CODE_INVALID_ARRAY_INDEX,
  BA_ERROR_CODE::BA_ERR_CODE_COV_SUBS_FAILED,
  BA_ERROR_CODE::BA_ERR_CODE_NOT_COV_PROPERTY,
  BA_ERROR_CODE::BA_ERR_CODE_OPTIONAL_FUNC_NOT_SUPP,
  BA_ERROR_CODE::BA_ERR_CODE_INVALID_CONFIG_DATA,
  BA_ERROR_CODE::BA_ERR_CODE_DATATYPE_NOT_SUPPORTED,
  BA_ERROR_CODE::BA_ERR_CODE_DUPLICATE_NAME,
  BA_ERROR_CODE::BA_ERR_CODE_DUPLICATE_OBJECT_ID,
  BA_ERROR_CODE::BA_ERR_CODE_PROPERTY_IS_NOT_AN_ARRAY,
  BA_ERROR_CODE::BA_ERR_CODE_VALUE_NOT_INITIALIZED,
  BA_ERROR_CODE::BA_ERR_CODE_INVALID_EVENT_STATE,
  BA_ERROR_CODE::BA_ERR_CODE_NO_ALARM_CONFIGURED,
  BA_ERROR_CODE::BA_ERR_CODE_LOG_BUFFER_FULL,
  BA_ERROR_CODE::BA_ERR_CODE_LIST_ELEMENT_NOT_FOUND,
  BA_ERROR_CODE::BA_ERR_CODE_LAST_KNOWN,
  BA_ERROR_CODE::BA_ERR_CODE_ASHRAE_MAX,
  BA_ERROR_CODE::BA_ERR_CODE_FIRST_PROPRIETARY,
  BA_ERROR_CODE::BA_ERR_CODE_MAX
};
const char* _kBA_ERROR_CODENames[] = {
  "BA_ERR_CODE_OTHER",
  "BA_ERR_CODE_AUTHENTICATION_FAILED",
  "BA_ERR_CODE_CONFIG_IN_PROGRESS",
  "BA_ERR_CODE_DEVICE_BUSY",
  "BA_ERR_CODE_DYN_CREATION_NOT_SUPP",
  "BA_ERR_CODE_FILE_ACCESS_DENIED",
  "BA_ERR_CODE_WRONG_SECURITY_LEVELS",
  "BA_ERR_CODE_INCONSISTENT_PARAMS",
  "BA_ERR_CODE_INVALID_PARAMETERS",
  "BA_ERR_CODE_INVALID_SELECTION_CRIT",
  "BA_ERR_CODE_INVALID_DATA_TYPE",
  "BA_ERR_CODE_INVALID_FILE_ACCESS",
  "BA_ERR_CODE_INVALID_FILE_START_POS",
  "BA_ERR_CODE_INVALID_OPERATOR_NAME",
  "BA_ERR_CODE_INVALID_PARAMETER_TYPE",
  "BA_ERR_CODE_INVALID_TIME_STAMP",
  "BA_ERR_CODE_KEY_GENERATION_ERROR",
  "BA_ERR_CODE_MISSING_PARAMETER",
  "BA_ERR_CODE_NO_OBJS_OF_SPEC_TYPE",
  "BA_ERR_CODE_OBJECT_NOT_FOUND",
  "BA_ERR_CODE_NO_SPACE_FOR_OBJECT",
  "BA_ERR_CODE_NO_SPACE_FOR_ELEMENT",
  "BA_ERR_CODE_NO_SPACE_TO_WRITE_PROP",
  "BA_ERR_CODE_NO_VT_SESSIONS_AVAIL",
  "BA_ERR_CODE_PROP_IS_NOT_A_LIST",
  "BA_ERR_CODE_OBJ_DELETION_DENIED",
  "BA_ERR_CODE_OBJ_ID_ALREADY_EXISTS",
  "BA_ERR_CODE_OPERATIONAL_PROBLEM",
  "BA_ERR_CODE_PASSWORD_FAILURE",
  "BA_ERR_CODE_READ_ACCESS_DENIED",
  "BA_ERR_CODE_SECURITY_NOT_SUPPORTED",
  "BA_ERR_CODE_SERVICE_REQUEST_DENIED",
  "BA_ERR_CODE_TIMEOUT",
  "BA_ERR_CODE_UNKNOWN_OBJECT",
  "BA_ERR_CODE_UNKNOWN_PROPERTY",
  "BA_ERR_CODE_UNKNOWN_VT_CLASS",
  "BA_ERR_CODE_UNKNOWN_VT_SESSION",
  "BA_ERR_CODE_UNSUPPORTED_OBJ_TYPE",
  "BA_ERR_CODE_VALUE_OUT_OF_RANGE",
  "BA_ERR_CODE_VT_SESSION_CLOSED",
  "BA_ERR_CODE_VT_SESSION_TERM_FAILED",
  "BA_ERR_CODE_WRITE_ACCESS_DENIED",
  "BA_ERR_CODE_CHAR_SET_NOT_SUPPORTED",
  "BA_ERR_CODE_INVALID_ARRAY_INDEX",
  "BA_ERR_CODE_COV_SUBS_FAILED",
  "BA_ERR_CODE_NOT_COV_PROPERTY",
  "BA_ERR_CODE_OPTIONAL_FUNC_NOT_SUPP",
  "BA_ERR_CODE_INVALID_CONFIG_DATA",
  "BA_ERR_CODE_DATATYPE_NOT_SUPPORTED",
  "BA_ERR_CODE_DUPLICATE_NAME",
  "BA_ERR_CODE_DUPLICATE_OBJECT_ID",
  "BA_ERR_CODE_PROPERTY_IS_NOT_AN_ARRAY",
  "BA_ERR_CODE_VALUE_NOT_INITIALIZED",
  "BA_ERR_CODE_INVALID_EVENT_STATE",
  "BA_ERR_CODE_NO_ALARM_CONFIGURED",
  "BA_ERR_CODE_LOG_BUFFER_FULL",
  "BA_ERR_CODE_LIST_ELEMENT_NOT_FOUND",
  "BA_ERR_CODE_LAST_KNOWN",
  "BA_ERR_CODE_ASHRAE_MAX",
  "BA_ERR_CODE_FIRST_PROPRIETARY",
  "BA_ERR_CODE_MAX"
};
const std::map<int, const char*> _BA_ERROR_CODE_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(61, _kBA_ERROR_CODEValues, _kBA_ERROR_CODENames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

const char* UserException::ascii_fingerprint = "24652790C81ECE22B629CB60A19F1E93";
const uint8_t UserException::binary_fingerprint[16] = {0x24,0x65,0x27,0x90,0xC8,0x1E,0xCE,0x22,0xB6,0x29,0xCB,0x60,0xA1,0x9F,0x1E,0x93};

uint32_t UserException::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_errorCode = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast0;
          xfer += iprot->readI32(ecast0);
          this->errorCode = (ErrorCode::type)ecast0;
          isset_errorCode = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->parameter);
          this->__isset.parameter = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_errorCode)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t UserException::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("UserException");

  xfer += oprot->writeFieldBegin("errorCode", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->errorCode);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.parameter) {
    xfer += oprot->writeFieldBegin("parameter", ::apache::thrift::protocol::T_STRING, 2);
    xfer += oprot->writeString(this->parameter);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(UserException &a, UserException &b) {
  using ::std::swap;
  swap(a.errorCode, b.errorCode);
  swap(a.parameter, b.parameter);
  swap(a.__isset, b.__isset);
}

const char* SystemException::ascii_fingerprint = "24652790C81ECE22B629CB60A19F1E93";
const uint8_t SystemException::binary_fingerprint[16] = {0x24,0x65,0x27,0x90,0xC8,0x1E,0xCE,0x22,0xB6,0x29,0xCB,0x60,0xA1,0x9F,0x1E,0x93};

uint32_t SystemException::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_errorCode = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast1;
          xfer += iprot->readI32(ecast1);
          this->errorCode = (ErrorCode::type)ecast1;
          isset_errorCode = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->message);
          this->__isset.message = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_errorCode)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t SystemException::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("SystemException");

  xfer += oprot->writeFieldBegin("errorCode", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->errorCode);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.message) {
    xfer += oprot->writeFieldBegin("message", ::apache::thrift::protocol::T_STRING, 2);
    xfer += oprot->writeString(this->message);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(SystemException &a, SystemException &b) {
  using ::std::swap;
  swap(a.errorCode, b.errorCode);
  swap(a.message, b.message);
  swap(a.__isset, b.__isset);
}

const char* NotFoundException::ascii_fingerprint = "D0297FC5011701BD87898CC36146A565";
const uint8_t NotFoundException::binary_fingerprint[16] = {0xD0,0x29,0x7F,0xC5,0x01,0x17,0x01,0xBD,0x87,0x89,0x8C,0xC3,0x61,0x46,0xA5,0x65};

uint32_t NotFoundException::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->identifier);
          this->__isset.identifier = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->key);
          this->__isset.key = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t NotFoundException::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("NotFoundException");

  if (this->__isset.identifier) {
    xfer += oprot->writeFieldBegin("identifier", ::apache::thrift::protocol::T_STRING, 1);
    xfer += oprot->writeString(this->identifier);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.key) {
    xfer += oprot->writeFieldBegin("key", ::apache::thrift::protocol::T_STRING, 2);
    xfer += oprot->writeString(this->key);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(NotFoundException &a, NotFoundException &b) {
  using ::std::swap;
  swap(a.identifier, b.identifier);
  swap(a.key, b.key);
  swap(a.__isset, b.__isset);
}

const char* BaException::ascii_fingerprint = "E6FEF1319ECC0005D2B15155790AA97B";
const uint8_t BaException::binary_fingerprint[16] = {0xE6,0xFE,0xF1,0x31,0x9E,0xCC,0x00,0x05,0xD2,0xB1,0x51,0x55,0x79,0x0A,0xA9,0x7B};

uint32_t BaException::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->message);
          this->__isset.message = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->obj_id.read(iprot);
          this->__isset.obj_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t BaException::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("BaException");

  xfer += oprot->writeFieldBegin("message", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->message);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("obj_id", ::apache::thrift::protocol::T_STRUCT, 2);
  xfer += this->obj_id.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(BaException &a, BaException &b) {
  using ::std::swap;
  swap(a.message, b.message);
  swap(a.obj_id, b.obj_id);
  swap(a.__isset, b.__isset);
}

}}} // namespace