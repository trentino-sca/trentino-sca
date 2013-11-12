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

#ifndef TrentinoAPIInvocationContextH
#define TrentinoAPIInvocationContextH

//standard
//#include <oasis/sca/ServiceProxy.h>

//specific
#include "TrentinoInvocation.h"
#include "./../ServiceRegistry/ServiceRegistry.h"

namespace Trentino{
namespace Invocation 
{	
   //**********************************************************************************************
   //                                        InvocationContext
   //**********************************************************************************************
   //! \ingroup Invocation
   //! \brief Stores additional data (beside what is passed in InvoationData) to be associated with 
   //!        an invocation.    
   //**********************************************************************************************
   class INVOCATION_IMPORT_EXPORT InvocationContext
   {
      //construction
	public:
      //*******************************************************************************************
      //                                  InvocationContext()
      //*******************************************************************************************      
      //! \brief Empty constructor. 
      //*******************************************************************************************
		InvocationContext();

      //*******************************************************************************************
      //                                  InvocationContext()
      //*******************************************************************************************      
      //! \brief Empty constructor. 
      //*******************************************************************************************
		~InvocationContext();
   private:
      //*******************************************************************************************
      //                      InvocationContext(const InvocationContext&)
      //*******************************************************************************************      
      //! \brief Disallow inadvertent copy construction. 
      //*******************************************************************************************
      InvocationContext(const InvocationContext&);

      //operators
   private:
      //*******************************************************************************************
      //                                       operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.
      //*******************************************************************************************
      void operator=(const InvocationContext&);

      //services
   public:
      //*******************************************************************************************
      //                                     currentInvoker()
      //*******************************************************************************************
      //! \brief Returns the invoker that is used to perform the current invocation.
      //! \return A shared pointer to the Invoker. 
      //! \sa setCurrentInvoker()
      //*******************************************************************************************
      Trentino::Invocation::InvokerPtr currentInvoker() const;

      //*******************************************************************************************
      //                                     setCurrentInvoker()
      //*******************************************************************************************
      //! \brief Set the invoker that is used to perform the current invocation.
      //! \param[in] A shared pointer to the Invoker.
      //! \sa invoker()
      //*******************************************************************************************
		void setCurrentInvoker(const Trentino::Invocation::InvokerPtr& invoker); 


      void setServiceInfo(const Trentino::ServiceRegistry::ServiceInfoPtr& serviceInfo);

      //data
	private:    
      //! Invoker used to perform the current invocation
		Trentino::Invocation::InvokerPtr mCurrentInvoker;
      //! \brief information about the currently called service
      //! \todo This information should not be stored here!
      Trentino::ServiceRegistry::ServiceInfoPtr mServiceInfo;
	};//class InvocationContext

   #include "TrentinoInvocationInvocationContext.inl"

}//namespace API
}//namespace Trentino

#endif //TrentinoAPIInvocationContextH
