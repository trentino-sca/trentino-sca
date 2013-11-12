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

#ifndef TrentinoInvocationServiceInvocationWrapperBaseH
#define TrentinoInvocationServiceInvocationWrapperBaseH

//specific
#include "TrentinoInvocation.h"

namespace Trentino{
namespace Invocation 
{  	
   //**********************************************************************************************
   //                             ServiceInvocationWrapperBase 
   //**********************************************************************************************
   //! \ingroup Invocation
   //! \brief Base class to be inherited by every generated invocation wrapper in order to execute
   //!        a service invocation on the callee side. 
   //!
   //! Every callable service must have a corresponding (generated) invocation wrapper. Every 
   //! specific (generated) wrapper is derived from ServiceInvocationWrapperBase and must implement 
   //! the pure virtual invoke() method. The implementation of this method should perform a 
   //! service call using the given targetInstance (as service implementation) according to the 
   //! passed InvocationData.   
   //**********************************************************************************************
   class ServiceInvocationWrapperBase 
   {
      //services
	public:
      //*******************************************************************************************
      //                             ServiceInvocationWrapperBase 
      //*******************************************************************************************      
      //! \brief Performs an invocation of a service method. 
      //! 
      //! \param[in] data A shared pointer to an InvocationData object containing all the necessary
      //!            information about which service method to execute and what parameters to pass.
      //! \param[in] ctx A shared pointer to an InvocationContext object that may contain 
      //!            additional information to be used during the invocation. Currently not used!
      //! \param[in] targetInstance A \c void pointer to the object implementing the service to 
      //!            be called. Before a service call can be executed this \c void pointer must 
      //!            be casted to the correct type.
      //! \par Example:
      //! \code
      //! //executing int MyService::func1(int, SomeType)
      //! void MyServiceWrapper::invoke( const Trentino::Invocation::InvocationDataPtr& data
      //!                              , const Trentino::Invocation::InvocationContextPtr& /*ctx*/
      //!                              , void* targetInstance)
      //! {
      //!    MyService* const myInstance = static_cast<MyService*>(targetInstance);
      //!    if(data->operation() == "func1")
      //!    {
      //!       int& param0 = *static_cast<int*>(data->params()[0]);
      //!       SomeType& param1 = *static_cast<SomeType*>(data->params()[1]);
      //!       int* result  = new int;
      //!       *result = myInstance->func1(param0, param1);
      //!       data->setResponse(result);
      //!    }
      //!    else if(data->operation() == "func")
      //!    //...
      //! }
      //! \endcode
      //*******************************************************************************************
		virtual void invoke( const Trentino::Invocation::InvocationDataPtr& data
                         , const Trentino::Invocation::InvocationContextPtr& ctx
                         , void* targetInstance) const = 0;      
	}; // class ServiceInvocationWrapperBase

}//namespace Invocation
}//namespace Trentino

#endif //TrentinoInvocationServiceInvocationWrapperBaseH
