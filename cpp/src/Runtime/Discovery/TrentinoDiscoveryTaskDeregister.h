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

#ifndef TrentinoDiscoveryTaskDeregisterH
#define TrentinoDiscoveryTaskDeregisterH

// standart
#include <string>

// specific
#include "TrentinoDiscoveryTask.h"

using namespace Trentino::SCA::Model;

namespace Trentino{
namespace Discovery
{

   //class declaration
   //**********************************************************************************************
   //                             DiscoveryTask
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief Discovery tasks are implemented here
   //
   //! Consider converting to command pattern but needs further heap allocation 
   //**********************************************************************************************
   class DiscoveryTaskDeregister : public DiscoveryTask
   {
      //construction
   public:
      //****************************************************************************************
      //                               DiscoveryTaskDeregister()
      //****************************************************************************************
      //! \brief Actual constructor to be used each time a register service task is created
      //****************************************************************************************
      DiscoveryTaskDeregister(discoveryFrameWorkCBFuncPtr funcPtr, 
               int retryCount,
               int retryInterval,
               DiscoveryMethodInterface* methodInterface,
               std::string serviceIdentifier);

         //services
   public:
      //****************************************************************************************
      //                               execute()
      //****************************************************************************************
      //! \brief Overridden func of base
      //****************************************************************************************
      bool execute();

      std::string getServiceIdentifier()
      {
         return mServiceIdentifier;
      }

       //data
   private:
      //! Service identifier to be used for registering the service
      std::string mServiceIdentifier;

   }; // class DiscoveryTaskDeregister


} // namespace Discovery
} // namespace Trentino
#endif //TrentinoDiscoveryTaskDeregisterH