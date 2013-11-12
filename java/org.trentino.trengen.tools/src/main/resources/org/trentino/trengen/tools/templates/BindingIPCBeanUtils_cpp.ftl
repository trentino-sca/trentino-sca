#pragma warning(push)
#pragma warning(disable:4290 4512 4244)
#include "TrentinoGenIPCBeanUtils.h"
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
  switch(pbObject){
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
	if (pbObject->has_${field.name?lower_case}())
	{
		${ftName}& m_pb = pbObject->${field.name?lower_case}();
		${field.type.namespace}::${field.type.name} m;
		copyProperties(m_pb, &m);
		object->set_${field.name}(m);
	}
<#elseif tmapper.isComplexType(field.getType())==true && j== -1 && i==-1>
	if (pbObject->has_${field.name?lower_case}())
	{
		${IPCnamespace}IPC${field.type.className}* m_pb = pbObject->${field.name?lower_case}().get();
		${field.type.namespace}::${field.type.name}* m =object->mutable_${field.name}();
		copyProperties(m_pb, m);
	}
<#else>
	object->set_${field.name}(pbObject->${field.name?lower_case}());
</#if>
</#foreach>
</#if>
</#macro>

<#foreach aType in ref.tidlInterfaceModel.allComplexTypes>
<#assign qname = aType.namespace+"::"+aType.name>
<#assign pbType = tmapper.name(aType)>
void ${namespace}::${ref.className}IPCBeanUtils::copyProperties(<#foreach part in ref.tidlInterfaceModel.nameSpaceParts>${part}::</#foreach>IPC${aType.name}* pbObject, ${qname}* object) // from ipc to normal
{
<@traceComplexType TIDLFieldModel = aType></@traceComplexType>
}

</#foreach>

${namespace}::${ref.className}IPCBeanUtils::${ref.className}IPCBeanUtils() {}
${namespace}::${ref.className}IPCBeanUtils::~${ref.className}IPCBeanUtils() {}

</#foreach>
