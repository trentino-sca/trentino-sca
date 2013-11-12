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
#ifndef TrentinoBindingSCASCABodyDeserializerH
#define TrentinoBindingSCASCABodyDeserializerH

#include "TrentinoBindingSCAImpl.h"
#include <Runtime/Invocation/TrentinoInvocation.h>


//compact soap
#include <Binding/CompactSoap/BindingCompactSoapProtobufMessages.h>



#include <Runtime/RuntimeModel/TrentinoRuntimeModel.h>
#include "TrentinoBindingSCASCABindingHelper.h"

namespace Trentino{
   namespace Binding{
      namespace SCA{
         class SCABodyDeserializer;
         typedef boost::shared_ptr<SCABodyDeserializer> SCABodyDeserializerPtr;


         //class declaration 
         //********************************************************************************
         //                            SCABodyDeserializer
         //********************************************************************************
         //! \brief
         //!
         //!
         //*******************************************************************************
         class BINDINGSCA_IMPORT_EXPORT SCABodyDeserializer 
         {
            //services
         public:

            virtual  const Trentino::Invocation::InvocationDataPtr 
               deserialize(
                            trentino::bindingsca::csoap::Soap& request
                           ,const Trentino::RuntimeModel::ConstServiceBasePtr& runtimeServicePtr
                           ,const SCABindingHelperBasePtr& scaBindingHelper
                           ,Trentino::RuntimeModel::ErrorCode& ec) const = 0;
         }; //class SCABodyDeserializer


         //class declaration 
         //********************************************************************************
         //                            SCABodyDeserializerImpl
         //********************************************************************************
         //! \brief
         //!
         //!
         //*******************************************************************************
         class BINDINGSCA_IMPORT_EXPORT SCABodyDeserializerImpl : public SCABodyDeserializer 
         {
            //service
         public:
            virtual const Trentino::Invocation::InvocationDataPtr 
               deserialize(
                            trentino::bindingsca::csoap::Soap& request
                           ,const Trentino::RuntimeModel::ConstServiceBasePtr& runtimeServicePtr
                           ,const SCABindingHelperBasePtr& scaBindingHelper
                           ,Trentino::RuntimeModel::ErrorCode& ec ) const;
         }; //Class SCABodyDeserializerImpl

      }//namespace SCA

   }//namespace Binding

}//namespace Trentino

#endif //TrentinoBindingSCASCABodyDeserializerH

