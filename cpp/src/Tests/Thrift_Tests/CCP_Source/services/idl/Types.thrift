/*
 * a simple service providing basic data of a device
 *
 * sample usage:
 * simple web interface, snmpd reads its basic configuration
 *
 * Roger Meier <r.meier@siemens.com>
 */

namespace java com.siemens.bt.type
namespace cpp siemens.bt.type
namespace csharp Siemens.BT.Type
namespace py siemens.bt.type


include "Scheduler.thrift"
include "Trend.thrift"

/**
 * language code (ISO 639-2)
 * country code (ISO 3166) => localization /usr/share/zoneinfo/iso3166.tab
 */
 



# following enums are imported from IBacnetdef.h and IBneterr.h
enum BA_DATA_TYPE
{
  BA_NULL = 0,
  BA_BOOL = 1,
  BA_UINT = 2,
  BA_INT = 3,
  BA_REAL = 4,
  BA_DOUBLE = 5,
  BA_OCTET_STRING = 6,
  BA_CHAR_STRING = 7,
  BA_BIT_STRING = 8,
  BA_ENUMERATED = 9,
  BA_DATE = 10,
  BA_TIME = 11,
  BA_OBJ_ID = 12
}

enum Property_Type {
  BA_PROP_ACKED_TRANSITIONS                         = 0,     // AckTra
  BA_PROP_ACK_REQUIRED                              = 1,     // AckReq
  BA_PROP_ACTION                                    = 2,     // Actn
  BA_PROP_ACTION_TEXT                               = 3,     // ActnTxt
  BA_PROP_ACTIVE_TEXT                               = 4,     // ActvTxt
  BA_PROP_ACTIVE_VT_SESSION                         = 5,     // ActvVTSs
  BA_PROP_ALARM_VALUE                               = 6,     // RefVal
  BA_PROP_ALARM_VALUES                              = 7,     // RefVals
  BA_PROP_ALL                                       = 8,     // All
  BA_PROP_ALL_WRITES_SUCCESSFUL                     = 9,     // WritScc
  BA_PROP_APDU_SEGMENT_TIMEOUT                      = 10,     // APDUST
  BA_PROP_APDU_TIMEOUT                              = 11,     // APDUT
  BA_PROP_APPLICATION_SOFTWARE_VERSION              = 12,     // AplSfwVn
  BA_PROP_ARCHIVE                                   = 13,     // Arch
  BA_PROP_BIAS                                      = 14,     // Bias
  BA_PROP_CHANGE_OF_STATE_COUNT                     = 15,     // CosCnt
  BA_PROP_CHANGE_OF_STATE_TIME                      = 16,     // TiCos
  BA_PROP_NOTIFICATION_CLASS                        = 17,     // NotifCl
  BA_PROP_CONTROLLED_VARIABLE_REFERENCE             = 19,     // CtlVarr
  BA_PROP_CONTROLLED_VARIABLE_UNITS                 = 20,     // CtlVarUn
  BA_PROP_CONTROLLED_VARIABLE_VALUE                 = 21,     // CtlVvl
  BA_PROP_COV_INCREMENT                             = 22,     // Cov
  BA_PROP_DATELIST                                  = 23,     // DateList
  BA_PROP_DAYLIGHT_SAVINGS_STATUS                   = 24,     // DsavSta
  BA_PROP_DEADBAND                                  = 25,     // Nz
  BA_PROP_DERIVATIVE_CONSTANT                       = 26,     // DervCon
  BA_PROP_DERIVATIVE_CONSTANT_UNITS                 = 27,     // DervCun
  BA_PROP_DESCRIPTION                               = 28,     // Des
  BA_PROP_DESCRIPTION_OF_HALT                       = 29,     // DesStp
  BA_PROP_DEVICE_ADDRESS_BINDING                    = 30,     // DevADRB
  BA_PROP_DEVICE_TYPE                               = 31,     // DevTyp
  BA_PROP_EFFECTIVE_PERIOD                          = 32,     // EfPrd
  BA_PROP_ELAPSED_ACTIVE_TIME                       = 33,     // Oph
  BA_PROP_ERROR_LIMIT                               = 34,     // ErLm
  BA_PROP_EVENT_ENABLE                              = 35,     // EnEvt
  BA_PROP_EVENT_STATE                               = 36,     // EvtSta
  BA_PROP_EVENT_TYPE                                = 37,     // EvtTyp
  BA_PROP_EXCEPTION_SCHEDULE                        = 38,     // EcptSchd
  BA_PROP_FAULT_VALUES                              = 39,     // FltVals
  BA_PROP_FEEDBACK_VALUE                            = 40,     // FbVal
  BA_PROP_FILE_ACCESS_METHOD                        = 41,     // FileAcmt
  BA_PROP_FILE_SIZE                                 = 42,     // FileSize
  BA_PROP_FILE_TYPE                                 = 43,     // FileTyp
  BA_PROP_FIRMWARE_REVISION                         = 44,     // FrmwRv
  BA_PROP_HIGH_LIMIT                                = 45,     // HiLm
  BA_PROP_INACTIVE_TEXT                             = 46,     // IactvTxt
  BA_PROP_IN_PROCESS                                = 47,     // TraSta
  BA_PROP_INSTANCE_OF                               = 48,     // Instn
  BA_PROP_INTEGRAL_CONSTANT                         = 49,     // IntgCon
  BA_PROP_INTEGRAL_CONSTANT_UNITS                   = 50,     // IntgCun
  BA_PROP_ISSUE_CONFIRMED_NOTIFICATIONS             = 51,     // CfmNotif
  BA_PROP_LIMIT_ENABLE                              = 52,     // EnLm
  BA_PROP_LIST_OF_GROUP_MEMBERS                     = 53,     // GrpmList
  BA_PROP_LIST_OF_OBJECT_PROPERTY_REFERENCES        = 54,     // PrprList
  BA_PROP_LIST_OF_SESSION_KEYS                      = 55,     // SkeyList
  BA_PROP_LOCAL_DATE                                = 56,     // LocDate
  BA_PROP_LOCAL_TIME                                = 57,     // TiLoc
  BA_PROP_LOCATION                                  = 58,     // Locat
  BA_PROP_LOW_LIMIT                                 = 59,     // LoLm
  BA_PROP_MANIPULATED_VARIABLE_REFERENCE            = 60,     // ChgdVarr
  BA_PROP_MAXIMUM_OUTPUT                            = 61,     // MaxOut
  BA_PROP_MAX_APDU_LENGTH_ACCEPTED                  = 62,     // APDULM
  BA_PROP_MAX_INFO_FRAMES                           = 63,     // MaxIfrms
  BA_PROP_MAX_MASTER                                = 64,     // MaxMstr
  BA_PROP_MAX_PRES_VALUE                            = 65,     // PrValMax
  BA_PROP_MINIMUM_OFF_TIME                          = 66,     // TiOffMin
  BA_PROP_MINIMUM_ON_TIME                           = 67,     // TiOnMin
  BA_PROP_MINIMUM_OUTPUT                            = 68,     // MinOut
  BA_PROP_MIN_PRES_VALUE                            = 69,     // PrValMin
  BA_PROP_MODEL_NAME                                = 70,     // ModelNam
  BA_PROP_MODIFICATION_DATE                         = 71,     // MdfcDate
  BA_PROP_NOTIFY_TYPE                               = 72,     // NotifTyp
  BA_PROP_NUMBER_OF_APDU_RETRIES                    = 73,     // APDURN
  BA_PROP_NUMBER_OF_STATES                          = 74,     // NumSta
  BA_PROP_OBJECT_IDENTIFIER                         = 75,     // ObjId
  BA_PROP_OBJECT_LIST                               = 76,     // ObjList
  BA_PROP_OBJECT_NAME                               = 77,     // ObjNam
  BA_PROP_OBJECT_PROPERTY_REFERENCE                 = 78,     // ObjPrpr
  BA_PROP_OBJECT_TYPE                               = 79,     // ObjTyp
  BA_PROP_OPTIONAL                                  = 80,     // Optnl
  BA_PROP_OUT_OF_SERVICE                            = 81,     // OoServ
  BA_PROP_OUTPUT_UNITS                              = 82,     // OutUn
  BA_PROP_EVENT_PARAMETERS                          = 83,     // EvtPars
  BA_PROP_POLARITY                                  = 84,     // Pol
  BA_PROP_PRESENT_VALUE                             = 85,     // PrVal
  BA_PROP_PRIORITY                                  = 86,     // Prio
  BA_PROP_PRIORITY_ARRAY                            = 87,     // PrioArr
  BA_PROP_PRIORITY_FOR_WRITING                      = 88,     // PrioWrit
  BA_PROP_PROCESS_IDENTIFIER                        = 89,     // PrcId
  BA_PROP_PROGRAM_CHANGE                            = 90,     // PgmChg
  BA_PROP_PROGRAM_LOCATION                          = 91,     // PgmLocat
  BA_PROP_PROGRAM_STATE                             = 92,     // PgmSta
  BA_PROP_PROPORTIONAL_CONSTANT                     = 93,     // PropCon
  BA_PROP_PROPORTIONAL_CONSTANT_UNITS               = 94,     // PropCun
  BA_PROP_PROTOCOL_CONFORMANCE_CLASS                = 95,     // ProtCncl
  BA_PROP_PROTOCOL_OBJECT_TYPES_SUPPORTED           = 96,     // ProtOTs
  BA_PROP_PROTOCOL_SERVICES_SUPPORTED               = 97,     // ProtServ
  BA_PROP_PROTOCOL_VERSION                          = 98,     // ProtVn
  BA_PROP_READ_ONLY                                 = 99,     // ReadOnly
  BA_PROP_REASON_FOR_HALT                           = 100,     // StpRsn
  BA_PROP_RECIPIENT                                 = 101,     // Recp
  BA_PROP_RECIPIENT_LIST                            = 102,     // RecpList
  BA_PROP_RELIABILITY                               = 103,     // Rlb
  BA_PROP_RELINQUISH_DEFAULT                        = 104,     // DefVal
  BA_PROP_REQUIRED                                  = 105,     // Rqd
  BA_PROP_RESOLUTION                                = 106,     // Rsl
  BA_PROP_SEGMENTATION_SUPPORTED                    = 107,     // SegmSprt
  BA_PROP_SETPOINT                                  = 108,     // Sp
  BA_PROP_SETPOINT_REFERENCE                        = 109,     // SpRef
  BA_PROP_STATE_TEXT                                = 110,     // StaTxt
  BA_PROP_STATUS_FLAGS                              = 111,     // StaFlg
  BA_PROP_SYSTEM_STATUS                             = 112,     // SysSta
  BA_PROP_TIME_DELAY                                = 113,     // TiMonDvn
  BA_PROP_TIME_OF_ACTIVE_TIME_RESET                 = 114,     // TiStmOph
  BA_PROP_TIME_OF_STATE_COUNT_RESET                 = 115,     // TSCR
  BA_PROP_TIME_SYNCHRONIZATION_RECIPIENTS           = 116,     // SynRecp
  BA_PROP_UNITS                                     = 117,     // Un
  BA_PROP_UPDATE_INTERVAL                           = 118,     // UpdIvl
  BA_PROP_UTC_OFFSET                                = 119,     // UtcOfs
  BA_PROP_VENDOR_IDENTIFIER                         = 120,     // VndrID
  BA_PROP_VENDOR_NAME                               = 121,     // VndrNam
  BA_PROP_VT_CLASSES_SUPPORTED                      = 122,     // VTClSprt
  BA_PROP_WEEKLY_SCHEDULE                           = 123,     // WeekSchd
  BA_PROP_ATTEMPTED_SAMPLES                         = 124,     // AtpdSmpl
  BA_PROP_AVERAGE_VALUE                             = 125,     // AvrgVal
  BA_PROP_BUFFER_SIZE                               = 126,     // BufSize
  BA_PROP_CLIENT_COV_INCREMENT                      = 127,     // CltCovic
  BA_PROP_COV_RESUBSCRIPTION_INTERVAL               = 128,     // CovRI
  BA_PROP_CURRENT_NOTIFY_TIME                       = 129,     // PrNotiTi
  BA_PROP_EVENT_TIME_STAMPS                         = 130,     // TiStmEvt
  BA_PROP_LOG_BUFFER                                = 131,     // LogBuf
  BA_PROP_LOG_DEVICE_OBJECT_PROPERTY                = 132,     // LogDOP
  BA_PROP_ENABLE                                    = 133,     // EnLog
  BA_PROP_LOG_INTERVAL                              = 134,     // LogIvl
  BA_PROP_MAXIMUM_VALUE                             = 135,     // ValMax
  BA_PROP_MINIMUM_VALUE                             = 136,     // ValMin
  BA_PROP_NOTIFICATION_THRESHOLD                    = 137,     // NotifThd
  BA_PROP_PREVIOUS_NOTIFY_TIME                      = 138,     // PrvNotif
  BA_PROP_PROTOCOL_REVISION                         = 139,     // ProtRv
  BA_PROP_RECORDS_SINCE_NOTIFICATION                = 140,     // RecNotif
  BA_PROP_RECORD_COUNT                              = 141,     // RecCnt
  BA_PROP_START_TIME                                = 142,     // TiStt
  BA_PROP_STOP_TIME                                 = 143,     // TiStp
  BA_PROP_STOP_WHEN_FULL                            = 144,     // StpFull
  BA_PROP_TOTAL_RECORD_COUNT                        = 145,     // TotRecnt
  BA_PROP_VALID_SAMPLES                             = 146,     // VldSmpl
  BA_PROP_WINDOW_INTERVAL                           = 147,     // WndIvl
  BA_PROP_WINDOW_SAMPLES                            = 148,     // WndSmpl
  BA_PROP_MAXIMUM_VALUE_TIMESTAMP                   = 149,     // TiValMax
  BA_PROP_MINIMUM_VALUE_TIMESTAMP                   = 150,     // TiValMin
  BA_PROP_VARIANCE_VALUE                            = 151,     // VrcVal
  BA_PROP_ACTIVE_COV_SUBSCRIPTIONS                  = 152,     // ActvCovs
  BA_PROP_BACKUP_FAILURE_TIMEOUT                    = 153,     // TioBck
  BA_PROP_CONFIGURATION_FILES                       = 154,     // CfFiles
  BA_PROP_DATABASE_REVISION                         = 155,     // DbRv
  BA_PROP_DIRECT_READING                            = 156,     // DirRead
  BA_PROP_LAST_RESTORE_TIME                         = 157,     // LstRsto
  BA_PROP_MAINTENANCE_REQUIRED                      = 158,     // MntnReq
  BA_PROP_MEMBER_OF                                 = 159,     // Mbr
  BA_PROP_MODE                                      = 160,     // Mod
  BA_PROP_OPERATION_REQUIRED                        = 161,     // OpReq
  BA_PROP_SETTING                                   = 162,     // Set
  BA_PROP_SILENCED                                  = 163,     // Silenced
  BA_PROP_TRACKING_VALUE                            = 164,     // TrackVal
  BA_PROP_ZONE_MEMBERS                              = 165,     // ZMbrs
  BA_PROP_LIFE_SAFETY_ALARM_VALUES                  = 166,     // SfAlmVal
  BA_PROP_MAX_SEGMENTS_ACCEPTED                     = 167,     // MaxSegm
  BA_PROP_PROFILE_NAME                              = 168,     // PrfNam
  BA_PROP_AUTO_SLAVE_DISCOVERY                      = 169,     // AutoSlvd
  BA_PROP_MANUAL_SLAVE_ADDRESS_BINDING              = 170,     // ManSlvab
  BA_PROP_SLAVE_ADDRESS_BINDING                     = 171,     // Slvab
  BA_PROP_SLAVE_PROXY_ENABLE                        = 172,     // SlvPxyEn
  BA_PROP_LAST_NOTIFY_RECORD                        = 173,     // LstRecNr
  BA_PROP_SCHEDULE_DEFAULT                          = 174,     // SdDefVal
  BA_PROP_ACCEPTED_MODES                            = 175,     // AccptMod
  BA_PROP_ADJUST_VALUE                              = 176,     // CorrVal
  BA_PROP_COUNT                                     = 177,     // Puc
  BA_PROP_COUNT_BEFORE_CHANGE                       = 178,     // PucBfCor
  BA_PROP_COUNT_CHANGE_TIME                         = 179,     // CorrTi
  BA_PROP_COV_PERIOD                                = 180,     // CovPrd
  BA_PROP_INPUT_REFERENCE                           = 181,     // InPrpr
  BA_PROP_LIMIT_MONITORING_INTERVAL                 = 182,     // MonIvl
  BA_PROP_LOGGING_OBJECT                            = 183,     // LogObj
  BA_PROP_LOGGING_RECORD                            = 184,     // LogRec
  BA_PROP_PRESCALE                                  = 185,     // PreScale
  BA_PROP_PULSE_RATE                                = 186,     // PulsRate
  BA_PROP_SCALE                                     = 187,     // Scale
  BA_PROP_SCALE_FACTOR                              = 188,     // CnvFac
  BA_PROP_UPDATE_TIME                               = 189,     // PucUdt
  BA_PROP_VALUE_BEFORE_CHANGE                       = 190,     // ValBfCor
  BA_PROP_VALUE_SET                                 = 191,     // SetVal
  BA_PROP_VALUE_CHANGE_TIME                         = 192,     // ChgTiStm
  BA_PROP_ALIGN_INTERVALS                           = 193,     // AlgnIvl
  BA_PROP_INTERVAL_OFFSET                           = 195,     // IvlOfs
  BA_PROP_LAST_RESTART_REASON                       = 196,     // LstRstRn
  BA_PROP_LOGGING_TYPE                              = 197,     // LogTyp
  BA_PROP_RESTART_NOTIFICATION_RECIPIENTS           = 202,     // RstNfRcp
  BA_PROP_TIME_OF_DEVICE_RESTART                    = 203,     // TiDevRst
  BA_PROP_TIME_SYNCHRONIZATION_INTERVAL             = 204,     // TiSynIvl
  BA_PROP_TRIGGER                                   = 205,     // Trg
  BA_PROP_UTC_TIME_SYNCHRONIZATION_RECIPIENTS       = 206,     // TiSynRcp
  BA_PROP_NODE_SUBTYPE                              = 207,     // NdSubTyp
  BA_PROP_NODE_TYPE                                 = 208,     // NdTyp
  BA_PROP_STRUCTURED_OBJECT_LIST                    = 209,     // StctList
  BA_PROP_SUBORDINATE_ANNOTATIONS                   = 210,     // SubAntn
  BA_PROP_SUBORDINATE_LIST                          = 211,     // SubList
  BA_PROP_ACTUAL_SHED_LEVEL                         = 212,     // ActSdLvl
  BA_PROP_DUTY_WINDOW                               = 213,     // DTY_WNDW
  BA_PROP_EXPECTED_SHED_LEVEL                       = 214,     // ExpSdLvl
  BA_PROP_FULL_DUTY_BASELINE                        = 215,     // FulDtyBl
  BA_PROP_REQUESTED_SHED_LEVEL                      = 218,     // ReqSdLvl
  BA_PROP_SHED_DURATION                             = 219,     // SdDurat
  BA_PROP_SHED_LEVEL_DESCRIPTIONS                   = 220,     // SdLvlDsc
  BA_PROP_SHED_LEVELS                               = 221,     // SdLvls
  BA_PROP_DOOR_ALARM_STATE                          = 226,     // DorAlSta
  BA_PROP_DOOR_EXTENDED_PULSE_TIME                  = 227,     // DorExPT
  BA_PROP_DOOR_MEMBERS                              = 228,     // DorMbrs
  BA_PROP_DOOR_OPEN_TOO_LONG_TIME                   = 229,     // DorOtlTi
  BA_PROP_DOOR_PULSE_TIME                           = 230,     // DorPuTi
  BA_PROP_DOOR_STATUS                               = 231,     // DorSta
  BA_PROP_DOOR_UNLOCK_DELAY_TIME                    = 232,     // DorUlDTi
  BA_PROP_LOCK_STATUS                               = 233,     // LckSta
  BA_PROP_MASKED_ALARM_VALUES                       = 234,     // MsAlVals
  BA_PROP_SECURED_STATUS                            = 235,     // SecSta
  BA_PROP_BACKUP_AND_RESTORE_STATE                  = 338,     // BckRsSta
  BA_PROP_BACKUP_PREPARATION_TIME                   = 339,     // BckPrpTi
  BA_PROP_RESTORE_COMPLETION_TIME                   = 340,     // RsCplTi
  BA_PROP_RESTORE_PREPARATION_TIME                  = 341,     // RsPrpTi
  
