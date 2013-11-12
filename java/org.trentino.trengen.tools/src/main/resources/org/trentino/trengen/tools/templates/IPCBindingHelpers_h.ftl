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
#ifndef ${contributionName}_IPCBindingHelpersH
#define ${contributionName}_IPCBindingHelpersH
#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif

#include <Runtime/Core/TrentinoCoreContributionInfoMacros.h>
#include <Runtime/Binding/TrentinoBindingBindingHelperBase.h>
#include <BindingIpcServer/TrentinoBindingIpcBindingHelper.h>
#include <BindingIpcServer/TrentinoBindingIpcFaultDetailBuilder.h>
#include "TrentinoGenContributionInfo.h"

namespace Trentino{
namespace Gen{
<#foreach protoBufContext in context.protoBufContexts>
	<#assign className = protoBufContext.namespace + "_" + protoBufContext.className + "_" >
	class ${className}IPCBindingHelper: public Trentino::Binding::IPC::BindingHelperIpc
{
     public:
     ${className}IPCBindingHelper();
     ~${className}IPCBindingHelper();
     virtual const Trentino::Binding::IPC::FaultDetailBuilderPtr getFaultBuilder() const;
     virtual void serializeResponse( const Trentino::Invocation::InvocationDataPtr& invocationDataPtr,Trentino::RuntimeModel::ErrorCode& ec )const;
     virtual void deserializeRequest( const Trentino::Invocation::InvocationDataPtr& invocationDataPtr, Trentino::RuntimeModel::ErrorCode& ec) const;
     virtual bool isOneWay( Trentino::Invocation::InvocationDataPtr& invocationDataPtr ) const;
     virtual int version()const;
};

 static Trentino::Binding::BindingHelperBase* ${className}IPCBindingHelper_getNewInstance();

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

#endif //${contributionName}_IPCBindingHelpersH

