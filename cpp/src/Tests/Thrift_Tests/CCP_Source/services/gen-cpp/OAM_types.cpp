/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "OAM_types.h"

#include <algorithm>

namespace siemens { namespace bt { namespace oam {

const char* ImageResult::ascii_fingerprint = "19B5240589E680301A7E32DF3971EFBE";
const uint8_t ImageResult::binary_fingerprint[16] = {0x19,0xB5,0x24,0x05,0x89,0xE6,0x80,0x30,0x1A,0x7E,0x32,0xDF,0x39,0x71,0xEF,0xBE};

uint32_t ImageResult::read(::apache::thrift::protocol::TProtocol* iprot) {

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
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast0;
          xfer += iprot->readI32(ecast0);
          this->resultCode = ( ::siemens::bt::type::Result_Code::type)ecast0;
          this->__isset.resultCode = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->mimeType);
          this->__isset.mimeType = true;
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

uint32_t ImageResult::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("ImageResult");

  xfer += oprot->writeFieldBegin("resultCode", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->resultCode);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("mimeType", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->mimeType);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ImageResult &a, ImageResult &b) {
  using ::std::swap;
  swap(a.resultCode, b.resultCode);
  swap(a.mimeType, b.mimeType);
  swap(a.__isset, b.__isset);
}

}}} // namespace
