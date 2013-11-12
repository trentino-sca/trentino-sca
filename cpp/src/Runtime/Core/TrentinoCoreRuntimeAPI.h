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

#ifndef TrentinoCoreRuntimeAPIH
#define TrentinoCoreRuntimeAPIH

//standard
#include <string>
#include <stdexcept>
#include <boost/smart_ptr/make_shared.hpp>

//specific
#include "./../../Utils/TrentinoUtils.h"
#include "./../../Utils/TrentinoUtilsDynamicLibrary.h"
#include "./../../Utils/TrentinoUtilsLogging.h"

#include "TrentinoCoreBootstrappingExplicitLinkingInterface.h"


//forward declarations
namespace Trentino
{
   class ManagementInterface;
} //namespace Trentino


//class declaration
namespace Trentino{
namespace Core
{
   class RuntimeAPI
   {
      //construction
   public:
      RuntimeAPI(const std::string& runtimeFilePath, const std::string& commandLine);
      //*******************************************************************************************
      //                               Destructor()
      //******************************************************************************************* 
      //! \brief Destructor
      //******************************************************************************************* 
      ~RuntimeAPI();
   private:
      //*******************************************************************************************
      //                               Default constructor()
      //******************************************************************************************* 
      //! \brief Default constructor
      //******************************************************************************************* 
      RuntimeAPI();
      //! not copyable
      RuntimeAPI(const RuntimeAPI&);

      //operators
   private:
      //! not assignable
      const RuntimeAPI& operator=(const RuntimeAPI&);

      //services
   public:
      //*******************************************************************************************
      //                               managementInterface()
      //******************************************************************************************* 
      //! \brief Returns and instance implementing the ManagementInterface.
      //! \return Raw pointer to a ManagementInterface.
      //*******************************************************************************************
      Trentino::ManagementInterface* managementInterface() const;

      //*******************************************************************************************
      //                                        runtimeDLL()
      //******************************************************************************************* 
      //! \brief Returns the Trentino Runtime DLL.
      //! \return Shared pointer to a DynamicLibrary object representing the Trentino Runtime DLL.
      //*******************************************************************************************
      const Trentino::Utils::DynamicLibraryPtr& runtimeDLL() const;

      //*******************************************************************************************
      //                                        create()
      //******************************************************************************************* 
      //! \brief Creates internal representation of runtime.
      //******************************************************************************************* 
      void create(const std::string& runtimeFilePath, const std::string& commandLine);

      //*******************************************************************************************
      //                                        destroy()
      //******************************************************************************************* 
      //! \brief Destroys internal representation of runtime.
      //******************************************************************************************* 
      void destroy();

      // data
   private:
      //! Raw pointer to an instance implementing the ManagementInterface.
      Trentino::ManagementInterface*  mManagementInterface;
      //! Shared pointer to the Trentino Runtime DLL. 
      Trentino::Utils::DynamicLibraryPtr mRuntimeDLL;
   }; //class RuntimeAPI

   #include "TrentinoCoreRuntimeAPI.inl"

} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreRuntimeAPIH
