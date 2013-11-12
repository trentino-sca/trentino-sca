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
#include "TrentinoUtilsLoggingLog4CPlus.h"

//standard
#include <string>
#include <stdexcept>
#include <boost/unordered_map.hpp>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <sstream>

using namespace std;
using namespace Trentino::Utils::Logging;

//global definitions
log4cplus::Logger* Log4CPlusLogger::mDefaultLogger = nullptr;
std::map<const string, std::vector<std::string> > Log4CPlusLogger::mLoggers;
std::map<const string, log4cplus::Logger> Log4CPlusLogger::mLoggerNameMap;

//class Log4CPlusLogger

//service

std::vector<std::string>* Log4CPlusLogger::loggerForNamespace(const std::string& loggerNamespace)
{
   std::map<const string, std::vector<std::string> >::iterator foundIter =
      mLoggers.find(loggerNamespace);
   if(foundIter == mLoggers.end())
      return nullptr;
   return &foundIter->second;
}

log4cplus::Logger Log4CPlusLogger::logger(const char* loggerName) 
{
   if(loggerName == nullptr)
   {
      if(mDefaultLogger == nullptr)
      {
         //Initialize with basic configuration
         setupLogger();
      }
      assert(mDefaultLogger != nullptr);
      return *mDefaultLogger;
   }
   else
   {
      assert(mLoggerNameMap.find(loggerName) != mLoggerNameMap.end());
      return mLoggerNameMap[loggerName];
   }
}

void Log4CPlusLogger::setupLogger(const char* loggerName, 
   const char* configFilePath, 
   const char* nameSpace)
{
   //safety
   log4cplus::Logger* foundLogger = nullptr;
   log4cplus::Logger tmpLogger;

   if(loggerName == nullptr)
   {
      static log4cplus::Logger defaultlogger = log4cplus::Logger::getInstance(L"default");
      foundLogger = mDefaultLogger = &defaultlogger;
   }
   else
   {
      wstringstream conv;
      conv << loggerName;
      tmpLogger = log4cplus::Logger::getInstance(conv.str());
      foundLogger = &tmpLogger;
   }

   if(foundLogger != nullptr)
   {
      if(configFilePath != nullptr)
      {
         wstringstream conv;
         conv << configFilePath;
         log4cplus::PropertyConfigurator::doConfigure(conv.str());
      }
      else
      {
         log4cplus::SharedAppenderPtr ptr (new log4cplus::ConsoleAppender(true));
         foundLogger->addAppender(ptr);
      }
            
      std::string loggerStr;
      if(loggerName != nullptr)
         loggerStr = loggerName;
      if(nameSpace != nullptr)
      {
         vector<std::string>& loggers = mLoggers[nameSpace];
         loggers.push_back(loggerStr);
      }

      mLoggerNameMap[loggerStr] = *foundLogger;
   }
}

