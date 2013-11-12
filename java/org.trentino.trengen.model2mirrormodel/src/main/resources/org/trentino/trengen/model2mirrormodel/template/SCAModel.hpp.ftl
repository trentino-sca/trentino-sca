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
<#assign macroName = classPrefix+classInfo.name+"H">
#ifndef ${macroName}
#define ${macroName}
<#if classInfo.hasSuperclass()>
//baseclass
#include "${classPrefix}${classInfo.superClass.name}.h"
</#if>
<#if classInfo.hasJavaList()>
//standard
#include <vector>
</#if>

//specific
#include "TrentinoSCAModel.h"

 
namespace Trentino{
namespace SCA{
namespace Model
{
   class ${className}<#if classInfo.hasSuperclass()> : public ${classInfo.superClass.name}</#if>
   {
      //construction
   public:
      <#if className=="Metadata" || className=="MetadataStringAttribute">SCAMODEL_IMPORT_EXPORT </#if> ${className}();
   private:
      ${className}(const ${className}&);
      void operator=(const ${className}&);

      //services
   public:
<#if classInfo.isExtentionPoint()>
      const Trentino::XML::Schema::QName& xsdType() const;
</#if>    
<#macro createField fieldInfo>
<#if fieldInfo.isList()>
<#if fieldInfo.firstLikeString()>
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  add${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}(const char* a${fieldInfo.name?cap_first});
     const std::vector<${fieldInfo.firstTypeParam}>& ${fieldInfo.name?uncap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}() const;
<#elseif fieldInfo.firstTypeParam == "BigInteger" >
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  add${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}(${fieldInfo.firstTypeParamFull}* a${fieldInfo.name?cap_first});
     const std::vector<int64_t>& ${fieldInfo.name?uncap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}() const;      
<#else>
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  add${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}(${fieldInfo.firstTypeParamFull}* a${fieldInfo.name?cap_first});
     const std::vector<${fieldInfo.firstTypeParam}Ptr>& ${fieldInfo.name?uncap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}() const;

</#if>
<#elseif fieldInfo.isLikeNCName()>
      const Trentino::XML::Schema::${fieldInfo.typeName}& ${fieldInfo.name}${fieldInfo.elementSuffix}() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  set${fieldInfo.name?cap_first}(const char* a${fieldInfo.name?cap_first});
<#elseif fieldInfo.isBoolean()>
      bool is${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  set${fieldInfo.name?cap_first}(bool is${fieldInfo.name?cap_first});
<#elseif fieldInfo.isString()>
      const std::string& ${fieldInfo.name}${fieldInfo.elementSuffix}() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  set${fieldInfo.name?cap_first}(const char* a${fieldInfo.name?cap_first});
<#elseif fieldInfo.isInt()>
      int ${fieldInfo.name}${fieldInfo.elementSuffix}() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  set${fieldInfo.name?cap_first}(int a${fieldInfo.name?cap_first});
<#elseif fieldInfo.isInt64()>
      int64_t ${fieldInfo.name}${fieldInfo.elementSuffix}() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  set${fieldInfo.name?cap_first}(int64_t a${fieldInfo.name?cap_first});        
<#else>
      ${fieldInfo.typeName}Ptr ${fieldInfo.name}${fieldInfo.elementSuffix}() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  set${fieldInfo.name?cap_first}(${fieldInfo.typeNameFull?cap_first}* a${fieldInfo.name?cap_first});
</#if>
</#macro>


<#if classInfo.hasElements()>

      //element accessors  
<#foreach fieldInfo in classInfo.fieldInfos>
<#if fieldInfo.isElement()>
<@createField fieldInfo=fieldInfo ></@createField>
</#if>
</#foreach>     
</#if>

<#if classInfo.hasAttributes()>
      //attribute accessors
<#foreach fieldInfo in classInfo.fieldInfos>
<#if fieldInfo.isElement()==false>
<@createField fieldInfo=fieldInfo ></@createField>
</#if>
</#foreach>
</#if>
<#macro createFieldData fieldInfo>
<#if fieldInfo.isList()>
<#if fieldInfo.firstLikeString() >
      std::vector<${fieldInfo.firstTypeParam}> m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural};
<#elseif fieldInfo.firstTypeParam =="BigInteger" >
      std::vector<int64_t> m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural};      
<#else>
      std::vector<${fieldInfo.firstTypeParam}Ptr> m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural};
</#if>      
<#elseif fieldInfo.isLikeNCName()>
      Trentino::XML::Schema::${fieldInfo.typeName} m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};   
<#elseif fieldInfo.isBoolean()>
      bool mIs${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
<#elseif fieldInfo.isString()>
      std::string m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
<#elseif fieldInfo.isInt()>
      int m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
<#elseif fieldInfo.isInt64()>
      int64_t m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};       
<#else>
      ${fieldInfo.typeName}Ptr m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
</#if>
</#macro>


<#if classInfo.hasData() || classInfo.isExtentionPoint()>
      //data
   protected:
 <#if classInfo.isExtentionPoint()>
	  QNamePtr mXSDType;
</#if>
<#if classInfo.hasElements()>
      //elements
<#foreach fieldInfo in classInfo.fieldInfos>
<#if fieldInfo.isElement()>
<@createFieldData fieldInfo=fieldInfo ></@createFieldData>
</#if>
</#foreach>       
 </#if>
 
 <#if classInfo.hasAttributes()>
      //attributes
<#foreach fieldInfo in classInfo.fieldInfos>
<#if fieldInfo.isElement()==false>
<@createFieldData fieldInfo=fieldInfo ></@createFieldData>
</#if>
</#foreach>       
 </#if>
</#if>   
   }; //class  ${className}

<#if classInfo.hasAccessors()>
   #include "${classPrefix}${className}.inl"   
</#if>

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //${macroName}
 