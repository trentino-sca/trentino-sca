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
 
#ifndef _oasis_sca_SCAException_h_
#define _oasis_sca_SCAException_h_

//standard
#include <stdexcept>
#include <string>

namespace oasis {
namespace sca 
{
   //class declaration
   //**********************************************************************************************
   //                             SCAException                          
   //**********************************************************************************************
   //! \brief  Clients calling service operations will experience business exceptions, 
   //!         and SCA runtime exceptions. 
   //!         Business exceptions are raised by the implementation of the called service operation. 
   //!         It is expected that these will be caught by client invoking the operation  
   //!         on the service.
   //!         SCA runtime exceptions are raised by the SCA runtime and signal problems 
   //!         in the management of the execution of components, 
   //!         and in the interaction with remote services. 
   //**********************************************************************************************
   class SCAException : public std::exception 
   {
      //construction
   public:
      //*******************************************************************************************
      //                                     SCAException()                               
      //*******************************************************************************************
      //! Default constructor.
      //*******************************************************************************************
      SCAException();

      //*******************************************************************************************
      //                                     SCAException()                               
      //*******************************************************************************************
      //! Constructor.
      //! \param  The type of the exception as a string. e.g. \sa “ServiceUnavailableException”.
      //! \param  The message which the SCA runtime attached to the exception.
      //! \param  The filename within which the exception occurred – 
      //!         Will be an empty string if the filename is not known.
      //! \param  The line number at which the exception occurred – 
      //!         Will 0 if the line number is not known.
      //! \param  The function name in which the exception occurred – 
      //!         Will be an empty string if the function name is not known.
      //*******************************************************************************************
      SCAException( const char* eClassName
                   ,const char* messageText
                   ,const char* fileName = nullptr
                   ,unsigned long lineNumber = 0
                   ,const char* functionName = nullptr);
      //services
   public:
      //*******************************************************************************************
      //                                     getEClassName()              
      //*******************************************************************************************
		//! \brief The type of the exception as a string. e.g. \sa “ServiceUnavailableException”
      //! \return Type of exception.
      //*******************************************************************************************
      const char* getEClassName() const;

      //*******************************************************************************************
      //                                     getMessageText()              
      //*******************************************************************************************
		//! \brief The message which the SCA runtime attached to the exception.
      //! \return Message of exception.
      //*******************************************************************************************
      const char* getMessageText() const;

      //*******************************************************************************************
      //                                     getFileName()              
      //*******************************************************************************************
		//! \brief The filename within which the exception occurred.
      //! \return The filename string.
      //!         Will be an empty string if the filename is not known.
      //*******************************************************************************************
      const char* getFileName() const;

      //*******************************************************************************************
      //                                     getLineNumber()              
      //*******************************************************************************************
		//! \brief The line number of exception
      //! \return The line number at which the exception occurred.
      //!         Will 0 if the line number is not known.
      //*******************************************************************************************
      unsigned long getLineNumber() const;

      //*******************************************************************************************
      //                                     getFunctionName()              
      //*******************************************************************************************
		//! \brief The function name of exception.
      //! \return The function name in which the exception occurred.
      //!         Will be an empty string if the function name is not known.
      //*******************************************************************************************
      const char* getFunctionName() const;
      //data
   private:
      //! Type of exception member.
      std::string mEClassName;
      //! Message text of sca exception.
      std::string mMessageText;
      //! Filename string in which exception is occurred
      std::string mFileName;
      //! Functionname in which exception is occurred
      std::string mFunctionName;
      unsigned long mLineNumber;
   }; //class SCAException
 
 
   //**********************************************************************************************
   //                           SCANullPointerException
   //**********************************************************************************************
   class SCANullPointerException : public SCAException 
   {
   };
 
 
   //**********************************************************************************************
   //                           ServiceRuntimeException
   //**********************************************************************************************
   class ServiceRuntimeException : public SCAException 
   {
   };
 
 
   //**********************************************************************************************
   //                           ServiceUnavailablException
   //**********************************************************************************************
   class ServiceUnavailablException : public ServiceRuntimeException 
   {
   };
 
 
   //**********************************************************************************************
   //                           MultipleServicesException
   //**********************************************************************************************
   class MultipleServicesException : public ServiceRuntimeException 
   {
   };
 
   #include "SCAException.inl"
 
} // namespace sca
} // namespace oasis
 
#endif /* _oasis_sca_SCAException_h_ */
