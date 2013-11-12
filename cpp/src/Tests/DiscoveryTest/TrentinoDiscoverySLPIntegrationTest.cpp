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
#include "TrentinoDiscoverySLPIntegrationTest.h"

//standard
#include <gtest/gtest.h>
#include <string>
#include <boost/thread.hpp>

//specific
#include "./../../Runtime/Discovery/TrentinoDiscoveryFactory.h"
#include "./../../Runtime/Discovery/TrentinoDiscoveryImpl.h"
#include "./../../Runtime/Discovery/TrentinoDiscoveryFoundService.h"
#include "./../../Runtime/SCAModel/TrentinoSCAModelMetadataStringAttribute.h"


//standard
#pragma warning(push)
#pragma warning(disable:4273)
#include "./../../Runtime/Discovery/TrentinoDiscoveryInterface.h"
#include "./../../Runtime/SCAModel/TrentinoSCAModelMetadata.h"
#pragma warning(pop)


using namespace Trentino::Discovery;
using ::testing::Return;
using namespace boost;
using namespace boost::this_thread;
using namespace std;

#include "./../../Utils/TrentinoUtilsLogging.h"

using namespace Trentino::Utils;
using namespace Trentino::Utils::Logging;

namespace Trentino{
namespace Tests{
namespace Discovery
{
   bool DiscoverySlpIntegrationTest::mIsCallBackTriggered =  false;
   string DiscoverySlpIntegrationTest::mCurrentRegistrationCode =  "";

   listFoundServices DiscoverySlpIntegrationTest::mFoundServicesRegFind;
   listFoundServices DiscoverySlpIntegrationTest::mFoundServicesMultipleReqFind;
   listFoundServices DiscoverySlpIntegrationTest::mFoundServicesFindSrvsWithAttr;
   
   listFoundServices DiscoverySlpIntegrationTest::mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchNoAtt;
   listFoundServices DiscoverySlpIntegrationTest::mFoundServices;
   listFoundServices DiscoverySlpIntegrationTest::mFoundServicesFindSrvsWithWrongAttributes;
   listFoundServices DiscoverySlpIntegrationTest::mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchAmatchingAtt;
   listFoundServices DiscoverySlpIntegrationTest::mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchUninterestingAtt;
  
   listFoundServices DiscoverySlpIntegrationTest::mFoundServicesFindSrvsWithMandatoryAttributes;
   //std::list< DiscoveryFoundService* > DiscoverySlpIntegrationTest::mFoundServicesFindSrvsWithMandatoryAttributes;
   //std::vector< DiscoveryFoundService* > DiscoverySlpIntegrationTest::mFoundServicesFindSrvsWithMandatoryAttributes;

   DiscoveryInterface* DiscoverySlpIntegrationTest::mDiscoveryInterface = nullptr;
   Trentino::Discovery::DiscoveryManagementInterface* mManagementInterfacePtr = nullptr;

    DiscoverySlpIntegrationTest::~DiscoverySlpIntegrationTest()
    {

    }

   void DiscoverySlpIntegrationTest::SetUp()
   {
      Logger::ConfigDesc config ={ "oleey.log", nullptr, nullptr };
      Logger::setup(Logger::SetupLogger, &config);

      mIsCallBackTriggered = false;
      mCurrentRegistrationCode.clear();
  
   }


   void DiscoverySlpIntegrationTest::callBackRegFind(int nID, bool f, std::string retVal)
   {
      nID;
      retVal;
      EXPECT_EQ(1,mFoundServicesRegFind.size());
      EXPECT_TRUE(f);

      if(mFoundServicesRegFind.size() == 0)
      {
         return;
      }
      //boost::shared_ptr<DiscoveryFoundService> foundService = mFoundServicesRegFind.front();

      size_t foundServiceCount = mFoundServicesRegFind.size();
      for(size_t i = 0; i < foundServiceCount; i++)
      {
         DiscoveryFoundService* foundService = mFoundServicesRegFind.front();
         delete foundService;
      }
      
      mFoundServicesRegFind.clear();
   }


   void DiscoverySlpIntegrationTest::CBFindSrvMultipleReg(int nID, bool f, std::string retVal)
   {
      nID;
      retVal;

      EXPECT_EQ(2,mFoundServicesMultipleReqFind.size());
      EXPECT_TRUE(f);
      size_t foundServiceCount = mFoundServicesMultipleReqFind.size();
      for(size_t i = 0; i < foundServiceCount; i++)
      {
         DiscoveryFoundService* foundService = mFoundServicesMultipleReqFind.front();
         mFoundServicesMultipleReqFind.pop_front();
         delete foundService;
      }
      mFoundServicesMultipleReqFind.clear();
   }
 
