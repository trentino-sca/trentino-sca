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
#include "TrentinoCoreContributionLoadingInstaller.h"

//standard
#include <stdexcept>
#include <vector>
#include <set>
#include <fstream>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#pragma warning(push)
#pragma warning(disable:4100 4512)
#include <boost/algorithm/string.hpp>
#pragma warning(pop)

//specific
#include "../../Global/TrentinoGlobal.h"
#include "TrentinoCoreContributionLoadingSCAModelLoader.h"
#include "TrentinoCoreContributionLoadingRuntimeModelCreator.h"
#include "../RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../RuntimeModel/TrentinoRuntimeModelCommonFuncs.h"
#include "../SCAModel/TrentinoSCAModelModelDescriptor.h"
#include "../../Utils/TrentinoUtilsLogging.h"
#include "../../Utils/TrentinoUtilsEnvironment.h"
#include "../../Utils/TrentinoUtilsDynamicLibrary.h"
#include "../../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"
#include "TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "TrentinoCoreBootstrappingRuntimeConfiguration.h"


using namespace Trentino;
using namespace std;
using Trentino::Core::ContributionLoading::Installer;
using Trentino::Core::ContributionLoading::RuntimeModelCreator;
using Trentino::Utils::DynamicLibraryPtr;
using Trentino::Utils::DynamicLibrary;
namespace fs = boost::filesystem;
namespace SCAModel = Trentino::SCA::Model;