  BA_PROP_USER_DESIGNATION                          = 3000,     // UsrDesg
  BA_PROP_SURROUND                                  = 3001,     // Surround
  BA_PROP_INTERFACE_LIST                            = 3002,     // ItfList
  BA_PROP_LOCAL_LIST                                = 3003,     // LocList
  BA_PROP_HIERARCHY_LIST                            = 3004,     // HrchList
  BA_PROP_ELEMENT_TYPE                              = 3005,     // EleTyp
  BA_PROP_OBJECT_TAG                                = 3006,     // ObjTag
  BA_PROP_FUNCTION_NAME                             = 3007,     // FunName
  BA_PROP_LOW_VALUE                                 = 3008,     // LoVal
  BA_PROP_HIGH_VALUE                                = 3009,     // HiVal
  BA_PROP_PARAMETER_KIND                            = 3010,     // ParKind
  BA_PROP_ALARM_ENABLE                              = 3011,     // EnAlm
  BA_PROP_LOCKED                                    = 3013,     // Lock
  BA_PROP_TIME_OF_ACKED                             = 3014,     // TiAck
  BA_PROP_ACK_INITIALS                              = 3015,     // AckSgn
  BA_PROP_MESSAGE_TEXT                              = 3016,     // MsgTxt
  BA_PROP_SLOPE                                     = 3017,     // Slpe
  BA_PROP_INTERCEPT                                 = 3018,     // Icpt
  BA_PROP_ADDRESS                                   = 3019,     // IOAddr
  BA_PROP_COMMISSIONING_STATE                       = 3021,     // ComgSta
  BA_PROP_NAME_REFERENCE                            = 3022,     // Namr
  BA_PROP_FEEDBACK_ADDR                             = 3023,     // FbAddr
  BA_PROP_DESTINATION_LIST                          = 3025,     // DestList
  BA_PROP_SITE_NAME                                 = 3026,     // SiteNam
  BA_PROP_PRIMARY_DEVICE                            = 3028,     // PrimDev
  BA_PROP_GLOBAL_OBJECTS_MODIFICATION_TIME          = 3029,     // GOEngTi
  BA_PROP_GLOBAL_OBJECTS_UPDATE_TIME                = 3030,     // GOChgTi
  BA_PROP_SYNCH_REQUEST_PERIOD                      = 3033,     // SynReqp
  BA_PROP_PROGRAM_MODIFICATION_TIME                 = 3034,     // PgmMti
  BA_PROP_MIN_CYCLE_TIME                            = 3035,     // TiCycMin
  BA_PROP_MAX_CYCLE_TIME                            = 3036,     // TiCycMax
  BA_PROP_CYCLE_TIME_STATISTICS                     = 3037,     // TiStcCyc
  BA_PROP_MEMORY_STATISTICS                         = 3038,     // MemStc
  BA_PROP_COMMUNICATION_STATISTICS                  = 3039,     // ComStc
  BA_PROP_SERIAL_LINE_STATISTICS                    = 3040,     // SerlnStc
  BA_PROP_DIAGNOSTICS                               = 3041,     // Diag
  BA_PROP_MAIN_PARAMETER                            = 3042,     // MnVal
  BA_PROP_ACCESS_RIGHT                              = 3043,     // AccCl
  BA_PROP_MAX_SIZE                                  = 3044,     // MaxSize
  BA_PROP_MIN_SIZE                                  = 3045,     // MinSize
  BA_PROP_ENABLE_ACTIVE_TIME                        = 3046,     // EnOph
  BA_PROP_ELAPSED_TIME_LIMIT                        = 3047,     // OphLm
  BA_PROP_TOTAL_ACTIVE_TIME                         = 3048,     // OphTot
  BA_PROP_SHADOW_DEV_OBJ_ID                         = 3049,     // ShwDOID
  BA_PROP_SHADOW_DEV_OBJ_NAME                       = 3050,     // ShwDON
  BA_PROP_EXPIRED_DATE                              = 3052,     // MntnDate
  BA_PROP_FEEDBACK_POLARITY                         = 3053,     // FbPol
  BA_PROP_FEEDBACK_SLOPE                            = 3054,     // FbSlpe
  BA_PROP_FEEDBACK_INTERCEPT                        = 3055,     // FbIcpt
  BA_PROP_EXCEPTIONS                                = 3056,     // Ecpt
  BA_PROP_NEXT_VALUE                                = 3057,     // NxVal
  BA_PROP_NEXT_TIME                                 = 3058,     // NxTi
  BA_PROP_PARAMETER_LIST                            = 3059,     // ParList
  BA_PROP_LIST_OF_NAME_REFERENCE                    = 3060,     // NamrList
  BA_PROP_DAYLIGHT_SAVING_BEGIN_DATE                = 3061,     // DsavSdt
  BA_PROP_DAYLIGHT_SAVING_BEGIN_TIME                = 3062,     // DsavSti
  BA_PROP_DAYLIGHT_SAVING_END_DATE                  = 3063,     // DsavEdt
  BA_PROP_DAYLIGHT_SAVING_END_TIME                  = 3064,     // DsavEti
  BA_PROP_OPERATING_HOURS_MESSAGE                   = 3066,     // OphMsg
  BA_PROP_EXPIRED                                   = 3067,     // MntnInd
  BA_PROP_ELAPSED_TIME                              = 3068,     // PrOph
  BA_PROP_MAX_INSTR_COUNT                           = 3069,     // MaxInstr
  BA_PROP_RECLAIM_TIME                              = 3070,     // ReclmTi
  BA_PROP_YESTERDAY                                 = 3072,     // YdayVal
  BA_PROP_NEXT_DATE                                 = 3073,     // NxDate
  BA_PROP_VISIBILITY                                = 3074,     // Visiblty
  BA_PROP_SERVER_TYPE                               = 3075,     // SrvTyp
  BA_PROP_NAME_RESOLUTION_INTERVAL                  = 3076,     // NamRI
  BA_PROP_SHADOW_APDU_SEGMENT_TIMEOUT               = 3077,     // SAPDUST
  BA_PROP_SHADOW_APDU_TIMEOUT                       = 3078,     // SAPDUT
  BA_PROP_SHADOW_MAX_APDU_LENGTH_ACCEPTED           = 3079,     // SMAPDULA
  BA_PROP_SHADOW_NUMBER_OF_APDU_RETRIES             = 3080,     // SNAPDUR
  BA_PROP_GLOBAL                                    = 3081,     // Global
  BA_PROP_STARTUP_STATISTIC                         = 3082,     // StupStc
  BA_PROP_DATETIME_SUBTYPE                          = 3083,     // DatiStyp
  BA_PROP_USERS                                     = 3084,     // Users
  BA_PROP_USERGROUPS                                = 3085,     // UsrGrps
  BA_PROP_SCOPES                                    = 3086,     // ScopeAcc
  BA_PROP_LAST_MODIFICATION                         = 3087,     // LstChg
  BA_PROP_GROUP                                     = 3088,     // GrpRef
  BA_PROP_MAXNR_CALL_REPETITIONS                    = 3089,     // MaxCallr
  BA_PROP_TERMINATION_TIME_VALUE                    = 3090,     // TiTrmSet
  BA_PROP_ACCESS_PASSWORD                           = 3091,     // RemAcpwd
  BA_PROP_COM_INTERFACE_LIST                        = 3092,     // ComList
  BA_PROP_CONNECTION_LIST                           = 3093,     // CnctList
  BA_PROP_MODEM_STATISTICS                          = 3094,     // MdmStc
  BA_PROP_MODEM_SETTINGS                            = 3095,     // MdmSet
  BA_PROP_MODEM_STATUS                              = 3096,     // MdmSta
  BA_PROP_CONNECT                                   = 3097,     // CnctReq
  BA_PROP_NETWORK_NUMBER                            = 3098,     // NwkNr
  BA_PROP_ALARM_PRIO_LIMIT                          = 3099,     // PrlmAlm
  BA_PROP_TOMORROW                                  = 3100,     // Tmw
  BA_PROP_DAY_AFTER_TOMORROW                        = 3101,     // DayAfTmw
  BA_PROP_INTERVAL                                  = 3102,     // Ivl
  BA_PROP_LAST_MESSAGE                              = 3103,     // LstMsg
  BA_PROP_GROUP_MEMBERS                             = 3104,     // GrpMbrs
  BA_PROP_ROOM_MEMBERS                              = 3105,     // RMbrs
  BA_PROP_MENU_LINES                                = 3106,     // MenuLine
  BA_PROP_TIME_DELAY1                               = 3107,     // TiMonOn
  BA_PROP_TIME_DELAY2                               = 3108,     // TiMonOff
  BA_PROP_IO_STATISTICS                             = 3109,     // IOStc
  BA_PROP_DELAY_ON                                  = 3110,     // DlyOn
  BA_PROP_DELAY_OFF                                 = 3111,     // DlyOff
  BA_PROP_ALARM_COLLECTION_REF                      = 3113,     // AlmColr
  BA_PROP_ALARM_CLASS                               = 3114,     // AlmCl
  BA_PROP_SWITCH_UP                                 = 3115,     // StepUp
  BA_PROP_SWITCH_DOWN                               = 3116,     // StepDn
  BA_PROP_PRESENT_POWER                             = 3117,     // PrPwr
  BA_PROP_CONTROLLED_POWER                          = 3118,     // CtldPwr
  BA_PROP_IP_PARAMETERS                             = 3119,     // IPPar
  BA_PROP_DPX_SUBSTITUTION_VALUE                    = 3120,     // SbstVal
  BA_PROP_DPX_DESCRIPTION_LIST                      = 3121,     // DesList
  BA_PROP_DPX_ALARM_FUNCTION                        = 3122,     // AlmFnct
  BA_PROP_DPX_HEARTBEAT                             = 3123,     // Hrtbt
  BA_PROP_DPX_JITTER_SUPPRESS                       = 3124,     // OutTsh
  BA_PROP_DPX_RELIABILITY_ERROR_LIST                = 3125,     // ErList
  BA_PROP_DPX_POLLING_CYCLE                         = 3126,     // TiPln
  BA_PROP_DPX_EVENT_COUNT                           = 3127,     // EvtCnt
  BA_PROP_DPX_EXTENDED_NOTIFY                       = 3132,     // ExtNotif
  BA_PROP_DPX_LOG_STATUS                            = 3133,     // LogSta
  BA_PROP_DPX_SET_VALUE                             = 3134,     // SetVal
  BA_PROP_DPX_INTEGRAL_TIME                         = 3135,     // TiIntgl
  BA_PROP_DPX_NEUTRAL_ZONE                          = 3136,     // NeutZone
  BA_PROP_DPX_DERIVATIVE_TIME                       = 3137,     // TiDerv
  BA_PROP_DPX_TI0TO100                              = 3138,     // Ti0To100
  BA_PROP_DPX_TI100TO0                              = 3139,     // Ti100to0
  BA_PROP_DPX_LOOP_STATE                            = 3140,     // LoopSta
  BA_PROP_DPX_SETPOINT_RESOLUTION                   = 3141,     // SpRsl
  BA_PROP_DPX_SETPOINT_HIGH_VALUE                   = 3142,     // SpHi
  BA_PROP_DPX_SETPOINT_LOW_VALUE                    = 3143,     // SpLo
  BA_PROP_DPX_ENABLE_LOG                            = 3144,     // EnLog
  BA_PROP_DPX_ALARM_CLASS_TEXT                      = 3145,     // AlmClTxt
  BA_PROP_DPX_EXTENDED_COMMAND                      = 3146,     // EnSfCmd
  BA_PROP_DPX_FILE_OPERATION                        = 3148,     // FileOp
  BA_PROP_DPX_PULSECOUNT                            = 3149,     // Puc
  BA_PROP_DPX_DATA_TIME_STAMP                       = 3150,     // CtnTiStm
  BA_PROP_DPX_DATA_SOURCE                           = 3151,     // FileSrc
  BA_PROP_DPX_SERIALIZATION_IN_PROGRESS             = 3152,     // SlzInprc
  BA_PROP_DPX_AVAILABLE_FILE_STORAGE                = 3153,     // AvlFlsto
  BA_PROP_DPX_DEVICE_INFO_REFERENCE                 = 3154,     // DevInfor
  BA_PROP_DPX_SCALE_FACTOR                          = 3200,     // CnvFac
  BA_PROP_DPX_COUNT                                 = 3201,     // PucR
  BA_PROP_DPX_COUNT_BEFORE_RESET                    = 3202,     // PucBfCoR
  BA_PROP_DPX_COV_PERIOD                            = 3203,     // CovPrd
  BA_PROP_DPX_RESET_TIME                            = 3204,     // CorrTi
  BA_PROP_DPX_RESET_VALUE                           = 3205,     // CorrVal
  BA_PROP_DPX_TOTAL_COUNT                           = 3206,     // PucTot
  BA_PROP_DPX_UPDATE_TIME                           = 3207,     // PucUdtR
  BA_PROP_DPX_S_IN_PROCESS                          = 3210,     // Tra
  BA_PROP_DPX_S_FEEDBACK_VALUE                      = 3211,     // FbValAna
  BA_PROP_DPX_RESOLUTION                            = 3212,     // RslDspy
  BA_PROP_DPX_S_UNIT                                = 3213,     // EngUn
  BA_PROP_DPX_S_INACTIVE_TEXT                       = 3214,     // IactvSta
  BA_PROP_DPX_S_ACTIVE_TEXT                         = 3215,     // ActvSta
  BA_PROP_DPX_S_NUMBER_OF_STATES                    = 3216,     // NumOfSta
  BA_PROP_DPX_S_STATE_TEXT                          = 3217,     // StaTxts
  BA_PROP_DPX_S_RECIPIENT_LIST                      = 3218,     // DevRecp
  BA_PROP_DPX_S_BUFFER_SIZE                         = 3219,     // AlmBuf
  BA_PROP_DPX_S_RECORD_COUNT                        = 3220,     // AlmRecc
  BA_PROP_DPX_S_NOTIFICATION_THRESHOLD              = 3221,     // AlmNtfts
  BA_PROP_DPX_S_BCKUP_SRVR_LIST                     = 3222,     // BckUpSrv
  BA_PROP_DPX_S_OUT_OF_SERVICE                      = 3224,     // DevOpMod
  BA_PROP_DPX_S_ELAPSED_ACTIVE_TIME                 = 3225,     // OpHours
  BA_PROP_DPX_S_TIME_OF_ACTIVE_TIME_RESET           = 3226,     // TiStmRst
  BA_PROP_DPX_S_MINIMUM_ON_TIME                     = 3227,     // TiONMin
  BA_PROP_DPX_S_MINIMUM_OFF_TIME                    = 3228,     // TiOFFMin
  BA_PROP_DPX_S_COV_RESUBSCRIPTION_INTERVAL         = 3229,     // CovRsbci
  BA_PROP_DPX_ACTUAL_VALUE                          = 3230,     // ActlVal
  BA_PROP_DPX_S_RELIABILITY                         = 3231,     // RlbSta
  BA_PROP_DPX_S_STATUS_FLAGS                        = 3232,     // StaFlgs
  BA_PROP_DPX_ENABLE_CHANGE_OF_STATE_COUNT          = 3233,     // EnCosCnt
  BA_PROP_DPX_TECHNICAL_DESIGNATION                 = 3234,     // TechDesg
  BA_PROP_DS7_INPUT_PTP                             = 3300,     // InPTP
  
