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
#ifndef BuilderGen_Trentino_Example_Builder_TrentinoGenProxiesWrappersH
#define BuilderGen_Trentino_Example_Builder_TrentinoGenProxiesWrappersH
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
	//wrapper class declaration Trentino_Example_Builder_ExecuteCompilerWrapper
	//*************************************************************************************************
   
	class Trentino_Example_Builder_ExecuteCompilerWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_Example_Builder_ExecuteCompilerWrapper
  

	//*************************************************************************************************
	//wrapper class declaration Trentino_Example_Builder_ExecuteLinkerWrapper
	//*************************************************************************************************
   
	class Trentino_Example_Builder_ExecuteLinkerWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_Example_Builder_ExecuteLinkerWrapper
  

	//*************************************************************************************************
	//wrapper class declaration Trentino_Example_Builder_BuildWrapper
	//*************************************************************************************************
   
	class Trentino_Example_Builder_BuildWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_Example_Builder_BuildWrapper
  

	//*************************************************************************************************
	//wrapper class declaration Trentino_Example_Builder_SmartLogWrapper
	//*************************************************************************************************
   
	class Trentino_Example_Builder_SmartLogWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_Example_Builder_SmartLogWrapper
  

	//*************************************************************************************************
	//wrapper class declaration Trentino_Example_Builder_LoggerConsoleWrapper
	//*************************************************************************************************
   
	class Trentino_Example_Builder_LoggerConsoleWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_Example_Builder_LoggerConsoleWrapper
  

	//*************************************************************************************************
	//wrapper class declaration Trentino_Example_Builder_LoggerFileWrapper
	//*************************************************************************************************
   
	class Trentino_Example_Builder_LoggerFileWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_Example_Builder_LoggerFileWrapper
  

	//*************************************************************************************************
	//wrapper class declaration Trentino_Example_Builder_LoggerWrapper
	//*************************************************************************************************
   
	class Trentino_Example_Builder_LoggerWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_Example_Builder_LoggerWrapper
  



   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************

//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_LoggerProxy
//*************************************************************************************************
 class Trentino_Example_Builder_LoggerProxy :public Trentino::Example::Builder::Logger
   {
      //construction
   public:
      Trentino_Example_Builder_LoggerProxy(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
  		virtual void log ( std::string logMsg);
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class Trentino_Example_Builder_LoggerProxy

//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_ExecuteLinkerProxy
//*************************************************************************************************
 class Trentino_Example_Builder_ExecuteLinkerProxy :public Trentino::Example::Builder::ExecuteLinker
   {
      //construction
   public:
      Trentino_Example_Builder_ExecuteLinkerProxy(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
  		virtual void executeLinker ( int versionID);
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class Trentino_Example_Builder_ExecuteLinkerProxy

//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_ExecuteCompilerProxy
//*************************************************************************************************
 class Trentino_Example_Builder_ExecuteCompilerProxy :public Trentino::Example::Builder::ExecuteCompiler
   {
      //construction
   public:
      Trentino_Example_Builder_ExecuteCompilerProxy(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
  		virtual void executeCompiler ( int versionID);
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class Trentino_Example_Builder_ExecuteCompilerProxy

//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_LoggerConsoleProxy
//*************************************************************************************************
 class Trentino_Example_Builder_LoggerConsoleProxy :public Trentino::Example::Builder::LoggerConsole
   {
      //construction
   public:
      Trentino_Example_Builder_LoggerConsoleProxy(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
  		virtual void writeConsole ( std::string logMsg);
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class Trentino_Example_Builder_LoggerConsoleProxy

//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_LoggerFileProxy
//*************************************************************************************************
 class Trentino_Example_Builder_LoggerFileProxy :public Trentino::Example::Builder::LoggerFile
   {
      //construction
   public:
      Trentino_Example_Builder_LoggerFileProxy(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
  		virtual void writeFile ( std::string logMsg);
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class Trentino_Example_Builder_LoggerFileProxy

//*************************************************************************************************
//Proxy class definition Trentino_Example_Builder_BuildProxy
//*************************************************************************************************
 class Trentino_Example_Builder_BuildProxy :public Trentino::Example::Builder::Build
   {
      //construction
   public:
      Trentino_Example_Builder_BuildProxy(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
  		virtual void build ( int versionID);
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class Trentino_Example_Builder_BuildProxy


}//namespace Gen
}//namespace Trentino
} //namespace BuilderGen

#endif //BuilderGen_Trentino_Example_Builder_TrentinoGenProxiesWrappersH

