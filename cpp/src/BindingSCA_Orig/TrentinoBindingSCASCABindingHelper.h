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

#ifndef TrentinoBindingSCABindingHelperH
#define TrentinoBindingSCABindingHelperH

//standard
#include <boost/shared_ptr.hpp>

//specific
#include <Runtime/RuntimeModel/TrentinoRuntimeModelServiceBase.h>
#include <Runtime/Binding/TrentinoBindingBindingHelperBase.h>
#include <Runtime/Invocation/TrentinoInvocationInvocationData.h>

//compact soap
#include <Binding/CompactSoap/BindingCompactSoapProtobufMessages.h>


#include "TrentinoBindingSCAFaultDetailBuilder.h"


namespace Trentino{
namespace Binding{
namespace SCA{

   class FaultDetailBuilder;
   class SCABindingHelper;
   typedef boost::shared_ptr<FaultDetailBuilder> FaultDetailBuilderPtr;
   typedef boost::shared_ptr<Trentino::Binding::SCA::SCABindingHelper> SCABindingHelperBasePtr;
   //*******************************************************************************************
   //                                   SCABindingHelper
   //*******************************************************************************************
   //! \brief Binding helper for the SCA binding
   //*******************************************************************************************
   class  SCABindingHelper : public Trentino::Binding::BindingHelperBase{

   public:
      //*******************************************************************************************
      //                                   getFaultBuilder()
      //*******************************************************************************************
      //! \brief Return the fault builder for this Service.
      //! \sa FaultDetailBuilder
      //*******************************************************************************************
     virtual const FaultDetailBuilderPtr getFaultBuilder() const =0;

      //*******************************************************************************************
      //                                   serializeResponse()
      //*******************************************************************************************
      //! \brief After service invocation, build the Soap response based on returned values available
      // in the invocation data
      //! \sa InvocationData
      //*******************************************************************************************
     virtual void serializeResponse( const Trentino::Invocation::InvocationDataPtr& invocationDataPtr, trentino::bindingsca::csoap::Soap& response, Trentino::RuntimeModel::ErrorCode& ec )const =0;

     //****************************************************************************************************
     //                                         deserializeRequest()
     //****************************************************************************************************
     //! \brief deserialize the given request and put parameters into the output invocation data
     //! \param const Trentino::Invocation::InvocationDataPtr & invocationDataPtr
     //! \param trentino::bindingsca::csoap::Soap & request
     //! \param Trentino::RuntimeModel::ErrorCode & ec
     //! \return void
     //****************************************************************************************************
     virtual void deserializeRequest( const Trentino::Invocation::InvocationDataPtr& invocationDataPtr, 
        trentino::bindingsca::csoap::Soap& request, Trentino::RuntimeModel::ErrorCode& ec) const =0;

     //****************************************************************************************************
     //                                         isOneWay()
     //****************************************************************************************************
     //! \brief check if the call in this InvocationData is a oneWay Call
     //! \param Trentino::Invocation::InvocationDataPtr & invocationDataPtr
     //! \return bool true if the operation is one way
     //****************************************************************************************************
     virtual bool isOneWay( Trentino::Invocation::InvocationDataPtr& invocationDataPtr ) const=0;
      };// class BindingHelper


} // namespace SCA
}// namespace Binding
} // namespace Trentino

#endif //TrentinoBindingSCABindingHelperH