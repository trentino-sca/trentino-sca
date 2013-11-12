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

#ifndef TrentinoRuntimeModelErrorCodeH
#define TrentinoRuntimeModelErrorCodeH

//standard
#include <exception>
#include <boost/shared_ptr.hpp>
#include <string>

//specific
#include "../../Global/TrentinoGlobal.h"


namespace Trentino{
   namespace RuntimeModel{

      typedef boost::shared_ptr<std::exception> ExceptionPtr;

      //class declaration
      //****************************************************************************************************
      //                               ErrorCode
      //****************************************************************************************************
      //! \brief the Trentino wide error code. It is an extension of the boost system error 
      //! code and provide more details about the error. For example, it can contains an
      //! exception
      //****************************************************************************************************
      class ErrorCode
         {



         //constructors
         public:
            //****************************************************************************************************
            //                                         ErrorCode()
            //****************************************************************************************************
            //! \brief default Error code with no description. error code is success
            //! \return 
            //****************************************************************************************************
            ErrorCode(){}

            ErrorCode(ExceptionPtr exceptionPtr) :mExceptionPtr(exceptionPtr) {}


            //****************************************************************************************************
            //                                         ErrorCode()
            //****************************************************************************************************
            //! \brief an error code with an initial value and an initial description
            //! \param int val
            //! \param std::string description
            //! \return 
            //****************************************************************************************************
            ErrorCode(int code,std::string description):mCode(code), mDescription(description){}


            //****************************************************************************************************
            //                                         ~ErrorCode()
            //****************************************************************************************************
            //! \brief default descructor actually does nothing
            //! \return 
            //****************************************************************************************************
            virtual ~ErrorCode() {}

            //services
         public:


            //****************************************************************************************************
            //                                         exceptionInfo()
            //****************************************************************************************************
            //! \brief get the last exception contained in this error object
            //! \return const ExceptionPtr&
            //****************************************************************************************************
            const ExceptionPtr& exceptionInfo() const
               {
               return mExceptionPtr;
               }


            //****************************************************************************************************
            //                                         hasException()
            //****************************************************************************************************
            //! \brief return true if the last error refer to an exception
            //! \return bool
            //****************************************************************************************************
            bool hasException()
               {
               return mExceptionPtr.get() !=nullptr;
               }

            const std::string description()
               {
               if(hasException()){
                  return mExceptionPtr->what();
                  }
               return mDescription;
               }

            void setException( boost::shared_ptr<std::exception> exceptionPtr ) 
               {
               mExceptionPtr = exceptionPtr;
               }

            void setDescription(const std::string& aDescription)
               {
               mDescription = aDescription;
               }

            //****************************************************************************************************
            //                                         isSuccess()
            //****************************************************************************************************
            //! \brief return true if the error code is equal boost::system::errc::success =0
            //! \return const bool
            //****************************************************************************************************
            const bool isSuccess() const {
               return mCode == 0;
               }

            const int value() const
               {
               return mCode;
               }

             void assign (int code)
                {
                mCode = code;
                }
            bool operator!() const  // true if no error
               {
               return isSuccess();
               }

            //data
         private:
            ExceptionPtr mExceptionPtr;
            std::string mDescription;
            int mCode;
         }; //class ErrorCode

         //****************************************************************************************************
         //                                RuntimeErrorValues
         //****************************************************************************************************
         //! \brief  list of error codes used internaly by the BindingSCA 
         //****************************************************************************************************
         enum RuntimeErrorValues {
           //! \brief a user of the Service Registry has a null pointer on a ServiceRegistry
           service_registry_not_available = 20002000,
           service_registry_multiple_services_found,
           service_registry_no_service_found,
           //! \brief error occured during invocation
           invocation_exception,

           //! \brief this message inform the caller that the invocation 
           //! will take place in a later time.
           //! this error value is used internally by the binding to inform clients that the call is a one way call
           //! and that it is delayed. For one way calls, the server will not provide a Soap Response
           invocation_delayed,
           //Binding SCA error values
           header_has_no_destination,
           header_has_no_action,
           header_has_no_sender


         }; // BindingSCAErrorCode

      }// namespace RuntimeModel
   }// namespace Trentino

#endif //TrentinoRuntimeModelErrorCodeH
