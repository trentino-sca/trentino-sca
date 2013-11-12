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

#ifndef TrentinoCoreBootstrappingRuntimeConfigurationH
#define TrentinoCoreBootstrappingRuntimeConfigurationH

//standard
#include <string>

//specific
#include "../../Utils/TrentinoUtilsConfiguration.h"
#include "../../Utils/TrentinoUtilsURI.h"

#ifdef WIN32
   #ifdef CORE_EXPORTS
      #define RUNTIMECONFIGURATION_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define RUNTIMECONFIGURATION_IMPORT_EXPORT __declspec(dllimport)       
   #endif //CORE_EXPORTS
#else
   #define RUNTIMECONFIGURATION_IMPORT_EXPORT
#endif //WIN32

namespace Trentino{
namespace Core{
namespace Bootstrapping
{
   //**********************************************************************************************
   //                                      RuntimeConfiguration
   //**********************************************************************************************
   //! \ingroup Bootstrapping
   //! \brief Class for passing options retrieved from a configuration file to RuntimeBootstrapper.
   //!
   //! RuntimeConfiguration internally uses Utils::Configuration for parsing configuration files
   //! and can also be easily extended to take and parse options from the command line because
   //! this functionality is already supported by Utils::Configuration.
   //**********************************************************************************************
   class RuntimeConfiguration 
   {
      //additional
   public:
      enum Source {
         //! \brief The options should be initialized with default values.
         //! 
         //! A default value for each option is specified inside of initOptions().
         //! \attention When adding new options, make sure to explicitly assign them default 
         //!            values. Options for which no default values were provided, \b will \b not  
         //!            be initialized with default constructed values or the like but treated as
         //!            if they aren't present at all. Thus using 
         //!            <tt>mConfiguration.optionsMap()["optionName"]</tt> will lead to undefined 
         //!            behavior in case \c optionName is not present (i.e has no default value).
         DefaultValues, 
         
         //! \brief The options should be initialized with values from the default configuration 
         //!         file.
         //! 
         //! For each option the configuration file doesn't provide a value, the default value is
         //! taken. \n
         //! The path to the default configuration file is constructed as follows: \n
         //! <tt><directory_path_of_the_current_executable>/../cfg/Runtime.conf</tt>
         //! \note <tt><directory_path_of_the_current_executable></tt> is \b not the working 
         //!        directory of the current executable but the physical path to the location  
         //!        of the executable file. 
         DefaultConfigFile};

      //construction
   public:
      //*******************************************************************************************
      //                               RuntimeConfiguration(Source)
      //*******************************************************************************************
      //! \brief Constructs a RuntimeConfiguration with the given Source to take the option values
      //!        from.
      //!
      //! \param[in] source An enumeration value specifying the source to take the option values
      //!            from. See RuntimeConfiguration::Source for a description of the supported
      //!            enumeration values.
      //! \throw std::runtime_error If RuntimeConfiguration::DefaultConfigFile is passed but the
      //!        corresponding file cannot be opened. 
      //! \throw boost::program_options::unkown_option If RuntimeConfiguration::DefaultConfigFile
      //!        is passed and the corresponding configuration file contains an unsupported option. 
      //*******************************************************************************************
      RUNTIMECONFIGURATION_IMPORT_EXPORT 
         explicit RuntimeConfiguration(const char* configFile,Source source = DefaultValues);
      explicit RuntimeConfiguration(Source source = DefaultValues);

      //*******************************************************************************************
      //                          RuntimeConfiguration(const std::string&)
      //*******************************************************************************************
      //! \brief Constructs a RuntimeConfiguration with the given configuration file to take the
      //!        option values from. 
      //!
      //! \param[in] configFilePath Path to a configuration file. For each option the configuration 
      //!            file doesn't provide a value, the default value is taken. For the description
      //!            of possible problems in not specifying default values for options see:
      //!            RuntimeConfiguration::Source. 
      //! \throw std::runtime_error If the specified configuration file cannot be opened.
      //! \throw boost::program_options::unkown_option If the specified configuration file contains
      //!        unsupported options. 
      //*******************************************************************************************
      RUNTIMECONFIGURATION_IMPORT_EXPORT 
         explicit RuntimeConfiguration(const std::string& configFilePath);
   private:
      //*******************************************************************************************
      //                     RuntimeConfiguration(const RuntimeConfiguration&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copy construction.      
      //*******************************************************************************************
      RuntimeConfiguration(const RuntimeConfiguration&);

      //operators
   private:
      //*******************************************************************************************
      //                                      operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.      
      //*******************************************************************************************
      void operator=(const RuntimeConfiguration&);

      //services
   public:

