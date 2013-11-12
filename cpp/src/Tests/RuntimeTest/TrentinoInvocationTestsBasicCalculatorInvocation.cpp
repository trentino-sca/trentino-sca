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

//specific
#include "../TrentinoTestsEnvironmentInfo.h"
#include "../../Runtime/Invocation/TrentinoInvocationInvoker.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModel.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../../Utils/TrentinoUtilsPatternStaticClass.h"
#include "../../Runtime/Invocation/TrentinoInvocationInvocationContext.h"
#include "../../Runtime/Invocation/TrentinoInvocationInvocationData.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelService.h"
#include "../../Runtime/Invocation/TrentinoInvocationInvokerBase.h"
#include "../../Runtime/Core/TrentinoCoreComponentImplementationManager.h"
#include "../../Runtime/Core/TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#ifdef WIN32
   #include <windows.h>
#endif

//header
#include "TrentinoInvocationTestsBasicCalculatorInvocation.h"

using namespace Trentino::RuntimeModel;
using namespace Trentino::Invocation;
using namespace Trentino::Invocation;
using namespace Trentino::Tests::BasicCalculator;
using namespace Trentino::Core::Bootstrapping;
using Trentino::Utils::Pattern::StaticClass;
using Trentino::Utils::Pattern::FullImplCTorDTor;
namespace RuntimeModel = Trentino::RuntimeModel;



namespace 
{
	Trentino::Invocation::InvocationContextPtr createBasicCalculatorContext ()
	{
		return InvocationContextPtr( new InvocationContext());
	}

   RuntimeModel::ContributionPtr createRuntimeContribution()
   {
      StaticClass<Trentino::Core::Runtime> runtime;
      const std::string contributionPath = 
         Trentino::Tests::EnvironmentInfo::OutputPath + "/BasicCalculatorGen";
      
      const std::string contributionBaseURI = "BaseURI";
      const Trentino::ManagementInterface::ErrorMessage rslt = 
         runtime->managementInterface().install(contributionPath, contributionBaseURI);
      assert(rslt.empty() == true);

      return runtime->findContribution(contributionBaseURI);
   }

	//creates a _complete_ sca and runtime model but returns only one service
   RuntimeModel::ServiceBasePtr createBasicCalculatorRuntimeModel(Trentino::RuntimeModel::CompositePtr& dummyComposite)
	{
      const RuntimeModel::ComponentPtr component = 
         dummyComposite->findComponentByName("CalculatorComponent");
      assert(component);

      //!\todo dangerous assumption: the first service is the right one
      return component->services().front();
	}


	Trentino::Invocation::InvocationDataPtr createSubBasicCalculatorInvocationData ()
	{
		return InvocationDataPtr(new InvocationData());
	}

   void destroyAddBasicCalculatorInvocationData (Trentino::Invocation::InvocationDataPtr& invocationData)
   {
      //the generated code knows the right data type
      int* param1 = static_cast<int*>(invocationData->parameters()[0]);
      int* param2 = static_cast<int*>(invocationData->parameters()[1]);
      delete param1;
      delete param2;
      int* response = static_cast<int*>(invocationData->response());
      delete response;
   }

   void destroyDivBasicCalculatorInvocationData (Trentino::Invocation::InvocationDataPtr& invocationData)
   {
      //the generated code knows the right data type
      int* param1 = static_cast<int*>(invocationData->parameters()[0]);
      int* param2 = static_cast<int*>(invocationData->parameters()[1]);
      delete param1;
      delete param2;
      int* response = static_cast<int*>(invocationData->response());
      delete response;
   }

   void destroyDiv2BasicCalculatorInvocationData (Trentino::Invocation::InvocationDataPtr& invocationData)
   {
      //the generated code knows the right data type
      int* param1 = static_cast<int*>(invocationData->parameters()[0]);
      int* param2 = static_cast<int*>(invocationData->parameters()[1]);
      delete param1;
      delete param2;
      int* response = static_cast<int*>(invocationData->response());
      delete response;
   }

	Trentino::Invocation::InvocationDataPtr createAddBasicCalculatorInvocationData (Trentino::RuntimeModel::CompositePtr& dummyComposite)
	{      
      InvocationDataPtr invocationData(new InvocationData());
      const RuntimeModel::ServiceBasePtr service = createBasicCalculatorRuntimeModel(dummyComposite);
      invocationData->setTargetService(service); 
      invocationData->setOperation("add");
      
      //the generated code knows the right data type
      int* const param1 = new int(3);
      int* const param2 = new int(4);
      InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(param1);
      params.push_back(param2);
      invocationData->setParameters(params);
      
      return invocationData;
	}


	Trentino::Invocation::InvocationDataPtr createDivBasicCalculatorInvocationData(Trentino::RuntimeModel::CompositePtr& dummyComposite)
	{
      InvocationDataPtr invocationData(new InvocationData());
      const RuntimeModel::ServiceBasePtr service = createBasicCalculatorRuntimeModel(dummyComposite);
      invocationData->setTargetService(service); 
      invocationData->setOperation("div");

      //the generated code knows the right data type
      int* const param1 = new int(10);
      int* const param2 = new int(5);
      InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(param1);
      params.push_back(param2);
      invocationData->setParameters(params);

      return invocationData;
	}


	Trentino::Invocation::InvocationDataPtr createDiv2BasicCalculatorInvocationData(Trentino::RuntimeModel::CompositePtr& dummyComposite)
	{
      InvocationDataPtr invocationData(new InvocationData());
      const RuntimeModel::ServiceBasePtr service = createBasicCalculatorRuntimeModel(dummyComposite);

      invocationData->setTargetService(service); 
      invocationData->setOperation("div2");

      //the generated code knows the right data type
      int* const param1 = new int(2);
      int* const param2 = new int(5);
      InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(param1);
      params.push_back(param2);
      invocationData->setParameters(params);

      return invocationData;
   }

} //namespace

TEST_F(DISABLED_BasicCalculatorInvocation,addTest)
{
   RuntimeModel::ContributionPtr contrib = createRuntimeContribution();
   
   Trentino::RuntimeModel::CompositePtr dummyComposite = contrib->composites()[0];
	InvocationDataPtr data = createAddBasicCalculatorInvocationData(dummyComposite);
	InvocationContextPtr ctx = createBasicCalculatorContext();
   const InvokerPtr invoker = RuntimeBootstrapper::instance().invoker();
   ctx->setCurrentInvoker(invoker); 

   EXPECT_NO_THROW(invoker->invoke(data, ctx));
   
   //the generated code knows the right data type
	int* const response = static_cast<int*>(data->response());
	ASSERT_TRUE( (*response) == 7 ); //=3+4

   // remove invocation data, generated code knows it
   destroyAddBasicCalculatorInvocationData(data);
}

TEST_F(DISABLED_BasicCalculatorInvocation,divTest)
{
   RuntimeModel::ContributionPtr contrib = createRuntimeContribution();

   Trentino::RuntimeModel::CompositePtr dummyComposite = contrib->composites()[0];
   InvocationDataPtr data = createDivBasicCalculatorInvocationData(dummyComposite);
   InvocationContextPtr ctx = createBasicCalculatorContext();
   const InvokerPtr invoker = RuntimeBootstrapper::instance().invoker();
   ctx->setCurrentInvoker(invoker);

   EXPECT_NO_THROW(invoker->invoke(data, ctx));

   int* response = static_cast<int*>(data->response());
	ASSERT_TRUE((*response) == 2); // 10 div 5

   destroyDivBasicCalculatorInvocationData(data);
}



