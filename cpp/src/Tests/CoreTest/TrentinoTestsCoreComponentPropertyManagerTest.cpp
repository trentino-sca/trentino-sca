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
#include "TrentinoTestsCoreComponentPropertyManagerTest.h"

//standard
#include <cstdarg>
#include <cstdio>
#include <deque>
#include <iterator>
#include <algorithm>
#include <utility>
#include <fstream>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

//specific
#include "../../Runtime/Core/TrentinoCoreComponentPropertyManager.h"
#include "../../Runtime/Core/TrentinoCoreException.h"
#include "../../Runtime/Core/TrentinoCoreComponentCPPImplementationLifeCycleMethodManager.h"
#include "../../Utils/TrentinoUtilsLoggingLogger.h"
#include "../../Utils/TrentinoUtilsPatternStaticClass.h"
#include "../../Runtime/Core/TrentinoCoreBootstrappingRuntimeConfiguration.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelProperty.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelPropertyValue.h"
#include "TestData/PropertyValues/TrentinoTestsCoreComponentWithProperties.h"

using namespace std;
using Trentino::Tests::Core::ComponentPropertyManagerValueAssignmentTest;   
using Trentino::Tests::Core::ComponentPropertyManagerValueAssignmentTestParams;
using Trentino::Tests::Core::ComponentPropertyManagerErrorsTest;
using Trentino::Tests::Core::ComponentPropertyManagerErrorsTestParams;
using Trentino::Tests::Core::makeContrbutionPath;
using Trentino::Core::Bootstrapping::RuntimeBootstrapper;
using Trentino::Core::ContributionLoading::ContributionLoader;
using Trentino::Core::ComponentPropertyManager;
using Trentino::XML::Schema::QName;
namespace RuntimeModel = Trentino::RuntimeModel;
namespace SCAModel = Trentino::SCA::Model;

namespace
{
   vector<string> makeStringVector(int size, ...)
   {
      vector<string> result;
      result.reserve(size);

      va_list arguments;
      va_start(arguments, size);

      for(int i = 0; i < size; i++)
      {
         result.push_back(va_arg(arguments, const char*));
      }

      va_end(arguments);
      return result;
   }

   ComponentPropertyManagerValueAssignmentTestParams::PropertyValuesMap 
      makeMapOf4( const ComponentPropertyManagerValueAssignmentTestParams::PropertyValuesMap::value_type& arg1
                , const ComponentPropertyManagerValueAssignmentTestParams::PropertyValuesMap::value_type& arg2
                , const ComponentPropertyManagerValueAssignmentTestParams::PropertyValuesMap::value_type& arg3
                , const ComponentPropertyManagerValueAssignmentTestParams::PropertyValuesMap::value_type& arg4)
   {
      ComponentPropertyManagerValueAssignmentTestParams::PropertyValuesMap result;
      result.insert(arg1);
      result.insert(arg2);
      result.insert(arg3);
      result.insert(arg4);

      return result;
   }

   RuntimeModel::ComponentPtr findComponentByURI(
      const RuntimeModel::ConstContributionPtr contribution, const std::string& uri) 
   {
      assert(contribution);
      RuntimeModel::ComponentPtr component;
      BOOST_FOREACH(const RuntimeModel::ConstCompositePtr& composite, contribution->composites())
      {
         assert(composite);
         const RuntimeModel::Components::const_iterator it =
            find_if( composite->components().begin()
                   , composite->components().end()
                   , boost::bind(&RuntimeModel::Component::uri, _1) == uri);

         if(it != composite->components().end())
         {
            component = *it;
            break;
         }
      } 

      return component;
   }
} //namespace


//*************************************************************************************************
//                    TEST(ComponentPropertyManagerTest, testPropertyFile)
//*************************************************************************************************
TEST(ComponentPropertyManager, testPropertyFile)
{
   const string xmlStart = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
   const string openingRootTag = "<values>";
   const string closingRootTag = "</values>";
   const string openingValueTag = "<value>";
   const string closingValueTag = "</value>";
   const string value1 = "Value1";
   const string value2 = "Value2";
   const string value3 = "Value3";

   //********************************************
   //File with empty <value> element
   //********************************************
   {  
      const string filePath = "testPropertyFile.SomeFile_2_290885";
      ofstream file(filePath.c_str(), ios::out);
      ASSERT_FALSE(!file);
  
      file << xmlStart << endl 
           << openingRootTag << endl 
           << "\t" << openingValueTag << value1 << closingValueTag << endl
           << openingValueTag << closingValueTag << endl << endl
           << openingValueTag << value3 << closingValueTag << endl
            << closingRootTag;
      file.close();

      ComponentPropertyManager::PropertyFile* propertyFile = nullptr;
      ASSERT_NO_THROW( propertyFile = new ComponentPropertyManager::PropertyFile(filePath) );      
      ComponentPropertyManager::PropertyFile::iterator it(propertyFile, string::npos);
      ASSERT_NO_THROW( it = propertyFile->begin() ); 
      ASSERT_NO_THROW( ++it );
      ASSERT_EQ( *it, "" );
      ASSERT_NO_THROW( ++it );      
      ASSERT_NO_THROW( ++it );
      ASSERT_EQ( it, propertyFile->end() );      

      delete propertyFile;

      remove(filePath.c_str());
   }

   //********************************************
   //File with three <value> elements
   //********************************************
   {  
      const string filePath = "testPropertyFile.SomeFile_3_290885";
      ofstream file(filePath.c_str(), ios::out);
      ASSERT_FALSE(!file);
  
      file << xmlStart << endl 
           << openingRootTag << endl 
           << "\t" << openingValueTag << value1 << closingValueTag << endl
           << openingValueTag << value2 << closingValueTag << endl << endl
           << openingValueTag << value3 << closingValueTag << endl
            << closingRootTag;
      file.close();

      ComponentPropertyManager::PropertyFile* propertyFile = nullptr;
      ASSERT_NO_THROW( propertyFile = new ComponentPropertyManager::PropertyFile(filePath) );      
      ComponentPropertyManager::PropertyFile::iterator it(propertyFile, string::npos);
      ASSERT_NO_THROW( it = propertyFile->begin() );      
      ASSERT_EQ( *it, value1 );
      ASSERT_NO_THROW( ++it );
      ASSERT_EQ( *it, value2 );
      ASSERT_NO_THROW( ++it );
      ASSERT_EQ( *it, value3 );
      ASSERT_NO_THROW( ++it );
      ASSERT_EQ( it, propertyFile->end() );
      
      ComponentPropertyManager::PropertyFile::iterator it2(propertyFile, string::npos);;
      ASSERT_NO_THROW( it2 = propertyFile->begin() );
      ASSERT_EQ( *(it2++), value1 );
      ASSERT_EQ( *(it2++), value2 );
      ASSERT_EQ( *(it2++), value3 );
      ASSERT_EQ( it2, propertyFile->end() );

      delete propertyFile;

      remove(filePath.c_str());
   }

   //********************************************
   //PropertyFileReadingError
   //********************************************
   try
   {
      ComponentPropertyManager::PropertyFile("NonExistent");      
      FAIL();
   }
   catch(Trentino::Core::Exception<ComponentPropertyManager::Error>& e)
   {
      ASSERT_EQ( e.data(), ComponentPropertyManager::PropertyFileReadingError );
   }
   catch(...) 
   { 
      FAIL();
   }

   //********************************************
   //missing opening <values> tag
   //********************************************
   {   
      const string filePath = "testPropertyFile.SomeFile_4_290885";
      ofstream file(filePath.c_str(), ios::out);
      ASSERT_FALSE(!file);
  
      file << xmlStart << endl            
           << "\t" << openingValueTag << value1 << closingValueTag << endl
           << openingValueTag << value2 << closingValueTag << endl << endl
           << openingValueTag << value3 << closingValueTag << endl
            << closingRootTag;
      file.close();
      
      try
      {
         ComponentPropertyManager::PropertyFile dummy(filePath);      
         FAIL();
      }
      catch(Trentino::Core::Exception<ComponentPropertyManager::Error>& e)
      {
         ASSERT_EQ( e.data(), ComponentPropertyManager::PropertyFileIllFormedError );
      }
      catch(...) 
      { 
         FAIL();
      }

      remove(filePath.c_str());
   }

   //********************************************
   //missing closing </values> tag
   //********************************************
   {   
      const string filePath = "testPropertyFile.SomeFile_5_290885";
      ofstream file(filePath.c_str(), ios::out);
      ASSERT_FALSE(!file);
  
      file << xmlStart << endl    
           << openingRootTag << endl 
           << "\t" << openingValueTag << value1 << closingValueTag << endl
           << openingValueTag << value2 << closingValueTag << endl << endl
           << openingValueTag << value3 << closingValueTag << endl;
      file.close();
      
      try
      {
         ComponentPropertyManager::PropertyFile dummy(filePath);      
         FAIL();
      }
      catch(Trentino::Core::Exception<ComponentPropertyManager::Error>& e)
      {
         ASSERT_EQ( e.data(), ComponentPropertyManager::PropertyFileIllFormedError );
      }
      catch(...) 
      { 
         FAIL();
      }

      remove(filePath.c_str());
   }

   //********************************************
   //file with no <value> tags
   //********************************************
   {  
      const string filePath = "testPropertyFile.SomeFile_1_290885";
      ofstream file(filePath.c_str(), ios::out);
      ASSERT_FALSE(!file);
  
      file << xmlStart << endl << openingRootTag << endl << closingRootTag;
      file.close();

      try
      {
         ComponentPropertyManager::PropertyFile dummy(filePath);      
         FAIL();
      }
      catch(Trentino::Core::Exception<ComponentPropertyManager::Error>& e)
      {
         ASSERT_EQ( e.data(), ComponentPropertyManager::PropertyFileIllFormedError );
      }
      catch(...) 
      { 
         FAIL();
      }

      remove(filePath.c_str());
   }

   //********************************************
   //missing closing </value> tag
   //********************************************
   {   
      const string filePath = "testPropertyFile.SomeFile_4_290885";
      ofstream file(filePath.c_str(), ios::out);
      ASSERT_FALSE(!file);
  
      file << xmlStart << endl    
           << openingRootTag << endl 
           << "\t" << openingValueTag << value1 << closingValueTag << endl
           << openingValueTag << value2 << closingValueTag << endl << endl
           << openingValueTag << value3
           << closingRootTag;
      file.close();

      ComponentPropertyManager::PropertyFile* propertyFile = nullptr;
      ASSERT_NO_THROW( propertyFile = new ComponentPropertyManager::PropertyFile(filePath) );
      ComponentPropertyManager::PropertyFile::iterator it(propertyFile, string::npos);
      ASSERT_NO_THROW( it = propertyFile->begin() );
      ASSERT_NO_THROW( ++it );
      
      try
      {
         ++it;     
         FAIL();
      }
      catch(Trentino::Core::Exception<ComponentPropertyManager::Error>& e)
      {
         ASSERT_EQ( e.data(), ComponentPropertyManager::PropertyFileIllFormedError );
      }
      catch(...) 
      { 
         FAIL();
      }

      delete propertyFile;
      remove(filePath.c_str());
   }
}

//*************************************************************************************************
//                    TEST_P(ComponentPropertyManagerValueAssignmentTest, test)
//*************************************************************************************************

//class ComponentPropertyManagerValueAssignmentTest
   //global operators
std::ostream& Trentino::Tests::Core::operator<<(
     std::ostream& os, const ComponentPropertyManagerValueAssignmentTestParams& params)
{
   os << endl << "componentURI='" << params.componentURI << "'" << endl;

   BOOST_FOREACH( const ComponentPropertyManagerValueAssignmentTestParams::PropertyValuesMap::value_type& pair
                  , params.expectedPropertyValues)
   {
      os << "   propertyName='" << pair.first << "'" << endl;
      os << "      values: ";
      BOOST_FOREACH(const string& value, pair.second)
      {
         os << "'" << value << "', ";
      }

      os << endl;
   }

   return os;
}
   //static member initialization