namespace
   {
   //constants
   const string GetContributionInfoFuncName  = "getContributionInfo";

   //functions
   //**********************************************************************************************
   //                           deleterDynamicLibraryUnloader()
   //**********************************************************************************************
   //! \brief Custom deleter used by boost::shared_pointer in order to automatically unload a 
   //!        dynamic library as soons as the corresponding Trentino::Utils::DynamicLibrary object
   //!        is destructed. 
   //! \param[in] ptr Raw pointer to the Trentino::Utils::DynamicLibrary object.
   //**********************************************************************************************
   void deleterDynamicLibraryUnloader(DynamicLibrary* ptr)
      {
      HLOGGER();   
      assert(ptr != nullptr);

      if(ptr->isLoaded())
         {
         // once should be sufficient
         ptr->unload(DynamicLibrary::Once);
         }

      delete ptr;
      }

   //**********************************************************************************************
   //                                  makeContributionDLLPath()
   //**********************************************************************************************
   //! \brief Constructs the path to the contribution's dynamic library.
   //!
   //! The name of the expected dynamic library is \c sca-contribution.dll on Windows and
   //! \c libsca-contribution.so on Linux. 
   //! \param[in] constributionPath Path to the contribution's root directory.  
   //! \return The full file path to the contribution dynamic library.
   //**********************************************************************************************
   const string makeContributionDLLPath(const string& contributionPath) 
      {
      HLOGGER();   
      const string contributionDLLSuffix = "/META-INF/" + 
         Trentino::Utils::Environment::makeDLLName("sca-contribution");
      return contributionPath + contributionDLLSuffix;
      }

   //**********************************************************************************************
   //                           makeContributionConfigurationFilePath()
   //**********************************************************************************************
   //! \brief Constructs the path to the contribution's configuration file. 
   //! \param[in] constributionPath Path to the contribution's root directory.  
   //! \return The full file path to the contribution's configuration file. 
   //! \sa loadBusinessDLLs()
   //**********************************************************************************************
   const string makeContributionConfigurationFilePath(const string& constributionPath)
      {
      HLOGGER();   
      return constributionPath + "/META-INF/sca-contribution.conf";
      }


   //**********************************************************************************************
   //                           normalizeFile()
   //**********************************************************************************************
   //! \brief create a normalized native system path and return the corresponding string. 
   //! throw a runtime_error if the file or the directory does not exists
   //! \param[in]  Path ttp be normalized. A file or directory.  
   //! \return String representation of the file 
   //! \sa readConfigFile()
   //**********************************************************************************************
   std::string normalizeFile(fs::path& dllPath)
      {
      dllPath.make_preferred();
      fs::path absPath = fs::absolute(dllPath);
      absPath.normalize();
      if(!fs::exists(absPath))
         {
         std::string val = dllPath.string();
         throw std::runtime_error("File or directory does not exists "+ val);
         }

      return absPath.string();
      }


   //**********************************************************************************************
   //                                 readConfigFile()
   //**********************************************************************************************
   //! \brief Returns a collection of full paths to all the business logic dynamic libraries   
   //!        referred via the <tt>\<implementatoin.cpp\>/\@library</tt> attribute.
   //! 
   //! This function uses the \c sca-conribution.conf file in order to retrieve the necessary 
   //! information. This file is expected to contain a list of relative (to the contribution's
   //! root directory) paths to the business logic libraries without any platform specific file
   //! extensions or prefixes.
   //!
   //! \param[in] contributionPathPath to the contribution's root directory.  
   //! \param[out] businessDLLsList Reference to an \c std::vector that will contain the 
   //!             the computed paths after the functions returns. 
   //!
   //! \par Example
   //! Given the following exemplary content of \c sca-contribution.conf: \n
   //! <tt>./Component1/Component1</tt>\n
   //! <tt>./Component2</tt>\n
   //! and assuming \c C:/contr as the contribution's root directory, 
   //! readConfigFile() will return the following paths on Windows: \n
   //! <tt>C:/contr/Component1/Component1.dll</tt> \n
   //! <tt>C:/contr/Component2.dll</tt>
   //! \sa loadBusinessDLLs()
   //**********************************************************************************************
   void readConfigFile(Trentino::Core::ContributionLoading::ContributionConfigFile& confFile, const string& contributionPath)
      {
      HLOGGER();   
      HLOGGER_INFO(contributionPath.c_str());
      ifstream contribConfigFile;
      const string configContributionFilePath = 
         makeContributionConfigurationFilePath(contributionPath);
      contribConfigFile.open(configContributionFilePath.c_str(), ios_base::in);
      if(contribConfigFile.fail() || contribConfigFile.bad())
         {
         char buffer[512] = {0};
         strerror_s(buffer, sizeof(buffer), errno);
         throw runtime_error(
            "Error reading contribution config file: " + configContributionFilePath +  
            ". Error:" + buffer);
         }

      while(!contribConfigFile.eof())
         {
         string strLine;
         getline(contribConfigFile, strLine);
         boost::algorithm::trim(strLine);
         bool isDir = false;
         bool isRelative = false;
         if(strLine.find('#') != string::npos || strLine.empty() == true)
            {
            //comment line will also consider lines containing # anywhere. So it should be documented for end user
            continue;
            }

         //check if it is a directory
         //it is not sufficient to just check if it starts with dir, since a directory could have the name "dir".
         //therefor we check if we have "dir " or "dir="
         if(strLine.find("Contribution.Version=")==0)
            {
             strLine = strLine.substr(21);
             confFile.mContributionVersion = strLine;
             continue;
            }
         if(strLine.find("dir ")==0 || strLine.find("dir=")==0)
            {
            //The input is a directory
            isDir=true;
            //remove the dir part and trim
            strLine = strLine.substr(3);
            boost::algorithm::trim(strLine);
            //remove the equal char
            if(strLine.find("=") == string::npos)
               {
               //invalid input. charachter = expected. It is better not to deploy this
               throw std::runtime_error("invalid input in sca-contribution.conf. Directory entry should have the form dir=<path/to/directory>,\n"
                  "where the path can be relative or absolute. relative paths should start with '.'");
               }
            strLine =strLine.substr(1);
            boost::algorithm::trim(strLine);
            //check if the path is relative and create the absolute path
            if(strLine.find(".")==0)
               {
               isRelative = true;
               }
            if(isRelative)
               {
               fs::path dllPath = fs::path(contributionPath) /fs::path(strLine);
               confFile.mThirdPartyDLLDirsList.insert(normalizeFile(dllPath));
               }
            else
               {
               fs::path dllPath = fs::path(strLine);
               confFile.mThirdPartyDLLDirsList.insert(normalizeFile(dllPath));
               }

            }
         else
            {
            const string dllName = Utils::Environment::makeDLLName(fs::path(strLine).filename().string());
            fs::path dllPath = 
               fs::path(contributionPath) / fs::path(strLine).parent_path() / fs::path(dllName);
            if(fs::exists(dllPath))
               {
               confFile.mBusinessDLLsList.insert(normalizeFile(dllPath));
               continue;
               }

            BOOST_FOREACH( const std::string& dllDir , confFile.mThirdPartyDLLDirsList )
               {
               fs::path aPath = 
                  fs::path(dllDir) / fs::path(dllName);
               if(fs::exists(aPath))
                  {
                  confFile.mBusinessDLLsList.insert(normalizeFile(aPath));
                  continue;
                  }
               }
            }
         }
      }


   //**********************************************************************************************
   //                                     loadBusinessDLLs()
   //**********************************************************************************************
   //! \brief Loads the dynamic libraries under the given paths.
   //!
   //! \param[in] fileList A collection of full paths to the libraries to load.
   //! \param[in] dirlist a collection of folder where dll dependencies can be found
   //! \param[out] loadedBusinessDLLs Reference to an \c std::vector that will contain shared 
   //!             pointers to Trentino::Utils::DynamicLibrary objects representing the loaded 
   //!             dynamic libraries after the function returns. 
   //**********************************************************************************************
   void loadBusinessDLLs( const set<string>& fileList
      , const set<string>& dirlist
      , vector<DynamicLibraryPtr>& loadedBusinessDLLs)
      {
      HLOGGER();  

      BOOST_FOREACH(const string& fileName, fileList)
         {
         const DynamicLibraryPtr dll(new DynamicLibrary(fileName), deleterDynamicLibraryUnloader);
         if(dirlist.size()==0)
            {
            dll->load();
            }
         else
            {
            dll->load(dirlist);
            }

         assert(dll->isLoaded());      
         loadedBusinessDLLs.push_back(dll);
         }
      }

   } //namespace

