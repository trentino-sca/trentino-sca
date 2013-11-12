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

#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif

//header
#include "BuilderGen_Trentino_Example_Builder_TrentinoGenProxiesWrappers.h"

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
#include "../Builder/services/Logger.h"
#include "../Builder/services/ExecuteLinker.h"
#include "../Builder/services/ExecuteCompiler.h"
#include "../Builder/services/LoggerConsole.h"
#include "../Builder/services/LoggerFile.h"
#include "../Builder/services/Build.h"
#include "../Builder/services/ExecuteCompiler.h"
#include "../Builder/services/ExecuteLinker.h"
#include "../Builder/services/Build.h"
#include "../Builder/services/SmartLog.h"
#include "../Builder/services/LoggerConsole.h"
#include "../Builder/services/LoggerFile.h"
#include "../Builder/services/Logger.h"

namespace Trentino{
namespace Gen{
namespace BuilderGen{
   //*************************************************************************************************
   //                                          WRAPPERS
   //*************************************************************************************************

	//*************************************************************************************************
	//wrapper class definition for wrapper: Trentino_Example_Builder_ExecuteCompilerWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_Example_Builder_ExecuteCompilerWrapper
	void Trentino_Example_Builder_ExecuteCompilerWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::Example::Builder::ExecuteCompiler* const myInstance = static_cast<Trentino::Example::Builder::ExecuteCompiler*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="executeCompiler" )
      {
      		
			int& param0 = *static_cast<int*>(data->parameters()[0]);
      		myInstance->executeCompiler(  param0 );
      	
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_Example_Builder_ExecuteCompilerWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_Example_Builder_ExecuteCompilerWrapper**>(retVal) = new Trentino_Example_Builder_ExecuteCompilerWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_Example_Builder_ExecuteCompilerWrapper* p = static_cast<Trentino_Example_Builder_ExecuteCompilerWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_Example_Builder_ExecuteCompilerWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_ExecuteCompilerWrapper *"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_Example_Builder_ExecuteCompilerWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_Example_Builder_ExecuteCompilerWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_Example_Builder_ExecuteCompilerWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_Example_Builder_ExecuteCompilerWrapperRflx

   
	static InitializerTrentino_Example_Builder_ExecuteCompilerWrapperRflx mInitializerTrentino_Example_Builder_ExecuteCompilerWrapperRflx1; 

	//*************************************************************************************************
	//wrapper class definition for wrapper: Trentino_Example_Builder_ExecuteLinkerWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_Example_Builder_ExecuteLinkerWrapper
	void Trentino_Example_Builder_ExecuteLinkerWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::Example::Builder::ExecuteLinker* const myInstance = static_cast<Trentino::Example::Builder::ExecuteLinker*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="executeLinker" )
      {
      		
			int& param0 = *static_cast<int*>(data->parameters()[0]);
      		myInstance->executeLinker(  param0 );
      	
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_Example_Builder_ExecuteLinkerWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_Example_Builder_ExecuteLinkerWrapper**>(retVal) = new Trentino_Example_Builder_ExecuteLinkerWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_Example_Builder_ExecuteLinkerWrapper* p = static_cast<Trentino_Example_Builder_ExecuteLinkerWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_Example_Builder_ExecuteLinkerWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_ExecuteLinkerWrapper *"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_Example_Builder_ExecuteLinkerWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_Example_Builder_ExecuteLinkerWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_Example_Builder_ExecuteLinkerWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_Example_Builder_ExecuteLinkerWrapperRflx

   
	static InitializerTrentino_Example_Builder_ExecuteLinkerWrapperRflx mInitializerTrentino_Example_Builder_ExecuteLinkerWrapperRflx2; 

	//*************************************************************************************************
	//wrapper class definition for wrapper: Trentino_Example_Builder_BuildWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_Example_Builder_BuildWrapper
	void Trentino_Example_Builder_BuildWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::Example::Builder::Build* const myInstance = static_cast<Trentino::Example::Builder::Build*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="build" )
      {
      		
			int& param0 = *static_cast<int*>(data->parameters()[0]);
      		myInstance->build(  param0 );
      	
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_Example_Builder_BuildWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_Example_Builder_BuildWrapper**>(retVal) = new Trentino_Example_Builder_BuildWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_Example_Builder_BuildWrapper* p = static_cast<Trentino_Example_Builder_BuildWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_Example_Builder_BuildWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_BuildWrapper *"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_Example_Builder_BuildWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_Example_Builder_BuildWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_Example_Builder_BuildWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_Example_Builder_BuildWrapperRflx

   
	static InitializerTrentino_Example_Builder_BuildWrapperRflx mInitializerTrentino_Example_Builder_BuildWrapperRflx3; 

	//*************************************************************************************************
	//wrapper class definition for wrapper: Trentino_Example_Builder_SmartLogWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_Example_Builder_SmartLogWrapper
	void Trentino_Example_Builder_SmartLogWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::Example::Builder::SmartLog* const myInstance = static_cast<Trentino::Example::Builder::SmartLog*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="write" )
      {
      		
			std::string& param0 = *static_cast<std::string*>(data->parameters()[0]);
      		myInstance->write(  param0 );
      	
      }

