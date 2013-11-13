/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "Diagnostic_types.h"

#include <algorithm>

namespace siemens { namespace bt { namespace diagnostic {

const char* StatLog::ascii_fingerprint = "8FA3A8CA1DD97FF671F3B861898C5270";
const uint8_t StatLog::binary_fingerprint[16] = {0x8F,0xA3,0xA8,0xCA,0x1D,0xD9,0x7F,0xF6,0x71,0xF3,0xB8,0x61,0x89,0x8C,0x52,0x70};

uint32_t StatLog::read(::apache::thrift::protocol::TProtocol* iprot) {

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
          xfer += iprot->readString(this->facility);
          this->__isset.facility = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->timeStamp);
          this->__isset.timeStamp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->ParamName.clear();
            uint32_t _size0;
            ::apache::thrift::protocol::TType _etype3;
            xfer += iprot->readListBegin(_etype3, _size0);
            this->ParamName.resize(_size0);
            uint32_t _i4;
            for (_i4 = 0; _i4 < _size0; ++_i4)
            {
              xfer += iprot->readString(this->ParamName[_i4]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.ParamName = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->ParamValue.clear();
            uint32_t _size5;
            ::apache::thrift::protocol::TType _etype8;
            xfer += iprot->readListBegin(_etype8, _size5);
            this->ParamValue.resize(_size5);
            uint32_t _i9;
            for (_i9 = 0; _i9 < _size5; ++_i9)
            {
              xfer += iprot->readI32(this->ParamValue[_i9]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.ParamValue = true;
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

uint32_t StatLog::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("StatLog");

  xfer += oprot->writeFieldBegin("facility", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->facility);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("timeStamp", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->timeStamp);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("ParamName", ::apache::thrift::protocol::T_LIST, 3);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->ParamName.size()));
    std::vector<std::string> ::const_iterator _iter10;
    for (_iter10 = this->ParamName.begin(); _iter10 != this->ParamName.end(); ++_iter10)
    {
      xfer += oprot->writeString((*_iter10));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("ParamValue", ::apache::thrift::protocol::T_LIST, 4);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_I32, static_cast<uint32_t>(this->ParamValue.size()));
    std::vector<int32_t> ::const_iterator _iter11;
    for (_iter11 = this->ParamValue.begin(); _iter11 != this->ParamValue.end(); ++_iter11)
    {
      xfer += oprot->writeI32((*_iter11));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(StatLog &a, StatLog &b) {
  using ::std::swap;
  swap(a.facility, b.facility);
  swap(a.timeStamp, b.timeStamp);
  swap(a.ParamName, b.ParamName);
  swap(a.ParamValue, b.ParamValue);
  swap(a.__isset, b.__isset);
}

const char* DiagLog::ascii_fingerprint = "D5082811F603CA229965DA45DAFDD5B7";
const uint8_t DiagLog::binary_fingerprint[16] = {0xD5,0x08,0x28,0x11,0xF6,0x03,0xCA,0x22,0x99,0x65,0xDA,0x45,0xDA,0xFD,0xD5,0xB7};

uint32_t DiagLog::read(::apache::thrift::protocol::TProtocol* iprot) {

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
          xfer += iprot->readString(this->facility);
          this->__isset.facility = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->timeStamp);
          this->__isset.timeStamp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->severity);
          this->__isset.severity = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->message.clear();
            uint32_t _size12;
            ::apache::thrift::protocol::TType _etype15;
            xfer += iprot->readListBegin(_etype15, _size12);
            this->message.resize(_size12);
            uint32_t _i16;
            for (_i16 = 0; _i16 < _size12; ++_i16)
            {
              xfer += iprot->readString(this->message[_i16]);
            }
            xfer += iprot->readListEnd();
          }
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

  return xfer;
}

uint32_t DiagLog::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("DiagLog");

  xfer += oprot->writeFieldBegin("facility", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->facility);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("timeStamp", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->timeStamp);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("severity", ::apache::thrift::protocol::T_STRING, 3);
  xfer += oprot->writeString(this->severity);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("message", ::apache::thrift::protocol::T_LIST, 4);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->message.size()));
    std::vector<std::string> ::const_iterator _iter17;
    for (_iter17 = this->message.begin(); _iter17 != this->message.end(); ++_iter17)
    {
      xfer += oprot->writeString((*_iter17));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(DiagLog &a, DiagLog &b) {
  using ::std::swap;
  swap(a.facility, b.facility);
  swap(a.timeStamp, b.timeStamp);
  swap(a.severity, b.severity);
  swap(a.message, b.message);
  swap(a.__isset, b.__isset);
}

}}} // namespace