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

//header
#include "TrentinoDiscoveryTaskQueue.h"
#include "TrentinoDiscoveryTask.h"

using namespace Trentino::Discovery;

boost::mutex DiscoveryTaskQueue::mMutex;
boost::condition_variable DiscoveryTaskQueue::mCond;

void DiscoveryTaskQueue::enqueue(const DiscoveryTaskSharedPtr discoveryTask)
{
   // Acquire lock on the queue
   boost::unique_lock<boost::mutex> lock(mMutex);
   
   // Add the data to the queue
   mQueue.push(discoveryTask);
   
   // Notify others that data is ready
   mCond.notify_one();
} // Lock is automatically released here

// Get data from the queue. Wait for data if not available
DiscoveryTaskQueue::DiscoveryTaskSharedPtr DiscoveryTaskQueue::dequeue()
{
   // Acquire lock on the queue
   boost::unique_lock<boost::mutex> lock(mMutex);

   // When there is no data, wait till someone fills it.
   // Lock is automatically released in the wait and obtained
   // again after the wait
   while (mQueue.empty()) 
   {
      mCond.wait(lock);
   }

   // Retrieve the data from the queue
   DiscoveryTaskSharedPtr discoveryTask = mQueue.front();
   mQueue.pop();
   return discoveryTask;

} // Lock is automatically released here

// Clear out all the tasks from the queue
void DiscoveryTaskQueue::clear()
{
   boost::unique_lock<boost::mutex> lock(mMutex);

   while(mQueue.empty() != true) 
   {
      mQueue.pop();
   }
} // Lock is automatically released here

// Check out if the queue is empty
bool DiscoveryTaskQueue::empty()
{
   return mQueue.empty();
} 
