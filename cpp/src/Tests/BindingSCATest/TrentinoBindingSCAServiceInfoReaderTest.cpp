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


//tests
#include <gmock/gmock.h>
#include <gtest/gtest.h>

//Class under test
#include "../../BindingSCA/TrentinoBindingSCAServiceInfoReader.h"
#include "../../Runtime/ServiceRegistry/TrentinoServiceRegistryServiceInfo.h"




//Usings
using namespace std;
using namespace Trentino::Binding::SCA;
using namespace Trentino::RuntimeModel;






//****************************************************************************
//
//                           ServiceInfoReaderTest Tests
//
//****************************************************************************
//! \brief 
//****************************************************************************


namespace{
   
}


//if header is valid then a non null ServiceInfoPtr Object is returned
TEST(ServiceInfoReaderTest,If_Header_is_valid_then_a_non_null_ServiceInfoPtr_is_returned){
   using namespace trentino::bindingsca::csoap;
   Soap message;
   Soap_Envelope* envelope = message.mutable_envelope();
   Soap_Header* header = envelope->mutable_header();
   Addressing* addressing  = header->mutable_addressing();
   const std::string action ="doIt";
   const std::string to ="to1/Calculator";
   addressing->set_action(action);
   addressing->set_to(to);
   addressing->set_from(to);

   ServiceInfoReaderImpl reader;
   Trentino::RuntimeModel::ErrorCode ec;
   Trentino::ServiceRegistry::ServiceInfo info;
   reader.readServiceInfo(message, info,ec);
   EXPECT_EQ(0,ec.value());

   }

//if header is valid then a non null ServiceInfoPtr Object is returned
TEST(ServiceInfoReaderTest,If_Header_is_valid_then_a_non_null_ServiceInfoPtr_is_returned2){
   using namespace trentino::bindingsca::csoap;
   Soap message;
   Soap_Envelope* envelope = message.mutable_envelope();
   Soap_Header* header = envelope->mutable_header();
   Addressing* addressing  = header->mutable_addressing();
   const std::string action ="doIt";
   const std::string to ="tecp:://localhost:8080/to1/Calculator";
   addressing->set_action(action);
   addressing->set_to(to);
   addressing->set_from(to);

   ServiceInfoReaderImpl reader;
   Trentino::ServiceRegistry::ServiceInfo info;
   Trentino::RuntimeModel::ErrorCode ec;
   reader.readServiceInfo(message, info, ec);
   EXPECT_EQ(0,ec.value());
   }