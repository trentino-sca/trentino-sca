/*
 * a simple service providing basic data of a device
 *
 * sample usage:
 * simple web interface, snmpd reads its basic configuration
 *
 * Roger Meier <r.meier@siemens.com>
 */

namespace java com.siemens.bt.error
namespace cpp siemens.bt.error
namespace csharp Siemens.BT.Error
namespace py siemens.bt.error

include "Types.thrift"


/**
 * Numeric codes indicating the type of error that occurred on the
 * service.
 * <dl>
 *   <dt>UNKNOWN</dt
 *     <dd>No information available about the error</dd>
 *   <dt>BAD_DATA_FORMAT</dt>
 *     <dd>The format of the request data was incorrect</dd>
 *   <dt>PERMISSION_DENIED</dt>
 *     <dd>Not permitted to perform action</dd>
 *   <dt>INTERNAL_ERROR</dt>
 *     <dd>Unexpected problem with the service</dd>
 *   <dt>DATA_REQUIRED</dt>
 *     <dd>A required parameter/field was absent</dd>
 *   <dt>LIMIT_REACHED</dt>
 *     <dd>Operation denied due to data model limit</dd>
 *   <dt>QUOTA_REACHED</dt>
 *     <dd>Operation denied due to user storage limit</dd>
 *   <dt>INVALID_AUTH</dt>
 *     <dd>Username and/or password incorrect</dd>
 *   <dt>AUTH_EXPIRED</dt>
 *     <dd>Authentication token expired</dd>
 *   <dt>DATA_CONFLICT</dt>
 *     <dd>Change denied due to data model conflict</dd>
 *   <dt>ENML_VALIDATION</dt>
 *     <dd>Content of submitted note was malformed</dd>
 *   <dt>SHARD_UNAVAILABLE</dt>
 *     <dd>Service shard with account data is temporarily down</dd>
 * </dl>
 */
enum ErrorCode {
  UNKNOWN = 1,
  BAD_DATA_FORMAT = 2,
  PERMISSION_DENIED = 3,
  INTERNAL_ERROR = 4,
  DATA_REQUIRED = 5,
  LIMIT_REACHED = 6,
  QUOTA_REACHED = 7,
  INVALID_AUTH = 8,
  AUTH_EXPIRED = 9,
  DATA_CONFLICT = 10,
  ENML_VALIDATION = 11,
  SHARD_UNAVAILABLE = 12
}


/**
 * This exception is thrown by different procedures when a call fails as a result of 
 * a problem that a user may be able to resolve.  For example, if the user
 * attempts to add a note to their account which would exceed their storage
 * quota, this type of exception may be thrown to indicate the source of the
 * error so that they can choose an alternate action.
 *
 * This exception would not be used for internal system errors that do not
 * reflect user actions, but rather reflect a problem within the service that
 * the user cannot resolve.
 *
 * errorCode:  The numeric code indicating the type of error that occurred.
 *   must be one of the values of ErrorCode.
 *
 * parameter:  If the error applied to a particular input parameter, this will
 *   indicate which parameter.
 */
exception UserException {
  1:  required  ErrorCode errorCode,
  2:  optional  string parameter
}


/**
 * This exception is thrown by different procedures when a call fails as a result of
 * an a problem in the service that could not be changed through user action.
 *
 * errorCode:  The numeric code indicating the type of error that occurred.
 *   must be one of the values of ErrorCode.
 *
 * message:  This may contain additional information about the error
 */
exception SystemException {
  1:  required  ErrorCode errorCode,
  2:  optional  string message
}


/**
 * This exception is thrown by EDAM procedures when a caller asks to perform
 * an operation that does not exist.  This may be thrown based on an invalid
 * primary identifier (e.g. a bad GUID), or when the caller refers to an object
 * by another unique identifier (e.g. a User's email address).
 *
 * identifier:  the object identifier that was not found on the server.
 *
 * key:  the value passed from the client in the identifier, which was not
 *   found.  E.g. the GUID of an object that was not found.
 */
exception NotFoundException {
  1:  optional  string identifier,
  2:  optional  string key
}

enum BA_ERROR_CLASS
{
    BA_ERR_CLASS_DEVICE            =    0,
    BA_ERR_CLASS_OBJECT            =    1,
    BA_ERR_CLASS_PROPERTY          =    2,
    BA_ERR_CLASS_RESOURCES         =    3,
    BA_ERR_CLASS_SECURITY          =    4,
    BA_ERR_CLASS_SERVICES          =    5,
    BA_ERR_CLASS_VT                =    6,
    BA_ERR_CLASS_LAST_KNOWN        =    6,
    BA_ERR_CLASS_ASHRAE_MAX        =    63,
    BA_ERR_CLASS_FIRST_PROPRIETARY =    64,
    BA_ERR_CLASS_MAX               = 65535
}

