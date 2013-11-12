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

// header
#include "TrentinoUtilsPerformanceHierarchyLoggerWriter.h"

//standard
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <errno.h>
#include <stdexcept>

using namespace Trentino::Utils::Performance;
using namespace std;


HierarchyLoggerWriter::HierarchyLoggerWriter(const string& fileName)
{
   mStream.reset(new ofstream);
   mStream->open(fileName.c_str(), ios_base::out);
   if(mStream->fail() || mStream->bad())
   {
      char buffer[512] = {0};
      strerror_s(buffer, sizeof(buffer), errno);
      throw runtime_error(
         "Error creating logger file: " + fileName +  
         ". Error:" + buffer);
   }

}

HierarchyLoggerWriter::HierarchyLoggerWriter()
{
}

HierarchyLoggerWriter::~HierarchyLoggerWriter()
{
   if(mStream.get() != nullptr)
   {
      mStream->close();
   }
}


void HierarchyLoggerWriter::printNode(HierarchyNode* node, int loglevel)
{
   if(node != nullptr)
   {
      //! \todo extend and refactor
      for(int i = 0; i < loglevel; i++)
      {
         cout << "..";
         if(mStream.get() != nullptr)
            mStream->write("..", 2);
      }
      char buffer[600];
      if(node->type() == nullptr && node->info() == nullptr)
      {
         sprintf_s(buffer, sizeof(buffer), "%.6f: %s \n", 
            node->elapsedTime(), node->functionName());
      }
      else
      {
         sprintf_s(buffer, sizeof(buffer), "%.6f: %s (%s:%s) \n", 
            node->elapsedTime(), node->functionName(), node->type(), node->info());
      }
      //! \todo refactor
      cout << buffer;
      if(mStream.get() != nullptr)
         mStream->write(buffer, strlen(buffer));

      HierarchyNode* iterChild = node->firstChild();
      while(iterChild != nullptr)
      {
         printNode(iterChild, loglevel + 1);
         iterChild = iterChild->successor();
      }
   }
   else
   {
      //! \todo refactor
      const char buffer[] = "root is NULL";
      cout << buffer;
      if(mStream.get() != nullptr)
         mStream->write(buffer, strlen(buffer));
   }

}

