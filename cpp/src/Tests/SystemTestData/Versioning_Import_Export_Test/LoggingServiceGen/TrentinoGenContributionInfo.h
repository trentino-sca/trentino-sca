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
#include <Runtime/Core/TrentinoCoreContributionInfo.h> 
#include <Runtime/Core/TrentinoCoreContributionInfoMacros.h>
#include <Runtime/ReflectionRuntime/TrentinoReflectionDataRegistry.h>
#ifndef Gen_ContributionInfoH
#define Gen_ContributionInfoH


namespace Trentino{
namespace Gen{
  typedef Trentino::Binding::BindingHelperBase*(*GetBindingHelper)();
  
      class BindingHelperFactory {
  public:
     std::string mBindingId;
     std::string mClassName;
     GetBindingHelper getBindingHelper;
     }; //class BindingHelperFactory
  
  class GenContributionInfo: public Trentino::Core::TrentinoContributionInfo {
CONTRIBUTION_HEADER_BODY(Gen)
  public:
  static void registerBindingFactoryHelper(BindingHelperFactory* factory);
  static Trentino::Reflection::DataRegistry& TRENTINO_CDECL getDataRegistry();
     }; //class GenContributionInfo
     
   typedef std::vector<BindingHelperFactory> BindingHelperFactoryList;
}//namespace Gen
}//namespace Trentino

#endif //Gen_ContributionInfoH