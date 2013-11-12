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

//header
#include "TrentinoInvocationSystemException.h"

//specific
#include "./../RuntimeModel/TrentinoRuntimeModelService.h"
#include "./../../Utils/TrentinoUtilsLogging.h"

using namespace Trentino::Invocation;

InvocationSystemException* InvocationSystemException::Instance = 0;

#if defined(__linux)
void InvocationSystemException::UnblockSignal(int signum __attribute__((__unused__)))
{
   sigset_t sigs;

   sigemptyset(&sigs);
   sigaddset(&sigs, signum);
   sigprocmask(SIG_UNBLOCK, &sigs, NULL);
}

void InvocationSystemException::CatchSEGV(int /*n*/)
{
   getInstance()->unblock_signal(SIGSEGV);
   getInstance()->errorCode |= 1 << SIGSEGV;
   longjmp(getInstance()->returnToTopLevel, 1);
}

void InvocationSystemException::CatchFPE(int /*n*/)
{
   getInstance()->unblock_signal(SIGFPE);
   getInstance()->errorCode |= 1 << SIGFPE;
   longjmp(getInstance()->returnToTopLevel, 1);
}

void InvocationSystemException::CatchSTKFLT(int /*n*/)
{
   getInstance()->unblock_signal(SIGSTKFLT);
   getInstance()->errorCode |= 1 << SIGSTKFLT;
   longjmp(getInstance()->returnToTopLevel, 1);
}
#endif

InvocationSystemException::InvocationSystemException()
{
      logInfo("Safe invocation init...");

#ifdef WIN32
   // Handles Win32 exceptions (C structured exceptions) as C++ typed exceptions.
   // If Windows generates an exception (paging fault, access violation, division by zero...)
   // the translation function will be called instead of application termination. This call
   // should be performed only once during runtime initialisation.
   defTranslator = _set_se_translator(&Trentino::Invocation::InvocationSystemException::TranslationFunction);
#elif defined(__linux)
   errorCode = 0;
   signal(SIGSEGV, InvocationSystemException::CatchSEGV);
   signal(SIGFPE, InvocationSystemException::CatchFPE);
   signal(SIGSTKFLT, InvocationSystemException::CatchSTKFLT);
#endif
}

InvocationSystemException* InvocationSystemException::getInstance()
{
   if (Instance == 0)
   {
      Instance = new InvocationSystemException;
   }

   return Instance;
}

#ifdef WIN32
// This function is executed when Windows has generated a system error (C exception). The
// idea is to throw C++ style exception here, so we can catch and process it by Runtime.
//
// This function takes two arguments:
//    u - exception code, they are defined as enums, below there are several most frequent examples
//        taken from msdn:
//
//        EXCEPTION_ACCESS_VIOLATION - The thread tried to read from or write to a virtual address
//                                     for which it does not have the appropriate access.
//
//        EXCEPTION_INT_DIVIDE_BY_ZERO - The thread tried to divide an integer value by an integer
//                                       divisor of zero.
//
//        EXCEPTION_STACK_OVERFLOW - The thread used up its stack.
//
//    pExp - exception pointer. This structure contains the overall system state before exception
//           happened. It can be used to print debug information or trace the system.
void InvocationSystemException::TranslationFunction(unsigned int u, EXCEPTION_POINTERS* /*pExp*/)
{
   throw InvocationSystemExceptionData(u);
}
#endif //WIN32

static void LocalWrapper(void* instance,
                         Trentino::Core::ComponentImplementationManagerBasePtr& implManager,
                         const Trentino::Invocation::InvocationData& data,
                         void * retVal,
                         const Trentino::Invocation::InvocationContext& ctx,
                         const Trentino::RuntimeModel::ServiceBasePtr& targetService)
{
 implManager->onInvoke(instance,data, retVal,ctx, targetService);
}


void InvocationSystemException::SafeInvocationWrapper(
                                 void* instance,
                                 Trentino::Core::ComponentImplementationManagerBasePtr& implManager,
                                 const Trentino::Invocation::InvocationData& data,
                                                                  void* retVal,
                                 const Trentino::Invocation::InvocationContext& ctx,
                                 const Trentino::RuntimeModel::ServiceBasePtr& targetService)
{
#ifdef WIN32
   __try
   {
      // __try/__finally block deprecates to use objects with destructors inside it, so
      // lets use a special wrapper.
      LocalWrapper(instance, implManager, data,retVal, ctx, targetService);
   }
   __finally
   {
      logTrace("System exception: __finaly");
   }
#elif defined(__linux)
   // Set the return label here. It will be used as a return point from signal handler.
   if (setjmp(returnToTopLevel) == 0) {
      // To be honest, there is no need to use this wrapper here, as mentioned above it's
      // required by Windows OS. But let's keep the code in unified style.
      LocalWrapper(instance, implManager, data, ctx, targetService);
   }

   if (errorCode) {
      unsigned int code = errorCode;
      errorCode = 0;
      throw InvocationSystemExceptionData(errorCode);
   }
#endif
}