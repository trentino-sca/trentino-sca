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
#include "TrentinoReflectionHelpersVariant.h"

//standard
#include <string.h>

//specific
#include "../../Utils/TrentinoUtilsTypeName.h"
#include "TrentinoReflectionHelpersDefaultValueVariant.h"
#include "TrentinoReflectionHelpersDefaultValue.h"


using namespace Trentino::Reflection::Helpers;
using Trentino::Utils::TypeName;


//services
Variant Variant::fromTypeName(const char* typeName)
{
   if(typeName != nullptr)
   {
      if(strcmp(typeName, TypeName<signed char>::name()) == 0)
         return DefaultValueVariant<signed char>::value();
      if(strcmp(typeName, TypeName<unsigned char>::name()) == 0)
         return DefaultValueVariant<unsigned char>::value();
      if(strcmp(typeName, TypeName<short>::name()) == 0)
         return DefaultValueVariant<short>::value();
      if(strcmp(typeName, TypeName<unsigned short>::name()) == 0)
         return DefaultValueVariant<unsigned short>::value();
      if(strcmp(typeName, TypeName<bool>::name()) == 0)
         return DefaultValueVariant<bool>::value();
      if(strcmp(typeName, TypeName<int>::name()) == 0)
         return DefaultValueVariant<int>::value();
      if(strcmp(typeName, TypeName<unsigned int>::name()) == 0)
         return DefaultValueVariant<unsigned int>::value();
      if(strcmp(typeName, TypeName<long>::name()) == 0)
         return DefaultValueVariant<long>::value();
      if(strcmp(typeName, TypeName<unsigned long>::name()) == 0)
         return DefaultValueVariant<unsigned long>::value();
      if(strcmp(typeName, TypeName<float>::name()) == 0)
         return DefaultValueVariant<float>::value();
      if(strcmp(typeName, TypeName<double>::name()) == 0)
         return DefaultValueVariant<double>::value();
      if(strcmp(typeName, TypeName<long long>::name()) == 0)
         return DefaultValueVariant<long long>::value();
      if(strcmp(typeName, TypeName<unsigned long long>::name()) == 0)
         return DefaultValueVariant<unsigned long long>::value();
      if(strcmp(typeName, TypeName<const char*>::name()) == 0)
         return DefaultValueVariant<const char*>::value();
      if(strcmp(typeName, TypeName<void*>::name()) == 0)
         return DefaultValueVariant<void*>::value();
      if(strcmp(typeName, TypeName< std::list<std::string> >::name()) == 0)
         return DefaultValueVariant<ListTypePtr>::value();
      if(strcmp(typeName, TypeName< std::list< std::list< std::string > > >::name()) == 0)
         return DefaultValueVariant<ListTypePtr>::value();
      if(strstr(typeName, "std::list") != nullptr)
         return DefaultValueVariant<ListTypePtr>::value();

      //should be sufficient to test existance of '*'
      if(strchr(typeName, '*') != nullptr)
         return DefaultValueVariant<void*>::value();
   }

   return Variant();
}
