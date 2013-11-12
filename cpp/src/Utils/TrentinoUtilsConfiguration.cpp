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
#include "TrentinoUtilsConfiguration.h"

//standard
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <errno.h>

//specific
#include "../Global/TrentinoGlobal.h"

using Trentino::Utils::Configuration;
namespace po = boost::program_options;
using namespace std;

namespace
{
   //constants
   const string ConfigOptionsCaption = 
      "Config options (override options from the configuration file)";
   /*const string GenericOptionsCaption = "Generic options";
   const string HiddenOptionsCaption = "Hidde options";
   const string DebugOptionsCaptions = "Debug options";*/
}

//class Configuration
   //construction
Configuration::Configuration( int argc
                            , char* argv[]
                            , const string& configFilePath)
: mArgc(argc)
, mArgv(argv)
, mConfigFilePath(configFilePath)
, mConfigOptions(ConfigOptionsCaption)   
/*, mGenericOptions(GenericOptionsCaption);
, mHiddenOptions (HiddenOptionsCaption);   
, mDebugOptions (DebugOptionsCaption);  */ 
{ }

Configuration::Configuration(const string& configFilePath)
: mArgc(0)
, mArgv(nullptr)
, mConfigFilePath(configFilePath)
, mConfigOptions(ConfigOptionsCaption)   
/*, mGenericOptions(GenericOptionsCaption);
, mHiddenOptions (HiddenOptionsCaption);   
, mDebugOptions (DebugOptionsCaption);  */ 
{ }

//services
void Configuration::parse(bool allow_unregistered) 
{
   //**********************************************************************************************
   //                                   for later use
   //**********************************************************************************************  
   /*po::options_description cmdLineOptions;
   initCommandLineOptions(cmdLineOptions);
   
   //parse command line
   po::command_line_parser cmdLineParser(argc, argv);
   cmdLineParser.options(cmdLineOptions);
   if( mPositionalOptions.max_total_count() > 0 )
      cmdLineParser.positional(mPositionalOptions);

   po::store(cmdLineParser.run(), mOptionsMap);*/

   //parse config file
   if( !mConfigOptions.options().empty() )
   {  
      ifstream configFile;
      if(!mConfigFilePath.empty()) 
      {
         configFile.open(mConfigFilePath.c_str(), ios_base::in);
         if(configFile.fail() || configFile.bad())
         {
            char buffer[512] = {0};
            strerror_s(buffer, sizeof(buffer), errno);
            throw runtime_error(
               "Error reading config file: " + mConfigFilePath +  ". " + 
               buffer);
         }
      }

      po::store( po::parse_config_file(configFile, mConfigOptions,allow_unregistered), mOptionsMap ); 
      notify(mOptionsMap);     
   }   
}

//*************************************************************************************************
//                                   for later use
//*************************************************************************************************
//void Configuration::initCommandLineOptions(po::options_description& cmdLineOptions)
//{   
//   cmdLineOptions.add(genericOptions());
//      
//   mVisibleOptions.add(genericOptions());                 
//
//   if( !mConfigOptions.options().empty() )
//   {
//      cmdLineOptions.add(mConfigOptions);
//      mVisibleOptions.add(mConfigOptions);
//   }
//
//   if( !mDebugOptions.options().empty() )
//   {
//      cmdLineOptions.add(mDebugOptions);
//      visibleOptions_.add(mDebugOptions);
//   }
//
//   if( !mHiddenOptions.options().empty() )
//   {
//      cmdLineOptions.add(mHiddenOptions);
//   }
//}