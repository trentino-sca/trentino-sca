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
#include "TrentinoTestsCoreContributionLoaderBaseTest.h"

//standard
#include <string>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

//specific
#include "../../Runtime/Core/TrentinoCoreBootstrappingRuntimeConfiguration.h"
#include "../../Runtime/Core/TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "../../Runtime/Core/TrentinoCoreDomain.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelReference.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelWireBase.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelModelDescriptor.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelContributionType.h"
#include "../../Runtime/XML/TrentinoXMLSchemaQName.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelComposite.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelWire.h"
#include "../../Utils/TrentinoUtilsLoggingLogger.h"
#include "../../Utils/TrentinoUtilsPatternStaticClass.h"

using namespace std;
using Trentino::Tests::Core::ContributionLoaderBaseTest;
using Trentino::Tests::Core::makeContrbutionPath;
using Trentino::Core::Bootstrapping::RuntimeBootstrapper;
using Trentino::Core::ContributionLoading::ContributionLoader;
namespace RuntimeModel = Trentino::RuntimeModel;
namespace SCAModel = Trentino::SCA::Model;
namespace ContributionLoading = Trentino::Core::ContributionLoading;

//class ContributionLoaderBaseTest
   //additional
      //class CollectingErrorHandler
         //services
void ContributionLoaderBaseTest::CollectingErrorHandler::issueError(
   ContributionLoading::Error error, const std::string& /*msg*/)
{
   mErrorHistory.push_back(error);
}

void ContributionLoaderBaseTest::CollectingErrorHandler::issueWarning(
   ContributionLoading::Warning warning, const std::string& /*msg*/)
{
   mWarningHistory.push_back(warning);
}

unsigned int ContributionLoaderBaseTest::CollectingErrorHandler::countErrorIssued(
   ContributionLoading::Error error) const
{
   return count( mErrorHistory.begin()
               , mErrorHistory.end()
               , error );
}

unsigned int ContributionLoaderBaseTest::CollectingErrorHandler::countWarningIssued(
   ContributionLoading::Warning warning) const
{  
   return count( mWarningHistory.begin()
               , mWarningHistory.end()
               , warning );
}
   //services
void ContributionLoaderBaseTest::SetUpTestCase()
{
   Trentino::Utils::Logging::Logger::setup(
      Trentino::Utils::Logging::Logger::DisableAllLoggers, nullptr);
}
void ContributionLoaderBaseTest::TearDownTestCase()
{
}

   //management
void ContributionLoaderBaseTest::SetUp()
{
   RuntimeBootstrapper::RuntimeConfigurationConstPtr runtimeConfiguration = 
      boost::make_shared<Trentino::Core::Bootstrapping::RuntimeConfiguration>();
   mApp = mBooter.boot(runtimeConfiguration);
   mContributionLoader = mApp->contributionLoader();
   mCollectingErrorHandler = boost::make_shared<CollectingErrorHandler>();
}

void ContributionLoaderBaseTest::TearDown()
{
   mBooter.shutdown(mApp); 
   mApp.reset();
}

unsigned int ContributionLoaderBaseTest::deployedCompositesCount(
   const RuntimeModel::ConstContributionPtr& contribution)
{
   return count_if( contribution->composites().begin()
                  , contribution->composites().end()
                  , boost::bind(&RuntimeModel::Composite::state, _1) == 
                        RuntimeModel::Composite::Deployed ); 
}

unsigned int ContributionLoaderBaseTest::deployableDeployedCompositesCount(
         const RuntimeModel::ConstContributionPtr& contribution)
 {
    return count_if( contribution->composites().begin()
                   , contribution->composites().end()
                   , boost::bind(&RuntimeModel::Composite::isDeployable, _1) == true && 
                     boost::bind(&RuntimeModel::Composite::state, _1) == 
                        RuntimeModel::Composite::Deployed );
 }


unsigned int ContributionLoaderBaseTest::deployableCompositesCount(
   const RuntimeModel::ConstContributionPtr& contribution)
{
   const SCAModel::ModelDescriptorPtr modelDescriptor = contribution->scaModelDescriptor();
   assert(modelDescriptor);
   const SCAModel::ContributionTypePtr scaContribution = modelDescriptor->contribution();
   assert(scaContribution);
   return scaContribution->deployableElements().size();   
}

TEST_F(ContributionLoaderBaseTest, testErrorHandlerAccessors)
{  
   const ContributionLoading::ConstErrorHandlerBasePtr errorHandler =
      mContributionLoader->errorHandler();
   const ContributionLoading::ErrorHandlerBasePtr emptyErrorHandlerPtr;
   ASSERT_THROW( mContributionLoader->setErrorHandler(emptyErrorHandlerPtr)
               , std::invalid_argument );
   ASSERT_EQ( errorHandler, mContributionLoader->errorHandler() );
   ASSERT_NO_THROW( mContributionLoader->setErrorHandler(mCollectingErrorHandler) );
   ASSERT_EQ( mCollectingErrorHandler, mContributionLoader->errorHandler() );
}

