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
#include "TrentinoUtilsStaticMap.h"

//standard
#include <assert.h>

using namespace std;
using namespace Trentino::Utils;

//global definitions
static std::map<unsigned long, StaticMap::Value> NamedObjects;




//class StaticMap

//service
void* StaticMap::retainNamedMemory(unsigned long hashIndex)
{
   std::map<unsigned long, StaticMap::Value>::iterator foundIndex = 
      NamedObjects.find(hashIndex);
   if(foundIndex == NamedObjects.end())
   {
      //not found
      return nullptr;
   }
   else
   {
      foundIndex->second.mRefCount++;
      return foundIndex->second.mPtr;
   }
}

void* StaticMap::releaseNamedMemory(unsigned long hashIndex)
{
   std::map<unsigned long, StaticMap::Value>::iterator foundIndex = 
      NamedObjects.find(hashIndex);
   if(foundIndex != NamedObjects.end())
   {
      --foundIndex->second.mRefCount;
      if(foundIndex->second.mRefCount == 0)
      {
         void* returnPtr = foundIndex->second.mPtr;
         NamedObjects.erase(hashIndex);
         return returnPtr;
      }
   }

   //not found/no action required 
   return nullptr;
}

unsigned long StaticMap::refCount(unsigned long hashIndex)
{
   std::map<unsigned long, StaticMap::Value>::const_iterator foundIndex = 
      NamedObjects.find(hashIndex);
   if(foundIndex != NamedObjects.end())
   {
      return foundIndex->second.mRefCount;
   }

   return 0;
}

void StaticMap::registerNamedMemory(unsigned long hashIndex, void* classPtr)
{
   assert(NamedObjects.find(hashIndex) == NamedObjects.end());
   StaticMap::Value newValue;
   newValue.mPtr = classPtr;
   NamedObjects.insert(StaticMap::HashMapPair(hashIndex, newValue));

}

bool StaticMap::isNamedMemoryRegistered(unsigned long hashIndex)
{
   std::map<unsigned long, StaticMap::Value>::const_iterator foundIndex = 
      NamedObjects.find(hashIndex);
   return(foundIndex != NamedObjects.end());
}
