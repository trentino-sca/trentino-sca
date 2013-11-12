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

#ifndef TrentinoConsoleContextAccessorH
#define TrentinoConsoleContextAccessorH

//specific
#include "./../Utils/TrentinoUtils.h"
#include "./../Runtime/Core/TrentinoCore.h"

namespace Trentino
{
   class ManagementInterface;
} //namespace Trentino

namespace Trentino{
namespace Console
{
   //**********************************************************************************************
   //                                      ContextAccessor
   //********************************************************************************************** 
   //! \brief Interface containing only the getter methods for a Context.
   //!
   //! A ContextAccessor is meant to be used by classes that should have only a non-modifying 
   //! access to a Context. 
   //! \sa Context, ContextAccessingCommand
   //**********************************************************************************************
   class ContextAccessor
   {
      //construction
   public:
      virtual ~ContextAccessor(){}

      //services
   public:
      //*******************************************************************************************
      //                               managementInterface()
      //******************************************************************************************* 
      //! \brief Returns and instance implementing the ManagementInterface.
      //! \return Shared pointer to a ManagementInterface.     
      //*******************************************************************************************
      virtual Trentino::ManagementInterface* managementInterface() const = 0;    
      virtual Trentino::Core::RuntimeAPIPtr runtimeAPI() const = 0;
   
   }; //class ContextAccessor

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleContextAccessorH