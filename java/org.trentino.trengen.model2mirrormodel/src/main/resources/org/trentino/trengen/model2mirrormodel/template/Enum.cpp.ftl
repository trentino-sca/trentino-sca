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

<#assign className = classInfo.name>
<#assign classPrefix = "TrentinoSCAModel" >
//header
#include "${classPrefix}${className}.h"

//standard
#include <cassert>
#include <utility>

using Trentino::SCA::Model::${className};
using namespace std;

//class ${className}
   //static member initialization
${className}::ValueMap ${className}::mValueMap = 
   ${className}::createValueMap();

  
   //construction
${className}::${className}(const string& valueStr)
: mValue(mValueMap[valueStr])
{}

   //services
string ${className}::toString() const
{   
   for( ValueMap::const_iterator it = mValueMap.begin();
        it != mValueMap.end();
        ++it)
   {
      if(it->second == mValue)
         return it->first;
   }

   assert(false);
   return "";
}

   //management
${className}::ValueMap ${className}::createValueMap()
{
   ValueMap valueMap;
<#foreach fieldInfo in classInfo.fieldInfos>
   valueMap.insert(make_pair("${fieldInfo.name}", ${fieldInfo.name?cap_first}));
</#foreach>   
   return valueMap;
}