  BA_PROP_DS1_ENABLE_MEMORIZE_FUNCTION              = 4901,     // Enable MemScene
  BA_PROP_DS1_RESOLUTION                            = 5035,     // Resolution 
  BA_PROP_DS1_MIN_PRESENT_VALUE                     = 5036,     // PrValueMin
  BA_PROP_DS1_MAX_PRESENT_VALUE                     = 5037,     // PrValueMax
  BA_PROP_DS1_PRESENT_COMMAND                       = 5052,     // PrCmd
  BA_PROP_DS1_RELIABILITY                           = 5053,     // Rlblty
  BA_PROP_DS1_SIEMENS_URL                           = 5054,     // OpURI
  BA_PROP_DS1_LIST_OF_ITEM_ATTRIBUTES               = 5055,     // ItemAttrs
  BA_PROP_DS1_LIST_OF_ANNOTATIONS                   = 5056,     // AntnList
  BA_PROP_DS1_LIST_OF_OBJECT_PROPERTY_REF           = 5057,     // ObjPrList
  BA_PROP_DS1_GROUP_MASTER                          = 5058,     // GrpMaster
  BA_PROP_DS1_GROUP_MEMBERS                         = 5059,     // GrpMbrs
  BA_PROP_DS1_COLLECTED_DATA                        = 5060,     // ColData
  BA_PROP_DS1_GROUP_COMMAND                         = 5061,     // GrpCmd
  BA_PROP_DS1_GROUP_NUMBER                          = 5062,     // GrpNr
  BA_PROP_DS1_GROUP_CATEGORY_TEXT                   = 5063,     // GrpCatTxt
  BA_PROP_DS1_GROUP_CATEGORY                        = 5064,     // GrpCat
  BA_PROP_DS1_SOURCE_PROPERTY_ID                    = 5065,     // SrcPropId
  BA_PROP_DS1_SOURCE_OBJECT_TAG                     = 5066,     // SrcObjTag
  BA_PROP_DS1_MEMORIZE_VALUE                        = 5067,     // MemScene
  BA_PROP_DS1_RAMP_RATE                             = 5068,     // RampRate
  BA_PROP_DS1_BINARY_THRESHOLD                      = 5069,     // TshLgtBin
  BA_PROP_DS1_BINARY_PRESENT_VALUE                  = 5070,     // PrValBin
  BA_PROP_DS1_BURN_IN_TIME                          = 5071,     // OphBrnin
  BA_PROP_DS1_FADE_TIME                             = 5072,     // TiFade
  BA_PROP_DS1_IN_PROCESS                            = 5073,     // InPrgs
  BA_PROP_DS1_LIFECYCLE_STATE                       = 5074,     // OphSta
  BA_PROP_DS1_LIFE_TIME                             = 5075,     // OphExpd
  BA_PROP_DS1_MIN_ACTUAL_VALUE                      = 5076,     // ActlMin
  BA_PROP_DS1_MAX_ACTUAL_VALUE                      = 5077,     // ActlMax
  BA_PROP_DS1_COMPRESSION                           = 5078,     // Cmpress
  BA_PROP_DS1_CHECKSUM                              = 5079,     // CheckSum
  BA_PROP_DS1_FILE_FEATURES                         = 5080,     // FileFtrs
  BA_PROP_DS1_RT_SEQUENCE_COUNT                     = 5081,     // RntSeqCnt
  BA_PROP_DS1_ENGINEERING_COUNT                     = 5082,     // EngCnt
  BA_PROP_DS1_PROGRESS_VALUE                        = 5083,     // PrgsVal
  BA_PROP_DS1_CONTROL_COMMAND                       = 5084,     // CtlCmd
  BA_PROP_DS1_RELINQUISH_DEFAULT_CONTROL            = 5085,     // DefCmdCtl
  BA_PROP_DS1_SUBORDINATE_ATTRIBUTES                = 5086,     // SubAttr
  BA_PROP_DS1_PERIPHERAL_DEVICE_TYPE                = 5087,     // PrphlDev
  BA_PROP_DS1_ABORT_COMMAND                         = 5088,     // CancelCmd
  BA_PROP_DS1_LASTMOVING_DIRECTION                  = 5089,     // LstDirc
  BA_PROP_DS1_LIGHTING_VALUE                        = 5090,     // LgtVal
  BA_PROP_DS1_LIGHTING_STATE                        = 5091,     // LgtSta
  BA_PROP_DS1_IOADDRESS                             = 5092,     // IOAddress
  BA_PROP_DS1_PRESENT_PRIORITY                      = 5093,     // PrPrio
  BA_PROP_DS1_UPDATE_COUNT                          = 5094,     // UpdCnt
  BA_PROP_DS1_DEVICE_COMMAND                        = 5095,     // DevCmd
  BA_PROP_DS1_ORPHAN_LIST                           = 5096,     // OrphanLst
  BA_PROP_DS1_FIELD_BUS_INFO                        = 5097,     // FldbInfo
  BA_PROP_DS1_DEVICE_COMMAND_RESULT                 = 5098,     // DevCmdRlt
  BA_PROP_DS1_FIELD_BUS_COMMAND                     = 5099,     // FldbCmd
  BA_PROP_DS1_SERIAL_NUMBER                         = 5100,     // SerialNr
  BA_PROP_DS1_PERIPHERAL_DEVICE_INFO                = 5101,     // PrphlInfo
  BA_PROP_DS1_BA_PROTOTYPE                          = 5102,     // BAObjTyp
  BA_PROP_DS1_COMMISSIONING_INFO                    = 5103,     // ComgInfo
  BA_PROP_DS1_COMMISSIONING_STATE                   = 5104,     // ComgSta
  BA_PROP_DS1_CORRECTION_FACTOR                     = 5105,     // CorrFac
  BA_PROP_DS1_CORRECTION_OFFSET                     = 5106,     // CorrOfs
  BA_PROP_DS1_TRACKING_VALUE                        = 5107,     // TckVldVal
  BA_PROP_DS1_S1_DEVICE_FEATURES                    = 5108,     // DevFtrs
  BA_PROP_DS1_ITEM_LIST                             = 5109,     // ItemList
  BA_PROP_DS1_DATA_TIMESTAMP                        = 5110,     // CnfgTiStm
  BA_PROP_DS1_OBJECT_ATTRIBUTES                     = 5111,     // FwObjAttr
  BA_PROP_DS1_INTERNAL_OVERRIDE                     = 5112,     // FwInlOvr
  BA_PROP_DS1_AVAILABLE_FLASH                       = 5113,     // FwFlash
  BA_PROP_DS1_AVAILABLE_MEMORY                      = 5114,     // FwMem
  BA_PROP_ISA_EVENT_MESSAGE_TEXTS                   = 5117,     // ISAEvmsg
  BA_PROP_ISA_FUNCTION_SETS                         = 5118,     // ISAFnSet
  BA_PROP_ISA_VERSION                               = 5119,     // ISAVer
  BA_PROP_PPCL_STATEMENT                            = 5120,     // PpclStmt
  
