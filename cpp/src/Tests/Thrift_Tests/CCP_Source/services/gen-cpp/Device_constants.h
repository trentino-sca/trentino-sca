/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Device_CONSTANTS_H
#define Device_CONSTANTS_H

#include "Device_types.h"

namespace siemens { namespace bt { namespace device {

class DeviceConstants {
 public:
  DeviceConstants();

  std::string INTERFACE_VERSION;
  std::string DEVICE_HTTP_JSON_URI;
  std::string SOCKET_TCP_BIN;
  std::string SOCKET_HTTP_JSON;
  std::string SESSION_ID_TOKEN;
};

extern const DeviceConstants g_Device_constants;

}}} // namespace

#endif
