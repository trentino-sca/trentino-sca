/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef OAM_CONSTANTS_H
#define OAM_CONSTANTS_H

#include "OAM_types.h"

namespace siemens { namespace bt { namespace oam {

class OAMConstants {
 public:
  OAMConstants();

  std::string INTERFACE_VERSION;
  std::string OAM_HTTP_JSON_URI;
  std::string SOCKET_TCP_BIN;
  std::string SOCKET_HTTP_JSON;
};

extern const OAMConstants g_OAM_constants;

}}} // namespace

#endif