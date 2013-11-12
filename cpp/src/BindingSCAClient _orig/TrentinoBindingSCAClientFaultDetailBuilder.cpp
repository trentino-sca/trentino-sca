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

#include <string>
#include <boost/shared_ptr.hpp>
#include "TrentinoBindingSCAClientFaultDetailBuilder.h"
#include <iosfwd>

using namespace Trentino::Binding::SCA::Client;

//class FaultDetailBuilder
//static member initialization
SubCodeToReasonMap FaultDetailBuilder::mValueMap = FaultDetailBuilder::createValueMap();

Trentino::Binding::SCA::Client::SubCodeToReasonMap Trentino::Binding::SCA::Client::FaultDetailBuilder::createValueMap()
{
   SubCodeToReasonMap valueMap;
   valueMap[C_400_BAD_REQUEST]="400 Bad Request";
   valueMap[C_404_NOT_FOUND]="404 Not Found";
   valueMap[C_501_NOT_IMPLEMENTED]="501 Not implemented";
   return valueMap;
}

//class DefaultFaultDetailBuilder
//constructor
Trentino::Binding::SCA::Client::DefaultFaultDetailBuilder::DefaultFaultDetailBuilder( 
   const std::string& defaultDetail, SubCodes defaultSubCode, const std::string& moreReason)
   : 
    mDefaultDetail(defaultDetail) 
   ,mDefaultSubCode(defaultSubCode)
   ,mMoreReason(moreReason)
{

}

void Trentino::Binding::SCA::Client::DefaultFaultDetailBuilder::setDefaultDetail(const std::string& detail )
{
   mDefaultDetail =  detail;
}

std::string Trentino::Binding::SCA::Client::DefaultFaultDetailBuilder::createSubCode
   (const Trentino::RuntimeModel::ErrorCode& /*ec*/) const
{
   std::stringstream ss;//create a stringstream
   ss << mDefaultSubCode;//add number to the stream
   return ss.str().data();
}

std::string Trentino::Binding::SCA::Client::DefaultFaultDetailBuilder::createReason
   (const Trentino::RuntimeModel::ErrorCode& /*ec*/) const
{
   std::string result;
   result +=FaultDetailBuilder::mValueMap[mDefaultSubCode];
   result+="\n "+mMoreReason;
   return result.data();
}


