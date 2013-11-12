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

#ifndef TrentinoUtilsDebugHeapSnapshotH
#define TrentinoUtilsDebugHeapSnapshotH

#ifdef WIN32
#ifdef UTILS_EXPORTS
#define DEBUG_IMPORT_EXPORT __declspec(dllexport)
#else
#define DEBUG_IMPORT_EXPORT __declspec(dllimport)       
#endif //UTILS_EXPORTS
#else
#define DEBUG_IMPORT_EXPORT
#endif //WIN32

//standard
#include <boost/shared_ptr.hpp>

//specific
#include "TrentinoUtils.h"

namespace Trentino{
namespace Utils{
//! \defgroup Debug
namespace Debug
{
   //class declaration
    //**********************************************************************************************
   //                             HeapSnapshot
   //**********************************************************************************************
   //! \brief Heapsnapshot uses the Windows Debug Heap.
   //! \todo Must implemented for unix
   //! If you create a new HeapSnapshot class under Windows following DebugHeap flags will be set:
   //! _CRTDBG_CHECK_ALWAYS_DF, _CRTDBG_ALLOC_MEM_DF, _CRTDBG_LEAK_CHECK_DF and
   //! _CRTDBG_DELAY_FREE_MEM_DF
   //! Old state of Debug-Heap will be restored if instance of HeapSnapshot is destroyed.
   //! The main capability for this class is to make some snapshots between some allocations/
   //! deallocations. So you can cascade different snapshots to make various peeks of memory.
   //! \todo Output must be able to be redirected
   //**********************************************************************************************
  class HeapSnapshot
   {
      //construction
   public:
      //*******************************************************************************************
      //                                   constructor()                               
      //*******************************************************************************************
      //! Creates a new snapshot objects, saves old Debug-Heap flags and sets
      //! _CRTDBG_CHECK_ALWAYS_DF, _CRTDBG_ALLOC_MEM_DF, _CRTDBG_LEAK_CHECK_DF and
      //! _CRTDBG_DELAY_FREE_MEM_DF flags of its own.
      //*******************************************************************************************
      DEBUG_IMPORT_EXPORT HeapSnapshot();

      //*******************************************************************************************
      //                                     destructor()                               
      //*******************************************************************************************
      //! Restores old snapshot states of debug heap. 
      //! \attention Beware of destruction order of HeapSnapshot objects. Should be the same order
      //! like during destruction.
      //*******************************************************************************************
      DEBUG_IMPORT_EXPORT ~HeapSnapshot();

      //services
   public:
      //*******************************************************************************************
      //                                     begin()                               
      //*******************************************************************************************
      //! Starts snapshot of heap, checks memory consistency too.
      //*******************************************************************************************
      void DEBUG_IMPORT_EXPORT begin();

      //*******************************************************************************************
      //                                     end()                               
      //*******************************************************************************************
      //! Ends a snapshot. Can be other instance of snapshot, so we can compare other begin()
      //! end() sequences of differenc heap snapshots. Checks memory consistency.
      //! Does a mem difference between begin of this snapshot and end of the other snapshot
      //! You should call \sa end() in other snapshot before you call this method.
      //! \param[in] Snapshot to compare with
      //*******************************************************************************************
      void DEBUG_IMPORT_EXPORT end(const HeapSnapshot& snapshot);

      //*******************************************************************************************
      //                                     end()                               
      //*******************************************************************************************
      //! Ends a snapshot and compares it with the state as you have called begin(). 
      //! Does make a MemDifference and checks memory consistency.
      //*******************************************************************************************
      void DEBUG_IMPORT_EXPORT end();

      //*******************************************************************************************
      //                                     dumpLeaks()                               
      //*******************************************************************************************
      //! Should be called if you shutdown your application.
      //! Dumps all open allocations. 
      //! \attention Beware of static initializers which have still objects allocated on heap.
      //*******************************************************************************************
      void DEBUG_IMPORT_EXPORT dumpLeaks();

      //data
   private:
      //! Used to store old Debug-Heap flag
      int mCRTFlag;
#ifdef WIN32
      // Used to store snapshot begin data
      CrtMemStatePtr mMemStatePtrBegin;
      // Used to store snapshot end data
      CrtMemStatePtr mMemStatePtrEnd;
#endif //WIN32
   };

   //inline
   #include "TrentinoUtilsDebugHeapSnapshot.inl"

}//namespace Debug
}//namespace Utils
}//namespace Trentino


#endif//TrentinoUtilsDebugHeapSnapshotH
