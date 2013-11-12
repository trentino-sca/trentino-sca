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

// header
#include "TrentinoUtilsLoggingLogger.h"

// standard
#include <stdio.h>
#include <cstdarg>
#include <cstring>
#include <boost/foreach.hpp>

//specific
#ifdef TRENTINO_LOGGING
   #include "TrentinoUtilsLoggingLog4CPlus.h"
#endif //TRENTINO_LOGGING

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif //WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif //_WIN32

using namespace Trentino::Utils::Logging;

//data
bool Logger::LoggersEnabled = true;


// construction
Logger::Logger()
{
   // does nothing for now
}

Logger::~Logger()
{
   // later: some house cleaning here
}

// services
void Logger::logFormatMessage(const char* /*loggerName */,
                              const char* tag, 
                              const char* message,
                              ...)
{
   if(LoggersEnabled == false)
      return;
   
   va_list variableArguments;
   va_start(variableArguments, message);

#if defined(WIN32)
   char messageBuffer[1024];

   //!\todo use platform header here
   int size = vsnprintf_s(messageBuffer,1023, 1023, message, variableArguments);

   if (size == -1)
   {
      size = _vscprintf(message, variableArguments);
      char* messageBuffer = new char[size + 1];
      vsnprintf_s(messageBuffer, size, size, message, variableArguments);
      messageBuffer[size] = '\0';

      // sufficient for now
      Logger::logMessage(nullptr, tag, messageBuffer);
      delete[] messageBuffer; 
   }
   else
   {
      messageBuffer[1023] = '\0';
      Logger::logMessage(nullptr, tag, messageBuffer);
   }
#endif //_WIN32
   va_end(variableArguments);
}


void Logger::logMessage(const char* loggerName,
                        const char* tag, 
                        const char* message)
{
   logMessage(loggerName, tag, message, __FUNCTION__, __FILE__, __LINE__);
}

void Logger::logMessage(const char* loggerName,
   const char* tag, 
   const char* message,
   const char* filePath,
   int line)
{
   if(LoggersEnabled == false)
      return;


#ifdef TRENTINO_LOGGING
   // TODO: optimize trace -> use nullptr as tag
   if(strcmp(tag, "Trace") == 0)
   {
      TRENTINO_LOG4PLUS_MACRO(loggerName, message, TRACE, filePath, line);
   }
   else if(strcmp(tag, "Info") == 0)
   {
      TRENTINO_LOG4PLUS_MACRO(loggerName, message, INFO, filePath, line);
   }
   else if(strcmp(tag, "Warn") == 0)
   {
      TRENTINO_LOG4PLUS_MACRO(loggerName, message, WARN, filePath, line);
   }
   else if(strcmp(tag, "Error") == 0)
   {
      TRENTINO_LOG4PLUS_MACRO(loggerName, message, ERROR, filePath, line);
   }
#else
   //unused
   (void)loggerName;
   (void)tag;
   (void)filePath;
   (void)line;
   // sufficient for now
   printf(message);
#ifdef _WIN32
   OutputDebugStringA(message);
#endif //_WIN32 
#endif //TRENTINO_LOGGING
}

std::string extractNamespace(const std::string& nmeSpc)
{
   int foundPos = nmeSpc.find_last_of("::");
   std::string result(nmeSpc);
   if(foundPos != -1)
   {
      result.erase(foundPos -1, result.size());
   }
   return result;
}


void Logger::logMessage(const char* loggerName,
                        const char* tag, 
                        const char* message,
                        const char* functionName,
                        const char* filePath,
                        int line)
{
   if(LoggersEnabled == false)
      return;

#ifdef TRENTINO_LOGGING
      if(functionName != nullptr && loggerName == nullptr)   
      {
         //Function call with namespace?
         std::string nmeSpcCut = extractNamespace(functionName);
         std::vector<std::string>* loggers = 
            LoggerExt::loggerForNamespace(nmeSpcCut);
         if(loggers == nullptr)
         {
            //Method class with namespace
            loggers = LoggerExt::loggerForNamespace(extractNamespace(nmeSpcCut));
         }

         if(loggers != nullptr)
         {
            BOOST_FOREACH(const std::string& loggerName, *loggers)
            {
               logMessage(loggerName.c_str(), tag, message, filePath, line);
            }
         }
         else
         {
            logMessage(nullptr, tag, message, filePath, line);
         }

      }
      else
      {
         logMessage(loggerName, tag, message, filePath, line);
      }
   #else
      (void)line;
      (void)filePath;
      (void)functionName;
      (void)message;
      (void)tag;
      (void)loggerName;
   #endif //TRENTINO_LOGGING
}

void Logger::setup(Logger::SetupType setupType, Logger::ConfigDesc* configDesc)
{
   (void) configDesc;
   switch (setupType)
   {
   case EnableAllLoggers:
      LoggersEnabled = true;
   	break;
   case DisableAllLoggers:
      LoggersEnabled = false;
      break;
#ifdef TRENTINO_LOGGING
   case SetupLogger:
      assert(configDesc != nullptr);
      LoggerExt::setupLogger(
         configDesc->loggerName, configDesc->configFilePath, configDesc->nameSpace);
      break;
#endif
   }
}

