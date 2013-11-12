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


package ${packageName};
<#assign className = classInfo.name>

import org.trentino.trengen.xml.schema.*;

import java.lang.reflect.Field;
import java.util.List;

public class ${className} <#if classInfo.hasSuperclass()> extends ${classInfo.superClass.name}</#if> implements MirrorClass{


<#macro createFieldData fieldInfo>
<#if fieldInfo.isList()>
<#if fieldInfo.firstLikeString() >
       protected List<${fieldInfo.firstTypeParamAsJavaString}> m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural} = new java.util.ArrayList<${fieldInfo.firstTypeParamAsJavaString}>();
<#elseif fieldInfo.firstTypeParam =="BigInteger" >
       protected  List<Long> m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural} = new java.util.ArrayList<Long>();   
<#else>
       protected  List<${fieldInfo.firstTypeParam}> m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural} =new java.util.ArrayList<${fieldInfo.firstTypeParam}>();
</#if>      
<#elseif fieldInfo.isLikeNCName()>
       protected  org.trentino.trengen.xml.schema.${fieldInfo.typeName} m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};   
<#elseif fieldInfo.isBoolean()>
       protected  boolean mIs${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
<#elseif fieldInfo.isString()>
       protected  String m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
<#elseif fieldInfo.isInt()>
       protected  Integer m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
<#elseif fieldInfo.isInt64()>
       protected Long m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};       
<#else>
       protected  ${fieldInfo.typeName} m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
</#if>
</#macro> 

<#if className = "SCAPropertyBase">
 public  List<String> mContent =new java.util.ArrayList<String>();
 public List<String> content(){
        return mContent;
      }
</#if>

<#if classInfo.hasData() >
<#if classInfo.hasElements()>
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
<#macro createField fieldInfo>
<#if fieldInfo.isList()>
<#if fieldInfo.firstLikeString()>
     public List<${fieldInfo.firstTypeParamAsJavaString}> ${fieldInfo.name?uncap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}(){
          return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural};
      }
<#elseif fieldInfo.firstTypeParam == "BigInteger" >
       public List<Long> ${fieldInfo.name?uncap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}(){
          return m${fieldInfo.name}${fieldInfo.elementSuffix}${fieldInfo.plural};
      }    
<#else>
       public List<${fieldInfo.firstTypeParam}> ${fieldInfo.name?uncap_first}${fieldInfo.elementSuffix}${fieldInfo.plural}(){
        return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}${fieldInfo.plural};
      }
</#if>
<#elseif fieldInfo.isLikeNCName()>
       public org.trentino.trengen.xml.schema.${fieldInfo.typeName} ${fieldInfo.name}${fieldInfo.elementSuffix}(){
        return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
      }
      public  void set${fieldInfo.name?cap_first}(final org.trentino.trengen.xml.schema.${fieldInfo.typeName} ${fieldInfo.name}){
         m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = ${fieldInfo.name};
      }
<#elseif fieldInfo.isBoolean()>
      public  boolean is${fieldInfo.name?cap_first}${fieldInfo.elementSuffix}(){
        return mIs${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
      }
      public void set${fieldInfo.name?cap_first}(boolean is${fieldInfo.name?cap_first}){
       mIs${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = is${fieldInfo.name?cap_first};
      }
<#elseif fieldInfo.isString()>
      public  String ${fieldInfo.name}${fieldInfo.elementSuffix}(){
         return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
      }
      public  void set${fieldInfo.name?cap_first}(final String ${fieldInfo.name}){
          m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = ${fieldInfo.name};
      }
<#elseif fieldInfo.isInt()>
       public Integer ${fieldInfo.name}${fieldInfo.elementSuffix}(){
         return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
      }
       public void set${fieldInfo.name?cap_first}(Integer ${fieldInfo.name}){
        m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = ${fieldInfo.name};
      }
<#elseif fieldInfo.isInt64()>
      public  Long ${fieldInfo.name}${fieldInfo.elementSuffix}(){
         return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
      }
       public void set${fieldInfo.name?cap_first}(Long ${fieldInfo.name}){
         m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = ${fieldInfo.name};
      }     
<#else>
      public  ${fieldInfo.typeName} ${fieldInfo.name}${fieldInfo.elementSuffix}(){
          return m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix};
      }
      public  void set${fieldInfo.name?cap_first}(${fieldInfo.typeName?cap_first} ${fieldInfo.name?uncap_first}Arg){
          m${fieldInfo.name?cap_first}${fieldInfo.elementSuffix} = ${fieldInfo.name}Arg;
      }
</#if>
</#macro>

      //accessors
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

	protected MirrorSupport ms = new MirrorSupport(this);
	@Override
	public List<MirrorField> getFields() {
	  return ms.getFields();
	}
	
	public String getClassName(){
	 return "${className}";
	}
	
	protected String mNameGen = "deneme";
	public void setNameGen(String nameGenToSet)
	{
		mNameGen =nameGenToSet;
	}
	public String getNameGen()
	{
		return mNameGen;
	}
	
	
	public String getName() 
	{
	    return  ms.getName();
	}

	
	public java.lang.Object getFieldValue(Field field) {
		try {
			return field.get(this);
		} catch (Exception e) {
			throw new IllegalStateException(field.getName(),e);
		}
	}
}
 