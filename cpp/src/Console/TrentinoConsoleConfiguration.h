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

#ifndef TrentinoConsoleConfigurationH
#define TrentinoConsoleConfigurationH

//standard
#include <string>

//specific
#include "../Utils/TrentinoUtilsConfiguration.h"

namespace Trentino{
namespace Console
{
   //**********************************************************************************************
   //                                      ConsoleConfiguration
   //**********************************************************************************************
   //! \ingroup Console
   //! \brief Class for passing options retrieved from a configuration file to the Console.
   //! 
   //! See Trentino::Core::Bootstrapping::RuntimeConfiguration for the documentation of a similar
   //! class.
   //! \todo Introduces a common base class for ConsoleConfiguration and RuntimeConfiguration and
   //!       rename Utils::Configuration to something having "program options" it its name. 
   //**********************************************************************************************
   class Configuration
   {
      //additional
   public:
      enum Source {DefaultValues, DefaultConfigFile};

      //construction
   public:
      Configuration(Source source = DefaultValues);
      Configuration(const std::string& configFilePath);

      //services
   public:
      std::string runtimeDLLPath() const;        
      std::string runtimeDLLName() const;

      //management
   private:
      void initOptions();
      std::string configFilePath(Source source) const;

      //data
   private:
      static const std::string DefaultConfigFilePath;
      Trentino::Utils::Configuration mConfiguration;
   
   }; //class Configuration

   #include "TrentinoConsoleConfiguration.inl"

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleConfigurationH
