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
#include "TrentinoRuntimeModelCPPImplementation.h"

//standard
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>

//specific
#include "./TrentinoRuntimeModel.h"
#include "./TrentinoRuntimeModelService.h"
#include "./TrentinoRuntimeModelComponent.h"
#include "./TrentinoRuntimeModelReference.h"
#include "./TrentinoRuntimeModelComposite.h"
#include "./TrentinoRuntimeModelProperty.h"
#include "./TrentinoRuntimeModelWire.h"
#include "./TrentinoRuntimeModelCommonFuncs.h"
#include "./../SCAModel/TrentinoSCAModelComponentTypeReference.h"
#include "./../SCAModel/TrentinoSCAModelComponentService.h"
#include "./../SCAModel/TrentinoSCAModelCPPImplementation.h"
#include "./../SCAModel/TrentinoSCAModelCPPImplementationScope.h"
#include "./../SCAModel/TrentinoSCAModelCPPInterface.h"
#include "./../SCAModel/TrentinoSCAModelProperty.h"
#include "./../Invocation/TrentinoInvocationServiceInvocationWrapperBase.h"
#include "./../ReflectionRuntime/TrentinoReflectionDataRegistry.h"
#include "./../ReflectionRuntime/TrentinoReflectionReflectObject.h"
#include "./../ReflectionRuntime/TrentinoReflectionHelpersDefaultValueVariant.h"
#include "./../../Utils/TrentinoUtilsTypeName.h"
#include "../SCAModel/TrentinoSCAModelCPPImplementationFunction.h"

using namespace std;
using namespace Trentino::RuntimeModel;
using namespace Trentino::Reflection;
using namespace Trentino::Reflection::Helpers;
using Trentino::Invocation::ServiceInvocationWrapperBase;
using Trentino::Invocation::ServiceInvocationWrapperBasePtr;
namespace SCAModel = Trentino::SCA::Model;


namespace
{  


   bool starts_with(const std::string& source, const char* subst){
      return strncmp(source.c_str(), subst, strlen(subst)) ==0;
     }


   void getMethodsName(std::string& initMethodName,std::string& destroyMethodName,std::string& setcontDirName,
      const Trentino::SCA::Model::CPPImplementationPtr& scaCPPImplementation)
   {
    const std::vector<SCAModel::CPPImplementationFunctionPtr>& functionElements=
       scaCPPImplementation->functionElements();
    const int len = (int)functionElements.size();
    for(int i=0; i <len; i++)
       {
        const SCAModel::CPPImplementationFunctionPtr& functionPtr = functionElements[i];
        const std::string& fName = functionPtr->name();
        if(!functionPtr)
           {
           continue;
           }
        if(functionPtr->isInit() || starts_with(fName,"init."))
           {
            initMethodName = fName;
           }
        else if(functionPtr->isDestroy()|| starts_with(fName,"destroy."))
           {
            destroyMethodName=fName;
           }
        else if(starts_with(fName,"set_root_path."))
           {
            setcontDirName=fName.substr(14);
           }
       }
   }
}

CPPImplementation::CPPImplementation(Trentino::Reflection::DataRegistry& registry, 
   const Trentino::SCA::Model::CPPImplementationPtr scaCPPImplementation) 
 : mSCACPPImplementation(scaCPPImplementation)
{
   mClass = registry.queryReflectObject(scaCPPImplementation->clazz());
   if(!mClass)
   {
      throw runtime_error(
            "Reflect object for class '" + scaCPPImplementation->clazz() + "' not found!"); 
   }

   std::string initMethodName;
   std::string destroyMethodName;
   std::string setDirName;
   getMethodsName(initMethodName, destroyMethodName,setDirName, scaCPPImplementation);
   mInitMethod = 
      initMethodName.empty() ? ReflectMethodPtr() : queryMethod(initMethodName);
   mDestroyMethod = 
      destroyMethodName.empty() ? ReflectMethodPtr() : queryMethod(destroyMethodName);
   mSetContributionDirMethod = setDirName.empty()?ReflectMethodPtr() : queryMethod(setDirName);
}

   //service
Trentino::Reflection::ReflectMethodPtr CPPImplementation::querySetterMethod(
   const ConstReferenceBasePtr& reference)
{  
   return queryMethod( CommonFuncs::setterName(reference) );   
}

Trentino::Reflection::ReflectMethodPtr CPPImplementation::queryPropertySetterMethod(
   const ConstPropertyPtr& property)
{
   return queryMethod( CommonFuncs::setterName(property) );
}

//management
ReflectMethodPtr CPPImplementation::queryMethod(const std::string& methodName) const
{
   assert(mClass);
   vector<ReflectMethodPtr> resultList;
   mClass->queryMethods(methodName, resultList);

   if(resultList.empty())
   {  
      throw runtime_error(
         "Reflections for method '" + mSCACPPImplementation->clazz() + 
         "::" + methodName + "' not found");      
   }

   if(resultList.size() != 1)
   {
      throw runtime_error(
         "Ambiguous reflections for method '" + mSCACPPImplementation->clazz() + 
         "::" + methodName + "' available");      
   }

   return resultList[0];
}

int CPPImplementation::scope() const
{
if(mSCACPPImplementation && mSCACPPImplementation->scope())
   {
   return mSCACPPImplementation->scope()->value();
   }
//default scope is composite for Trentino
return SCAModel::CPPImplementationScope::Composite;
}