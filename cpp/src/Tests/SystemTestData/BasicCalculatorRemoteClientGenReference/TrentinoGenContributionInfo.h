// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************
#include <Runtime/Core/TrentinoCoreContributionInfo.h>
#include <Runtime/Core/TrentinoCoreContributionInfoMacros.h>

#ifndef Gen_ContributionInfoH
#define Gen_ContributionInfoH
#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif


namespace Trentino{
namespace Gen{
  typedef Trentino::Binding::BindingHelperBase*(*GetBindingHelper)();
  class GenContributionInfo: public Trentino::Core::TrentinoContributionInfo {
CONTRIBUTION_HEADER_BODY(Gen);
     }; //class GenContributionInfo
     
    class BindingHelperFactory {
  public:
     std::string mBindingId;
     std::string mClassName;
     GetBindingHelper getBindingHelper;
     }; //class BindingHelperFactory

   typedef std::vector<BindingHelperFactory> BindingHelperFactoryList;
   static BindingHelperFactoryList bindingHelperFactories;
   
}//namespace Gen
}//namespace Trentino

#endif Gen_ContributionInfoH