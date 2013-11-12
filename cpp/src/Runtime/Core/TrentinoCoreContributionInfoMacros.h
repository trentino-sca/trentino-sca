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

#ifndef TrentinoCoreContributionInfoMacrosH
#define TrentinoCoreContributionInfoMacrosH




#define CONTRIBUTION_HEADER_BODY(contributionName)\
   public:\
   contributionName##ContributionInfo();\
virtual ~contributionName##ContributionInfo();\
   public:\
   virtual TRENTINO_DLLEXPORT void TRENTINO_CDECL loadModel(Trentino::Core::ContributionLoading::SCAModelLoader* modelLoader);\
   virtual TRENTINO_DLLEXPORT  Trentino::Binding::BindingHelperBase* TRENTINO_CDECL getBindingHelperByBindingIdAndClassName(const std::string& biningId,const std::string& className );\
   virtual TRENTINO_DLLEXPORT  const char* TRENTINO_CDECL getAllDeclaredBindings() const;\
   virtual TRENTINO_DLLEXPORT Trentino::Reflection::DataRegistry& TRENTINO_CDECL dataRegistry()const;

#define CONTRIBUTIONINFO_CPP_CDTOR(contributionName)\
   contributionName##ContributionInfo::contributionName##ContributionInfo() { }\
   contributionName##ContributionInfo::~contributionName##ContributionInfo(){}

#define BINDING_SCA_GENERATE_BINDING_HELPER_HEADER(className)\
class className##SCABindingHelper: public Trentino::Binding::SCA::SCABindingHelper\
{\
     public:\
     className##SCABindingHelper();\
     ~className##SCABindingHelper();\
     virtual const Trentino::Binding::SCA::FaultDetailBuilderPtr getFaultBuilder() const;\
     virtual void serializeResponse( const Trentino::Invocation::InvocationDataPtr& invocationDataPtr, trentino::bindingsca::csoap::Soap& response, Trentino::RuntimeModel::ErrorCode& ec )const;\
     virtual void deserializeRequest( const Trentino::Invocation::InvocationDataPtr& invocationDataPtr,         trentino::bindingsca::csoap::Soap& request, Trentino::RuntimeModel::ErrorCode& ec) const;\
     virtual bool isOneWay( Trentino::Invocation::InvocationDataPtr& invocationDataPtr ) const;\
     virtual int version()const;\
};\
 static Trentino::Binding::BindingHelperBase* className##SCABindingHelper_getNewInstance();

#endif //TrentinoCoreContributionInfoMacrosH