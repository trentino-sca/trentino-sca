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

#ifndef TrentinoConsoleContextH
#define TrentinoConsoleContextH

//baseclass
#include "TrentinoConsoleContextAccessor.h"

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
   //                                           Context
   //********************************************************************************************** 
   //! \brief Serves as a container for different information needed during the execution of a 
   //!        command.
   //!
   //! \sa ContextManager
   //**********************************************************************************************
   class Context : public ContextAccessor
   {
      //construction
   public:
      //*******************************************************************************************
      //                                     Context()
      //******************************************************************************************* 
      //! \brief Constructs a Context with all members initialized with default values.
      //*******************************************************************************************
      Context();
      ~Context();

      //services
   public:
      //*******************************************************************************************
      //                               managementInterface()
      //******************************************************************************************* 
      //! \brief Returns and instance implementing the ManagementInterface.
      //! \return Shared pointer to a ManagementInterface.
      //! \sa setManagementInterface()
      //*******************************************************************************************
      virtual Trentino::ManagementInterface* managementInterface() const;

      //*******************************************************************************************
      //                                        runtimeAPI()
      //******************************************************************************************* 
      //! \brief Returns the Trentino Runtime API.
      //! \return Shared pointer to a RuntimeAPI object representing the Trentino Runtime API.
      //! \sa Trentino::Core::RuntimeAPI
      //*******************************************************************************************
      virtual Trentino::Core::RuntimeAPIPtr runtimeAPI() const;

      //*******************************************************************************************
      //                                        setRuntimeAPI()
      //******************************************************************************************* 
      //! \brief Sets the Trentino Runtime API.
      //! \param[in] Shared pointer to a RuntimeAPI object representing the Trentino Runtime 
      //!            DLL
      //! \sa runtimeDLL()
      //*******************************************************************************************
      void setRuntimeAPI(const Trentino::Core::RuntimeAPIPtr runtimeDLL);

            //*******************************************************************************************
      //                                        cleanUp()
      //******************************************************************************************* 
      //! \brief delete all data stored in the context. Will cause Runtime to shut down
      //*******************************************************************************************
      void cleanUp();
      
      //data
   private:
      //! Shared pointer to an instance implementing the ManagementInterface.
      Trentino::Core::RuntimeAPIPtr  mRuntimeAPI;
   }; //class Context

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleContextH
