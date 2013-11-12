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

#ifndef TrentinoInvocationInvokerBaseH
#define TrentinoInvocationInvokerBaseH

//specific
#include "TrentinoInvocation.h"
#include "../RuntimeModel/TrentinoRuntimeModel.h"

namespace Trentino{
namespace Invocation 
{
   //class declaration
   //**********************************************************************************************
   //                                       InvokerBase
   //**********************************************************************************************
   //! \ingroup Invocation
   //! \brief Base class offering an interface for performing service invocations.    
   //**********************************************************************************************
   class InvokerBase
   {
      //construction
   public:
      virtual ~InvokerBase(){}

      //services
   public:
      //*******************************************************************************************
      //                                     invoke()
      //*******************************************************************************************
      //! \brief Invokes a method.
      //! \param[in] InvocationData object containing all the necessary
      //!            information about which service and which method to execute and what 
      //!            parameters to pass.
      //! \param[in] an InvocationContext object that may contain 
      //!            additional information to be used during the invocation. 
      //! \return \c true if the invocation was successful, otherwise \c false.
      //*******************************************************************************************
	   virtual bool invoke(const Trentino::Invocation::InvocationData& data,
                          void* retVal,
                          const Trentino::Invocation::InvocationContext& ctx) = 0;

      //*******************************************************************************************
      //                               invoke()
      //*******************************************************************************************
      // override from InvokerBase (see documentation in InvokerBase)
      //*******************************************************************************************
      virtual bool invoke( const Trentino::Invocation::InvocationData& data,
                         void* retVal,
                         const Trentino::Invocation::InvocationContext& ctx,
                     const Trentino::RuntimeModel::ServiceBasePtr& targetService)=0;
	};//class InvokerBase
}//namespace Invocation 
}//namespace Trentino

#endif //TrentinoInvocationInvokerBaseH
