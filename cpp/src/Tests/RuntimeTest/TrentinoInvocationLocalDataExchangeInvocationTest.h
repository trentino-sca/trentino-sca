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

#ifndef TrentinoInvocationLocalDataExchangeInvocationTestH
#define TrentinoInvocationLocalDataExchangeInvocationTestH

//standard
#include <boost/shared_ptr.hpp>

//specific
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "TrentinoLocalCallDataExchangeServiceAB.h"
#include "../ProxiesAndWrappers/LocalCallDataExchangeGen_Trentino_LocalCallDataExchange_TrentinoGenProxiesWrappers.h"
#include "TrentinoRuntimeModelMocks.h"
#include <Runtime/RuntimeModel/TrentinoRuntimeModelWireable.h>
#include "boost/smart_ptr/make_shared.hpp"
#include <Runtime/Invocation/TrentinoInvocationInvocationContext.h>
#include "Runtime/Invocation/TrentinoInvocationInvoker.h"
#include "TrentinoCoreMocks.h"
#include "Runtime/Invocation/TrentinoInvocationServiceInvocationWrapperBase.h"


namespace Trentino{
namespace Tests{
namespace LocalCallDataExchange
{

   class LocalDataExchangeInvocationTest:  public ::testing::Test
   {
      //service
   protected:
   void SetUp();
   void TearDown(){}
   public:
     boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceA> mServiceA;
     boost::shared_ptr<Trentino::LocalCallDataExchange::ServiceB> mServiceB;
     Trentino::RuntimeModel::WirePtr mWire;
     Trentino::Invocation::InvokerPtr mInvoker ;
     Trentino::Invocation::InvocationContextPtr mInvocationContext;
     boost::shared_ptr<Trentino::Core::Tests::MockComponentImplementationManagerBase> mMockComponentImplementationManagerBase;
     void * mCurrentInstance;
     Trentino::RuntimeModel::ReferenceBasePtr mReferencePtr;
     Trentino::RuntimeModel::ServiceBasePtr mServicePtr;
     Trentino::RuntimeModel::ReferenceBaseWeakPtr mReferenceWeakPtr;
     Trentino::RuntimeModel::ServiceBaseWeakPtr mServiceWeakPtr;
     Trentino::Invocation::ServiceInvocationWrapperBasePtr mServiceWrapper;
   };//class LocalDataExchangeInvocation

} // namespace LocalDataExchange
} // namespace Tests
} // namespace Trentino

#endif TrentinoInvocationLocalDataExchangeInvocationTestH
