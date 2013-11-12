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
#include "TrentinoReflectionReflectObject.h"

//standard
#include <boost/smart_ptr/scoped_ptr.hpp>

//specific
#include "TrentinoReflectionHelpersDefaultValueVariant.h"
#include "TrentinoReflectionDataRegistry.h"
#include "TrentinoReflectionReflectMethod.h"
#include "./../../Utils/TrentinoUtilsTypeName.h"

using namespace std;
using namespace Trentino::Reflection;
using namespace Trentino::Reflection::Helpers;
using namespace Trentino::Reflection::Data;

//construction
ReflectObject::ReflectObject(const Object::MetaData data):mData(data)
{  
}


//operators
void ReflectObject::operator=(const ReflectObject& source) 
{ 
   copyFrom(source); 
}

//services
void* ReflectObject::newInstance(Trentino::Reflection::DataRegistry& registry, bool registerInstance) const
{
   //signature of method is empty
   //we need default constructor new
   std::vector<string> signatureList;
   ReflectMethodPtr resultMethod = queryMethod("new", signatureList);
   if(resultMethod.get() != nullptr)
      {
      Variant returnPtr = DefaultValueVariant<void*>::value();         
      returnPtr = resultMethod->invoke(nullptr, nullptr);

      if((registerInstance == true || mData.castCall != nullptr) && returnPtr.toVoidPtr() != nullptr)
         {
         registry.registerInstance(returnPtr.toVoidPtr(), *this);
         }

      return returnPtr.toVoidPtr();
      }
   return nullptr;
}

void* ReflectObject::newInstance(Trentino::Reflection::DataRegistry& registry,
                                 const std::vector<std::string>& parameterTypes,
                                 const std::vector<Helpers::Variant>& params,
                                 bool registerInstance) const
{
   boost::scoped_array<void*> voidParamList(new void*[params.size()]);
   for(int i = 0; i < static_cast<int>(params.size()); ++i)
   {
      voidParamList[i] = const_cast<Variant::Data*>(params[i].dataPtr());
   }

   return newInstance(registry,parameterTypes, voidParamList.get(), registerInstance);
}


void* ReflectObject::newInstance(Trentino::Reflection::DataRegistry& registry,
                                 const std::vector<std::string>& parameterTypes,
                                 void* params[],
                                 bool registerInstance) const
{
   const char* newMethodName = "new";
   ReflectMethodPtr newMethod = queryMethod(newMethodName, parameterTypes);

   //found?
   if(newMethod.get() != nullptr)
   {
      Variant returnPtr = DefaultValueVariant<void*>::value();         
      returnPtr = newMethod->invoke(nullptr, params);
      
      if((registerInstance == true ||  mData.castCall != nullptr) && returnPtr.toVoidPtr() != nullptr)
      {
         registry.registerInstance(returnPtr.toVoidPtr(), *this);
      }

      return returnPtr.toVoidPtr();
   }

   return nullptr;
}


void ReflectObject::deleteInstance(DataRegistry& /*registry*/,void* object, bool /*unregisterInstance*/) const
{

   if(object == nullptr)
      {
      return;
      }

   std::vector<ReflectMethodPtr> resultList;
   queryMethods("delete", resultList);

   assert(resultList.empty() == false);

   if(resultList.empty() == false)
      {
      // there is only one delete!
      assert(resultList.size() == 1);
      resultList[0]->invoke(object, nullptr);
      }
}

bool ReflectObject::deleteRegisteredInstance(Trentino::Reflection::DataRegistry& registry,void* object)
{
   assert(object != nullptr);

   if(object != nullptr)
   {
      ReflectObjectPtr reflectObject = 
         registry.queryReflectObjectByInstance(object);

      if(reflectObject)
      {
         reflectObject->deleteInstance(registry,object, true);

         return true;
      }

   }

   assert(false); //no valid instance found!

   return false;
}

void* ReflectObject::castCall(void* ptr, const std::string& castInto) const
{
   if(ptr != nullptr && mData.castCall != nullptr)
   {
      return mData.castCall(ptr, castInto.c_str());
   }

   return ptr;
}

void* ReflectObject::castCallRegistered(Trentino::Reflection::DataRegistry& registry,
                                        void* ptr, const std::string& castInto)
{
   if(ptr != nullptr)
   {
      ReflectObjectPtr reflectObject = 
         registry.queryReflectObjectByInstance(ptr);

      if(reflectObject.get() != nullptr)
      {
         return reflectObject->castCall(ptr, castInto);
      }
   }

   return ptr;
}

bool ReflectObject::queryMethods(const std::string& methodName, 
                                 std::vector<ReflectMethodPtr>& resultList) const
{
   if(methodName.empty() == false)
   {
      for(int i = 0; i < mData.methodCount; ++i)
      {
      const char* lName =  mData.methods[i].methodName;
      if(0 == strcmp(methodName.c_str(),lName))
            resultList.push_back(ReflectMethod::constructReflectMethod(mData.methods[i]));
      }
      return !resultList.empty();
   }

   return false;
}

ReflectMethodPtr ReflectObject::queryMethod(const std::string& methodName, 
                                            const std::vector<std::string>& parameterTypes) const
{
   if(methodName.empty() == false)
   {
      for(int i = 0; i < mData.methodCount; ++i)
      {
         const Method::MetaData& methodData = mData.methods[i];
         // same size and same parameter count?
         if(static_cast<int>(parameterTypes.size()) == methodData.paramsCount && 
            0 == strcmp(methodName.c_str(), methodData.methodName))
         {
            bool found = true;
            for(int j = 0; j < methodData.paramsCount; ++j)
            {
               if(parameterTypes[j] != methodData.params[j].type)
               {
                  found = false;
                  break;
               }
            }
            if(found == true)
            {
               return ReflectMethod::constructReflectMethod(methodData);
            }
         }

      }
   }
   return ReflectMethodPtr();
}

int ReflectObject::methodCount() const
{
      return mData.methodCount;
}

ReflectMethodPtr ReflectObject::methodAt(int index) const
{
   if(index < 0 || index >= mData.methodCount)
   {
      return ReflectMethod::constructReflectMethod(mData.methods[index]);
   }

   return ReflectMethodPtr();
}

const char* ReflectObject::className() const
{
   return mData.className;
}

//management
void ReflectObject::copyFrom(const ReflectObject& source) 
{ 
   mData = source.mData;
}

