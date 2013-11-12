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
#include "TrentinoTestsDeployTest.h"

//specific



//standard
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/filesystem.hpp> 
#include "gtest/gtest.h"

using namespace std;
using namespace Trentino;
using namespace Trentino::Console;
using namespace Trentino::Tests;

namespace {
   std::string getContributionPath(std::string ctbtionName){
      boost::filesystem::path abs_path = boost::filesystem::system_complete(Trentino::Tests::DeployTest::mTestDataDir+"/"+ctbtionName);
      boost::filesystem::file_status aStatus= boost::filesystem::status(abs_path);
      bool exists = boost::filesystem::exists(aStatus);
      (void)exists;
      assert(exists);
      std::string abs_path_str = abs_path.string();
      return abs_path_str;
      }
   }
TEST_F(DeployTest,boot_exit_does_not_throw_an_error_code_is_inSetUp_and_Teardown){
    
   }

TEST_F(DeployTest,install_contribution_contribution_should_not_return_an_error){
   //"install [-hi] PathToContribution ContributionBaseURI"
   std::string contrubitionPath = getContributionPath(std::string("BasicCalculator"));//Trentino::Tests::DeployTest::mTestDataDir+"\\TrentinoBasicCalculator";
   std::string line = "install -i "+contrubitionPath+" test";

   mCmd = mParser->parse(line);
   EXPECT_NO_THROW(mCmd->execute());
   ASSERT_EQ("",mCmd->errorMessage());
   //now the contribution is installed, the status of the contribution should be 'installed'

   }

TEST_F(DeployTest,boot_exit_does_not_throw_an_error_code_is_inSetUp_and_Teardown2){

   }