Trentino::RuntimeModel::ContributionPtr ComponentPropertyManagerValueAssignmentTest::mContribution;
Trentino::Tests::Core::Booter::BootPtr ComponentPropertyManagerValueAssignmentTest::mApp;
   //services
void ComponentPropertyManagerValueAssignmentTest::SetUpTestCase()
{
   //disable logging
   Trentino::Utils::Logging::Logger::setup(
      Trentino::Utils::Logging::Logger::DisableAllLoggers, nullptr);
   
   //boot the runtime 
   RuntimeBootstrapper::RuntimeConfigurationConstPtr runtimeConfiguration = 
      boost::make_shared<Trentino::Core::Bootstrapping::RuntimeConfiguration>();
   Trentino::Tests::Core::Booter booter;
   mApp = booter.boot(runtimeConfiguration);

   //deploy the test contribution
   const string contributionPath = makeContrbutionPath("ValidProperties");
   ASSERT_NO_THROW( mContribution = mApp->contributionLoader()->install(contributionPath, "BaseURI") );
      
   //Deployment is used here only to make the contribution loader create the runtime model.
   //The influence of the contribution loader (which internally used the ComponentPropertyManager)
   //on property processing will be eliminated by clearing all the property values assigned during 
   //deployment
   ASSERT_NO_THROW( mApp->contributionLoader()->deploy(mContribution) );
   
   //iterate over all the properties in the contribution and clear their values 
   BOOST_FOREACH(const RuntimeModel::ConstCompositePtr& composite, mContribution->composites())
   {
      ASSERT_TRUE( composite );
      BOOST_FOREACH(const RuntimeModel::ConstComponentPtr& component, composite->components())
      {
         ASSERT_TRUE( component );
         BOOST_FOREACH(const RuntimeModel::PropertyPtr& property, component->properties())
         {
            ASSERT_TRUE( property );
            //clear the values
            property->setValues(RuntimeModel::Property::Values());
         }
      }
   }

   //Iterate over all the properties in the contribution IN THE CORRECT ORDER 
   //(i.e. property values for components implemented by composites are set BEFORE the 
   //property values of the components contained in the implementation composite) 
   //and let the ComponentPropertyManager set their values
   Trentino::Utils::Pattern::StaticClass<ComponentPropertyManager> componentPropertyManager;
   ASSERT_TRUE(componentPropertyManager.hasReference());
   
   deque<RuntimeModel::ConstCompositePtr> compositeStack;
   BOOST_FOREACH(const RuntimeModel::CompositePtr composite, mContribution->composites())
   {
      if(composite->isDeployable())
      {
         compositeStack.push_back(composite);
      }
   }
   
   while(!compositeStack.empty())
   {
      const RuntimeModel::ConstCompositePtr composite = compositeStack.back();
      compositeStack.pop_back();
      
      BOOST_FOREACH(const RuntimeModel::ConstComponentPtr& component, composite->components())
      {
         ASSERT_TRUE( component );
         BOOST_FOREACH(const RuntimeModel::PropertyPtr& property, component->properties())
         {
            ASSERT_TRUE( property );
            ASSERT_NO_THROW( componentPropertyManager->assignValuesFromSCAModel(property) );           
         }

         //Use a dynamic cast to determine whether the component is implemented by a composite.
         //If yes the composite is put on the stack to be further processed. 
         const RuntimeModel::CompositePtr implementingComposite =
            boost::dynamic_pointer_cast<RuntimeModel::Composite>(component->implementation());
         if(implementingComposite)
         {
            compositeStack.push_back(implementingComposite);
         }         
      }
   }   
}

void ComponentPropertyManagerValueAssignmentTest::TearDownTestCase()
{
   ASSERT_NO_THROW( mApp->contributionLoader()->remove(mContribution) );
   mContribution.reset();
   Trentino::Tests::Core::Booter booter;
   booter.shutdown(mApp);  
   mApp.reset();
}  

INSTANTIATE_TEST_CASE_P(
   /*empty argument = nameless instantiation*/
   , ComponentPropertyManagerValueAssignmentTest
   , ::testing::Values 
   (
      ComponentPropertyManagerValueAssignmentTestParams
      (  
         "ComponentWithValues", 
         makeMapOf4( make_pair("PropertyWithSingleDefaultValue"
                              , makeStringVector(1, "ComponentWithValuesValue1"))
                   , make_pair("PropertyWithManyDefaultValues"
                              , makeStringVector(2, "ComponentWithValuesValue2" 
                                                  , "ComponentWithValuesValue3"))
                   , make_pair("PropertyWithUselesseDefaultValue"
                              , makeStringVector(1, "ComponentWithValuesValue4"))
                   , make_pair("PropertyWithNoDefaultValue"
                              , makeStringVector(1, "ComponentWithValuesValue5")))
      ),

      ComponentPropertyManagerValueAssignmentTestParams
      ( 
         "ComponentWithoutValues", 
         makeMapOf4( make_pair("PropertyWithSingleDefaultValue"
                              , makeStringVector(1, "ComponentTypeDefaultValue"))
                   , make_pair("PropertyWithManyDefaultValues"
                              , makeStringVector(3, "ComponentTypeDefaultValue1"
                                                  , "ComponentTypeDefaultValue2"
                                                  , "ComponentTypeDefaultValue3"))
                   , make_pair("PropertyWithUselesseDefaultValue"
                              , makeStringVector(1, "ComponentWithoutValuesValue1"))
                   , make_pair("PropertyWithNoDefaultValue"
                              , makeStringVector(1, "ComponentWithoutValuesValue2")))
      ),

      ComponentPropertyManagerValueAssignmentTestParams
      ( 
         "ComponentWithSourceAttribute", 
         makeMapOf4( make_pair("PropertyWithSingleDefaultValue"
                              , makeStringVector(1, "ComponentTypeDefaultValue"))
                   , make_pair("PropertyWithManyDefaultValues"
                              , makeStringVector(3, "DeployableCompositeDefaultValue1"
                                                  , "DeployableCompositeDefaultValue2"
                                                  , "DeployableCompositeDefaultValue3"))
                   , make_pair("PropertyWithUselesseDefaultValue"
                              , makeStringVector(1, "DeployableCompositeDefaultValue"))
                   , make_pair("PropertyWithNoDefaultValue"
                              , makeStringVector(1, "DeployableCompositeDefaultValue")))
      ),

      ComponentPropertyManagerValueAssignmentTestParams
      (  
         "ComponentWithFileAttribute", 
         makeMapOf4( make_pair("PropertyWithSingleDefaultValue"
                              , makeStringVector(1, "ComponentTypeDefaultValue"))
                   , make_pair("PropertyWithManyDefaultValues"
                              , makeStringVector(2, "ValueFromFile1"
                                                  , "ValueFromFile2"))
                   , make_pair("PropertyWithUselesseDefaultValue"
                              , makeStringVector(1, "SingleValueFromFile"))
                   , make_pair("PropertyWithNoDefaultValue"
                              , makeStringVector(1, "SingleValueFromFile")))
      ),

      ComponentPropertyManagerValueAssignmentTestParams
      (  
         "ComponentWithPrecedence", 
         makeMapOf4( make_pair("PropertyWithSingleDefaultValue"
                              , makeStringVector(1, "DeployableCompositeDefaultValue"))
                   , make_pair("PropertyWithManyDefaultValues"
                              , makeStringVector(2, "ValueFromFile1"
                                                  , "ValueFromFile2"))
                   , make_pair("PropertyWithUselesseDefaultValue"
                              , makeStringVector(1, "DeployableCompositeDefaultValue"))
                   , make_pair("PropertyWithNoDefaultValue"
                              , makeStringVector(1, "DeployableCompositeDefaultValue")))
      ),

      ComponentPropertyManagerValueAssignmentTestParams
      ( 
         "ComponentImplByCompositeWithValues", 
         makeMapOf4( make_pair("ImplCompositePropertyWithSingleDefaultValue"
                              , makeStringVector(1, "ComponentImplByCompositeWithValuesValue1"))
                   , make_pair("ImplCompositePropertyWithManyDefaultValues"
                              , makeStringVector(2, "ComponentImplByCompositeWithValuesValue2"
                                                  , "ComponentImplByCompositeWithValuesValue3"))
                   , make_pair("ImplCompositePropertyWithUselesseDefaultValue"
                              , makeStringVector(1, "ComponentImplByCompositeWithValuesValue4"))
                   , make_pair("ImplCompositePropertyWithNoDefaultValue"
                              , makeStringVector(1, "ComponentImplByCompositeWithValuesValue5")))
      ),

      ComponentPropertyManagerValueAssignmentTestParams
      ( 
         "ComponentImplByCompositeWithoutValues", 
         makeMapOf4( make_pair("ImplCompositePropertyWithSingleDefaultValue"
                              , makeStringVector(1, "ImplCompositeDefaultValue"))
                   , make_pair("ImplCompositePropertyWithManyDefaultValues"
                              , makeStringVector(3, "ImplCompositeDefaultValue1"
                                                  , "ImplCompositeDefaultValue2"
                                                  , "ImplCompositeDefaultValue3"))
                   , make_pair("ImplCompositePropertyWithUselesseDefaultValue"
                              , makeStringVector(1, "ComponentImplByCompositeWithoutValuesValue1"))
                   , make_pair("ImplCompositePropertyWithNoDefaultValue"
                              , makeStringVector(1, "ComponentImplByCompositeWithoutValuesValue2")))
      ),

      ComponentPropertyManagerValueAssignmentTestParams
      ( 
         "ComponentImplByCompositeWithValues/InnerComponentWithValues", 
         makeMapOf4( make_pair("PropertyWithSingleDefaultValue"
                              , makeStringVector(1, "ComponentImplByCompositeWithValuesValue1"))
                   , make_pair("PropertyWithManyDefaultValues"
                              , makeStringVector(2, "ComponentImplByCompositeWithValuesValue2"
                                                  , "ComponentImplByCompositeWithValuesValue3"))
                   , make_pair("PropertyWithUselesseDefaultValue"
                              , makeStringVector(1, "ComponentImplByCompositeWithValuesValue4"))
                   , make_pair("PropertyWithNoDefaultValue"
                              , makeStringVector(1, "ComponentImplByCompositeWithValuesValue5")))
      ),

      ComponentPropertyManagerValueAssignmentTestParams
      ( 
         "ComponentImplByCompositeWithoutValues/InnerComponentWithValues", 
         makeMapOf4( make_pair("PropertyWithSingleDefaultValue"
                              , makeStringVector(1, "ImplCompositeDefaultValue"))
                   , make_pair("PropertyWithManyDefaultValues"
                              , makeStringVector(3, "ImplCompositeDefaultValue1"
                                                  , "ImplCompositeDefaultValue2"
                                                  , "ImplCompositeDefaultValue3"))
                   , make_pair("PropertyWithUselesseDefaultValue"
                              , makeStringVector(1, "ComponentImplByCompositeWithoutValuesValue1"))
                   , make_pair("PropertyWithNoDefaultValue"
                              , makeStringVector(1, "ComponentImplByCompositeWithoutValuesValue2")))
      )
   )
);

TEST_P(ComponentPropertyManagerValueAssignmentTest, test)
{ 
   //find the component specified in the test parameters
   RuntimeModel::ConstComponentPtr component;
   BOOST_FOREACH(const RuntimeModel::ConstCompositePtr& composite, mContribution->composites())
   {
      const RuntimeModel::Components::const_iterator it =
         find_if( composite->components().begin()
                , composite->components().end()
                , boost::bind(&RuntimeModel::Component::uri, _1) == GetParam().componentURI);

      if(it != composite->components().end())
      {
         component = *it;
         break;
      }
   } 
   
   ASSERT_TRUE( component );

   //iterate over all the property names in the test parameters
   BOOST_FOREACH( const ComponentPropertyManagerValueAssignmentTestParams::
                     PropertyValuesMap::value_type& pair
                , GetParam().expectedPropertyValues)
   {
      const RuntimeModel::ConstPropertyPtr property = 
         component->findPropertyByName(pair.first);
      ASSERT_TRUE( property );

      //test that the number of property values corresponds to the expected number
      ASSERT_EQ( property->values().size(), pair.second.size() );
      //test that all the property values are equal with the expected ones 
      //(i.e. there is no mismatch in the both ranges)
      ASSERT_EQ( mismatch( property->values().begin()
                         , property->values().end()
                         , pair.second.begin() ).first
                         , property->values().end() );
   }   
}

