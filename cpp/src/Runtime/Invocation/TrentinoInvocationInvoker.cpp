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
#include "TrentinoInvocationInvoker.h"

#include "TrentinoInvocationSystemException.h"
#include "TrentinoInvocationRecoveryService.h"

//specific
#include "TrentinoInvocation.h"
#include "TrentinoInvocationGen.h"
#include "TrentinoInvocationServiceInvocationWrapperBase.h"
#include "TrentinoInvocationInvocationData.h"
#include "TrentinoInvocationInvocationContext.h"
#include "./../Core/TrentinoCoreComponentImplementationManagerBase.h"
#include "./../RuntimeModel/TrentinoRuntimeModelService.h"
#include "./../RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "./../RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "./../Core/TrentinoCoreSCAComponentContext.h"
#include "./../SCAModel/TrentinoSCAModelComponent.h"
#include "./../SCAModel/TrentinoSCAModelComposite.h"
#include "./../../Utils/TrentinoUtilsLogging.h"
#include "../Core/TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "../Core/TrentinoCoreBootstrappingRuntimeConfiguration.h"

#include <iostream>
#include "../RuntimeModel/TrentinoRuntimeModel.h"
#include "../RuntimeModel/TrentinoRuntimeModelWireBase.h"
#include <boost/exception/diagnostic_information.hpp> 
#include <boost/exception_ptr.hpp> 

using namespace Trentino::Invocation;
using namespace Trentino::Core;

namespace
   {
   void logException( const Trentino::Invocation::InvocationData& data,const Trentino::RuntimeModel::ServiceBasePtr& service, std::string& msg){
      Trentino::RuntimeModel::ComponentPtr comp = service->component().lock();
      logWarn("Exception in method '%s/%s/%s::%s',\nMessage '%s'\nre-throw",
         comp->composite().lock()->scaComposite()->name().c_str(),
         comp->scaComponent()->name().c_str(),
         service->name().c_str(),
         data.operation().c_str(),
         msg.c_str());
      }

   //! used to acquire and safely release instance objects
   struct InstanceObject {
      InstanceObject(Trentino::Core::ComponentImplementationManagerBasePtr mgr,
         Trentino::RuntimeModel::ServiceBasePtr targetService):
      mManager(mgr),mTargetService(targetService)
         {
         mInstance = mManager->getInstance(mTargetService);
         }
      ~InstanceObject()
         {
         if(mInstance)
            {
            SCAComponentContext::setCurrent();
            mManager->releaseInstance(mInstance, mTargetService);
            }
         }
      void* mInstance;
      Trentino::Core::ComponentImplementationManagerBasePtr mManager;
      Trentino::RuntimeModel::ServiceBasePtr mTargetService;
      };
   }


//construction
Invoker::Invoker()
   {
   //does nothing
   }

Invoker::~Invoker()
   {
   //does nothing
   }

bool Invoker::isSafeInvocationEnabled() const
   {
   using namespace Trentino::Core::Bootstrapping;
   const RuntimeBootstrapper&  bootstrapper = RuntimeBootstrapper::instance();
   RuntimeBootstrapper::RuntimeConfigurationConstPtr conf= bootstrapper.configuration();
   const bool enabledSafeInvocation = conf->enableSafeInvocation();
   return enabledSafeInvocation;
   }

//services

bool Invoker::invoke(const Trentino::Invocation::InvocationData& data,
                     void* retVal,
                     const Trentino::Invocation::InvocationContext& ctx,
                     const Trentino::RuntimeModel::ServiceBasePtr& targetService
                     )
   {
   bool enabledSafeInvocation =  isSafeInvocationEnabled();
   if(!targetService)
      {
      throw new std::runtime_error("Service not available");
      }

   InstanceObject instanceObject(mComponentImplementationManager,targetService);
   //Initialize the service Wrapper
   void* const instance = instanceObject.mInstance;
   if(instance)
      {
      if(enabledSafeInvocation)
         {
         try
            {
            InvocationSystemException* seInstance = InvocationSystemException::getInstance();// getInstance();
            seInstance->SafeInvocationWrapper(instance, mComponentImplementationManager, data, retVal, ctx, targetService);
            //mComponentImplementationManager->onInvoke(instance,data,ctx);
            }
         //System exception happened
         catch(InvocationSystemExceptionData ex)
            {
            //Call recovery service and pass necessary information to it
            InvocationRecoveryService::getInstance()->Recover(data, ex.getID());
            throw;
            }
         //Software exception happened
         catch(std::exception& ex)
            {
            std::string msg(ex.what());
            logException(data,targetService, msg);
            throw;
            }
         catch(boost::exception& ex)
            {
            std::string msg = boost::diagnostic_information(ex);
            logException(data, targetService,msg);
            throw;
            }
         catch(...)
            {
            std::string msg;
            logException(data, targetService, msg);
            throw;
            }
         }
      else
         {
         oasis::sca::ComponentContextPtr componentPtr(new SCAComponentContext(targetService->component().lock()->uri()));
         SCAComponentContext::setCurrent(componentPtr);

         try
            {
            mComponentImplementationManager->onInvoke(instance,data, retVal,ctx, targetService);
            }
         catch(...)
            {
            throw;
            }
         }
      return true;
      }
   else
      {
      logWarn("Implementation instance for service with @name='%s' " 
         "in component with @name='%s' in composite with @name='%s' could not be retrieved", 
         targetService->name().c_str(), 
         targetService->component().lock()->scaComponent()->name().c_str(),
         targetService->component().lock()->composite().lock()->
         scaComposite()->name().c_str());
      return false;
      }
   }



bool Invoker::invoke( const Trentino::Invocation::InvocationData& data,
                     void* retVal,
                     const Trentino::Invocation::InvocationContext& ctx) 
   {

   Trentino::ServiceRegistry::ServiceRegistryPtr reg = 
      Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance().serviceRegistry();
   Trentino::RuntimeModel::ServiceBasePtr targetService =reg->findService(data.targetComponent(),data.targetService());
   return invoke(data,retVal,ctx,targetService);
   }


//TODO: move this method in its own class. The method is used by the generated code
INVOCATION_IMPORT_EXPORT void TRENTINO_CDECL Trentino::Gen::trentino_gen_invoke
   (void* retVal,
   const std::string& opName,
   Trentino::Invocation::InvocationData::Parameters& params,
   Trentino::RuntimeModel::WireBase* wire
   )
   {
   assert(wire);
   const std::string& targetService = wire->service();
   Trentino::Invocation::InvocationData invocationData;
   std::size_t index = targetService.find_last_of("/");
   std::string componentname = targetService.substr(0,index);
   std::string serviceName = targetService.substr(index+1);
   invocationData.setTargetService(serviceName); 
   invocationData.setTargetComponent(componentname);
   invocationData.setOperation(opName);
   invocationData.setParameters(params);

   const Trentino::Invocation::InvocationContextPtr ctx = wire->invocationContext();
   if(!ctx->currentInvoker()->invoke(invocationData, retVal, *ctx))
      {
      throw std::runtime_error("service unavailable");
      }
   }

