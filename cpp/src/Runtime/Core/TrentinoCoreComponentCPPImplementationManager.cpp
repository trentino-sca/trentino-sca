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
#include "TrentinoCoreComponentCPPImplementationManager.h"

//standard
#include <string>
#include <utility>  
#include <stdexcept>
#include <boost/thread/locks.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/smart_ptr/make_shared.hpp>

//specific
#include "../../Global/TrentinoGlobal.h"
#include "TrentinoCoreComponentPropertyManager.h"
#include "../RuntimeModel/TrentinoRuntimeModel.h"
#include "../RuntimeModel/TrentinoRuntimeModelService.h"
#include "../RuntimeModel/TrentinoRuntimeModelReference.h"
#include "../RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../RuntimeModel/TrentinoRuntimeModelCPPImplementation.h"
#include "../RuntimeModel/TrentinoRuntimeModelWire.h"
#include "../RuntimeModel/TrentinoRuntimeModelProperty.h"
#include "../SCAModel/TrentinoSCAModelComponentReference.h"
#include "../SCAModel/TrentinoSCAModelComponentService.h"
#include "../SCAModel/TrentinoSCAModelComponentTypeReference.h"
#include "../SCAModel/TrentinoSCAModelCPPImplementation.h"
#include "../SCAModel/TrentinoSCAModelCPPImplementationScope.h"
#include "../SCAModel/TrentinoSCAModelCPPInterface.h"
#include "../Invocation/TrentinoInvocationInvocationData.h"
#include "../../Utils/TrentinoUtilsLogging.h"
#include "TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "TrentinoCoreComponentCPPImplementationLifeCycleMethodManager.h"
#include "../XML/TrentinoXMLSchema.h"

using Trentino::Core::ComponentCPPImplementationManager;
using namespace std;
namespace RuntimeModel = Trentino::RuntimeModel;
namespace SCAModel = Trentino::SCA::Model;

namespace
{
   void performDependencyInjection( const RuntimeModel::ConstComponentPtr& component
                                  , void* instance)
   {
      assert(component);
      //inject references
      BOOST_FOREACH(const RuntimeModel::ConstReferenceBasePtr& reference, component->references())
      {
         // Ultimate multiplicity checks
         if(reference->multiplicity() == SCAModel::ReferenceMultiplicity1to1)
         {
            assert(reference->wireableSupport().wires().size() == 1);
         }
         else if (reference->multiplicity() == SCAModel::ReferenceMultiplicity1toN)
         {
            assert(reference->wireableSupport().wires().size() >= 1);
         }

         // Detect if a single value or a list is to be injected based on referenceType multiplicity
         // Reason: multiplicity in component can be narrowed down (1..N -> 1..1 and 0..N -> 0..1)
         // See [ASM50009] (assembly spec 1.1 committee specification draft 08 / public review draft 03, 3 May 2011, pg. 28, ln. 869)
         if(reference->scaReferenceType()->multiplicity() == SCAModel::ReferenceMultiplicity0toN
            ||  reference->scaReferenceType()->multiplicity() == SCAModel::ReferenceMultiplicity1toN)
         { // List injection
            RuntimeModel::Reference::VoidPtrList proxies;
             BOOST_FOREACH( const RuntimeModel::ConstWireBasePtr& wire
                          , reference->wireableSupport().wires() )
             {
                proxies.push_back(wire->proxy().get());
             }

             reference->invokeSetter(instance, proxies);
         }
         else
         { // Single value injection
            // Check if the wires list is not empty - it is possible for optional references
            if (reference->wireableSupport().wires().size() != 0)
            {
               const RuntimeModel::ConstWireBasePtr wire = 
                  *(reference->wireableSupport().wires().begin());   
               try
               {
               reference->invokeSetter(
               instance, wire->proxy().get());
               }
               catch(...)
               {
                  throw;
               }
            }
         }

      } 


      Trentino::Core::CPPImplementationLifeCycleMethodManager methodLifeCycleManager;
      //inject current contribution directory
      methodLifeCycleManager.callSetContributionRootDirMethod(component,instance);

      //inject properties      
      //The Property object knows its values already, so that it's not necessary to pass them
      //to invokeSetter() as its done in case of reference injection 
      Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
      Trentino::Core::ComponentPropertyManager& componentPropertyManager = booter.componentPropertyManager();

      BOOST_FOREACH(const RuntimeModel::PropertyPtr& property, component->properties())
      {
         componentPropertyManager.injectValues(property, instance);
      } 

      
      methodLifeCycleManager.callOnInitMethod(component,instance);
   }

