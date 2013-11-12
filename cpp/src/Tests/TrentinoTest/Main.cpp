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

//standard

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "TrentinoTestsDeployTest.h"
#include <boost/thread.hpp>
#ifdef WIN32
#include <windows.h>
#endif

Trentino::Console::Context context;
std::string Trentino::Tests::DeployTest::mTestDataDir("");
boost::mutex gMutexExit;
boost::condition_variable gConditionExit;

int main(int argc, char** argv)
{
//arg[1] should be: I:\\Trentino\\trentino\\DEV\\cpp\\src\\Tests\\TestData
//you can set the value in TrentinoTest->Properties ->..-> command arguments
#ifdef WIN32
SetErrorMode(SEM_FAILCRITICALERRORS); 
#endif

//no command line arguments? 
if(argc <= 1)
{
   printf("no command line arguments!");
   return 0;
}

Trentino::Tests::DeployTest::mTestDataDir =std::string(argv[1]);
// Verify that the version of the library that we linked against is
// compatible with the version of the headers we compiled against.
//char* argv2[1];
char *option[] ={ const_cast<char*>("dummy.exe"), //it doesn't have meaning, just dummy
   const_cast<char*>("--gtest_output=xml:report/TrentinoTestReport.xml") };
int argc2 = 2;
::testing::InitGoogleMock(&argc2, option);
 return RUN_ALL_TESTS(); 
}
