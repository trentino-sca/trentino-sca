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

#ifndef TrentinoBindingCompactSoapUtilH
#define TrentinoBindingCompactSoapUtilH

//specific
#include <zmq.hpp>
#include "BindingCompactSoapProtobufMessages.h"

namespace Trentino{
namespace Binding{
namespace CompactSoap{

          typedef zmq::message_t* ZMQMessagePtr;
         //****************************************************************************************************
         //                                         BindingSCASession
         //****************************************************************************************************
         //! \ingroup SCA 
         //! \brief A Session actualy handle data exchange betwwen a client and the SCA Binding Server
         //! it is the place where the communication logic is implemented
         //! here it is decided if and when the server should wait for / send a message from the client or close 
         //! a session
         //****************************************************************************************************
         class BINDINGCOMPACTSOAP_IMPORT_EXPORT CompactSoapUtil{
               //services
         public:
            static void fromZMQMsg( zmq::message_t& message, trentino::bindingsca::csoap::Soap* soap );
            static void toZMQMsg( const  trentino::bindingsca::csoap::Soap* soap, ZMQMessagePtr message );
            }; // class Util

         }//namespace CompactSoap
      }//namespace Binding
   }//namepsace Trentino

#endif //TrentinoBindingCompactSoapUtilH