//*************************************************************************************************
//                    TEST(ComponentPropertyManagerTest, testValueInjection)
//*************************************************************************************************

TEST(ComponentPropertyManagerTest, testValueInjection)
{  
   //disable logging to console from runtime (to keep the test outputs clear)
   Trentino::Utils::Logging::Logger::setup(
      Trentino::Utils::Logging::Logger::DisableAllLoggers, nullptr);

   //boot the runtime 
   RuntimeBootstrapper::RuntimeConfigurationConstPtr runtimeConfiguration = 
      boost::make_shared<Trentino::Core::Bootstrapping::RuntimeConfiguration>();
   Trentino::Tests::Core::Booter booter;
   Trentino::Tests::Core::Booter::BootPtr app = booter.boot(runtimeConfiguration);  

   //deploy the test contribution
   const string contributionPath = makeContrbutionPath("PropertyValues");
   RuntimeModel::ContributionPtr contribution;  
   ASSERT_NO_THROW( contribution = app->contributionLoader()->install(contributionPath, "BaseURI") );
   ASSERT_NO_THROW( app->contributionLoader()->deploy(contribution) );
   ASSERT_NO_THROW( app->contributionLoader()->run(contribution) );

   const RuntimeModel::ComponentPtr component = 
      findComponentByURI(contribution, "ComponentWithProperties");
   ASSERT_TRUE( component );       
   
   //instantiate the implementation of our test component 
   Trentino::Core::CPPImplementationLifeCycleMethodManager lifeCycleMethodManager;
   Trentino::Tests::Core::ComponentWithProperties* const impl =
      static_cast<Trentino::Tests::Core::ComponentWithProperties*>(
         lifeCycleMethodManager.newInstance(component));

   //retrieve instance of ComponentPropertyManager
   Trentino::Utils::Pattern::StaticClass<ComponentPropertyManager> componentPropertyManager;
   ASSERT_TRUE(componentPropertyManager.hasReference());

   //to decrease the coupling of this test to the correct value assignment 
   //(see ComponentPropertyManagerValueAssignmentTest), don't rely on the property values 
   //assigned in SCDL (i.e. in the SCA::Model) but assign own values

   //**********************************************************************************************
   //                                        @many="false"
   //**********************************************************************************************
   
   //********************************************
   //anySimpleType
   //********************************************
   const RuntimeModel::PropertyPtr anySimpleType_S = component->findPropertyByName("_anySimpleType_S");   
   ASSERT_TRUE( anySimpleType_S );
   anySimpleType_S->setValues(RuntimeModel::Property::Values());
   const string anySimpleType_SValue = "anySimpleType_SValue";
   anySimpleType_S->addValue(anySimpleType_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(anySimpleType_S, impl) );
   ASSERT_EQ( impl->anySimpleType_S, anySimpleType_SValue);
  
   //********************************************
   //anyURI
   //********************************************
   const RuntimeModel::PropertyPtr anyURI_S = component->findPropertyByName("_anyURI_S");   
   ASSERT_TRUE( anyURI_S );
   anyURI_S->setValues(RuntimeModel::Property::Values());
   const string anyURI_SValue = "anyURI_SValue";
   anyURI_S->addValue(anyURI_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(anyURI_S, impl) );
   ASSERT_EQ( impl->anyURI_S, anyURI_SValue);
  
   //********************************************
   //base64Binary
   //********************************************
   const RuntimeModel::PropertyPtr base64Binary_S = component->findPropertyByName("_base64Binary_S");   
   ASSERT_TRUE( base64Binary_S );
   base64Binary_S->setValues(RuntimeModel::Property::Values());
   string base64Binary_SValue = "0000";
   base64Binary_S->addValue(base64Binary_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(base64Binary_S, impl) );
   ASSERT_EQ( string(impl->base64Binary_S), base64Binary_SValue);
  
   //********************************************
   //boolean
   //********************************************
   const RuntimeModel::PropertyPtr boolean_S = component->findPropertyByName("_boolean_S");   
   ASSERT_TRUE( boolean_S );
   boolean_S->setValues(RuntimeModel::Property::Values());
   const bool boolean_SValue = false;
   boolean_S->addValue(boost::lexical_cast<string>(boolean_SValue));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(boolean_S, impl) );
   ASSERT_EQ( impl->boolean_S, boolean_SValue);
  
   //********************************************
   //byte
   //********************************************
   const RuntimeModel::PropertyPtr byte_S = component->findPropertyByName("_byte_S");   
   ASSERT_TRUE( byte_S );
   byte_S->setValues(RuntimeModel::Property::Values());
   const int8_t byte_SValue = -23;
   byte_S->addValue( boost::lexical_cast<string>(static_cast<int32_t>(byte_SValue)) );
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(byte_S, impl) );
   ASSERT_EQ( impl->byte_S, byte_SValue);  

   //********************************************
   //date
   //********************************************
   const RuntimeModel::PropertyPtr date_S = component->findPropertyByName("_date_S");   
   ASSERT_TRUE( date_S );
   date_S->setValues(RuntimeModel::Property::Values());
   const string date_SValue = "2012-02-27";
   date_S->addValue(date_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(date_S, impl) );
   ASSERT_EQ( impl->date_S, date_SValue);
  
   //********************************************
   //dateTime
   //********************************************
   const RuntimeModel::PropertyPtr dateTime_S = component->findPropertyByName("_dateTime_S");   
   ASSERT_TRUE( dateTime_S );
   dateTime_S->setValues(RuntimeModel::Property::Values());
   const string dateTime_SValue = "2010-02-27T17:48:00";
   dateTime_S->addValue(dateTime_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(dateTime_S, impl) );
   ASSERT_EQ( impl->dateTime_S, dateTime_SValue);
  
   //********************************************
   //decimal
   //********************************************
   const RuntimeModel::PropertyPtr decimal_S = component->findPropertyByName("_decimal_S");   
   ASSERT_TRUE( decimal_S );
   decimal_S->setValues(RuntimeModel::Property::Values());
   const string decimal_SValue = "46";
   decimal_S->addValue(decimal_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(decimal_S, impl) );
   ASSERT_EQ( impl->decimal_S, decimal_SValue);
  
   //********************************************
   //double
   //********************************************
   const RuntimeModel::PropertyPtr double_S = component->findPropertyByName("_double_S");   
   ASSERT_TRUE( double_S );
   double_S->setValues(RuntimeModel::Property::Values());
   const double double_SValue = 1.7e-230;
   double_S->addValue(boost::lexical_cast<string>(double_SValue));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(double_S, impl) );
   ASSERT_EQ( impl->double_S, double_SValue);  

   //********************************************
   //duration
   //********************************************
   const RuntimeModel::PropertyPtr duration_S = component->findPropertyByName("_duration_S");   
   ASSERT_TRUE( duration_S );
   duration_S->setValues(RuntimeModel::Property::Values());
   const string duration_SValue = "P5Y";
   duration_S->addValue(duration_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(duration_S, impl) );
   ASSERT_EQ( impl->duration_S, duration_SValue);
  
   //********************************************
   //ENTITY
   //********************************************
   const RuntimeModel::PropertyPtr ENTITY_S = component->findPropertyByName("_ENTITY_S");   
   ASSERT_TRUE( ENTITY_S );
   ENTITY_S->setValues(RuntimeModel::Property::Values());
   const string ENTITY_SValue = "ENTITY_SValue";
   ENTITY_S->addValue(ENTITY_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(ENTITY_S, impl) );
   ASSERT_EQ( impl->ENTITY_S, ENTITY_SValue);  

   //********************************************
   //ENTITIES
   //********************************************
   const RuntimeModel::PropertyPtr ENTITIES_S = component->findPropertyByName("_ENTITIES_S");   
   ASSERT_TRUE( ENTITIES_S );
   ENTITIES_S->setValues(RuntimeModel::Property::Values());
   const string ENTITIES_SValue1 = "ENTITIES_SValue1";
   const string ENTITIES_SValue2 = "ENTITIES_SValue2";
   const string ENTITIES_SValue = ENTITIES_SValue1 + " " + ENTITIES_SValue2;
   ENTITIES_S->addValue(ENTITIES_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(ENTITIES_S, impl) );
   ASSERT_EQ( impl->ENTITIES_S.size(), 2 );
   ASSERT_EQ( impl->ENTITIES_S.front(), ENTITIES_SValue1);
   ASSERT_EQ( impl->ENTITIES_S.back(), ENTITIES_SValue2);

   //********************************************
   //float
   //********************************************
   const RuntimeModel::PropertyPtr float_S = component->findPropertyByName("_float_S");   
   ASSERT_TRUE( float_S );
   float_S->setValues(RuntimeModel::Property::Values());
   const float float_SValue = 23.23F;
   float_S->addValue(boost::lexical_cast<string>(float_SValue));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(float_S, impl) );
   ASSERT_EQ( impl->float_S, float_SValue);  

   //********************************************
   //gDay
   //********************************************
   const RuntimeModel::PropertyPtr gDay_S = component->findPropertyByName("_gDay_S");   
   ASSERT_TRUE( gDay_S );
   gDay_S->setValues(RuntimeModel::Property::Values());
   const string gDay_SValue = "---29";
   gDay_S->addValue(gDay_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(gDay_S, impl) );
   ASSERT_EQ( impl->gDay_S, gDay_SValue);
  
   //********************************************
   //gMonth
   //********************************************
   const RuntimeModel::PropertyPtr gMonth_S = component->findPropertyByName("_gMonth_S");   
   ASSERT_TRUE( gMonth_S );
   gMonth_S->setValues(RuntimeModel::Property::Values());
   const string gMonth_SValue = "--08";
   gMonth_S->addValue(gMonth_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(gMonth_S, impl) );
   ASSERT_EQ( impl->gMonth_S, gMonth_SValue);
  
   //********************************************
   //gMonthDay
   //********************************************
   const RuntimeModel::PropertyPtr gMonthDay_S = component->findPropertyByName("_gMonthDay_S");   
   ASSERT_TRUE( gMonthDay_S );
   gMonthDay_S->setValues(RuntimeModel::Property::Values());
   const string gMonthDay_SValue = "--08-29";
   gMonthDay_S->addValue(gMonthDay_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(gMonthDay_S, impl) );
   ASSERT_EQ( impl->gMonthDay_S, gMonthDay_SValue);
  
   //********************************************
   //gYear
   //********************************************
   const RuntimeModel::PropertyPtr gYear_S = component->findPropertyByName("_gYear_S");   
   ASSERT_TRUE( gYear_S );
   gYear_S->setValues(RuntimeModel::Property::Values());
   const string gYear_SValue = "1985";
   gYear_S->addValue(gYear_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(gYear_S, impl) );
   ASSERT_EQ( impl->gYear_S, gYear_SValue);
  
   //********************************************
   //gYearMonth
   //********************************************
   const RuntimeModel::PropertyPtr gYearMonth_S = component->findPropertyByName("_gYearMonth_S");   
   ASSERT_TRUE( gYearMonth_S );
   gYearMonth_S->setValues(RuntimeModel::Property::Values());
   const string gYearMonth_SValue = "1985-08";
   gYearMonth_S->addValue(gYearMonth_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(gYearMonth_S, impl) );
   ASSERT_EQ( impl->gYearMonth_S, gYearMonth_SValue);
  
   //********************************************
   //hexBinary
   //********************************************
   const RuntimeModel::PropertyPtr hexBinary_S = component->findPropertyByName("_hexBinary_S");   
   ASSERT_TRUE( hexBinary_S );
   hexBinary_S->setValues(RuntimeModel::Property::Values());
   string hexBinary_SValue = "00";
   hexBinary_S->addValue(hexBinary_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(hexBinary_S, impl) );
   ASSERT_EQ( string(impl->hexBinary_S), hexBinary_SValue);
  
   //********************************************
   //ID
   //********************************************
   const RuntimeModel::PropertyPtr ID_S = component->findPropertyByName("_ID_S");   
   ASSERT_TRUE( ID_S );
   ID_S->setValues(RuntimeModel::Property::Values());
   const string ID_SValue = "ID_SValue";
   ID_S->addValue(ID_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(ID_S, impl) );
   ASSERT_EQ( impl->ID_S, ID_SValue);
  
   //********************************************
   //IDREF
   //********************************************
   const RuntimeModel::PropertyPtr IDREF_S = component->findPropertyByName("_IDREF_S");   
   ASSERT_TRUE( IDREF_S );
   IDREF_S->setValues(RuntimeModel::Property::Values());
   const string IDREF_SValue = "IDREF_SValue";
   IDREF_S->addValue(IDREF_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(IDREF_S, impl) );
   ASSERT_EQ( impl->IDREF_S, IDREF_SValue);
  
   //********************************************
   //IDREFS
   //********************************************
   const RuntimeModel::PropertyPtr IDREFS_S = component->findPropertyByName("_IDREFS_S");   
   ASSERT_TRUE( IDREFS_S );
   IDREFS_S->setValues(RuntimeModel::Property::Values());
   const string IDREFS_SValue1 = "IDREFS_SValue1";
   const string IDREFS_SValue2 = "IDREFS_SValue2";
   const string IDREFS_SValue = IDREFS_SValue1 + " " + IDREFS_SValue2;
   IDREFS_S->addValue(IDREFS_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(IDREFS_S, impl) );
   ASSERT_EQ( impl->IDREFS_S.size(), 2);
   ASSERT_EQ( impl->IDREFS_S.front(), IDREFS_SValue1);
   ASSERT_EQ( impl->IDREFS_S.back(), IDREFS_SValue2);
  
   //********************************************
   //int
   //********************************************
   const RuntimeModel::PropertyPtr int_S = component->findPropertyByName("_int_S");   
   ASSERT_TRUE( int_S );
   int_S->setValues(RuntimeModel::Property::Values());
   const int32_t int_SValue = -29081985;
   int_S->addValue(boost::lexical_cast<string>(int_SValue));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(int_S, impl) );
   ASSERT_EQ( impl->int_S, int_SValue);  

   //********************************************
   //integer
   //********************************************
   const RuntimeModel::PropertyPtr integer_S = component->findPropertyByName("_integer_S");   
   ASSERT_TRUE( integer_S );
   integer_S->setValues(RuntimeModel::Property::Values());
   const string integer_SValue = "23";
   integer_S->addValue(integer_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(integer_S, impl) );
   ASSERT_EQ( impl->integer_S, integer_SValue);
  
   //********************************************
   //language
   //********************************************
   const RuntimeModel::PropertyPtr language_S = component->findPropertyByName("_language_S");   
   ASSERT_TRUE( language_S );
   language_S->setValues(RuntimeModel::Property::Values());
   const string language_SValue = "de";
   language_S->addValue(language_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(language_S, impl) );
   ASSERT_EQ( impl->language_S, language_SValue);
  
   //********************************************
   //long
   //********************************************
   const RuntimeModel::PropertyPtr long_S = component->findPropertyByName("_long_S");   
   ASSERT_TRUE( long_S );
   long_S->setValues(RuntimeModel::Property::Values());
   const int64_t long_SValue = -0x123456789ABCDE;
   long_S->addValue(boost::lexical_cast<string>(long_SValue));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(long_S, impl) );
   ASSERT_EQ( impl->long_S, long_SValue);  
  
   //********************************************
   //Name
   //********************************************
   const RuntimeModel::PropertyPtr Name_S = component->findPropertyByName("_Name_S");   
   ASSERT_TRUE( Name_S );
   Name_S->setValues(RuntimeModel::Property::Values());
   const string Name_SValue = "Name_SValue";
   Name_S->addValue(Name_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(Name_S, impl) );
   ASSERT_EQ( impl->Name_S, Name_SValue);
  
   //********************************************
   //NCName
   //********************************************
   const RuntimeModel::PropertyPtr NCName_S = component->findPropertyByName("_NCName_S");   
   ASSERT_TRUE( NCName_S );
   NCName_S->setValues(RuntimeModel::Property::Values());
   const string NCName_SValue = "NCName_SValue";
   NCName_S->addValue(NCName_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(NCName_S, impl) );
   ASSERT_EQ( impl->NCName_S, NCName_SValue);
  
   //********************************************
   //negativeInteger
   //********************************************
   const RuntimeModel::PropertyPtr negativeInteger_S = component->findPropertyByName("_negativeInteger_S");   
   ASSERT_TRUE( negativeInteger_S );
   negativeInteger_S->setValues(RuntimeModel::Property::Values());
   const string negativeInteger_SValue = "-23";
   negativeInteger_S->addValue(negativeInteger_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(negativeInteger_S, impl) );
   ASSERT_EQ( impl->negativeInteger_S, negativeInteger_SValue);
  
   //********************************************
   //NMTOKEN
   //********************************************
   const RuntimeModel::PropertyPtr NMTOKEN_S = component->findPropertyByName("_NMTOKEN_S");   
   ASSERT_TRUE( NMTOKEN_S );
   NMTOKEN_S->setValues(RuntimeModel::Property::Values());
   const string NMTOKEN_SValue = "NMTOKEN_SValue";
   NMTOKEN_S->addValue(NMTOKEN_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(NMTOKEN_S, impl) );
   ASSERT_EQ( impl->NMTOKEN_S, NMTOKEN_SValue);
  
   //********************************************
   //NMTOKENS
   //********************************************
   const RuntimeModel::PropertyPtr NMTOKENS_S = component->findPropertyByName("_NMTOKENS_S");   
   ASSERT_TRUE( NMTOKENS_S );
   NMTOKENS_S->setValues(RuntimeModel::Property::Values());
   const string NMTOKENS_SValue1 = "NMTOKENS_SValue1";
   const string NMTOKENS_SValue2 = "NMTOKENS_SValue2";
   const string NMTOKENS_SValue = NMTOKENS_SValue1 + " " + NMTOKENS_SValue2;
   NMTOKENS_S->addValue(NMTOKENS_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(NMTOKENS_S, impl) );
   ASSERT_EQ( impl->NMTOKENS_S.size(), 2 );
   ASSERT_EQ( impl->NMTOKENS_S.front(), NMTOKENS_SValue1);
   ASSERT_EQ( impl->NMTOKENS_S.back(), NMTOKENS_SValue2);
  
   //********************************************
   //nonNegativeInteger
   //********************************************
   const RuntimeModel::PropertyPtr nonNegativeInteger_S = component->findPropertyByName("_nonNegativeInteger_S");   
   ASSERT_TRUE( nonNegativeInteger_S );
   nonNegativeInteger_S->setValues(RuntimeModel::Property::Values());
   const string nonNegativeInteger_SValue = "46";
   nonNegativeInteger_S->addValue(nonNegativeInteger_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(nonNegativeInteger_S, impl) );
   ASSERT_EQ( impl->nonNegativeInteger_S, nonNegativeInteger_SValue);
  
   //********************************************
   //nonPositiveInteger
   //********************************************
   const RuntimeModel::PropertyPtr nonPositiveInteger_S = component->findPropertyByName("_nonPositiveInteger_S");   
   ASSERT_TRUE( nonPositiveInteger_S );
   nonPositiveInteger_S->setValues(RuntimeModel::Property::Values());
   const string nonPositiveInteger_SValue = "-46";
   nonPositiveInteger_S->addValue(nonPositiveInteger_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(nonPositiveInteger_S, impl) );
   ASSERT_EQ( impl->nonPositiveInteger_S, nonPositiveInteger_SValue);
  
   //********************************************
   //normalizedString
   //********************************************
   const RuntimeModel::PropertyPtr normalizedString_S = component->findPropertyByName("_normalizedString_S");   
   ASSERT_TRUE( normalizedString_S );
   normalizedString_S->setValues(RuntimeModel::Property::Values());
   const string normalizedString_SValue = "normalizedString_SValue";
   normalizedString_S->addValue(normalizedString_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(normalizedString_S, impl) );
   ASSERT_EQ( impl->normalizedString_S, normalizedString_SValue);
  
   //********************************************
   //NOTATION
   //********************************************
   const RuntimeModel::PropertyPtr NOTATION_S = component->findPropertyByName("_NOTATION_S");   
   ASSERT_TRUE( NOTATION_S );
   NOTATION_S->setValues(RuntimeModel::Property::Values());
   const string NOTATION_SValue = "NOTATION_SValue";
   NOTATION_S->addValue(NOTATION_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(NOTATION_S, impl) );
   ASSERT_EQ( impl->NOTATION_S, NOTATION_SValue);
  
   //********************************************
   //positiveInteger
   //********************************************
   const RuntimeModel::PropertyPtr positiveInteger_S = component->findPropertyByName("_positiveInteger_S");   
   ASSERT_TRUE( positiveInteger_S );
   positiveInteger_S->setValues(RuntimeModel::Property::Values());
   const string positiveInteger_SValue = "23";
   positiveInteger_S->addValue(positiveInteger_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(positiveInteger_S, impl) );
   ASSERT_EQ( impl->positiveInteger_S, positiveInteger_SValue);
  
   //********************************************
   //QName
   //********************************************
   const RuntimeModel::PropertyPtr QName_S = component->findPropertyByName("_QName_S");   
   ASSERT_TRUE( QName_S );
   QName_S->setValues(RuntimeModel::Property::Values());
   const string QName_SValue = "ns:QName_SValue";
   QName_S->addValue(QName_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(QName_S, impl) );
   ASSERT_EQ( impl->QName_S, QName_SValue);
  
   //********************************************
   //short
   //********************************************
   const RuntimeModel::PropertyPtr short_S = component->findPropertyByName("_short_S");   
   ASSERT_TRUE( short_S );
   short_S->setValues(RuntimeModel::Property::Values());
   const int16_t short_SValue = -23000;
   short_S->addValue(boost::lexical_cast<string>(short_SValue));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(short_S, impl) );
   ASSERT_EQ( impl->short_S, short_SValue);  

   //********************************************
   //string
   //********************************************
   const RuntimeModel::PropertyPtr string_S = component->findPropertyByName("_string_S");   
   ASSERT_TRUE( string_S );
   string_S->setValues(RuntimeModel::Property::Values());
   const string string_SValue = "string_SValue";
   string_S->addValue(string_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(string_S, impl) );
   ASSERT_EQ( impl->string_S, string_SValue);
  
   //********************************************
   //time
   //********************************************
   const RuntimeModel::PropertyPtr time_S = component->findPropertyByName("_time_S");   
   ASSERT_TRUE( time_S );
   time_S->setValues(RuntimeModel::Property::Values());
   const string time_SValue = "23:39:00";
   time_S->addValue(time_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(time_S, impl) );
   ASSERT_EQ( impl->time_S, time_SValue);
  
   //********************************************
   //token
   //********************************************
   const RuntimeModel::PropertyPtr token_S = component->findPropertyByName("_token_S");   
   ASSERT_TRUE( token_S );
   token_S->setValues(RuntimeModel::Property::Values());
   const string token_SValue = "token_SValue";
   token_S->addValue(token_SValue);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(token_S, impl) );
   ASSERT_EQ( impl->token_S, token_SValue);
  
   //********************************************
   //unsignedByte
   //********************************************
   const RuntimeModel::PropertyPtr unsignedByte_S = component->findPropertyByName("_unsignedByte_S");   
   ASSERT_TRUE( unsignedByte_S );
   unsignedByte_S->setValues(RuntimeModel::Property::Values());
   const uint8_t unsignedByte_SValue = 255;
   unsignedByte_S->addValue(boost::lexical_cast<string>(static_cast<uint32_t>(unsignedByte_SValue)));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(unsignedByte_S, impl) );
   ASSERT_EQ( impl->unsignedByte_S, unsignedByte_SValue);
  
   //********************************************
   //unsignedInt
   //********************************************
   const RuntimeModel::PropertyPtr unsignedInt_S = component->findPropertyByName("_unsignedInt_S");   
   ASSERT_TRUE( unsignedInt_S );
   unsignedInt_S->setValues(RuntimeModel::Property::Values());
   const uint32_t unsignedInt_SValue = 29081985;
   unsignedInt_S->addValue(boost::lexical_cast<string>(unsignedInt_SValue));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(unsignedInt_S, impl) );
   ASSERT_EQ( impl->unsignedInt_S, unsignedInt_SValue);
  
   //********************************************
   //unsignedLong
   //********************************************
   const RuntimeModel::PropertyPtr unsignedLong_S = component->findPropertyByName("_unsignedLong_S");   
   ASSERT_TRUE( unsignedLong_S );
   unsignedLong_S->setValues(RuntimeModel::Property::Values());
   const uint64_t unsignedLong_SValue = 0xABCDABCDABCDFFFF;
   unsignedLong_S->addValue(boost::lexical_cast<string>(unsignedLong_SValue));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(unsignedLong_S, impl) );
   ASSERT_EQ( impl->unsignedLong_S, unsignedLong_SValue);
  
   //********************************************
   //unsignedShort
   //********************************************
   const RuntimeModel::PropertyPtr unsignedShort_S = component->findPropertyByName("_unsignedShort_S");   
   ASSERT_TRUE( unsignedShort_S );
   unsignedShort_S->setValues(RuntimeModel::Property::Values());
   const uint16_t unsignedShort_SValue = 23000;
   unsignedShort_S->addValue(boost::lexical_cast<string>(unsignedShort_SValue));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(unsignedShort_S, impl) );
   ASSERT_EQ( impl->unsignedShort_S, unsignedShort_SValue);
  
   //**********************************************************************************************
   //                                        @many="true"
   //**********************************************************************************************

   //********************************************
   //anySimpleType
   //********************************************
   const RuntimeModel::PropertyPtr anySimpleType_M = component->findPropertyByName("_anySimpleType_M");   
   ASSERT_TRUE( anySimpleType_M );
   anySimpleType_M->setValues(RuntimeModel::Property::Values());
   const string anySimpleType_MValue1 = "anySimpleType_MValue1";
   const string anySimpleType_MValue2 = "anySimpleType_MValue2";
   anySimpleType_M->addValue(anySimpleType_MValue1);
   anySimpleType_M->addValue(anySimpleType_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(anySimpleType_M, impl) );
   ASSERT_EQ( impl->anySimpleType_M.size(), 2 );
   ASSERT_EQ( impl->anySimpleType_M.front(), anySimpleType_MValue1 );
   ASSERT_EQ( impl->anySimpleType_M.back(), anySimpleType_MValue2 );
  
   //********************************************
   //anyURI
   //********************************************
   const RuntimeModel::PropertyPtr anyURI_M = component->findPropertyByName("_anyURI_M");   
   ASSERT_TRUE( anyURI_M );
   anyURI_M->setValues(RuntimeModel::Property::Values());
   const string anyURI_MValue1 = "anyURI_MValue1";
   const string anyURI_MValue2 = "anyURI_MValue2";
   anyURI_M->addValue(anyURI_MValue1);
   anyURI_M->addValue(anyURI_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(anyURI_M, impl) );
   ASSERT_EQ( impl->anyURI_M.size(), 2 );
   ASSERT_EQ( impl->anyURI_M.front(), anyURI_MValue1 );
   ASSERT_EQ( impl->anyURI_M.back(), anyURI_MValue2 );
  
   //********************************************
   //base64Binary
   //********************************************
   const RuntimeModel::PropertyPtr base64Binary_M = component->findPropertyByName("_base64Binary_M");   
   ASSERT_TRUE( base64Binary_M );
   base64Binary_M->setValues(RuntimeModel::Property::Values());
   string base64Binary_MValue1 = "0000";
   string base64Binary_MValue2 = "0001";
   base64Binary_M->addValue(base64Binary_MValue1);
   base64Binary_M->addValue(base64Binary_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(base64Binary_M, impl) );
   ASSERT_EQ( impl->base64Binary_M.size(), 2 );
   ASSERT_EQ( string(impl->base64Binary_M.front()), base64Binary_MValue1 );
   ASSERT_EQ( string(impl->base64Binary_M.back()), base64Binary_MValue2 );
  
   //********************************************
   //boolean
   //********************************************
   const RuntimeModel::PropertyPtr boolean_M = component->findPropertyByName("_boolean_M");   
   ASSERT_TRUE( boolean_M );
   boolean_M->setValues(RuntimeModel::Property::Values());
   const bool boolean_MValue1 = false;
   const bool boolean_MValue2 = true;
   boolean_M->addValue(boost::lexical_cast<string>(boolean_MValue1));
   boolean_M->addValue(boost::lexical_cast<string>(boolean_MValue2));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(boolean_M, impl) );
   ASSERT_EQ( impl->boolean_M.size(), 2 );
   ASSERT_EQ( impl->boolean_M.front(), boolean_MValue1 );
   ASSERT_EQ( impl->boolean_M.back(), boolean_MValue2 );
  
   //********************************************
   //byte
   //********************************************
   const RuntimeModel::PropertyPtr byte_M = component->findPropertyByName("_byte_M");   
   ASSERT_TRUE( byte_M );
   byte_M->setValues(RuntimeModel::Property::Values());
   const int8_t byte_MValue1 = -23;
   const int8_t byte_MValue2 = -24;
   byte_M->addValue(boost::lexical_cast<string>(static_cast<int32_t>(byte_MValue1)));
   byte_M->addValue(boost::lexical_cast<string>(static_cast<int32_t>(byte_MValue2)));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(byte_M, impl) );
   ASSERT_EQ( impl->byte_M.size(), 2 );
   ASSERT_EQ( impl->byte_M.front(), byte_MValue1 );
   ASSERT_EQ( impl->byte_M.back(), byte_MValue2 );  

   //********************************************
   //date
   //********************************************
   const RuntimeModel::PropertyPtr date_M = component->findPropertyByName("_date_M");   
   ASSERT_TRUE( date_M );
   date_M->setValues(RuntimeModel::Property::Values());
   const string date_MValue1 = "2012-02-27";
   const string date_MValue2 = "2012-02-28";
   date_M->addValue(date_MValue1);
   date_M->addValue(date_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(date_M, impl) );
   ASSERT_EQ( impl->date_M.size(), 2 );
   ASSERT_EQ( impl->date_M.front(), date_MValue1 );
   ASSERT_EQ( impl->date_M.back(), date_MValue2 );
  
   //********************************************
   //dateTime
   //********************************************
   const RuntimeModel::PropertyPtr dateTime_M = component->findPropertyByName("_dateTime_M");   
   ASSERT_TRUE( dateTime_M );
   dateTime_M->setValues(RuntimeModel::Property::Values());
   const string dateTime_MValue1 = "2010-02-27T17:48:00";
   const string dateTime_MValue2 = "2010-02-27T17:49:00";
   dateTime_M->addValue(dateTime_MValue1);
   dateTime_M->addValue(dateTime_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(dateTime_M, impl) );
   ASSERT_EQ( impl->dateTime_M.size(), 2 );
   ASSERT_EQ( impl->dateTime_M.front(), dateTime_MValue1 );
   ASSERT_EQ( impl->dateTime_M.back(), dateTime_MValue2 );
  
   //********************************************
   //decimal
   //********************************************
   const RuntimeModel::PropertyPtr decimal_M = component->findPropertyByName("_decimal_M");   
   ASSERT_TRUE( decimal_M );
   decimal_M->setValues(RuntimeModel::Property::Values());
   const string decimal_MValue1 = "46";
   const string decimal_MValue2 = "47";
   decimal_M->addValue(decimal_MValue1);
   decimal_M->addValue(decimal_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(decimal_M, impl) );
   ASSERT_EQ( impl->decimal_M.size(), 2 );
   ASSERT_EQ( impl->decimal_M.front(), decimal_MValue1 );
   ASSERT_EQ( impl->decimal_M.back(), decimal_MValue2 );
  
   //********************************************
   //double
   //********************************************
   const RuntimeModel::PropertyPtr double_M = component->findPropertyByName("_double_M");   
   ASSERT_TRUE( double_M );
   double_M->setValues(RuntimeModel::Property::Values());
   const double double_MValue1 = 1.7e-230;
   const double double_MValue2 = 1.7e-229;
   double_M->addValue(boost::lexical_cast<string>(double_MValue1));
   double_M->addValue(boost::lexical_cast<string>(double_MValue2));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(double_M, impl) );
   ASSERT_EQ( impl->double_M.size(), 2 );
   ASSERT_EQ( impl->double_M.front(), double_MValue1 );
   ASSERT_EQ( impl->double_M.back(), double_MValue2 );
  

   //********************************************
   //duration
   //********************************************
   const RuntimeModel::PropertyPtr duration_M = component->findPropertyByName("_duration_M");   
   ASSERT_TRUE( duration_M );
   duration_M->setValues(RuntimeModel::Property::Values());
   const string duration_MValue1 = "P5Y";
   const string duration_MValue2 = "P6Y";
   duration_M->addValue(duration_MValue1);
   duration_M->addValue(duration_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(duration_M, impl) );
   ASSERT_EQ( impl->duration_M.size(), 2 );
   ASSERT_EQ( impl->duration_M.front(), duration_MValue1 );
   ASSERT_EQ( impl->duration_M.back(), duration_MValue2 );
  
   //********************************************
   //ENTITY
   //********************************************
   const RuntimeModel::PropertyPtr ENTITY_M = component->findPropertyByName("_ENTITY_M");   
   ASSERT_TRUE( ENTITY_M );
   ENTITY_M->setValues(RuntimeModel::Property::Values());
   const string ENTITY_MValue1 = "ENTITY_MValue1";
   const string ENTITY_MValue2 = "ENTITY_MValue2";
   ENTITY_M->addValue(ENTITY_MValue1);
   ENTITY_M->addValue(ENTITY_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(ENTITY_M, impl) );
   ASSERT_EQ( impl->ENTITY_M.size(), 2 );
   ASSERT_EQ( impl->ENTITY_M.front(), ENTITY_MValue1 );
   ASSERT_EQ( impl->ENTITY_M.back(), ENTITY_MValue2 );
  
   //********************************************
   //ENTITIES
   //********************************************
   const RuntimeModel::PropertyPtr ENTITIES_M = component->findPropertyByName("_ENTITIES_M");   
   ASSERT_TRUE( ENTITIES_M );
   ENTITIES_M->setValues(RuntimeModel::Property::Values());
   const string ENTITIES_MValue1_1 = "ENTITIES_MValue1";
   const string ENTITIES_MValue1_2 = "ENTITIES_MValue2";
   const string ENTITIES_MValue2_1 = "ENTITIES_MValue3";
   const string ENTITIES_MValue2_2 = "ENTITIES_MValue4";
   const string ENTITIES_MValue1 = ENTITIES_MValue1_1 + " " + ENTITIES_MValue1_2;
   const string ENTITIES_MValue2 = ENTITIES_MValue2_1 + " " + ENTITIES_MValue2_2;
   ENTITIES_M->addValue(ENTITIES_MValue1);
   ENTITIES_M->addValue(ENTITIES_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(ENTITIES_M, impl) );
   ASSERT_EQ( impl->ENTITIES_M.size(), 2 );
   ASSERT_EQ( impl->ENTITIES_M.front().size(), 2);
   ASSERT_EQ( impl->ENTITIES_M.back().size(), 2);
   ASSERT_EQ( impl->ENTITIES_M.front().front(), ENTITIES_MValue1_1);
   ASSERT_EQ( impl->ENTITIES_M.front().back(), ENTITIES_MValue1_2);
   ASSERT_EQ( impl->ENTITIES_M.back().front(), ENTITIES_MValue2_1);
   ASSERT_EQ( impl->ENTITIES_M.back().back(), ENTITIES_MValue2_2);
  
   //********************************************
   //float
   //********************************************
   const RuntimeModel::PropertyPtr float_M = component->findPropertyByName("_float_M");   
   ASSERT_TRUE( float_M );
   float_M->setValues(RuntimeModel::Property::Values());
   const float float_MValue1 = 23.23F;
   const float float_MValue2 = 24.23F;
   float_M->addValue(boost::lexical_cast<string>(float_MValue1));
   float_M->addValue(boost::lexical_cast<string>(float_MValue2));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(float_M, impl) );
   ASSERT_EQ( impl->float_M.size(), 2 );
   ASSERT_EQ( impl->float_M.front(), float_MValue1 );
   ASSERT_EQ( impl->float_M.back(), float_MValue2 );  

   //********************************************
   //gDay
   //********************************************
   const RuntimeModel::PropertyPtr gDay_M = component->findPropertyByName("_gDay_M");   
   ASSERT_TRUE( gDay_M );
   gDay_M->setValues(RuntimeModel::Property::Values());
   const string gDay_MValue1 = "---29";
   const string gDay_MValue2 = "---30";
   gDay_M->addValue(gDay_MValue1);
   gDay_M->addValue(gDay_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(gDay_M, impl) );
   ASSERT_EQ( impl->gDay_M.size(), 2 );
   ASSERT_EQ( impl->gDay_M.front(), gDay_MValue1 );
   ASSERT_EQ( impl->gDay_M.back(), gDay_MValue2 );
  
   //********************************************
   //gMonth
   //********************************************
   const RuntimeModel::PropertyPtr gMonth_M = component->findPropertyByName("_gMonth_M");   
   ASSERT_TRUE( gMonth_M );
   gMonth_M->setValues(RuntimeModel::Property::Values());
   const string gMonth_MValue1 = "--08";
   const string gMonth_MValue2 = "--09";
   gMonth_M->addValue(gMonth_MValue1);
   gMonth_M->addValue(gMonth_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(gMonth_M, impl) );
   ASSERT_EQ( impl->gMonth_M.size(), 2 );
   ASSERT_EQ( impl->gMonth_M.front(), gMonth_MValue1 );
   ASSERT_EQ( impl->gMonth_M.back(), gMonth_MValue2 );
  
   //********************************************
   //gMonthDay
   //********************************************
   const RuntimeModel::PropertyPtr gMonthDay_M = component->findPropertyByName("_gMonthDay_M");   
   ASSERT_TRUE( gMonthDay_M );
   gMonthDay_M->setValues(RuntimeModel::Property::Values());
   const string gMonthDay_MValue1 = "--08-29";
   const string gMonthDay_MValue2 = "--09-30";
   gMonthDay_M->addValue(gMonthDay_MValue1);
   gMonthDay_M->addValue(gMonthDay_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(gMonthDay_M, impl) );
   ASSERT_EQ( impl->gMonthDay_M.size(), 2 );
   ASSERT_EQ( impl->gMonthDay_M.front(), gMonthDay_MValue1 );
   ASSERT_EQ( impl->gMonthDay_M.back(), gMonthDay_MValue2 );
  
   //********************************************
   //gYear
   //********************************************
   const RuntimeModel::PropertyPtr gYear_M = component->findPropertyByName("_gYear_M");   
   ASSERT_TRUE( gYear_M );
   gYear_M->setValues(RuntimeModel::Property::Values());
   const string gYear_MValue1 = "1985";
   const string gYear_MValue2 = "1986";
   gYear_M->addValue(gYear_MValue1);
   gYear_M->addValue(gYear_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(gYear_M, impl) );
   ASSERT_EQ( impl->gYear_M.size(), 2 );
   ASSERT_EQ( impl->gYear_M.front(), gYear_MValue1 );
   ASSERT_EQ( impl->gYear_M.back(), gYear_MValue2 );
  
   //********************************************
   //gYearMonth
   //********************************************
   const RuntimeModel::PropertyPtr gYearMonth_M = component->findPropertyByName("_gYearMonth_M");   
   ASSERT_TRUE( gYearMonth_M );
   gYearMonth_M->setValues(RuntimeModel::Property::Values());
   const string gYearMonth_MValue1 = "1985-08";
   const string gYearMonth_MValue2 = "1986-09";
   gYearMonth_M->addValue(gYearMonth_MValue1);
   gYearMonth_M->addValue(gYearMonth_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(gYearMonth_M, impl) );
   ASSERT_EQ( impl->gYearMonth_M.size(), 2 );
   ASSERT_EQ( impl->gYearMonth_M.front(), gYearMonth_MValue1 );
   ASSERT_EQ( impl->gYearMonth_M.back(), gYearMonth_MValue2 );
  
   //********************************************
   //hexBinary
   //********************************************
   const RuntimeModel::PropertyPtr hexBinary_M = component->findPropertyByName("_hexBinary_M");   
   ASSERT_TRUE( hexBinary_M );
   hexBinary_M->setValues(RuntimeModel::Property::Values());
   string hexBinary_MValue1 = "00";
   string hexBinary_MValue2 = "01";
   hexBinary_M->addValue(hexBinary_MValue1);
   hexBinary_M->addValue(hexBinary_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(hexBinary_M, impl) );
   ASSERT_EQ( impl->hexBinary_M.size(), 2 );
   ASSERT_EQ( string(impl->hexBinary_M.front()), hexBinary_MValue1 );
   ASSERT_EQ( string(impl->hexBinary_M.back()), hexBinary_MValue2 );
  
   //********************************************
   //ID
   //********************************************
   const RuntimeModel::PropertyPtr ID_M = component->findPropertyByName("_ID_M");   
   ASSERT_TRUE( ID_M );
   ID_M->setValues(RuntimeModel::Property::Values());
   const string ID_MValue1 = "ID_MValue1";
   const string ID_MValue2 = "ID_MValue2";
   ID_M->addValue(ID_MValue1);
   ID_M->addValue(ID_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(ID_M, impl) );
   ASSERT_EQ( impl->ID_M.size(), 2 );
   ASSERT_EQ( impl->ID_M.front(), ID_MValue1 );
   ASSERT_EQ( impl->ID_M.back(), ID_MValue2 );
  
   //********************************************
   //IDREF
   //********************************************
   const RuntimeModel::PropertyPtr IDREF_M = component->findPropertyByName("_IDREF_M");   
   ASSERT_TRUE( IDREF_M );
   IDREF_M->setValues(RuntimeModel::Property::Values());
   const string IDREF_MValue1 = "IDREF_MValue1";
   const string IDREF_MValue2 = "IDREF_MValue2";
   IDREF_M->addValue(IDREF_MValue1);
   IDREF_M->addValue(IDREF_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(IDREF_M, impl) );
   ASSERT_EQ( impl->IDREF_M.size(), 2 );
   ASSERT_EQ( impl->IDREF_M.front(), IDREF_MValue1 );
   ASSERT_EQ( impl->IDREF_M.back(), IDREF_MValue2 );   

   //********************************************
   //IDREFS
   //********************************************
   const RuntimeModel::PropertyPtr IDREFS_M = component->findPropertyByName("_IDREFS_M");   
   ASSERT_TRUE( IDREFS_M );
   IDREFS_M->setValues(RuntimeModel::Property::Values());
   const string IDREFS_MValue1_1 = "IDREFS_MValue1";
   const string IDREFS_MValue1_2 = "IDREFS_MValue2";
   const string IDREFS_MValue2_1 = "IDREFS_MValue3";
   const string IDREFS_MValue2_2 = "IDREFS_MValue4";
   const string IDREFS_MValue1 = IDREFS_MValue1_1 + " " + IDREFS_MValue1_2;
   const string IDREFS_MValue2 = IDREFS_MValue2_1 + " " + IDREFS_MValue2_2;
   IDREFS_M->addValue(IDREFS_MValue1);
   IDREFS_M->addValue(IDREFS_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(IDREFS_M, impl) );
   ASSERT_EQ( impl->IDREFS_M.size(), 2 );
   ASSERT_EQ( impl->IDREFS_M.front().size(), 2);
   ASSERT_EQ( impl->IDREFS_M.back().size(), 2);
   ASSERT_EQ( impl->IDREFS_M.front().front(), IDREFS_MValue1_1);
   ASSERT_EQ( impl->IDREFS_M.front().back(), IDREFS_MValue1_2);
   ASSERT_EQ( impl->IDREFS_M.back().front(), IDREFS_MValue2_1);
   ASSERT_EQ( impl->IDREFS_M.back().back(), IDREFS_MValue2_2);
  
   //********************************************
   //int
   //********************************************
   const RuntimeModel::PropertyPtr int_M = component->findPropertyByName("_int_M");   
   ASSERT_TRUE( int_M );
   int_M->setValues(RuntimeModel::Property::Values());
   const int32_t int_MValue1 = -29081985;
   const int32_t int_MValue2 = -29081984;
   int_M->addValue(boost::lexical_cast<string>(int_MValue1));
   int_M->addValue(boost::lexical_cast<string>(int_MValue2));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(int_M, impl) );
   ASSERT_EQ( impl->int_M.size(), 2 );
   ASSERT_EQ( impl->int_M.front(), int_MValue1 );
   ASSERT_EQ( impl->int_M.back(), int_MValue2 );  

   //********************************************
   //integer
   //********************************************
   const RuntimeModel::PropertyPtr integer_M = component->findPropertyByName("_integer_M");   
   ASSERT_TRUE( integer_M );
   integer_M->setValues(RuntimeModel::Property::Values());
   const string integer_MValue1 = "23";
   const string integer_MValue2 = "24";
   integer_M->addValue(integer_MValue1);
   integer_M->addValue(integer_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(integer_M, impl) );
   ASSERT_EQ( impl->integer_M.size(), 2 );
   ASSERT_EQ( impl->integer_M.front(), integer_MValue1 );
   ASSERT_EQ( impl->integer_M.back(), integer_MValue2 );
  
   //********************************************
   //language
   //********************************************
   const RuntimeModel::PropertyPtr language_M = component->findPropertyByName("_language_M");   
   ASSERT_TRUE( language_M );
   language_M->setValues(RuntimeModel::Property::Values());
   const string language_MValue1 = "de";
   const string language_MValue2 = "en";
   language_M->addValue(language_MValue1);
   language_M->addValue(language_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(language_M, impl) );
   ASSERT_EQ( impl->language_M.size(), 2 );
   ASSERT_EQ( impl->language_M.front(), language_MValue1 );
   ASSERT_EQ( impl->language_M.back(), language_MValue2 );
  
   //********************************************
   //long
   //********************************************
   const RuntimeModel::PropertyPtr long_M = component->findPropertyByName("_long_M");   
   ASSERT_TRUE( long_M );
   long_M->setValues(RuntimeModel::Property::Values());
   const int64_t long_MValue1 = -0x123456789ABCDE;
   const int64_t long_MValue2 = -0x123456789ABCDD;
   long_M->addValue(boost::lexical_cast<string>(long_MValue1));
   long_M->addValue(boost::lexical_cast<string>(long_MValue2));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(long_M, impl) );
   ASSERT_EQ( impl->long_M.size(), 2 );
   ASSERT_EQ( impl->long_M.front(), long_MValue1 );
   ASSERT_EQ( impl->long_M.back(), long_MValue2 );  

   //********************************************
   //Name
   //********************************************
   const RuntimeModel::PropertyPtr Name_M = component->findPropertyByName("_Name_M");   
   ASSERT_TRUE( Name_M );
   Name_M->setValues(RuntimeModel::Property::Values());
   const string Name_MValue1 = "Name_MValue1";
   const string Name_MValue2 = "Name_MValue2";
   Name_M->addValue(Name_MValue1);
   Name_M->addValue(Name_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(Name_M, impl) );
   ASSERT_EQ( impl->Name_M.size(), 2 );
   ASSERT_EQ( impl->Name_M.front(), Name_MValue1 );
   ASSERT_EQ( impl->Name_M.back(), Name_MValue2 );
  
   //********************************************
   //NCName
   //********************************************
   const RuntimeModel::PropertyPtr NCName_M = component->findPropertyByName("_NCName_M");   
   ASSERT_TRUE( NCName_M );
   NCName_M->setValues(RuntimeModel::Property::Values());
   const string NCName_MValue1 = "NCName_MValue1";
   const string NCName_MValue2 = "NCName_MValue2";
   NCName_M->addValue(NCName_MValue1);
   NCName_M->addValue(NCName_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(NCName_M, impl) );
   ASSERT_EQ( impl->NCName_M.size(), 2 );
   ASSERT_EQ( impl->NCName_M.front(), NCName_MValue1 );
   ASSERT_EQ( impl->NCName_M.back(), NCName_MValue2 );
  
   //********************************************
   //negativeInteger
   //********************************************
   const RuntimeModel::PropertyPtr negativeInteger_M = component->findPropertyByName("_negativeInteger_M");   
   ASSERT_TRUE( negativeInteger_M );
   negativeInteger_M->setValues(RuntimeModel::Property::Values());
   const string negativeInteger_MValue1 = "-23";
   const string negativeInteger_MValue2 = "-22";
   negativeInteger_M->addValue(negativeInteger_MValue1);
   negativeInteger_M->addValue(negativeInteger_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(negativeInteger_M, impl) );
   ASSERT_EQ( impl->negativeInteger_M.size(), 2 );
   ASSERT_EQ( impl->negativeInteger_M.front(), negativeInteger_MValue1 );
   ASSERT_EQ( impl->negativeInteger_M.back(), negativeInteger_MValue2 );
  
   //********************************************
   //NMTOKEN
   //********************************************
   const RuntimeModel::PropertyPtr NMTOKEN_M = component->findPropertyByName("_NMTOKEN_M");   
   ASSERT_TRUE( NMTOKEN_M );
   NMTOKEN_M->setValues(RuntimeModel::Property::Values());
   const string NMTOKEN_MValue1 = "NMTOKEN_MValue1";
   const string NMTOKEN_MValue2 = "NMTOKEN_MValue2";
   NMTOKEN_M->addValue(NMTOKEN_MValue1);
   NMTOKEN_M->addValue(NMTOKEN_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(NMTOKEN_M, impl) );
   ASSERT_EQ( impl->NMTOKEN_M.size(), 2 );
   ASSERT_EQ( impl->NMTOKEN_M.front(), NMTOKEN_MValue1 );
   ASSERT_EQ( impl->NMTOKEN_M.back(), NMTOKEN_MValue2 );  

   //********************************************
   //NMTOKENS
   //********************************************
   const RuntimeModel::PropertyPtr NMTOKENS_M = component->findPropertyByName("_NMTOKENS_M");   
   ASSERT_TRUE( NMTOKENS_M );
   NMTOKENS_M->setValues(RuntimeModel::Property::Values());
   const string NMTOKENS_MValue1_1 = "NMTOKENS_MValue1";
   const string NMTOKENS_MValue1_2 = "NMTOKENS_MValue2";
   const string NMTOKENS_MValue2_1 = "NMTOKENS_MValue3";
   const string NMTOKENS_MValue2_2 = "NMTOKENS_MValue4";
   const string NMTOKENS_MValue1 = NMTOKENS_MValue1_1 + " " + NMTOKENS_MValue1_2;
   const string NMTOKENS_MValue2 = NMTOKENS_MValue2_1 + " " + NMTOKENS_MValue2_2;
   NMTOKENS_M->addValue(NMTOKENS_MValue1);
   NMTOKENS_M->addValue(NMTOKENS_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(NMTOKENS_M, impl) );
   ASSERT_EQ( impl->NMTOKENS_M.size(), 2 );
   ASSERT_EQ( impl->NMTOKENS_M.front().size(), 2);
   ASSERT_EQ( impl->NMTOKENS_M.back().size(), 2);
   ASSERT_EQ( impl->NMTOKENS_M.front().front(), NMTOKENS_MValue1_1);
   ASSERT_EQ( impl->NMTOKENS_M.front().back(), NMTOKENS_MValue1_2);
   ASSERT_EQ( impl->NMTOKENS_M.back().front(), NMTOKENS_MValue2_1);
   ASSERT_EQ( impl->NMTOKENS_M.back().back(), NMTOKENS_MValue2_2);
  
   //********************************************
   //nonNegativeInteger
   //********************************************
   const RuntimeModel::PropertyPtr nonNegativeInteger_M = component->findPropertyByName("_nonNegativeInteger_M");   
   ASSERT_TRUE( nonNegativeInteger_M );
   nonNegativeInteger_M->setValues(RuntimeModel::Property::Values());
   const string nonNegativeInteger_MValue1 = "46";
   const string nonNegativeInteger_MValue2 = "45";
   nonNegativeInteger_M->addValue(nonNegativeInteger_MValue1);
   nonNegativeInteger_M->addValue(nonNegativeInteger_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(nonNegativeInteger_M, impl) );
   ASSERT_EQ( impl->nonNegativeInteger_M.size(), 2 );
   ASSERT_EQ( impl->nonNegativeInteger_M.front(), nonNegativeInteger_MValue1 );
   ASSERT_EQ( impl->nonNegativeInteger_M.back(), nonNegativeInteger_MValue2 );
  
   //********************************************
   //nonPositiveInteger
   //********************************************
   const RuntimeModel::PropertyPtr nonPositiveInteger_M = component->findPropertyByName("_nonPositiveInteger_M");   
   ASSERT_TRUE( nonPositiveInteger_M );
   nonPositiveInteger_M->setValues(RuntimeModel::Property::Values());
   const string nonPositiveInteger_MValue1 = "-46";
   const string nonPositiveInteger_MValue2 = "-44";
   nonPositiveInteger_M->addValue(nonPositiveInteger_MValue1);
   nonPositiveInteger_M->addValue(nonPositiveInteger_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(nonPositiveInteger_M, impl) );
   ASSERT_EQ( impl->nonPositiveInteger_M.size(), 2 );
   ASSERT_EQ( impl->nonPositiveInteger_M.front(), nonPositiveInteger_MValue1 );
   ASSERT_EQ( impl->nonPositiveInteger_M.back(), nonPositiveInteger_MValue2 );
  
   //********************************************
   //normalizedString
   //********************************************
   const RuntimeModel::PropertyPtr normalizedString_M = component->findPropertyByName("_normalizedString_M");   
   ASSERT_TRUE( normalizedString_M );
   normalizedString_M->setValues(RuntimeModel::Property::Values());
   const string normalizedString_MValue1 = "normalizedString_MValue1";
   const string normalizedString_MValue2 = "normalizedString_MValue2";
   normalizedString_M->addValue(normalizedString_MValue1);
   normalizedString_M->addValue(normalizedString_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(normalizedString_M, impl) );
   ASSERT_EQ( impl->normalizedString_M.size(), 2 );
   ASSERT_EQ( impl->normalizedString_M.front(), normalizedString_MValue1 );
   ASSERT_EQ( impl->normalizedString_M.back(), normalizedString_MValue2 );
  
   //********************************************
   //NOTATION
   //********************************************
   const RuntimeModel::PropertyPtr NOTATION_M = component->findPropertyByName("_NOTATION_M");   
   ASSERT_TRUE( NOTATION_M );
   NOTATION_M->setValues(RuntimeModel::Property::Values());
   const string NOTATION_MValue1 = "NOTATION_MValue1";
   const string NOTATION_MValue2 = "NOTATION_MValue2";
   NOTATION_M->addValue(NOTATION_MValue1);
   NOTATION_M->addValue(NOTATION_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(NOTATION_M, impl) );
   ASSERT_EQ( impl->NOTATION_M.size(), 2 );
   ASSERT_EQ( impl->NOTATION_M.front(), NOTATION_MValue1 );
   ASSERT_EQ( impl->NOTATION_M.back(), NOTATION_MValue2 );
  
   //********************************************
   //positiveInteger
   //********************************************
   const RuntimeModel::PropertyPtr positiveInteger_M = component->findPropertyByName("_positiveInteger_M");   
   ASSERT_TRUE( positiveInteger_M );
   positiveInteger_M->setValues(RuntimeModel::Property::Values());
   const string positiveInteger_MValue1 = "23";
   const string positiveInteger_MValue2 = "24";
   positiveInteger_M->addValue(positiveInteger_MValue1);
   positiveInteger_M->addValue(positiveInteger_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(positiveInteger_M, impl) );
   ASSERT_EQ( impl->positiveInteger_M.size(), 2 );
   ASSERT_EQ( impl->positiveInteger_M.front(), positiveInteger_MValue1 );
   ASSERT_EQ( impl->positiveInteger_M.back(), positiveInteger_MValue2 );
  
   //********************************************
   //QName
   //********************************************
   const RuntimeModel::PropertyPtr QName_M = component->findPropertyByName("_QName_M");   
   ASSERT_TRUE( QName_M );
   QName_M->setValues(RuntimeModel::Property::Values());
   const string QName_MValue1 = "ns:QName_MValue1";
   const string QName_MValue2 = "ns:QName_MValue2";
   QName_M->addValue(QName_MValue1);
   QName_M->addValue(QName_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(QName_M, impl) );
   ASSERT_EQ( impl->QName_M.size(), 2 );
   ASSERT_EQ( impl->QName_M.front(), QName_MValue1 );
   ASSERT_EQ( impl->QName_M.back(), QName_MValue2 );
  
   //********************************************
   //short
   //********************************************
   const RuntimeModel::PropertyPtr short_M = component->findPropertyByName("_short_M");   
   ASSERT_TRUE( short_M );
   short_M->setValues(RuntimeModel::Property::Values());
   const int16_t short_MValue1 = -23000;
   const int16_t short_MValue2 = -22000;
   short_M->addValue(boost::lexical_cast<string>(short_MValue1));
   short_M->addValue(boost::lexical_cast<string>(short_MValue2));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(short_M, impl) );
   ASSERT_EQ( impl->short_M.size(), 2 );
   ASSERT_EQ( impl->short_M.front(), short_MValue1 );
   ASSERT_EQ( impl->short_M.back(), short_MValue2 );  

   //********************************************
   //string
   //********************************************
   const RuntimeModel::PropertyPtr string_M = component->findPropertyByName("_string_M");   
   ASSERT_TRUE( string_M );
   string_M->setValues(RuntimeModel::Property::Values());
   const string string_MValue1 = "string_MValue1";
   const string string_MValue2 = "string_MValue2";
   string_M->addValue(string_MValue1);
   string_M->addValue(string_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(string_M, impl) );
   ASSERT_EQ( impl->string_M.size(), 2 );
   ASSERT_EQ( impl->string_M.front(), string_MValue1 );
   ASSERT_EQ( impl->string_M.back(), string_MValue2 );
  
   //********************************************
   //time
   //********************************************
   const RuntimeModel::PropertyPtr time_M = component->findPropertyByName("_time_M");   
   ASSERT_TRUE( time_M );
   time_M->setValues(RuntimeModel::Property::Values());
   const string time_MValue1 = "23:39:00";
   const string time_MValue2 = "00:00:00";
   time_M->addValue(time_MValue1);
   time_M->addValue(time_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(time_M, impl) );
   ASSERT_EQ( impl->time_M.size(), 2 );
   ASSERT_EQ( impl->time_M.front(), time_MValue1 );
   ASSERT_EQ( impl->time_M.back(), time_MValue2 );
  
   //********************************************
   //token
   //********************************************
   const RuntimeModel::PropertyPtr token_M = component->findPropertyByName("_token_M");   
   ASSERT_TRUE( token_M );
   token_M->setValues(RuntimeModel::Property::Values());
   const string token_MValue1 = "token_MValue1";
   const string token_MValue2 = "token_MValue2";
   token_M->addValue(token_MValue1);
   token_M->addValue(token_MValue2);
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(token_M, impl) );
   ASSERT_EQ( impl->token_M.size(), 2 );
   ASSERT_EQ( impl->token_M.front(), token_MValue1 );
   ASSERT_EQ( impl->token_M.back(), token_MValue2 );
  
   //********************************************
   //unsignedByte
   //********************************************
   const RuntimeModel::PropertyPtr unsignedByte_M = component->findPropertyByName("_unsignedByte_M");   
   ASSERT_TRUE( unsignedByte_M );
   unsignedByte_M->setValues(RuntimeModel::Property::Values());
   const uint8_t unsignedByte_MValue1 = 255;
   const uint8_t unsignedByte_MValue2 = 254;
   unsignedByte_M->addValue(boost::lexical_cast<string>(static_cast<uint32_t>(unsignedByte_MValue1)));
   unsignedByte_M->addValue(boost::lexical_cast<string>(static_cast<uint32_t>(unsignedByte_MValue2)));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(unsignedByte_M, impl) );
   ASSERT_EQ( impl->unsignedByte_M.size(), 2 );
   ASSERT_EQ( impl->unsignedByte_M.front(), unsignedByte_MValue1 );
   ASSERT_EQ( impl->unsignedByte_M.back(), unsignedByte_MValue2 );
  
   //********************************************
   //unsignedInt
   //********************************************
   const RuntimeModel::PropertyPtr unsignedInt_M = component->findPropertyByName("_unsignedInt_M");   
   ASSERT_TRUE( unsignedInt_M );
   unsignedInt_M->setValues(RuntimeModel::Property::Values());
   const uint32_t unsignedInt_MValue1 = 29081985;
   const uint32_t unsignedInt_MValue2 = 29081986;
   unsignedInt_M->addValue(boost::lexical_cast<string>(unsignedInt_MValue1));
   unsignedInt_M->addValue(boost::lexical_cast<string>(unsignedInt_MValue2));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(unsignedInt_M, impl) );
   ASSERT_EQ( impl->unsignedInt_M.size(), 2 );
   ASSERT_EQ( impl->unsignedInt_M.front(), unsignedInt_MValue1 );
   ASSERT_EQ( impl->unsignedInt_M.back(), unsignedInt_MValue2 );
  
   //********************************************
   //unsignedLong
   //********************************************
   const RuntimeModel::PropertyPtr unsignedLong_M = component->findPropertyByName("_unsignedLong_M");   
   ASSERT_TRUE( unsignedLong_M );
   unsignedLong_M->setValues(RuntimeModel::Property::Values());
   const uint64_t unsignedLong_MValue1 = 0xABCDABCDABCDFFFF;
   const uint64_t unsignedLong_MValue2 = 0xABCDABCDABCDFFFD;
   unsignedLong_M->addValue(boost::lexical_cast<string>(unsignedLong_MValue1));
   unsignedLong_M->addValue(boost::lexical_cast<string>(unsignedLong_MValue2));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(unsignedLong_M, impl) );
   ASSERT_EQ( impl->unsignedLong_M.size(), 2 );
   ASSERT_EQ( impl->unsignedLong_M.front(), unsignedLong_MValue1 );
   ASSERT_EQ( impl->unsignedLong_M.back(), unsignedLong_MValue2 );
  
   //********************************************
   //unsignedShort
   //********************************************
   const RuntimeModel::PropertyPtr unsignedShort_M = component->findPropertyByName("_unsignedShort_M");   
   ASSERT_TRUE( unsignedShort_M );
   unsignedShort_M->setValues(RuntimeModel::Property::Values());
   const uint64_t unsignedShort_MValue1 = 23000;
   const uint64_t unsignedShort_MValue2 = 24000;
   unsignedShort_M->addValue(boost::lexical_cast<string>(unsignedShort_MValue1));
   unsignedShort_M->addValue(boost::lexical_cast<string>(unsignedShort_MValue2));
   ASSERT_NE( impl, static_cast<Trentino::Tests::Core::ComponentWithProperties*>(nullptr) );
   ASSERT_NO_THROW( componentPropertyManager->injectValues(unsignedShort_M, impl) );
   ASSERT_EQ( impl->unsignedShort_M.size(), 2 );
   ASSERT_EQ( impl->unsignedShort_M.front(), unsignedShort_MValue1 );
   ASSERT_EQ( impl->unsignedShort_M.back(), unsignedShort_MValue2 );   

   //delete the component implementation instance
   lifeCycleMethodManager.deleteInstance(component, impl);

   //undeploy the test contribution
   ASSERT_NO_THROW( app->contributionLoader()->remove(contribution) );
   //shutdown the runtime
   booter.shutdown(app); 
}