   const RuntimeModel::CPPImplementationPtr getCPPImplementation(
      const RuntimeModel::ConstComponentPtr& component)
   {
      const RuntimeModel::ImplementationPtr implementation = 
         component->implementation();
      assert(implementation);
 
      return  boost::dynamic_pointer_cast<RuntimeModel::CPPImplementation>(implementation);    
   }
} //namespace

//class ComponentCPPImplementationManager  
   //additional
      //struct ImplInfo
         //construction
ComponentCPPImplementationManager::ImplInfo::ImplInfo()
: instance(nullptr)
, usageCount(0)
{}
   //services
void ComponentCPPImplementationManager::onInit(const RuntimeModel::ConstComponentPtr& component)
{
   const RuntimeModel::ConstCPPImplementationPtr cppImplementation = getCPPImplementation(component);
   assert(cppImplementation);
   const ComponentCPPImplementationManager::ImplInfoPtr implInfo = getImplInfo(cppImplementation.get());       

   boost::unique_lock<boost::mutex> lock(implInfo->mutex);
   if(   cppImplementation->scaCPPImplementation()->isEagerInit()
      && cppImplementation->scaCPPImplementation()->scope()->value() == 
            SCAModel::CPPImplementationScope::Composite )
   {  
      if(!implInfo->instance)
      {      
         Trentino::Core::CPPImplementationLifeCycleMethodManager methodLifeCycleManager;
         implInfo->instance = methodLifeCycleManager.newInstance(component);

         if(implInfo->instance)
         {
            performDependencyInjection(component, implInfo->instance);
         }
         else
         {  
            throw runtime_error(
               string("Could not instantiate implementation for component with uri '") + 
                  component->uri().c_str() + "'" );
         }
      }
   }
   
}
   //construction
ComponentCPPImplementationManager::ComponentCPPImplementationManager()
{
   //does nothing here   
}
   
//services
void* ComponentCPPImplementationManager::getInstance(const RuntimeModel::ConstServiceBasePtr& service)
{
   RuntimeModel::ConstComponentPtr component = service->component().lock();
   void* const instance = getInstance(component);

   if(instance)
   {
      //!\todo we assume here a cpp interface !
      SCAModel::CPPInterfacePtr cppInterface = 
         boost::static_pointer_cast<SCAModel::CPPInterface>(
            service->scaServiceType()->interfaceElement());
 
      return Trentino::Reflection::ReflectObject::castCallRegistered(component->dataRegistry(),
         instance, cppInterface->clazz());
   }

   return nullptr;
}

void ComponentCPPImplementationManager::releaseInstance( void* instance
                                                       , const RuntimeModel::ConstServiceBasePtr& service)
{
   const RuntimeModel::ConstCPPImplementationPtr cppImplementation = 
      getCPPImplementation(service->component().lock());
   assert(cppImplementation);
   
   const ComponentCPPImplementationManager::ImplInfoPtr implInfo = 
      getImplInfo(cppImplementation.get()); 

   boost::unique_lock<boost::mutex> lock(implInfo->mutex);
   switch(cppImplementation->scope())
   {      
      case SCAModel::CPPImplementationScope::Composite:
      {  
         //there must be only one instance for composite scoped implementations
         assert(instance == implInfo->instance);
         implInfo->usageCount = implInfo->usageCount > 0 ? --implInfo->usageCount : 0;
         break;
      }  
      case SCAModel::CPPImplementationScope::Stateless:   
      {          
         Trentino::Core::CPPImplementationLifeCycleMethodManager methodLifeCycleManager;
         methodLifeCycleManager.deleteInstance(service->component().lock(),instance);         

         implInfo->usageCount = implInfo->usageCount > 0 ? --implInfo->usageCount : 0;
         break;
      }
      default:
         assert(false);   
   } //switch(cppImplScope->value())

   implInfo->noUsers.notify_one();
}     

