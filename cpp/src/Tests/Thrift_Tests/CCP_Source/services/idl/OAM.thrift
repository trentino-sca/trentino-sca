#--------------------------------------------------------------------------
# (C) Copyright Siemens Building Technologies
#--------------------------------------------------------------------------
#  Project             :  Systen ONE
#  Author              :  Patni OSD Team
#  Date of creation    :  2011-09-08
#  Workfile            :  OAM.thrift
#--------------------------------------------------------------------------
#  Description:
#    a simple service providing basic data for the OAM
#
# TODO:
# - review namespaces
# - 
#
#--------------------------------------------------------------------------



namespace java com.siemens.bt.oam
namespace cpp siemens.bt.oam
namespace csharp Siemens.BT.OAM
namespace py siemens.bt.oam

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
const string INTERFACE_VERSION = "0.0.1"

const string OAM_HTTP_JSON_URI   = "/api/thrift/oam.json"

const string SOCKET_TCP_BIN = "/tmp/t_oam_tcpbin.socket"
const string SOCKET_HTTP_JSON = "/tmp/t_oam_httpjs.socket"



struct ImageResult
{
	1: Types.Result_Code resultCode,
	2: string mimeType
	//3: optional binary blob
}


/**
 * Standard OAM Service
 */
service OAMService
{
	//Types.ServiceResult serviceCall(1: string authenticationToken,2: Types.ServiceCommand command ),
	Types.ServiceResult serviceCall(1: string authenticationToken,2: string viewState ,3: Types.ServiceCommand command),
	
	ImageResult prepareBackgroundImage(1: string authToken, 2: string viewId, 3: i32 pageId, 4: string imageDestPath)
	//ImageResult getBackgroundImage(1: string authToken, 2: i32 pageId)

/*
	Types.ServiceResult copyDailyProfile(1: string schedulerId, 2: byte sourceDay, 3: list<byte> destinationDays),
	Types.ServiceResult copyExceptionProfile(1: string schedulerId, 2: string exceptionId, 3: list<Types.TDate> destinationDates),
	Types.ServiceResult setTimeValueForDay(1: string schedulerId, 2: byte day, 3: double startTime, 4: double endTime, 5: i32 value),
	Types.ServiceResult setTimeValueForException(1: string schedulerId, 2: string exceptionId, 3: double startTime, 4: double endTime, 5: i32 value),
	Types.ServiceResult createException(1: string schedulerId, 2: Types.TDate date, 3: double startTime, 4: double endTime, 5: i32 value),
	Types.ServiceResult deleteException(1: string schedulerId, 2: string exceptionId),
	Types.ServiceResult setDateRange(1: string schedulerId, 2: string exceptionId, 3: Types.TDate endDate),
	Types.ServiceResult setRecurring(1: string schedulerId, 2: string exceptionId, 3: string specification),
*/
}