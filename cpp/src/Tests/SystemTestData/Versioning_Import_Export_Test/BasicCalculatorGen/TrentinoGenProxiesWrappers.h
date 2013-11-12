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


#include <Global/TrentinoGlobal.h>
#include <Runtime/Invocation/TrentinoInvocationInvocationData.h>
#include <Runtime/Invocation/TrentinoInvocationInvocationContext.h> //! \todo: currently not used
#include <Runtime/Invocation/TrentinoInvocationInvokerBase.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModelWireBase.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModelServiceBase.h>
#include <Runtime/ReflectionRuntime/TrentinoReflectionRegistration.h>
#include <Runtime/Invocation/TrentinoInvocationGen.h>

//specific
#pragma warning(push)
#pragma warning(disable:4290)
#include "TrentinoExampleBasicCalculatorCalculatorImpl.h"
#pragma warning(pop)

namespace Trentino{
namespace Gen{

using namespace Trentino::Example::Logging;


   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************

//*************************************************************************************************
//Proxy class definition Trentino_Example_Logging_LoggingServiceProxy
//*************************************************************************************************
 class Trentino_Example_Logging_LoggingServiceProxy :public Trentino::Example::Logging::LoggingService
   {
      //construction
   public:
      Trentino_Example_Logging_LoggingServiceProxy(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
  		virtual void logError ( const char* log);
  		virtual void logDebug ( const char* log);
  		virtual void logInfo ( const char* log);
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class Trentino_Example_Logging_LoggingServiceProxy


}//namespace Gen
}//namespace Trentino

#endif //TrentinoGenProxiesWrappersH