   void DiscoverySlpIntegrationTest::CBFindSrvMultipleReg2(int nID, bool f, std::string retVal)
   {
      nID;
      f;
      retVal;

      EXPECT_EQ(2,mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchNoAtt.size());
      EXPECT_TRUE(f);

      size_t foundServiceCount = mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchNoAtt.size();
      for(size_t i = 0; i < foundServiceCount; i++)
      {
         DiscoveryFoundService* foundService = mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchNoAtt.front();
         mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchNoAtt.pop_front();
         delete foundService;
      }
      mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchNoAtt.clear();

   }

   void DiscoverySlpIntegrationTest::CBFindSrvsWithMultipleAttr(int nID, bool f, std::string retVal)
   {
      nID;
      retVal;
      EXPECT_EQ(1, mFoundServicesFindSrvsWithAttr.size());
      EXPECT_TRUE(f);

      size_t foundServiceCount = mFoundServicesFindSrvsWithAttr.size();
      for(size_t i = 0; i < foundServiceCount; i++)
      {
         DiscoveryFoundService* foundService = mFoundServicesFindSrvsWithAttr.front();
         delete foundService;
      }
      mFoundServicesFindSrvsWithAttr.clear();
   }

   void DiscoverySlpIntegrationTest::CBFindSrvsWithOneAttrWithOneMandatoryAttr(int nID, bool f, std::string retVal)
   {
      nID;
      f;
      retVal;

      EXPECT_EQ(1,mFoundServicesFindSrvsWithMandatoryAttributes.size());
      EXPECT_TRUE(f);
      if(mFoundServicesFindSrvsWithMandatoryAttributes.size() == 0)
      {
         return;
      }
      //boost::shared_ptr<DiscoveryFoundService> foundService = mFoundServicesFindSrvsWithMandatoryAttributes.front();
      DiscoveryFoundService* foundService = mFoundServicesFindSrvsWithMandatoryAttributes.front();
      
      std::string serviceUr = foundService->getServiceUrl();

      const std::vector<MetadataStringAttributePtr>& vectorOfAttributes = foundService->mMetaDatasOfService->stringAttributesElements();
      std::string name = vectorOfAttributes[0]->name();
      std::string val =  vectorOfAttributes[0]->value();
      EXPECT_EQ(name, "_binding");
      
      //clean up
      size_t foundServiceCount = mFoundServicesFindSrvsWithMandatoryAttributes.size();
      for(size_t i = 0; i < foundServiceCount; i++)
      {
         DiscoveryFoundService* foundService = mFoundServicesFindSrvsWithMandatoryAttributes.front();
         delete foundService;
      }
      mFoundServicesFindSrvsWithMandatoryAttributes.clear();
   
      
   }
  // void DiscoverySlpIntegrationTest::VerifyClean()
  // {
  //    mFoundServicesFindSrvsWithMandatoryAttributes.clear();
  // }

   void DiscoverySlpIntegrationTest::CB_MultipleReqWithTheSameName_WithDifferentAttributes_searchAmatchingAtt(int nID, bool f, std::string retVal)
   {
      nID;
      f;
      retVal;
      EXPECT_EQ(1,mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchAmatchingAtt.size());
      EXPECT_TRUE(f);

      size_t foundServiceCount = mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchAmatchingAtt.size();
      for(size_t i = 0; i < foundServiceCount; i++)
      {
         DiscoveryFoundService* foundService = mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchAmatchingAtt.front();
         delete foundService;
      }
      mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchAmatchingAtt.clear();
   }

   void DiscoverySlpIntegrationTest::CB_MultipleReqWithTheSameName_WithDifferentAttributes_searchUninterestingAtt(int nID, bool f, std::string retVal)
   {
      nID;
      f;
      retVal;
      EXPECT_EQ(0, mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchUninterestingAtt.size());
      EXPECT_TRUE(f);
      size_t foundServiceCount = mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchUninterestingAtt.size();
      for(size_t i = 0; i < foundServiceCount; i++)
      {
         DiscoveryFoundService* foundService = mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchUninterestingAtt.front();
         delete foundService;
      }
      mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchUninterestingAtt.clear();
   }
  

