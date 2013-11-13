#--------------------------------------------------------------------------
# (C) Copyright Siemens Building Technologies
#--------------------------------------------------------------------------
#  Project             :  Systen ONE
#  Author              :  Roger Meier <r.meier@siemens.com>
#  Date of creation    :  2010-03-18
#  Workfile            :  Pllink.thrift
#--------------------------------------------------------------------------
#  Description:
#    a simple service providing basic data of a pllink
#    e.g. used web interface or a snmpd reads its basic configuration
#
# TODO:
# - review namespaces
# - 
#
#--------------------------------------------------------------------------



namespace java com.siemens.bt.pllink
namespace cpp siemens.bt.pllink
namespace csharp Siemens.BT.pllink
namespace py siemens.bt.pllink

include "Ba.thrift"

include "Types.thrift"
include "Errors.thrift"
include "Channel.thrift"


# The API version (NOT the product version), composed as a dot delimited
# string with major, minor, and patch level components.
#
#  - Major: Incremented for backward incompatible changes. An example would
#           be changes to the number or disposition of method arguments.
#  - Minor: Incremented for backward compatible changes. An example would
#           be the addition of a new (optional) method.
#  - Patch: Incremented for bug fixes. The patch level should be increased
#           for every edit that doesn't result in a change to major/minor.
#
# See the Semantic Versioning Specification (SemVer) http://semver.org.
const string INTERFACE_VERSION = "0.36.0"

const string PLLINK_HTTP_JSON_URI = "/api/thrift/pllink.json"

const string SOCKET_TCP_BIN = "/tmp/t_pllink_tcpbin.socket"
const string SOCKET_HTTP_JSON = "/tmp/t_pllink_httpjs.socket"



/**
 * Standard Pllink Service
 */
service PllinkService extends Channel.ChannelService {

  /**
   * Channel.Device will waiting for identification (programming mode button)
   * return: position in waiting queue
   */
  i32 identifyDevice(1:string authToken, 2:i32 devKey) throws (1: Errors.BaException baException),

  /**
   * not implemented yet
   */
  Channel.Device resetDevice(1:string authToken, 2:i32 devKey) throws (1: Errors.BaException baException),

}