//*************************************************************************************************
//              TEST_P(ComponentPropertyManagerErrorsTest, testValueAssignmentErrors)
//*************************************************************************************************

//classComponentPropertyManagerErrorsTest
   //global operators
std::ostream& Trentino::Tests::Core::operator<<(
   std::ostream& os, const ComponentPropertyManagerErrorsTestParams& params)
{
   return os << "{componentURI='"   << params.componentURI
             << "', propertyName='"  << params.propertyName
             << "', attribute='"     << params.attribute
             << "', attributeValue='"<< params.attributeValue
             << ", expectedError="  << static_cast<int>(params.expectedError) << "}";
}

   //static member initialization
Trentino::RuntimeModel::ContributionPtr ComponentPropertyManagerErrorsTest::mContribution;
Trentino::Tests::Core::Booter::BootPtr ComponentPropertyManagerErrorsTest::mApp;
   //services
void ComponentPropertyManagerErrorsTest::SetUpTestCase()
{ 
   //disable logging
   Trentino::Utils::Logging::Logger::setup(
      Trentino::Utils::Logging::Logger::DisableAllLoggers, nullptr);
   
   //boot the runtime 
   RuntimeBootstrapper::RuntimeConfigurationConstPtr runtimeConfiguration = 
      boost::make_shared<Trentino::Core::Bootstrapping::RuntimeConfiguration>();
   Trentino::Tests::Core::Booter booter;
   mApp = booter.boot(runtimeConfiguration);

   //deploy the test contribution
   const string contributionPath = makeContrbutionPath("InvalidProperties");
   ASSERT_NO_THROW( mContribution = mApp->contributionLoader()->install(contributionPath, "BaseURI") );
   EXPECT_NO_THROW( mApp->contributionLoader()->deploy(mContribution) );

   //introduce artificial errors 
   //(that would pass the validation but cannot be correctly treated at runtime)
    const RuntimeModel::ComponentPtr component = 
      findComponentByURI(mContribution, "ComponentReferencesEmptyCompositeProperty");
    ASSERT_TRUE( component ); 

}

