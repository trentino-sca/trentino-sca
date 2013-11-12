// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
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
#ifndef ${contributionName}_IPCHelperH
#define ${contributionName}_IPCHelperH
#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif

#include <Runtime/Core/TrentinoCoreContributionInfoMacros.h>
#include <Runtime/Binding/TrentinoBindingBindingHelperBase.h>
#include <Binding/Ipc/TrentinoBindingIpcBindingHelper.h>
#include <Binding/Ipc/TrentinoBindingIpcFaultDetailBuilder.h>
#include <Binding/Ipc/TrentinoBindingIpcSoapMsg.h>
#include "TrentinoGenContributionInfo.h"

namespace Trentino{
namespace Gen{
<#foreach protoBufContext in context.protoBufContexts>
	<#assign className = protoBufContext.namespace + "_" + protoBufContext.className + "_" >
	class ${className}IPCHelper: public Trentino::Binding::IPC::BindingHelperIpc
{
     public:
     ${className}IPCHelper();
     ~${className}IPCHelper();
     
     virtual const Trentino::Binding::IPC::FaultDetailBuilderPtr getFaultBuilder() const;
     
     virtual void serializeResponse( const Trentino::Invocation::InvocationData& invocationData, 
	 	void* retParam,
	 	Trentino::Binding::IPC::IpcSoapMsg& soapMsg,
	 	Trentino::RuntimeModel::ErrorCode& ec,
	 	boost::interprocess::managed_shared_memory* managed_shm )const;
	 	
	 void invoke( BindingHelperIpc::InvokeCallback callback, 
          void* handler,
          Trentino::Invocation::InvocationData& invocationData, 
          Trentino::Invocation::InvocationContext& invocationContext,
          Trentino::Binding::IPC::IpcSoapMsg& resquest, 
          Trentino::Binding::IPC::IpcSoapMsg& response, 
          Trentino::RuntimeModel::ErrorCode& ec,
          boost::interprocess::managed_shared_memory* managed_shm );
     
     virtual bool isOneWay( Trentino::Invocation::InvocationData& invocationData ) const;     
     
     virtual int version()const;
};

 static Trentino::Binding::BindingHelperBase* ${className}IPCHelper_getNewInstance();

</#foreach>
	
	template <class IPCBindingHelperImpl>
   	class IPCBindingHelperInjector {
   	public:
		IPCBindingHelperInjector (std::string classNameP,Trentino::Gen::GetBindingHelper helper)
		{
			BindingHelperFactory* factory = new BindingHelperFactory();
			factory->mBindingId = std::string("binding.ipc");
			factory->mClassName = classNameP;
			factory->getBindingHelper = helper;
			GenContributionInfo::registerBindingFactoryHelper(factory);
         }
      };
}//namespace Gen
}//namespace Trentino

#endif //${contributionName}_IPCHelperH