		else
		      if(op =="writeFile" )
      {
      		
			std::string& param0 = *static_cast<std::string*>(data->parameters()[0]);
      		myInstance->writeFile(  param0 );
      	
      }

		else
		      if(op =="writeConsole" )
      {
      		
			std::string& param0 = *static_cast<std::string*>(data->parameters()[0]);
      		myInstance->writeConsole(  param0 );
      	
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_Example_Builder_SmartLogWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_Example_Builder_SmartLogWrapper**>(retVal) = new Trentino_Example_Builder_SmartLogWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_Example_Builder_SmartLogWrapper* p = static_cast<Trentino_Example_Builder_SmartLogWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_Example_Builder_SmartLogWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_SmartLogWrapper *"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_Example_Builder_SmartLogWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_Example_Builder_SmartLogWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_Example_Builder_SmartLogWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_Example_Builder_SmartLogWrapperRflx

   
	static InitializerTrentino_Example_Builder_SmartLogWrapperRflx mInitializerTrentino_Example_Builder_SmartLogWrapperRflx4; 

	//*************************************************************************************************
	//wrapper class definition for wrapper: Trentino_Example_Builder_LoggerConsoleWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_Example_Builder_LoggerConsoleWrapper
	void Trentino_Example_Builder_LoggerConsoleWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::Example::Builder::LoggerConsole* const myInstance = static_cast<Trentino::Example::Builder::LoggerConsole*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="writeConsole" )
      {
      		
			std::string& param0 = *static_cast<std::string*>(data->parameters()[0]);
      		myInstance->writeConsole(  param0 );
      	
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_Example_Builder_LoggerConsoleWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_Example_Builder_LoggerConsoleWrapper**>(retVal) = new Trentino_Example_Builder_LoggerConsoleWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_Example_Builder_LoggerConsoleWrapper* p = static_cast<Trentino_Example_Builder_LoggerConsoleWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_Example_Builder_LoggerConsoleWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_LoggerConsoleWrapper *"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_Example_Builder_LoggerConsoleWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_Example_Builder_LoggerConsoleWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_Example_Builder_LoggerConsoleWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_Example_Builder_LoggerConsoleWrapperRflx

   
	static InitializerTrentino_Example_Builder_LoggerConsoleWrapperRflx mInitializerTrentino_Example_Builder_LoggerConsoleWrapperRflx5; 

	//*************************************************************************************************
	//wrapper class definition for wrapper: Trentino_Example_Builder_LoggerFileWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_Example_Builder_LoggerFileWrapper
	void Trentino_Example_Builder_LoggerFileWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::Example::Builder::LoggerFile* const myInstance = static_cast<Trentino::Example::Builder::LoggerFile*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="writeFile" )
      {
      		
			std::string& param0 = *static_cast<std::string*>(data->parameters()[0]);
      		myInstance->writeFile(  param0 );
      	
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_Example_Builder_LoggerFileWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_Example_Builder_LoggerFileWrapper**>(retVal) = new Trentino_Example_Builder_LoggerFileWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_Example_Builder_LoggerFileWrapper* p = static_cast<Trentino_Example_Builder_LoggerFileWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_Example_Builder_LoggerFileWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_LoggerFileWrapper *"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_Example_Builder_LoggerFileWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_Example_Builder_LoggerFileWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_Example_Builder_LoggerFileWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_Example_Builder_LoggerFileWrapperRflx

   
	static InitializerTrentino_Example_Builder_LoggerFileWrapperRflx mInitializerTrentino_Example_Builder_LoggerFileWrapperRflx6; 

	//*************************************************************************************************
	//wrapper class definition for wrapper: Trentino_Example_Builder_LoggerWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_Example_Builder_LoggerWrapper
	void Trentino_Example_Builder_LoggerWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::Example::Builder::Logger* const myInstance = static_cast<Trentino::Example::Builder::Logger*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="log" )
      {
      		
			std::string& param0 = *static_cast<std::string*>(data->parameters()[0]);
      		myInstance->log(  param0 );
      	
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_Example_Builder_LoggerWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_Example_Builder_LoggerWrapper**>(retVal) = new Trentino_Example_Builder_LoggerWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_Example_Builder_LoggerWrapper* p = static_cast<Trentino_Example_Builder_LoggerWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_Example_Builder_LoggerWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_LoggerWrapper *"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_Example_Builder_LoggerWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_Example_Builder_LoggerWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_Example_Builder_LoggerWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_Example_Builder_LoggerWrapperRflx

   
	static InitializerTrentino_Example_Builder_LoggerWrapperRflx mInitializerTrentino_Example_Builder_LoggerWrapperRflx7; 



   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************

//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_LoggerProxy
//*************************************************************************************************
      Trentino_Example_Builder_LoggerProxy::Trentino_Example_Builder_LoggerProxy(Trentino::RuntimeModel::WireBase* wire):mWire(wire){}  
 void Trentino_Example_Builder_LoggerProxy::log( std::string logMsg)
 {
      assert(mWire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("log");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(1);
        	//here4
       		 	params.push_back(&logMsg);
      	    
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
   }

  //class declaration&definition
  //****************************************************************************************************
  //                                         InitializerTrentino_Example_Builder_LoggerProxyRflx
  //****************************************************************************************************
  //! \brief based on implementation.cpp/class (including the parsing of namespaces in the header)
  //! most parts are static right??
  //****************************************************************************************************
   class InitializerTrentino_Example_Builder_LoggerProxyRflx
   {
      //****************************************************************************************************
      //                                         newObjectWithParam()
      //****************************************************************************************************
      //! \brief
      //! \param void *
      //! \param void * retVal
      //! \param void * params[]
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL newObjectWithParam(void* /*thisPtr*/, void* retVal, void* params[])
      {

         *reinterpret_cast<Trentino_Example_Builder_LoggerProxy**>(retVal) = 
            new Trentino_Example_Builder_LoggerProxy(
            *reinterpret_cast<Trentino::RuntimeModel::WireBase**>(params[0]));   
      }

      //****************************************************************************************************
      //                                         deleteObject()
      //****************************************************************************************************
      //! \brief
      //! \param void * thisPtr
      //! \param void *
      //! \param void * *
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino_Example_Builder_LoggerProxy* p = 
            static_cast<Trentino_Example_Builder_LoggerProxy*>(thisPtr);
         delete p;
      }


      //construction
   public:
      //****************************************************************************************************
      //                   InitializerTrentino_Example_Builder_LoggerProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      InitializerTrentino_Example_Builder_LoggerProxyRflx()
      {
         // METHOD SIGNATURES
         static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_LoggerProxy *"
         };

         static const Trentino::Reflection::Data::Method::Param newParam[] = {"Trentino::RuntimeModel::Wire *"};

         static Trentino::Reflection::Data::Method::MetaData mdm[] = {
            { "new", "Trentino_Example_Builder_LoggerProxy *", newParam, COUNT_OF(newParam), newObjectWithParam }, 
            { "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
         };

         // OBJECT
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino_Example_Builder_LoggerProxy", 
            nullptr, 
            nullptr,
            0,
            mdm,
            COUNT_OF(mdm),
         };

         mmdoHandle = &mdo;

         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      //****************************************************************************************************
      //                ~InitializerTrentino_Example_Builder_LoggerProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      ~InitializerTrentino_Example_Builder_LoggerProxyRflx()
      {
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   }; //class InitializerTrentino_Example_Builder_LoggerProxyRflx
   static InitializerTrentino_Example_Builder_LoggerProxyRflx mInitializerTrentino_Example_Builder_LoggerProxyRflx8;


//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_ExecuteLinkerProxy
//*************************************************************************************************
      Trentino_Example_Builder_ExecuteLinkerProxy::Trentino_Example_Builder_ExecuteLinkerProxy(Trentino::RuntimeModel::WireBase* wire):mWire(wire){}  
 void Trentino_Example_Builder_ExecuteLinkerProxy::executeLinker( int versionID)
 {
      assert(mWire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("executeLinker");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(1);
        	//here4
       		 	params.push_back(&versionID);
      	    
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
   }

  //class declaration&definition
  //****************************************************************************************************
  //                                         InitializerTrentino_Example_Builder_ExecuteLinkerProxyRflx
  //****************************************************************************************************
  //! \brief based on implementation.cpp/class (including the parsing of namespaces in the header)
  //! most parts are static right??
  //****************************************************************************************************
   class InitializerTrentino_Example_Builder_ExecuteLinkerProxyRflx
   {
      //****************************************************************************************************
      //                                         newObjectWithParam()
      //****************************************************************************************************
      //! \brief
      //! \param void *
      //! \param void * retVal
      //! \param void * params[]
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL newObjectWithParam(void* /*thisPtr*/, void* retVal, void* params[])
      {

         *reinterpret_cast<Trentino_Example_Builder_ExecuteLinkerProxy**>(retVal) = 
            new Trentino_Example_Builder_ExecuteLinkerProxy(
            *reinterpret_cast<Trentino::RuntimeModel::WireBase**>(params[0]));   
      }

      //****************************************************************************************************
      //                                         deleteObject()
      //****************************************************************************************************
      //! \brief
      //! \param void * thisPtr
      //! \param void *
      //! \param void * *
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino_Example_Builder_ExecuteLinkerProxy* p = 
            static_cast<Trentino_Example_Builder_ExecuteLinkerProxy*>(thisPtr);
         delete p;
      }


      //construction
   public:
      //****************************************************************************************************
      //                   InitializerTrentino_Example_Builder_ExecuteLinkerProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      InitializerTrentino_Example_Builder_ExecuteLinkerProxyRflx()
      {
         // METHOD SIGNATURES
         static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_ExecuteLinkerProxy *"
         };

         static const Trentino::Reflection::Data::Method::Param newParam[] = {"Trentino::RuntimeModel::Wire *"};

         static Trentino::Reflection::Data::Method::MetaData mdm[] = {
            { "new", "Trentino_Example_Builder_ExecuteLinkerProxy *", newParam, COUNT_OF(newParam), newObjectWithParam }, 
            { "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
         };

         // OBJECT
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino_Example_Builder_ExecuteLinkerProxy", 
            nullptr, 
            nullptr,
            0,
            mdm,
            COUNT_OF(mdm),
         };

         mmdoHandle = &mdo;

         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      //****************************************************************************************************
      //                ~InitializerTrentino_Example_Builder_ExecuteLinkerProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      ~InitializerTrentino_Example_Builder_ExecuteLinkerProxyRflx()
      {
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   }; //class InitializerTrentino_Example_Builder_ExecuteLinkerProxyRflx
   static InitializerTrentino_Example_Builder_ExecuteLinkerProxyRflx mInitializerTrentino_Example_Builder_ExecuteLinkerProxyRflx9;


//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_ExecuteCompilerProxy
//*************************************************************************************************
      Trentino_Example_Builder_ExecuteCompilerProxy::Trentino_Example_Builder_ExecuteCompilerProxy(Trentino::RuntimeModel::WireBase* wire):mWire(wire){}  
 void Trentino_Example_Builder_ExecuteCompilerProxy::executeCompiler( int versionID)
 {
      assert(mWire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("executeCompiler");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(1);
        	//here4
       		 	params.push_back(&versionID);
      	    
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
   }

  //class declaration&definition
  //****************************************************************************************************
  //                                         InitializerTrentino_Example_Builder_ExecuteCompilerProxyRflx
  //****************************************************************************************************
  //! \brief based on implementation.cpp/class (including the parsing of namespaces in the header)
  //! most parts are static right??
  //****************************************************************************************************
   class InitializerTrentino_Example_Builder_ExecuteCompilerProxyRflx
   {
      //****************************************************************************************************
      //                                         newObjectWithParam()
      //****************************************************************************************************
      //! \brief
      //! \param void *
      //! \param void * retVal
      //! \param void * params[]
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL newObjectWithParam(void* /*thisPtr*/, void* retVal, void* params[])
      {

         *reinterpret_cast<Trentino_Example_Builder_ExecuteCompilerProxy**>(retVal) = 
            new Trentino_Example_Builder_ExecuteCompilerProxy(
            *reinterpret_cast<Trentino::RuntimeModel::WireBase**>(params[0]));   
      }

      //****************************************************************************************************
      //                                         deleteObject()
      //****************************************************************************************************
      //! \brief
      //! \param void * thisPtr
      //! \param void *
      //! \param void * *
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino_Example_Builder_ExecuteCompilerProxy* p = 
            static_cast<Trentino_Example_Builder_ExecuteCompilerProxy*>(thisPtr);
         delete p;
      }


      //construction
   public:
      //****************************************************************************************************
      //                   InitializerTrentino_Example_Builder_ExecuteCompilerProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      InitializerTrentino_Example_Builder_ExecuteCompilerProxyRflx()
      {
         // METHOD SIGNATURES
         static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_ExecuteCompilerProxy *"
         };

         static const Trentino::Reflection::Data::Method::Param newParam[] = {"Trentino::RuntimeModel::Wire *"};

         static Trentino::Reflection::Data::Method::MetaData mdm[] = {
            { "new", "Trentino_Example_Builder_ExecuteCompilerProxy *", newParam, COUNT_OF(newParam), newObjectWithParam }, 
            { "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
         };

         // OBJECT
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino_Example_Builder_ExecuteCompilerProxy", 
            nullptr, 
            nullptr,
            0,
            mdm,
            COUNT_OF(mdm),
         };

         mmdoHandle = &mdo;

         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      //****************************************************************************************************
      //                ~InitializerTrentino_Example_Builder_ExecuteCompilerProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      ~InitializerTrentino_Example_Builder_ExecuteCompilerProxyRflx()
      {
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   }; //class InitializerTrentino_Example_Builder_ExecuteCompilerProxyRflx
   static InitializerTrentino_Example_Builder_ExecuteCompilerProxyRflx mInitializerTrentino_Example_Builder_ExecuteCompilerProxyRflx10;


//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_LoggerConsoleProxy
//*************************************************************************************************
      Trentino_Example_Builder_LoggerConsoleProxy::Trentino_Example_Builder_LoggerConsoleProxy(Trentino::RuntimeModel::WireBase* wire):mWire(wire){}  
 void Trentino_Example_Builder_LoggerConsoleProxy::writeConsole( std::string logMsg)
 {
      assert(mWire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("writeConsole");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(1);
        	//here4
       		 	params.push_back(&logMsg);
      	    
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
   }

  //class declaration&definition
  //****************************************************************************************************
  //                                         InitializerTrentino_Example_Builder_LoggerConsoleProxyRflx
  //****************************************************************************************************
  //! \brief based on implementation.cpp/class (including the parsing of namespaces in the header)
  //! most parts are static right??
  //****************************************************************************************************
   class InitializerTrentino_Example_Builder_LoggerConsoleProxyRflx
   {
      //****************************************************************************************************
      //                                         newObjectWithParam()
      //****************************************************************************************************
      //! \brief
      //! \param void *
      //! \param void * retVal
      //! \param void * params[]
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL newObjectWithParam(void* /*thisPtr*/, void* retVal, void* params[])
      {

         *reinterpret_cast<Trentino_Example_Builder_LoggerConsoleProxy**>(retVal) = 
            new Trentino_Example_Builder_LoggerConsoleProxy(
            *reinterpret_cast<Trentino::RuntimeModel::WireBase**>(params[0]));   
      }

      //****************************************************************************************************
      //                                         deleteObject()
      //****************************************************************************************************
      //! \brief
      //! \param void * thisPtr
      //! \param void *
      //! \param void * *
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino_Example_Builder_LoggerConsoleProxy* p = 
            static_cast<Trentino_Example_Builder_LoggerConsoleProxy*>(thisPtr);
         delete p;
      }


      //construction
   public:
      //****************************************************************************************************
      //                   InitializerTrentino_Example_Builder_LoggerConsoleProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      InitializerTrentino_Example_Builder_LoggerConsoleProxyRflx()
      {
         // METHOD SIGNATURES
         static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_LoggerConsoleProxy *"
         };

         static const Trentino::Reflection::Data::Method::Param newParam[] = {"Trentino::RuntimeModel::Wire *"};

         static Trentino::Reflection::Data::Method::MetaData mdm[] = {
            { "new", "Trentino_Example_Builder_LoggerConsoleProxy *", newParam, COUNT_OF(newParam), newObjectWithParam }, 
            { "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
         };

         // OBJECT
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino_Example_Builder_LoggerConsoleProxy", 
            nullptr, 
            nullptr,
            0,
            mdm,
            COUNT_OF(mdm),
         };

         mmdoHandle = &mdo;

         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      //****************************************************************************************************
      //                ~InitializerTrentino_Example_Builder_LoggerConsoleProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      ~InitializerTrentino_Example_Builder_LoggerConsoleProxyRflx()
      {
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   }; //class InitializerTrentino_Example_Builder_LoggerConsoleProxyRflx
   static InitializerTrentino_Example_Builder_LoggerConsoleProxyRflx mInitializerTrentino_Example_Builder_LoggerConsoleProxyRflx11;


//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_LoggerFileProxy
//*************************************************************************************************
      Trentino_Example_Builder_LoggerFileProxy::Trentino_Example_Builder_LoggerFileProxy(Trentino::RuntimeModel::WireBase* wire):mWire(wire){}  
 void Trentino_Example_Builder_LoggerFileProxy::writeFile( std::string logMsg)
 {
      assert(mWire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("writeFile");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(1);
        	//here4
       		 	params.push_back(&logMsg);
      	    
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
   }

  //class declaration&definition
  //****************************************************************************************************
  //                                         InitializerTrentino_Example_Builder_LoggerFileProxyRflx
  //****************************************************************************************************
  //! \brief based on implementation.cpp/class (including the parsing of namespaces in the header)
  //! most parts are static right??
  //****************************************************************************************************
   class InitializerTrentino_Example_Builder_LoggerFileProxyRflx
   {
      //****************************************************************************************************
      //                                         newObjectWithParam()
      //****************************************************************************************************
      //! \brief
      //! \param void *
      //! \param void * retVal
      //! \param void * params[]
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL newObjectWithParam(void* /*thisPtr*/, void* retVal, void* params[])
      {

         *reinterpret_cast<Trentino_Example_Builder_LoggerFileProxy**>(retVal) = 
            new Trentino_Example_Builder_LoggerFileProxy(
            *reinterpret_cast<Trentino::RuntimeModel::WireBase**>(params[0]));   
      }

      //****************************************************************************************************
      //                                         deleteObject()
      //****************************************************************************************************
      //! \brief
      //! \param void * thisPtr
      //! \param void *
      //! \param void * *
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino_Example_Builder_LoggerFileProxy* p = 
            static_cast<Trentino_Example_Builder_LoggerFileProxy*>(thisPtr);
         delete p;
      }


      //construction
   public:
      //****************************************************************************************************
      //                   InitializerTrentino_Example_Builder_LoggerFileProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      InitializerTrentino_Example_Builder_LoggerFileProxyRflx()
      {
         // METHOD SIGNATURES
         static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_LoggerFileProxy *"
         };

         static const Trentino::Reflection::Data::Method::Param newParam[] = {"Trentino::RuntimeModel::Wire *"};

         static Trentino::Reflection::Data::Method::MetaData mdm[] = {
            { "new", "Trentino_Example_Builder_LoggerFileProxy *", newParam, COUNT_OF(newParam), newObjectWithParam }, 
            { "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
         };

         // OBJECT
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino_Example_Builder_LoggerFileProxy", 
            nullptr, 
            nullptr,
            0,
            mdm,
            COUNT_OF(mdm),
         };

         mmdoHandle = &mdo;

         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      //****************************************************************************************************
      //                ~InitializerTrentino_Example_Builder_LoggerFileProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      ~InitializerTrentino_Example_Builder_LoggerFileProxyRflx()
      {
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   }; //class InitializerTrentino_Example_Builder_LoggerFileProxyRflx
   static InitializerTrentino_Example_Builder_LoggerFileProxyRflx mInitializerTrentino_Example_Builder_LoggerFileProxyRflx12;


//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_BuildProxy
//*************************************************************************************************
      Trentino_Example_Builder_BuildProxy::Trentino_Example_Builder_BuildProxy(Trentino::RuntimeModel::WireBase* wire):mWire(wire){}  
 void Trentino_Example_Builder_BuildProxy::build( int versionID)
 {
      assert(mWire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("build");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(1);
        	//here4
       		 	params.push_back(&versionID);
      	    
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
   }

  //class declaration&definition
  //****************************************************************************************************
  //                                         InitializerTrentino_Example_Builder_BuildProxyRflx
  //****************************************************************************************************
  //! \brief based on implementation.cpp/class (including the parsing of namespaces in the header)
  //! most parts are static right??
  //****************************************************************************************************
   class InitializerTrentino_Example_Builder_BuildProxyRflx
   {
      //****************************************************************************************************
      //                                         newObjectWithParam()
      //****************************************************************************************************
      //! \brief
      //! \param void *
      //! \param void * retVal
      //! \param void * params[]
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL newObjectWithParam(void* /*thisPtr*/, void* retVal, void* params[])
      {

         *reinterpret_cast<Trentino_Example_Builder_BuildProxy**>(retVal) = 
            new Trentino_Example_Builder_BuildProxy(
            *reinterpret_cast<Trentino::RuntimeModel::WireBase**>(params[0]));   
      }

      //****************************************************************************************************
      //                                         deleteObject()
      //****************************************************************************************************
      //! \brief
      //! \param void * thisPtr
      //! \param void *
      //! \param void * *
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino_Example_Builder_BuildProxy* p = 
            static_cast<Trentino_Example_Builder_BuildProxy*>(thisPtr);
         delete p;
      }


      //construction
   public:
      //****************************************************************************************************
      //                   InitializerTrentino_Example_Builder_BuildProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      InitializerTrentino_Example_Builder_BuildProxyRflx()
      {
         // METHOD SIGNATURES
         static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_Builder_BuildProxy *"
         };

         static const Trentino::Reflection::Data::Method::Param newParam[] = {"Trentino::RuntimeModel::Wire *"};

         static Trentino::Reflection::Data::Method::MetaData mdm[] = {
            { "new", "Trentino_Example_Builder_BuildProxy *", newParam, COUNT_OF(newParam), newObjectWithParam }, 
            { "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
         };

         // OBJECT
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino_Example_Builder_BuildProxy", 
            nullptr, 
            nullptr,
            0,
            mdm,
            COUNT_OF(mdm),
         };

         mmdoHandle = &mdo;

         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      //****************************************************************************************************
      //                ~InitializerTrentino_Example_Builder_BuildProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      ~InitializerTrentino_Example_Builder_BuildProxyRflx()
      {
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   }; //class InitializerTrentino_Example_Builder_BuildProxyRflx
   static InitializerTrentino_Example_Builder_BuildProxyRflx mInitializerTrentino_Example_Builder_BuildProxyRflx13;



}//namespace Gen
}//namespace Trentino
} //namespace BuilderGen