//class Installer
//services

   void Installer::readSCAConfigFile(Trentino::Core::ContributionLoading::ContributionConfigFile& confFile,
      const std::string& contributionPath)
   {
      HLOGGER();
      HLOGGER_INFO(contributionPath.c_str());
      std::string contPath = contributionPath;
   if(!fs::exists(contributionPath))
      {
         //get real path
         using namespace Trentino::Core::Bootstrapping;
         const RuntimeBootstrapper& bootstrapper = RuntimeBootstrapper::instance();
         RuntimeBootstrapper::RuntimeConfigurationConstPtr conf= bootstrapper.configuration();
         std::string contFolder = conf->getContributionFolder();
         contPath = (fs::path(contFolder) / fs::path(contributionPath)).string();
      }
    //first load conf file
     confFile.mRealContributionPath = contPath;
     readConfigFile(confFile, contPath);
   }

RuntimeModel::ContributionPtr Installer::install( const string& contributionPath 
   , const Utils::URI& baseURI )
   {
   Trentino::Core::ContributionLoading::ContributionConfigFile confFile;
   std::string& contPath = confFile.mRealContributionPath;
   readSCAConfigFile(confFile,contributionPath);
   vector<DynamicLibraryPtr> businessDlls;
   loadBusinessDLLs(confFile.mBusinessDLLsList, confFile.mThirdPartyDLLDirsList, businessDlls);

   const string dllPath = makeContributionDLLPath(contPath);

   const DynamicLibraryPtr dll(new DynamicLibrary(dllPath), deleterDynamicLibraryUnloader);
   dll->load();
   assert(dll->isLoaded());   

   typedef Core::TrentinoContributionInfo* (TRENTINO_CDECL *GetContributionInfoFunc) ();
   const GetContributionInfoFunc getContributionInfo = 
      dll->functionAddress<GetContributionInfoFunc>(GetContributionInfoFuncName);
   assert(getContributionInfo);
   Core::TrentinoContributionInfo* contributionInfo = getContributionInfo();

   const SCAModel::ModelDescriptorPtr modelDescriptor = 
      boost::make_shared<SCAModel::ModelDescriptor>();
   Core::ContributionLoading::SCAModelLoader modelLoader(*modelDescriptor);
   contributionInfo->loadModel(&modelLoader);


   logInfo("installing contribution '%s'...", contPath.c_str() );
   const RuntimeModel::ContributionPtr contribution  = 
      RuntimeModelCreator::createContribution( modelDescriptor
      , baseURI                                                   
      , contPath 
      , dll
      , businessDlls
      , contributionInfo);
   contribution->setState(RuntimeModel::Contribution::Installed);
   contribution->setVersion(confFile.mContributionVersion);
   logInfo("contribution '%s' installed!", contPath.c_str());

   return contribution;
   }

void Installer::uninstall(const RuntimeModel::ContributionPtr& contribution) 
   {     
   if( contribution->state() != RuntimeModel::Contribution::Installed )
      {
      throw invalid_argument( 
         "Cannot uninstall a contribution that is in '" + 
         RuntimeModel::CommonFuncs::toString( contribution->state() ) + "' state. First undeploy." );       
      }

   contribution->setState(RuntimeModel::Contribution::None);
   }
