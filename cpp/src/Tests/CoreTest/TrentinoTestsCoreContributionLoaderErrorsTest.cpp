//header
#include "TrentinoTestsCoreContributionLoaderErrorsTest.h"

//standard
#include <boost/bind.hpp>

//specific
#include "../../Global/TrentinoGlobal.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelModelDescriptor.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelComposite.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelWire.h"
#include "../../Runtime/XML/TrentinoXMLSchemaQName.h"

using namespace std;
using Trentino::Tests::Core::ContributionLoaderDeploymentCriticalErrorsTest;
using Trentino::Tests::Core::ContributionLoaderWiringErrorsTest1;
using Trentino::Tests::Core::ContributionLoaderWiringErrorsTest2;
using Trentino::Tests::Core::ContributionLoaderErrorsTestParams;
using Trentino::Tests::Core::ContributionLoader2ContribErrorsTestParams;
using Trentino::Tests::Core::ContributionLoaderWireElementsWiringErrorsTest;
using Trentino::Tests::Core::ContributionLoaderWireElementsTestParams;
using Trentino::Tests::Core::makeContrbutionPath;
using Trentino::Core::Bootstrapping::RuntimeBootstrapper;
using Trentino::Core::ContributionLoading::ContributionLoader;
namespace RuntimeModel = Trentino::RuntimeModel;
namespace SCAModel = Trentino::SCA::Model;
namespace ContributionLoading = Trentino::Core::ContributionLoading;

static ContributionLoaderErrorsTestParams cricitcalErrorsTestValues[] = {
   {"NonExistentImplementationComposite", ContributionLoading::CompositeNotFoundError, 1},
   {"NonExistentComponentType", ContributionLoading::ComponentTypeNotFoundError, 1},
   {"NonExistentProxyReflectObject", ContributionLoading::ReflectObjectNotFoundError, 1},
   {"NonExistentSetterMethodReflectObject", ContributionLoading::CompositeNotDeployedError, 1},
   {"NonExistentImplClassReflectObject", ContributionLoading::CompositeNotDeployedError, 1},
   {"AmbiguousSetterMethods", ContributionLoading::CompositeNotDeployedError, 1},
   {"NonInstantiableProxy", ContributionLoading::ProxyInstanceNotCreatedError, 1}};

INSTANTIATE_TEST_CASE_P( //empty argument = nameless instantiation 
                       , ContributionLoaderDeploymentCriticalErrorsTest 
                       , ::testing::ValuesIn(cricitcalErrorsTestValues));

TEST_P(ContributionLoaderDeploymentCriticalErrorsTest, testIssuedErrors)
{
   mContributionLoader->setErrorHandler(mCollectingErrorHandler);
   const string contributionPath = makeContrbutionPath(GetParam().contributionName);
   RuntimeModel::ContributionPtr contribution; 
   ASSERT_NO_THROW( contribution = mContributionLoader->install(contributionPath, "BaseURI") );
   ASSERT_EQ( contribution->state(), RuntimeModel::Contribution::Installed );
   ASSERT_THROW( mContributionLoader->deploy(contribution), std::runtime_error );
   ASSERT_EQ( contribution->state(), RuntimeModel::Contribution::Installed );   
   ASSERT_LT( deployableDeployedCompositesCount(contribution)
            , deployableCompositesCount(contribution) );

   const unsigned int errorCount = 
      mCollectingErrorHandler->countErrorIssued(GetParam().expectedError);
   ASSERT_GT( errorCount, 0U );
   EXPECT_EQ( errorCount, GetParam().expectedErrorCount);   
}

static ContributionLoaderErrorsTestParams wiringErrorsTest1Values[] = {   
   {"WireToNonExistentComponent", ContributionLoading::ComponentNotFoundError, 3}};

INSTANTIATE_TEST_CASE_P( //empty argument = nameless instantiation 
                       , ContributionLoaderWiringErrorsTest1
                       , ::testing::ValuesIn(wiringErrorsTest1Values)); 

TEST_P(ContributionLoaderWiringErrorsTest1, testIssuedErrors)
{
   mContributionLoader->setErrorHandler(mCollectingErrorHandler);
   const string contributionPath = makeContrbutionPath(GetParam().contributionName);
   RuntimeModel::ContributionPtr contribution; 
   ASSERT_NO_THROW( contribution = mContributionLoader->install(contributionPath, "BaseURI") );   
   ASSERT_NO_THROW( mContributionLoader->deploy(contribution) );
   ASSERT_EQ( contribution->state(), RuntimeModel::Contribution::Deployed );
   ASSERT_EQ( deployableDeployedCompositesCount(contribution)              
            , deployableCompositesCount(contribution) );

   const unsigned int errorCount = 
      mCollectingErrorHandler->countErrorIssued(GetParam().expectedError);  
   ASSERT_EQ( errorCount, GetParam().expectedErrorCount );
   
   ASSERT_NO_THROW( mContributionLoader->remove(contribution) );   
}

