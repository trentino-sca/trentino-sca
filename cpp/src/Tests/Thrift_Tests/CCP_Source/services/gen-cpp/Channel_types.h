/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Channel_TYPES_H
#define Channel_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include "Types_types.h"
#include "Errors_types.h"


namespace siemens { namespace bt { namespace channel {

struct Channel_Label {
  enum type {
    CHANNEL_IO_LABEL = 1,
    CHANNEL_PL_LABEL = 2,
    CHANNEL_DALI_LABEL = 3,
    CHANNEL_ANYORDUMMY_VALUE = 65535
  };
};

extern const std::map<int, const char*> _Channel_Label_VALUES_TO_NAMES;

typedef struct _BusStatus__isset {
  _BusStatus__isset() : code(false), text(false), rank(false) {}
  bool code;
  bool text;
  bool rank;
} _BusStatus__isset;

class BusStatus {
 public:

  static const char* ascii_fingerprint; // = "4F4AB97912D4FF290CDFBAAE221A7AAB";
  static const uint8_t binary_fingerprint[16]; // = {0x4F,0x4A,0xB9,0x79,0x12,0xD4,0xFF,0x29,0x0C,0xDF,0xBA,0xAE,0x22,0x1A,0x7A,0xAB};

  BusStatus() : code(0), text(), rank(0) {
  }

  virtual ~BusStatus() throw() {}

  int16_t code;
  std::string text;
  int16_t rank;

  _BusStatus__isset __isset;

  void __set_code(const int16_t val) {
    code = val;
  }

  void __set_text(const std::string& val) {
    text = val;
  }

  void __set_rank(const int16_t val) {
    rank = val;
  }

