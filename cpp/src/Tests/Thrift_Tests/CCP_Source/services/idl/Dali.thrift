#--------------------------------------------------------------------------
# (C) Copyright Siemens Building Technologies
#--------------------------------------------------------------------------
#  Project             :  Systen ONE
#  Author              :  Roger Meier <r.meier@siemens.com>
#  Date of creation    :  2010-03-18
#  Workfile            :  Dali.thrift
#--------------------------------------------------------------------------
#  Description:
#    a simple service providing basic data of a dali
#    e.g. used web interface or a snmpd reads its basic configuration
#
# TODO:
# - review namespaces
# - 
#
#--------------------------------------------------------------------------



namespace java com.siemens.bt.dali
namespace cpp siemens.bt.dali
namespace csharp Siemens.BT.dali
namespace py siemens.bt.dali

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
const string INTERFACE_VERSION = "0.36.1"

const string DALI_HTTP_JSON_URI = "/api/thrift/dali.json"

const string SOCKET_TCP_BIN = "/tmp/t_dali_tcpbin.socket"
const string SOCKET_HTTP_JSON = "/tmp/t_dali_httpjs.socket"



/**
 * Standard Dali Service
 */
service DaliService extends Channel.ChannelService {

  /**
   * check whether FMO is busy (if device command is working)
   */
  bool isBusy(1:string authToken),

  bool lightsOn(1:string authToken) throws (1: Errors.BaException baException),
  bool lightsOff(1:string authToken) throws (1: Errors.BaException baException),
  bool lightsBlink(1:string authToken) throws (1: Errors.BaException baException),
  bool autoassignDevices(1:string authToken) throws (1: Errors.BaException baException),

  list<Channel.Orphan> getOrphans(1:string authToken) throws (1: Errors.BaException baException),
  bool blinkOrphan(1:string authToken, 2:i32 networkAddress) throws (1: Errors.BaException baException),
  bool blinkPDO(1:string authToken, 2:i32 deviceLogical) throws (1: Errors.BaException baException),

  /**
   * assign a network address to a logical device
   */
  i32 identifyDevice(1:string authToken, 2:i32 devKey, 3:i32 deviceLogical, 4:i32 networkAddress, 5:bool reset) throws (1: Errors.BaException baException),

  /**
   * reset a device assignment
   */
  Channel.Device resetDevice(1:string authToken, 2:i32 devKey) throws (1: Errors.BaException baException),

}
