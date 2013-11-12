<#import "CppInterface.ftl" as util>
#ifndef ${context.nameGeneratedFile}BINDINGPROXYH
#define ${context.nameGeneratedFile}BINDINGPROXYH

#include <${context.nameGeneratedFile}Request.pb.h>
#include <${context.nameGeneratedFile}Response.pb.h>
//#include <${context.filename}.h>

<#foreach part in context.tidlInterfaceModel.nameSpaceParts>
namespace ${part}{
</#foreach>
namespace protobuf{

class Mapper{
  //construction
	public:
	Mapper();
	virtual ~Mapper();
	//services
	public:
  <#assign nspace=""/>
  <#foreach part in context.tidlInterfaceModel.nameSpaceParts>
  <#if nspace=="">
     <#assign nspace=part/>
   <#else>
       <#assign nspace=nspace+"::"+part/>
  </#if>
  </#foreach>
  <#assign nspace=nspace+"::protobuf"/>
  
<#foreach method in context.tidlInterfaceModel.functions>
	static ${nspace}::${context.tidlInterfaceModel.name}Request_${method.name}Request create${method.name?cap_first}Request(<#list method.arguments as x><@util.fpmod arg=x/> ${tmapper.name(x.type)}<@util.refmod arg=x.type/> ${x.name}<#if x_has_next>,</#if></#list>);
	static ${nspace}::${context.tidlInterfaceModel.name}Response_${method.name}Response create${method.name?cap_first}Response(<#list method.returnArguments as x>const ${tmapper.name(x.type)}<@util.refmod arg=x.type/> ${x.name}<#if x_has_next>,</#if></#list>);
</#foreach>
    template <typename Response>
    static Response* parseResponse(const compact_soap::Soap& soapResponse){
	    Response* resp = new Response();
	    compact_soap::Soap_Envelope envelope = soapResponse.envelope();
	    compact_soap::Soap_Body body = envelope.body();
	    const std::string content= body.content();
	    resp->ParseFromString(content);
	    return resp;
    }
};//class Mapper

<#foreach part in context.tidlInterfaceModel.nameSpaceParts>
} //namespace ${part}
</#foreach>
} //protobuf
#endif ${context.nameGeneratedFile}BINDINGPROXYH