  bool operator == (const BusStatus & rhs) const
  {
    if (!(code == rhs.code))
      return false;
    if (!(text == rhs.text))
      return false;
    if (!(rank == rhs.rank))
      return false;
    return true;
  }
  bool operator != (const BusStatus &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const BusStatus & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(BusStatus &a, BusStatus &b);

typedef struct _Device__isset {
  _Device__isset() : key(false), crc(false), address(false), dl(false), type(false), type_online(false), name(false), description(false), serial_number(false), online(false), state_text(false), state(false), queue(false), version(false) {}
  bool key;
  bool crc;
  bool address;
  bool dl;
  bool type;
  bool type_online;
  bool name;
  bool description;
  bool serial_number;
  bool online;
  bool state_text;
  bool state;
  bool queue;
  bool version;
} _Device__isset;

class Device {
 public:

  static const char* ascii_fingerprint; // = "E21DEE4E137AE90F99019F2B7D0DB15E";
  static const uint8_t binary_fingerprint[16]; // = {0xE2,0x1D,0xEE,0x4E,0x13,0x7A,0xE9,0x0F,0x99,0x01,0x9F,0x2B,0x7D,0x0D,0xB1,0x5E};

  Device() : key(0), crc(0), address(), dl(0), type(), type_online(), name(), description(), serial_number(), online(0), state_text(), state(0), queue(0), version() {
  }

  virtual ~Device() throw() {}

  int32_t key;
  int32_t crc;
  std::string address;
  int32_t dl;
  std::string type;
  std::string type_online;
  std::string name;
  std::string description;
  std::string serial_number;
  int32_t online;
  std::string state_text;
  int32_t state;
  int32_t queue;
  std::string version;

  _Device__isset __isset;

  void __set_key(const int32_t val) {
    key = val;
  }

  void __set_crc(const int32_t val) {
    crc = val;
  }

  void __set_address(const std::string& val) {
    address = val;
  }

  void __set_dl(const int32_t val) {
    dl = val;
  }

  void __set_type(const std::string& val) {
    type = val;
  }

  void __set_type_online(const std::string& val) {
    type_online = val;
  }

  void __set_name(const std::string& val) {
    name = val;
  }

  void __set_description(const std::string& val) {
    description = val;
  }

  void __set_serial_number(const std::string& val) {
    serial_number = val;
  }

  void __set_online(const int32_t val) {
    online = val;
  }

  void __set_state_text(const std::string& val) {
    state_text = val;
  }

  void __set_state(const int32_t val) {
    state = val;
  }

  void __set_queue(const int32_t val) {
    queue = val;
  }

  void __set_version(const std::string& val) {
    version = val;
  }

  bool operator == (const Device & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(crc == rhs.crc))
      return false;
    if (!(address == rhs.address))
      return false;
    if (!(dl == rhs.dl))
      return false;
    if (!(type == rhs.type))
      return false;
    if (!(type_online == rhs.type_online))
      return false;
    if (!(name == rhs.name))
      return false;
    if (!(description == rhs.description))
      return false;
    if (!(serial_number == rhs.serial_number))
      return false;
    if (!(online == rhs.online))
      return false;
    if (!(state_text == rhs.state_text))
      return false;
    if (!(state == rhs.state))
      return false;
    if (!(queue == rhs.queue))
      return false;
    if (!(version == rhs.version))
      return false;
    return true;
  }
  bool operator != (const Device &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Device & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(Device &a, Device &b);

typedef struct _PointTest__isset {
  _PointTest__isset() : key(false), crc(false), address(false), value(false), unit(false), reliability(false), name(false), description(false), state(false), comment(false), read_only(false), overwrite(true), flags(false), dl(false), device(false), present_prio(false) {}
  bool key;
  bool crc;
  bool address;
  bool value;
  bool unit;
  bool reliability;
  bool name;
  bool description;
  bool state;
  bool comment;
  bool read_only;
  bool overwrite;
  bool flags;
  bool dl;
  bool device;
  bool present_prio;
} _PointTest__isset;

class PointTest {
 public:

  static const char* ascii_fingerprint; // = "A364F6C3D7F5B145D26D9B314FBF550C";
  static const uint8_t binary_fingerprint[16]; // = {0xA3,0x64,0xF6,0xC3,0xD7,0xF5,0xB1,0x45,0xD2,0x6D,0x9B,0x31,0x4F,0xBF,0x55,0x0C};

  PointTest() : key(0), crc(0), address(), value(), unit(0), reliability(0), name(), description(), state(0), comment(), read_only(0), overwrite(false), dl(0), present_prio(0) {
  }

  virtual ~PointTest() throw() {}

  int32_t key;
  int32_t crc;
  std::string address;
  std::string value;
  int32_t unit;
  int32_t reliability;
  std::string name;
  std::string description;
  int32_t state;
  std::string comment;
  bool read_only;
  bool overwrite;
  std::vector<int8_t>  flags;
  int32_t dl;
  Device device;
  int32_t present_prio;

  _PointTest__isset __isset;

  void __set_key(const int32_t val) {
    key = val;
  }

  void __set_crc(const int32_t val) {
    crc = val;
  }

  void __set_address(const std::string& val) {
    address = val;
  }

  void __set_value(const std::string& val) {
    value = val;
  }

  void __set_unit(const int32_t val) {
    unit = val;
  }

  void __set_reliability(const int32_t val) {
    reliability = val;
  }

  void __set_name(const std::string& val) {
    name = val;
  }

  void __set_description(const std::string& val) {
    description = val;
  }

  void __set_state(const int32_t val) {
    state = val;
  }

  void __set_comment(const std::string& val) {
    comment = val;
  }

  void __set_read_only(const bool val) {
    read_only = val;
  }

  void __set_overwrite(const bool val) {
    overwrite = val;
  }

  void __set_flags(const std::vector<int8_t> & val) {
    flags = val;
  }

  void __set_dl(const int32_t val) {
    dl = val;
  }

  void __set_device(const Device& val) {
    device = val;
  }

  void __set_present_prio(const int32_t val) {
    present_prio = val;
  }

  bool operator == (const PointTest & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(crc == rhs.crc))
      return false;
    if (!(address == rhs.address))
      return false;
    if (!(value == rhs.value))
      return false;
    if (!(unit == rhs.unit))
      return false;
    if (!(reliability == rhs.reliability))
      return false;
    if (!(name == rhs.name))
      return false;
    if (!(description == rhs.description))
      return false;
    if (!(state == rhs.state))
      return false;
    if (!(comment == rhs.comment))
      return false;
    if (!(read_only == rhs.read_only))
      return false;
    if (!(overwrite == rhs.overwrite))
      return false;
    if (!(flags == rhs.flags))
      return false;
    if (!(dl == rhs.dl))
      return false;
    if (!(device == rhs.device))
      return false;
    if (!(present_prio == rhs.present_prio))
      return false;
    return true;
  }
  bool operator != (const PointTest &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PointTest & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(PointTest &a, PointTest &b);

typedef struct _OverviewData__isset {
  _OverviewData__isset() : crc(false), status(false), connectedDevs(false), configuredDevs(false), reliability(false), overwrite(true) {}
  bool crc;
  bool status;
  bool connectedDevs;
  bool configuredDevs;
  bool reliability;
  bool overwrite;
} _OverviewData__isset;

class OverviewData {
 public:

  static const char* ascii_fingerprint; // = "F07EF730219CCA2F15892D0A79149BFE";
  static const uint8_t binary_fingerprint[16]; // = {0xF0,0x7E,0xF7,0x30,0x21,0x9C,0xCA,0x2F,0x15,0x89,0x2D,0x0A,0x79,0x14,0x9B,0xFE};

  OverviewData() : crc(0), connectedDevs(0), configuredDevs(0), overwrite(false) {
  }

  virtual ~OverviewData() throw() {}

  int32_t crc;
  BusStatus status;
  int32_t connectedDevs;
  int32_t configuredDevs;
  BusStatus reliability;
  bool overwrite;

  _OverviewData__isset __isset;

  void __set_crc(const int32_t val) {
    crc = val;
  }

  void __set_status(const BusStatus& val) {
    status = val;
    __isset.status = true;
  }

  void __set_connectedDevs(const int32_t val) {
    connectedDevs = val;
    __isset.connectedDevs = true;
  }

  void __set_configuredDevs(const int32_t val) {
    configuredDevs = val;
    __isset.configuredDevs = true;
  }

  void __set_reliability(const BusStatus& val) {
    reliability = val;
    __isset.reliability = true;
  }

  void __set_overwrite(const bool val) {
    overwrite = val;
    __isset.overwrite = true;
  }

  bool operator == (const OverviewData & rhs) const
  {
    if (!(crc == rhs.crc))
      return false;
    if (__isset.status != rhs.__isset.status)
      return false;
    else if (__isset.status && !(status == rhs.status))
      return false;
    if (__isset.connectedDevs != rhs.__isset.connectedDevs)
      return false;
    else if (__isset.connectedDevs && !(connectedDevs == rhs.connectedDevs))
      return false;
    if (__isset.configuredDevs != rhs.__isset.configuredDevs)
      return false;
    else if (__isset.configuredDevs && !(configuredDevs == rhs.configuredDevs))
      return false;
    if (__isset.reliability != rhs.__isset.reliability)
      return false;
    else if (__isset.reliability && !(reliability == rhs.reliability))
      return false;
    if (__isset.overwrite != rhs.__isset.overwrite)
      return false;
    else if (__isset.overwrite && !(overwrite == rhs.overwrite))
      return false;
    return true;
  }
  bool operator != (const OverviewData &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const OverviewData & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(OverviewData &a, OverviewData &b);

typedef struct _Orphan__isset {
  _Orphan__isset() : orph(false), na(false), ddt(false) {}
  bool orph;
  bool na;
  bool ddt;
} _Orphan__isset;

class Orphan {
 public:

  static const char* ascii_fingerprint; // = "3368C2F81F2FEF71F11EDACDB2A3ECEF";
  static const uint8_t binary_fingerprint[16]; // = {0x33,0x68,0xC2,0xF8,0x1F,0x2F,0xEF,0x71,0xF1,0x1E,0xDA,0xCD,0xB2,0xA3,0xEC,0xEF};

  Orphan() : orph(0), na(), ddt() {
  }

  virtual ~Orphan() throw() {}

  int32_t orph;
  std::string na;
  std::string ddt;

  _Orphan__isset __isset;

  void __set_orph(const int32_t val) {
    orph = val;
  }

  void __set_na(const std::string& val) {
    na = val;
  }

  void __set_ddt(const std::string& val) {
    ddt = val;
  }

  bool operator == (const Orphan & rhs) const
  {
    if (!(orph == rhs.orph))
      return false;
    if (!(na == rhs.na))
      return false;
    if (!(ddt == rhs.ddt))
      return false;
    return true;
  }
  bool operator != (const Orphan &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Orphan & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(Orphan &a, Orphan &b);

typedef struct _BusData__isset {
  _BusData__isset() : available(false), overview(false), devices(false), tests(false), orphans(false) {}
  bool available;
  bool overview;
  bool devices;
  bool tests;
  bool orphans;
} _BusData__isset;

class BusData {
 public:

  static const char* ascii_fingerprint; // = "AABA4E4D9A6E0E64C53BD1FBD4247F6F";
  static const uint8_t binary_fingerprint[16]; // = {0xAA,0xBA,0x4E,0x4D,0x9A,0x6E,0x0E,0x64,0xC5,0x3B,0xD1,0xFB,0xD4,0x24,0x7F,0x6F};

  BusData() : available(0) {
  }

  virtual ~BusData() throw() {}

  bool available;
  OverviewData overview;
  std::map<int32_t, Device>  devices;
  std::map<int32_t, PointTest>  tests;
  std::vector<Orphan>  orphans;

  _BusData__isset __isset;

  void __set_available(const bool val) {
    available = val;
  }

  void __set_overview(const OverviewData& val) {
    overview = val;
    __isset.overview = true;
  }

  void __set_devices(const std::map<int32_t, Device> & val) {
    devices = val;
    __isset.devices = true;
  }

  void __set_tests(const std::map<int32_t, PointTest> & val) {
    tests = val;
    __isset.tests = true;
  }

  void __set_orphans(const std::vector<Orphan> & val) {
    orphans = val;
    __isset.orphans = true;
  }

  bool operator == (const BusData & rhs) const
  {
    if (!(available == rhs.available))
      return false;
    if (__isset.overview != rhs.__isset.overview)
      return false;
    else if (__isset.overview && !(overview == rhs.overview))
      return false;
    if (__isset.devices != rhs.__isset.devices)
      return false;
    else if (__isset.devices && !(devices == rhs.devices))
      return false;
    if (__isset.tests != rhs.__isset.tests)
      return false;
    else if (__isset.tests && !(tests == rhs.tests))
      return false;
    if (__isset.orphans != rhs.__isset.orphans)
      return false;
    else if (__isset.orphans && !(orphans == rhs.orphans))
      return false;
    return true;
  }
  bool operator != (const BusData &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const BusData & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(BusData &a, BusData &b);


class DeviceCmdException : public ::apache::thrift::TException {
 public:

  static const char* ascii_fingerprint; // = "3F5FC93B338687BC7235B1AB103F47B3";
  static const uint8_t binary_fingerprint[16]; // = {0x3F,0x5F,0xC9,0x3B,0x33,0x86,0x87,0xBC,0x72,0x35,0xB1,0xAB,0x10,0x3F,0x47,0xB3};

  DeviceCmdException() : errorCode(0), message() {
  }

  virtual ~DeviceCmdException() throw() {}

  int32_t errorCode;
  std::string message;

  void __set_errorCode(const int32_t val) {
    errorCode = val;
  }

  void __set_message(const std::string& val) {
    message = val;
  }

  bool operator == (const DeviceCmdException & rhs) const
  {
    if (!(errorCode == rhs.errorCode))
      return false;
    if (!(message == rhs.message))
      return false;
    return true;
  }
  bool operator != (const DeviceCmdException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DeviceCmdException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(DeviceCmdException &a, DeviceCmdException &b);

}}} // namespace

#endif
