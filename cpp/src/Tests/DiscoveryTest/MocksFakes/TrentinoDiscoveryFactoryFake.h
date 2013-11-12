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

#ifndef TrentinoDiscoveryFactoryFakeH
#define TrentinoDiscoveryFactoryFakeH

//test
#include "gmock/gmock.h" 

// specific 
#include "../../../Runtime/Discovery/TrentinoDiscoveryFactory.h"

// test specific
#include "TrentinoDiscoveryMethodInterfaceFake.h"
#include "TrentinoDiscoveryMethodInterfaceUnsucceedingFake.h"

using namespace Trentino::Discovery;
using ::testing::_; 
using ::testing::Invoke; 

namespace Trentino{
namespace Tests{
namespace Discovery
{
      const std::string GetDiscoveryMethodInterfaceFuncName = "getDiscoveryMethodInterface";
      typedef DiscoveryMethodInterface* (TRENTINO_CDECL *getDiscoveryMethodInterfaceFunc)  ();

      typedef DiscoveryInterface* (*GetDiscoveryInterfaceFn)(void); 
      
      // no need to have it as a shared pointer since DiscoveryImpl is also converted to singleton
      //typedef boost::shared_ptr<DiscoveryInterface> (*GetDiscoveryInterfaceFn)(void); 
      //typedef boost::shared_ptr<DiscoveryInterface> DiscoveryInterfacePtr;
      //class declaration

   //**********************************************************************************************
   //                             DiscoveryFactoryFake
   //**********************************************************************************************
   //! \ingroup Tests::Discovery
   //! \brief Class faking the method interfaces 
   //! discovery dll
   //**********************************************************************************************
   class DiscoveryFactoryFake :public DiscoveryManagementInterface
   { 
      //additional
   public:
      enum FakeDiscoveryMethod
      {
         //! OpenSLP implementation of SLP protocol RFC  
         SLP,
         DUMMY_SUCCEEDING,
         DUMMY_UNSUCCEEDING
      };
      //construction
   public:
      //****************************************************************************************
      //                                DiscoveryFactory()
      //****************************************************************************************
      //! \brief Disallow construction.  
      //****************************************************************************************
      DiscoveryFactoryFake(); 

      //****************************************************************************************
      //                                !DiscoveryFactory()
      //****************************************************************************************
      //! \brief Disallow distuction.  
      //****************************************************************************************
      ~DiscoveryFactoryFake() 
      { 
      }

      //****************************************************************************************
      //                                DiscoveryFactory()
      //****************************************************************************************
      //! \brief Disallow copy construction.  
      //****************************************************************************************
      DiscoveryFactoryFake(const DiscoveryFactory &) 
      { 
      }

      //operators
   private:
      //****************************************************************************************
      //                                operator=()
      //****************************************************************************************
      //! \brief Disallow assignment
      //****************************************************************************************
      DiscoveryFactoryFake &operator=(const DiscoveryFactory &);
 
      //services
   public:
      //****************************************************************************************
      //                                GetDiscoveryManagementInterface
      //****************************************************************************************
      //! \brief Return a pointer to the ManagemenInterface 
      //****************************************************************************************
      static DiscoveryManagementInterface* getDiscoveryManagementInterface(DiscoveryMethod chosenDiscoveryMethod);
   
      static void setDiscoveryManagementMethod(FakeDiscoveryMethod fakemethod)
      {
         mFakeDiscoveryMethod = fakemethod;
      }

   private:
      
      // Discovery Framework Management Functions to be accessed via base class(DiscoveryManagementInterface)
      // (see documentation in DiscoveryManagementInterface)
      void start(bool isDA, int retryCount,int retryInterval, onDiscoveryStartCBPtr discoveryTaskCB);
      void stop(); 
      Trentino::Discovery::DiscoveryInterfacePtr getDiscoveryInterface();
  


      //void registerDiscoveryMethod(DiscoveryMethod discoveryMethod, GetDiscoveryInterfaceFn pfnCreate);
      

      //data members
   private:  
      //typedef map<DiscoveryMethod,GetDiscoveryInterfaceFn> FactoryMap;
      // typedef map<DiscoveryMethod,DiscoveryInterface*> FactoryMap;
      //FactoryMap m_FactoryMap;
     
      //GetDiscoveryInterfaceFn mDiscoveryInterface;
      
      //! Discovery interface wrapping the current discoverydll
      DiscoveryInterface* mDiscoveryInterface;

      const char* mDiscoveryMethodDllNames[1];

      //FAKE-ADD
      TrentinoDiscoveryMethodFake mDiscoveryMethodFake;

      DiscoveryMethodUnsucceedingFake mDiscoveryMethodUnsucceedingFake;

      static FakeDiscoveryMethod mFakeDiscoveryMethod;
 
   }; // class DiscoveryFactoryMock

    //**********************************************************************************************
   //                             DiscoveryFactoryMock
   //**********************************************************************************************
   //! \ingroup Test::Discovery
   //! \brief 
   //**********************************************************************************************
   class DiscoveryFactoryMock :public DiscoveryManagementInterface
   { 
  
   public:
      MOCK_METHOD4(start,void(bool,int,int,onDiscoveryStartCBPtr));
      MOCK_METHOD0(stop,void());
      MOCK_METHOD0(getDiscoveryInterface, Trentino::Discovery::DiscoveryInterfacePtr());
         
   }; // class DiscoveryFactoryMock



      //***************************************************************************
      // non singleton factory
      //**********************************************************************
   //**********************************************************************************************
   //                             FakeDiscoveryFactory2
   //**********************************************************************************************
   //! \ingroup Tests::Discovery
   //! \brief fake class to receive the delegated calls from the mock for start func
   //**********************************************************************************************
  
}
}
}

#endif //TrentinoDiscoveryFactoryFakeH