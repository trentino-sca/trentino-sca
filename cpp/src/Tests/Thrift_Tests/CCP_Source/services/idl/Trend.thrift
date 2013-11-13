//--------------------------------------------------------------------------
// (C) Copyright Siemens Building Technologies
//--------------------------------------------------------------------------
//  Project             :  Desigo Touch Panel & Web
//  Author              :  PATNI OSD TEAM
//  Date of creation    :  2012-06-20
//  Workfile            :  Trend.thrift
//--------------------------------------------------------------------------------------
//  Description:
//  Declaration for OAM Trends
//--------------------------------------------------------------------------

namespace java com.siemens.bt.trend
namespace cpp siemens.bt.trend
namespace csharp Siemens.BT.Trend
namespace py siemens.bt.trend
namespace js Trend

enum XAxisResolutionType
{
  ALL   		 = 0,
  ONE_HOUR  	 = 1,
  SIX_HOUR 	     = 2,
  TWELVE_HOUR    = 3,
  ONE_DAY   	 = 4,
  ONE_WEEK  	 = 5,
  ONE_MONTH  	 = 6,
  THREE_MONTH    = 7 
}

enum YMode 
{
  MANUAL		= 0,
  AUTOMATIC	    = 1
}

enum Trend_Command_Type
{
  CMD_MODIFY_X_AXIS = 0,
  CMD_MODIFY_Y_AXIS = 1
}

enum TrendObjectState
{
   STATE_EMPTY      = 0,
   STATE_UPDATING   = 1,
   STATE_READY      = 2, 
   STATE_ERROR      = 3
}
  
struct GetTrendLogDataParamaters
{
  1: optional i32    startTime,
  2: optional i32    endTime,
  3: optional i32    maxNrOfLogEntries,
  4: optional bool   refreshLogBuffer
}

struct ModifyXAxisSettingsParameters
{
  1: XAxisResolutionType xResolution
}

struct ModifyYAxisSettingsParameters
{
  1: YMode yMode,
  2: optional double yMinValue,
  3: optional double yMaxValue
}
 
struct ModifyAxisSettingsParameters
{
  1: optional ModifyXAxisSettingsParameters modifyXAxisSettingsParameters,
  2: optional ModifyYAxisSettingsParameters modifyYAxisSettingsParameters
} 

struct TrendParameters
{
  1: string trendId,
  2: optional Trend_Command_Type command,
  3: optional GetTrendLogDataParamaters getTrendLogDataParamaters,
  4: optional ModifyAxisSettingsParameters modifyAxisSettingsParameters
}