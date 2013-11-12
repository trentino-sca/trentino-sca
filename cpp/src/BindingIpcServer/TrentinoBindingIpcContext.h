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

#ifndef TrentinoBindingIpcContextH
#define TrentinoBindingIpcContextH

//specific
#include <Runtime/ServiceRegistry/ServiceRegistry.h>
#include <Runtime/Invocation/TrentinoInvocation.h>


namespace Trentino{
namespace Binding{
namespace IPC
{
   class Context;
   typedef boost::shared_ptr<Context> ContextPtr;
   //****************************************************************************************************
   //                                   Context
   //****************************************************************************************************
   //! \brief This clas contains external dependencies of the IPC Binding Module
   //****************************************************************************************************
   class Context
   {

         //services
      public:
      //****************************************************************************************************
      //                                   setInvoker()
      //****************************************************************************************************
      //! \brief
      //! \param const Trentino::Invocation::InvokerPtr & invoker
      //! \return void
      //****************************************************************************************************
      void setInvoker(const Trentino::Invocation::InvokerPtr& invoker)
      {
         mInvoker = invoker;
      }

      //****************************************************************************************************
      //                                         invoker()
      //****************************************************************************************************
      //! \brief return the invoker used by this binding
      //! \return const Trentino::Invocation::InvokerPtr&
      //****************************************************************************************************
      const Trentino::Invocation::InvokerPtr& invoker() const
      { 
         return mInvoker;
      }


      //****************************************************************************************************
      //                                         serviceRegistry()
      //****************************************************************************************************
      //! \brief return the ServiceRegistry used by this Binding
      //! \return Trentino::ServiceRegistry::ServiceRegistryPtr
      //****************************************************************************************************
      Trentino::ServiceRegistry::ServiceRegistryPtr serviceRegistry() const
      {
         return mServiceRegistry;
      }


      //****************************************************************************************************
      //                                         setServiceRegistry()
      //****************************************************************************************************
      //! \brief set the Service Registry used by this Binding
      //! \param const Trentino::ServiceRegistry::ServiceRegistryPtr & val
      //! \return void
      //****************************************************************************************************
      void setServiceRegistry(const Trentino::ServiceRegistry::ServiceRegistryPtr& val)
      { 
         mServiceRegistry = val;
      }

         //data
   private:
         Trentino::Invocation::InvokerPtr mInvoker;
         Trentino::ServiceRegistry::ServiceRegistryPtr mServiceRegistry;
   }; // class Context

}//namespace IPC
}//namespace TBinding
}//namepsace Trentino

#endif //TrentinoBindingIpcContextH

