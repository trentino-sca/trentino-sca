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
#ifndef TrentinoBindingSCAServiceInfoReaderH
#define TrentinoBindingSCAServiceInfoReaderH

//specific
#include "TrentinoBindingSCAImpl.h"

//compact soap
#include <Binding/CompactSoap/BindingCompactSoapProtobufMessages.h>

#include "../Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModel.h"
#include "../Runtime/ServiceRegistry/ServiceRegistry.h"

namespace Trentino{
   namespace Binding{
      namespace SCA{

         class ServiceInfoReader;
         typedef boost::shared_ptr<ServiceInfoReader> ServiceInfoReaderPtr;
         //***********************************************************************************
         //                            ServiceInfoReader
         //***********************************************************************************
         //! \brief main class responsible of reading a soap header and therefore determine
         //! attributes of the header that are relevant for the invocation.
         //! it is also the place where validation take place if the soap header is not valid
         //***********************************************************************************
         class BINDINGSCA_IMPORT_EXPORT ServiceInfoReader {
            //services
         public:
            virtual Trentino::ServiceRegistry::ServiceInfoPtr readServiceInfo(const trentino::bindingsca::csoap::Soap& request, Trentino::RuntimeModel::ErrorCode& ec ) const = 0;
         }; //class ServiceInfoReader


                  //class declaration 
         //********************************************************************************
         //                            ServiceInfoReaderImpl
         //********************************************************************************
         //! \brief ServiceInfoReader implementation
         //********************************************************************************
         class BINDINGSCA_IMPORT_EXPORT ServiceInfoReaderImpl : public ServiceInfoReader {

            //constructor
         public:
            ServiceInfoReaderImpl();
            virtual ~ServiceInfoReaderImpl();
            //services
         public:
            virtual Trentino::ServiceRegistry::ServiceInfoPtr readServiceInfo(const trentino::bindingsca::csoap::Soap& request, Trentino::RuntimeModel::ErrorCode& ec) const;
         }; //Class ServiceInfoReaderImpl

      }//namespace SCA

   }//namespace Binding

}//namespace Trentino

#endif //TrentinoBindingSCAServiceInfoReaderH

