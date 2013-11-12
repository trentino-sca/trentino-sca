#ifndef TrentinoGenIpcBindingProxyH
#define TrentinoGenIpcBindingProxyH
// ****************************************************************************
// Generated by Trengen. Do not modify
// **************************************************************************** 


#ifdef WIN32
   #ifdef STAND_ALONE_CLIENT_EXPORT
      #define BINDINGIPCPROXY_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define BINDINGIPCPROXY_IMPORT_EXPORT
   #endif //STAND_ALONE_CLIENT_EXPORT
#endif //WIN32

#include <boost/interprocess/managed_shared_memory.hpp> 

//specific
#include <Binding\IPC\Client\TrentinoBindingIPCClientProxyDelegate.h>
<#foreach cppInterface in context.cppInterfaces>
#include "${cppInterface}"
</#foreach>

namespace Trentino{
namespace Gen{

typedef boost::shared_ptr<Trentino::Binding::IPC::Client::BindingProxyDelegateIPC> BindingProxyDelegatePtr;
//*************************************************************************************************
//                                          Binding Proxies
//*************************************************************************************************

<@traceReferenceInterfacesList ctxList = remotableReferences> </@traceReferenceInterfacesList>

<#-------------------------------------------------------------------------------------------->
<#--------------------------------------Binding Proxy Generation-------------------------------------->
<#-------------------------------------------------------------------------------------------->
<#-- for each implementation a class should be generated within the reflection code-->
<#macro traceReferenceInterfacesList ctxList>
<#foreach ctx in ctxList><@createBindingProxy referenceContext = ctx> </@createBindingProxy></#foreach>
</#macro>

<#macro createBindingProxy referenceContext>
<#assign referenceInterface=referenceContext.referenceServiceInterface>
<#assign bindingProxyNamespace = referenceInterface.interfaceClassNamespaces+"BindingProxy">
	
	//*************************************************************************************************
	//Binding proxy class declaration ${bindingProxyNamespace}
	//*************************************************************************************************
   
	class BINDINGIPCPROXY_IMPORT_EXPORT ${bindingProxyNamespace} : public ${referenceInterface.interfaceClassNamespacesSemicolonSeperated}
	{
   		public:
   		${bindingProxyNamespace}()
   		:managed_shm(boost::interprocess::open_or_create, "3178", 1024)
   		{
   		
   		};
   		~${bindingProxyNamespace}(){ mDelegate.reset();};
   		//remote references
      	<#foreach Method in referenceInterface.interfaceMethods>
		<@createMethodForBindingProxy interfaceMethod = Method> </@createMethodForBindingProxy></#foreach>
		void set_Trentino_internal_adress_property_do_not_use_this_name_(const char* anAdress)
		{
			mTrentino_internal_adress_property_do_not_use_this_name_ =anAdress;
			if(!mDelegate.get())
	   		{
				mDelegate.reset(new  Trentino::Binding::IPC::Client::BindingProxyDelegateIPC(mTrentino_internal_adress_property_do_not_use_this_name_));
			}
			else
		    {
		       //mDelegate->setHost(mTrentino_internal_adress_property_do_not_use_this_name_);
		    }
			
		}
		
		const char* get_Trentino_internal_adress_property_do_not_use_this_name_() const
		{
			return mTrentino_internal_adress_property_do_not_use_this_name_;
		}
		
		private:
		 BindingProxyDelegatePtr mDelegate;
		 const char* mTrentino_internal_adress_property_do_not_use_this_name_;
		 boost::interprocess::managed_shared_memory managed_shm;
   	
	};// class ${bindingProxyNamespace}		
</#macro>
<#------ macro for generate the inner part of the invoke method --->
<#macro createMethodForBindingProxy  interfaceMethod>      
${interfaceMethod.returnType} ${interfaceMethod.name}(<#foreach argument in interfaceMethod.arguments>${argument.type} ${argument.name}<#if argument_has_next>,</#if></#foreach>);
</#macro>
}
}

#endif //TrentinoGenIpcBindingProxyH