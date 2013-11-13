#--------------------------------------------------------------------------
# (C) Copyright Siemens Building Technologies
#--------------------------------------------------------------------------
#  Project             :  Systen ONE
#  Author              :  Roger Meier <r.meier@siemens.com>
#  Date of creation    :  2010-03-18
#  Workfile            :  Device.thrift
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



namespace java com.siemens.bt.device
namespace cpp siemens.bt.device
namespace csharp Siemens.BT.device
namespace py siemens.bt.device

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
const string INTERFACE_VERSION = "1.15.1"

const string DEVICE_HTTP_JSON_URI   = "/api/thrift/device.json"

const string SOCKET_TCP_BIN = "/tmp/t_device_tcpbin.socket"
const string SOCKET_HTTP_JSON = "/tmp/t_device_httpjs.socket"

const string SESSION_ID_TOKEN  = "SessionId"




/**
 * Whole device data, used by client observers (client/server synchronization)
 */
struct Data
{
  1: optional Types.ControlProgramState s7State,
  2: optional map<Types.Property_Type, string> baProperties,
  3: optional map<Channel.Channel_Label, Channel.BusData> bus,
}



/**
 * Standard Device Service
 */
service DeviceService {

  /**
   * Returns the version of the service
   */
  string getInterfaceVersion(),


  /**
   * Start/Stop/Reset S7 Application
   */
  bool setControlProgramState(1: string authenticationToken, 2: Types.ControlProgramState ctrlState)
    throws (1: Errors.BaException baException),


  /**
   * Get S7 Application Status
   */
  Types.ControlProgramState getControlProgramState(1: string authenticationToken)
    throws (1: Errors.BaException baException),


  /**
   * Returns the ASN of the device
   */
  string getASN(1: string authenticationToken),


  /**
   * Authenticate a sessionId or a token (e.g. "SessionId=2246923a-4a24-40e3-b132-601d13ba6ff6")
   * user authorization is not checked
   */
  Types.AuthenticationResult authenticate(1: string authenticationToken)
    throws (1: Errors.UserException userException,
            2: Errors.SystemException systemException),


  /**
   * Check authorization of a user
   */
  Types.AuthenticationResult authorize(1: string authenticationToken)
    throws (1: Errors.UserException userException,
            2: Errors.SystemException systemException),


  /**
   * Authenticate a user with username and password (md5 hash)
   */
   //@TODO refactor to use plain text Password or an intermediate hash
  Types.AuthenticationResult authenticateUser(3: string formerToken, //numbering keeps back compatibility
                                              1: string username,
                                              2: string passwordHash)
    throws (1: Errors.UserException userException,
            2: Errors.SystemException systemException),


  /**
  * Update user profile
  **/
  void updateUserProfile(1: string authenticationToken,
                         2: Types.User user)
    throws (1: Errors.UserException userException),


  /**
   * change user password
   */
  bool changePassword(1: string authenticationToken, 2: string passwordMd5Hash),


  /**
   * Remove User from session, this session can still be authenticated but not authorized in any user required applications
   */
  Types.AuthenticationResult logoutUser(1: string authenticationToken)
    throws (1: Errors.UserException userException,
            2: Errors.SystemException systemException),


  /**
   * Update session time-stamp to prevent timeout
   */
  oneway void updateSession(1: string authenticationToken),


  /**
   * DICP Authentication
   * check if dicpAuthToken is valid (md5 hash)
   */
  bool Authenticated(1: string dicpAuthToken),


  /**
   * Returns a descriptive name of the service
   */
  string getName(1: string authenticationToken),


  /**
   * Gets the local BA device instance number
   */
  i32 getLocalDeviceInst(),


  /**
   * Gets Firmware Revision
   */
  string getFirmwareRevision(),


   /**
   * Create a restore point backup of /opt/sysone/s1pdata/s1conf directories
   */
  void createRestorePoint(1: string authenticationToken, 2: bool logoutUser),


  /**
   * Update the whole device data (long polling process)
   * Data set on client side is compared against the server data and only the difference is sent back
   *
   * Long polling: returns only if there is a difference, or after timeout (<15min)
   *  Client data: empty objects with a key are enough to trigger updates;
   *               matching CRCs avoid the update: no need to send the whole object back to the server.
   */
  Data updateData(1: string authenticationToken, 2: Data clientData)
    throws (1: Channel.DeviceCmdException cmdException,
            2: Errors.UserException userException,
            3: Errors.SystemException systemException),


  /**
   * set device state
   */
  bool setDeviceState(1: string authenticationToken, 2: Types.DeviceState state)


  /**
   * restart the system
   */
  oneway void restartDevice(1: string authenticationToken, 2: bool createRestorePoint = 1, 3: bool logoutUser = 1)

}
