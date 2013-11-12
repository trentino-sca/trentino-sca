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
#include "TrentinoCoreComponentCPPImplementationLifeCycleMethodManager.h"


//standard

//specific
#include "../RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../ReflectionRuntime/TrentinoReflectionReflectMethod.h"
#include "../RuntimeModel/TrentinoRuntimeModelCPPImplementation.h"
#include "../SCAModel/TrentinoSCAModelCPPImplementation.h"


using namespace Trentino::Core;
using namespace Trentino::RuntimeModel;

namespace
{

   //***********************************************************************************************
   //                                         LifeCycleMethodTyp
   //***********************************************************************************************
   //! \brief an enum representing lifecycle method types init and destroy
   //***********************************************************************************************
   enum LifeCycleMethodType {
      init,
      destroy,
      setContributionDir,
      invoke
      };

    CPPImplementationPtr getCPPImplementation(const ConstComponentPtr& component){
       ImplementationPtr impl = component->implementation();
       if(!impl){
          return CPPImplementationPtr();
          }
       
       CPPImplementationPtr cppImpl = 
          boost::dynamic_pointer_cast<CPPImplementation,Implementation>(impl);
       assert(cppImpl.get()!=nullptr);
       return cppImpl;
    }


    Trentino::Reflection::ReflectMethodPtr getLifeCycleMethodByComponentAndLifeCycleMethodType
       (const ConstComponentPtr& component, LifeCycleMethodType lcmtype)
    {
    
    CPPImplementationPtr cppImpl = getCPPImplementation(component);
    switch(lcmtype){
    case init:
       return cppImpl->initLifeCycleMethod();
    case destroy:
           return cppImpl->destroyLifeCycleMethod();
    case setContributionDir:
       return cppImpl->setContributionDirLifeCycleMethod();
    case invoke:
       {
        static std::string mtd ("trentino_internal_impl_cpp_invoke_do_not_use_this_name");
        return cppImpl->queryMethod(mtd);
       }
      
    default:
       throw std::runtime_error("unknown life cycle method");
       }   
    }
}

//class CPPImplementationLifeCycleMethodManager

CPPImplementationLifeCycleMethodManager::CPPImplementationLifeCycleMethodManager()
{
  
}

CPPImplementationLifeCycleMethodManager::~CPPImplementationLifeCycleMethodManager()
{

}

void CPPImplementationLifeCycleMethodManager::callOnInitMethod( const ConstComponentPtr& component,
   void* instance ) const
{
   const Trentino::Reflection::ReflectMethodPtr onInitMethod= 
      getLifeCycleMethodByComponentAndLifeCycleMethodType(component, init);
   
   if(!onInitMethod)
      {
      //This implementation does not have a life cycle init method.
      return;
      }

   onInitMethod->invoke(instance,nullptr);
}

void CPPImplementationLifeCycleMethodManager::callOnDestroyMethod( const ConstComponentPtr& component, 
   void* instance ) const
{
 const Trentino::Reflection::ReflectMethodPtr onDestroyMethod= 
    getLifeCycleMethodByComponentAndLifeCycleMethodType(component, destroy);

 if(!onDestroyMethod)
    {
    //This implementation does not have a life cycle destroy method.
    return;
    }

  onDestroyMethod->invoke(instance,nullptr);
}



void Trentino::Core::CPPImplementationLifeCycleMethodManager::callSetContributionRootDirMethod( const Trentino::RuntimeModel::ConstComponentPtr& component, void* instance ) const
{
const Trentino::Reflection::ReflectMethodPtr setContributionDirMethod= 
   getLifeCycleMethodByComponentAndLifeCycleMethodType(component, setContributionDir);

if(!setContributionDirMethod)
   {
   //This implementation does not have a life cycle destroy method.
   return;
   }
 std::string path = component->composite().lock()->contribution().lock()->localPath();
 void* params[1];
 params[0]=&path;
 setContributionDirMethod->invoke(instance,params);
}


void CPPImplementationLifeCycleMethodManager::deleteInstance( const ConstComponentPtr& component, 
   void* instance )const
 {
    callOnDestroyMethod(component,instance);
    const CPPImplementationPtr cppImpl = getCPPImplementation(component);
   if(cppImpl->scaCPPImplementation()->header() == "TrentinoGenBindingProxy.h")
   {
      return;
   }
    const Trentino::Reflection::ReflectObjectPtr reflxObj= cppImpl->instanceReflectObject();
    assert(reflxObj.get() != nullptr);
    reflxObj->deleteInstance(component->dataRegistry(),instance);
 }

void* CPPImplementationLifeCycleMethodManager::newInstance( const ConstComponentPtr& component ) const
{
    const CPPImplementationPtr cppImpl = getCPPImplementation(component);
    const Trentino::Reflection::ReflectObjectPtr reflxObj= cppImpl->instanceReflectObject();
    assert(reflxObj.get() != nullptr);
    return reflxObj->newInstance(component->dataRegistry());
}

void CPPImplementationLifeCycleMethodManager::invokeOnInstance(const Trentino::XML::Schema::Name&  serviceId, const ConstComponentPtr& component, const Trentino::Invocation::InvocationData& data
                    , void* retVal
                    , const Trentino::Invocation::InvocationContext& ctx, void* instance)const
   {
   const Trentino::Reflection::ReflectMethodPtr method= 
   getLifeCycleMethodByComponentAndLifeCycleMethodType(component, invoke);
   assert(method.get() != nullptr);
   void* params[4];
   params[0] = const_cast<Trentino::XML::Schema::Name*>(&serviceId);
   params[1] = const_cast<Trentino::Invocation::InvocationData*>(&data);
   params[2] = const_cast<Trentino::Invocation::InvocationContext*>(&ctx);
   params[3] = retVal;
   method->invoke(instance,params);
   }
