#--------------------------------------------------------------------------
# (C) Copyright Siemens Building Technologies
#--------------------------------------------------------------------------
#  Project             :  Systen ONE
#  Author              :  Wiles Mutira <wiles.mutira@siemens.com>
#  Date of creation    :  2011-09-02
#  Workfile            :  Diagnostic.thrift
#--------------------------------------------------------------------------
#  Description:
#    This service provide interfaces for statistic and diagnostic
#
#
#--------------------------------------------------------------------------



namespace java com.siemens.bt.diagnostic
namespace cpp siemens.bt.diagnostic
namespace csharp Siemens.BT.diagnostic
namespace py siemens.bt.diagnostic

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

const string DIAGNOSTIC_HTTP_JSON_URI   = "/api/thrift/diagnostic.json"

const string SOCKET_TCP_BIN = "/tmp/t_diagnostic_tcpbin.socket"
const string SOCKET_HTTP_JSON = "/tmp/t_diagnostic_httpjs.socket"


/*
* facility: service or component
* timeStamp: time stamp of the message
* message: statistic message
*/
struct StatLog
{
  1: string facility,
  2: i32 timeStamp,
  3: list<string> ParamName,
  4: list<i32> ParamValue,
}

/*
* facility: service or component
* timeStamp: time stamp of the message
* severity: classification of the message
* message: statistic message
*/
struct DiagLog
{
  1: string facility,
  2: string timeStamp,
  3: string severity,
  4: list<string> message
}

/**
 * Standard diagnostic Services
 */
service DiagnosticService {

  /**
   * Returns the version of the service
   */
  string getInterfaceVersion(),
  
  /**
   * get all available facilities
   */
  list<string> getFacilities(1: string authenticationToken),
  
  /**
   * get all avaialbe severities
   */
  list<string> getSeverities(1: string authenticationToken),
  
  /**
   * Return statistics data from certain facility
   */
  list<StatLog> getStatByFacility(1: string authenticationToken, 2: string facility),
  
  /**
   * Return statistics data from all facilities
   */
  list<StatLog> getAllStatistics(1: string authenticationToken),
  
  /**
   * Return diagnostics data by facility
   */
  list<DiagLog> getDiagByFacility(1: string authenticationToken, 2: string facility),
  
  /**
   * Return diagnostics data by severity
   */
  list<DiagLog> getDiagBySeverity(1: string authenticationToken, 2: string severity),
  
  /**
   * Return diagnostics data from all facilities
   */
  list<DiagLog> getAllDiagnostics(1: string authenticationToken),
  
}
