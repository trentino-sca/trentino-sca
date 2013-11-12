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
#include "TrentinoReflectionReflectMethod.h"

//standard
#include <boost/smart_ptr/scoped_ptr.hpp>

//specific
#include "TrentinoReflectionHelpersVariant.h"

using namespace Trentino::Reflection;
using namespace Trentino::Reflection::Helpers;
using namespace Trentino::Reflection::Data::Method;

//construction
ReflectMethod::ReflectMethod(const MetaData* data) 
{ 
   mData = data; 
}

ReflectMethod::ReflectMethod(const ReflectMethod& source) 
{ 
   copyFrom(source); 
}

ReflectMethod::ReflectMethod(void) : mData(nullptr) 
{
   //does nothing here
}

//operators
void ReflectMethod::operator=(const ReflectMethod& source) 
{ 
   copyFrom(source); 
}

//service
const char* ReflectMethod::name() const
{
   assert(mData != nullptr);
   if(mData != nullptr)
   {
      return mData->methodName;
   }

   return nullptr;
}

const char* ReflectMethod::returnType( ) const
{
   assert(mData != nullptr);
   if(mData != nullptr)
   {
      return mData->returnType;
   }

   return nullptr;
}


int ReflectMethod::paramsCount() const
{
   assert(mData != nullptr);
   if(mData != nullptr)
   {
      return mData->paramsCount;
   }

   return -1;
}

const Param* ReflectMethod::paramsAt(int index) const
{
   assert(mData != nullptr);
   if(mData != nullptr || index < 0 || index >= mData->paramsCount)
   {
      return &mData->params[index];
   }

   return nullptr;
}

Helpers::Variant ReflectMethod::invoke(void* thisPtr, const std::vector<Variant>& params) const
{
   boost::scoped_array<void*> voidParamList(new void*[params.size()]);
   
   for(int i = 0; i < static_cast<int>(params.size()); ++i)
   {
      voidParamList[i] = const_cast<Variant::Data*>(params[i].dataPtr());
   }

   return invoke(thisPtr, voidParamList.get());
}


Variant ReflectMethod::invoke(void* thisPtr, void* params[]) const
{
   assert(mData != nullptr);
   if(mData != nullptr)
   {
      Variant result = Variant::fromTypeName(returnType());

      try
      {

      mData->invoke(thisPtr, const_cast<Variant::Data*>(result.dataPtr()), params);
      }
      catch(...)
      {
         throw;
      }
      return result;
   }
   return Variant();
}

//management
boost::shared_ptr<ReflectMethod> ReflectMethod::constructReflectMethod(const MetaData& metaData)
{
   return boost::shared_ptr<ReflectMethod>(new ReflectMethod(&metaData));
}

void ReflectMethod::copyFrom(const ReflectMethod& source) 
{ 
   mData = source.mData; 
}