  BA_PROP_DS1_SOURCE_DATA_TAG                       = 6000,
  BA_PROP_DS1_SOURCE_PROPERTY_TAG                   = 6001,
  BA_PROP_DS1_ITEM_VALUE_DATA_TAG                   = 6002,
  BA_PROP_DS1_ITEM_VALUE_OPERATION                  = 6003,
  BA_PROP_DS1_ITEM_VALUE_PRIORITY                   = 6004,
  BA_PROP_DS1_ITEM_VALUE                            = 6005,
  BA_PROP_DS1_ITEM_RELIABILITY                      = 6006,
  BA_PROP_DS1_COLLECTED_DATA_SEQ_NUMBER             = 6007,
  
  
  BA_PROP_ANYORDUMMY_VALUE                          = 0xFFFF // Any,dummy init. value
}

enum Object_Type {
  BA_OBJ_ANALOG_INPUT                              = 0,     // AI
  BA_OBJ_ANALOG_OUTPUT                             = 1,     // AO
  BA_OBJ_ANALOG_VALUE                              = 2,     // AVAL
  BA_OBJ_BINARY_INPUT                              = 3,     // BI
  BA_OBJ_BINARY_OUTPUT                             = 4,     // BO
  BA_OBJ_BINARY_VALUE                              = 5,     // BVAL
  BA_OBJ_CALENDAR                                  = 6,     // CLN
  BA_OBJ_COMMAND                                   = 7,     // CMD
  BA_OBJ_DEVICE                                    = 8,     // DEV
  BA_OBJ_EVENT_ENROLLMENT                          = 9,     // EVTERLMT
  BA_OBJ_FILE                                      = 10,     // FILE
  BA_OBJ_GROUP                                     = 11,     // GRP
  BA_OBJ_LOOP                                      = 12,     // LOOP
  BA_OBJ_MULTISTATE_INPUT                          = 13,     // MI
  BA_OBJ_MULTISTATE_OUTPUT                         = 14,     // MO
  BA_OBJ_NOTIFICATION_CLASS                        = 15,     // NOTIFCL
  BA_OBJ_PROGRAM                                   = 16,     // PGM
  BA_OBJ_SCHEDULE                                  = 17,     // SCHED
  BA_OBJ_AVERAGING                                 = 18,     // AVG
  BA_OBJ_MULTISTATE_VALUE                          = 19,     // MVAL
  BA_OBJ_TREND_LOG                                 = 20,     // TRNDLOG
  BA_OBJ_LIFE_SAFETY_POINT                         = 21,     // SFTYPNT
  BA_OBJ_LIFE_SAFETY_ZONE                          = 22,     // SFTYZONE
  BA_OBJ_ACCUMULATOR                               = 23,     // CI_ACC
  BA_OBJ_PULSE_CONVERTER                           = 24,     // CI
  BA_OBJ_EVENT_LOG                                 = 25,     // EVTLOG
  BA_OBJ_GLOBAL_GROUP                              = 26,     // GLOBGRP
  BA_OBJ_TREND_LOG_MULTIPLE                        = 27,     // TRNDLOGM
  BA_OBJ_LOAD_CONTROL                              = 28,     // LD_CTRL
  BA_OBJ_STRUCTURED_VIEW                           = 29,     // STR_VIEW
  BA_OBJ_ACCESS_DOOR                               = 30,     // AC_DOOR
  BA_OBJ_ACCESS_CREDENTIAL                         = 32,     // ACCCRED
  BA_OBJ_ACCESS_POINT                              = 33,     // ACCPOINT
  BA_OBJ_ACCESS_RIGHTS                             = 34,     // ACCRGHTS
  BA_OBJ_ACCESS_USER                               = 35,     // ACCUSER
  BA_OBJ_ACCESS_ZONE                               = 36,     // ACCZONE
  BA_OBJ_CREDENTIAL_DATA_INPUT                     = 37,     // CREDDI
  BA_OBJ_BITSTRING_VALUE                           = 39,     // BITSTRV
  BA_OBJ_CHARACTERSTRING_VALUE                     = 40,     // CHRSTRV
  BA_OBJ_DATE_PATTERN_VALUE                        = 41,     // DATPTNV
  BA_OBJ_DATE_VALUE                                = 42,     // DATV
  BA_OBJ_DATETIME_PATTERN_VALUE                    = 43,     // DTPTNV
  BA_OBJ_DATETIME_VALUE                            = 44,     // DATIVAL
  BA_OBJ_INTEGER_VALUE                             = 45,     // INTVAL
  BA_OBJ_LARGE_ANALOG_VALUE                        = 46,     // LGAVAL
  BA_OBJ_OCTETSTRING_VALUE                         = 47,     // OCTSTRGV
  BA_OBJ_POSITIVE_INTEGER_VALUE                    = 48,     // INTPOSVAL
  BA_OBJ_TIME_PATTERN_VALUE                        = 49,     // TIPTNVAL
  BA_OBJ_TIME_VALUE                                = 50,     // TIVAL
  BA_OBJ_HIERARCHY                                 = 200,    // Hierarchy 
  BA_OBJ_BLOCK                                     = 201,    // Block
  BA_OBJ_CMN_ALM								   = 214,	 // CMN_ALM
  BA_OBJ_DEVINFO								   = 217,	 // DEV_INFO
  BA_OBJ_DS1_GROUP_MEMBER                          = 256,     // GRPMBR
  BA_OBJ_DS1_GROUP_MASTER                          = 257,     // GRPMASTER
  BA_OBJ_DS1_BLINDS_OUTPUT                         = 258,     // BLSO
  BA_OBJ_DS1_BLINDS_INPUT                          = 259,     // BLSI
  BA_OBJ_DS1_LIGHT_OUTPUT_ANALOG                   = 260,     // LGTOA
  BA_OBJ_DS1_LIGHT_OUTPUT_BINARY                   = 261,     // LGTOB
  BA_OBJ_DS1_LIGHT_INPUT                           = 262,     // LGTI
  BA_OBJ_ANYORDUMMY_VALUE                          = 0xFFFF // Any,dummy init. value
}



