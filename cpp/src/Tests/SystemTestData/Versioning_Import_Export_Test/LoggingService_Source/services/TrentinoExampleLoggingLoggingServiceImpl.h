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

#ifndef TrentinoExampleLoggingLoggingServiceImplH
#define TrentinoExampleLoggingLoggingServiceImplH

//standard
//#include <oasis\sca\ComponentContext.h>
#include <string>

//specific
#include "TrentinoExampleLoggingLoggingService.h"


#ifndef nullptr
   #define nullptr 0
#endif

#ifdef WIN32
   #ifdef LoggingService_EXPORTS
      #undef LOGGINGSERVICE_IMPORT_EXPORT
      #define LOGGINGSERVICE_IMPORT_EXPORT __declspec(dllexport)
   #else
      #undef LOGGINGSERVICE_IMPORT_EXPORT
      #define LOGGINGSERVICE_IMPORT_EXPORT __declspec(dllimport)       
   #endif //LOGGINGSERVICE_EXPORTS
   #else
      #define LOGGINGSERVICE_IMPORT_EXPORT
#endif //WIN32

namespace oasis{
namespace sca
{
   class ComponentContext;
} //namespace sca
} //namespace oasis

namespace Trentino{
namespace Example{
namespace Logging
{

   //class declaration
   //**********************************************************************************************
   //                             LoggingServiceImpl
   //**********************************************************************************************
   //! LoggingServiceImpl implementation testcode
   //**********************************************************************************************
   class LOGGINGSERVICE_IMPORT_EXPORT LoggingServiceImpl : public LoggingService
   {
	   public:
		  LoggingServiceImpl();
		  virtual ~LoggingServiceImpl();
		  
	   public:
		virtual void logError(const char* log);
		virtual void logDebug(const char* log);
		virtual void logInfo(const char* log);
		void setLoggerName(const std::string& loggerName);
	   
	   //data
	   private:
	   std::string mLoggerName;
   };//class LoggingServiceImpl

}//namespace Logging
}//namespace Example
}//namespace Trentino



#endif //TrentinoExampleLoggingLoggingServiceImplH