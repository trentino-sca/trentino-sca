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
#ifndef BasicCalculatorThrowErrorGen_Trentino_Example_BasicCalculatorThrowError_TrentinoGenProxiesWrappersH
#define BasicCalculatorThrowErrorGen_Trentino_Example_BasicCalculatorThrowError_TrentinoGenProxiesWrappersH
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
#include "../BasicCalculatorThrowError/services/TrentinoExampleBasicCalculatorDivider.h"
#include "../BasicCalculatorThrowError/services/TrentinoExampleBasicCalculatorCalculator.h"
#include "../BasicCalculatorThrowError/services/TrentinoExampleBasicCalculatorDivider.h"

namespace Trentino{
namespace Gen{
namespace BasicCalculatorThrowErrorGen{
   //*************************************************************************************************
   //                                          WRAPPERS
   //*************************************************************************************************

	//*************************************************************************************************
	//wrapper class declaration Trentino_Example_BasicCalculatorThrowError_CalculatorWrapper
	//*************************************************************************************************
   
	class Trentino_Example_BasicCalculatorThrowError_CalculatorWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_Example_BasicCalculatorThrowError_CalculatorWrapper
  

	//*************************************************************************************************
	//wrapper class declaration Trentino_Example_BasicCalculatorThrowError_DividerWrapper
	//*************************************************************************************************
   
	class Trentino_Example_BasicCalculatorThrowError_DividerWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_Example_BasicCalculatorThrowError_DividerWrapper
  



   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************

//*************************************************************************************************
//Proxy class definition Trentino_Example_BasicCalculatorThrowError_DividerProxy
//*************************************************************************************************
 class Trentino_Example_BasicCalculatorThrowError_DividerProxy :public Trentino::Example::BasicCalculatorThrowError::Divider
   {
      //construction
   public:
      Trentino_Example_BasicCalculatorThrowError_DividerProxy(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
  		virtual int& divide ( int a, int b);
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class Trentino_Example_BasicCalculatorThrowError_DividerProxy


}//namespace Gen
}//namespace Trentino
}//namespace BasicCalculatorThrowErrorGen

#endif //BasicCalculatorThrowErrorGen_Trentino_Example_BasicCalculatorThrowError_TrentinoGenProxiesWrappersH

