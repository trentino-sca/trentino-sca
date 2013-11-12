// ****************************************************************************
// Generated by Trengen. Do not modify
// **************************************************************************** 

#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif

//header
#include "TrentinoGenProxiesWrappers.h"

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

using namespace Trentino::Example;

namespace Trentino{
namespace Gen{

namespace
{

   Trentino::Invocation::InvocationDataPtr trentino_sca_runtime_generated_proxies_invoke_helper_do_not_reuse_this_name(
   const std::string opName,
   Trentino::Invocation::InvocationData::Parameters& params,
   Trentino::RuntimeModel::WireBase* wire
   ){
      assert(wire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = wire->service().lock();
	  if(targetService.get() == nullptr){
	    throw std::runtime_error("service unavailable");
	  }
         
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation(opName);
	  invocationData->setParameters(params);
	  
	  const Trentino::Invocation::InvocationContextPtr ctx = wire->invocationContext();
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
	  return invocationData;
   }
   
   template<class T>
   void trentino_proxies_push_back(T& elem, Trentino::Invocation::InvocationData::Parameters& params){
    params.push_back(&elem);
   }
   
   template<class T>
   void trentino_proxies_push_back(T* elem, Trentino::Invocation::InvocationData::Parameters& params){
    params.push_back(elem);
   }
   

   template<class T>
   void trentino_proxies_push_back_const(const T& elem, Trentino::Invocation::InvocationData::Parameters& params){
      params.push_back(const_cast<T*>(&elem));
      }
   
   template<class T>
   void trentino_proxies_push_back_const(const T * elem, Trentino::Invocation::InvocationData::Parameters& params){
    params.push_back(const_cast<T*>(elem));
   }
} 

   //*************************************************************************************************
   //                                          WRAPPERS
   //*************************************************************************************************
	//*************************************************************************************************
	//wrapper class definition for wrapper: Trentino_Example_BasicPrinterWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_Example_BasicPrinterWrapper
	void Trentino_Example_BasicPrinterWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& /*ctx*/
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::Example::BasicPrinter* const myInstance = static_cast<Trentino::Example::BasicPrinter*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="add" )
      {
			  const Trentino::Example::BasicPrinter::ComplexNumber& param0 = *static_cast<const Trentino::Example::BasicPrinter::ComplexNumber*>(data->parameters()[0]);

			  const Trentino::Example::BasicPrinter::ComplexNumber& param1 = *static_cast<const Trentino::Example::BasicPrinter::ComplexNumber*>(data->parameters()[1]);

			 				Trentino::Example::BasicPrinter::ComplexNumber* result = new Trentino::Example::BasicPrinter::ComplexNumber;
				*result =  myInstance->add( param0, param1 ); 
				data->setResponse(result);
      }
else       if(op =="addSimple" )
      {
			  const tint32_t& param0 = *static_cast<const tint32_t*>(data->parameters()[0]);

			  const tint32_t& param1 = *static_cast<const tint32_t*>(data->parameters()[1]);

			 				tint32_t* result = new tint32_t;
				*result =  myInstance->addSimple( param0, param1 ); 
				data->setResponse(result);
      }
else       if(op =="divide" )
      {
			  const Trentino::Example::BasicPrinter::ComplexNumber& param0 = *static_cast<const Trentino::Example::BasicPrinter::ComplexNumber*>(data->parameters()[0]);

			  const Trentino::Example::BasicPrinter::ComplexNumber& param1 = *static_cast<const Trentino::Example::BasicPrinter::ComplexNumber*>(data->parameters()[1]);

			 				Trentino::Example::BasicPrinter::ComplexNumber* result = new Trentino::Example::BasicPrinter::ComplexNumber;
				*result =  myInstance->divide( param0, param1 ); 
				data->setResponse(result);
      }
else       if(op =="multiply" )
      {
			  const Trentino::Example::BasicPrinter::ComplexNumber& param0 = *static_cast<const Trentino::Example::BasicPrinter::ComplexNumber*>(data->parameters()[0]);

			  const Trentino::Example::BasicPrinter::ComplexNumber& param1 = *static_cast<const Trentino::Example::BasicPrinter::ComplexNumber*>(data->parameters()[1]);

			  Trentino::Example::BasicPrinter::ComplexNumber& param2 = *static_cast<Trentino::Example::BasicPrinter::ComplexNumber*>(data->parameters()[2]);

      		myInstance->multiply(  param0, param1, param2 );
      }
else       if(op =="divide2" )
      {
			  const Trentino::Example::BasicPrinter::TupleComplexNumber& param0 = *static_cast<const Trentino::Example::BasicPrinter::TupleComplexNumber*>(data->parameters()[0]);

			 				Trentino::Example::BasicPrinter::ComplexNumber* result = new Trentino::Example::BasicPrinter::ComplexNumber;
				*result =  myInstance->divide2( param0 ); 
				data->setResponse(result);
      }
else       if(op =="calculateAge" )
      {
			  const Trentino::Example::BasicPrinter::Person& param0 = *static_cast<const Trentino::Example::BasicPrinter::Person*>(data->parameters()[0]);

			 				tuint32_t* result = new tuint32_t;
				*result =  myInstance->calculateAge( param0 ); 
				data->setResponse(result);
      }

	}
 



   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************  


}//namespace Gen
}//namespace Trentino

