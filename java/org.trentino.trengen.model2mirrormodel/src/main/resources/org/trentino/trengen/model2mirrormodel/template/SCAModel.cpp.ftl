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
<#assign classPrefix = "TrentinoSCAModel" >
//standard
#include <cassert>
#include <utility>
#include <stdexcept>

//header
<#foreach classInfo in classes>
#include "${classPrefix}${classInfo.name}.h"
</#foreach>

using namespace Trentino::SCA::Model;
using Trentino::XML::Schema::QName;
using namespace std;
<#foreach classInfo in classes>
<#if classInfo.isExtentionPoint()>

<#foreach subclassInfo in classInfo.subClasses >
//!brief deleter for class ${subclassInfo.name}
void deleter${subclassInfo.name}(${classInfo.name}* a${classInfo.name})
{
   ${subclassInfo.name}* const my${subclassInfo.name} = static_cast<${subclassInfo.name}*>(a${classInfo.name});
   delete my${subclassInfo.name};
}

</#foreach>
</#if> 
</#foreach>
<#foreach classInfo in classes>
<#assign className = classInfo.name>


//Class implementation
//************************************************************************************************************
//                                    ${className}
//************************************************************************************************************
<#if classInfo.enum>
	//static member initialization
	${className}::ValueMap ${className}::mValueMap = ${className}::createValueMap();

  
   //construction
	${className}::${className}(const string& valueStr): mValue(mValueMap[valueStr]){}

    //services
	string ${className}::toString() const
	{   
	   for( ValueMap::const_iterator it = mValueMap.begin();
	        it != mValueMap.end(); ++it)
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
<#else>
   //construction
${className}::${className}()
      {
<#if classInfo.isExtentionPoint()||classInfo.isSubClassOfExtentionPoint()>
	       mXSDType.reset(new QName("${className}", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
</#if>
      }

   //services
<#macro createField fieldInfo>
<#if fieldInfo.isList()>
<#if fieldInfo.firstLikeString()>
       void TRENTINO_STDCALL  ${className}::add${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}(const char* a${fieldInfo.name?cap_first}){
           //std::vector<${fieldInfo.firstTypeParam}> m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural};
           m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}.push_back(a${fieldInfo.name?cap_first});
       }
<#elseif fieldInfo.firstTypeParam == "BigInteger" >
       void TRENTINO_STDCALL  ${className}::add${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}(${fieldInfo.firstTypeParamFull}* a${fieldInfo.name?cap_first}){
        //std::vector<int64_t> m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural};
        m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}.push_back(a${fieldInfo.name?cap_first});
       }
<#else>
       void TRENTINO_STDCALL  ${className}::add${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}(${fieldInfo.firstTypeParamFull}* a${fieldInfo.name?cap_first}){
         m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}.push_back(${fieldInfo.firstTypeParam}Ptr(a${fieldInfo.name?cap_first}));
       }
</#if>
<#elseif fieldInfo.isLikeNCName()>
       void TRENTINO_STDCALL  ${className}::set${fieldInfo.name?cap_first}(const char* a${fieldInfo.name?cap_first}){
            m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = a${fieldInfo.name?cap_first};
       }
       
<#elseif fieldInfo.isBoolean()>
       void TRENTINO_STDCALL  ${className}::set${fieldInfo.name?cap_first}(bool is${fieldInfo.name?cap_first}){
         mIs${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = is${fieldInfo.name?cap_first};
      }
      
<#elseif fieldInfo.isString()>
       void TRENTINO_STDCALL  ${className}::set${fieldInfo.name?cap_first}(const char* a${fieldInfo.name?cap_first}){
         m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = a${fieldInfo.name?cap_first};
      }
      
<#elseif fieldInfo.isInt()>
       void TRENTINO_STDCALL  ${className}::set${fieldInfo.name?cap_first}(int a${fieldInfo.name?cap_first}){
       m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = a${fieldInfo.name?cap_first};
      }
      
<#elseif fieldInfo.isInt64()>
       void TRENTINO_STDCALL  ${className}::set${fieldInfo.name?cap_first}(int64_t a${fieldInfo.name?cap_first}){
        m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = a${fieldInfo.name?cap_first};
      } 
<#elseif fieldInfo.isQName()>
	 void TRENTINO_STDCALL  ${className}::set${fieldInfo.name?cap_first}(Trentino::XML::Schema::QName* a${fieldInfo.name?cap_first}){
		   m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} =QNamePtr(a${fieldInfo.name?cap_first});
		}
<#elseif context.isExtentionPoint(fieldInfo.typeNameFull)==true>
     void  TRENTINO_STDCALL  ${className}::set${fieldInfo.name?cap_first}(${fieldInfo.typeNameFull?cap_first}* a${fieldInfo.name?cap_first}){
     <#assign fname= fieldInfo.name?cap_first/>
     <#assign fieldClassInfo = context.getClassInfo(fieldInfo.typeNameFull) />
     <#foreach subclassInfo in fieldClassInfo.subClasses >
       if(a${fname}->xsdType().localPart() == "${subclassInfo.name}")
       {
          m${fname}${fieldInfo.elementSuffix} = ${fieldInfo.typeNameFull}Ptr(a${fname},deleter${subclassInfo.name});
          return;
       }	
	 </#foreach>
        throw std::runtime_error("unknown type of implementation!");
       }
<#else>
     void  TRENTINO_STDCALL  ${className}::set${fieldInfo.name?cap_first}(${fieldInfo.typeNameFull?cap_first}* a${fieldInfo.name?cap_first}){
          m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = ${fieldInfo.typeNameFull}Ptr(a${fieldInfo.name?cap_first});
       }
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
</#if>
</#foreach>
