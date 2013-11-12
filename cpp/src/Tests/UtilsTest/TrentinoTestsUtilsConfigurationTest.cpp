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
#include "gtest/gtest.h"

//standard
#include <stdexcept>
#pragma warning(push)
#pragma warning(disable:4512)
#include <boost/program_options.hpp>
#pragma warning(pop)

//specific
#include "../../Utils/TrentinoUtilsConfiguration.h"
#include "../TrentinoTestsEnvironmentInfo.h"
#include "TrentinoTestsUtilsConfigurationTest.h"

using Trentino::Tests::Utils::ConfigurationTest;
using Trentino::Utils::Configuration;
using namespace std;
namespace po = boost::program_options;

#pragma warning(push)
#pragma warning(disable:4127)


namespace
{
   typedef void(*InitOptionsDescriptionFunc)(po::options_description&);

   //global funcs
   void initNoDefaultValues(po::options_description& optionsDescription)
   {
      //options from ConfigFile.conf
      optionsDescription.add_options()
            ("Section1.option1", po::value<int>())
            ("Section1.option2", po::value<std::string>())
            ("Section2.option1", po::value<double>());            
   }

   void initWithDefaultValues(po::options_description& optionsDescription)
   {
      //options from ConfigFile.conf
      optionsDescription.add_options()
            ("Section1.option1", po::value<int>()->default_value(123))
            ("Section1.option2", po::value<std::string>()->default_value("DefaultString"))
            ("Section2.option1", po::value<double>()->default_value(0.9));            
   }
   
} //namespace


//class ConfigurationTest
   //services
TEST(ConfigurationTest, testValidValues)
{
   const string configFile1Path = 
      Trentino::Tests::EnvironmentInfo::SrcDirectoryPath + "/Tests/UtilsTest/TestData/ConfigFile1.conf"; 
   
   Configuration config1(configFile1Path);
   initNoDefaultValues(config1.configOptions());
   ASSERT_EQ(0,config1.optionsMap().count("Section1.option1"));
   ASSERT_EQ(0,config1.optionsMap().count("Section1.option2") );
   ASSERT_EQ(0,config1.optionsMap().count("Section2.option1"));   
   
   EXPECT_NO_THROW(config1.parse());   
   ASSERT_EQ(23,config1.optionsMap()["Section1.option1"].as<int>());
   EXPECT_STREQ(config1.optionsMap()["Section1.option2"].as<string>().c_str() , "someStringContent1");   
   ASSERT_EQ(0.5,config1.optionsMap()["Section2.option1"].as<double>());   

   Configuration config2;   
   initNoDefaultValues(config2.configOptions());
   EXPECT_NO_THROW(config2.parse());  
   ASSERT_EQ(0,config2.optionsMap().count("Section1.option1"));
   ASSERT_EQ(0,config2.optionsMap().count("Section1.option2"));
   ASSERT_EQ(0,config2.optionsMap().count("Section2.option1"));

   Configuration config3;
   initWithDefaultValues(config3.configOptions());
   EXPECT_NO_THROW(config3.parse());   
   ASSERT_TRUE(config3.optionsMap()["Section1.option1"].as<int>() == 123);
   ASSERT_TRUE(config3.optionsMap()["Section1.option2"].as<string>() == "DefaultString");   
   ASSERT_TRUE(config3.optionsMap()["Section2.option1"].as<double>() == 0.9);
}

TEST(ConfigurationTest, testInvalidValues)
{
    const string configFile2Path = 
      Trentino::Tests::EnvironmentInfo::SrcDirectoryPath + "/Tests/UtilsTest/TestData/ConfigFile2.conf"; 
   Configuration config(configFile2Path);   
   initNoDefaultValues(config.configOptions());
   EXPECT_THROW(config.parse(), po::unknown_option);
}

TEST(ConfigurationTest, testInvalidPaths)
{
   Configuration configNonExistentPath("NonExistentPath");
   initNoDefaultValues(configNonExistentPath.configOptions());
   EXPECT_THROW(configNonExistentPath.parse(), std::runtime_error);
}

#pragma warning(pop)

