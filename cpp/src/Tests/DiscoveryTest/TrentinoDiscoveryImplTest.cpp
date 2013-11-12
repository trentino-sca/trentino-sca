//// **********************************************************************************
//// Trentino - A C++ based lightweight, non-invasive SCA runtime.
//// Copyright (C) Siemens AG, 2012
//// All Rights Reserved
//// http://trentino.sourceforge.net/
////
//// This library is free software; you can redistribute it and/or
//// modify it under the terms of the GNU Lesser General Public
//// License as published by the Free Software Foundation; either
//// version 2.1 of the License, or (at your option) any later version.
////
//// This library is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//// Lesser General Public License for more details.
////
//// You should have received a copy of the GNU Lesser General Public
//// License along with this library; if not, write to the Free Software
//// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//// **********************************************************************************
//
////header
//#include "TrentinoDiscoveryImplTest.h"
////standard
//#include <gtest/gtest.h>
//#include <string>
//#include <boost/thread.hpp>
//
////specific
//#include "./../../Runtime/Discovery/TrentinoDiscoveryFactory.h"
//#include "./../../Runtime/Discovery/TrentinoDiscoveryImpl.h"
//#include "./../../Runtime/SCAModel/TrentinoSCAModelMetadataStringAttribute.h"
//
//
////standard
//#pragma warning(push)
//#pragma warning(disable:4273)
//#include "./../../Runtime/Discovery/TrentinoDiscoveryInterface.h"
//#include "./../../Runtime/SCAModel/TrentinoSCAModelMetadata.h"
//#pragma warning(pop)
//
//
////test
//#include "./MocksFakes/TrentinoDiscoveryFactoryFake.h"
//
//
//
//using namespace Trentino::Discovery;
//using ::testing::Return;
//using namespace boost;
//using namespace boost::this_thread;
//using namespace std;
//
//namespace Trentino{
//namespace Tests{
//namespace Discovery
//{
//   
//   bool DiscoveryFrameworkTest::mIsCallBackTriggered =  false;
//   string DiscoveryFrameworkTest::mCurrentRegistrationCode =  "";
//   listFoundServices DiscoveryFrameworkTest::mFoundServices;
//   DiscoveryInterface* DiscoveryFrameworkTest::mDiscoveryInterface = nullptr;
//
//   void DiscoveryFrameworkTest::SetUp()
//   {
//      mIsCallBackTriggered = false;
//      mFoundServices.clear();
//      mCurrentRegistrationCode.clear();
//   }
//
//   void DiscoveryFrameworkTest::callBack(int nID, bool f, std::string retVal)
//   {
//      nID;
//      f;
//      retVal;
//      //TODO write the asserts here
//   }
//
//   void DiscoveryFrameworkTest::CBStart(bool f, std::string retVal)
//   {
//      f;
//      retVal;
//   }
//
//   void DiscoveryFrameworkTest::CBRegister(int nID, bool f, std::string retVal)
//   {
//      nID;
//      f;
//      retVal;
//      //mIsCallBackTriggered = true;
//   }
//
//   TEST_F(DiscoveryFrameworkTest, DISABLED_DiscoveryInterfaceCreate)
//   {
//      //DiscoveryManagementInterface* managementInterfacePtr = DiscoveryFactory::getDiscoveryManagementInterface(DiscoveryFactory::SLP);
//      //managementInterfacePtr->start(false, 3, 50, &callBack);
//      //DiscoveryInterface *pDiscoveryInterface = managementInterfacePtr->getDiscoveryInterface();
//      //pDiscoveryInterface;
//   }
//
//      
//   TEST_F(DiscoveryFrameworkTest, DISABLED_TestWithMockDiscoveryFactory2)
//   {
//      MockDiscoveryFactory2 mockDiscoveryFactory;
//      mockDiscoveryFactory.DelegateToFake();
//
//      DiscoveryManagementInterface* managementInterfacePtr = mockDiscoveryFactory.getDiscoveryManagementInterface(DiscoveryFactory::SLP);
//      //internally fake factory class starts the fake method interface
//      managementInterfacePtr->start(false, 3, 50, &CBStart);  
//
//   }
//
//   TEST_F(DiscoveryFrameworkTest, DISABLED_NormalSequenceToFollowWithFakeFactory)
//   {
//       DiscoveryManagementInterface* managementInterfacePtr = DiscoveryFactoryFake::getDiscoveryManagementInterface(DiscoveryFactory::SLP);
//       DiscoveryFactoryFake::setDiscoveryManagementMethod(DiscoveryFactoryFake::DUMMY_SUCCEEDING);
//       //ASSERT_NE(nullptr, managementInterfacePtr);
//       EXPECT_TRUE(managementInterfacePtr != nullptr);
//
//       //internally fake factory class starts the fake method interface
//       managementInterfacePtr->start(false, 3, 50, &CBStart);
//
//       // Asserts checing for triggereing of callback does not make sense 
//       // since they will be triggered from a seperate thread
//       // ASSERT_TRUE(mIsCallBackTriggered);
//       //mIsCallBackTriggered =  false;
//       
//       DiscoveryInterface *pDiscoveryInterface = managementInterfacePtr->getDiscoveryInterface();
//
//       //ASSERT_NE(nullptr, pDiscoveryInterface);
//       EXPECT_TRUE(pDiscoveryInterface != nullptr);
//
//       MetadataSharedPtr serviceAttributes (new Metadata());
//
//       
//       pDiscoveryInterface->registerService("xyz", serviceAttributes, &CBRegister);
//
//       pDiscoveryInterface->findService("xyz", serviceAttributes, mFoundServices, &callBack);
//
//       serviceAttributes.reset();
//
//   }
//
//   TEST_F(DiscoveryFrameworkTest, DISABLED_WithUnsucceedingMethodInterface)
//   {
//      DiscoveryManagementInterface* managementInterfacePtr = DiscoveryFactoryFake::getDiscoveryManagementInterface(DiscoveryFactory::SLP);
//      DiscoveryFactoryFake::setDiscoveryManagementMethod(DiscoveryFactoryFake::DUMMY_UNSUCCEEDING);
//      //ASSERT_NE(nullptr, managementInterfacePtr);
//      EXPECT_TRUE(managementInterfacePtr != nullptr);
//
//      //internally fake factory class starts the fake method interface
//      managementInterfacePtr->start(false, 3, 50, &CBStart);
//
//      boost::this_thread::sleep(boost::posix_time::millisec(4000));
//
//      managementInterfacePtr->stop();
//
//   }
//   
//
//  
//} // namespace Discovery
//} // namespace Tests
//} // namespace Trentino