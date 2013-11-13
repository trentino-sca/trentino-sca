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



namespace java com.siemens.bt.ba
namespace cpp siemens.bt.ba
namespace csharp Siemens.BT.BA
namespace py siemens.bt.ba


include "Types.thrift"
include "Errors.thrift"


# The API version (NOT the product version), composed as a dot delimited
# string with major, minor, and patch level components.
#
# - Major: Incremented for backward incompatible changes. An example would
#           be changes to the number or disposition of method arguments.
# - Minor: Incremented for backward compatible changes. An example would
#           be the addition of a new (optional) method.
# - Patch: Incremented for bug fixes. The patch level should be increased
#           for every edit that doesn't result in a change to major/minor.
#
# See the Semantic Versioning Specification (SemVer) http://semver.org.
const string INTERFACE_VERSION = "0.27.3"

const string BA_HTTP_JSON_URI = "/api/thrift/ba.json"

const string SOCKET_TCP_BIN = "/tmp/t_ba_tcpbin.socket"
const string SOCKET_HTTP_JSON = "/tmp/t_ba_httpjs.socket"


//TODO: move it to channel.thrift

/**
 * BA Service
 */
service BaService {

  /**
   * Returns the version of the service
   */
  string getInterfaceVersion(),

  /**
   * Gets the local BA device instance number
   */
  Types.Object_Id getLocalDeviceInst(),

  string readPropertyString(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type),
  string readPropertyStringArray(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type, 4: i32 array_index),
  list<string> readPropertyStringList(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type),

  double readPropertyReal(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type),
  double readPropertyRealArray(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type, 4: i32 array_index),

  i32 readPropertyInt(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type),
  i32 readPropertyIntArray(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type, 4: i32 array_index),

  string writePropertyString(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type, 4: string value)
    throws (1: Errors.BaException baException),

  double writePropertyReal(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type, 4: double value)
    throws (1: Errors.BaException baException),

  i32 writePropertyInt(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type, 4: i32 value)
    throws (1: Errors.BaException baException),

  list<Types.Object_Id> readObjectList(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type),

  bool releasePresentValue(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Write_Priority writePriority),

  /**
   * Use getPropertyDescription to get a string representation of the property value
   */
  string readProperty(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type)
    throws (1: Errors.BaException baException),
    
  /**
   * Use getPropertyDescription to get a string representation of the property value
   */
  string writeProperty(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type, 4: string value)
    throws (1: Errors.BaException baException),

  /**
   * Read a property description from the BA meta-data
   */
  Types.Property_Info getPropertyDescription(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type),

  /**
   * Get a object's property list from the BA meta-data
   */
  list<Types.Property_Type> getProperties(1: string authToken, 2: Types.Object_Id object_id),

 
  /**
   * Get a property's unit of measurement, if available
   */

  string getPropertyUnit(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type),
  
   /**
   * Get a object's property list and its description
   **/
  
  /*map<Types.Property_Type, Types.Property_Info> getPropertiesWithDescription(1: string authToken, 2: Types.Object_Id object_id), */
  
  list<Types.PropertyDesc_Info> getPropertiesWithDescription(1: string authToken, 2: Types.Object_Id object_id), 

  /**
   * Get a object's property list and its text value
   */
  map<Types.Property_Type, string> getPropertiesWithText(1: string authToken, 2: Types.Object_Id object_id),

 
  /**
   * Get a property's enumeration text, if available
   */
  map<i32, string> getPropertyEnum(1: string authToken, 2: Types.Object_Id object_id, 3: Types.Property_Type property_type),
  /**
   * Gets the Remote BA device list
   */
  list<Types.Object_Id> getRemoteDeviceList(),
}