enum BA_ERROR_CODE
{
    BA_ERR_CODE_OTHER = 0,
    BA_ERR_CODE_AUTHENTICATION_FAILED =    1,
    BA_ERR_CODE_CONFIG_IN_PROGRESS =       2,
    BA_ERR_CODE_DEVICE_BUSY =              3,
    BA_ERR_CODE_DYN_CREATION_NOT_SUPP =    4,
    BA_ERR_CODE_FILE_ACCESS_DENIED =       5,
    BA_ERR_CODE_WRONG_SECURITY_LEVELS =    6,
    BA_ERR_CODE_INCONSISTENT_PARAMS =      7,
    BA_ERR_CODE_INVALID_PARAMETERS =       7,
        /* bad name; leave in for compatibility reasons */
    BA_ERR_CODE_INVALID_SELECTION_CRIT =   8,
    BA_ERR_CODE_INVALID_DATA_TYPE =        9,
    BA_ERR_CODE_INVALID_FILE_ACCESS =      10,
    BA_ERR_CODE_INVALID_FILE_START_POS =   11,
    BA_ERR_CODE_INVALID_OPERATOR_NAME =    12,
    BA_ERR_CODE_INVALID_PARAMETER_TYPE =   13,
    BA_ERR_CODE_INVALID_TIME_STAMP =       14,
    BA_ERR_CODE_KEY_GENERATION_ERROR =     15,
    BA_ERR_CODE_MISSING_PARAMETER =        16,
    BA_ERR_CODE_NO_OBJS_OF_SPEC_TYPE =     17,
    BA_ERR_CODE_OBJECT_NOT_FOUND =         17,
        /* obsolete; use BA_ERR_CODE_UNKNOWN_OBJECT (maps to BACnet unknown-object)
         * or BA_ERR_CODE_NO_OBJS_OF_SPEC_TYPE (maps to BACnet no-objects-of-
         * specified-type)
         */
    BA_ERR_CODE_NO_SPACE_FOR_OBJECT =      18,
    BA_ERR_CODE_NO_SPACE_FOR_ELEMENT =     19,
    BA_ERR_CODE_NO_SPACE_TO_WRITE_PROP =   20,
    BA_ERR_CODE_NO_VT_SESSIONS_AVAIL =     21,
    BA_ERR_CODE_PROP_IS_NOT_A_LIST =       22,
    BA_ERR_CODE_OBJ_DELETION_DENIED =      23,
    BA_ERR_CODE_OBJ_ID_ALREADY_EXISTS =    24,
    BA_ERR_CODE_OPERATIONAL_PROBLEM =      25,
    BA_ERR_CODE_PASSWORD_FAILURE =         26,
    BA_ERR_CODE_READ_ACCESS_DENIED =       27,
    BA_ERR_CODE_SECURITY_NOT_SUPPORTED =   28,
    BA_ERR_CODE_SERVICE_REQUEST_DENIED =   29,
    BA_ERR_CODE_TIMEOUT =                  30,
    BA_ERR_CODE_UNKNOWN_OBJECT =           31,
    BA_ERR_CODE_UNKNOWN_PROPERTY =         32,
    BA_ERR_CODE_UNKNOWN_VT_CLASS =         34,
    BA_ERR_CODE_UNKNOWN_VT_SESSION =       35,
    BA_ERR_CODE_UNSUPPORTED_OBJ_TYPE =     36,
    BA_ERR_CODE_VALUE_OUT_OF_RANGE =       37,
    BA_ERR_CODE_VT_SESSION_CLOSED =        38,
    BA_ERR_CODE_VT_SESSION_TERM_FAILED =   39,
    BA_ERR_CODE_WRITE_ACCESS_DENIED =      40,
    BA_ERR_CODE_CHAR_SET_NOT_SUPPORTED =   41,
    BA_ERR_CODE_INVALID_ARRAY_INDEX =      42,
    BA_ERR_CODE_COV_SUBS_FAILED =          43,
    BA_ERR_CODE_NOT_COV_PROPERTY =         44,
    BA_ERR_CODE_OPTIONAL_FUNC_NOT_SUPP =   45,
    BA_ERR_CODE_INVALID_CONFIG_DATA =      46,
    BA_ERR_CODE_DATATYPE_NOT_SUPPORTED =   47,    /* Add-135a-2001 */
    BA_ERR_CODE_DUPLICATE_NAME =           48,    /* Add-135c-2001 */
    BA_ERR_CODE_DUPLICATE_OBJECT_ID =      49,    /* Add-135c-2001 */
    BA_ERR_CODE_PROPERTY_IS_NOT_AN_ARRAY = 50,    /* Add-135c-2001 */
    BA_ERR_CODE_VALUE_NOT_INITIALIZED =    72,    /* Add-135?-200? */
    BA_ERR_CODE_INVALID_EVENT_STATE =      73,    /* Add-135d-2004(11) */
    BA_ERR_CODE_NO_ALARM_CONFIGURED =      74,    /* Add-135d-2004(11) */
    BA_ERR_CODE_LOG_BUFFER_FULL =          75,    /* Add-135d-2004(11) */
    BA_ERR_CODE_LIST_ELEMENT_NOT_FOUND=    81,    /*Add -135-2008-Errata-2010-11*/

    BA_ERR_CODE_LAST_KNOWN =               81,
    BA_ERR_CODE_ASHRAE_MAX =              255,
    BA_ERR_CODE_FIRST_PROPRIETARY =       256,
    BA_ERR_CODE_MAX =                   65535
}

exception BaException {
  1: string 				 message,
  2: Types.Object_Id obj_id,
}
