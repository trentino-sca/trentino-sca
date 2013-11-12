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

#ifndef TrentinoCoreContributionLoadingErrorReporterH
#define TrentinoCoreContributionLoadingErrorReporterH

//specific
#include "TrentinoCoreContributionLoading.h"

namespace Trentino{
namespace Core{
namespace ContributionLoading
{
   //**********************************************************************************************
   //                                      ErrorReporter 
   //**********************************************************************************************
   //! \ingroup ContributionLoading
   //! \brief Base class providing the functionality to associate an error handler
   //!        (ContributionLoading::ErrorHandlerBase) with the derived classes. 
   //!
   //! Classes that want to use error handlers should be derived from ErrorReporter. 
   //**********************************************************************************************
   class ErrorReporter
   {
      //construction
   protected:
      //*******************************************************************************************
      //                                      ErrorReporter()
      //*******************************************************************************************
      //! \brief Empty constructor.      
      //*******************************************************************************************
      ErrorReporter();

      //*******************************************************************************************
      //                                     ~ErrorReporter()
      //*******************************************************************************************
      //! \brief Empty destructor.      
      //*******************************************************************************************
      virtual ~ErrorReporter();

      //services
   public:
      //*******************************************************************************************
      //                                      errorHandler() 
      //*******************************************************************************************
      //! \brief Returns the error handler associated with the ErrorReporter.
      //!
      //! \return A shared pointer to the error handler.      
      //! \sa setErrorHandler()
      //*******************************************************************************************
      ErrorHandlerBasePtr errorHandler() const;

      //*******************************************************************************************
      //                                     setErrorHandler()
      //*******************************************************************************************
      //! \brief Sets the error handler to be associated with the ErrorReporter.
      //!
      //! \param[in] errorHandler A shared pointer to an ErrorHandlerBase object.      
      //! \throw std::invalid_argument In case an empty shared pointer is passed. 
      //! \sa errorHandler()
      //*******************************************************************************************
      virtual void setErrorHandler(const ErrorHandlerBasePtr& errorHandler);     

      //data
   private:
      //! The error handler associated with this object. 
      ErrorHandlerBasePtr mErrorHandler;
   }; //class ErrorReporter

   //services
   inline ErrorHandlerBasePtr ErrorReporter::errorHandler() const
   {
      return mErrorHandler;
   }

} //namespace ContributionLoading
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreContributionLoadingErrorReporterH