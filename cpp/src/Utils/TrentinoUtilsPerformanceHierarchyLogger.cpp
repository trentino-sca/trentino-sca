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

//headers
#include "TrentinoUtilsPerformanceHierarchyLogger.h"

//standard
#ifdef WIN32
   #include <Windows.h>
#endif

using namespace Trentino::Utils::Performance;

HierarchyLogger& HierarchyLogger::instance()
{
   static HierarchyLogger instance;
   return instance;
}

HierarchyLogger::HierarchyLogger()
{
   mRoot = nullptr;
   mCurrentNode = nullptr;
   createNode("root");
}

HierarchyLogger::~HierarchyLogger()
{
   delete mRoot;
}

HierarchyNode* HierarchyLogger::createInternalNode(const char* functionName, HierarchyNode* parentNode)
{
   HierarchyNode* newNode = new HierarchyNode(functionName, parentNode);
   if(mRoot == nullptr)
   {
      mRoot = newNode;
   }

   return newNode;
}

void HierarchyLogger::clear()
{
   mCurrentNode = nullptr;
   delete mRoot;
   mRoot = nullptr;
}

HierarchyNode* HierarchyLogger::createNode(const char* functionName)
{
   mCurrentNode = createInternalNode(functionName, mCurrentNode);
   return mCurrentNode;
}

void HierarchyLogger::createSibling(const char* functionName)
{
   if(mRoot == nullptr)
   {
      createNode(functionName);
   }
   else
   {
      mCurrentNode = createInternalNode(functionName, mCurrentNode->parent());      
   }
}

void HierarchyNodeScope::beginMeasurement()
{
   assert(mNode != nullptr);
   #ifdef WIN32
      QueryPerformanceCounter(
         reinterpret_cast<LARGE_INTEGER*>(&mStartTime));
   #else
      mStartTime = 0;
   #endif
}

void HierarchyNodeScope::endMeasurement()
{
   assert(mNode != nullptr);
   #ifdef WIN32
      unsigned long long stop, ticks;
      QueryPerformanceFrequency(
         reinterpret_cast<LARGE_INTEGER*>(&ticks));
      QueryPerformanceCounter(
         reinterpret_cast<LARGE_INTEGER*>(&stop));

      mNode->mTimeMSec = static_cast<float>(stop - mStartTime) / ticks;
   #else
      mNode->mTimeMSec = 0.0f;
   #endif
}

