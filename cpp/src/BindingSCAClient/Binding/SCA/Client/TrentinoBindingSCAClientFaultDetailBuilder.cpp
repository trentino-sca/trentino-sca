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

#include <string>
#include <sstream>
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


