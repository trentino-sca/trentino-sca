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

#ifndef TrentinoRuntimeServiceH
#define TrentinoRuntimeServiceH

//standard
#include <string>

namespace Trentino {

   //*********************************************************************************************
   //                                      RuntimeService
   //*********************************************************************************************
   //! \class RuntimeService
   //! \brief Windows service entry point and main body
   //!
   //! This class represents the methods to install and register new Windows service which is
   //! called TrentinoRuntimeService. This service is a central object in Runtime part. It works
   //! in the background and manage framework control flow.
   //*********************************************************************************************
   class RuntimeService
   {
      //construction
   public:
      RuntimeService()
      : mErrorCode(0)
      {};

      //services
   public:
      //*********************************************************************************************
      //                                      doInstall()
      //*********************************************************************************************
      //! \brief Install a service in the SCM database
      //*********************************************************************************************
      void doInstall();

      //*********************************************************************************************
      //                                      dispatcher()
      //*********************************************************************************************
      //! \brief Start a service control dispatcher
      //*********************************************************************************************
      void startDispatcher();

      //getters
   public:
      //*********************************************************************************************
      //                                   errorMessage()
      //*********************************************************************************************
      //! \brief Get an error message. Empty string if no error was occured.
      //*********************************************************************************************
      std::string errorMessage() const;

      //*********************************************************************************************
      //                                    errorCode()
      //*********************************************************************************************
      //! \brief Get an error code.
      //*********************************************************************************************
      int errorCode() const;

      //data
   private:
      //*********************************************************************************************
      //                                   mErrorMessage
      //*********************************************************************************************
      //! \brief String to store error message if it's occured
      //*********************************************************************************************
      std::string mErrorMessage;

      //*********************************************************************************************
      //                                     mErrorCode
      //*********************************************************************************************
      //! \brief Store an error code if possible
      //*********************************************************************************************
      int mErrorCode;

   }; //class RuntimeService

   inline int RuntimeService::errorCode() const
   {
      return mErrorCode;
   }

   inline std::string RuntimeService::errorMessage() const
   {
      return mErrorMessage;
   }

} //namespace Trentino

#endif TrentinoRuntimeServiceH