#pragma warning(push)
#pragma warning(disable:4290 4512 4244)
#include "${context.nameGeneratedFile}BeanUtils.h"
#pragma warning(pop)

<#assign namespace = context.tidlInterfaceModel.namespace?replace(".","::")>

<#macro traceComplexType TIDLFieldModel>
<#assign tmapper=context.tmapper>
<#assign pbtmapper=context.pbtmapper>
<#assign qname = TIDLFieldModel.namespace+"::"+TIDLFieldModel.name>
<#assign pbType = pbtmapper.qName(TIDLFieldModel)>
<#if TIDLFieldModel.enumeration>
  switch(pbObject){
  <#foreach field in TIDLFieldModel.fields>
  <#assign fName = pbtmapper.enumName(field)>
  <#assign fName = pbtmapper.trimEnumName(TIDLFieldModel,pbType,fName)>
  <#assign fName2 = pbtmapper.trimEnumName2(TIDLFieldModel,qname,field.name)>
  case ${fName}:
       { 
           object=${fName2};
           break;
       }
  </#foreach>
  }
<#else>
<#foreach field in TIDLFieldModel.fields>
<#assign name=tmapper.name(field.getType())/>
<#assign ftName=pbtmapper.qName(field.getType())/>
<#assign j = name?index_of("string")>
<#assign i = name?index_of("char*")>
<#if field.type.enumeration>
	if (pbObject.has_${field.name?lower_case}())
	{
		const ${ftName}& m_pb = pbObject.${field.name?lower_case}();
		${field.type.namespace}::${field.type.name} m;
		copyProperties(m_pb, m);
		object.set_${field.name}(m);
	}
<#elseif tmapper.isComplexType(field.getType())==true && j== -1 && i==-1>
	if (pbObject.has_${field.name?lower_case}())
	{
		const ${ftName}& m_pb = pbObject.${field.name?lower_case}();
		${field.type.namespace}::${field.type.name}& m =object.mutable_${field.name}();
		copyProperties(m_pb, m);
	}
<#else>
	object.set_${field.name}(pbObject.${field.name?lower_case}());
</#if>
</#foreach>
</#if>
</#macro>

<#macro tracePBComplexType TIDLFieldModel>
<#assign qname = TIDLFieldModel.namespace+"::"+TIDLFieldModel.name>
<#assign pbType = pbtmapper.qName(TIDLFieldModel)>
<#if TIDLFieldModel.enumeration>
  switch(object){
  <#foreach field in TIDLFieldModel.fields>
  <#assign fName = pbtmapper.enumName(field)>
  <#assign fName = pbtmapper.trimEnumName(TIDLFieldModel,pbType,fName)>
  <#assign fName2 = pbtmapper.trimEnumName2(TIDLFieldModel,qname,field.name)>
  case ${fName2}: 
       { 
         *pbObject=${fName};
          break;
       }
  </#foreach>
  }
<#else>
<#foreach field in TIDLFieldModel.fields>
<#assign ftName=pbtmapper.qName(field.getType())/>
<#assign name=tmapper.name(field.getType())/>
<#assign j = name?index_of("string")>
<#assign i = name?index_of("char*")>
<#if field.type.enumeration>
	{
		${ftName} m_pb;
		${field.type.namespace}::${field.type.name} m =object.${field.name}();
		copyProperties(m, &m_pb);
		pbObject->set_${field.name?lower_case}(m_pb);
	}
<#elseif tmapper.isComplexType(field.getType())==true && j== -1 && i==-1>
	if (object.has_${field.name}())
	{
		${ftName}* m_pb = pbObject->mutable_${field.name?lower_case}();
		const ${field.type.namespace}::${field.type.name}& m =object.${field.name}();
		copyProperties(m, m_pb);
	}
<#else>
	pbObject->set_${field.name?lower_case}(object.${field.name}());
</#if>
</#foreach>
</#if>
</#macro>

<#foreach aType in context.tidlInterfaceModel.allComplexTypes>
<#assign qname = aType.namespace+"::"+aType.name>
<#assign pbType = pbtmapper.qName(aType)>
void ${namespace}::${context.className}BeanUtils::copyProperties(const ${pbType}& pbObject, ${qname}& object)
{
<@traceComplexType TIDLFieldModel = aType></@traceComplexType>
}

void ${namespace}::${context.className}BeanUtils::copyProperties(const ${qname}& object, ${pbType}* pbObject)
{
<@tracePBComplexType TIDLFieldModel = aType></@tracePBComplexType>
}

</#foreach>

${namespace}::${context.className}BeanUtils::${context.className}BeanUtils() {}
${namespace}::${context.className}BeanUtils::~${context.className}BeanUtils() {}