TEST_F(ContributionLoaderBaseTest, testImplCompositesNotDeployedIfDeployableNotDeployed)
{
   const string contributionPath = makeContrbutionPath("NonInstantiableProxy");

   RuntimeModel::ContributionPtr contribution;
   ASSERT_NO_THROW( contribution = mContributionLoader->install(contributionPath, "BaseURI") );
   ASSERT_THROW(mContributionLoader->deploy(contribution), std::runtime_error);
     
   ASSERT_EQ( deployedCompositesCount(contribution), 0 );
}

TEST_F(ContributionLoaderBaseTest, testIssuedWarnings)
{
   mContributionLoader->setErrorHandler(mCollectingErrorHandler);
   const string contributionPath = makeContrbutionPath("NonExistentDeployableQName");

   RuntimeModel::ContributionPtr contribution;
   ASSERT_NO_THROW( contribution = mContributionLoader->install(contributionPath, "BaseURI") );   

   ASSERT_THROW(mContributionLoader->deploy(contribution), std::runtime_error);
   const unsigned int compositeNotFoundWarnings = 
      mCollectingErrorHandler->countWarningIssued(ContributionLoading::CompositeNotFoundWarning);
   ASSERT_GT( compositeNotFoundWarnings, 0U );
   EXPECT_EQ( compositeNotFoundWarnings, 1U );   
   ASSERT_EQ( contribution->state(), RuntimeModel::Contribution::Installed );
   ASSERT_TRUE( contribution->composites().empty() );
   mContributionLoader->uninstall(contribution);
}

TEST_F(ContributionLoaderBaseTest, testSeparateWireElements)
{
   const string contributionPath = makeContrbutionPath("SeparateWires");
   
   RuntimeModel::ContributionPtr contribution;
   ASSERT_NO_THROW( contribution = mContributionLoader->install(contributionPath, "BaseURI") );

   const SCAModel::ModelDescriptorPtr scaModelDescriptor = contribution->scaModelDescriptor();
   ASSERT_TRUE( scaModelDescriptor );

   const SCAModel::CompositePtr scaComposite = scaModelDescriptor->findCompositeByQName(
      Trentino::XML::Schema::QName("SecondComposite", "SeparateWiresTest") );
   ASSERT_TRUE( scaComposite );
      
   const string componentWithRefName = "FirstCompositeComponentWithRef";
   const string componentWithSvcName = "FirstCompositeComponentWithSvc";
   
   SCAModel::Wire* const wireElementSourceWithReference = new SCAModel::Wire;
   wireElementSourceWithReference->setSource( (componentWithRefName + "/EmptyService").c_str() );      
   wireElementSourceWithReference->setTarget( (componentWithSvcName + "/EmptyService").c_str() );
   SCAModel::Wire* const wireElementSourceWithoutReference = new SCAModel::Wire;
   wireElementSourceWithoutReference->setSource(componentWithRefName.c_str());
   wireElementSourceWithoutReference->setTarget( (componentWithSvcName + "/EmptyService").c_str() );
      
   //now the composite has the ownership for the wire elements and
   //is responsible for their deletion
   scaComposite->addWireElement( wireElementSourceWithReference );
   scaComposite->addWireElement( wireElementSourceWithoutReference );

   ASSERT_NO_THROW( mContributionLoader->deploy(contribution) );

   Trentino::Utils::Pattern::StaticClass<Trentino::Core::Domain> domain;
   ASSERT_TRUE( domain.hasReference() );  

   //test that wiring has be performed correctly   
   const RuntimeModel::ConstComponentPtr componentWithRef = 
      domain->findDomainLevelComponentByName(componentWithRefName);
   ASSERT_TRUE( componentWithRef );

   const RuntimeModel::ConstReferenceBasePtr emptyServiceReference = 
      componentWithRef->findReferenceByName("EmptyService");
   ASSERT_TRUE( emptyServiceReference );
   
   const RuntimeModel::ConstComponentPtr componentWithSvc = 
      domain->findDomainLevelComponentByName(componentWithSvcName);
   ASSERT_TRUE( componentWithSvc );
   
   const RuntimeModel::ConstServiceBasePtr emptyServiceService = 
      componentWithSvc->findServiceByName("EmptyService");
   ASSERT_TRUE( emptyServiceService );
   
   unsigned int numberOfCorrectWires = 0;
   BOOST_FOREACH( const RuntimeModel::ConstWireBasePtr& wire
                , emptyServiceReference->wireableSupport().wires() )
   {
      const RuntimeModel::ConstReferenceBasePtr reference = wire->reference().lock();
      ASSERT_TRUE( reference );
      const RuntimeModel::ConstServiceBasePtr service = wire->originalService().lock();
      ASSERT_TRUE( reference );

      if(reference == emptyServiceReference && service == emptyServiceService)
      {
         ++numberOfCorrectWires;
      }
   }

   ASSERT_EQ( numberOfCorrectWires, 2);
   ASSERT_NO_THROW( mContributionLoader->remove(contribution) );
}
