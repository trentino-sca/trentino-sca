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

#ifndef TrentinoCoreComponentCPPImplementationLifeCycleMethodManagerH
#define TrentinoCoreComponentCPPImplementationLifeCycleMethodManagerH


//standard

//specific
#include "TrentinoCore.h"
#include "../RuntimeModel/TrentinoRuntimeModel.h"
#include "../Invocation/TrentinoInvocationInvocationData.h"
#include "../Invocation/TrentinoInvocationInvocationContext.h"
#include "../XML/TrentinoXMLSchema.h"

namespace Trentino{
namespace Core
{	
   //**********************************************************************************************
   //                             CPPImplementationLifeCycleMethodManager
   //**********************************************************************************************
   //! \ingroup Core
   //! \brief is reponsible for calling lifecycle methods on a cpp implementation instance of 
   //! a component
   //**********************************************************************************************   
   class CORE_IMPORT_EXPORT CPPImplementationLifeCycleMethodManager
   {
    //construction
   public:
      CPPImplementationLifeCycleMethodManager();
      ~CPPImplementationLifeCycleMethodManager();

      //services
   public:
      //*******************************************************************************************
      //                                         callOnInitMethod()
      //*******************************************************************************************
      //! \brief call the onInit method
      //! \param const Trentino::RuntimeModel::ConstComponentPtr & component the component 
      //! to instantiate
      //! \param void * instance, the component implemenation instance
      //! \return void
      //*******************************************************************************************
      void callOnInitMethod( const Trentino::RuntimeModel::ConstComponentPtr& component, 
                                                           void* instance ) const;

      //*******************************************************************************************
      //                                         callOnDestroyMethod()
      //*******************************************************************************************
      //! \brief call the on destroy method
      //! \param const Trentino::RuntimeModel::ConstComponentPtr & component: : The component which 
      //! instance
      //! destroyed
      //! \param void * instance: the component implemenation instance
      //! \return void
      //*******************************************************************************************
      void callOnDestroyMethod( const Trentino::RuntimeModel::ConstComponentPtr& component, 
                                                              void* instance ) const;


      //*******************************************************************************************
      //                                         callSetContributionRootDirMethod()
      //*******************************************************************************************
      //! \brief call the set contribution dir lyfecycle method
      //! \param const Trentino::RuntimeModel::ConstComponentPtr & component: : The component which 
      //! instance
      //! is initialized
      //! \param void * instance: the component implemenation instance
      //! \return void
      //*******************************************************************************************
      void callSetContributionRootDirMethod(const Trentino::RuntimeModel::ConstComponentPtr& component, 
         void* instance ) const;


      //*******************************************************************************************
      //                                         deleteInstance()
      //*******************************************************************************************
      //! \brief delete this instance of the component
      //! \param const RuntimeModel::ConstComponentPtr & component: component which instance 
      // is deleted
      //! \param void * instance: the instance to delete
      //! \return void
      //*******************************************************************************************
      void deleteInstance(const RuntimeModel::ConstComponentPtr& component, void* instance) const;

      //*******************************************************************************************
      //                                  newInstance()
      //*******************************************************************************************
      //! \brief Convenience method for creating a new instance of the implementation class.
      //! \return Instance of the implementation class or a nullptr if no instance could be
      //!         created.
      //*******************************************************************************************
      void* newInstance(const RuntimeModel::ConstComponentPtr& component) const;

      //*******************************************************************************************
      //                                  invokeOnInstance()
      //*******************************************************************************************
      //! \brief invoke a method by using the Reflection runtime
      //*******************************************************************************************
      void invokeOnInstance(const Trentino::XML::Schema::Name&  serviceId, const RuntimeModel::ConstComponentPtr& component, const Trentino::Invocation::InvocationData& data
                    , void* retVal
                    , const Trentino::Invocation::InvocationContext& ctx, void* instance)const;
	};//class CPPImplementationLifeCycleMethodManager

}//namespace Core
}//namespace Trentino

#endif //TrentinoCoreComponentCPPImplementationLifeCycleMethodManagerH
