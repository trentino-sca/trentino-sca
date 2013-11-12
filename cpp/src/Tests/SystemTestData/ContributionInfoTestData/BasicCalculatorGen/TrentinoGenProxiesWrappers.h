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
#ifndef TrentinoGenProxiesWrappersH
#define TrentinoGenProxiesWrappersH
#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif


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
#include "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/BasicCalculator/services/TrentinoExampleBasicCalculatorDivider.h"
#include "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/BasicCalculator/services/TrentinoExampleBasicCalculatorCalculator.h"
#include "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/BasicCalculator/services/TrentinoExampleBasicCalculatorDivider.h"

namespace Trentino{
namespace Gen{
namespace BasicCalculatorGen{
   //*************************************************************************************************
   //                                          WRAPPERS
   //*************************************************************************************************

	//*************************************************************************************************
	//wrapper class declaration Trentino_Example_BasicCalculator_CalculatorWrapper
	//*************************************************************************************************
   
	class Trentino_Example_BasicCalculator_CalculatorWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data
      			 , const Trentino::Invocation::InvocationContextPtr& /*ctx*/
                 ,void* targetInstance) const;
   
	};// class Trentino_Example_BasicCalculator_CalculatorWrapper
  

	//*************************************************************************************************
	//wrapper class declaration Trentino_Example_BasicCalculator_DividerWrapper
	//*************************************************************************************************
   
	class Trentino_Example_BasicCalculator_DividerWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data
      			 , const Trentino::Invocation::InvocationContextPtr& /*ctx*/
                 ,void* targetInstance) const;
   
	};// class Trentino_Example_BasicCalculator_DividerWrapper
  



   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************

//*************************************************************************************************
//Proxy class definition Trentino_Example_BasicCalculator_DividerProxy
//*************************************************************************************************
 class Trentino_Example_BasicCalculator_DividerProxy :public Trentino::Example::BasicCalculator::Divider
   {
      //construction
   public:
      Trentino_Example_BasicCalculator_DividerProxy(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
  		virtual int& divide ( int a, int b);
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class Trentino_Example_BasicCalculator_DividerProxy


}//namespace Gen
}//namespace Trentino
}//namespace BasicCalculatorGen

#endif //TrentinoGenProxiesWrappersH

