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

#ifndef TrentinoExampleBuilderLoggerImpllH
#define TrentinoExampleBuilderLoggerImpllH

//specific
#include "services/LoggerFile.h"
#include "services/LoggerConsole.h"
#include "services/Logger.h"
#include <string>

#ifdef WIN32
   #ifdef BUILDER_EXPORTS
      #undef BUILDER_IMPORT_EXPORT
      #define BUILDER_IMPORT_EXPORT __declspec(dllexport)
   #else
      #undef BUILDER_IMPORT_EXPORT
      #define BUILDER_IMPORT_EXPORT __declspec(dllimport)       
   #endif //BUILDER_EXPORTS
   #else
      #define BUILDER_IMPORT_EXPORT
#endif //WIN32


namespace Trentino{
namespace Example{
namespace Builder
{
   //class declaration
   //**********************************************************************************************
   //                             LoggerImpl
   //**********************************************************************************************
   //! LoggerImpl implementation testcode
   //**********************************************************************************************
   class BUILDER_IMPORT_EXPORT LoggerImpl : public Logger
   {
      //construction
   public :
      LoggerImpl();
      ~LoggerImpl();

	  //references
	  void setFileLogger(LoggerFile* fileLogger);
	  void setConsoleLogger(LoggerConsole* consoleLogger);
      //services
   public :
      void log(std::string logMsg);
	  
	private:
	//references
  	LoggerFile* mFileLogger;
	LoggerConsole* mConsoleLogger;
	
   };//class LoggerImpl

}//namespace Builder
}//namespace Example
}//namespace Trentino

#endif //TrentinoExampleBuilderLoggerImpllH