// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2012 by Siemens AG. All rights reserved.
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
#include "TrentinoInvocationBasicCalculatorReturnVoidTest.h"

//tests
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "TrentinoCoreMocks.h"


using namespace Trentino::Tests::BasicCalculatorReturnVoid;
using namespace Trentino::Example::BasicCalculatorReturnVoid;
using namespace Trentino::Core::Tests;
using namespace Trentino::RuntimeModel::Tests;
using namespace Trentino::Gen::BasicCalculatorReturnVoidGen;

using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using ::testing::An;
using ::testing::ReturnRef;


namespace {
   void setUpImplementation(   boost::shared_ptr<Trentino::Example::BasicCalculatorReturnVoid::CalculatorImpl>& valA,
      const boost::shared_ptr<Trentino::Core::Tests::MockComponentImplementationManagerBase>& mockComponentImplementationManagerBase){
         Trentino::Example::BasicCalculatorReturnVoid::CalculatorImpl* serviceAImpl = new Trentino::Example::BasicCalculatorReturnVoid::CalculatorImpl();
         valA.reset(serviceAImpl);
         MockComponentImplementationManagerBase* componentImplementationManager = mockComponentImplementationManagerBase.get();
         ON_CALL(*componentImplementationManager,getInstance(An<const Trentino::RuntimeModel::ServiceBasePtr&>()))
            .WillByDefault(Return((void *)serviceAImpl));
      }
   }
TEST_F(BasicCalculatorReturnVoidInvocationTest, call_add_no_exception){
    Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
    invocationData->setTargetService(mServicePtr);
    int a =1;
    int b = 2;
    invocationData->setOperation("add");

    Trentino::Invocation::InvocationData::Parameters params;
    params.reserve(2);
    //here4
    params.push_back(&a);

    //here4
    params.push_back(&b);

    invocationData->setParameters(params);
     boost::shared_ptr<Trentino::Example::BasicCalculatorReturnVoid::CalculatorImpl> valA;
     setUpImplementation(valA,mMockComponentImplementationManagerBase);
    ASSERT_NO_THROW(mInvoker->invoke(invocationData,mInvocationContext));
   }


void Trentino::Tests::BasicCalculatorReturnVoid::BasicCalculatorReturnVoidInvocationTest::SetUp()
   {
   //create mock service
   Trentino::RuntimeModel::Tests::MockServiceBase* service = new Trentino::RuntimeModel::Tests::MockServiceBase();
   Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper* wrapper = new Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper();
   mServiceWrapper.reset(wrapper);
   ON_CALL(*service,serviceInvocationWrapper())
      .WillByDefault(ReturnRef(mServiceWrapper));

   mServicePtr.reset(service);
   mServiceWeakPtr = mServicePtr;
   //create mock reference
   Trentino::RuntimeModel::Tests::MockReferenceBase* reference = new Trentino::RuntimeModel::Tests::MockReferenceBase();
   mReferencePtr.reset(reference);
   mReferenceWeakPtr = mReferencePtr;
   //create Mock Component implementation manager


   //create invoker and invocation context
   mInvocationContext =    boost::make_shared<Trentino::Invocation::InvocationContext>();
   Trentino::Invocation::Invoker* invoker = new Trentino::Invocation::Invoker();
   MockComponentImplementationManagerBase* componentImplementationManager = new MockComponentImplementationManagerBase();
   mMockComponentImplementationManagerBase.reset(componentImplementationManager);
   invoker->setComponentImplementationManager(mMockComponentImplementationManagerBase);
   mInvoker.reset(invoker);
   mInvocationContext->setCurrentInvoker(mInvoker);

   //create wire from reference to service
   MockWireBase* wireObj = new MockWireBase();
   ON_CALL(*wireObj,reference())
      .WillByDefault(Return(mReferenceWeakPtr));

   ON_CALL(*wireObj,service())
      .WillByDefault(Return(mServiceWeakPtr));

   ON_CALL(*wireObj,invocationContext())
      .WillByDefault(Return(mInvocationContext));

   mWire.reset(wireObj);
   }
