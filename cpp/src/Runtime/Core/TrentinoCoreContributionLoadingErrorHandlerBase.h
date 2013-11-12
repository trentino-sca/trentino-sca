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

#ifndef TrentinoCoreContributionLoadingErrorHandlerBaseH
#define TrentinoCoreContributionLoadingErrorHandlerBaseH

//standard
#include <string>

//specific
#include "TrentinoCoreContributionLoading.h"

namespace Trentino{
namespace Core{
namespace ContributionLoading
{
   //**********************************************************************************************
   //                                      ErrorHandlerBase 
   //**********************************************************************************************
   //! \ingroup ContributionLoading
   //! \brief Abstract base class used to derive concrete error handlers from.
   //!
   //! Error handlers are used in order to abstract the way in which errors are handled (e.g. shown
   //! to the user) during contribution loading. The classes responsible for the contribution
   //! loading process (currently ContributionLoading::Installer, ContributionLoading::Deployer,
   //! and ContributionLoading::Runner) should not print error message directly to the screen or
   //! log them. Instead each error or warning should be issued by calling the issueError() or
   //! issueWarning() method of the associated error handler. 
   //!
   //! Since the both issue* methods expect an error or warning number to be passed as argument,
   //! using an error handler facilitates testing: in tests, a custom error handler can be assigned
   //! which is capable of keeping track of the issued errors and test against the expected ones. 
   //! See Tests::Core::ContributionLoaderBaseTest::CollectingErrorHandler for an example.
   //!
   //! Classes that want to use error handlers should be derived from 
   //! ContributionLoading::ErrorReporter. 
   //**********************************************************************************************
   class ErrorHandlerBase
   {
      //construction
   public:
      //*******************************************************************************************
      //                                    ErrorHandlerBase()
      //*******************************************************************************************
      //! \brief Empty constructor.      
      //*******************************************************************************************
      ErrorHandlerBase(){}

      //*******************************************************************************************
      //                                    ~ErrorHandlerBase()
      //*******************************************************************************************
      //! \brief Empty destructor.      
      //*******************************************************************************************
      virtual ~ErrorHandlerBase(){}  

      //services
   public:
      //*******************************************************************************************
      //                                     issueError()
      //*******************************************************************************************
      //! \brief Should be called by clients in order to issue an error.
      //!
      //! \param[in] error The error code of the issued error.
      //! \param[in] msg Text message associated with the error.
      //*******************************************************************************************
      virtual void issueError(Error error, const std::string& msg) = 0;

      //*******************************************************************************************
      //                                     issueWarning()
      //*******************************************************************************************
      //! \brief Should be called by clients in order to issue a warning.
      //!
      //! \param[in] warning The warning code of the issued warning.
      //! \param[in] msg Text message associated with the warning.
      //*******************************************************************************************
      virtual void issueWarning(Warning warning, const std::string& msg) = 0;
   }; //class ErrorHandlerBase

} //namespace ContributionLoading
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreContributionLoadingErrorHandlerBaseH