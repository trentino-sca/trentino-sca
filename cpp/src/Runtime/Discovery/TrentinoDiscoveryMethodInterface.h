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

#ifndef TrentinoDiscoveryMethodInterfaceH
#define TrentinoDiscoveryMethodInterfaceH

// standart
#include <string>
#include <boost/shared_ptr.hpp>

// specific
#include "../SCAModel/TrentinoSCAModelMetadata.h"
#include "TrentinoDiscoveryTask.h"

using namespace boost;
using namespace Trentino::SCA::Model;

namespace Trentino{
namespace Discovery
{

   //class declaration
   //**********************************************************************************************
   //                             DiscoveryMethodInterface
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief Interface that needs to be implemented by each dll implementing a certain discovery 
   //! method
   //**********************************************************************************************
   class DiscoveryMethodInterface
   {
      //additional 
   public:
      typedef boost::shared_ptr<Trentino::Discovery::DiscoveryTask> DiscoveryTaskSharedPtr;

      //construction
   public:
      virtual ~DiscoveryMethodInterface() {}; 

      //services
   public:
      //****************************************************************************************
      //                                start()
      //****************************************************************************************
      //! \brief Function to start the specific discovery method implementation
      //****************************************************************************************
      virtual void start(Trentino::Discovery::DiscoveryTask*  task) = 0;

      //****************************************************************************************
      //                                stop()
      //****************************************************************************************
      //! \brief Function to stop the specific discovery method implementation
      //****************************************************************************************
      virtual void stop(Trentino::Discovery::DiscoveryTask*  task) = 0;

      //****************************************************************************************
      //                                registerSrv()
      //****************************************************************************************
      //! \brief Function to register a service with a the specific discovery method implementation
      //
      //****************************************************************************************
      virtual void registerSrv(Trentino::Discovery::DiscoveryTask*  task) = 0;
      
      //****************************************************************************************
      //                                deregisterSrv()
      //****************************************************************************************
      //! \brief Function to deregister a service with a the specific discovery method 
      //! implementation
      //****************************************************************************************
      virtual void deregisterSrv(Trentino::Discovery::DiscoveryTask* task) = 0;
            
      //****************************************************************************************
      //                                findSrv()
      //****************************************************************************************
      //! \brief Function to find a service with a the specific discovery method implementation
      //****************************************************************************************
      virtual void findSrv(Trentino::Discovery::DiscoveryTask*  task) = 0;
   
   }; // class DiscoveryMethodInterface


} // namespace Discovery
} // namespace Trentino

#endif//TrentinoDiscoveryMethodInterfaceH