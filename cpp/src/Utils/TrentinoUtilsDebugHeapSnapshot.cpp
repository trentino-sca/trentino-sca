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
#include "TrentinoUtilsDebugHeapSnapshot.h"

//standard
#ifdef WIN32
   #include <Windows.h>
#endif//WIN32

using namespace Trentino::Utils::Debug;


HeapSnapshot::HeapSnapshot()
{
   #ifdef WIN32
      mCRTFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
      _CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF |
         _CRTDBG_ALLOC_MEM_DF |
         _CRTDBG_LEAK_CHECK_DF | 
         _CRTDBG_DELAY_FREE_MEM_DF);
   #else
      mCRTFlag = 0;
   #endif//WIN32
}

HeapSnapshot::~HeapSnapshot()
{
   #ifdef WIN32
      _CrtSetDbgFlag(mCRTFlag);
   #endif//WIN32
}


void HeapSnapshot::begin()
{
#ifdef WIN32
   _CrtMemDumpAllObjectsSince(NULL);
   mMemStatePtrBegin.reset(new _CrtMemState);
   _CrtMemCheckpoint(mMemStatePtrBegin.get());
   _CrtCheckMemory();
#endif//WIN32
}

void HeapSnapshot::end(const HeapSnapshot& snapshot)
{
#ifdef WIN32
   //only for safety
   if(mMemStatePtrBegin.get() == nullptr)
   {
      begin();
   }

   if(snapshot.mMemStatePtrEnd.get() != nullptr)
   {
      _CrtMemDumpAllObjectsSince(snapshot.mMemStatePtrEnd.get());
      mMemStatePtrEnd.reset(new _CrtMemState);
      _CrtMemCheckpoint(mMemStatePtrEnd.get());
      _CrtMemState checkCurrentState;
      (void)checkCurrentState;
      _CrtMemDifference(&checkCurrentState, snapshot.mMemStatePtrEnd.get(), mMemStatePtrEnd.get());
      _CrtMemDumpStatistics(&checkCurrentState);
      _CrtCheckMemory();
   }
#endif//WIN32
}

void HeapSnapshot::end()
{
#ifdef WIN32
   if(mMemStatePtrBegin.get() != nullptr)
   {
      _CrtMemDumpAllObjectsSince(mMemStatePtrBegin.get());
      mMemStatePtrEnd.reset(new _CrtMemState);
      _CrtMemCheckpoint(mMemStatePtrEnd.get());

      _CrtMemState checkCurrentState;
      (void)checkCurrentState;
      _CrtMemDifference(&checkCurrentState, mMemStatePtrBegin.get(), mMemStatePtrEnd.get());
      _CrtMemDumpStatistics(&checkCurrentState);
      _CrtCheckMemory();
   }
#endif//WIN32
}


void HeapSnapshot::dumpLeaks()
{
#ifdef WIN32
   _CrtDumpMemoryLeaks();
#endif//WIN32
}
