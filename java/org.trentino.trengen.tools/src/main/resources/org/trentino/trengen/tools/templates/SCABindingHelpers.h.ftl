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
#ifndef ${contributionName}_SCABindingHelpersH
#define ${contributionName}_SCABindingHelpersH

#include <Runtime/Core/TrentinoCoreContributionInfoMacros.h>
#include <Runtime/Binding/TrentinoBindingBindingHelperBase.h>
#include <Binding/SCA/TrentinoBindingSCASCABindingHelper.h>
#include <Binding/SCA/TrentinoBindingSCAFaultDetailBuilder.h>
#include "TrentinoGenContributionInfo.h"


<#foreach header in beanHeaders>
#include "${header}"
</#foreach>


namespace Trentino{
namespace Gen{
<#foreach protoBufContext in context.protoBufContexts>
	<#assign className = protoBufContext.namespace + "_" + protoBufContext.className + "_" >
	class ${className}SCABindingHelper: public Trentino::Binding::SCA::SCABindingHelper
{
     public:
     ${className}SCABindingHelper();
     ~${className}SCABindingHelper();
     virtual const Trentino::Binding::SCA::FaultDetailBuilderPtr getFaultBuilder() const;
     virtual void serializeResponse( const Trentino::Invocation::InvocationData& invocationData,void* retVal, trentino::bindingsca::csoap::Soap& response, Trentino::RuntimeModel::ErrorCode& ec )const;
     //virtual void deserializeRequest( const Trentino::Invocation::InvocationData& invocationData,         trentino::bindingsca::csoap::Soap& request, Trentino::RuntimeModel::ErrorCode& ec) const;
     virtual bool isOneWay( Trentino::Invocation::InvocationData& invocationData ) const;
     virtual int version()const;
     virtual void invoke(InvokeCallback callback, void* handler,
        Trentino::Invocation::InvocationData& invocationData,
        const Trentino::RuntimeModel::ServiceBasePtr& runtimeServicePtr,
        Trentino::Invocation::InvocationContext& invocationContextPtr,
        trentino::bindingsca::csoap::Soap& resquest, 
        trentino::bindingsca::csoap::Soap& response, 
        Trentino::RuntimeModel::ErrorCode& ec);
};

 static Trentino::Binding::BindingHelperBase* ${className}SCABindingHelper_getNewInstance();

</#foreach>
	
	template <class SCABindingHelperImpl>
   	class SCABindingHelperInjector {
   	public:
		SCABindingHelperInjector (std::string classNameP,Trentino::Gen::GetBindingHelper helper)
		{
			BindingHelperFactory* factory = new BindingHelperFactory;
			factory->mBindingId = std::string("binding.sca");
			factory->mClassName = classNameP;
			factory->getBindingHelper = helper;
			GenContributionInfo::registerBindingFactoryHelper(factory);
         }
      };
}//namespace Gen
}//namespace Trentino

#endif //${contributionName}_SCABindingHelpersH