void ComponentPropertyManagerErrorsTest::TearDownTestCase()
{
   ASSERT_NO_THROW( mApp->contributionLoader()->remove(mContribution) );
   mContribution.reset();
   Trentino::Tests::Core::Booter booter;
   booter.shutdown(mApp);
   mApp.reset();
}  

static ComponentPropertyManagerErrorsTestParams assignmentErrorsValues[] = {
   {  
      "ComponentReferencesEmptyCompositeProperty",
      "PropertyWithUselesseDefaultValue",
      's', "$EmptyCompositeProperty",
      ComponentPropertyManager::NoPropertyValuesError
   },
   {  
      "ComponentReferencesEmptyPropertyFile",
      "PropertyWithUselesseDefaultValue",
      'f', "EmptyPropertyFile.xml",
      ComponentPropertyManager::PropertyFileIllFormedError
   },
   {  
      "ComponentReferencesIllFormedPropertyFile",
      "PropertyWithUselesseDefaultValue",
      'f', "IllFormedPropertyFile1.xml",
      ComponentPropertyManager::PropertyFileIllFormedError
   },
   {  
      "ComponentReferencesNonExistentPropertyFile",
      "PropertyWithUselesseDefaultValue",
      'f', "NonExistentPropertyFile",
      ComponentPropertyManager::PropertyFileReadingError
   },   
   {  
      "ComponentNoValueForPropertyWithoutDefaultValue",
      "OptionalPropertyWithNoDefaultValue",
      'v', "",
      ComponentPropertyManager::NoDefaultPropertyValuesError
   },
};

