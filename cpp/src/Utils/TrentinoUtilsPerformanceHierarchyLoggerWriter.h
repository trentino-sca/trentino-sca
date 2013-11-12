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

#ifndef TrentinoUtilsPerformanceHierarchyLoggerWriterH
#define TrentinoUtilsPerformanceHierarchyLoggerWriterH

//standard
#include <string>
#include <boost/shared_ptr.hpp>

//specific
#include "../Global/TrentinoGlobal.h"
#include "TrentinoUtilsPerformanceHierarchyLogger.h"

namespace Trentino{
namespace Utils{
namespace Performance
{
   //class declaration
   //**********************************************************************************************
   //                             HierarchyLoggerWriter
   //**********************************************************************************************
   //! \brief Prints the complete hierarchy of nodes to console or to file.
   //**********************************************************************************************
   class PERFORMANCE_IMPORT_EXPORT HierarchyLoggerWriter
   {
      //construction
   public:
      //*******************************************************************************************
      //                                   constructor()                               
      //*******************************************************************************************
      //! Creates a new instance of HierarchyLoggerWriter with specified file output. 
      //! \param[in] Filename to write all nodes into.
      //! File is recreated and hierarchy will be written.
      //*******************************************************************************************
      HierarchyLoggerWriter(const std::string& fileName);

      //*******************************************************************************************
      //                                   constructor()                               
      //*******************************************************************************************
      //! Creates a new instance of HierarchyLoggerWriter with console output. 
      //*******************************************************************************************
      HierarchyLoggerWriter();

      //*******************************************************************************************
      //                                   destructor()                               
      //*******************************************************************************************
      //! Destroy instance of HierarchyLoggerWriter.
      //*******************************************************************************************
      ~HierarchyLoggerWriter();

      //services
   public:
      //*******************************************************************************************
      //                                   printNode()                               
      //*******************************************************************************************
      //! Prints given node and all its children to console and/or file (if given by constructor)
      //! \param[in] First \sa HierarchyNode which should be printed into console and/or file.
      //! \param[in] Level of node, used internally by method. Alternatively a start level can be
      //!            given.
      //*******************************************************************************************
      void printNode(HierarchyNode* node, int loglevel = 0);

      //data
   private:
      //! Stores an output filestream if a specified filename is given.
      boost::shared_ptr<std::ofstream> mStream;
   };//class HierarchyLoggerWriter

}//namespace Performance
}//namespace Utils
}//namespace Trentino

#endif//TrentinoUtilsPerformanceHierarchyLoggerWriterH