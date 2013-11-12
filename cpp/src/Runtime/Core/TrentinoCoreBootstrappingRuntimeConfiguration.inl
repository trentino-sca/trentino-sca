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
#include <boost/program_options.hpp>

//class RuntimeConfiguration
//services

inline const Trentino::Utils::Configuration& RuntimeConfiguration::getConfiguration() const
{
   return mConfiguration;
}

inline Trentino::Utils::URI RuntimeConfiguration::domainURI() const
{
   assert(mConfiguration.optionsMap().count("Domain.URI") != 0);
   return mConfiguration.optionsMap()["Domain.URI"].as<std::string>();
}


inline const std::string RuntimeConfiguration::bindingConfigFilename() const
{
   assert(mConfiguration.optionsMap().count("Binding.binding.conf.file") != 0);
   return mConfiguration.optionsMap()["Binding.binding.conf.file"].as<std::string>();
}

inline bool RuntimeConfiguration::enableSafeInvocation() const
{
   assert(mConfiguration.optionsMap().count("Safe_Invocation.enable") != 0);
   const bool rSafeInvocationEnabled = mConfiguration.optionsMap()["Safe_Invocation.enable"].as<bool>();
   return rSafeInvocationEnabled;
}


inline std::string trim(const std::string &s)
{
   std::string retval =  s.substr(s.find_first_not_of("\t "), retval.length() );
   retval = retval.substr(0, retval.find_last_not_of("\t ")+1);
   return retval;
}

inline std::vector<std::string> split_and_trim(const std::string &s, const std::string &delim)
{
   std::vector<std::string> retval;

   std::string p1 = s.substr(0, s.find_first_of(delim));
   std::string p2 = s.substr( s.find_first_of(delim)+1, s.length());
   p1 = trim(p1);
   p2 = trim(p2);
   retval.push_back(p1);
   retval.push_back(p2);

   return retval;
}

inline std::map<std::string, std::string> RuntimeConfiguration::autoLoadContributions() const
{
  std::map<std::string, std::string> retval;

  if (mConfiguration.optionsMap().count("Contribution_AutoLoad.Contribution") != 0)
  {
     const std::vector<std::string> contributions = mConfiguration.optionsMap()["Contribution_AutoLoad.Contribution"].as<std::vector<std::string>>();
     for (size_t i = 0; i < contributions.size(); i++ )
     {
        std::vector<std::string> cut = split_and_trim(contributions[i], "|");
        if (cut.size()==2)
        {
           std::string uri = cut[0];
           std::string path = cut[1];
           retval[uri]=path;
        }
     }

  }

  return retval;
}
