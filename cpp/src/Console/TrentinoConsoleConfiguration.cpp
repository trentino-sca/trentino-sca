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
#include "TrentinoConsoleConfiguration.h"

//standard
#include <boost/program_options.hpp>
#include <boost/filesystem/path.hpp>

//specific
#include "../Utils/TrentinoUtilsEnvironment.h"

using Trentino::Console::Configuration;
namespace po = boost::program_options;
namespace fs = boost::filesystem;
namespace Environment = Trentino::Utils::Environment;
using namespace std;

//class Configuration
   //static memmber initialization
const string Configuration::DefaultConfigFilePath = "../cfg/Console.conf";
   
   //construction
Configuration::Configuration(Configuration::Source source)
: mConfiguration(configFilePath(source))
{
   initOptions();
   mConfiguration.parse();
}

Configuration::Configuration(const std::string& configFilePath)
: mConfiguration(configFilePath)
{
   initOptions();
   mConfiguration.parse();
}

//management
void Configuration::initOptions()
{
   mConfiguration.configOptions().add_options()
      ("Runtime.DLLPath", po::value<string>()->default_value( "./"))
      ("Runtime.DLLName", po::value<string>()->default_value( "TrentinoRuntime"));  
}

string Configuration::configFilePath(Configuration::Source source) const
{
   switch(source)
   {
      case DefaultValues: return "";
      case DefaultConfigFile:          
         return ( fs::path(Environment::executablePath()).parent_path() / 
                  fs::path(DefaultConfigFilePath) ).string();
   }
   assert(false);

   return string();
}