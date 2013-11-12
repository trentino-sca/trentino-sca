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
#include "TrentinoCoreBootstrappingModuleBase.h"

//standard
#include <assert.h>

//specific
#include "../../Utils/TrentinoUtilsTypeName.h"

using namespace std;
using namespace Trentino::Core::Bootstrapping;
using Trentino::Utils::TypeName;

//class ModuleBase

//construction
ModuleBase::ModuleBase() : mRefCount(0)
{

}
ModuleBase::~ModuleBase()
{

}

//service
unsigned long ModuleBase::addRef()
{
   ++mRefCount;

   return mRefCount;
}

const char* ModuleBase::name() const
{
   return TypeName<ModuleBase>::name();
}


unsigned long ModuleBase::releaseRef()
{
   if(mRefCount != 0)
   {
      --mRefCount;
      if(mRefCount == 0)
      {
         delete this;
      }
      else
      {
         return mRefCount;
      }
   }
   return 0;
}