enum Object_Prototype
{
    BA_PROT_ANALOGINPUT                            = 1,     // AI
    BA_PROT_ANALOGPROCESSVALUE                     = 2,     // APrcVal
    BA_PROT_ANALOGOUTPUT                           = 3,     // AO
    BA_PROT_BINARYINPUT                            = 4,     // BI
    BA_PROT_BINARYPROCESSVALUE                     = 5,     // BPrcVal
    BA_PROT_BINARYOUTPUT                           = 6,     // BO
    BA_PROT_MULTISTATEINPUT                        = 7,     // MI
    BA_PROT_MULTISTATEPROCESSVALUE                 = 8,     // MPrcVal
    BA_PROT_MULTISTATEOUTPUT                       = 9,     // MO
    BA_PROT_DEVICEOBJECT                           = 10,     // DevObj
    BA_PROT_ANALOGCONFIGVALUE                      = 11,     // ACnfVal
    BA_PROT_ANALOGCALCULATEDVALUE                  = 12,     // ACalcVal
    BA_PROT_BINARYCONFIGVALUE                      = 13,     // BCnfVal
    BA_PROT_BINARYCALCULATEDVALUE                  = 14,     // BCalcVal
    BA_PROT_MULTISTATECONFIGVALUE                  = 15,     // MCnfVal
    BA_PROT_MULTISTATECALCULATEDVALUE              = 16,     // MCalcVal
    BA_PROT_UNSIGNEDCONFIGVALUE                    = 17,     // UCnfVal
    BA_PROT_LIGHTINPUT                             = 18,     // LgtIn
    BA_PROT_LIGHTOUTPUTANALOG                      = 19,     // LgtAOut
    BA_PROT_LIGHTOUTPUTBINARY                      = 20,     // LgtBOut
    BA_PROT_BLINDSINPUT                            = 22,     // BlsIn
    BA_PROT_BLINDSOUTPUT                           = 23,     // BlsOut
    BA_PROT_PERIPHERALDEVICE                       = 24,     // PrphDev
    BA_PROT_FIELDBUSMANAGEMENT                     = 25,     // FldBusMgmt
    BA_PROT_FILEOBJECT                             = 31,     // FileObj
    BA_PROT_COMMAND                                = 32,     // CmdObj
    BA_PROT_GROUPMASTER                            = 33,     // GrpMaster
    BA_PROT_GROUPMEMBER                            = 34,     // GrpMbr
    BA_PROT_EVENTLOG                               = 35,     // EvtLog
    BA_PROT_TRENDLOG_SIMPLE                        = 36,     // TrndLogS
    BA_PROT_NOTIFICATIONCLASS                      = 37,     // NotifClass
    BA_PROT_VNOBJECTFUNCTIONAL                     = 40,     // FnctView
    BA_PROT_VNOBJECTCOLLECTION                     = 41,     // ColView
    BA_PROT_VNOBJECTDEVICE                         = 42,     // DevView
    BA_PROT_VNOBJECTNETWORK                        = 43,     // NwkView
    BA_PROT_VNOBJECTAREA                           = 44,     // AreaView
    BA_PROT_ANYORDUMMY_VALUE                          = 0xFFFF // Any,dummy init. value
}

