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

#ifndef TrentinoCoreBootstrappingExplicitLinkingInterfaceH
#define TrentinoCoreBootstrappingExplicitLinkingInterfaceH

//standard
#include <string>

//specific
#include "../../Global/TrentinoGlobal.h"
#include "TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "TrentinoCoreBootstrappingRuntimeConfiguration.h"

namespace Trentino
{
   class ManagementInterface;
} //namespace Trentino

namespace Trentino{
namespace Core{
namespace Bootstrapping
{
   class RuntimeConfiguration;

   const std::string CreateRuntimeConfiguration1FuncName = "createRuntimeConfiguration1";
   const std::string BootDefaultFuncName = "bootDefault";
   const std::string BootFuncName = "boot";
   const std::string GetManagementInterfaceFuncName = "getManagementInterface";
   const std::string ShutdownFuncName = "shutdown";   

   typedef Trentino::Core::Bootstrapping::RuntimeConfiguration* 
      (TRENTINO_CDECL *CreateRuntimeConfiguration1Func)(
         Trentino::Core::Bootstrapping::RuntimeConfiguration::Source, const char*);
   typedef void (TRENTINO_CDECL *BootFunc) (
      const Trentino::Core::Bootstrapping::RuntimeConfiguration*);
   typedef void (TRENTINO_CDECL *BootDefaultFunc)();
   typedef Trentino::ManagementInterface* 
      (TRENTINO_CDECL *GetManagementInterfaceFunc) ();
   typedef void (TRENTINO_CDECL *ShutdownFunc) ();
   

} //namespace Bootstrapping
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreBootstrappingExplicitLinkingInterfaceH