    <#macro findArgumentIndexForReturnType returnTypeName func argumentIndex>
        
        <#foreach argument in func.arguments>
            in findArg 
            ${argument.name}
            ${argumentIndex}
            <#if argument.name == returnTypeName>
            //indexxxx ${argumentIndex}
            </#if>
            <#assign argumentIndex = argumentIndex + 1>
            ----${argumentIndex}
        </#foreach>
    </#macro>
    
    // ****************************************************************************
    // Generated by Trengen. Do not modify
    // **************************************************************************** 
    #include "TrentinoGenProxiesWrappers.h"
    #pragma warning(push)
    #pragma warning(disable:4290)
    #include "TrentinoGenSCABindingHelpers.h"
    #pragma warning(pop)
    <#foreach protoBufContext in context.protoBufContexts>
    #include "${protoBufContext.nameGeneratedFile}ProbobufMessages.h"
    </#foreach>
    using namespace Trentino::Gen;
    using namespace Trentino::Binding::SCA;
    
    namespace
    {
    
    void setBodyContent(trentino::bindingsca::csoap::Soap& response, std::string& serializedResponse)
        {
            ::trentino::bindingsca::csoap::Soap_Envelope* env = response.mutable_envelope();
            if(!env->has_body())
            {
                ::trentino::bindingsca::csoap::Soap_Body* body  = env->mutable_body();
                body->set_content(serializedResponse);
            }
            else
            {
                ::trentino::bindingsca::csoap::Soap_Body body= env->body();
                body.set_content(serializedResponse);
             }
        
        }
    
    }
    
    <#foreach protoBufContext in context.protoBufContexts>
    <#assign model=protoBufContext.tidlInterfaceModel >
    <#assign pbtmapper=protoBufContext.pbtmapper>
    <#assign className = protoBufContext.namespace + "_" + protoBufContext.className + "_" + "SCABindingHelper">
        <#assign namespace = protoBufContext.tidlInterfaceModel.namespace?replace(".","::")>
        <#assign namespaceProto = namespace + "::protobuf">
    //----------------------------------------------------------------------------------
    // Binding helper for class ${className}
    //----------------------------------------------------------------------------------
        ${className}::${className}(){}
        ${className}::~${className}(){}
        
        const FaultDetailBuilderPtr ${className}::getFaultBuilder()const
        {
            FaultDetailBuilderPtr emptyVal;
            return emptyVal;
        }
    
    
        void ${className}::serializeResponse(const Trentino::Invocation::InvocationData& invocationData,
                                            void* retParam,
                                            trentino::bindingsca::csoap::Soap& response, 
                                            Trentino::RuntimeModel::ErrorCode& /*ec*/ )const
        {
            <#if protoBufContext.hasBeanUtils()>
            <#foreach part in protoBufContext.tidlInterfaceModel.nameSpaceParts>${part}::</#foreach>${protoBufContext.className}BeanUtils util;
            </#if>
            <#foreach function in protoBufContext.tidlInterfaceModel.functions>
    
                <#assign methodName = function.methodId>
                <#assign methodName = methodName?lower_case>
                <#assign response = methodName + "_response">
            if(invocationData.operation() == "${function.methodId}")
            {
                  protobuf::${namespace}::${model.name}::${model.name}Response_${function.methodId}Response ${response};
                  <#assign argumentIndex = 0>
                <#if   !function.returnType.void>
                  {
                   <#if function.returnType.primitive>
                    <#assign primitiveType = tmapper.name(function.returnType)>
                      ${primitiveType}* argResponse = (${primitiveType}*) retParam;
                      ${response}.set_${methodName}response(*argResponse);
                   <#else>
                        <#assign tn=function.returnType.qualifiedName?replace(".","::")>
                      ${tn}* argResponse = (${tn}*) retParam;
                      ${pbtmapper.qName(function.returnType)}*    pb_argResponse = ${response}.mutable_${methodName}response();
                      util.copyProperties(*argResponse,pb_argResponse);
                   </#if>
                  }
                </#if>
                <#assign argumentIndex = 0>
                <#foreach returnArg in function.arguments>
                    <#if returnArg.isHasOut() || returnArg.isHasInOut()>
                        <#if returnArg.type.void>
                        <#elseif returnArg.type.primitive>
                            <#assign primitiveType = tmapper.name(returnArg.type)>
                 {
                    void* retParam =  invocationData.parameters()[${argumentIndex}];
                    ${primitiveType}* argResponse = (${primitiveType}*) retParam;
                    ${response}.set_${methodName}response(*argResponse);
                 }
                <#else>
                 {
                    ${pbtmapper.qName(returnArg.type)}*    pb_argResponse = ${response}.mutable_${returnArg.name}();
                    void* retParam =  invocationData.parameters()[${argumentIndex}];
                    <#assign tn=returnArg.type.qualifiedName?replace(".","::")>
                    ${tn}* argResponse = (${tn}*) retParam;
                    util.copyProperties(*argResponse,pb_argResponse);
                 }
                        </#if>
                    </#if>
            <#assign argumentIndex = argumentIndex +1>
            </#foreach>
                 std::string serializedResponse;
                 ${response}.SerializeToString(&serializedResponse);
                 setBodyContent(response,serializedResponse);
            }
            </#foreach>
        }
    
    
        void ${className}::invoke( SCABindingHelper::InvokeCallback callback, void* handler,
          Trentino::Invocation::InvocationData& invocationData,
        const Trentino::RuntimeModel::ServiceBasePtr& runtimeServicePtr, 
          Trentino::Invocation::InvocationContext& invocationContext,
          trentino::bindingsca::csoap::Soap& request,
          trentino::bindingsca::csoap::Soap& response,
          Trentino::RuntimeModel::ErrorCode& ec )
        {
    
           <#if protoBufContext.hasBeanUtils()>
            <#foreach part in protoBufContext.tidlInterfaceModel.nameSpaceParts>${part}::</#foreach>${protoBufContext.className}BeanUtils util;
        </#if>
        <#foreach function in model.functions>
        if(invocationData.operation() == "${function.methodId}")
        {
            std::string content = request.envelope().body().content();    
            <#assign request = function.name + "_request">
            protobuf::${namespace}::${model.name}::${model.name}Request_${function.methodId}Request request;
            request.ParseFromString(content);
            
            Trentino::Invocation::InvocationData::Parameters params;
              <#assign argCount = function.arguments?size>
            params.reserve(${argCount});
               <#foreach argument in function.arguments>
                 <#assign name = argument.name>
                 <#assign tn=argument.type.qualifiedName?replace(".","::")>
                <#if !argument.isHasOut()>
                      <#if argument.type.isPrimitive()>
                          <#assign primitiveType = tmapper.name(argument.type)>
            ${primitiveType} ${name};
            ${name} = request.${name?lower_case}();
            <#assign push_back_name=primitiveType>
            //trentino_proxies_push_back(${name},params);
                    <#else>    
            const ${pbtmapper.qName(argument.type)}& pb_${name} = request.${name?lower_case}();
            ${tn} ${name};
            <#assign push_back_name=tn>
            util.copyProperties(pb_${name}, ${name});
                     </#if>
                     <#elseif argument.isHasOut()> <#--handle out params-->
            //@out param
                    <#if argument.type.isPrimitive()>
                          <#assign primitiveType = tmapper.name(argument.type)>
            ${primitiveType} ${name};
            <#assign push_back_name=primitiveType>
                    <#else><#-- primitive complex types-->
                    <#assign push_back_name=tn>
            ${tn} ${name};
                     </#if>
                </#if>
                {
                   static Trentino::Gen::Trentino_Param_Push_Back<${push_back_name}> pb;
                   pb.push_back(${argument.name},params);
                }
              </#foreach>  <#--argument-->
            invocationData.setParameters(params);
            <#if function.returnType.void >
            callback(handler,invocationData,runtimeServicePtr,nullptr, invocationContext, this, response, ec);
            return;
            <#else>
            <#assign returnType = tmapper.name(function.returnType) >
            ${returnType} ret[1];
            callback(handler,invocationData,runtimeServicePtr,(void *)ret, invocationContext, this, response, ec);
            return;
            </#if>
        }
        </#foreach>
     }
    
     bool ${className}::isOneWay( Trentino::Invocation::InvocationData& /*invocationDataPtr*/ ) const 
     {
        //only request with replies currently supported
        return false;
     }
    
     int ${className}::version()const 
     {
       return 1;
     }

     static Trentino::Binding::BindingHelperBase* Trentino::Gen::${className}_getNewInstance()
     {
        return new ${className}();
     }
    
     static SCABindingHelperInjector<${className}> m${className}HelperInjector(std::string("${namespace}::${protoBufContext.className}"), &Trentino::Gen::${className}_getNewInstance);
</#foreach>