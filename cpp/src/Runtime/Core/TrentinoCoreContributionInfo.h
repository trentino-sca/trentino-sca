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

#ifndef TrentinoCoreContributionInfoH
#define TrentinoCoreContributionInfoH

//standard


//specific
#include "TrentinoCoreContributionLoadingSCAModelLoader.h"
#include "../Binding/TrentinoBindingBindingHelperBase.h"
#include "../ReflectionRuntime/TrentinoReflectionDataRegistry.h"



namespace Trentino{
namespace Core
{
   class TrentinoContributionInfo {
   
   public:
     virtual TRENTINO_DLLEXPORT void TRENTINO_CDECL loadModel(Trentino::Core::ContributionLoading::SCAModelLoader* modelLoader)=0;
     //virtual TRENTINO_DLLEXPORT  Trentino::Invocation::ServiceInvocationWrapperBase* TRENTINO_CDECL getServiceInvocationWrapperByClassName(const std::string& className ) =0;
     virtual TRENTINO_DLLEXPORT  Trentino::Binding::BindingHelperBase* TRENTINO_CDECL getBindingHelperByBindingIdAndClassName(const std::string& biningId,const std::string& className ) =0;
     //****************************************************************************************************
     //                                         getAllDeclaredBindings()
     //****************************************************************************************************
     //! \brief return a comma separated lidt of all the bindings available in this contribution
     //! \return TRENTINO_DLLEXPORT  std::string TRENTINO_CDECL
     //****************************************************************************************************
     virtual TRENTINO_DLLEXPORT const char* TRENTINO_CDECL getAllDeclaredBindings()const =0;

     virtual TRENTINO_DLLEXPORT Trentino::Reflection::DataRegistry& TRENTINO_CDECL dataRegistry()const =0;
   
   }; //class TrentinoContributionInfo

} //namespace Core
} //namespace Trentino
#endif //TrentinoCoreDomainH