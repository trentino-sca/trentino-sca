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

#ifndef TrentinoInvocationInvokerH
#define TrentinoInvocationInvokerH

//specific
#include "../../Utils/TrentinoUtilsPatternStaticClass.h"
#include "TrentinoInvocation.h"
#include "./../Core/TrentinoCore.h"

//baseclass
#include "TrentinoInvocationInvokerBase.h"
#include "../Core/TrentinoCoreComponentImplementationManagerBase.h"

namespace Trentino{
namespace Invocation 
{     
   //**********************************************************************************************
   //                                           Invoker
   //**********************************************************************************************
   //! \ingroup Invocation
   //! \brief Implementation of the InvokerBase interface.
   //**********************************************************************************************
   class INVOCATION_IMPORT_EXPORT Invoker : public InvokerBase 
   {
      //construction
   public:
      //*******************************************************************************************
      //                                       Invoker()
      //*******************************************************************************************
      //! \brief Empty constructor.
      //*******************************************************************************************
      Invoker();

      //*******************************************************************************************
      //                                      ~Invoker()
      //*******************************************************************************************
      //! \brief Empty destructor.
      //*******************************************************************************************
      virtual ~Invoker();
   private:
      //*******************************************************************************************
      //                                  Invoker(const Invoker&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copy construction.          
      //*******************************************************************************************
      Invoker(const Invoker&);

      //operators
   private:
      //*******************************************************************************************
      //                            operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.
      //*******************************************************************************************
      void operator=(const Invoker&);

      //services
   public:
      //*******************************************************************************************
      //                               invoke()
      //*******************************************************************************************
      // override from InvokerBase (see documentation in InvokerBase)
      //*******************************************************************************************
      virtual bool invoke( const Trentino::Invocation::InvocationData& data,
                         void* retVal,
                         const Trentino::Invocation::InvocationContext& ctx);

      //*******************************************************************************************
      //                               invoke()
      //*******************************************************************************************
      // override from InvokerBase (see documentation in InvokerBase)
      //*******************************************************************************************
      virtual bool invoke( const Trentino::Invocation::InvocationData& data,
                         void* retVal,
                         const Trentino::Invocation::InvocationContext& ctx,
                     const Trentino::RuntimeModel::ServiceBasePtr& targetService);

      //*******************************************************************************************
      //                                  addFilter()
      //*******************************************************************************************
      //! \brief Adds a new filter.
      //! \param[in] Shared pointer of Filter to add.
      //*******************************************************************************************
      //void addFilter(const Trentino::Invocation::Filtering::FilterPtr& filter) const;

      //*******************************************************************************************
      //                        componentImplementationManager()
      //*******************************************************************************************
      //! \brief Returns the Component Implementation Manager used by this Invoker.
      //! \return A shared pointer to a Component Implementation Manager instance. 
      //! \sa setComponentImplementationManager()
      //*******************************************************************************************
       Trentino::Core::ComponentImplementationManagerBasePtr componentImplementationManager() const;
      
      //*******************************************************************************************
      //                        setComponentImplementationManager()
      //*******************************************************************************************
      //! \brief Sets the Component Implementation Manager to be used by this Invoker.
      //! \param[in] componentImplementationManager A shared pointer to a Component Implementation 
      //!            Manager instance.
      //! \sa componentImplementationManager()
      //*******************************************************************************************
      void setComponentImplementationManager(const Trentino::Core::
         ComponentImplementationManagerBasePtr& componentImplementationManager);      
      //management
   private:
      //*******************************************************************************************
      //                        isSafeInvocationEnabled()
      //*******************************************************************************************
      //! \brief 
      //*******************************************************************************************
      bool isSafeInvocationEnabled() const;

     //data
   private:
       //! Component Implementation Manager used by the Invoker. 
       Trentino::Core::ComponentImplementationManagerBasePtr mComponentImplementationManager;
   };//class Invoker

   //inline
   #include "TrentinoInvocationInvoker.inl"

}//namespace Invocation
}//namespace Trentino

#endif //TrentinoInvocationInvokerH
