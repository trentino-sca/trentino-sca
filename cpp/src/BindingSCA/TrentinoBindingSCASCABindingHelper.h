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
      typedef void (*InvokeCallback) (void* handler, 
                                           Trentino::Invocation::InvocationData& invocationDataPtr,
                                           const Trentino::RuntimeModel::ServiceBasePtr& runtimeServicePtr,
                                           void* retVal,
                                           Trentino::Invocation::InvocationContext& invocationContextPtr,
                                          const  SCABindingHelper* scaBindingHelperBasePtr, 
                                          trentino::bindingsca::csoap::Soap& response, 
                                          Trentino::RuntimeModel::ErrorCode& ec);
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
      virtual void serializeResponse( const Trentino::Invocation::InvocationData& invocationData,void* retVal, trentino::bindingsca::csoap::Soap& response, Trentino::RuntimeModel::ErrorCode& ec )const =0;

     //****************************************************************************************************
     //                                         deserializeRequest()
     //****************************************************************************************************
     //! \brief deserialize the given request and put parameters into the output invocation data
     //! \param const Trentino::Invocation::InvocationDataPtr & invocationDataPtr
     //! \param trentino::bindingsca::csoap::Soap & request
     //! \param Trentino::RuntimeModel::ErrorCode & ec
     //! \return void
     //****************************************************************************************************
     //virtual void deserializeRequest( const Trentino::Invocation::InvocationDataPtr& invocationDataPtr, 
     //   trentino::bindingsca::csoap::Soap& request, Trentino::RuntimeModel::ErrorCode& ec) const =0;

     //****************************************************************************************************
     //                                         isOneWay()
     //****************************************************************************************************
     //! \brief check if the call in this InvocationData is a oneWay Call
     //! \param Trentino::Invocation::InvocationDataPtr & invocationDataPtr
     //! \return bool true if the operation is one way
     //****************************************************************************************************
     virtual bool isOneWay( Trentino::Invocation::InvocationData& invocationDataPtr ) const=0;

     virtual void invoke(InvokeCallback callback, void* handler,
        Trentino::Invocation::InvocationData& invocationData,
        const Trentino::RuntimeModel::ServiceBasePtr& runtimeServicePtr,
        Trentino::Invocation::InvocationContext& invocationContextPtr,
        trentino::bindingsca::csoap::Soap& resquest, 
        trentino::bindingsca::csoap::Soap& response, 
        Trentino::RuntimeModel::ErrorCode& ec)=0;
      };// class BindingHelper


} // namespace SCA
}// namespace Binding
} // namespace Trentino

#endif //TrentinoBindingSCABindingHelperH