   void DiscoverySlpIntegrationTest::CBStart(bool f, std::string retVal)
   {
      f;
      retVal;
   }

   void DiscoverySlpIntegrationTest::CBRegister(int nID, bool f, std::string retVal)
   {
      nID;
      f;
      retVal;
   }

   void DiscoverySlpIntegrationTest::CBRegisterDeregister(int nID, bool registerResult, std::string retVal)
   {
      nID;
      if( registerResult)
      {
         mDiscoveryInterface->deregisterService(retVal);
      }
   }

 	void DiscoverySlpIntegrationTest::CBFindSrvsWithWrongAttr(int nID, bool f, std::string retVal)
   {
      nID;
      f;
      retVal;
      EXPECT_FALSE(f);
      EXPECT_EQ(0, mFoundServicesFindSrvsWithWrongAttributes.size());
      mFoundServicesFindSrvsWithWrongAttributes.clear();
   }
   
   TEST_F(DiscoverySlpIntegrationTest, RegFind)
   {

       DiscoveryInterface *pDiscoveryInterface = mManagementInterfacePtr->getDiscoveryInterface();

       //ASSERT_NE(nullptr, pDiscoveryInterface);
       EXPECT_TRUE(pDiscoveryInterface != nullptr);

       MetadataSharedPtr serviceAttributes (new Metadata());
       
       pDiscoveryInterface->registerService("xyz", serviceAttributes, &CBRegister);

       pDiscoveryInterface->findService("xyz", serviceAttributes, mFoundServicesRegFind, &callBackRegFind);

       //serviceAttributes.reset();

   }

   TEST_F(DiscoverySlpIntegrationTest, MultipleReqFind)
   {
      DiscoveryInterface *pDiscoveryInterface = mManagementInterfacePtr->getDiscoveryInterface();

      ASSERT_NE(nullptr, pDiscoveryInterface);

      MetadataSharedPtr serviceAttributes (new Metadata());


      pDiscoveryInterface->registerService("xyzt", serviceAttributes, &CBRegister);
      pDiscoveryInterface->registerService("xyzt", serviceAttributes, &CBRegister);

      pDiscoveryInterface->findService("xyzt", serviceAttributes, mFoundServicesMultipleReqFind, &CBFindSrvMultipleReg); // expect 2

      boost::this_thread::sleep(boost::posix_time::millisec(4000));
      serviceAttributes.reset();
}


   TEST_F(DiscoverySlpIntegrationTest, FindSrvsWithAttr)
   {
      DiscoveryInterface *pDiscoveryInterface = mManagementInterfacePtr->getDiscoveryInterface();

      ASSERT_NE(nullptr, pDiscoveryInterface);
      MetadataSharedPtr serviceAttributes (new Metadata());

      MetadataStringAttribute* stringAttribute =  new MetadataStringAttribute();
      stringAttribute->setName("floor");
      stringAttribute->setValue("3");
      serviceAttributes->addStringAttributesElement(stringAttribute);

      MetadataStringAttribute* stringAttribute2 =  new MetadataStringAttribute();
      stringAttribute2->setName("color");
      stringAttribute2->setValue("red");
      serviceAttributes->addStringAttributesElement(stringAttribute2);

      pDiscoveryInterface->registerService("abc", serviceAttributes, &CBRegister);

      
      pDiscoveryInterface->findService("abc", serviceAttributes, mFoundServicesFindSrvsWithAttr, &CBFindSrvsWithMultipleAttr);

      //boost::this_thread::sleep(boost::posix_time::millisec(4000));
      serviceAttributes.reset();

   }
   
