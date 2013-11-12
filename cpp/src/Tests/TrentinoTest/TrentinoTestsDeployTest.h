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

#ifndef TrentinoTestsDeployTestH
#define TrentinoTestsDeployTestH

//standard
#include "boost/shared_ptr.hpp"
#include <boost/smart_ptr/make_shared.hpp>

//test
#include <gmock/gmock.h>
#include <gtest/gtest.h>

//specific
#include "../../Console/TrentinoConsoleCommandInfo.h"
#include "../../Console/TrentinoConsole.h"
#include "../../Console/TrentinoConsoleTextOutputVisitor.h"
#include "../../Console/TrentinoConsoleCommand.h"
#include "../../Console/TrentinoConsoleParser.h"
#include "../../Console/TrentinoConsoleConfiguration.h"



namespace Trentino {
namespace Tests {
   typedef boost::shared_ptr<Trentino::Console::Parser> ParserPtr;
   //class declaration


   class DeployTest : public ::testing::Test
   {

   public:
   //services
   void SetUp(){
      using namespace std;
      using namespace Trentino;
      using namespace Trentino::Console;

      Trentino::Console::globalConfiguration = 
         boost::make_shared<Configuration>(Configuration::DefaultConfigFile);

      Configuration configuraiton(Configuration::DefaultConfigFile); 
         mParser.reset(new Parser(mContext));
      //set up will boot the system
            std::string line ("boot");
            mCmd = mParser->parse(line);
            mCmd->execute();
      }
   void TearDown(){
      using namespace std;
      using namespace Trentino;
      using namespace Trentino::Console;

      std::string line ("exit");
      mCmd = mParser->parse(line);
      mCmd->execute();
      }

   public:
      Trentino::Console::Command::CommandSharedPtr mCmd;
      ParserPtr mParser;
      Trentino::Console::Context mContext;
   public:
      static std::string mTestDataDir;
   }; //class DeployTest
} //namespace Tests
} //namespace Trentino

#endif //TrentinoTestsDeployTestH
