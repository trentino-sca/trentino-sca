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

#ifndef TrentinoInvocationSystemExceptionH
#define TrentinoInvocationSystemExceptionH

#ifdef WIN32
   #include <Windows.h>
   #include <eh.h>
#elif defined(__linux)
   #include <signal.h>
   #include <setjmp.h>
#endif

#include "TrentinoInvocationServiceInvocationWrapperBase.h"
#include "TrentinoInvocationSystemExceptionData.h"
#include "TrentinoInvocationInvocationData.h"
#include "TrentinoInvocationInvocationContext.h"
#include "../Core/TrentinoCoreComponentImplementationManagerBase.h"
#include "../Core/TrentinoCore.h"

namespace Trentino {
namespace Invocation {
   //**********************************************************************************************
   //                             InvocationSystemException 
   //**********************************************************************************************
   //! \ingroup Invocation
   //! \brief SEH functionality
   //
   //   This class provides functionality to handle structured (system) exceptions. These exceptions
   //  represents operating system errors like page fault, division by zero.
   //
   //  NOTE: to make this code compilable, there should be enable the following option:
   //        Runtime solution -> Properties -> C/C++ -> Code Generation -> Enable C++ Exceptions ->
   //        /EHa
   //**********************************************************************************************
   class InvocationSystemException {
      //construction
   private:
      InvocationSystemException();
      ~InvocationSystemException() {};

   public:
      //**********************************************************************************************
      //                                           getInstance
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief get a single instance of the class
      //
      //  This class intended to handle hardware faults during runtime execution, so it should be the
      // only one instance of this class in the system. Therefore it's implemented as a singleton.
      // This method returns a pointer to this instance.
      //**********************************************************************************************
      static InvocationSystemException* getInstance();

#ifdef WIN32
      //**********************************************************************************************
      //                                        TranslationFunction
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief translate HW fault to generic C++ style exception
      //**********************************************************************************************
      static void TranslationFunction(unsigned int u, EXCEPTION_POINTERS* pExp);
#elif defined(__linux)
      //**********************************************************************************************
      //                                        CatchSEGV
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief handler for Segmentation Fault (SIGSEGV) signal.
      //**********************************************************************************************
      static void CatchSEGV(int /*n*/);
      static void CatchSIGFPE(int /*n*/);
      static void CatchSIGSTKFLT(int /*n*/);

   private:
      //**********************************************************************************************
      //                                      UnblockSignal
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief unblock a signal.
      //
      // Unless we do this, the signal may only sent once.
      //**********************************************************************************************
      void UnblockSignal(int signum __attribute__((__unused__)));
#endif
   public:
      //**********************************************************************************************
      //                                       SafeInvocationWrapper
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief wrapper for the invoker call
      //
      //  This wrapper implements __try/__catch block.
      //**********************************************************************************************
      void SafeInvocationWrapper(void* instance,
                                 Trentino::Core::ComponentImplementationManagerBasePtr& implManager,
                                 const Trentino::Invocation::InvocationData& data,
                                 void* retVal,
                                 const Trentino::Invocation::InvocationContext& ctx,
                                 const Trentino::RuntimeModel::ServiceBasePtr& targetService);

   private:
      //**********************************************************************************************
      //                                       Instance
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief pointer to singleton instance
      //**********************************************************************************************
      static InvocationSystemException* Instance;

#ifdef WIN32
      //**********************************************************************************************
      //                                       defTranslator
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief default handler for the system exceptions
      //**********************************************************************************************
      _se_translator_function defTranslator;
#elif defined(__linux)
      //**********************************************************************************************
      //                                       errorCode
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief Linux error code
      //
      // If something goes wrong on the Linux site, it generates signals. There are about 30 signals
      // and it seems that flags should be used here. errorCode is 32-bits variable, so we can use it
      // like following: errorCode |= 1 << SIGNAL_NUMBER
      //**********************************************************************************************
      unsigned int errorCode;
      jmp_buf returnToTopLevel;
#endif
   };

} //namespace Invocation
} //namespace Trentino

#endif //TrentinoInvocationSystemExceptionH