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

#ifndef TrentinoCoreContributionLoadingLoggingErrorHandlerH
#define TrentinoCoreContributionLoadingLoggingErrorHandlerH

//baseclass
#include "TrentinoCoreContributionLoadingErrorHandlerBase.h"

namespace Trentino{
namespace Core{
namespace ContributionLoading
{
   //**********************************************************************************************
   //                                      LoggingErrorHandler 
   //**********************************************************************************************
   //! \ingroup ContributionLoading
   //! \brief Uses the trentino logging system in order to print error and warning messages. 
   //!
   //! That way, the way in which error and warning messages are shown to the user is effectively 
   //! delegated to the logging system (that by default will print them to the screen).
   //**********************************************************************************************
   class LoggingErrorHandler : public ErrorHandlerBase
   {
      //construction
   public:
      //*******************************************************************************************
      //                                   LoggingErrorHandler()
      //*******************************************************************************************
      //! \brief Empty constructor.      
      //*******************************************************************************************
      LoggingErrorHandler();

      //*******************************************************************************************
      //                                   ~LoggingErrorHandler()
      //*******************************************************************************************
      //! \brief Empty destructor.      
      //*******************************************************************************************
      ~LoggingErrorHandler();

   private:
      //*******************************************************************************************
      //                        LoggingErrorHandler(const LoggingErrorHandler&)()
      //*******************************************************************************************
      //! \brief Disallow inadvertent copying.  
      //*******************************************************************************************
      LoggingErrorHandler(const LoggingErrorHandler&);

      //operators
   private:
      //*******************************************************************************************
      //                                        operator=()
      //*******************************************************************************************
      //! \brief Disallow inadvertent assignment.      
      //*******************************************************************************************
      void operator=(const LoggingErrorHandler&);

      //services
   public:
      //*******************************************************************************************
      //                                        issueError()
      //*******************************************************************************************
      //override from ErrorHandlerBase (see documentation in ErrorHandlerBase)
      //! \brief Uses logError() for printing the error message. 
      //!
      //! \param[in] error The error code of the issued error. Currently not used. 
      //! \param[in] msg Text message associated with the error.
      //*******************************************************************************************
      virtual void issueError(Error error, const std::string& msg);

      //*******************************************************************************************
      //                                       issueWarning()
      //*******************************************************************************************
      ////override from ErrorHandlerBase (see documentation in ErrorHandlerBase)
      //! \brief Uses logWarn() for printing the warning message. 
      //!
      //! \param[in] warning The warning code of the issued warning. Currently not used. 
      //! \param[in] msg Text message associated with the warning.
      //*******************************************************************************************
      virtual void issueWarning(Warning warning, const std::string& msg);
   }; //class LoggingErrorHandler

} //namespace ContributionLoading
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreContributionLoadingLoggingErrorHandlerH