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

#ifndef TrentinoCoreContributionLoadingInstallerH
#define TrentinoCoreContributionLoadingInstallerH

//standard
#include <string>
#include <set>

//specific
#include "../RuntimeModel/TrentinoRuntimeModel.h"
#include "../../Utils/TrentinoUtilsURI.h"
#include "../../Utils/TrentinoUtilsDataObject.h"

namespace Trentino{
namespace Core{
namespace ContributionLoading
{  
   
   //**********************************************************************************************
   //                                       ContributionConfigFile 
   //**********************************************************************************************
   //! \ingroup ContributionLoading
   //! \brief Contains data from sca-contribution.conf
   //**********************************************************************************************
  struct ContributionConfigFile
     {
        std::set<std::string> mBusinessDLLsList;
        std::set<std::string> mThirdPartyDLLDirsList;
        std::string mContributionVersion;
        std::string mRealContributionPath;
     }; //ContributionConfigFile
   

   //**********************************************************************************************
   //                                       Installer 
   //**********************************************************************************************
   //! \ingroup ContributionLoading
   //! \brief Responsible for putting a contribution into the 
   //!        RuntimeModel::Contribution::Installed state. 
   //!
   //! For clients, it's not necessary no use the Installer class directly, instead its  
   //! functionality is provided through the facade class ContributionLoader. 
   //! 
   //! Currently, Installer has no member data and therefore offers only static methods. This isn't
   //! a fundamental design decision - data may be added in future if necessary. 
   //**********************************************************************************************
   class Installer
   {
      //construction
   private:
      //*******************************************************************************************
      //                                      Installer()
      //*******************************************************************************************
      //! \brief Disallow construction (class has only static methods and no data).      
      //*******************************************************************************************
      Installer();

      //*******************************************************************************************
      //                                      ~Installer()
      //*******************************************************************************************
      //! \brief Disallow destruction (class has only static members and no data).   
      //*******************************************************************************************
      ~Installer();
      //*******************************************************************************************
      //                               Installer(const Installer&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copying.      
      //*******************************************************************************************
      Installer(const Installer&);

      //operators
   private:
      //*******************************************************************************************
      //                                      operator=()
      //*******************************************************************************************
      //! \brief Disallow inadvertent assignment.      
      //*******************************************************************************************
      void operator=(const Installer&);

      //services
   public:

     static  void readSCAConfigFile(ContributionConfigFile& confFile,const std::string& contributionPath);
      //*******************************************************************************************
      //                                         install()
      //*******************************************************************************************
      //! \brief Loads the contribution under the specified path and assigns it the given base URI. 
      //!
      //! During the installation process, following actions take place:
      //! - the \c sca-contribution dynamic library (expected in the \c META-INF folder) is loaded 
      //! - the \c sca-contribution.conf file (expected in the \c META-INF folder) is read
      //! - all the contribution's business logic dynamic libraries referred via the 
      //!   <tt>\<implementatoin.cpp\>/\@library</tt> attribute are loaded
      //! - the generated %SCA model loader code is executed in order to construct an in-memory
      //!   representation of the contribution's SCDL definitions
      //! - a RuntimeModel::Contribution object is created and put into the 
      //!   RuntimeModel::Contribution::Installed state. 
      //!
      //! \param[in] contributionPath Path to the contribution to be installed.
      //! \param[in] baseURI Base URI to be assigned to the contribution.
      //! \return A shared pointer to the Contribution object representing the installed 
      //!         contribution.
      //! \throw std::runtime_error In case the \c sca-contribution.conf file couldn't be read.
      //! \throw std::runtime_error In case the \c sca-contribution dynamic library or one of the 
      //!        business logic dynamic libraries couldn't be load. 
      //! \sa uninstall()
      //*******************************************************************************************
      static Trentino::RuntimeModel::ContributionPtr install( const std::string& contributionPath
                                                            , const Trentino::Utils::URI& baseURI);
      
      //*******************************************************************************************
      //                                       uninstall()
      //*******************************************************************************************
      //! \brief Assigns the given contribution the RuntimeModel::Contribution::None state.  
      //!
      //! This is the only action currently performed by the uninstall() method. Actions performed
      //! by the install() method (such as loading dynamic libraries and constructing the %SCA
      //! Model) <b>are not reverted by uninstall() but rather during the destruction of the 
      //! Contribution object returned by the install() method.</b> 
      //!
      //! Largely, the uninstall() method is reserved for future use in order to perform possible 
      //! additional actions needed during the uninstallation (that cannot be performed on 
      //! destruction of the Contribution object).Therefore, from the client's point of view, the 
      //! uninstall() method should be always called before a Contribution object is destructed. 
      //! Otherwise a consistent behavior cannot be guaranteed. 
      //! 
      //! \param[in] contribution A shared pointer to the contribution to be uninstalled. The
      //!            given contribution must be in RuntimeModel::Contribution::Installed state. 
      //! \throw std::invalid_argument In case the given contribution is not in the 
      //!        RuntimeModel::Contribution::Installed state.
      //! \sa install()
      //*******************************************************************************************
      static void uninstall(const Trentino::RuntimeModel::ContributionPtr& contribution);

   }; //class Installer

} //namespace ContributionLoading
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreContributionLoadingInstallerH