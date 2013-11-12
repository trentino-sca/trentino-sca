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

//header
#include "TrentinoTestsLoggingLoggerTest.h"

using Trentino::Tests::Logging::LoggerTest;
using namespace Trentino::Utils::Logging;
using namespace std;

TRENTINO_UTILS_LOGGING_MSG_TAG(Test1, true)
TRENTINO_UTILS_LOGGING_MSG_TAG(Test2, false)
TRENTINO_UTILS_LOGGING_MSG_TAG(Test3, true)

//static member definitions
int LoggerTest::counter_ = 0;
string LoggerTest::messages[] = {"Test1|Test1:42|Trentino::Tests::Logging::LoggerTest::testLogMessage", 
                                           "Test3|Test3:foo|Trentino::Tests::Logging::LoggerTest::testLogMessage",
// is switched off if not debug
#ifdef TRENTINO_DEBUG_OUTPUT
                                           "Trace|Test LogTrace: c0deba5e|Trentino::Tests::Logging::LoggerTest::testLogMessage",
#endif //TRENTINO_DEBUG_OUTPUT
                                           "Info|Test LogInfo: c001d00d|Trentino::Tests::Logging::LoggerTest::testLogMessage",
                                           "Warn|Test LogWarn: baadfeed|Trentino::Tests::Logging::LoggerTest::testLogMessage",
                                           "Error|Test LogError: deadbeef|Trentino::Tests::Logging::LoggerTest::testLogMessage",
                                           "Error|Test LogError simple|Trentino::Tests::Logging::LoggerTest::testLogMessage",};
                                             
// redefine output
#undef TRENTINO_UTILS_LOGGING_INTERNALFUNC
#define TRENTINO_UTILS_LOGGING_INTERNALFUNC LoggerTest::logMessage

// services
void LoggerTest::logMessage(const char* /*loggerName*/,
                            const char* tag, 
                            const char* message,
                            const char* functionName,
                            const char* /*filePath*/,
                            int /*line*/)
{
   // we don´t test here the filepath and line, we assume that all other values are sufficient to check
   const string delimiter = "|";

   const int countStrings = sizeof(messages) / sizeof(string);

   string buildStr = string(tag) + delimiter + string(message) + delimiter + string(functionName);
  //EXPECT_EQ("Only Test1 and Test2 should print a message. Counter is greater 2!", counter_ < countStrings);
   EXPECT_EQ(true, counter_ < countStrings);
   ++counter_;
}

TEST_F (LoggerTest, testLogMessage)
{
   TRENTINO_UTILS_LOGGING_MSG(Test1, "Test1:%d", 42);
   TRENTINO_UTILS_LOGGING_MSG(Test2, "Test2:%d", 42);
   TRENTINO_UTILS_LOGGING_MSG(Test3, "Test3:%s", "foo");
   logTrace("Test LogTrace: %x", 0xc0deba5e);
   logInfo("Test LogInfo: %x", 0xc001d00d);
   logWarn("Test LogWarn: %x", 0xbaadfeed);
   logError("Test LogError: %x", 0xdeadbeef);
   logError("Test LogError simple");
}
