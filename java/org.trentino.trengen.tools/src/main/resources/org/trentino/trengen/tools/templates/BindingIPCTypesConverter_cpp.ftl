#pragma warning(push)
#pragma warning(disable:4290 4512 4244)
#include "TrentinoGenIPCTypesConverter.h"
#pragma warning(pop)

<#foreach ref in remotableReferences>
<#assign IPCnamespace = "">
<#foreach part in ref.tidlInterfaceModel.nameSpaceParts>
<#assign IPCnamespace = IPCnamespace + part+"::" >
</#foreach> 
<#assign namespace = ref.tidlInterfaceModel.namespace?replace(".","::")>

<#macro traceComplexType TIDLFieldModel>
<#assign qname = TIDLFieldModel.namespace+"::"+TIDLFieldModel.name>
<#assign pbType = tmapper.name(TIDLFieldModel)>
<#if TIDLFieldModel.enumeration>
  switch(ipcObject){
  <#foreach field in TIDLFieldModel.fields>
  <#assign fName = tmapper.enumName(field)>
  <#assign fName = tmapper.trimEnumName(TIDLFieldModel,pbType,fName)>
  <#assign fName2 = tmapper.trimEnumName2(TIDLFieldModel,qname,field.name)>
  case ${fName}:
       { 
          *object=${fName2};
           break;
       }
  </#foreach>
  }
<#else>
<#foreach field in TIDLFieldModel.fields>
<#assign name=tmapper.name(field.getType())/>
<#assign ftName=tmapper.name(field.getType())/>
<#assign j = name?index_of("string")>
<#assign i = name?index_of("char*")>
<#if field.type.enumeration>
	if (ipcObject->has_${field.name?lower_case}())
	{
		${ftName}& m_pb = ipcObject->${field.name?lower_case}();
		${field.type.namespace}::${field.type.name} m;
		copyProperties(m_pb, &m);
		object->set_${field.name}(m);
	}
<#elseif tmapper.isComplexType(field.getType())==true && j== -1 && i==-1>
	if (ipcObject->has_${field.name?lower_case}())
	{
		${IPCnamespace}IPC${field.type.className}* m_pb = ipcObject->${field.name?lower_case}().get();
		${field.type.namespace}::${field.type.name}& m =object->mutable_${field.name}();
		copyProperties(m_pb, &m);
	}
<#else>
	object->set_${field.name}(ipcObject->${field.name?lower_case}());
</#if>
</#foreach>
</#if>
</#macro>

<#macro tracePBComplexType TIDLFieldModel>
<#assign qname = TIDLFieldModel.namespace+"::"+TIDLFieldModel.name>
<#assign pbType = tmapper.name(TIDLFieldModel)>
<#if TIDLFieldModel.enumeration>
  switch(object){
  <#foreach field in TIDLFieldModel.fields>
  <#assign fName = tmapper.enumName(field)>
  <#assign fName = pbtmapper.trimEnumName(TIDLFieldModel,pbType,fName)>
  <#assign fName2 = pbtmapper.trimEnumName2(TIDLFieldModel,qname,field.name)>
  case ${fName2}: 
       { 
         *ipcObject=${fName};
          break;
       }
  </#foreach>
  }
<#else>
<#foreach field in TIDLFieldModel.fields>
<#assign ftName=tmapper.name(field.getType())/>
<#assign name=tmapper.name(field.getType())/>
<#assign j = name?index_of("string")>
<#assign i = name?index_of("char*")>
<#if field.type.enumeration>
	{
		//ali
		${IPCnamespace}IPC${field.type.className} m_pb;

		${field.type.namespace}::${field.type.name} m =object.${field.name}();
		copyProperties(m, &m_pb);
		ipcObject->set_${field.name?lower_case}(m_pb);
	}
<#elseif tmapper.isComplexType(field.getType())==true && j== -1 && i==-1>
	if (object.has_${field.name}())
	{
		//copy complex type
		//${IPCnamespace}IPC${field.type.className}* m_pb = ipcObject->${field.name?lower_case}().get();
		//const ${field.type.namespace}::${field.type.name}& m =object.${field.name}();
		//copyProperties(m, m_pb);
		copyProperties(object.${field.name}(), ipcObject->${field.name?lower_case}());
	}
<#else>
	ipcObject->set_${field.name?lower_case}(object.${field.name}());
</#if>
</#foreach>
</#if>
</#macro>

<#foreach aType in ref.tidlInterfaceModel.allComplexTypes>
<#assign qname = aType.namespace+"::"+aType.name>
<#assign pbType = tmapper.name(aType)>
void ${namespace}::${ref.className}IPCBeanUtils::copyProperties(<#foreach part in ref.tidlInterfaceModel.nameSpaceParts>${part}::</#foreach>IPC${aType.name}* ipcObject, ${qname}* object) // from ipc to normal
{
<@traceComplexType TIDLFieldModel = aType></@traceComplexType>
}

void ${namespace}::${ref.className}IPCBeanUtils::copyProperties(const ${qname}& object, <#foreach part in ref.tidlInterfaceModel.nameSpaceParts>${part}::</#foreach>IPC${aType.name}* ipcObject)
{
<@tracePBComplexType TIDLFieldModel = aType></@tracePBComplexType>
}

void ${namespace}::${ref.className}IPCBeanUtils::copyProperties(const ${qname}& object, boost::interprocess::offset_ptr<IPC${aType.name}>& ipcObject)
{
<@tracePBComplexType TIDLFieldModel = aType></@tracePBComplexType>
}
</#foreach>

${namespace}::${ref.className}IPCBeanUtils::${ref.className}IPCBeanUtils() {}
${namespace}::${ref.className}IPCBeanUtils::~${ref.className}IPCBeanUtils() {}

</#foreach>