   TEST_F(DiscoverySlpIntegrationTest, FindSrvsWithMandatoryAttributes)
   {
      //mManagementInterfacePtr = DiscoveryFactory::getDiscoveryManagementInterface(DiscoveryFactory::SLP);
      //mManagementInterfacePtr->start(false, 3, 50, &CBStart);

      DiscoveryInterface *pDiscoveryInterface = mManagementInterfacePtr->getDiscoveryInterface();

      ASSERT_NE(nullptr, pDiscoveryInterface);
      MetadataSharedPtr serviceAttributes (new Metadata());

      MetadataStringAttribute* stringAttribute =  new MetadataStringAttribute();
      stringAttribute->setName("floor");
      stringAttribute->setValue("3");
      serviceAttributes->addStringAttributesElement(stringAttribute);

      MetadataStringAttribute* stringAttribute2 =  new MetadataStringAttribute();
      stringAttribute2->setName("color");
      stringAttribute2->setValue("red");
      serviceAttributes->addStringAttributesElement(stringAttribute2);


      MetadataStringAttribute* stringAttribute3 =  new MetadataStringAttribute();
      stringAttribute3->setName("_binding");
      stringAttribute3->setValue("here is the binding whatever URI");
      serviceAttributes->addStringAttributesElement(stringAttribute3);

      pDiscoveryInterface->registerService("zzz", serviceAttributes, &CBRegister);

      MetadataSharedPtr filterAttributes (new Metadata());

      MetadataStringAttribute* stringAttribute4 =  new MetadataStringAttribute();
      stringAttribute4->setName("floor");
      stringAttribute4->setValue("3");
      filterAttributes->addStringAttributesElement(stringAttribute4);

      pDiscoveryInterface->findService("zzz", filterAttributes, mFoundServicesFindSrvsWithMandatoryAttributes, &CBFindSrvsWithOneAttrWithOneMandatoryAttr);

      serviceAttributes.reset();
   }

   //Test below is used for manual testing of start and stopping of discovery layer with SLP
   //TEST_F(DiscoverySlpIntegrationTest, DISABLED_StartStopTest)
   //{
   //   //DiscoveryManagementInterface* mManagementInterfacePtr = DiscoveryFactory::getDiscoveryManagementInterface(DiscoveryFactory::SLP);

   //   //ASSERT_NE(nullptr, mManagementInterfacePtr);

   //  // mManagementInterfacePtr->start(false, 3, 50, &CBStart);

   //   mManagementInterfacePtr->stop();

   //   boost::this_thread::sleep(boost::posix_time::millisec(50000));

   //}
   
   TEST_F(DiscoverySlpIntegrationTest, RealFactoryRegisterFindDeregister)
   {
      mDiscoveryInterface = mManagementInterfacePtr->getDiscoveryInterface();

      ASSERT_NE(nullptr, mDiscoveryInterface);
      MetadataSharedPtr serviceAttributes (new Metadata());

      mDiscoveryInterface->registerService("yyy", serviceAttributes, &CBRegisterDeregister);

      //boost::this_thread::sleep(boost::posix_time::millisec(4000000));
      serviceAttributes.reset();
   }

   //error
    TEST_F(DiscoverySlpIntegrationTest, MultipleReqWithTheSameName_WithDifferentAttributes_searchNoAtt)
   {
      DiscoveryInterface *pDiscoveryInterface = mManagementInterfacePtr->getDiscoveryInterface();

      ASSERT_NE(nullptr, pDiscoveryInterface);

      MetadataSharedPtr serviceAttributes (new Metadata());

	  MetadataStringAttribute* stringAttribute =  new MetadataStringAttribute();
      stringAttribute->setName("floor");
      stringAttribute->setValue("3");
      serviceAttributes->addStringAttributesElement(stringAttribute);

      pDiscoveryInterface->registerService("ServiceA", serviceAttributes, &CBRegister);

	  MetadataSharedPtr serviceAttributes2 (new Metadata());

	  MetadataStringAttribute* stringAttribute2 =  new MetadataStringAttribute();
      stringAttribute2->setName("color");
      stringAttribute2->setValue("red");
      serviceAttributes2->addStringAttributesElement(stringAttribute2);

      pDiscoveryInterface->registerService("ServiceA", serviceAttributes2, &CBRegister);

	   MetadataSharedPtr serviceAttributes3 (new Metadata());
      pDiscoveryInterface->findService("ServiceA", serviceAttributes3, mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchNoAtt, &CBFindSrvMultipleReg2); // expect 2

      //boost::this_thread::sleep(boost::posix_time::millisec(4000000));
      serviceAttributes.reset();
	  serviceAttributes2.reset();
	  serviceAttributes3.reset();

   }

