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

#pragma warning(push)
#pragma warning(disable:4290)
#include "TrentinoGenIPCHelper.h"
#include "TrentinoGenIPCTypesConverter.h"
#pragma warning(pop)
using namespace Trentino::Gen;
using namespace Trentino::Binding::IPC;


<#foreach protoBufContext in context.protoBufContexts>
<#assign model=protoBufContext.tidlInterfaceModel >
<#assign pbtmapper=protoBufContext.pbtmapper>
<#assign className = protoBufContext.namespace + "_" + protoBufContext.className + "_" + "IPCHelper">
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
										Trentino::Binding::IPC::IpcSoapMsg& soapMsg,
										Trentino::RuntimeModel::ErrorCode& /*ec*/,
										boost::interprocess::managed_shared_memory* managed_shm )const
	{
	<#foreach part in model.nameSpaceParts>${part}::</#foreach>${protoBufContext.className}IPCBeanUtils util;
		<#foreach function in protoBufContext.tidlInterfaceModel.functions>

			<#assign methodName = function.methodId>
			<#assign methodName = methodName?lower_case>
			<#assign response = methodName + "_response">
				if(invocationData.operation() == "${function.methodId}")
				{
					//boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "3178", 1024); 
               		std::pair<${namespace}::IpcMemoryMapObj_${function.methodId}*, std::size_t> p = managed_shm->find<${namespace}::IpcMemoryMapObj_${function.methodId}>("${function.methodId}");
               		${namespace}::IpcMemoryMapObj_${function.methodId}* ${response} = p.first;
					
					<#assign argumentIndex = 0>
					<#if   !function.returnType.void>
						    <#if function.returnType.primitive>
						    <#assign primitiveType = tmapper.name(function.returnType)>
						    	${primitiveType}* argResponse = (${primitiveType}*) retParam;
								${response}->set_returnValue(*argResponse);
						   <#else>
						        <#assign tn=function.returnType.qualifiedName?replace(".","::")>
							   	${tn}* argResponse = (${tn}*) retParam;
							   	//cengiz
							   	managed_shm->destroy<<#foreach part in model.nameSpaceParts>${part}::</#foreach>IPC${function.returnType.className}>("returnVal");
							   	<#foreach part in model.nameSpaceParts>${part}::</#foreach>IPC${function.returnType.className}* returnVal =	managed_shm->construct<<#foreach part in model.nameSpaceParts>${part}::</#foreach>IPC${function.returnType.className}>("returnVal")();
							   util.copyProperties(*argResponse, returnVal);
							   //<#foreach part in model.nameSpaceParts>${part}::</#foreach>IPC${function.returnType.className}* returnVal = <#foreach part in model.nameSpaceParts>${part}::</#foreach>populate_IPC${function.returnType.className}(argResponse, managed_shm);
						   	   ${response}->set_returnValue_ptr(returnVal);
						   </#if>
					</#if>
					<#assign argumentIndex = 0>
					<#foreach returnArg in function.arguments>
					    <#if returnArg.isHasOut() || returnArg.isHasInOut()>
					        <#if returnArg.type.void>
					    	<#elseif returnArg.type.primitive>
								<#assign primitiveType = tmapper.name(returnArg.type)>
								void* retParam =  invocationData.parameters()[${argumentIndex}];
								${primitiveType}* argResponse = (${primitiveType}*) retParam;
								${response}->set_returnValue(*argResponse);
							<#else>
							//faruk
							    void* retParam =  invocationData.parameters()[${argumentIndex}];
							    <#assign tn=returnArg.type.qualifiedName?replace(".","::")>
							   	${tn}* argResponse = (${tn}*) retParam;
							   	managed_shm->destroy<<#foreach part in model.nameSpaceParts>${part}::</#foreach>IPC${returnArg.className}>("returnVal");
							   <#foreach part in model.nameSpaceParts>${part}::</#foreach>IPC${returnArg.className}* returnVal =	managed_shm->construct<<#foreach part in model.nameSpaceParts>${part}::</#foreach>IPC${returnArg.className}>("returnVal")();
							   util.copyProperties(*argResponse, returnVal);
							   
							   //	<#foreach part in model.nameSpaceParts>${part}::</#foreach>IPC${returnArg.className}* returnVal = <#foreach part in model.nameSpaceParts>${part}::</#foreach>populate_IPC${returnArg.className}(argResponse, managed_shm);
						   	    ${response}->set_${returnArg.name?lower_case}_ptr(returnVal);
							</#if>
					    </#if>
				<#assign argumentIndex = argumentIndex +1>
				</#foreach>
			}
		</#foreach>
	}


	void ${className}::invoke(BindingHelperIpc::InvokeCallback callback, 
          void* handler,
          Trentino::Invocation::InvocationData& invocationData, 
          Trentino::Invocation::InvocationContext& invocationContext,
          Trentino::Binding::IPC::IpcSoapMsg& resquest, 
          Trentino::Binding::IPC::IpcSoapMsg& response, 
          Trentino::RuntimeModel::ErrorCode& ec,
          boost::interprocess::managed_shared_memory* managed_shm) 
     {
	<#foreach part in model.nameSpaceParts>${part}::</#foreach>${protoBufContext.className}IPCBeanUtils util;
	<#foreach function in model.functions>
	
	if(invocationData.operation() == "${function.methodId}")
	{
		<#assign request = function.name + "_request">
		// boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "3178", 1024); 
     	std::pair<${namespace}::IpcMemoryMapObj_${function.methodId}*, std::size_t> p = managed_shm->find<${namespace}::IpcMemoryMapObj_${function.methodId}>("${function.methodId}");
     	${namespace}::IpcMemoryMapObj_${function.methodId}* ${request} = p.first;

     /* boost::interprocess::offset_ptr<IpcMemoryMapObj> memMappedObj = resquest.envelope().body().mMemoryMappedObj;
      Trentino::Example::BasicCalculatorRemote::IpcMemoryMapObj_addSimple* addSimple_request= (Trentino::Example::BasicCalculatorRemote::IpcMemoryMapObj_addSimple*)memMappedObj;*/
	
	

     	Trentino::Invocation::InvocationData::Parameters params;
      	<#assign argCount = function.arguments?size>
      	params.reserve(${argCount});
      	//boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "${function.methodId}", 1024); 
      		
   	    <#foreach argument in function.arguments>
     		<#assign name = argument.name>
     		<#assign tn=argument.type.qualifiedName?replace(".","::")>
        	<#if !argument.isHasOut()>
      			<#if argument.type.isPrimitive()>
      				<#assign primitiveType = tmapper.name(argument.type)>
					${primitiveType}* ${name} = new ${primitiveType};
					*${name} = ${request}->${name?lower_case}();
					params.push_back(const_cast<${primitiveType}*>(${name}));
				<#else><#-- primitive complex types-->
				    <#foreach part in model.nameSpaceParts>${part}::</#foreach>IPC${argument.className}* pb_${name} = ${request}->${name?lower_case}().get();
					${tn}* ${name} = new ${tn};
					util.copyProperties(pb_${name}, ${name});
					params.push_back(const_cast<${tn}*>(${name}));
					
						//<#foreach part in model.nameSpaceParts>${part}::</#foreach>IPC${argument.className}* ipc_${name} = <#foreach part in model.nameSpaceParts>${part}::</#foreach>populate_IPC${argument.className}(${name}, managed_shm);
						// ${request}->set_${name}_ptr(ipc_${name});
						 
 				</#if>
 				<#elseif argument.isHasOut()> <#--handle out params-->
				//@out param
				<#if argument.type.isPrimitive()>
      				<#assign primitiveType = tmapper.name(argument.type)>
					${primitiveType}* ${name} = new ${primitiveType};
					params.push_back(*${name});
				<#else><#-- primitive complex types-->
					${tn}* ${name} = new ${tn};
					params.push_back(const_cast<${tn}*>(${name}));
 				</#if>
			</#if>
  		</#foreach>  <#--argument-->
		invocationData.setParameters(params);
		<#if function.returnType.void >
            callback(handler,invocationData,nullptr, invocationContext, this, response, ec);
            return;
        <#else>
        <#assign returnType = tmapper.name(function.returnType) >
            ${returnType} ret[1];
            callback(handler,invocationData,(void *)ret, invocationContext, this, response, ec);
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
	
	static IPCBindingHelperInjector<${className}> m${className}HelperInjector(std::string("${namespace}::${protoBufContext.className}"), &Trentino::Gen::${className}_getNewInstance);
</#foreach>
<#--
<#foreach remotableService in remotableServices>
<#assign partOfClassName = remotableService.interfaceClassNamespaces >
<#assign className = remotableService.interfaceClassNamespaces + "IPCBindingHelper">
//----------------------------------------------------------------------------------
// Binding helper for class ${className}
//----------------------------------------------------------------------------------
	${className}::${className}(){}
	${className}::~${className}(){}

	const FaultDetailBuilderPtr ${className}::getFaultBuilder()const
	{
		throw "not implemented";
	}


	void ${className}::serializeResponse(const Trentino::Invocation::InvocationDataPtr& invocationDataPtr, 
										trentino::bindingipc::csoap::Soap& response, 
										Trentino::RuntimeModel::ErrorCode& /*ec*/ )const
	{
		BasicCalculatorBeanUtils util;
		<#foreach method in remotableService.interfaceMethods>
		<#assign methodName = method.name>
		<#assign methodName = methodName?lower_case>
		<#assign type = method.trimmedReturnType>
		<#if type != "void">
		if(invocationDataPtr->operation() == "${method.name}")
		{
			<#assign response = method.name + "_response">
			BasicCalculatorResponse_${method.name}Response ${method.name}_response;
			<#if tmapper.isCppPrimitive(method.trimmedReturnType)>
			void* retParam =  invocationDataPtr->response();
			${type}* argResponse = (${type}*) retParam;
			${response}.set_${methodName}response(*argResponse);
			<#else>
			Trentino::Example::BasicCalculatorRemote::protobuf::PB_${type}* pb_argResponse = ${response}.mutable_${methodName}response();
			void* retParam =  invocationDataPtr->response();
			${type}* argResponse = (${type}*) retParam;
			util.copyProperties(argResponse,pb_argResponse);
			</#if>
		}
		</#if>
		</#foreach>
		
	}

	void ${className}::deserializeRequest( const Trentino::Invocation::InvocationDataPtr& invocationDataPtr, 
   											trentino::bindingipc::csoap::Soap& request, 
   											Trentino::RuntimeModel::ErrorCode& /*ec*/) const
   	{
   	BasicCalculatorBeanUtils util;
		<#foreach method in remotableService.interfaceMethods>
		if(invocationDataPtr->operation() == "${method.name}")
		{
			std::string content = request.envelope().body().content();
			<#assign request = method.name + "_request">
			BasicCalculatorRequest_${method.name}Request request;
			request.ParseFromString(content);

     		Trentino::Invocation::InvocationData::Parameters params;
      <#assign argCount = method.arguments?size>
      params.reserve(${argCount});
      <#foreach argument in method.arguments>
	      <#assign argumentType =argument.type>
     		<#assign argumentTrimmedType = argument.trimmedType>
     		<#assign name = argument.name>
           	<#assign i = argumentType?index_of("*")>
      		<#assign argumentType =argumentType?replace("&", "")>
      <#if argumentType?starts_with("const ")>

        	<#assign argumentType = argumentType?replace("const ", "")>
        	<#if tmapper.isCppPrimitive(argumentType)> 
        	<#if i!= -1 >
	        		//here1
	        		const ${argumentTrimmedType} ${name} = request.${name}();
	        		params.push_back(const_cast<${argumentType}>(${name}));
	        		 
	        	<#else>
	        		//here2
	        		const ${argumentTrimmedType} ${name} = request.${name}();
	       		 	params.push_back(const_cast<${argumentType}*>(&${name}));
	       		 </#if>
	        <#else>
	       		 <#if i!= -1 >
	        		//here1
	        		const PB_${argumentTrimmedType} pb_${name} = request.${name}();
	        		${argumentType} ${name};
	        		util.copyProperties(pb_${name}, ${name});
	        		params.push_back(const_cast<${argumentType}>(${name}));
	        	<#else>
	        		//here2
	        		const PB_${argumentTrimmedType} pb_${name} = request.${name}();
	        		${argumentType} ${name};
	        		util.copyProperties(pb_${name}, ${name});
	       		 	params.push_back(const_cast<${argumentType}*>(&${name}));
	       		 	
	       		 	
	       		 </#if>
       		 </#if>
      <#else>
	      <#if tmapper.isCppPrimitive(argumentType)>
	     		<#if i!= -1 >
	        		//here3
	        		${argumentTrimmedType} ${name} = request.${name}();
	        		 params.push_back(${name});
	        		 
	        	<#else>
	        		//here4
	        		${argumentTrimmedType} ${name} = request.${name}();
	       		 	params.push_back(&${name});
	       		 </#if>
	      	<#else>
	      		<#if i!= -1 >
	        		//here3
	        		${argumentTrimmedType} pb_${name} = request.${name}();
	        		${argumentTrimmedType} ${name};
	        		util.copyProperties(pb_${name}, ${name});
	        		 params.push_back(${name});
	        		 
	        	<#else>
	        		//here44
	        		const PB_${argumentTrimmedType} pb_${name} = request.${name}();
	        		${argumentType} ${name};
	        		util.copyProperties(pb_${name}, ${name});
	       		 	params.push_back(&${name});
	       		 </#if>
	      	</#if>    
      </#if>
  			</#foreach> 
			invocationDataPtr->setParameters(params);
		}
		 
		</#foreach> 
	}


</#foreach>
-->
