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
#include "../../Console/TrentinoConsoleContext.h"
#include <boost/thread.hpp>

boost::mutex gMutexExit;
using namespace Trentino;
using namespace Trentino::Console;
Trentino::Console::Context context;
boost::condition_variable gConditionExit;

int main(int /*argc*/, char** /*argv*/)
{

// Verify that the version of the library that we linked against is
// compatible with the version of the headers we compiled against.
//char* argv2[1];
   char *option[] ={ const_cast<char*>("dummy.exe"), //it doesn't have meaning, just dummy
      const_cast<char*>("--gtest_output=xml:report/ConsoleTestReport.xml") };
   int argc2 = 2;
   ::testing::InitGoogleMock(&argc2, option);
    return RUN_ALL_TESTS(); 
}
