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
//class ${className}
   //services 
<#if classInfo.isExtentionPoint()>

inline const Trentino::XML::Schema::QName& ${className}::xsdType() const
{
   return *mXSDType;
}

</#if>    
<#macro createInline fieldInfo>
<#if fieldInfo.isList()>
<#if fieldInfo.firstLikeString()>

inline const std::vector<${fieldInfo.firstTypeParam}>& ${className}::${fieldInfo.name?uncap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}() const
{
  return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural};
}
<#elseif  fieldInfo.firstTypeParam == "BigInteger" >

inline const std::vector<int64_t>& ${className}::${fieldInfo.name?uncap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}() const
{
  return m${fieldInfo.name}${fieldInfo.elementSuffix}${fieldInfo.plural};
}

<#else>
inline const std::vector<${fieldInfo.firstTypeParam}Ptr>& ${className}::${fieldInfo.name?uncap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}() const
{
  return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural};
}

</#if>
<#elseif fieldInfo.isLikeNCName()>

inline const Trentino::XML::Schema::${fieldInfo.typeName}& ${className}::${fieldInfo.name}${fieldInfo.elementSuffix}() const
{
   return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
}

<#elseif fieldInfo.isBoolean()>

inline bool ${className}::is${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}() const
{
   return mIs${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
}

<#elseif fieldInfo.isString()>

inline const std::string& ${className}::${fieldInfo.name}${fieldInfo.elementSuffix}() const
{
   return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
}

<#elseif fieldInfo.isInt()>

inline int ${className}::${fieldInfo.name}${fieldInfo.elementSuffix}() const
{
   return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
}

<#elseif fieldInfo.isInt64()>

inline int64_t ${className}::${fieldInfo.name}${fieldInfo.elementSuffix}() const
{
   return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
}

<#elseif fieldInfo.isQName()>

inline QNamePtr ${className}::${fieldInfo.name}${fieldInfo.elementSuffix}() const
{
   return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
}

<#else>

inline ${fieldInfo.typeName}Ptr ${className}::${fieldInfo.name}${fieldInfo.elementSuffix}() const
{
   return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
}
</#if>
</#macro>
<#foreach fieldInfo in classInfo.fieldInfos>
<@createInline fieldInfo=fieldInfo ></@createInline>
</#foreach>


 