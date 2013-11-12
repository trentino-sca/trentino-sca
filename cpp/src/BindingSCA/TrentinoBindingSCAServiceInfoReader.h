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
      
            virtual void readServiceInfo(const trentino::bindingsca::csoap::Soap& request,
               Trentino::ServiceRegistry::ServiceInfo& result,
               Trentino::RuntimeModel::ErrorCode& ec) const =0;
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
            virtual void readServiceInfo(const trentino::bindingsca::csoap::Soap& request,
               Trentino::ServiceRegistry::ServiceInfo& result,
               Trentino::RuntimeModel::ErrorCode& ec) const;
         }; //Class ServiceInfoReaderImpl

      }//namespace SCA

   }//namespace Binding

}//namespace Trentino

#endif //TrentinoBindingSCAServiceInfoReaderH