      //*******************************************************************************************
      //                                     dgetConfiguration()
      //*******************************************************************************************
      //! \brief Return the internal configuration object used for this configuration
      //*******************************************************************************************
      const Trentino::Utils::Configuration& getConfiguration() const;
      
      //*******************************************************************************************
      //                                     domainURI()
      //*******************************************************************************************
      //! \brief Returns the value of the \c Domain.URI option.
      //! \return Value of the \c domainURI option. The default value is: \c trentino.siemens.com.
      //*******************************************************************************************
      Trentino::Utils::URI domainURI() const;

      //*******************************************************************************************
      //                                     bindingConfigFilename()
      //*******************************************************************************************
      //! \brief Returns the value of the \c binding.conf.file option.
      //! \return Returns the value of the \c binding.conf.file option. Def value is Binding.conf
      //*******************************************************************************************
      const std::string bindingConfigFilename() const;

      //*******************************************************************************************
      //                                     getContributionFolderByContributionName()
      //*******************************************************************************************
      //! \brief Return path to the contribution folder
      //! \return Path to the contributions folder
      //*******************************************************************************************
      std::string getContributionFolder() const;

      //*******************************************************************************************
      //                                 log4cplusConfigFilePath()
      //*******************************************************************************************
      //! \brief Returns the full path to the configuration file for log4cplus. 
      //!
      //! \return Full path to the configuration file for log4cplus, i.e: 
      //! <tt><directory_path_of_the_current_executable>/<value of the Logging.Log4CPlusConfigFile 
      //! option></tt>\n
      //! The default value (for the \c Logging.Log4CplusConfigFile option itself as well as for
      //! the whole return value of this method) is an empty string. 
      //!
      //! \par Example:
      //! If <tt><directory_path_of_the_current_executable>=C:/Trentino/bin</tt> and
      //! <tt>Logging.Log4CPlusConfigFile=../cfg/log4cplus.properties</tt> then 
      //! <tt>C:/Trentino/bin/../cfg/log4cplus.properties</tt> is returned. 
      //!
      //! \note <tt><directory_path_of_the_current_executable></tt> is \b not the working 
      //!        directory of the current executable but the physical path to the location  
      //!        of the executable file.         
      //*******************************************************************************************
      RUNTIMECONFIGURATION_IMPORT_EXPORT std::string log4cplusConfigFilePath() const;
      RUNTIMECONFIGURATION_IMPORT_EXPORT bool enableLocalServiceDiscovery() const;
      RUNTIMECONFIGURATION_IMPORT_EXPORT bool enableRemoteServiceDiscovery() const;
      RUNTIMECONFIGURATION_IMPORT_EXPORT bool startDiscoveryProxy() const;
      RUNTIMECONFIGURATION_IMPORT_EXPORT int discoveryMaxRetry() const;
      RUNTIMECONFIGURATION_IMPORT_EXPORT int discoveryRetryInterval() const;
      RUNTIMECONFIGURATION_IMPORT_EXPORT bool lazyDiscoveryOnEagerFailed() const;
      RUNTIMECONFIGURATION_IMPORT_EXPORT bool enableSafeInvocation() const;
      RUNTIMECONFIGURATION_IMPORT_EXPORT std::map<std::string,std::string> autoLoadContributions() const;

      //management
   private:
      //*******************************************************************************************
      //                                 initOptions()
      //*******************************************************************************************
      //! \brief Is called on construction and defines the supported options and their default 
      //!        values.
      //!
      //! New options can be added by extending this method. See RuntimeConfiguration::Source for a
      //! discussion on the importance of providing a default value for each option.
      //*******************************************************************************************
      void initOptions();

      //*******************************************************************************************
      //                                     configFilePath()
      //*******************************************************************************************
      //! \brief Returns the configuration file dependen on the passed RuntimeConfguration::Source
      //!        value.
      //!
      //! \return An empty string for source=DefaultValues and a path to the default configuration
      //!         file for source=DefaultConfigurationFile. See documentation for 
      //!         RuntimeConfiguration::Source for a description of how the default configuration
      //!         file path is constructed.
      //*******************************************************************************************
      std::string configFilePath(Source source,const char* configFile) const;

      //data
   private:
      //! Relative path to the default configuration file
      static const std::string DefaultConfigFilePath;
      //! Object providing the logic for parsing options from config files (and the cmd line)
      Trentino::Utils::Configuration mConfiguration;
   
   }; //class RuntimeConfiguration

   #include "TrentinoCoreBootstrappingRuntimeConfiguration.inl"

} //Bootstrapping
} //namespace Core
} //namespace Trentino

#endif // TrentinoCoreBootstrappingRuntimeConfigurationH
