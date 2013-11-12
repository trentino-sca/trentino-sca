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
#include <gtest/gtest.h>
#include <boost/filesystem/path.hpp>

//specific
#include "./../../Utils/TrentinoUtilsEnvironment.h"
#include "./../../Utils/TrentinoUtilsLoggingLogger.h"
#include "./../../Utils/TrentinoUtilsPatternStaticClass.h"
#include "./../../Runtime/Core/TrentinoCoreRuntimeAPI.h"
#include "./../../Runtime/Core/TrentinoCoreDomain.h"
#include "./../../Runtime/Oasis/sca/ComponentContext.h"
#include "./../../Runtime/Core/TrentinoCoreSCAComponentContext.h"


using namespace std;
using namespace Trentino::Utils;
using namespace Trentino::Utils::Logging;
using namespace Trentino::Utils::Pattern;
using namespace Trentino::Core;


TEST(RuntimeAPITest, ContextTest)
{
   //disable all logging outputs
   Logger::setup(Logger::DisableAllLoggers, nullptr);

   const boost::filesystem::path runtimeDLLPath = 
      boost::filesystem::path( Environment::executablePath() ).parent_path() /
      boost::filesystem::path( "TrentinoRuntime.dll" );
   RuntimeAPIPtr runtimePtr;
   std::string command ;
   runtimePtr.reset(new RuntimeAPI(runtimeDLLPath.string(),command));

   EXPECT_TRUE(runtimePtr->runtimeDLL());

   oasis::sca::RefCountingPointer<oasis::sca::ComponentContext> refPtr(new SCAComponentContext());

   oasis::sca::ComponentContextPtr componentPtr = oasis::sca::ComponentContext::getCurrent();
   EXPECT_FALSE(componentPtr);

   SCAComponentContext::setCurrent(refPtr);

   EXPECT_EQ(refPtr.get(), oasis::sca::ComponentContext::getCurrent().get());

   SCAComponentContext::setCurrent();
   EXPECT_EQ( static_cast<oasis::sca::ComponentContext*>(nullptr)
            , oasis::sca::ComponentContext::getCurrent().get());

   runtimePtr.reset();
}
