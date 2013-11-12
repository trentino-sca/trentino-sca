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
#include "TrentinoTestsConsoleParserTest.h"

//standard
#include <stdexcept>

//specific
#include "../../Console/TrentinoConsoleParser.h"
#include "../../Console/TrentinoConsoleCommandInfo.h"
#include "../../Console/TrentinoConsoleCommandInstall.h"

using namespace std;
using namespace Trentino::Console;
using Trentino::Tests::Console::ParserTest;

//class ParserTest
//services

extern Trentino::Console::Context context;

TEST_F(ParserTest, parse_info_usage_with_double_minus_throw_error){
   Parser consoleParser(context);
   EXPECT_THROW(consoleParser.parse("info --h"), std::runtime_error);
   }


TEST_F(ParserTest, parse_info_usage_with_minus_space_minus_throw_error){
   Parser consoleParser(context);
   EXPECT_THROW(consoleParser.parse("info - -h"), std::runtime_error);
   }

TEST_F(ParserTest, parse_info_usage_with_extra_argument_throws_error){
   Parser consoleParser(context);
   EXPECT_THROW(consoleParser.parse("info -h -d1"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info -h -d2"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info -h -s"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info -h --q"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info -h --qc"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info -h someURI"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info -h -d1 -s -qp"), std::runtime_error);
   }

