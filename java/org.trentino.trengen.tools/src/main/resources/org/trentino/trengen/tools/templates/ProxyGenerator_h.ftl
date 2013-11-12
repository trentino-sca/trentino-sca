// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2012 by Siemens AG. All rights reserved.
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
#ifndef ${headerFileName}H
#define ${headerFileName}H

<#assign ReflxStaticVariableCount = 1>

#include <Global/TrentinoGlobal.h>
#include <Runtime/Invocation/TrentinoInvocationInvocationData.h>
#include <Runtime/Invocation/TrentinoInvocationInvocationContext.h> //! \todo: currently not used
#include <Runtime/Invocation/TrentinoInvocationInvokerBase.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModelWireBase.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModelServiceBase.h>
#include <Runtime/ReflectionRuntime/TrentinoReflectionRegistration.h>
#include <Runtime/Invocation/TrentinoInvocationGen.h>

//specific
#pragma warning(push)
#pragma warning(disable:4290)
<#foreach include in includesList>
#include "${include}"
</#foreach>
#pragma warning(pop)

namespace Trentino{
namespace Gen{

<#foreach str in context.usingDirectivesForProxies>
using namespace ${str};
</#foreach>

  <#--
    template<typename P0>
    void trentino_gen_internal_push_back(P0& p0, Trentino::Invocation::InvocationData::Parameters& params)
    {
            static Trentino::Gen::Trentino_Param_Push_Back<P0> pb;
            pb.push_back(p0,params);
    }
    

       <#foreach item in context.invokeInfo>
   
   template<typename T <#list item.arguments as x>, typename P${x.i}</#list> >
   void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, void (*call)(T*<#list item.arguments as x>, P${x.i}</#list>)){
      <#list item.arguments as x>
      static GetParam<P${x.i}> gP${x.i};
      </#list>
      call(myInstance<#list item.arguments as x>,*gP${x.i}.get(data,${x.i})</#list>);
      (void)retValPointer;
      }
      
    template<typename T,typename R <#list item.arguments as x>, typename P${x.i}</#list> >
    void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, R (*call)(T*<#list item.arguments as x>, P${x.i}</#list>)){
      <#list item.arguments as x>
      static GetParam<P${x.i}> gP${x.i};
      </#list>
        R res = call(myInstance<#list item.arguments as x>,*gP${x.i}.get(data,${x.i})</#list>);
        static Trentino_Converter<R> converter;
        converter.convert(retValPointer,res);
      }  
   </#foreach>
   -->

   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************

<@traceReferenceInterfacesList referenceInterfacesList = referenceInterfacesList> </@traceReferenceInterfacesList>
}//namespace Gen
}//namespace Trentino

#endif //${headerFileName}H

<#-------------------------------------------------------------------------------------------->
<#--------------------------------------Wrapper Generation-------------------------------------->

<#-------------------------------------------------------------------------------------------->
<#--------------------------------------Proxy Generation-------------------------------------->
<#-------------------------------------------------------------------------------------------->
<#-- for each reference a proxy needs to be generated-->
<#macro traceReferenceInterfacesList referenceInterfacesList>
<#foreach referenceInterface in referenceInterfacesList>
<@createProxy referenceInterface = referenceInterface> </@createProxy>
</#foreach>
</#macro>

<#-- for each reference a proxy needs to be generated-->
<#macro createProxy referenceInterface>
<#assign proxyName = referenceInterface.interfaceClassName>
<#assign proxyNamespace = referenceInterface.interfaceClassNamespaces>
<#assign proxyClassName = proxyNamespace+"Proxy" >
<#assign proxyClass = referenceInterface.interfaceClassNamespacesSemicolonSeperated>
//*************************************************************************************************
//Proxy class definition ${proxyClassName}
//*************************************************************************************************
 class ${proxyClassName} :public ${proxyClass}
   {
      //construction
   public:
      ${proxyClassName}(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
	<#foreach method in referenceInterface.interfaceMethods>
  		virtual ${method.returnType} ${method.name} (<#list method.arguments as x> ${x.type} ${x.name}<#if x_has_next>,</#if></#list>);
	</#foreach>
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class ${proxyClassName}
</#macro>