enum Write_Priority
{
    BA_PRIO_MANUAL_LIFE_SAFETY                     = 1,  
    BA_PRIO_MANUAL_AUTOMATIC_LIFE_SAFETY           = 2,
    BA_PRIO_AVAILABLE3                             = 3,
    BA_PRIO_AVAILABLE4                             = 4,
    BA_PRIO_CRITICAL_EQUIPT_CTRL                   = 5,
    BA_PRIO_MIN_ON_OFF                             = 6,
    BA_PRIO_AVAILABLE7                             = 7,
    BA_PRIO_MANUAL_OPERATOR                        = 8,
    BA_PRIO_AVAILABLE9                             = 9,
    BA_PRIO_AVAILABLE10                            = 10,
    BA_PRIO_AVAILABLE11                            = 11,
    BA_PRIO_AVAILABLE12                            = 12,
    BA_PRIO_AVAILABLE13                            = 13,
    BA_PRIO_AVAILABLE14                            = 14,
    BA_PRIO_AVAILABLE15                            = 15,
    BA_PRIO_AVAILABLE16                            = 16
}

enum BAPA_READACCESS_TYPE
{
    BA_RA_NOACCESS				   = 0,     // no access /not readable
    BA_RA_INTERNAL	                	   = 1,	    // internal
    BA_RA_EXTENDED_SERVICE			   = 2,	    // extended service
    BA_RA_BASIC_SERVICE				   = 3,	    // basic service
    BA_RA_ADMINISTRATOR				   = 4,	    // administrator
    BA_RA_EXTENDED_OPERATION			   = 5,	    // extended operation
    BA_RA_STANDARD_OPEARATION			   = 6,	    // standard operation
    BA_RA_BASIC_OPERATION			   = 7	    // basic operation
}

