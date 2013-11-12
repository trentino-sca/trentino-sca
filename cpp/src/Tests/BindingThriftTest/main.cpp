// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************

//#include <vld.h>
#pragma warning(push)
#pragma warning(disable:4512 4244)

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#pragma warning(pop)

int main(int /*argc*/, char* /*argv[]*/)
{
   // Verify that the version of the library that we linked against is
   // compatible with the version of the headers we compiled against.
   //char* argv2[1];
   char *option[] ={ "dummy.exe", //it doesn't have meaning, just dummy
      "--gtest_output=xml:report/BindingThriftTestReport.xml" };
   int argc2 = 2;
   ::testing::InitGoogleMock(&argc2, option);
   return RUN_ALL_TESTS();
}