static ContributionLoader2ContribErrorsTestParams wiringErrorsTest2Values[] = {   
   {"ValidContribution1", "WireToNonExistentService", 
      ContributionLoading::ServiceNotFoundError, 3},
   {"ValidContribution1", "WireToNonCompatibleService", 
      ContributionLoading::ServiceIncombatibleError, 3},
   {"ValidContribution1", "WireToComponentWithNoCompatibleServices", 
      ContributionLoading::NoCompatibleServicesError, 3}};

INSTANTIATE_TEST_CASE_P( //empty argument = nameless instantiation 
                       , ContributionLoaderWiringErrorsTest2
                       , ::testing::ValuesIn(wiringErrorsTest2Values)); 

TEST_P(ContributionLoaderWiringErrorsTest2, testIssuedErrors)
{
   //deploy first contribution
   const string contribution1Path = 
      makeContrbutionPath(GetParam().contribution1Name);
   RuntimeModel::ContributionPtr contribution1; 
   ASSERT_NO_THROW( contribution1 = 
      mContributionLoader->install(contribution1Path, "BaseURI1") );
   ASSERT_NO_THROW( mContributionLoader->deploy(contribution1) );
   ASSERT_NO_THROW( mContributionLoader->run(contribution1) );
   ASSERT_EQ( contribution1->state(), RuntimeModel::Contribution::Running );

   mContributionLoader->setErrorHandler(mCollectingErrorHandler);

   //deploy second contribution
   const string contribution2Path = 
      makeContrbutionPath(GetParam().contribution2Name);
   RuntimeModel::ContributionPtr contribution2; 
   ASSERT_NO_THROW( contribution2 = 
      mContributionLoader->install(contribution2Path, "BaseURI2") );   
   ASSERT_NO_THROW( mContributionLoader->deploy(contribution2) );   
   ASSERT_EQ( contribution2->state(), RuntimeModel::Contribution::Deployed );
   ASSERT_EQ( deployableDeployedCompositesCount(contribution2)              
            , deployableCompositesCount(contribution2) );
   
   const unsigned int errorCount = 
      mCollectingErrorHandler->countErrorIssued(GetParam().expectedError);  
   ASSERT_EQ( errorCount, GetParam().expectedErrorCount );   
   
   mContributionLoader->remove(contribution2);
   mContributionLoader->remove(contribution1);
}

static ContributionLoaderWireElementsTestParams wireElementsTestParams[] = {   
   {"SecondCompositeComponentWith2Ref/NonExistentRef", ContributionLoading::ReferenceNotFoundError},
   {"SecondCompositeComponentWithNoRef", ContributionLoading::ReferenceNotFoundError},
   {"FirstCompositeComponentWith2Ref", ContributionLoading::AmbigousReferencesError},
   {"FirstCompositeComponentWithNoRef", ContributionLoading::ReferenceNotFoundError},
   {"FirstCompositeComponentWith2Ref/NonExistentRef", ContributionLoading::ReferenceNotFoundError},
   {"NonExistentComponent", ContributionLoading::ComponentNotFoundError} };

INSTANTIATE_TEST_CASE_P( //empty argument = nameless instantiation 
                       , ContributionLoaderWireElementsWiringErrorsTest
                       , ::testing::ValuesIn(wireElementsTestParams)); 

TEST_P(ContributionLoaderWireElementsWiringErrorsTest, testIssuedErrors)
{
   const string contributionPath = makeContrbutionPath("SeparateWires");      
   mContributionLoader->setErrorHandler(mCollectingErrorHandler);
   RuntimeModel::ContributionPtr contribution;   
   ASSERT_NO_THROW( contribution = mContributionLoader->install(contributionPath, "BaseURI") );

   const SCAModel::ModelDescriptorPtr scaModelDescriptor = contribution->scaModelDescriptor();
   ASSERT_TRUE( scaModelDescriptor );

   const SCAModel::CompositePtr scaComposite = scaModelDescriptor->findCompositeByQName(
      Trentino::XML::Schema::QName("SecondComposite", "SeparateWiresTest") );
   ASSERT_TRUE( scaComposite );
      
   SCAModel::Wire* const newWire = new SCAModel::Wire;
   newWire->setSource( GetParam().wireSource.c_str() );
   newWire->setTarget( "FirstCompositeComponentWithSvc/EmptyService" );   
      
   //now the composite has the ownership for the wire element and
   //is responsible for its deletion
   scaComposite->addWireElement(newWire);  

   ASSERT_NO_THROW( mContributionLoader->deploy(contribution) );

   const unsigned int errorCount = 
      mCollectingErrorHandler->countErrorIssued(GetParam().expectedError);        
   ASSERT_EQ( errorCount, 1 );  

   mContributionLoader->remove(contribution);   
}
