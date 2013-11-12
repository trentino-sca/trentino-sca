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
   
#ifndef TrentinoUtilsConfigurationH
#define TrentinoUtilsConfigurationH

//standard
#include <string>

#pragma warning(push)
#pragma warning(disable:4512)
   #include <boost/program_options.hpp>
#pragma warning(pop)

#ifdef WIN32
   #ifdef UTILS_EXPORTS
      #define CONFIGURATION_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define CONFIGURATION_IMPORT_EXPORT __declspec(dllimport)       
   #endif //UTILS_EXPORTS
#else
   #define CONFIGURATION_IMPORT_EXPORT
#endif //WIN32

namespace Trentino{
namespace Utils
{
   //**********************************************************************************************
   //                                        Configuration                               
   //**********************************************************************************************
   //! \ingroup Utils
   //! \brief Class to be used for parsing configuration options from command line and ini-
   //!        like configuration files.
   //!
   //! The configuration class is a wrapper around certain boost::program_option functionalities
   //! encapsulating the logic for parsing the command line and configuration files and offering 
   //! the clients a predefined set of option categories. 
   //! 
   //! The available options should be defined by populating the corresponding
   //! program_options::options_description instances (that can be retrieved via public member
   //! functions).
   //! \par Example: 
   //! \code
   //! Configuration config("file.conf");
   //! 
   //! config.configOptions().add_options()
   //!         ("Section1.option1", po::value<int>())
   //!         ("Section1.option2", po::value<std::string>());
   //! \endcode
   //! \sa configOptions()
   //**********************************************************************************************
   class Configuration
   {
      //construction
   public:
      //*******************************************************************************************
      //                                        Configuration()                              
      //*******************************************************************************************
      //! \brief Constructs a Configuration instance with the given argc, argv and 
      //!        configuration file path.
      //! \param[in] argc Command line argument count as passed to main()
      //! \param[in] argv Command line argument array as passed to main()
      //! \param[in] configFilePath Path to the configuration file to be parsed. An empty string
      //!            (the default value) may be passed to indicate that no configuration file 
      //!            should be used.
      //*******************************************************************************************
      CONFIGURATION_IMPORT_EXPORT Configuration( int argc
                                               , char* argv[]
                                               , const std::string& configFilePath = "");
      
      //*******************************************************************************************
      //                                         Configuration()                               
      //*******************************************************************************************
      //! \brief Constructs a Configuration instance with the given configuration file path.
      //! \param[in] configFilePath Path to the configuration file. An empty string
      //!            (the default value) may be passed to indicate that no configuration file 
      //!            should be used. This can be used to make the default values specified for the
      //!            options to be applied without to parse the command line and/or a configuration
      //!            file.
      //*******************************************************************************************
      CONFIGURATION_IMPORT_EXPORT explicit Configuration(const std::string& configFilePath = "");   
   private:
      //*******************************************************************************************
      //                                  Configuration(const Configuration&)                               
      //*******************************************************************************************
      //! \brief Disallow copying.
      //*******************************************************************************************
      Configuration(const Configuration&);

      //operators
   private:
      //*******************************************************************************************
      //                                        operator=()                               
      //*******************************************************************************************
      //! \brief Disallow assignment.
      //*******************************************************************************************
      void operator=(const Configuration&);      

      //services
   public: 
      //*******************************************************************************************
      //                                        parse()                               
      //*******************************************************************************************
      //! \brief Calls necessary boost::program_options functionalities in order to parse arguments
      //!        from the command line and a configuration file.
      //!    
      //! \throw std::runtime_error Indicated an error in reading the configuration file
      //! \throw boost::program_options::unknown_option If an unknown options is encountered. 
      //! \attention The method throws also all the exception defined in boost::program_options. 
      //!            In particular boost::progrm_options::unknown_argument is thrown whenever an 
      //!            unregistered argument is encountered on the command line or in the 
      //!            configuration file.
      //*******************************************************************************************
      CONFIGURATION_IMPORT_EXPORT void parse(bool allow_unregistered=false);

      //*******************************************************************************************
      //                                        optionsMap()                               
      //*******************************************************************************************
      //! \brief Returns the map containing values of the parsed arguments.
      //! \return Const reference to the map containing values of the parsed arguments.
      //*******************************************************************************************
      const boost::program_options::variables_map& optionsMap() const;
      
      //*******************************************************************************************
      //                                        configOptions()                               
      //*******************************************************************************************
      //! \brief Returns the options_description object containing options that should be available
      //!        in the configuration file.
      //!
      //! This method is supposed to be used by derived classes in order to add their own 
      //! configuration options.  
      //! \return Reference to the options_description object for configuration file options.
      //*******************************************************************************************
      boost::program_options::options_description& configOptions();

      const std::string getConfigFilepath() const;

      //*******************************************************************************************
      //                                   for later use
      //*******************************************************************************************
      /*boost::program_options::options_description& genericOptions();
      boost::program_options::options_description& hiddenOptions();
      boost::program_options::positional_options_description& positionalOptions();      
      boost::program_options::options_description& debugOptions();
      bool showHelp() const;*/    
     
   /*private:
      void initCommandLineOptions(po::options_description& cmdLineOptions)*/
      
      //data
   private:
      //! argc as passed to main
      const int mArgc;
      //! argv as passed to main
      char* const * const mArgv;
      //! path to the configuration file
      const std::string mConfigFilePath;
      //! contains options for configuration files (should be populated by derived classes)
      boost::program_options::options_description mConfigOptions;
      //! map containing the vlaues of the parsed option (populated during the parsing process)
      boost::program_options::variables_map mOptionsMap;
      //*******************************************************************************************
      //                                   for later use
      //*******************************************************************************************
      /*boost::program_options::options_description mGenericOptions;
      boost::program_options::options_description mHiddenOptions;
      boost::program_options::positional_options_description mPositionalOptions;      
      boost::program_options::options_description mDebugOptions;
      boost::program_options::options_description mVisibleOptions;*/            
   
   }; //class Configration

   #include "TrentinoUtilsConfiguration.inl"

} //namespace Utils
} //namespace Trentino

#endif //TrentinoUtilsConfigurationH
