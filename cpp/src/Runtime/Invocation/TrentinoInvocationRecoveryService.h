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

#ifndef TrentinoInvocationRecoveryServiceH
#define TrentinoInvocationRecoveryServiceH

#include "TrentinoInvocationServiceInvocationWrapperBase.h"
#include "TrentinoInvocationSystemExceptionData.h"
#include "TrentinoInvocationInvocationData.h"
#include "TrentinoInvocationInvocationContext.h"

namespace Trentino {
namespace Invocation {
   //**********************************************************************************************
   //                             InvocationRecoveryService 
   //**********************************************************************************************
   //! \ingroup Invocation
   //! \brief Recovery Service for Safe Invocation
   //
   // If OS fault happened, Safe Invocation translates this fault to the C++ exception. This class
   // is responsible for recovering Runtime after this exception.
   //**********************************************************************************************
   class InvocationRecoveryService {
      //construction
   private:
      InvocationRecoveryService();
      ~InvocationRecoveryService() {};

   public:
      //**********************************************************************************************
      //                                           getInstance
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief get a single instance of the class
      //
      //  This class intended to recover Runtime after OS faults during runtime execution, so it
      // should be the only one instance of this class in the system. Therefore it's implemented as a
      // singleton. This method returns a pointer to this instance.
      //**********************************************************************************************
      static InvocationRecoveryService* getInstance();

      //**********************************************************************************************
      //                                           Recover
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief recover Runtime after fault
      //**********************************************************************************************
      void Recover(const Trentino::Invocation::InvocationData& data, unsigned int u);

      //**********************************************************************************************
      //                                           Recover
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief recover Runtime after fault
      //**********************************************************************************************
      void Recover(const Trentino::Invocation::InvocationData& data);

   private:
      //**********************************************************************************************
      //                                       Instance
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief pointer to singleton instance
      //**********************************************************************************************
      static InvocationRecoveryService* Instance;
   };

} //namespace Invocation
} //namespace Trentino

#endif //TrentinoInvocationRecoveryServiceH