INSTANTIATE_TEST_CASE_P( //empty argument = nameless instantiation 
                       , ComponentPropertyManagerErrorsTest 
                       , ::testing::ValuesIn(assignmentErrorsValues));

TEST_P(ComponentPropertyManagerErrorsTest, testValueAssignmentErrors)
{
   //retrieve instance of ComponentImplementationManager
   Trentino::Utils::Pattern::StaticClass<ComponentPropertyManager> componentPropertyManager;
   ASSERT_TRUE(componentPropertyManager.hasReference());   
     
   const RuntimeModel::ComponentPtr component = 
      findComponentByURI(mContribution, GetParam().componentURI);
   ASSERT_TRUE( component );   

   const RuntimeModel::Properties::const_iterator it = 
      find_if( component->properties().begin()
               , component->properties().end() 
               , boost::bind(&RuntimeModel::Property::name, _1) == GetParam().propertyName);
                    
   ASSERT_NE( it, component->properties().end());
   const RuntimeModel::PropertyPtr property = *it;
   ASSERT_TRUE( property );   

   //introduce error
   //1) delete the property value assigned during contribution loading
   property->setValues(RuntimeModel::Property::Values());
   const SCAModel::PropertyValuePtr scaProperty = property->scaProperty();
   ASSERT_TRUE( scaProperty ); 
   //2) delete the value attribute in the SCAModel
   scaProperty->setValue("");
   //3) assign new value of the specified attribute
   switch(GetParam().attribute)
   {
      case 'v': scaProperty->setValue(GetParam().attributeValue.c_str()); break;
      case 's': scaProperty->setSource(GetParam().attributeValue.c_str()); break;
      case 'f': scaProperty->setFile(GetParam().attributeValue.c_str()); break;
      default: FAIL();
   }

   try
   {
      componentPropertyManager->assignValuesFromSCAModel(property);
      FAIL();
   }
   catch(Trentino::Core::Exception<ComponentPropertyManager::Error>& e)
   {
      ASSERT_EQ( e.data(), GetParam().expectedError );
   }
   catch(...)
   {
      FAIL();
   }   
}


