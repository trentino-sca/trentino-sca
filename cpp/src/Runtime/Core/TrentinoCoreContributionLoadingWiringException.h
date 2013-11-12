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

#ifndef TrentinoCoreContributionLoadingWiringExceptionH
#define TrentinoCoreContributionLoadingWiringExceptionH

//standard
#include <string>

//specific
#include "TrentinoCoreContributionLoading.h"

namespace Trentino{
namespace Core{
namespace ContributionLoading
{
   //**********************************************************************************************
   //                                      WiringException 
   //**********************************************************************************************
   //! \ingroup ContributionLoading
   //! \brief Exception thrown in case a wiring related error occurs. 
   //!
   //! WiringException allows for associating further data with the exception so that more 
   //! meaningful error messages can be produced.
   //**********************************************************************************************
   class WiringException : public ErrorException
   {
      //construction
   public:
      //*******************************************************************************************
      //                     WiringException(Error, std::string&, std::string&)
      //*******************************************************************************************
      //! \brief Constructs a WiringException with information only about the target component.
      //!
      //! Using this constructor will make hasServiceInfo() return \c false. 
      //! \param[in] error Error code of the error that caused the exception.
      //! \param[in] what The description (error message) of the exception.
      //! \param[in] targetComponentName Name of the component which was the target of the wiring
      //!            attempt when the exception occurred. 
      //! \note Using WiringException(Error, const std::string&, const std::string&, 
      //!       const std::string&) with an empty \c targetServiceName won't resemble the behavior
      //!       of this constructor. Once \c targetServiceName is set from outside, hasServieInfo()
      //!       will always return \c true independently of whether the name is empty or not. 
      //*******************************************************************************************
      WiringException( Error error
                     , const std::string& what
                     , const std::string& targetComponentName);         
   
      //*******************************************************************************************
      //              WiringException(Error, std::string&, std::string&, std::string&)
      //*******************************************************************************************
      //! \brief Constructs a WiringException with information about the target component as well
      //!        as about the target service. 
      //! Using this constructor will make hasServiceInfo() return \c true. 
      //! \param[in] error Error code of the error that caused the exception.
      //! \param[in] what The description (error message) of the exception.
      //! \param[in] targetComponentName Name of the component which was the target of the wiring
      //!            attempt when the exception occurred. 
      //! \param[in] targetServiceName Name of the service which was the target of the wiring
      //!            attempt when the exception occurred. 
      //! \note Using this constructor with an empty \c targetServiceName won't resemble the 
      //!       behavior of WiringException(Error, std::string&, std::string&). 
      //!       Once \c targetServiceName is set from outside, hasServieInfo()will always return 
      //!       \c true independently of whether the name is empty or not. 
      //*******************************************************************************************
      WiringException( Error error 
                     , const std::string& what
                     , const std::string& targetComponentName
                     , const std::string& targetServiceName );

      //*******************************************************************************************
      //                                    -WiringException()
      //*******************************************************************************************
      //! \brief Empty destructor.      
      //*******************************************************************************************
      ~WiringException() throw(); 

          //operators
   private:
      //*******************************************************************************************
      //                                      operator=()
      //*******************************************************************************************
      //! \brief Disallow inadvertent assignment.      
      //*******************************************************************************************
      void operator=(const WiringException&);

      //services
   public:
      //*******************************************************************************************
      //                                     targetComponentName()
      //*******************************************************************************************
      //! \brief Returns the name of the target component.
      //! \return Name of the component which was the target of the wiring attempt when the 
      //!         exception occurred. 
      //*******************************************************************************************
      std::string targetComponentName() const;

      //*******************************************************************************************
      //                                     targetServiceName()
      //*******************************************************************************************
      //! \brief Returns the name of the target service.
      //! \return Name of the service which was the target of the wiring attempt when the 
      //!         exception occurred. 
      //! \attention The return value should be used only if hasServiceInfo() returns \c true, 
      //             otherwise it has no meaning. 
      //*******************************************************************************************
      std::string targetServiceName() const;

      //*******************************************************************************************
      //                                     hasServiceInfo()
      //*******************************************************************************************
      //! \brief Returns whether information about the target service has been associated with
      //!        the exception.
      //! \return \c true in case the return value of targetServiceName() should be considered as
      //!         valid, \c false otherwise. 
      //*******************************************************************************************
      bool hasServiceInfo() const;

      //data
   private:
      //! Name of the component which was the target of the wiring attempt 
      //! when the exception occurred.                
      const std::string mTargetComponentName;
      //! Name of the service which was the target of the wiring attempt 
      //! when the exception occurred. 
      const std::string mTargetServiceName;
      //! Flag specifying whether the value contained in mTargetService should be considered as 
      //! valid.
      bool mHasServiceInfo;
   }; //class WiringException

   //services
   inline std::string WiringException::targetComponentName() const 
   {
      return mTargetComponentName; 
   }

   inline std::string WiringException::targetServiceName() const 
   {
      return mTargetServiceName; 
   }

   inline bool WiringException::hasServiceInfo() const 
   {
      return mHasServiceInfo; 
   }

} //namespace ContributionLoading
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreContributionLoadingWiringExceptionH