#--------------------------------------------------------------------------
# (C) Copyright Siemens Building Technologies
#--------------------------------------------------------------------------
#  Project             :  Systen ONE
#  Author              :  henrique.mendonca@siemens.com
#  Date of creation    :  2012-04-03
#  Workfile            :  Scheduler.thrift
#--------------------------------------------------------------------------
#  Description:
#    type definition for the OAM Scheduler
#
#--------------------------------------------------------------------------


namespace java com.siemens.bt.scheduler
namespace cpp siemens.bt.scheduler
namespace csharp Siemens.BT.Scheduler
namespace py siemens.bt.scheduler
namespace js Scheduler

# 24 * 3600
const i32 END_OF_DAY = 86400


enum ExceptionType
{
	READ_ONLY
	SINGLE,
	MULTIPLE,
}

enum PeriodType
{
  DATE,
  DATE_RANGE,
  WEEKNDAY,
  CALENDAR_REF,
  UNDEFINED
}

struct Date
{
  1:i16 year,
  2:byte month,
  3:byte day,
}

struct WeekNDay
{
  1:i32 month,
  2:i32 weekOfMonth,
  3:i32 dayOfWeek,
}

struct RecurringType
{
  1: PeriodType period,
  2: optional Date date,
  3: optional WeekNDay weekNDay
}

/* command parameter */
enum Scheduler_Command_Type
{
  CMD_SET_PHASE_FOR_DAY = 1,
  CMD_CHANGE_PHASE_FOR_DAY,
  CMD_DELETE_PHASE_FOR_DAY,
  CMD_COPY_DAILY_PROFILE,
  CMD_SET_PHASE_FOR_SPECIAL_EVENT,
  CMD_CHANGE_PHASE_FOR_SPECIAL_EVENT,
  CMD_DELETE_PHASE_FOR_SPECIAL_EVENT,
  CMD_COPY_SPECIAL_EVENT_PROFILE,
  CMD_CREATE_SPECIAL_EVENTS,
  CMD_SET_DATE_RANGE,
  CMD_SET_RECURRING,
  CMD_DELETE_SPECIAL_EVENT,
  CMD_REQ_EXCEPTION_MONTH
}

struct SetPhaseForDay
{
  1: byte day,
  2: i32 startTime,
  3: i32 endTime,
  4: i32 value,
}

struct ChangePhaseForDay
{
  1: byte day,
  2: i32 prevStartTime,
  3: i32 newStartTime,
  4: i32 newEndTime,
  5: i32 value,
}

struct DeletePhaseForDay
{
  1: byte day,
  2: i32 startTime,
}

struct CopyDailyProfile
{
  1: byte srcDay,
  2: list<byte> destDays,
}

struct SetPhaseForSpecialEvent
{
  1: i16 specialEventId,
  2: i32 startTime,
  3: i32 endTime,
  4: i32 value,
}

struct ChangePhaseForSpecialEvent
{
  1: i16 specialEventId,
  2: i32 prevStartTime,
  3: i32 newStartTime,
  4: i32 newEndTime,
  5: i32 value,
}

struct DeletePhaseForSpecialEvent
{
  1: i16 specialEventId,
  2: i32 startTime,
}

struct CopySpecialEventProfile
{
  1: i16 specialEventId,
  2: list<Date> destDate,
}

struct CreateSpecialEvent
{
  1: RecurringType recurringSpec,
  2: i32 startTime,
  3: i32 endTime,
  4: i32 value,
}

struct SetDateRange
{
  1:i16 specialEventId,
  2: Date endDate,
}

struct SetRecurring
{
  1:i16 specialEventId,
  2:RecurringType recurringSpec,
}

struct DeleteSpecialEvent
{
  1:i16 specialEventId,
}

struct RequestExceptionMonths
{
  1:i32 startYear,
  2:i32 startMonth,
  3:i32 numberOfMonths,
}

struct SchedulerParameters
{
  1: i16 schedulerId,
  2: Scheduler_Command_Type command,
  3: optional SetPhaseForDay setPhaseForDay,
  4: optional ChangePhaseForDay changePhaseForDay,
  5: optional DeletePhaseForDay deletePhaseForDay,
  6: optional CopyDailyProfile copyDailyProfile,
  7: optional SetPhaseForSpecialEvent setPhaseForSpecialEvent,
  8: optional ChangePhaseForSpecialEvent changePhaseForSpecialEvent,
  9: optional DeletePhaseForSpecialEvent deletePhaseForSpecialEvent,
  10: optional CopySpecialEventProfile copySpecialEventProfile,
  11: optional CreateSpecialEvent createSpecialEvent,
  12: optional SetDateRange setDateRange,
  13: optional SetRecurring setRecurring,
  14: optional DeleteSpecialEvent deleteSpecialEvent,
  15: optional RequestExceptionMonths requestExceptionMonth, 
}

struct SchedulerResult
{
  1:i16 specialEventId,
}



