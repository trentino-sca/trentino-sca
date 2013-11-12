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

#ifndef TrentinoUtilsLoggingLog4CPlusH
#define TrentinoUtilsLoggingLog4CPlusH

//standard
#include <log4cplus/logger.h>
#include <string>
#include <vector>
#include <map>
#include <sstream>

//specific
#include "../Global/TrentinoGlobal.h"
#include "TrentinoUtils.h"

#ifdef WIN32
   #ifdef UTILS_EXPORTS
      #define LOG4CPLUSLOGGER_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define LOG4CPLUSLOGGER_IMPORT_EXPORT __declspec(dllimport)       
   #endif //UTILS_EXPORTS
#else
   #define LOG4CPLUSLOGGER_IMPORT_EXPORT
#endif //WIN32

//*************************************************************************************************
//                             TRENTINO_LOG4PLUS_MACRO
//*************************************************************************************************
//! Used to call logging function in log4cplus, passing file and line information.  
//! \param[in] loggerName Name of logger, nullptr if defaultlogger is used.
//! \param[in] message The logging message to show.
//! \param[in] logLevel Desired loglevel, could be TRACE, INFO, WARN, ERROR.
//! \param[in] fileName Filename in which message is called.
//! \param[in] lineNumber Linenumber in which message is called.
//*************************************************************************************************
#define TRENTINO_LOG4PLUS_MACRO(loggerName, message, logLevel, fileName, lineNumber)\
   log4cplus::Logger logger = LoggerExt::logger(loggerName);\
   do\
   {\
   if(logger.isEnabledFor(log4cplus::logLevel##_LOG_LEVEL))\
      {\
      log4cplus::tostringstream _log4cplus_buf;\
      _log4cplus_buf << message;\
      (logger).forcedLog(log4cplus::logLevel##_LOG_LEVEL,\
      _log4cplus_buf.str(), fileName, lineNumber);\
      }\
   } while (Trentino::Utils::constantExpression<bool>(false))

namespace Trentino{
namespace Utils{
namespace Logging
{
   //forward declaration
   class Logger;

   //class declaration
   //**********************************************************************************************
   //                             Log4CPlusLogger                             
   //**********************************************************************************************
   //! \brief Thin class to wrap log4cplus functionality.
   //! Supports query and setup of log4cplus loggers.
   //**********************************************************************************************
   class Log4CPlusLogger
   {
      friend class Logger;

      //additional
      //! Pointer to logger by Console name
      static std::map<const std::string, std::vector<std::string> > mLoggers;
      static std::map<const std::string, log4cplus::Logger> mLoggerNameMap;
      //! Pointer to default logger to gain faster access.
      static log4cplus::Logger* mDefaultLogger;
   private:
      //service
   public:
      //*******************************************************************************************
      //                              logger()
      //*******************************************************************************************
      //! \brief Returns logger with a specified logger name. 
      //! \todo Currently is only default logger supported. Do we need more?
      //! \param[in] loggerName Name of logger, can be nullptr to retrieve default logger 
      //!            for faster access.
      //! \return Logger with specified logger name or default logger named "default".
      //*******************************************************************************************
      static LOG4CPLUSLOGGER_IMPORT_EXPORT log4cplus::Logger logger(const char* loggerName = nullptr);

      //*******************************************************************************************
      //                            loggerForNamespace()
      //*******************************************************************************************
      //! \brief Returns logger for specified namespace. 
      //! \param[in] loggerNamespace of logger
      //! \return vector of Loggers with specified logger name. Can be null if no valid logger
      //!         for namespace is found
      //*******************************************************************************************
      static LOG4CPLUSLOGGER_IMPORT_EXPORT std::vector<std::string>* loggerForNamespace
         (const std::string& loggerNamespace);

   private:
      //*******************************************************************************************
      //                              setupLogger()
      //*******************************************************************************************
      //! \brief Constructs a specified logger with an optional configuration.
      //! \todo Currently is only default logger supported. Do we need more?
      //! \param[in] loggerName Name of logger, can be nullptr to create default logger
      //!            with "default" as name.
      //! \param[in] configFilePath Filepath of configuration file. Can be nullptr, a
      //!            basic configuration will be assumed.
      //! \param[in] namespace to set and associate with a specified namespace
      //*******************************************************************************************
      static LOG4CPLUSLOGGER_IMPORT_EXPORT void setupLogger(const char* loggerName = nullptr,
                              const char* configFilePath = nullptr,
                              const char* nameSpace = nullptr);
   }; //class Log4CPlusLogger

   typedef Log4CPlusLogger LoggerExt;
} //namespace Logging
} //namespace Utils
} //namespace Trentino


#endif //TrentinoUtilsLoggingLog4CPlusH
