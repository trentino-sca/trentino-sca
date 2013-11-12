// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2012 by Siemens AG. All rights reserved.
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
#ifndef BasicCalculatorReturnVoidGen__TrentinoGenProxiesWrappersH
#define BasicCalculatorReturnVoidGen__TrentinoGenProxiesWrappersH
#define BOOST_ALL_NO_LIB


//standard
#include <boost/scoped_ptr.hpp>

#include <Global/TrentinoGlobal.h>
#include <Runtime/Invocation/TrentinoInvocation.h>
#include <Runtime/Invocation/TrentinoInvocationInvocationData.h>
#include <Runtime/Invocation/TrentinoInvocationInvocationContext.h> //! \todo: currently not used
#include <Runtime/Invocation/TrentinoInvocationInvokerBase.h>
#include <Runtime/Invocation/TrentinoInvocationServiceInvocationWrapperBase.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModelWireBase.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModelServiceBase.h>
#include <Runtime/ReflectionRuntime/TrentinoReflectionRegistration.h>

//specific
#include "../BasicCalculatorReturnVoid/services/TrentinoExampleBasicCalculatorCalculator.h"

namespace Trentino{
namespace Gen{
namespace BasicCalculatorReturnVoidGen{
   //*************************************************************************************************
   //                                          WRAPPERS
   //*************************************************************************************************

	//*************************************************************************************************
	//wrapper class declaration Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper
	//*************************************************************************************************
   
	class Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper
  



   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************


}//namespace Gen
}//namespace Trentino
}//namespace BasicCalculatorReturnVoidGen

#endif //BasicCalculatorReturnVoidGen__TrentinoGenProxiesWrappersH