enum BAPA_WRITEACCESS_TYPE
{
    BA_WR_NOACCESS				   = 0,	    // no access /not readable
    BA_WR_INTERNAL				   = 1,	    // internal
    BA_WR_EXTENDED_SERVICE			   = 2,	    // extended service
    BA_WR_BASIC_SERVICE				   = 3,	    // basic service
    BA_WR_ADMINISTRATOR				   = 4,	    // administrator
    BA_WR_EXTENDED_OPERATION			   = 5,	    // extended operation
    BA_WR_STANDARD_OPEARATION			   = 6,     // standard operation
    BA_WR_BASIC_OPERATION			   = 7	    // basic operation
}

struct AccessInfo
{
  1: BAPA_READACCESS_TYPE readAccess,
  2: BAPA_WRITEACCESS_TYPE writeAccess
}

struct TypeInfo
{
  1: string defValue, // for all data type
  2: string minValue,  // real
  3: string maxValue,  // real
  4: string resolution, // real
  5: i32 minLength, // for string data type. Query - Can have string type instead of i32?
  6: i32 maxLength, // for string data type
  7: i32 arrayIndex, // for standard datatypes array index
  8: i32 stringIndex, 
  9: string unit,
  10: i32 textGroup
}

struct Property_Info
{
  1: BA_DATA_TYPE data_type,
  2: AccessInfo accessInfo,
  3: TypeInfo typeInfo
}

struct PropertyDesc_Info
{
  1: Property_Type propertyType,
  2: Property_Info propertyInfo
}

/*
 * use Object_Id instead of BAObjectRef [T060.S100-3D010]
 */
struct Object_Id {
  1: i32 device_instance,     // 22 bit instance number, type is fix => DEV
  2: Object_Type object_type, // 10 bit object type
  3: i32 object_instance,     // 22 bit instance number
}

/*
 * The User Object stored within Database
 */
//@TODO align with DESIGO user profile requirements 
struct User {
  1: i32 id = 0, // 0 = not autenticated
  2: string username,
  3: string password,
  5: i16 autologin = 0,
  6: string firstname,
  7: string lastname,
  8: string language = "en",
  9: string country = "US",
 10: string web_theme = "siemens-2004",
 11: string email,
 12: string comment 
}

struct FileTransferLocation{
  1: string name,
  2: string path,
  3: string localpath,
  4: string description,
  5: string comment
}

enum PasswordType {
	PW_PLAIN    = 0,
	PW_MD5		= 1
    /* add PW_SHA in the future */
}

struct Password {
  1: string password,
  2: PasswordType type
}

struct Location {
  1: string name,
  2: string description,
  3: string password,
  4: Object_Id home,
  5: list<Object_Id> systemNavigationEntries
}

struct AuthenticationResult {
  1: required string authenticationToken,
  2: optional User user
  3: optional Location location
}


/**
 * This Enumeration MUSS be the same as ES7CpuState in S7_CPU_STATE.h
 */
enum ControlProgramState
{
  S7_STOP_UPDATE   = 1,  // mapped to V7_STATE_STOP_Update   (0x01)  firmware loading (not implemented by v7)
  S7_STOP_RESET    = 2,  // mapped to V7_STATE_STOP_Reset    (0x02)  stop state in which the OVS system is being set to default state
  S7_STOP_INIT     = 3,  // mapped to V7_STATE_STOP_Init     (0x03)  stop state in which the OVS system is being constructed
  S7_STOP_INTERNAL = 4,  // mapped to V7_STATE_STOP_Internal (0x04)  stop state in which a valid OVS system exists
  S7_START_OB102   = 5,  // mapped to V7_STATE_START_OB102   (0x05)  Performing Cold Start
  S7_START_OB100   = 6,  // mapped to V7_STATE_START_OB100   (0x06)  Performing Complete Restart
  S7_START_OB101   = 7,  // mapped to V7_STATE_START_OB101   (0x07)  Performing Hot Start (not implemented by v7)
  S7_RUN           = 8,  // mapped to V7_STATE_RUN           (0x08)  Running
  S7_HALT          = 10, // mapped to V7_STATE_HALT          (0x0A)  Running CPU is paused at a breakpoint
  S7_DEFECTIVE     = 13, // mapped to V7_STATE_DEFECTIVE     (0x0D)  CPU is in an unknown state
  S7_POWER_OFF     = 15, // mapped to V7_STATE_POWER_OFF     (0x0F)  Power off
  NO_S7            = 255,// Still no CPU created
}



/**
 * Enumeration of Application State, this is product specific.
 */
enum DeviceState
{
  DEV_RUN           = 1,  
  DEV_HALT          = 2,
  DEV_RESTART       = 3,
  DEV_RESET         = 4,
}

struct Model{
    1: string locationDescription;
}

//Implemented by Patni OSD for Desigo TP & Web Project

enum Result_Code
{
	RESULT_SUCCESS 				    			         = 1,
	RESULT_LOCATION_AUTHENTICATION_REQUIRED  = 2,
	RESULT_INVALID_ENTRY_ID 					       = 3,
	RESULT_USER_AUTHENTICATION_REQUIRED 		 = 4,
	RESULT_INVALID_CRENDENTIALS 				     = 5,
	RESULT_IMAGE_ERROR 							         = 6,
	RESULT_COMMAND_VALUE_ERROR 					     = 7,
	RESULT_COMMAND_SCHEDULE_ERROR 				   = 8,
	RESULT_COMMAND_TREND_ERROR 					     = 9,
	RESULT_XML_WRITING_FAILED 					     = 10,
	RESULT_OBJECT_NOT_FOUND 					       = 11,
	RESULT_OBJECT_DATA_NOT_READY			       = 12,
	RESULT_PHASE_LIMIT_EXCEEDED              = 13,
	RESULT_SPECIAL_EVENT_LIMIT_EXCEEDED      = 14,
	RESULT_PROCESS_ERROR				             = 15,
	RESULT_INVALID_ELEMENT_NUMBER            = 16,   // RUT invalid element number in ElementId (VIEWID(CVC_ID + CV_ID) + ELEMENT_NUM)
	RESULT_COMMAND_MEMORIZE_FAILED           = 17    // RUT Memorize Scene Failure
}

enum Command_Type
{

	CMD_GET_MODEL_UPDATES 		  = 1,
	CMD_AUTHENTICATION_LOCATION = 2,
	CMD_USER_LOGIN 				      = 3,
	CMD_USER_LOGOUT 			      = 4,
	CMD_SELECT_VIEW 			      = 5,
	CMD_SELECT_FUNCTION 		    = 6, 
	CMD_COMMAND_VALUE			      = 7,
	CMD_MODIFY_SERVER_SETTINGS  = 8,
	CMD_SCHEDULE 				        = 9,
	CMD_TREND 					        = 10,
	CMD_ALARM_ACKNOWLEDGE		    = 11 
}

enum CoreFunction
{
  CORE_PLANT_VIEW       = 0,
  CORE_FAVOURITES       = 1,
  CORE_ALARMS           = 2,
  CORE_SCHEDULE         = 3,
  CORE_TREND            = 4,
  CORE_SETTINGS         = 5,
  CORE_DEFAULT		      = 6
}

enum AutoLogoutTime
{
	ALT_5MIN	= 5,
	ALT_10MIN	= 10,
	ALT_15MIN	= 15,
	ALT_30MIN	= 30,
	ALT_45MIN	= 45,
	ALT_60MIN	= 60
}
enum ScreenSaverTiOut
{
  SST_5MIN	  = 05,
	SST_10MIN	  = 10,
	SST_15MIN	  = 15,
	SST_30MIN	  = 30,
	SST_45MIN	  = 45,
	SST_60MIN	  = 60,
	SST_DEFAULT = 15
}
enum NavigBarTiOut
{
        NBT_0FF         =  0;
        NBT_5MIN	=  5,
	NBT_10MIN	= 10,
	NBT_15MIN	= 15,
	NBT_30MIN	= 30,
	NBT_45MIN	= 45,
	NBT_60MIN	= 60,
	NBT_DEFAULT     = 30
}
enum KeyBoardLayout
{
	KBL_STANDARD   = 0,
	KBL_RUSSIAN    = 1   
}