   TEST_F(DiscoverySlpIntegrationTest, MultipleReqWithTheSameName_WithDifferentAttributes_searchAmatchingAtt)
   {
      DiscoveryInterface *pDiscoveryInterface = mManagementInterfacePtr->getDiscoveryInterface();

      ASSERT_NE(nullptr, pDiscoveryInterface);

      MetadataSharedPtr serviceAttributes (new Metadata());

      MetadataStringAttribute* stringAttribute =  new MetadataStringAttribute();
      stringAttribute->setName("floor");
      stringAttribute->setValue("3");
      serviceAttributes->addStringAttributesElement(stringAttribute);

      pDiscoveryInterface->registerService("ServiceAB", serviceAttributes, &CBRegister);

      MetadataSharedPtr serviceAttributes2 (new Metadata());

      MetadataStringAttribute* stringAttribute2 =  new MetadataStringAttribute();
      stringAttribute2->setName("color");
      stringAttribute2->setValue("red");
      serviceAttributes2->addStringAttributesElement(stringAttribute2);

      pDiscoveryInterface->registerService("ServiceAB", serviceAttributes2, &CBRegister);

      pDiscoveryInterface->findService("ServiceAB", serviceAttributes2, mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchAmatchingAtt, &CB_MultipleReqWithTheSameName_WithDifferentAttributes_searchAmatchingAtt); // expect 1

      //boost::this_thread::sleep(boost::posix_time::millisec(4000000));
      serviceAttributes.reset();
      serviceAttributes2.reset();
   }

   TEST_F(DiscoverySlpIntegrationTest, MultipleReqWithTheSameName_WithDifferentAttributes_searchUninterestingAtt)
   {
      DiscoveryInterface *pDiscoveryInterface = mManagementInterfacePtr->getDiscoveryInterface();
      ASSERT_NE(nullptr, pDiscoveryInterface);

      MetadataSharedPtr serviceAttributes (new Metadata());
      MetadataStringAttribute* stringAttribute =  new MetadataStringAttribute();

      stringAttribute->setName("floor");

      stringAttribute->setValue("3");

      serviceAttributes->addStringAttributesElement(stringAttribute);
      pDiscoveryInterface->registerService("ServiceAT", serviceAttributes, &CBRegister);

      MetadataSharedPtr serviceAttributes2 (new Metadata());
      MetadataStringAttribute* stringAttribute2 =  new MetadataStringAttribute();

      stringAttribute2->setName("color");
      stringAttribute2->setValue("red");
      serviceAttributes2->addStringAttributesElement(stringAttribute2);

      pDiscoveryInterface->registerService("ServiceAT", serviceAttributes2, &CBRegister);

      MetadataSharedPtr serviceAttributes3 (new Metadata());

      MetadataStringAttribute* stringAttribute3 =  new MetadataStringAttribute();

      stringAttribute3->setName("color");
      stringAttribute3->setValue("yellow");
      serviceAttributes3->addStringAttributesElement(stringAttribute3);

      pDiscoveryInterface->findService("ServiceAT", serviceAttributes3, mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchUninterestingAtt, &CB_MultipleReqWithTheSameName_WithDifferentAttributes_searchUninterestingAtt); // expect 0

      //boost::this_thread::sleep(boost::posix_time::millisec(4000000));

      serviceAttributes.reset();
      serviceAttributes2.reset();
      serviceAttributes3.reset();

   }

   TEST_F(DiscoverySlpIntegrationTest, FindSrvsWithWrongAttributes)
   {
      DiscoveryInterface *pDiscoveryInterface = mManagementInterfacePtr->getDiscoveryInterface();

      ASSERT_NE(nullptr, pDiscoveryInterface);
      MetadataSharedPtr serviceAttributes (new Metadata());

      MetadataStringAttribute* stringAttribute =  new MetadataStringAttribute();
      stringAttribute->setName("floor");
      stringAttribute->setValue("3");
      serviceAttributes->addStringAttributesElement(stringAttribute);

      MetadataStringAttribute* stringAttribute2 =  new MetadataStringAttribute();
      stringAttribute2->setName("color");
      stringAttribute2->setValue("red");
      serviceAttributes->addStringAttributesElement(stringAttribute2);

      pDiscoveryInterface->registerService("zzz2", serviceAttributes, &CBRegister);

      MetadataSharedPtr filterAttributes (new Metadata());

      MetadataStringAttribute* stringAttribute4 =  new MetadataStringAttribute();
      stringAttribute4->setName("floor");
      stringAttribute4->setValue("4");
      filterAttributes->addStringAttributesElement(stringAttribute4);

      pDiscoveryInterface->findService("zzz2", filterAttributes, mFoundServicesFindSrvsWithWrongAttributes, &CBFindSrvsWithWrongAttr);

      //boost::this_thread::sleep(boost::posix_time::millisec(4000000));
      serviceAttributes.reset();
   }
   
} // namespace Discovery
} // namespace Tests
} // namespace Trentino