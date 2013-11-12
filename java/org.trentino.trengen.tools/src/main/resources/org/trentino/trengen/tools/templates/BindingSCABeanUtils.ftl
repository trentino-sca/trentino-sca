<#macro fpmod arg><#if !arg.hasOut && !arg.hasInOut>const</#if></#macro>
<#-- generate the reference modifier for the  parameter e.g & if necessary -->
<#macro refmod arg><#if arg.complexType>&</#if></#macro>
#ifndef ${context.nameGeneratedFile}BeanUtilsH
#define ${context.nameGeneratedFile}BeanUtilsH

#include "${context.nameGeneratedFile}ProbobufMessages.h"
#include "${context.headerFilenamePrefix}.h"


<#foreach part in context.tidlInterfaceModel.nameSpaceParts>
namespace ${part}{
</#foreach>
<#assign tidlInterfaceModel=context.tidlInterfaceModel>
class ${context.className}BeanUtils {
  //construction
	public:
	${context.className}BeanUtils();
	~${context.className}BeanUtils();
	//services
	public:
<#assign namespace = "protobuf::"+context.tidlInterfaceModel.namespace?replace(".","::")>
<#foreach aType in context.tidlInterfaceModel.allComplexTypes>
    <#assign qname = aType.namespace+"::"+aType.name>
    <#assign pbType = pbtmapper.qName(aType)>
	static void copyProperties(const ${pbType}& pbObject, ${qname}& object);
	static void copyProperties(const ${qname}& object, ${pbType}* pbObject);
</#foreach>

};//class ${context.className}BeanUtils
 
<#foreach part in context.tidlInterfaceModel.nameSpaceParts>
} //namespace ${part}
</#foreach>
#endif ${context.nameGeneratedFile}BeanUtilsH