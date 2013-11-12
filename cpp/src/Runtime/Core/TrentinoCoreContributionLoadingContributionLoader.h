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

#ifndef TrentinoCoreContributionLoadingContributionLoaderH
#define TrentinoCoreContributionLoadingContributionLoaderH

//baseclass 
#include "TrentinoCoreContributionLoadingErrorReporter.h"

//standard
#include <string>

//specific
#include "TrentinoCore.h"
#include "TrentinoCoreContributionLoadingDeployer.h"
#include "TrentinoCoreContributionLoadingInstaller.h"
#include "TrentinoCoreContributionLoadingRunner.h"
#include "../RuntimeModel/TrentinoRuntimeModel.h"
#include "../../Utils/TrentinoUtilsURI.h"
#include "../../Utils/TrentinoUtilsDataObject.h"

#ifdef WIN32
   #ifdef CORE_EXPORTS
      #define CONTRIBUTIONLOADER_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define CONTRIBUTIONLOADER_IMPORT_EXPORT __declspec(dllimport)       
   #endif //CORE_EXPORTS
#else
   #define CONTRIBUTIONLOADER_IMPORT_EXPORT
#endif //WIN32

namespace Trentino{
namespace Core{
namespace ContributionLoading
{
   //**********************************************************************************************
   //                                     ContributionLoader 
   //**********************************************************************************************
   //! \ingroup ContributionLoading
   //! \brief A facade class offering a convenient interface to functionality related to 
   //!        contribution loading (installing, deploying, running).
   //!
   //! The actualy functionality is provided by further classes from the Core::ContributionLoading
   //! namespace. In using the ContributionLoader, the client doesn't need to directly interact 
   //! with these classes. 
   //**********************************************************************************************
   class ContributionLoader : public ErrorReporter
   {
      //construction
   public:
      //*******************************************************************************************
      //                                  ContributionLoader()
      //*******************************************************************************************
      //! \brief Constructs a ContributionLoader instance that uses 
      //!        ContributionLoading::LoggingErrorHandler as the default error handler.        
      //*******************************************************************************************
      ContributionLoader();

      //*******************************************************************************************
      //                                 ~ContributionLoader()
      //*******************************************************************************************
      //! \brief Empty destructor.      
      //*******************************************************************************************
      ~ContributionLoader();
   private:
      //*******************************************************************************************
      //                        ContributionLoader(const ContributionLoader&);
      //*******************************************************************************************
      //! \brief Disallow inadvertent copying.      
      //*******************************************************************************************
      ContributionLoader(const ContributionLoader&);

      //operators
   private:
      //*******************************************************************************************
      //                                      operator=()
      //*******************************************************************************************
      //! \brief Disallow inadvertent assignment.      
      //*******************************************************************************************
      void operator=(const ContributionLoader&);

      //services
   public:
      //*******************************************************************************************
      //                                    setErrorHandler()
      //*******************************************************************************************
      //override from ErrorReporter (see documentation in ErrorReporter)
      //! \copydoc ContributionLoading::ErrorReporter::setErrorHandler()
      //*******************************************************************************************
      CONTRIBUTIONLOADER_IMPORT_EXPORT  
         void setErrorHandler(const ErrorHandlerBasePtr& errorHandler);

      //*******************************************************************************************
      //                                        install()
      //*******************************************************************************************
      //! \copydoc ContributionLoading::Installer::install()
      //*******************************************************************************************
      CONTRIBUTIONLOADER_IMPORT_EXPORT 
         Trentino::RuntimeModel::ContributionPtr install( const std::string& contributionPath
                                                     , const Trentino::Utils::URI& baseURI);
      //*******************************************************************************************
      //                                        readSCAConfigFile()
      //*******************************************************************************************
      //! \copydoc ContributionLoading::Installer::readSCAConfigFile()
      //*******************************************************************************************
      CONTRIBUTIONLOADER_IMPORT_EXPORT
      void ContributionLoader::readSCAConfigFile(Trentino::Core::ContributionLoading::ContributionConfigFile& confFile
                                           ,const std::string& contributionPath);

      //*******************************************************************************************
      //                                        deploy()
      //*******************************************************************************************
      //! \copydoc ContributionLoading::Deployer::deploy()
      //*******************************************************************************************
      CONTRIBUTIONLOADER_IMPORT_EXPORT void deploy(
         const Trentino::RuntimeModel::ContributionPtr& contribution);

      //*******************************************************************************************
      //                                         run()
      //*******************************************************************************************
      //! \copydoc ContributionLoading::Runner::run()
      //*******************************************************************************************
      CONTRIBUTIONLOADER_IMPORT_EXPORT void run(
         const Trentino::RuntimeModel::ContributionPtr& contribution);

      //*******************************************************************************************
      //                                         stop()
      //*******************************************************************************************
      //! \copydoc ContributionLoading::Runner::stop()
      //*******************************************************************************************
      CONTRIBUTIONLOADER_IMPORT_EXPORT void stop(
         const Trentino::RuntimeModel::ContributionPtr& contribution);

      //*******************************************************************************************
      //                                       uninstall()
      //*******************************************************************************************
      //! \copydoc ContributionLoading::Installer::uninstall()
      //*******************************************************************************************
      CONTRIBUTIONLOADER_IMPORT_EXPORT void uninstall(
         const Trentino::RuntimeModel::ContributionPtr& contribution);

      //*******************************************************************************************
      //                                       undeploy()
      //*******************************************************************************************
      //! \copydoc ContributionLoading::Deployer::undeploy()
      //*******************************************************************************************
      CONTRIBUTIONLOADER_IMPORT_EXPORT void undeploy(
         const Trentino::RuntimeModel::ContributionPtr& contribution);

      //*******************************************************************************************
      //! \name convenience methods 
      //! @{
      //*******************************************************************************************
      
      //*******************************************************************************************
      //                                        remove()
      //*******************************************************************************************
      //! \brief Convenience method for removing a contribution independently of its state.
      //!      
      //! \param[in] contribution A shared pointer to the contribution to remove.  
      //! \sa stop(), undeploy(), uninstall()
      //*******************************************************************************************
      CONTRIBUTIONLOADER_IMPORT_EXPORT void remove(
         const Trentino::RuntimeModel::ContributionPtr& contribution);
      //! @}

      //data
   private:
      //! The deplloy() and undeploy() methods are forwared to this object.
      Deployer mDeployer;
      //! The run() and stop() methods are forwared to this object. 
      Runner mRunner;
   }; //class ContributionLoader
} //namespace ContributionLoading
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreContributionLoadingContributionLoaderH
