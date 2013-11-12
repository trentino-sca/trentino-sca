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
#include "TrentinoInvocationLocalDataExchangeInvocationTest.h"

//tests
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "TrentinoCoreMocks.h"
#include "TrentinoLocalCallDataExchangeServiceABImpl.h"

using namespace Trentino::Tests::LocalCallDataExchange;
using namespace Trentino::LocalCallDataExchange;
using namespace Trentino::Core::Tests;
using namespace Trentino::RuntimeModel::Tests;
using namespace Trentino::Gen::LocalCallDataExchangeGen;

using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using ::testing::An;
using ::testing::ReturnRef;

namespace {
   void setUpImplementation(   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceAImpl>& valA,
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceBImpl>& valB,const boost::shared_ptr<Trentino::Core::Tests::MockComponentImplementationManagerBase>& mockComponentImplementationManagerBase){
         Trentino::LocalCallDataExchange::ServiceAImpl* serviceAImpl = new Trentino::LocalCallDataExchange::ServiceAImpl();
         valA.reset(serviceAImpl);
         Trentino::LocalCallDataExchange::ServiceBImpl* serviceBImpl = new Trentino::LocalCallDataExchange::ServiceBImpl();
          valB.reset(serviceBImpl);
         serviceAImpl->setServiceB(serviceBImpl);
         MockComponentImplementationManagerBase* componentImplementationManager = mockComponentImplementationManagerBase.get();
         ON_CALL(*componentImplementationManager,getInstance(An<const Trentino::RuntimeModel::ServiceBasePtr&>()))
            .WillByDefault(Return((void *)serviceAImpl));
      }
   }

TEST_F(LocalDataExchangeInvocationTest, method_with_two_parameters_passed_by_value){
   ClassA a;
   ClassB b;
   a.a = 2;
   std::string val("123");
   b.elems.push_back(val);

   std::string val2("321");
   b.elems.push_back(val2);
   b.aObject.b =1;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceAImpl> valA;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceBImpl>valB;
   setUpImplementation(valA,valB,mMockComponentImplementationManagerBase);
  ClassC c = mServiceA->method_with_two_parameters_passed_by_value(a,b);
  ASSERT_TRUE(c.x == std::string("OK"));
   }

TEST_F(LocalDataExchangeInvocationTest, method_with_two_parameters_first_by_value_second_by_reference){
   ClassA a;
   ClassB b;
   a.a = 2;
   std::string val("123");
   b.elems.push_back(val);

   std::string val2("321");
   b.elems.push_back(val2);
   b.aObject.b =1;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceAImpl> valA;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceBImpl>valB;
   setUpImplementation(valA,valB,mMockComponentImplementationManagerBase);
   ClassC c = mServiceA->method_with_two_parameters_first_by_value_second_by_reference(a,b);
   ASSERT_TRUE(c.x == std::string("OK"));
   }

TEST_F(LocalDataExchangeInvocationTest,method_with_two_parameters_first_by_const_value_second_by_reference){
   ClassA a;
   ClassB b;
   a.a = 2;
   std::string val("123");
   b.elems.push_back(val);

   std::string val2("321");
   b.elems.push_back(val2);
   b.aObject.b =1;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceAImpl> valA;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceBImpl>valB;
   setUpImplementation(valA,valB,mMockComponentImplementationManagerBase);
   ClassC c = mServiceA->method_with_two_parameters_first_by_const_value_second_by_reference(a,b);
   ASSERT_TRUE(c.x == std::string("OK"));
   }

TEST_F(LocalDataExchangeInvocationTest,method_with_two_parameters_first_by_value_second_const_reference){
   ClassA a;
   ClassB b;
   a.a = 2;
   std::string val("123");
   b.elems.push_back(val);

   std::string val2("321");
   b.elems.push_back(val2);
   b.aObject.b =1;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceAImpl> valA;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceBImpl>valB;
   setUpImplementation(valA,valB,mMockComponentImplementationManagerBase);
   ClassC c = mServiceA->method_with_two_parameters_first_by_value_second_const_reference(a,b);
   ASSERT_TRUE(c.x == std::string("OK"));
   }

TEST_F(LocalDataExchangeInvocationTest,method_with_two_arguments_return_const_value){
   ClassA a;
   ClassB b;
   a.a = 2;
   std::string val("123");
   b.elems.push_back(val);

   std::string val2("321");
   b.elems.push_back(val2);
   b.aObject.b =1;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceAImpl> valA;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceBImpl>valB;
   setUpImplementation(valA,valB,mMockComponentImplementationManagerBase);
  const ClassC c = mServiceA->method_with_two_arguments_return_const_value(a,b);
   ASSERT_TRUE(c.x == std::string("OK"));
   }


TEST_F(LocalDataExchangeInvocationTest,method_with_one_value_return_a_const_Reference){
   ClassB b;
   std::string val("123");
   b.elems.push_back(val);

   std::string val2("321");
   b.elems.push_back(val2);
   b.aObject.b =1;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceAImpl> valA;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceBImpl>valB;
   setUpImplementation(valA,valB,mMockComponentImplementationManagerBase);
   const ClassC& c = mServiceA->method_with_one_value_return_a_const_Reference(b);
   ASSERT_TRUE(c.x == std::string("OK"));
   }

TEST_F(LocalDataExchangeInvocationTest,method_has_many_value_or_const_parameters){
   ClassA a;
   ClassB b;
   a.a = 2;
   std::string val("123");
   b.elems.push_back(val);

   std::string val2("321");
   b.elems.push_back(val2);
   b.aObject.b =1;
   ClassA a2 =a;
   a2.a =1;
   ClassC c;
   c.x=std::string("OK");
   c.a =1;
   ClassB b2;
   b2.aObject.b =2;

   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceAImpl> valA;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceBImpl>valB;
   setUpImplementation(valA,valB,mMockComponentImplementationManagerBase);
   const ClassC& cRes = mServiceA->method_has_many_value_or_const_parameters(a,b,c,a2,b2);
   ASSERT_TRUE(cRes.x == std::string("OK"));
   }

TEST_F(LocalDataExchangeInvocationTest,method_has_a_pointer_and_a_value_return_a_pointer){
   ClassA a;
   ClassB b;
   a.a = 2;
   std::string val("123");
   b.elems.push_back(val);

   std::string val2("321");
   b.elems.push_back(val2);
   b.aObject.b =1;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceAImpl> valA;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceBImpl>valB;
   setUpImplementation(valA,valB,mMockComponentImplementationManagerBase);
   ClassC* c = mServiceA->method_has_a_pointer_and_a_value_return_a_pointer(&a,b);
   ASSERT_TRUE(c->x == std::string("OK"));
   }

TEST_F(LocalDataExchangeInvocationTest,method_has_two_const_pointers_return_a_pointer){
   ClassA a;
   ClassB b;
   a.a = 2;
   std::string val("123");
   b.elems.push_back(val);

   std::string val2("321");
   b.elems.push_back(val2);
   b.aObject.b =1;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceAImpl> valA;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceBImpl>valB;
   setUpImplementation(valA,valB,mMockComponentImplementationManagerBase);
   ClassC* c = mServiceA->method_has_two_const_pointers_return_a_pointer(&a,&b);
   ASSERT_TRUE(c->x == std::string("OK"));
   }


TEST_F(LocalDataExchangeInvocationTest,method_has_a_template_class_as_argument){
   std::vector<Trentino::LocalCallDataExchange::ClassA> valuesOfA;
   ClassA a;
   a.a = 2;
   valuesOfA.push_back(a);
   ClassA a2;
   a2.a =1;
   valuesOfA.push_back(a2);

   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceAImpl> valA;
   boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceBImpl>valB;
   setUpImplementation(valA,valB,mMockComponentImplementationManagerBase);
   ClassC* c = mServiceA->method_has_a_template_class_as_argument(valuesOfA);
   ASSERT_TRUE(c->x == std::string("OK"));
   }

void Trentino::Tests::LocalCallDataExchange::LocalDataExchangeInvocationTest::SetUp()
   {

   //create mock service
   Trentino::RuntimeModel::Tests::MockServiceBase* service = new Trentino::RuntimeModel::Tests::MockServiceBase();
   Trentino_LocalCallDataExchange_ServiceAWrapper* wrapper = new Trentino_LocalCallDataExchange_ServiceAWrapper();
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

   //setup ServiceA.
   Trentino_LocalCallDataExchange_ServiceAProxy* serviceA = new Trentino_LocalCallDataExchange_ServiceAProxy(wireObj);
   mServiceA.reset(serviceA);
   }
