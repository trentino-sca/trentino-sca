// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2012 by Siemens AG. All rights reserved.
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

//memory Leak detection
#include "TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorProbobufMessages.h"

#include <vld.h>
#include <stdlib.h>
#include <crtdbg.h>





#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../../BindingSCAClient/TrentinoBindingSCAClientCommunicationController.h"

int main(int /*argc*/, char** /*argv*/)
   {
     using namespace Trentino::Binding::SCA::Client;
     CommunicationControllerPtr instance = CommunicationController::getInstance(1);
     instance->run();
   // Verify that the version of the library that we linked against is
   // compatible with the version of the headers we compiled against.
   GOOGLE_PROTOBUF_VERIFY_VERSION;
   //char* argv2[1];
   char *option[] ={ const_cast<char*>("dummy.exe"), //it doesn't have meaning, just dummy
      const_cast<char*>("--gtest_output=xml:report/BindingSCAClientTestReport.xml") };
   int argc2 = 2;
   ::testing::InitGoogleMock(&argc2, option);
   int res= RUN_ALL_TESTS();
   instance->stop();
   return res;
   }

