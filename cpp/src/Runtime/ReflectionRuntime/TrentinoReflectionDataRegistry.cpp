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
#include "TrentinoReflectionDataRegistry.h"

//specific
#include "TrentinoReflectionReflectObject.h"

using namespace std;
using namespace Trentino::Reflection;
using namespace Trentino::Reflection::Data;

//global functions
namespace
{
   //! Only simple helper function to gain singleton here
   template<class CLASS>
   static inline CLASS& instance()
   {
      static CLASS funcInstance;
      return funcInstance;
   } //template<class CLASS> CLASS& instance()
} //namespace


//construction
DataRegistry::DataRegistry(const DataRegistry& /*source*/)
{
   //does nothing here
}

DataRegistry::DataRegistry()
{
   //does nothing here
}

//operators
void DataRegistry::operator=(const DataRegistry& /*source*/)
{
   //does nothing here
}

//management
void DataRegistry::registerReflectObject(const Object::MetaData& data)
{
   boost::lock_guard<boost::mutex> lock(mMetaDataChangesMutex);
   mReflectionObjects.insert(ReflectionObjectPair(data.className, data));
}

void DataRegistry::unregisterReflectObject(const Object::MetaData& data)
{
   boost::lock_guard<boost::mutex> lock(mMetaDataChangesMutex);

   for(RegisteredInstances::const_iterator iter = mRegisteredInstances.begin();iter !=mRegisteredInstances.end();){
      if(iter->second == data.className)
         {
         ReflectObject::deleteRegisteredInstance(*this,iter->first);
         }
         ++iter;
      }
   mReflectionObjects.erase(data.className);
}


//services

ReflectObjectPtr DataRegistry::constructReflectObject(const Data::Object::MetaData& metaData) const
{
   return ReflectObjectPtr(new ReflectObject(metaData));
}

ReflectObjectPtr DataRegistry::queryReflectObject(const std::string& className) const
{
   boost::lock_guard<boost::mutex> lock(mMetaDataChangesMutex);

   map<string, const Object::MetaData>::const_iterator iter = mReflectionObjects.find(className);
   if(iter == mReflectionObjects.end())
   {
      // log here
      return ReflectObjectPtr();
   }
   else
   {
      return constructReflectObject(iter->second);
   }
}

int DataRegistry::reflectObjectCount() const
{
   //return mReflectObjectsArray.size();
   return mReflectionObjects.size();
}

void DataRegistry::registerInstance(void* inst, const ReflectObject& reflectObject)
{
   assert(inst != nullptr);

   boost::lock_guard<boost::mutex> lock(mRegInstanceChangesMutex);
   mRegisteredInstances.insert(InstanceReflectObjectPair(inst, reflectObject.mData.className));
}

bool DataRegistry::unregisterInstance(void* inst)
{
   if(inst ==nullptr)
   {
    return false;
   }

   boost::lock_guard<boost::mutex> lock(mRegInstanceChangesMutex);
   return mRegisteredInstances.erase(inst) != 0;
}

ReflectObjectPtr DataRegistry::queryReflectObjectByInstance(void* inst) const
{
   assert(inst != nullptr);

   boost::lock_guard<boost::mutex> lock(mRegInstanceChangesMutex);

   RegisteredInstances::const_iterator iter = mRegisteredInstances.find(inst);
   if(iter == mRegisteredInstances.end())
   {
      // log here
      return ReflectObjectPtr();
   }
   else
   { 
      std::string className = iter->second;
      ReflectionObjects::const_iterator iter2 = mReflectionObjects.find(className);
      assert(iter2 != mReflectionObjects.end());
      return constructReflectObject(iter2->second);
   }

}


 void DataRegistry::cleanUp()
{
    //unregister all registered instances
    RegisteredInstances::const_iterator iter;
    for(iter = mRegisteredInstances.begin();iter!=mRegisteredInstances.end();)
       {
       ReflectObject::deleteRegisteredInstance(*this,iter->first);
       unregisterInstance(iter->first);
       iter = mRegisteredInstances.begin();
       }
   assert(mRegisteredInstances.size() == 0);
}

DataRegistry::~DataRegistry()
{
}