enum DateFormat
{
	DF_DDMMYYYY_DOT      = 0,
	DF_DDMMYYYY_FSLASH   = 1,
	DF_DDMMYYYY_DASH     = 2,
	DF_YYYYMMDD_DOT      = 3,
	DF_YYYYMMDD_FSLASH   = 4,
	DF_YYYYMMDD_DASH     = 5,
	DF_MMDDYYYY_DASH     = 6,
	DF_MMDDYYYY_FSLASH   = 7
}

enum TimeFormat
{
	TF_24H	= 0,
	TF_12H	= 1
}

enum Style
{
	STYLE_DEFAULT		= 0,
	STYLE_INVISIBLE		= 1,
	STYLE_RED			= 2,
	STYLE_GREEN			= 3,
	STYLE_YELLOW		= 4,
	STYLE_RED_BOLD		= 5,
	STYLE_GREEN_BOLD	= 6,
	STYLE_YELLOW_BOLD	= 7,
	STYLE_BLUE    		= 8,
	STYLE_BLUE_BOLD		= 9
}

enum Indicator
{
    // Alarm States
    ALARM_ACKNOWLEDGE_NEEDED      = 1,
    ALARM_RESET_NEEDED            = 2,
    ALARM_NOTHING_NEEDED          = 3,
    NO_ALARM_ACKNOWLEDGE_NEEDED   = 4,
    NO_ALARM_RESET_NEEDED         = 5,
 
    // OperationMode
    OVERRIDDEN                    = 6,
    OUT_OF_SERVICE                = 7,
    LIFE_SAFETY                   = 8,
    CRITICAL_OPERATION            = 9,
    ON_OFF_DELAY                  = 10,
    MANUAL_SWITCH                 = 11,
    SYSTEM_OPERATOR               = 12,
    
    // Transient Mode
    TRANSIENT                     = 13
}

enum AlarmFunction
{
	NONE = 0,
	ACKNOWLEDGE = 1,
	RESET = 2,
	ACKNOWLEDGE_RESET = 3
}
enum Anchor
{
	ANCHOR_TOP_LEFT = 0,
	ANCHOR_BOTTOM_LEFT = 1,
	ANCHOR_TOP_RIGHT = 2,
	ANCHOR_BOTTOM_RIGHT = 3,
	ANCHOR_TOP_CENTER = 4,                      //Added in RUT
	ANCHOR_BOTTOM_CENTER = 5,                   //Added in RUT
	ANCHOR_CENTER =6                            //Added in RUT
}

enum RelativePosition                                  
{
	INVISIBLE      = 0,
    POSITION_LEFT  = 1,
    POSITION_ABOVE = 2,
    POSITION_BELOW = 3              //Added for RUT
}

enum ManipulatorType
{
	SETVALUE						=0,
	SETSIZE							=1,
	NAVIGATE_TO						=2,
	NAVIGATE_TO_COLLECTION_MEMBER	=3,
	NAVIGATE_BACK
}

enum Mode 
{
	MANUAL		= 0,
	AUTOMATIC	= 1
}

enum GraphicPageElementType
{
    PANE         = 0,
    LINK         = 1,
    PROCESSVALUE = 2,
    SETTINGS     = 3
}

enum BehaviorType
{
    NORMAL                = 0,
    TRIGGER_FEEDBACK      = 1,
    TRIGGER_TOGGLE        = 2,
    SCENE                 = 3,
    LGT_RELATIVE          = 4,
    LGT_ABSOLUTE          = 5,
    BLIND                 = 6
}

struct AuthenticationLocationParameters
{
	1: string locationName,
	2: string password

}
struct UserLoginParameters
{
	1: string UserName,
	2: string password
}

struct GetModelUpdateParameters 
{
	1: bool keepAlive
}

struct SelectFunctionParameters
{
    1: CoreFunction currentFunction
}

struct SelectViewParamaters
{
	1: string viewId
}

struct Commandvalue
{
	1:optional i32 Discretevalue,
	2:optional double Analogvalue
}

enum CommandValueType
{
  CMD_VALUE  = 1,
  CMD_MEMORIZE       = 2,
  CMD_LIGHT_CONTROL  = 3,
  CMD_BLIND_CONTROL  = 4
}

enum LightOperation 
{
  LIGHT_OP_STOP           = 0,
  LIGHT_OP_START_DIM_UP   = 1,
  LIGHT_OP_START_DIM_DOWN = 2,
  LIGHT_OP_STEP_UP        = 3,
  LIGHT_OP_STEP_DOWN      = 4,
  LIGHT_OP_SWITCH_ON      = 5,
  LIGHT_OP_SWITCH_OFF     = 6,
  LIGHT_OP_GOTO_LEVEL     = 7
}

struct LightControlParameters
{
  1: LightOperation operation,
  2: optional double value
}

enum BlindOperation 
{
  BLIND_OP_STOP                     = 0,
  BLIND_OP_MOVE_UP                  = 1,
  BLIND_OP_MOVE_DOWN                = 2,
  BLIND_OP_STOP_OR_STEP_UP          = 3,
  BLIND_OP_STOP_OR_STEP_DOWN        = 4,
  BLIND_OP_GOTO_HEIGHT              = 5,
  BLIND_OP_GOTO_ANGLE               = 6,
  BLIND_OP_GOTO_POSITION            = 7,
  BLIND_OP_GOTO_PREDEFINED_POSITION = 8,
  BLIND_OP_NO_OPERATION             = 9
}

struct BlindControlParameters
{
  1: BlindOperation operation,
  2: optional double height,
  3: optional double angle,
  4: optional i32 predefinedPos
}

struct CommandValueParameters
{
	1: optional i32 elementId,
	2: optional Commandvalue commandvalue,
	3: optional CommandValueType commandValueType, 
  4: optional string placeableElementId,
  5: optional LightControlParameters lightControlParameters,
  6: optional BlindControlParameters blindControlParameters
}

struct ServerSettingParameters
{
	1: optional string languageSymbol,
	2: optional TimeFormat timeFormat,
	3: optional DateFormat dateFormat,
	4: optional KeyBoardLayout keyboardLayout,
	5: optional AutoLogoutTime autoLogoutTime,
	6: optional NavigBarTiOut  navigBarTiOut,
	7: optional ScreenSaverTiOut screenSaverTiOut,	
	
}

struct TDate
{
	1: i16  year,
	2: byte month,
	3: byte day,
}

struct ServiceCommand
{
	1: Command_Type commandType,
	2: optional AuthenticationLocationParameters authenticateLocationParameters,
	3: optional UserLoginParameters userLoginParameters,
    4: optional GetModelUpdateParameters getModelUpdateParameters,
	5: optional SelectFunctionParameters selectFunctionParameters,
	6: optional SelectViewParamaters selectViewParameters,
	7: optional CommandValueParameters commandValueParameters,
	8: optional Scheduler.SchedulerParameters schedulerParameters,
	9: optional ServerSettingParameters serverSettingParameters,
   10: optional Trend.TrendParameters trendParameters
}

struct Value
{
 	1: optional bool boolValue,
 	2: optional i32 intValue,
 	3: optional double doubleValue,
 	4: optional string stringValue
}

struct ManipulatorCommand
{
	1: ManipulatorType manipulatortype,
	2: optional string attribute,
	3: optional Value value,
	4: optional i32 size_index
}

struct ModelUpdate
{
	1: string viewstate,
	2: list<ManipulatorCommand> updateinstruction
}

struct LogRecord
{
 	1: i32 timeStamp,
 	2: double value  
}

struct ServiceResult
{
	1: optional string newSessionId,
	2: Result_Code resultCode,
	3: optional ModelUpdate modelUpdate,
	4: optional list<Value> result,
	5: optional list<LogRecord> logRecord, //TODO: use ModelUpdate
	6: optional Scheduler.SchedulerResult schedulerResult,
}

enum PaneKind                          // Added For RUT
{
	PANE_APPLICATION = 0,
	PANE_PAGES = 1,
	PANE_STATUS = 2,
	PANE_CONTENT = 3,
 	PANE_NAVIGATION = 4
}

enum ElementType                       // Added For RUT
{
    ELEM_TYPE_MODIFY_TP                               = 0,
    ELEM_TYPE_MODIFY_RUT1                             = 1,
    ELEM_TYPE_MODIFY_RUT2                             = 2,
    ELEM_TYPE_TRIGGER                                 = 3,
    ELEM_TYPE_READ_ONLY                               = 4
    
}
enum ElementSize                          // Added For RUT
{
	ELEM_SIZE_NORMAL = 0,
	ELEM_SIZE_STATUSBAR = 1
}
