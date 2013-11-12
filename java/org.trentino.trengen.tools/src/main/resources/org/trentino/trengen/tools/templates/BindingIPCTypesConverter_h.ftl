<#macro fpmod arg><#if !arg.hasOut && !arg.hasInOut>const</#if></#macro>
<#-- generate the reference modifier for the  parameter e.g & if necessary -->
<#macro refmod arg><#if arg.complexType>&</#if></#macro>
#ifndef TrentinoGenIPCTypesConverterH
#define TrentinoGenIPCTypesConverterH

#include "TrentinoGenIPCTypes.h"

<#foreach ref in remotableReferences>
<#foreach part in ref.tidlInterfaceModel.nameSpaceParts>
namespace ${part}{
</#foreach>
<#assign tidlInterfaceModel=ref.tidlInterfaceModel>
class ${ref.className}IPCBeanUtils {
  //construction
	public:
	${ref.className}IPCBeanUtils();
	~${ref.className}IPCBeanUtils();
	//services
	public:
<#assign namespace = "protobuf::"+ref.tidlInterfaceModel.namespace?replace(".","::")>
<#foreach aType in ref.tidlInterfaceModel.allComplexTypes>
    <#assign qname = aType.namespace+"::"+aType.name>
    <#assign pbType = tmapper.name(aType)>
	static void copyProperties(<#foreach part in ref.tidlInterfaceModel.nameSpaceParts>${part}::</#foreach>IPC${aType.name}* pbObject, ${qname}* object); // from ipc to normal
	static void copyProperties(const ${qname}& object, <#foreach part in ref.tidlInterfaceModel.nameSpaceParts>${part}::</#foreach>IPC${aType.name}* ipcObject);
	static void copyProperties(const ${qname}& object, boost::interprocess::offset_ptr<IPC${aType.name}>& ipcObject);
	
</#foreach>

};//class ${ref.className}IPCBeanUtils
 
<#foreach part in ref.tidlInterfaceModel.nameSpaceParts>
} //namespace ${part}
</#foreach>
</#foreach>
#endif TrentinoGenIPCTypesConverterH