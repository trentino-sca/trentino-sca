// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
// http://trentino.sourceforge.net/
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
// **********************************************************************************

#ifndef TrentinoUtilsLoggingH
#define TrentinoUtilsLoggingH

//standard
#include <cstdio>

//*************************************************************************************************
//                             LOG4PLUS_LOGGERNAME
//*************************************************************************************************
//! Can be redefined to inject an optional logger.
//*************************************************************************************************
#define LOG4PLUS_LOGGERNAME nullptr

//*************************************************************************************************
//                             TRENTINO_UTILS_LOGGING_MSG_TAG
//*************************************************************************************************
//! Tag to check if a kind of message should be printed or not. 
//! Using constantExpression pattern to remove in release builds.
//! \param[in] tag The messagetype(tag) to log.
//! \param[in] on Determines if type(tag) of message is shown or not. 
//! Complete expression is removed in release builds.
//*************************************************************************************************
#define TRENTINO_UTILS_LOGGING_MSG_TAG(tag, on)\
static inline bool TrentinoUtilsLogging##tag() \
{ return Trentino::Utils::constantExpression<bool>(on); }

//*************************************************************************************************
//                              TRENTINO_UTILS_LOGGING_MSG
//*************************************************************************************************
//! logMessage can  be removed due return value constant expression function.
//! \param[in] tag The messagetype(tag) to log.
//! \param[in] message The message which should be logged.
//! \param[in] ... Variable argumentlist.
//*************************************************************************************************
#ifdef TRENTINO_LOGGING

   #ifdef WIN32
      #define TRENTINO_UTILS_LOGGING_MSG(tag, message, ...)\
      if(TrentinoUtilsLogging##tag() == true) \
         TRENTINO_UTILS_LOGGING_MSG_(tag, message, ##__VA_ARGS__); 
   #else // WIN32
      #define TRENTINO_UTILS_LOGGING_MSG(tag, message...)\
      if(TrentinoUtilsLogging##tag() == true) \
         TRENTINO_UTILS_LOGGING_MSG_(tag, message); 
   #endif // WIN32

#else // TRENTINO_LOGGING

   #ifdef WIN32
      #define TRENTINO_UTILS_LOGGING_MSG(tag, message, ...) (void) message
   #else // WIN32
      #define TRENTINO_UTILS_LOGGING_MSG(tag, message...) (void) message
   #endif // WIN32

#endif // TRENTINO_LOGGING

//! can be undefined, for testing purposes etc.
//! \todo redirecting should be done later in logger itself
#define TRENTINO_UTILS_LOGGING_INTERNALFUNC Trentino::Utils::Logging::Logger::logMessage

//*************************************************************************************************
//                              TRENTINO_UTILS_LOGGING_MSG_
//*************************************************************************************************
//! Main internal macro to build up logMessage.
//! \param[in] tag The messagetype(tag) to log.
//! \param[in] message The message which should be logged.
//! \param[in] ... Variable argumentlist.
//*************************************************************************************************
#ifdef WIN32
#define TRENTINO_UTILS_LOGGING_MSG_(tag, message, ...)\
{\
char traceBuffer##__LINE__[512];\
sprintf_s((char*)traceBuffer##__LINE__, 512, message, __VA_ARGS__ );\
TRENTINO_UTILS_LOGGING_INTERNALFUNC\
   (LOG4PLUS_LOGGERNAME, #tag, traceBuffer##__LINE__, __FUNCTION__, __FILE__, __LINE__ - 4);\
}
#else
#define TRENTINO_UTILS_LOGGING_MSG_(tag, message...)\
{\
char traceBuffer##__LINE__[512];\
   sprintf((char*)traceBuffer##__LINE__, message );\
TRENTINO_UTILS_LOGGING_INTERNALFUNC\
   (LOG4PLUS_LOGGERNAME, #tag, traceBuffer##__LINE__, __FUNCTION__, __FILE__, __LINE__ - 4);\
}
#endif


// convenience macros
//*************************************************************************************************
//                                       logTrace()                               
//*************************************************************************************************
//! \brief Logs trace messages.
//! \param[in] message The message which should be logged.
//! \param[in] ... Variable argumentlist.
//*************************************************************************************************
#ifdef WIN32
   #define logTrace(message, ...) TRENTINO_UTILS_LOGGING_MSG(Trace, message, ##__VA_ARGS__);
#else
   #define logTrace(message...) TRENTINO_UTILS_LOGGING_MSG(Trace, message);
#endif

//*************************************************************************************************
//                                       logInfo()                               
//*************************************************************************************************
//! \brief Logs info messages.
//! \param[in] message The message which should be logged.
//! \param[in] ... Variable argumentlist.
//*************************************************************************************************
#ifdef WIN32
   #define logInfo(message, ...) TRENTINO_UTILS_LOGGING_MSG(Info, message, ##__VA_ARGS__);
#else
   #define logInfo(message...) TRENTINO_UTILS_LOGGING_MSG(Info, message);
#endif

//*************************************************************************************************
//                                       logWarn()                               
//*************************************************************************************************
//! \brief Logs warning messages.
//! \param[in] message The message which should be logged.
//! \param[in] ... Variable argumentlist.
//*************************************************************************************************
#ifdef WIN32
   #define logWarn(message, ...) TRENTINO_UTILS_LOGGING_MSG(Warn, message, ##__VA_ARGS__);
#else
   #define logWarn(message...) TRENTINO_UTILS_LOGGING_MSG(Warn, message);
#endif

//*************************************************************************************************
//                                       logError()                               
//*************************************************************************************************
//! \brief Logs error messages.
//! \param[in] message The message which should be logged.
//! \param[in] ... Variable argumentlist.
//*************************************************************************************************
#ifdef WIN32
   #define logError(message, ...) TRENTINO_UTILS_LOGGING_MSG(Error, message, ##__VA_ARGS__);
#else
   #define logError(message...) TRENTINO_UTILS_LOGGING_MSG(Error, message);
#endif

//specific
#include "../Global/TrentinoGlobal.h"
#include "TrentinoUtils.h"
#include "TrentinoUtilsLoggingLogger.h"

//*************************************************************************************************
//                                       configuration
//*************************************************************************************************
// must be defined after including all headers!
#ifdef TRENTINO_DEBUG_OUTPUT
//! Switches Trace messages on/off
   TRENTINO_UTILS_LOGGING_MSG_TAG(Trace, true)
#else
   TRENTINO_UTILS_LOGGING_MSG_TAG(Trace, false)
#endif //TRENTINO_DEBUG_OUTPUT

//! Switches Info messages on/off
TRENTINO_UTILS_LOGGING_MSG_TAG(Info, true)
//! Switches Info warning on/off
TRENTINO_UTILS_LOGGING_MSG_TAG(Warn, true)
//! Switches Info Error on/off
TRENTINO_UTILS_LOGGING_MSG_TAG(Error, true)


namespace Trentino{
namespace Utils{
namespace Logging
{
} //namespace Logging
} //namespace Utils
} //namespace Trentino

#endif //TrentinoUtilsLoggingH
