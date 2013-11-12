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

#ifndef TrentinoDiscoveryTaskQueueH
#define TrentinoDiscoveryTaskQueueH

// standart
#include <boost/thread.hpp>

#include <queue>

// specific
#include "TrentinoDiscoveryTask.h"

using namespace boost;
using namespace boost::this_thread;


namespace Trentino{
namespace Discovery
{
   //class declaration
   //**********************************************************************************************
   //                             DiscoveryTaskQueue
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief Thread safe discovery task queue to host discovery tasks
   //**********************************************************************************************
   class DiscoveryTaskQueue
   {
      //additional
   private:
      typedef boost::shared_ptr<DiscoveryTask> DiscoveryTaskSharedPtr;

      //services
   public:
       //****************************************************************************************
      //                               enqueue()
      //****************************************************************************************
      //! \brief Add data to the queue and notify others
      //****************************************************************************************
      void enqueue(const DiscoveryTaskSharedPtr discoveryTask);

      //****************************************************************************************
      //                               dequeue()
      //****************************************************************************************
      //! \brief Get data from the queue. Wait for data if not available
      //****************************************************************************************
      DiscoveryTaskSharedPtr dequeue();

      //****************************************************************************************
      //                               clear()
      //****************************************************************************************
      //! \brief Clear out the pending tasks
      //****************************************************************************************
      void clear();

      //****************************************************************************************
      //                               empty()
      //****************************************************************************************
      //! \brief returns true if the queue is empty
      //****************************************************************************************
      bool empty();

      //data
   private://TODO compile error once private?????
      //! Use STL queue to store data
     std::queue<DiscoveryTaskSharedPtr> mQueue;
   public:
      // std::queue<DiscoveryTask> mQueue;
       //! The mutex to synchronise on
      static boost::mutex mMutex;

      //! The condition to wait for
      static boost::condition_variable mCond; 
   };


} // namespace Discovery
} // namespace Trentino
#endif //TrentinoDiscoveryTaskQueueH