#--------------------------------------------------------------------------
# (C) Copyright Siemens Building Technologies
#--------------------------------------------------------------------------
#  Project             :  Systen ONE
#  Author              :  Wiles Mutira <wiles.mutira@siemens.com>
#  Date of creation    :  2011-07-22
#  Workfile            :  ConfigureAndLoad.thrift
#--------------------------------------------------------------------------
#  Description:
#    This service provide interfaces for configure and load functionalities
#    e.g. used web interface for device configuration or load configuration files
#
#
#--------------------------------------------------------------------------



namespace java com.siemens.bt.configureandload
namespace cpp siemens.bt.configureandload
namespace csharp Siemens.BT.configureandload
namespace py siemens.bt.configureandload

include "Types.thrift"
include "Errors.thrift"
include "DICP.thrift"

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

const string INTERFACE_VERSION = "0.2.1"

const string CONFIGUREANDLOAD_HTTP_JSON_URI   = "/api/thrift/configureandload.json"

const string SOCKET_TCP_BIN = "/tmp/t_configureandload_tcpbin.socket"
const string SOCKET_HTTP_JSON = "/tmp/t_configureandload_httpjs.socket"


struct DeviceConfigParameter
{
  1: optional DICP.DevIdent  devIdent,
  2: optional DICP.BaDevData baDevData,
  3: optional DICP.URIData uriData,
  4: optional DICP.DevInfo devInfo
}

struct ConfigureData
{
  1: DICP.BaDev     baDev,
  2: DICP.BaPar     baPar,
  3: DICP.BaNw      baNw,
  4: list<DICP.BaPort>  baPort,
  5: list<DICP.NwItf>   nwItf,
  6: DeviceConfigParameter devPar,
  7: i64 utcTime,
  8: DICP.TimeSet tz
}

/**
 * Standard ConfigureAndLoad Service
 */
service ConfigureAndLoadService {

  /**
   * Returns the version of the service
   */
  string getInterfaceVersion(),

  /**
  * read Node Setup Data
  **/
  ConfigureData readConfiguration(1: string authenticationToken),
  /**
  
  /**
  * write Node Setup Data
  **/
  void writeConfiguration(1: string authenticationToken, 2: ConfigureData config),
  /**

  /**
  * set Network Configuration Data via DICP
  **/
  void setNwConfig(1: string authenticationToken, 2: list<DICP.NwItf>  nwItf),

  /**
  * get Network Configuration Data from DICP
  **/
  list<DICP.NwItf> getNwConfig(1: string authenticationToken),

  /**
  * set bacnet device and apdu configuration
  **/
  void setBaDevConfig(1: string authenticationToken, 2: DICP.BaDev dev, 3: DICP.BaPar apdu),

  /**
  * get bacnet device configuration
  **/
  DICP.BaDev getBaDevConfig(1: string authenticationToken),

  /**
  * get bacnet parameter configuration
  **/
  DICP.BaPar getBaParConfig(1: string authenticationToken),

  /**
  * set bacnet network configuration
  **/
  void setBaNwConfig(1: string authenticationToken, 2: DICP.BaNw network, 3: list<DICP.BaPort> ports),

  /**
  * get bacnet network configuration
  **/
  DICP.BaNw getBaNwConfig(1: string authenticationToken),

  /**
  * get bacnet port configuration
  **/
  list<DICP.BaPort> getBaPortConfig(1: string authenticationToken),

  /**
  * set time as utc time
  **/
  void setUTCTime(1: string authenticationToken, 2: i64  utctime),

  /**
  * get time as utc time
  **/
  i64 getUTCTime(1: string authenticationToken),

  /**
   * process a new Pack & Go file located at path
   */
  bool processPackAndGo(1: string authenticationToken, 2: string path),

  /**
   * get status of packandgo processing
   */
   i32 getPackAndGoStatus(1: string authenticationToken),

  /**
   * create a new device backup file located at path
   */
  bool createBackup(1: string authenticationToken, 2: string path) throws (1: Errors.UserException userException),

  /**
   * get status of backup creation
   */
   i32 getBackupStatus(1: string authenticationToken) throws (1: Errors.UserException userException),

  /**
   * activate configuration data
  */
  void activateConfigData(1: string authenticationToken, 2: bool activate),

  /**
   * set device info
  */
  void setDeviceConfigParameter(1: string authenticationToken, 2: DeviceConfigParameter devConfig),
  
  /**
   * get device info
  */
  DeviceConfigParameter getDeviceConfigParameter(1: string authenticationToken),
  
  /**
   * set timezone
  */
  void setTimeZone(1: string authenticationToken, 2: DICP.TimeSet tz),
  
  /**
   * get timezone
  */
  DICP.TimeSet getTimeZone(1: string authenticationToken),
  
  /**
   * add ip port
  */
  DICP.IPport addIPPort(1: string authenticationToken, 2: DICP.Lan lanNwItf),
  
  /**
   * add lon port
  */
  DICP.LONport addLONPort(1: string authenticationToken, 2: DICP.Eia709 eia709NwItf),
  
  /**
   * add mstp port
  */
  DICP.MSTPport addMSTPPort(1: string authenticationToken, 2: DICP.Rs485 rs485NwItf),
  
  /**
   * add Lan network interface
  */
  DICP.Lan addLanItf(1: string authenticationToken),
  
  /**
   * add Eia709 network interface
  */
  DICP.Eia709 addEia709Itf(1: string authenticationToken),
  
  /**
   * add Rs485 network interface
  */
  DICP.Rs485 addRs485Itf(1: string authenticationToken),
  
  /**
   * check if mstp supported
  */
  i32 IsMSTPSupported(1: string authenticationToken),
  
  /**
   * check if lon supported
  */
  i32 IsLONSupported(1: string authenticationToken),
  
  /**
   * check ssh daemon state
  */
  bool getStateSSH(1: string authenticationToken),
  
  /**
   * start ssh daemon
  */
  bool startSSH(1: string authenticationToken),
  
  /**
   * stop ssh daemon
  */
  bool stopSSH(1: string authenticationToken),
}

