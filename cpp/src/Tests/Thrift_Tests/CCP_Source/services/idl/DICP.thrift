#--------------------------------------------------------------------------
# (C) Copyright Siemens Building Technologies
#--------------------------------------------------------------------------
#  Project             :  Systen ONE
#  Author              :  Andreas Schlumberger <andreas.schlumberger@siemens.com>
#  Date of creation    :  2010-09-27
#  Workfile            :  dicp.thrift
#--------------------------------------------------------------------------
#  Description:
#    a simple service providing services for the 
#    device identifcation and configuration protocol used for NodeSetup
#
# TODO:
# - split data structures and services in different files
#
#--------------------------------------------------------------------------
# Rev      Date        Author
# "2.4.0"  29.11.2011  Wiles Mutira
#                      Added optional mstp port parameter slave proxy enable
#---------------------------------------------------------------------------
# Rev      Date        Author
# "2.3.0"  11.08.2011  Bob Kalafut, Andreas Schlumberger
#                      Added additional IdentificationReasons for restarting
#                      and wink response
#--------------------------------------------------------------------------
# Rev      Date        Author
# "2.2.0"  11.05.2011  Bob Kalafut,
#                      Added new service setpassword()
#                      Added new structure - SetPassWordServiceData
#                      Added additional IdentificationReason - PASSWORD_SET
#--------------------------------------------------------------------------
# Rev      Date        Author
# "2.1.0"  10.03.2011  Andreas Schlumberger ,
#                      New structures added for local WEB client operations
#                      for the new router. 
#                      LONport, Eia709, IPport.fdt IPport.bdt IPport.fd added
#                      Statements added how to handle future DICP extensions 
#                      with optional fields.
#--------------------------------------------------------------------------
# Rev      Date        Author
# "2.0.0"  12.11.2010  Andreas Schlumberger restructure service data fields,
#                      put origin at top., make some optionals required.
#                      Add LAN RS485 to identification service. 
#                      Remove IdentSrc, wink as a scope filter,
#                      remove choice emulations. change scopefilter in 
#                      unconfigure to unconfigureLevel,
#                      add macAddr in LAN , use unix epoch time in s
#--------------------------------------------------------------------------
# Rev      Date        Author
# "1.1.0"  27.09.2010  Andreas Schlumberger     enums for IfAddrMode,
#                      IdentificationReason added, new opt field ifMode in
#                      BaDevData,origin field added for client requests. 
#--------------------------------------------------------------------------
# Rev      Date        Author
# "1.0.0"  27.09.2010  Andreas Schlumberger     Inital creation
#--------------------------------------------------------------------------


// *****************************************************************
//include "shared.thrift"
// *****************************************************************
namespace cpp dicp
// namespace csharp makes add. directories under gen-csharp
namespace csharp Siemens.BASys.Services.DICP

const string DICT_IDENT = "DICT"
const byte DICT_VERSION = 1 // protocol version

# The API version (NOT the product version), composed as a dot delimited
# string with major, minor, and patch level components.
#
#  - Major: Incremented for backward incompatible changes. An example would
#           be changes to the number or disposition of method arguments.
#           This field shall be checked at runtime for backwards compatibility.
#  - Minor: Incremented for backward compatible changes. An example would
#           be the addition of a new (optional) field, struct or method.
#  - Patch: Incremented for bug fixes. The patch level should be increased
#           for every edit that doesn't result in a change to major/minor.
#
# See the Semantic Versioning Specification (SemVer) http://semver.org.
const string INTERFACE_VERSION = "2.4.0"

// *****************************************************************
// DICP structures
// *****************************************************************
// These structures are the building blocks for the DICP protocol 
//  and general node configuration.
// As a general rule how to extend DICP fields: 
// The structures shall contain only fields that are also present
// in the XR NodeConfig schema file.
//
// Current XR NodeConfig schema: "XRF_NdSetUp_v01.06.xsd"
// Current rule exception: The following params are not in the schema
// Eia709.neuronId, LAN.macAddr, FDT.list<FDTEntry>
// *****************************************************************


// *****************************************************************
// DICP common structures
// *****************************************************************

typedef i64 timestamp //long in C#  represents unix utc Unix Epoch Time (s since 1.1.1970 GMT)

struct DevIdent {
  1: string serNr,
  2: string modelNam
}

//prefix is needed for the thrift compiler to separate identical enum consts.
enum IfAddrMode {
  DHCP   = 0,   
  STATIC = 1,
  //BRIDGED = 3, //and others not used yet
  IFAM_AnyOrDummyValue = 0xFFFF	// Any,dummy init. value
}

// *****************************************************************
// DICP structures for indentification
// *****************************************************************

enum PasswordType {
	PW_MD5		= 0,
	PW_PLAIN	= 1
}

enum IdentificationReason {
  SEARCH_RESPONSE 		= 0,
  PIN_PRESSED     		= 1,
  CONFIG_CHANGE   		= 2,
  PASSWORD_SET    		= 3,
  PASSWORD_SET_FAILED 	= 4,
  AUTHENTICATION_FAILED	= 5,
  CONFIGURING			= 6,
  UNCONFIGURING			= 7,
  RESTARTING			= 8,
  TIME_SET				= 9,
  WINK_RESPONSE			= 10,
  IDRE_AnyOrDummyValue 	= 0xFFFF	// Any,dummy init. value
}

struct BaDevData {
  1: i32    deviceInst,
  2: string deviceName,
  3: i32    deviceStatus,
  4: string deviceVersion, //version identifier of the controller
  5: string deviceAddr,    //BACnet MAC
}


