#--------------------------------------------------------------------------
# (C) Copyright Siemens Building Technologies
#--------------------------------------------------------------------------
#  Project             :  Systen ONE
#  Author              :  Bob Kalafut <bob.kalafut@siemens.com>
#  Date of creation    :  2010-03-18
#  Workfile            :  CSML.thrift
#--------------------------------------------------------------------------
#  Description:
#    a simple service providing basic data of a device
#    e.g. used web interface or a snmpd reads its basic configuration
#
# TODO:
# - review namespaces
# - 
#
#--------------------------------------------------------------------------



namespace java com.siemens.bt.csml
namespace cpp siemens.bt.csml
namespace csharp Siemens.BT.csml
namespace py siemens.bt.csml

include "Types.thrift"
include "Errors.thrift"


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
const string INTERFACE_VERSION = "0.1.0"

const string DEVICE_HTTP_JSON_URI = "/api/thrift/cmsl.json"

const string SOCKET_TCP_BIN = "/tmp/t_cmsl_tcpbin.socket"
const string SOCKET_HTTP_JSON = "/tmp/t_cmsl_httpjs.socket"



/**
 * Standard Device Service
 */
service CSMLService {

  /**
   * Returns the version of the service
   */
  string getInterfaceVersion(),
  
  /**
   * Returns the model type of the device
   */
  string CSMLRequest(1:string p_Request)

}
