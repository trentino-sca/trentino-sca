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
#include "TrentinoCoreContributionLoadingContributionLoader.h"

//standard
#include <boost/smart_ptr/make_shared.hpp>

//specific
#include "TrentinoCoreContributionLoadingInstaller.h"
#include "TrentinoCoreContributionLoadingLoggingErrorHandler.h"
#include "../RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "./../../Utils/TrentinoUtilsLogging.h"

using namespace Trentino::Core::ContributionLoading;
using Trentino::Core::ContributionLoading::ContributionLoader;
namespace RuntimeModel = Trentino::RuntimeModel;

//class ContributionLoader
   //construction
ContributionLoader::ContributionLoader()
{
   setErrorHandler(boost::make_shared<LoggingErrorHandler>());
}

ContributionLoader::~ContributionLoader()
{}

   //services
 void ContributionLoader::setErrorHandler(const ErrorHandlerBasePtr& errorHandler)
{
   ErrorReporter::setErrorHandler(errorHandler);
   mDeployer.setErrorHandler(errorHandler);
   mRunner.setErrorHandler(errorHandler);   
}


RuntimeModel::ContributionPtr ContributionLoader::install( const std::string& contributionPath 
                                                         , const Trentino::Utils::URI& baseURI )
{
   return Installer::install(contributionPath, baseURI);
}

void ContributionLoader::readSCAConfigFile(Trentino::Core::ContributionLoading::ContributionConfigFile& confFile
                                           ,const std::string& contributionPath)
{
    Installer::readSCAConfigFile(confFile,contributionPath);
}

void ContributionLoader::deploy( const RuntimeModel::ContributionPtr& contribution )
{
   mDeployer.deploy(contribution);
}

void ContributionLoader::run( const RuntimeModel::ContributionPtr& contribution )
{
   try
 {
	 mRunner.run(contribution);
 }
 catch (...)
 {
    //mRunner.stop(contribution);
    throw;
 }
}

void ContributionLoader::stop( const RuntimeModel::ContributionPtr& contribution )
{
   mRunner.stop(contribution);
}

void ContributionLoader::uninstall( const RuntimeModel::ContributionPtr& contribution )
{
   Installer::uninstall(contribution);
}

void ContributionLoader::undeploy( const RuntimeModel::ContributionPtr& contribution )
{
   mDeployer.undeploy(contribution);
}

void ContributionLoader::remove(const RuntimeModel::ContributionPtr& contribution)
{
   if(contribution->state() == RuntimeModel::Contribution::Running)
   {
      stop(contribution);
   }

   if(contribution->state() == RuntimeModel::Contribution::Deployed)
   {
      undeploy(contribution);
   }

   if(contribution->state() == RuntimeModel::Contribution::Installed)
   {
      uninstall(contribution);
   }
}
