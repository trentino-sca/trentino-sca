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

#ifndef TrentinoDiscoverySlpIntegrationTestH
#define TrentinoDiscoverySlpIntegrationTestH

//standard
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

//specific
#include "./../../Runtime/Discovery/TrentinoDiscoveryFactory.h"
#include "./MocksFakes/TrentinoDiscoveryMethodInterfaceUnsucceedingFake.h"
#include "./../../Runtime/Discovery/TrentinoDiscoveryFoundService.h"
#include "./../../Runtime/Discovery/TrentinoDiscovery.h"

using namespace Trentino::Discovery;

namespace Trentino{
namespace Tests{
namespace Discovery
{
   //class declaration
   class DiscoverySlpIntegrationTest : public ::testing::Test
   {
      //additional
   public:
      typedef boost::shared_ptr<Metadata> MetadataSharedPtr;
      ~DiscoverySlpIntegrationTest();
   protected:
      void SetUp();

      static void callBackRegFind(int nID, bool f, std::string retVal);
	  //new begin
      static void CBFindSrvMultipleReg(int nID, bool f, std::string retVal);
      static void CBFindSrvMultipleReg2(int nID, bool f, std::string retVal);
      
	  static void CB_MultipleReqWithTheSameName_WithDifferentAttributes_searchAmatchingAtt(int nID, bool f, std::string retVal);
	  static void CB_MultipleReqWithTheSameName_WithDifferentAttributes_searchUninterestingAtt(int nID, bool f, std::string retVal);
	  //new end
      static void CBFindSrvsWithMultipleAttr(int nID, bool f, std::string retVal);
      static void CBFindSrvsWithOneAttrWithOneMandatoryAttr(int nID, bool f, std::string retVal);
      static void CBFindSrvsWithWrongAttr(int nID, bool f, std::string retVal);
      
      static void CBRegister(int nID, bool f, std::string retVal);
      static void CBRegisterDeregister(int nID, bool f, std::string retVal);
      
      static void CBStart(bool f, std::string retVal);

      static void VerifyClean();
   protected:
      static bool mIsCallBackTriggered;
      
      static listFoundServices mFoundServicesRegFind;
      static listFoundServices mFoundServicesMultipleReqFind;
      static listFoundServices mFoundServicesFindSrvsWithAttr;

      static listFoundServices mFoundServicesFindSrvsWithMandatoryAttributes;
      //static std::list< DiscoveryFoundService* > DiscoverySlpIntegrationTest::mFoundServicesFindSrvsWithMandatoryAttributes;
      //static std::vector< DiscoveryFoundService* > mFoundServicesFindSrvsWithMandatoryAttributes;

      static listFoundServices mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchNoAtt;
      static listFoundServices mFoundServices;
      static listFoundServices mFoundServicesFindSrvsWithWrongAttributes;
      static listFoundServices mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchAmatchingAtt;
      static listFoundServices mFoundServicesMultipleReqWithTheSameName_WithDifferentAttributes_searchUninterestingAtt;

      static std::string mCurrentRegistrationCode;

      static DiscoveryInterface *mDiscoveryInterface;
     
      //Trentino::Discovery::DiscoveryManagementInterface* mManagementInterfacePtr;
   }; //class DiscoverySlpIntegrationTest

} //namespace Discovery
} //namespace Tests
} //namespace Trentino


#endif //TrentinoDiscoverySlpIntegrationTestH