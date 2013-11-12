// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2012 by Siemens AG. All rights reserved.
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

#ifndef TrentinoExampleBuilderSmartLoggerImplH
#define TrentinoExampleBuilderSmartLoggerImplH

#include "services/SmartLog.h"
#include <string>

#ifdef WIN32
   #ifdef VALIDCONTRIBUITION1_EXPORTS
      #undef VALIDCONTRIBUITION1_IMPORT_EXPORT
      #define VALIDCONTRIBUITION1_IMPORT_EXPORT __declspec(dllexport)
   #else
      #undef VALIDCONTRIBUITION1_IMPORT_EXPORT
      #define VALIDCONTRIBUITION1_IMPORT_EXPORT __declspec(dllimport)       
   #endif //VALIDCONTRIBUITION1_EXPORTS
   #else
      #define VALIDCONTRIBUITION1_IMPORT_EXPORT
#endif //WIN32


namespace Trentino{
namespace Example{
namespace ValidContribution1
{
   //class declaration
   //**********************************************************************************************
   //                             SmartLogger
   //**********************************************************************************************
   //! DividerImpl implementation testcode
   //**********************************************************************************************
   class VALIDCONTRIBUITION1_IMPORT_EXPORT SmartLoggerImpl: public SmartLog
   {
      //construction
   public :
      SmartLoggerImpl();
      ~SmartLoggerImpl();

      //services
   public :
      void write(std::string logMsg);
     virtual void writeFile(std::string logMsg) ;
	  virtual void writeConsole(std::string logMsg);
   };//class SmartLoggerImpl

}//namespace ValidContribution1
}//namespace Example
}//namespace Trentino



#endif //TrentinoExampleBuilderSmartLoggerImplH