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
#include "TrentinoCoreBootstrappingRuntimeConfiguration.h"

//standard
#include <boost/program_options.hpp>
#include <boost/filesystem/path.hpp>

//specific
#include "../../Utils/TrentinoUtilsEnvironment.h"
#include "../../Utils/TrentinoUtilsLogging.h"

using Trentino::Core::Bootstrapping::RuntimeConfiguration;
namespace po = boost::program_options;
namespace fs = boost::filesystem;
namespace Environment = Trentino::Utils::Environment;
using namespace std;

//class RuntimeConfiguration
//static memmber initialization
const string RuntimeConfiguration::DefaultConfigFilePath = "../cfg/Runtime.conf";

//construction
RuntimeConfiguration::RuntimeConfiguration(const char* configFile,RuntimeConfiguration::Source source)
   : mConfiguration(configFilePath(source,configFile))
   {
   initOptions();
   mConfiguration.parse();
   }

RuntimeConfiguration::RuntimeConfiguration(RuntimeConfiguration::Source source)
   : mConfiguration(configFilePath(source,nullptr))
   {
   initOptions();
   mConfiguration.parse();
   }

RuntimeConfiguration::RuntimeConfiguration(const std::string& configFilePath)
   : mConfiguration(configFilePath)
   {
   initOptions();
   mConfiguration.parse();
   }

//services
string RuntimeConfiguration::log4cplusConfigFilePath() const
   {
   assert(mConfiguration.optionsMap().count("Logging.Log4CPlusConfigFile") != 0);
   const string relativePath = 
      mConfiguration.optionsMap()["Logging.Log4CPlusConfigFile"].as<std::string>();
   if(relativePath.empty())
      return relativePath;
   return ( fs::path(Environment::executablePath()).parent_path() / 
      fs::path(relativePath) ).string();    
   }

bool RuntimeConfiguration::enableLocalServiceDiscovery() const
   {
   assert(mConfiguration.optionsMap().count("Service_Discovery.enable.local.service.discovery") != 0);
   const bool localServiceDiscoveryEnabled = 
      mConfiguration.optionsMap()["Service_Discovery.enable.local.service.discovery"].as<bool>();
   return localServiceDiscoveryEnabled;
   }

bool RuntimeConfiguration::enableRemoteServiceDiscovery() const
   {
   assert(mConfiguration.optionsMap().count("Service_Discovery.enable.remote.service.discovery") != 0);
   const bool remoteServiceDiscoveryEnabled = 
      mConfiguration.optionsMap()["Service_Discovery.enable.remote.service.discovery"].as<bool>();
   return remoteServiceDiscoveryEnabled;
   }

bool RuntimeConfiguration::startDiscoveryProxy() const
   {
   assert(mConfiguration.optionsMap().count("Service_Discovery.start.discovery.proxy") != 0);
   const bool discoveryProxyStarted = 
      mConfiguration.optionsMap()["Service_Discovery.start.discovery.proxy"].as<bool>();
   return discoveryProxyStarted;
   }

int RuntimeConfiguration::discoveryMaxRetry() const
   {
   assert(mConfiguration.optionsMap().count("Service_Discovery.discovery.max.retry") != 0);
   const int discoveryMaxRetryTimes = 
      mConfiguration.optionsMap()["Service_Discovery.discovery.max.retry"].as<int>();
   return discoveryMaxRetryTimes;
   }

int RuntimeConfiguration::discoveryRetryInterval() const
   {
   assert(mConfiguration.optionsMap().count("Service_Discovery.discovery.retry.interval") != 0);
   const int discoveryRetryIntervalSec = 
      mConfiguration.optionsMap()["Service_Discovery.discovery.retry.interval"].as<int>();
   return discoveryRetryIntervalSec;
   }

std::string RuntimeConfiguration::getContributionFolder() const 
   {
   assert(mConfiguration.optionsMap().count("Domain.contributions.dir") != 0);
   string cfolder = 
      mConfiguration.optionsMap()["Domain.contributions.dir"].as<std::string>();
   return cfolder;
   }

bool RuntimeConfiguration::lazyDiscoveryOnEagerFailed() const
   {
   assert(mConfiguration.optionsMap().count("Service_Discovery.lazy.discovery.on.eager.failed") != 0);
   const bool lazyDiscoveryWhenEagerFailed = 
      mConfiguration.optionsMap()["Service_Discovery.lazy.discovery.on.eager.failed"].as<bool>();
   return lazyDiscoveryWhenEagerFailed;
   }

//management
void RuntimeConfiguration::initOptions()
{
   std::string defContribDir = (fs::path(Environment::executablePath()).parent_path() 
      / fs::path("contributions")).string();

   mConfiguration.configOptions().add_options()
      ("Domain.URI", po::value<string>()->default_value("trentino.siemens.com"))
      ("Logging.Log4CPlusConfigFile", po::value<string>()->default_value(""))
      ("Service_Discovery.enable.local.service.discovery", po::value<bool>()->default_value(true))
      ("Service_Discovery.enable.remote.service.discovery", po::value<bool>()->default_value(true))
      ("Service_Discovery.start.discovery.proxy", po::value<bool>()->default_value(true))
      ("Service_Discovery.discovery.max.retry", po::value<int>()->default_value(3))
      ("Service_Discovery.discovery.retry.interval", po::value<int>()->default_value(10))
      ("Service_Discovery.lazy.discovery.on.eager.failed", po::value<bool>()->default_value(true))
      ("Binding.binding.conf.file", po::value<std::string>()->default_value( "Binding.conf"))
      ("Domain.contributions.dir", po::value<std::string>()->default_value( defContribDir))
      ("Safe_Invocation.enable", po::value<bool>()->default_value(false))
      ("Contribution_AutoLoad.Contribution", po::value<vector<string> >());
}

string RuntimeConfiguration::configFilePath(RuntimeConfiguration::Source source,const char* configFile) const
   {
   switch(source)
      {
      case DefaultValues: return "";
      case DefaultConfigFile:
         if(configFile ==nullptr || std::string(configFile) == ""){
            logInfo("Using default configuration file");
            return ( fs::path(Environment::executablePath()).parent_path() / 
               fs::path(DefaultConfigFilePath) ).string();
            }
         else{ 
            std::string msg ="Using custom configuration file : ";
            msg+=configFile;
            logInfo(msg.c_str());
            return ( fs::path(configFile)).string();   
            }


      default: assert(false);
      }
   return string();
   }