//*************************************************************************************************
//              TEST_F(ComponentPropertyManagerErrorsTest, testValueInjectionErrors)
//*************************************************************************************************
TEST_F(ComponentPropertyManagerErrorsTest, testValueInjectionErrors)
{  
   const RuntimeModel::ComponentPtr component = 
      findComponentByURI(mContribution, "ComponentWithNoErrors");
   ASSERT_TRUE( component ); 

   const RuntimeModel::Properties::const_iterator it = 
      find_if( component->properties().begin()
               , component->properties().end() 
               , boost::bind(&RuntimeModel::Property::name, _1) == "IntProperty");

   ASSERT_NE( it, component->properties().end());
   const RuntimeModel::PropertyPtr intProperty = *it;
   ASSERT_TRUE( intProperty ); 

    //instantiate the implementation of our test component   
   Trentino::Core::CPPImplementationLifeCycleMethodManager lifeCycleMethodManager;
   void* const instance = lifeCycleMethodManager.newInstance(component);

   //retrieve instance of ComponentImplementationManager
   Trentino::Utils::Pattern::StaticClass<ComponentPropertyManager> componentPropertyManager;
   ASSERT_TRUE(componentPropertyManager.hasReference()); 

   intProperty->setValues(RuntimeModel::Property::Values());
   intProperty->addValue("abc");
   
   try
   {
      componentPropertyManager->injectValues(intProperty, instance);
      FAIL();
   }
   catch(Trentino::Core::Exception<ComponentPropertyManager::Error>& e)
   {
      ASSERT_EQ( e.data(), ComponentPropertyManager::PropertyValueCastError );
   }
   catch(...)
   {
      FAIL();
   } 

   intProperty->setValues(RuntimeModel::Property::Values());
   intProperty->addValue("1234124312431243124312");
   
   try
   {
      componentPropertyManager->injectValues(intProperty, instance);
      FAIL();
   }
   catch(Trentino::Core::Exception<ComponentPropertyManager::Error>& e)
   {
      ASSERT_EQ( e.data(), ComponentPropertyManager::PropertyValueCastError );
   }
   catch(...)
   {
      FAIL();
   } 

   intProperty->setValues(RuntimeModel::Property::Values());
   intProperty->addValue("");
   
   try
   {
      componentPropertyManager->injectValues(intProperty, instance);
      FAIL();
   }
   catch(Trentino::Core::Exception<ComponentPropertyManager::Error>& e)
   {
      ASSERT_EQ( e.data(), ComponentPropertyManager::PropertyValueCastError );
   }
   catch(...)
   {
      FAIL();
   } 

   const Trentino::Core::CPPImplementationLifeCycleMethodManager lifeCycleManager;
   lifeCycleManager.deleteInstance(component, instance);
}
