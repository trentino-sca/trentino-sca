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

#ifndef TrentinoUtilsLoggingLoggerH
#define TrentinoUtilsLoggingLoggerH

//specific
#include "../Global/TrentinoGlobal.h"

#ifdef WIN32
   #ifdef UTILS_EXPORTS
      #define LOGGER_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define LOGGER_IMPORT_EXPORT __declspec(dllimport)       
   #endif //UTILS_EXPORTS
#else
   #define LOGGER_IMPORT_EXPORT
#endif //WIN32

namespace Trentino{
namespace Utils{
namespace Logging
{
   //class declaration
   //**********************************************************************************************
   //                             Logger                             
   //**********************************************************************************************
   //! \brief Central logging facility to log message, used by Trentino logging macros. 
   //**********************************************************************************************
   class LOGGER_IMPORT_EXPORT Logger
   {
      // additional
   public:
      //! \brief configures the logger
      enum SetupType
      {
         //! Logger is configured with \sa ConfigDesc::loggerName, 
         //! \sa ConfigDesc::configFilePath and \sa ConfigDesc::nameSpace
         //! \sa ConfigDesc::loggerName can be nullptr if configuring default logger and
         //! \sa ConfigDesc::configFilePath can be nullptr if a specified logger should be 
         //! configured with base configuration (console output).
         SetupLogger,
         //! Disabled all loggers available by Runtime, whole \sa ConfigDesc is ignored here
         DisableAllLoggers,
         //! Enables all loggers available by Runtime, whole \sa ConfigDesc is ignored here
         EnableAllLoggers
      };

      //! Configuration descriptor
      struct ConfigDesc
      {
         //! Logger name you set this configuration. Can be nullptr if it is set for default
         //! logger
         const char* loggerName;
         //! Used by extended Setup. If associated logger should have a appropriate 
         //! configuration file, Filepath is recommended here. Can be nullptr if Default logger is
         //! chosen.
         const char* configFilePath;
         //! Namespace which should be configured for this logger with specified \sa loggerName.
         const char* nameSpace;
      };

      //construction
   public:
      //*******************************************************************************************
      //                                           Logger()                               
      //*******************************************************************************************
      //! Default constructor of logger singleton. 
      // \todo Currently not used, logMessage is called statically.
      //*******************************************************************************************
      Logger();

      //*******************************************************************************************
      //                                           ~Logger()                               
      //*******************************************************************************************
      //! Destructor of logger singleton.
      // \todo Currently not used, logMessage is called statically.
      //*******************************************************************************************
      ~Logger();

      //services
   public:
      //*******************************************************************************************
      //                                       logMessage()                               
      //*******************************************************************************************
      //! \brief Logs a message and takes additional arguments name of function and filepath.
      //!
      //! \param[in] loggerName optional loggername, to dispatch message into different loggers. 
      //! \param[in] tag Userdefined tag, can be a grouptype of a message. 
      //! \param[in] message The message which should be logged.
      //! \param[in] filePath file in which message is occurred.
      //! \param[in] line linenumber on which message is occurred.
      //*******************************************************************************************
      static void logMessage( const char* loggerName,
                              const char* tag, 
                              const char* message,
                              const char* filePath,
                              int line);

      //*******************************************************************************************
      //                                       logMessage()                               
      //*******************************************************************************************
      //! \brief Logs a message and takes additional arguments name of function and filepath.
      //!
      //! \param[in] loggerName optional loggername, to dispatch message into different loggers. 
      //! \param[in] tag Userdefined tag, can be a grouptype of a message. 
      //! \param[in] message The message which should be logged.
      //! \param[in] functionName Name of function, mostly determined by __FUNCTION__ macro.
      //! \param[in] filePath file in which message is occurred.
      //! \param[in] line linenumber on which message is occurred.
      //*******************************************************************************************
      static void logMessage( const char* loggerName,
                              const char* tag, 
                              const char* message,
                              const char* functionName,
                              const char* filePath,
                              int line);

      //*******************************************************************************************
      //                                       logMessage()                               
      //*******************************************************************************************
      //! \brief Logs a single message without any additional arguments.
      //!
      //! \param[in] loggerName optional loggername, to dispatch message into different loggers.
      //! \param[in] tag Userdefined tag, can be a grouptype of a message.
      //! \param[in] message The message which should be logged.
      //*******************************************************************************************
      static void logMessage( const char* loggerName,
                              const char* tag, 
                              const char* message);

      //*******************************************************************************************
      //                                   logFormatMessage()                               
      //*******************************************************************************************
      //! \brief Logs a message and takes additional variable arguments.
      //!
      //! \param[in] loggerName optional loggername, to dispatch message into different loggers.
      //! \param[in] tag Userdefined tag, can be a grouptype of a message.
      //! \param[in] message The message which should be logged.
      //! \param[in] ... Variable argumentlist.
      //*******************************************************************************************
      static void logFormatMessage( const char* loggerName,
                                    const char* tag, 
                                    const char* message, ...);

      //*******************************************************************************************
      //                                   setup()                               
      //*******************************************************************************************
      //! \brief Sets ups the logger configuration
      //! Can be called more than one. Used to setup extended loggers, default logger or
      //! disabling the whole output of all loggers
      //!
      //! \param[in] SetupType of logger, see there for more information.
      //! \param[in] Configuration descriptor, can be nullptr if \sa SetupType is 
      //! \sa EnableAllLoggers or \sa DisableAllLoggers
      //*******************************************************************************************
      static void setup(SetupType setupType, ConfigDesc* configDesc);
        
         //data
      private:
         static bool LoggersEnabled;
   }; //class Logger


} //namespace Logging
} //namespace Utils
} //namespace Trentino

#endif //TrentinoUtilsLoggingLoggerH
