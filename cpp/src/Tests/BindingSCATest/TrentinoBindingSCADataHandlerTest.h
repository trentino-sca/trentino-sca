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

#ifndef TrentinoBindingSCADataHandlerTestH
#define TrentinoBindingSCADataHandlerTestH

//standard
#include <fstream>

//tests
#include <gmock/gmock.h>
#include <gtest/gtest.h>

//specific
#include "../../BindingSCA/TrentinoBindingSCADataHandler.h"
#include "TrentinoBindingSCAMocks.h"
//#include "../../BindingSCA/TrentinoBindingSCAProtobufMessages.h"
#include "../../BindingCompactSoap/Binding/CompactSoap/BindingCompactSoapProtobufMessages.h"


#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h"

namespace Trentino{
   namespace Binding{
      namespace SCA{
         namespace Tests{

            //****************************************************************************
            //                        DataHandlerTestHelper
            //****************************************************************************
            //! \brief helper class used to write custom mock actions
            //****************************************************************************
            class DataHandlerTestHelper{

               //************************************************************************
               //                        CompactSoapConverter helper methods and data
            public:
               // virtual void toBuffer(trentino::bindingsca::csoap::Soap& aMessage, std::string* valueInString, Trentino::RuntimeModel::ErrorCode& ec ) const =0;

               //virtual void toMessage(trentino::bindingsca::csoap::Soap& aMessage, const std::string& valueInString, Trentino::RuntimeModel::ErrorCode& ec) const =0;
               void CompactSoapConverter_toMessage_converterReturnError(trentino::bindingsca::csoap::Soap& aMessage,const ArrayInputStreamPtr& is, Trentino::RuntimeModel::ErrorCode& ec);
               void CompactSoapConverter_toMessage_converterReturnDefaultMessage(trentino::bindingsca::csoap::Soap& aMessage,const ArrayInputStreamPtr& /*is*/, Trentino::RuntimeModel::ErrorCode& ec){
                  aMessage.CopyFrom(mToMessageDefaultMessage);
                  ec.assign(0);
                  }


               //************************************************************************
               //                        setDefaultMessage()
               //************************************************************************
               //! \brief set the default message returned by this helper class when 
               //  toMessage is invoked
               void setDefaultMessage(trentino::bindingsca::csoap::Soap defaultMessage){
                  mToMessageDefaultMessage = defaultMessage;
                  }
            private:
               //! \brief the default message returned by this helper
               trentino::bindingsca::csoap::Soap mToMessageDefaultMessage;



               //***********************************************************************
               //**************ServiceInfoReader helper methods and data
               //***********************************************************************
            public:
               //virtual Trentino::ServiceRegistry::ServiceInfoPtr readServiceInfo( trentino::bindingsca::csoap::Soap request, Trentino::RuntimeModel::ErrorCode& ec) const = 0;
               void ServiceInfoReader_readServiceInfo_ReturnNonInitializedSharedPointer(trentino::bindingsca::csoap::Soap request, Trentino::ServiceRegistry::ServiceInfo& info, Trentino::RuntimeModel::ErrorCode& ec);
               void ServiceInfoReader_readServiceInfo_ReturnDefault(trentino::bindingsca::csoap::Soap request,Trentino::ServiceRegistry::ServiceInfo& info, Trentino::RuntimeModel::ErrorCode& ec);



               //*************************************************************************
               //                                    SCAServiceLocator
               //*************************************************************************
            public:
               Trentino::RuntimeModel::ServiceBasePtr ServiceRegistry_findService_ReturnNullPointer(const Trentino::ServiceRegistry::ServiceInfo& serviceInfo);
               Trentino::RuntimeModel::ServiceBasePtr ServiceRegistry_findService_ReturnNoNullPointerButAssignError(const Trentino::ServiceRegistry::ServiceInfo& serviceInfo);
               Trentino::RuntimeModel::ServiceBasePtr ServiceRegistry_findService_ReturnHelperDefaultValue(const Trentino::ServiceRegistry::ServiceInfo& serviceInfo);
               Trentino::RuntimeModel::ServiceBasePtr mSCAServiceLocator_findService_defaultReturnValue;
               };//helper class for custom actions


            //****************************************************************************
            //                        DataHandlerTest
            //****************************************************************************
            //! \brief This class contains DataHandler unit tests
            //****************************************************************************
            class DISABLED_DataHandlerTest : public ::testing::Test{

            protected:
               virtual void SetUp(){
                  deps = boost::shared_ptr<DataHandlerDependencies> (new DataHandlerDependencies());
                  handler.setDependencies(deps);
                  }
               virtual void TearDown(){}

               DataHandler handler;
               DataHandlerTestHelper helper;
               boost::shared_ptr<DataHandlerDependencies> deps;

               };//class DataHandlerTest

            } // namespace Trentino
         } // namespace Binding
      } //SCA
   } // namespace Tests
#endif //TrentinoBindingSCADataHandlerTestH