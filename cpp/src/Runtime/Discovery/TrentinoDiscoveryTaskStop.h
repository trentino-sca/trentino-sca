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

#ifndef TrentinoDiscoveryTaskStopH
#define TrentinoDiscoveryTaskStopH

// standart
#include <string>

// specific
#include "TrentinoDiscoveryTask.h"
#include "TrentinoDiscoveryMethodInterface.h"
#include "../SCAModel/TrentinoSCAModelMetadata.h"

namespace Trentino{
namespace Discovery
{
     

   //class declaration
   //**********************************************************************************************
   //                             DiscoveryTaskStart
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief Discovery task to stop the specific discovery method implementation
   //
   //**********************************************************************************************
   class DiscoveryTaskStop : public DiscoveryTask
   {
      // additional
   public:
        typedef void (*onStopFuncPtr)();
        // friend becuase DiscoverySLP will be capable of using the member callbacks of the task
        //friend class Trentino::Discovery::SLP::OpenSLP::TrentinoDiscoverySlp;

      //construction
   public:
      //****************************************************************************************
      //                               DiscoveryTaskStop()
      //****************************************************************************************
      //! \brief Actual constructor to be used each time a stop task is created
      //!
      //! \param callback function of the discovery layer to be called once a task is finished 
      //!  without success
      //! \param retryCount
      //! \param retryInterval
      //! \param methodInterface Interface used for actually doing the task(for example implemented
      //!  by OpenSLP)
      //! \param runtimeCB Callback to be triggered once the task succeeds or once all the 
      //!  retries are consumed.
      //****************************************************************************************
      DiscoveryTaskStop(DiscoveryTask::discoveryFrameWorkCBFuncPtr discoveryFrameworkCB, 
      int retryCount,
      int retryInterval,
      DiscoveryMethodInterface* methodInterface);

      ~DiscoveryTaskStop();

	//services
	public:
      //****************************************************************************************
      //                               execute()
      //****************************************************************************************
      //! \brief Overridden func of base
      //****************************************************************************************
      bool execute();

      //****************************************************************************************
      //                               onTaskCancelled()
      //****************************************************************************************
      //! \brief Once all the retries fail to call the runtimeCB with the last error
      //****************************************************************************************
      void onTaskCancelled();

      //data
   private:

      //! onStopCallback to be triggered once the stop task is finished
      onStopFuncPtr mOnStopCB;
      
   }; // class DiscoveryTaskStop


} // namespace Discovery
} // namespace Trentino
#endif //TrentinoDiscoveryTaskStopH