TEST_F(ParserTest,parse_info_minus_h_at_wrong_position_throws_error){
   Parser consoleParser(context);
   EXPECT_THROW(consoleParser.parse("info -s -h"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info -d1 -h"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info -qs -h"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info xxxx -h"), std::runtime_error);
   }


TEST_F(ParserTest, info_without_argument_throw_error){
   Parser consoleParser(context);
   //test parser for command info
   EXPECT_THROW(consoleParser.parse("info"), std::runtime_error);}


TEST_F(ParserTest, parse_info_with_usage_return_a_non_null_pointer_with_showUsage_equas_true){
   Parser consoleParser(context);
   //test parser for command info
   EXPECT_NO_THROW(cmd = consoleParser.parse("info -h"));
   ASSERT_TRUE(dynamic_cast<CommandInfo*>(cmd.get()) != 0);
   ASSERT_EQ(dynamic_cast<CommandInfo*>(cmd.get())->showUsage(), true);}


TEST_F(ParserTest, parse_info_query_without_artifact_uri_throw_error){
   Parser consoleParser(context);
   //test parser for command info
   EXPECT_THROW(consoleParser.parse("info -qa"), std::runtime_error);
   ASSERT_NO_THROW(consoleParser.parse("info -qc"));
   EXPECT_THROW(consoleParser.parse("info -qp"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info -qr"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info -qs"), std::runtime_error);
   }


TEST_F(ParserTest, parse_info_query_with_wrong_specificator_throw_error_1){
   Parser consoleParser(context);
   //test parser for command info
   EXPECT_THROW(consoleParser.parse("info -qt xxx"), std::runtime_error);
   }


TEST_F(ParserTest, parse_info_query_with_wrong_specificator_throw_error_2){
   Parser consoleParser(context);
   //test parser for command info
   EXPECT_THROW(consoleParser.parse("info -qi xxx"), std::runtime_error);
   }


TEST_F(ParserTest, parse_info_query_with_wrong_specificator_throw_error_3){
   Parser consoleParser(context);
   //test parser for command info
   EXPECT_THROW(consoleParser.parse("info -qz xxx"), std::runtime_error);
   }


TEST_F(ParserTest, parse_info_query_with_wrong_specificator_throw_error_4){
   Parser consoleParser(context);
   //test parser for command info
   EXPECT_THROW(consoleParser.parse("info -qai xxx"), std::runtime_error);
   }


TEST_F(ParserTest, parse_info_query_with_wrong_specificator_throw_error_5){
   Parser consoleParser(context);
   //test parser for command info;
   EXPECT_THROW(consoleParser.parse("info -qbz xxx"), std::runtime_error);
   }


TEST_F(ParserTest, parse_info_query_with_rigth_specificator_wont_throw_error){
   Parser consoleParser(context);
   //test parser for command info;
   EXPECT_NO_THROW(consoleParser.parse("info -qb xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qc xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qr xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qs xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qp xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qrs xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qsr xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qrp xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qpr xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qsp xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qps xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qrsp xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qrps xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qprs xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qpsr xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qspr xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qsrp xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qbc xxx"));
   EXPECT_NO_THROW(consoleParser.parse("info -qbcrs xxx"));
   }

TEST_F(ParserTest,depth_of_artifacts_should_comes_before_arfifacts_status){
   Parser consoleParser(context);
   //test parser for command info;
   EXPECT_NO_THROW(cmd=consoleParser.parse("info -s -d2 xxx"));
   boost::shared_ptr<CommandInfo> cmdInfo = boost::dynamic_pointer_cast<CommandInfo>(cmd);
   ASSERT_TRUE(cmdInfo);
   }


TEST_F(ParserTest,depth_of_artifacts_should_be_positive_1){
   Parser consoleParser(context);
   //test parser for command info;
   EXPECT_THROW(consoleParser.parse("info -s -d-1 xxx"), std::runtime_error);
   }


TEST_F(ParserTest,depth_of_artifacts_should_be_positive_2){
   Parser consoleParser(context);
   //test parser for command info;
   EXPECT_THROW(consoleParser.parse("info -s -d0 xxx"), std::runtime_error);
   }

TEST_F(ParserTest, parse_info_tests){
   Parser consoleParser(context);
   //test parser for command info
   EXPECT_THROW(consoleParser.parse("info URI1 URI2"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("info -dN URI"), std::runtime_error);
   EXPECT_NO_THROW(cmd = consoleParser.parse("info -d1 -s URI"));
   ASSERT_TRUE(dynamic_cast<CommandInfo*>(cmd.get()) != 0);
   EXPECT_NO_THROW(cmd = consoleParser.parse("info -d2 -s -qrs URI"));
   ASSERT_TRUE(dynamic_cast<CommandInfo*>(cmd.get()) != 0);
   }

TEST_F(ParserTest,command_install)
{
   Parser consoleParser(context);
   //test parser for command install
   EXPECT_THROW(consoleParser.parse("install"), std::runtime_error);
   EXPECT_NO_THROW(cmd = consoleParser.parse("install -h"));
   ASSERT_EQ(dynamic_cast<CommandInstall*>(cmd.get())->showUsage(), true);
   ASSERT_TRUE(dynamic_cast<CommandInstall*>(cmd.get()) != 0);
   EXPECT_THROW(consoleParser.parse("install contrib"), std::runtime_error);
   EXPECT_NO_THROW(cmd = consoleParser.parse("install contrib baseURI"));
   ASSERT_TRUE(dynamic_cast<CommandInstall*>(cmd.get()) != 0);
   EXPECT_THROW(consoleParser.parse("install -i"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("install -h -i"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("install -i contrib baseURI"), std::runtime_error);

   
   CommandInstall* cmdInstall = 0;

   ASSERT_NO_THROW( cmd = consoleParser.parse("install \"Path space\" baseURI") );   
   cmdInstall = dynamic_cast<CommandInstall*>(cmd.get());
   assert(cmdInstall);
   ASSERT_EQ(cmdInstall->commandArgs().pathToContribution, "Path space");
   ASSERT_EQ(cmdInstall->commandArgs().contributionBaseURI, "baseURI");
   
   ASSERT_NO_THROW( cmd = consoleParser.parse("install \"Path space more\" baseURI") );   
   cmdInstall = dynamic_cast<CommandInstall*>(cmd.get());
   assert(cmdInstall);
   ASSERT_EQ(cmdInstall->commandArgs().pathToContribution, "Path space more");
   ASSERT_EQ(cmdInstall->commandArgs().contributionBaseURI, "baseURI");
   
   ASSERT_NO_THROW( cmd = consoleParser.parse("install \"WithoutSpaces\" baseURI") );   
   cmdInstall = dynamic_cast<CommandInstall*>(cmd.get());
   assert(cmdInstall);
   ASSERT_EQ(cmdInstall->commandArgs().pathToContribution, "WithoutSpaces");
   ASSERT_EQ(cmdInstall->commandArgs().contributionBaseURI, "baseURI");

   ASSERT_NO_THROW( cmd = consoleParser.parse("install  NoSpacesNoQuotes baseURI") );   
   cmdInstall = dynamic_cast<CommandInstall*>(cmd.get());
   assert(cmdInstall);
   ASSERT_EQ(cmdInstall->commandArgs().pathToContribution, "NoSpacesNoQuotes");
   ASSERT_EQ(cmdInstall->commandArgs().contributionBaseURI, "baseURI");

   ASSERT_NO_THROW( cmd = consoleParser.parse("install  \"\" baseURI") );   
   cmdInstall = dynamic_cast<CommandInstall*>(cmd.get());
   assert(cmdInstall);
   ASSERT_EQ(cmdInstall->commandArgs().pathToContribution, "");
   ASSERT_EQ(cmdInstall->commandArgs().contributionBaseURI, "baseURI");

   ASSERT_NO_THROW( cmd = consoleParser.parse("install  \"One\" \"baseURI\"") );   
   cmdInstall = dynamic_cast<CommandInstall*>(cmd.get());
   assert(cmdInstall);
   ASSERT_EQ(cmdInstall->commandArgs().pathToContribution, "One");
   ASSERT_EQ(cmdInstall->commandArgs().contributionBaseURI, "baseURI");

   ASSERT_NO_THROW( cmd = consoleParser.parse("  install   \"One\"   baseURI") );   
   cmdInstall = dynamic_cast<CommandInstall*>(cmd.get());
   assert(cmdInstall);
   ASSERT_EQ(cmdInstall->commandArgs().pathToContribution, "One");
   ASSERT_EQ(cmdInstall->commandArgs().contributionBaseURI, "baseURI");

   ASSERT_NO_THROW( cmd = consoleParser.parse("install  \"One\"\"baseURI\"") );   
   cmdInstall = dynamic_cast<CommandInstall*>(cmd.get());
   assert(cmdInstall);
   ASSERT_EQ(cmdInstall->commandArgs().pathToContribution, "One");
   ASSERT_EQ(cmdInstall->commandArgs().contributionBaseURI, "baseURI");

   ASSERT_NO_THROW( cmd = consoleParser.parse("install  \"One\"baseURI\"") );   
   cmdInstall = dynamic_cast<CommandInstall*>(cmd.get());
   assert(cmdInstall);
   ASSERT_EQ(cmdInstall->commandArgs().pathToContribution, "One");
   ASSERT_EQ(cmdInstall->commandArgs().contributionBaseURI, "baseURI\"");

   ASSERT_THROW( cmd = consoleParser.parse("install  \" baseURI"), std::runtime_error );   
   ASSERT_THROW( cmd = consoleParser.parse("install  \"start baseURI"), std::runtime_error);
   ASSERT_THROW( cmd = consoleParser.parse("install  \"start baseURI"), std::runtime_error);
   
}


TEST_F(ParserTest, command_remove){
   Parser consoleParser(context);
   //test parser for command remove
   EXPECT_NO_THROW(cmd = consoleParser.parse("remove -h"));
   ASSERT_EQ(dynamic_cast<CommandRemove*>(cmd.get())->showUsage(), true);
   ASSERT_TRUE(dynamic_cast<CommandRemove*>(cmd.get()) != 0);
   EXPECT_NO_THROW(cmd = consoleParser.parse("remove contrib"));
   ASSERT_TRUE(dynamic_cast<CommandRemove*>(cmd.get()) != 0);
   }


TEST_F(ParserTest, command_rewire){
   Parser consoleParser(context);

   //test parser for command rewire
   EXPECT_THROW(consoleParser.parse("rewire"), std::runtime_error);
   EXPECT_NO_THROW(cmd = consoleParser.parse("rewire -h"));
   ASSERT_EQ(dynamic_cast<CommandRewire*>(cmd.get())->showUsage(), true);
   ASSERT_TRUE(dynamic_cast<CommandRewire*>(cmd.get()) != 0);
   EXPECT_NO_THROW(cmd = consoleParser.parse("rewire reference target"));
   ASSERT_TRUE(dynamic_cast<CommandRewire*>(cmd.get()) != 0);
   EXPECT_NO_THROW(cmd = consoleParser.parse("rewire reference target binding"));
   ASSERT_TRUE(dynamic_cast<CommandRewire*>(cmd.get()) != 0);
   EXPECT_THROW(consoleParser.parse("rewire -h reference"), std::runtime_error);}



TEST_F(ParserTest, command_set){
   Parser consoleParser(context);
   //test parser for command set
   EXPECT_THROW(consoleParser.parse("set"), std::runtime_error);
   EXPECT_NO_THROW(cmd = consoleParser.parse("set -h"));
   ASSERT_EQ(dynamic_cast<CommandSetProperty*>(cmd.get())->showUsage(), true);
   ASSERT_TRUE(dynamic_cast<CommandSetProperty*>(cmd.get()) != 0);
   EXPECT_NO_THROW(cmd = consoleParser.parse("set a b c"));
   ASSERT_TRUE(dynamic_cast<CommandSetProperty*>(cmd.get()) != 0);
   }

TEST_F(ParserTest, command_quit){
   Parser consoleParser(context);
   //test parser for command quit
   EXPECT_NO_THROW(consoleParser.parse("quit"));
   }

TEST_F(ParserTest, multiple_parser_tests){
    Parser consoleParser(context);
   //test parser for garbage
   EXPECT_THROW(consoleParser.parse("hello"), std::runtime_error);
   EXPECT_THROW(consoleParser.parse("this is a test"), std::runtime_error);
   }