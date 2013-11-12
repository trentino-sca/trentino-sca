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

#ifndef TrentinoRuntimeServiceControlH
#define TrentinoRuntimeServiceControlH

//standard
#include <string>

#if defined(WIN32)
   #include <Windows.h>
#else
   #define WINAPI
#endif //WIN32

namespace Trentino
{
   //*********************************************************************************************
   //                                    RuntimeServiceControl
   //*********************************************************************************************
   //! \class RuntimeServiceControl
   //! \brief Control the state of the TrentinoRuntimeService
   //!
   //! start/stop and update DACL
   //*********************************************************************************************
   class RuntimeServiceControl
   {
      //construction
   public:
      RuntimeServiceControl()
      : mErrorCode(0)
      {};

      //services
   public:
      //*********************************************************************************************
      //                                      start()
      //*********************************************************************************************
      //! \brief Start the Runtime service
      //*********************************************************************************************
      void WINAPI start();

#if defined(WIN32)
      //*********************************************************************************************
      //                                  updateServiceDACL()
      //*********************************************************************************************
      //! \brief Update DACL for the Runtime service
      //*********************************************************************************************
      void WINAPI updateServiceDACL();
#endif //WIN32

      //*********************************************************************************************
      //                                       stop()
      //*********************************************************************************************
      //! \brief Stop the runtime service
      //*********************************************************************************************
      void WINAPI stop();

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

   }; //class RuntimeServiceControl

   inline int RuntimeServiceControl::errorCode() const
   {
      return mErrorCode;
   }

   inline std::string RuntimeServiceControl::errorMessage() const
   {
      return mErrorMessage;
   }

} //namespace Trentino

#endif //TrentinoRuntimeServiceControlH