struct URIData {
  1: string uriBase,
  2: optional string uriPath
}
struct DevInfo {
  1: optional string deviceDescr,
  2: optional string location
}

// *****************************************************************
// DICP structures for configure
// *****************************************************************

struct BaDev {
  1: string pidref,
  2: i32    deviceInst,
  3: string deviceName
}

struct BaPar {
  1: i32 maxAPDU,
  2: i32 aPDUTout,
  3: i32 retries,
  4: i32 segSupp,
  5: optional i32 segTout,
  6: optional i32 maxWind,
  7: optional i32 maxSegAcc
}

struct BaNw {
  1: optional i32 nwKind,
  2: i32 maxPorts
}

struct BDTEntry
{ 
  1:  string ipAddr,
  2:  i32    udpPort, 
  3:  optional string bdmask // broadcast distribution mask
}

struct FDTEntry //for display only!
{
  1:  string ipAddr,    //either FD's or BBMD's ip address 
  2:  i32    udpPort,
  3:  i32    ttl       // time to live in seconds
}

struct BDT
{
  1: i32          maxEntries,
  2: optional list<BDTEntry> entry, 
  3: optional string natPubIP
}

struct FDT
{
  1: i32          maxEntries,
  2: optional list<FDTEntry> entry, //not a config parameter, for display only!!
}
struct IPport {
  1: string pid,
  2: string nwRef,
  3: i32    nwNb,
  4: i32    udpPort,
  5: optional BDT bdt,
  6: optional FDT fdt,
  7: optional FDTEntry fd //if used, bdt and fdt fields are not present.
}

struct MSTPport {
  1: string pid,
  2: string nwRef,
  3: i32    nwNb,
  4: i32    addr,
  5: optional i32 maxInfo,
  6: optional i32 maxMaster,
  7: optional i32 slvP
}

struct LONport {
  1: string pid,
  2: string nwRef,
  3: i32    nwNb,
  4: i32    domain,
  5: i32    channel,
  6: i32    subnet,
  7: i32    node
}

// server has to check isset field to see the present fields
struct BaPort { 
  1: optional IPport     ip,
  2: optional MSTPport mstp,
  3: optional LONport  lon 
}



struct Lan {
  1: string   nwID,
  2: i32      ifMode,   // see IfAddrMode
  3: string   ipAddr,
  4: optional string netmask,
  5: optional string gtWay,
  6: optional string type,
  7: optional string macAddr //not a config param yet. for display only! 
}

struct Rs485 {
  1: string   nwID,
  2: i32      baudRate,
  3: optional string type
}

struct Eia709 {
  1: string nwID,
  2: optional string type,
  3: optional string neuronId //not a config param yet. for display only!
}

// server has to check isset field to see the present fields
struct NwItf { 
  1: optional Lan   lanItf,
  2: optional Rs485 rs485Itf,
  3: optional Eia709 eiaItf 
}

struct TimeSet { 
  1: string tz,
  2: optional i32 uTCOffs
}

// *****************************************************************
// DICP service data structures
// *****************************************************************
// These structures are the building blocks for the DICP protocol   
//  services data.
// These structures may only be used in the context of the 
// DICP service definitions below. E.g.
// ConfigureServiceData shall be used only for the configure service.
// *****************************************************************

struct DiscoverServiceData
{
  1: string authToken,
  2: string origin,
  3: string scopeFilter
}

struct WinkServiceData
{
  1: string authToken,
  2: string origin,
  3: string scopeFilter
}


struct IdentificationServiceData
{
  1: string    authToken,
  2: string    origin,
  3: i32       reason,   // see IdentificationReason
  4: DevIdent  devIdent, // nested struct
  5: BaDevData baDev,    // nested struct
  6: optional  DevInfo    devInfo,  // nested struct
  7: optional  Lan        lanItf,
  8: optional  Rs485      rs485Itf,
  9: optional  URIData    uridata,  // nested struct
  10: optional timestamp  utctime
}

struct ConfigureServiceData
{
  1: string    authToken,
  2: string    origin,
  3: DevIdent  devIdent, // nested struct
  4: BaDev     baDev,    // nested struct
  5: BaPar     baPar,    // nested struct
  6: BaNw      baNw,     // nested struct
  7: BaPort    baPort,   // nested struct, choice, one port only
  8: NwItf     nwItf,    // nested struct, choice, one port only
  9: TimeSet   timeSet   // nested struct
}


struct UnconfigureServiceData
{
  1: string    authToken,
  2: string    origin,
  3: DevIdent  devIdent, // nested struct
  4: string    unconfigureLevel // "?Config=All"
}

struct SetTimeServiceData
{
  1: string    authToken,
  2: string    origin,
  3: string    scopeFilter, // same as for discovery 
  4: timestamp utctime
}

struct SetPasswordServiceData
{
  1: string     authToken,
  2: string     origin,
  3: string     scopeFilter, // same as for discovery 
  4: i32		type,        // see PasswordType
  5: string     newpassword
}

// *****************************************************************
// DICP service definitions
// *****************************************************************
service DICPService {

  oneway void discover(1:DiscoverServiceData data ),
  oneway void wink(1:WinkServiceData data),
  oneway void configure(1:ConfigureServiceData data),
  oneway void unconfigure(1:UnconfigureServiceData data),
  oneway void settime(1:SetTimeServiceData data),
  oneway void setpassword(1:SetPasswordServiceData data)
}

service DICPEventService {
  oneway void identification(1:IdentificationServiceData data, 2: string ifversion)
}