void ComponentCPPImplementationManager::onRemove(const RuntimeModel::ConstComponentPtr& component)
{  
   const RuntimeModel::ConstCPPImplementationPtr cppImplementation = 
      getCPPImplementation(component);

   const ComponentCPPImplementationManager::ImplInfoPtr implInfo = 
      getImplInfo(cppImplementation.get());     

   //wait until all the current users have called releaseInstance() for all of the instances
   //of the given implementation
   {
      boost::unique_lock<boost::mutex> lock(implInfo->mutex);
      if(implInfo->usageCount > 0)
         implInfo->noUsers.wait(lock);

      if(implInfo->instance)
      {
         Trentino::Core::CPPImplementationLifeCycleMethodManager methodLifeCycleManager;
         methodLifeCycleManager.deleteInstance(component,implInfo->instance);
         implInfo->instance = nullptr;
      }
   }

   boost::unique_lock<boost::mutex> lock(mImplInfoMapMutex);
   mImplInfoMap.erase(cppImplementation.get());
}

   //management
void* ComponentCPPImplementationManager::getInstance(const RuntimeModel::ConstComponentPtr& component)
{  
   assert(component);
   boost::lock_guard<boost::recursive_mutex> componentLock(component->mutex());

   //Due to concurrency issues it could happen that an instance for 
   //an unaccessible component is requested.
   const bool isAccessible =    component->state() == RuntimeModel::Component::Resolved 
                             || component->state() == RuntimeModel::Component::OptionalUnresolved;
   if(!isAccessible)         
      return nullptr;
   
   const RuntimeModel::ConstCPPImplementationPtr cppImplementation = 
      getCPPImplementation(component);
   assert(cppImplementation);
   
   const ComponentCPPImplementationManager::ImplInfoPtr implInfo = 
      getImplInfo(cppImplementation.get());  

   void* instance = nullptr;
   boost::unique_lock<boost::mutex> lock(implInfo->mutex);
   switch(cppImplementation->scope())
   {      
      case SCAModel::CPPImplementationScope::Composite:
      {  
         //this is the first time the instance is requested
         if(!implInfo->instance)
         {
            Trentino::Core::CPPImplementationLifeCycleMethodManager methodLifeCycleManager;
            implInfo->instance = methodLifeCycleManager.newInstance(component);
            if(implInfo->instance)
            {
               performDependencyInjection(component, implInfo->instance);
            }
            else
            {
               logError( "%s: Could not instantiate implementation for component with uri '%s'"
                      , __FUNCTION__
                      , component->uri().c_str() );
            }
         }

         instance = implInfo->instance; 
         break;
      }  
      case SCAModel::CPPImplementationScope::Stateless:   
      {  
         Trentino::Core::CPPImplementationLifeCycleMethodManager methodLifeCycleManager;
         instance = methodLifeCycleManager.newInstance(component);
         if(instance)
         {            
            performDependencyInjection(component, instance);
         }
         else
         {
            logError( "%s: Could not instantiate implementation for component with uri '%s'"
                     , __FUNCTION__
                     , component->uri().c_str() );
         }
             
         break;
      }
      default:
         assert(false);   
   } //switch(cppImplScope->value())

   if(instance)
      implInfo->usageCount++;  

   //!\todo consider throwing an appropriate exception if the instance cannot be retrieved
   return instance;
}

ComponentCPPImplementationManager::ImplInfoPtr 
   ComponentCPPImplementationManager::getImplInfo(const void* key)
{     
   boost::unique_lock<boost::mutex> lock(mImplInfoMapMutex);
   const ImplInfoMap::const_iterator it = mImplInfoMap.find(key);
   
   if(it == mImplInfoMap.end())
   {
      const ComponentCPPImplementationManager::ImplInfoPtr implInfo = 
         boost::make_shared<ComponentCPPImplementationManager::ImplInfo>();
      mImplInfoMap[key] = implInfo;
      return implInfo;
   }
   else
   {   
      return it->second;
   }
}

void ComponentCPPImplementationManager::onInvoke(void* instance, 
   const Trentino::Invocation::InvocationData& data,
   void* retVal,
   const Trentino::Invocation::InvocationContext& ctx,
   const Trentino::RuntimeModel::ServiceBasePtr& targetService) const
{          
   const RuntimeModel::ConstComponentPtr& component = targetService->component().lock();
   Trentino::Core::CPPImplementationLifeCycleMethodManager methodLifeCycleManager;
   SCAModel::CPPInterfacePtr cppInterface = 
      boost::static_pointer_cast<SCAModel::CPPInterface>(
      targetService->scaServiceType()->interfaceElement());
   methodLifeCycleManager.invokeOnInstance(cppInterface->clazz(),component,data, retVal,ctx,instance);
}
