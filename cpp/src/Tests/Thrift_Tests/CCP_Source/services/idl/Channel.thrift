#--------------------------------------------------------------------------
# (C) Copyright Siemens Building Technologies
#--------------------------------------------------------------------------
#  Project             :  Systen ONE
#  Author              :  Roger Meier <r.meier@siemens.com>
#  Date of creation    :  2010-03-18
#  Workfile            :  Ba.thrift
#--------------------------------------------------------------------------
#  Description:
#    this service provides access to th BA world
#
# TODO:
# - review namespaces
# - define all services and types
#
#--------------------------------------------------------------------------



namespace java com.siemens.bt.channel
namespace cpp siemens.bt.channel
namespace csharp Siemens.BT.channel
namespace py siemens.bt.channel

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
const string INTERFACE_VERSION = "0.36.0"


// Analog to SDU Definition
enum Channel_Label
{
  CHANNEL_IO_LABEL                                  = 1,     // IO
  CHANNEL_PL_LABEL                                  = 2,     // PL
  CHANNEL_DALI_LABEL                                = 3,     // DALI
  CHANNEL_ANYORDUMMY_VALUE                          = 0xFFFF // Any,dummy init. value
}


struct BusStatus {
  1:  i16 code,
  2:  string text,
  3:  i16 rank,
}


/**
 * Peripheral device object
 */
struct Device {

/** BA object Id */
  1: i32 key,

/** object's CRC16 */
  2: i32 crc,

/** bus address */
  3: string address,

/** device's logical address */
  4: i32 dl,

  5: string type,
  6: string type_online,
  7: string name,
  8: string description,
  9: string serial_number,
 10: i32 online,
 11: string state_text,
 12: i32 state,

/** identification order */
 13: i32 queue,

/** Online peripheral device firmware and hardware version */
 14: string version,
}

/**
 * IO data point object
 */
struct PointTest {

/** BA object Id */
  1: i32 key,

/** object's CRC16 */
  2: i32 crc,

/** bus address */
  3: string address,

  4: string value
  5: i32 unit,
  6: i32 reliability,
  7: string name,
  8: string description,

/** Commissioning state: set by installer: not checked, OK, Defect */
  9: i32 state,

/** additional comment to document his point test or give hints */
 10: string comment,

/** disable commands for this output (during point test) */
 11: bool read_only,

/** True if manually overridden; only for output object */
 12: bool overwrite = 0,

/** Status flags property */
 13: list<byte> flags,

/** device's logical address */
  14: i32 dl,

/** parent device */
 15: Device device,
 
/** present priority */
 16: i32 present_prio,

}

/**
 * Basic channel data and status, used by client observers (client/server synchronization)
 */
struct OverviewData
{
  1: i32 crc,
  2: optional BusStatus status,
  3: optional i32 connectedDevs,
  4: optional i32 configuredDevs,
  5: optional BusStatus reliability,

/** True if any point test is manually overridden */
  6: optional bool overwrite = 0,
}

/**
 * cASA-[T010.S040-2]-Coded-String-Syntax :: [T010-S040-2D050-023] Domain labels for Orphan-List
 */
struct Orphan
{
/** Represents (Enum-Value of) the orphan reason (e.g. ‘not assigned to engineered device’ or ‘no configuration available’). */
  1: i32 orph,
/** Identifies the orphan device by its Network Address  */
  2: string na,
/** Identifies the discovered orphan device by its Type  */
  3: string ddt,
}

/**
 * Channel data, used by client observers (client/server synchronization)
 */
struct BusData
{
  1: bool available,
  2: optional OverviewData overview,
  3: optional map<i32, Device> devices,
  4: optional map<i32, PointTest> tests,
  5: optional list<Orphan> orphans,
}


/**
 * This exception is thrown when the device identification process fails
 *
 * errorCode: SDU's CSIE_BA_DeviceCommandErrors
 * message:   error text from CS1WEB_BA_DeviceCommandErrors
 */
exception DeviceCmdException {
  1:  required  i32 errorCode,
  2:  required  string message
}



/**
 * Basic Channel Service
 */
service ChannelService {

  /**
   * Returns the version of the service
   */
  string getInterfaceVersion(),


  bool isAvailable(),
  BusStatus getBusStatus(1:string authToken) throws (1: Errors.BaException baException),
  OverviewData getBusOverview(1:string authToken) throws (1: Errors.BaException baException),
  bool reset(1:string authToken) throws (1: Errors.BaException baException),
  bool stop(1:string authToken) throws (1: Errors.BaException baException),
  bool start(1:string authToken) throws (1: Errors.BaException baException),



  /**
   * return: every peripheral device on this channel
   */
  list<Device> getDevices(1:string authToken),
  Device getDevice(1:string authToken, 2:i32 devKey)
    throws (1: Errors.BaException baException,
            2: DeviceCmdException cmdException),
  i32 countConnectedDevices(1:string authToken),
  i32 countConfiguredDevices(1:string authToken),
  BusStatus getDeviceListStatus(1:string authToken) throws (1: Errors.BaException baException),
  list<string> readOrphanList(1:string authToken) throws (1: Errors.BaException baException),



  /**
   * return: every point test on this channel
   */
  list<PointTest> getTests(1:string authToken),

  /**
   * Release all overwritten point tests
   * return: total of overwritten point tests released
   */
  i32 releaseOverwrite(1:string authToken),

  /**
   * Increment point test's value
   * return: formatted new value
   */
  string incrementValue(1:string authToken, 2:i32 key) throws (1: Errors.BaException baException),

  /**
   * Decrement point test's value
   * return: formatted new value
   */
  string decrementValue(1:string authToken, 2:i32 key) throws (1: Errors.BaException baException),

  /**
   * Set point test's value
   * return: formatted new value
   */
  string setTestValue(1:string authToken, 2:i32 key, 3:double value) throws (1: Errors.BaException baException),

  /**
   * return: formatted value of a point test
   */
  string getTestValue(1:string authToken, 2:i32 key) throws (1: Errors.BaException baException),

  /**
   * Set the commissioning state of a point test
   */
  i32 setState(1:string authToken, 2:i32 key, 3:i32 state) throws (1: Errors.BaException baException),

  /**
   * Set the commissioning comment of a point test
   */
  string setComment(1:string authToken, 2:i32 key, 3:string value) throws (1: Errors.BaException baException),
      
}