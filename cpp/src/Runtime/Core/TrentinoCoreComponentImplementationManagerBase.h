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

#ifndef TrentinoCoreComponentImplementationManagerBaseH
#define TrentinoCoreComponentImplementationManagerBaseH

//specific
#include "../RuntimeModel/TrentinoRuntimeModel.h"
#include "../Invocation/TrentinoInvocationInvocationContext.h"
#include "../Invocation/TrentinoInvocationInvocationData.h"
namespace Trentino{
namespace Core 
{
   //class declaration
   //**********************************************************************************************
   //                             ComponentImplementationManagerBase 
   //**********************************************************************************************
   //! \ingroup Core
   //! \brief Offers an interface for creating and managing instances of component implementations.   
   //**********************************************************************************************
	class ComponentImplementationManagerBase 
   {
      //construction
   public:
      virtual ~ComponentImplementationManagerBase(){}

      //services
	public:
      //*******************************************************************************************
      //                                        onInit()
      //*******************************************************************************************
      //! \brief Performs certain initializations for the given component's implementation.
      //!
      //! This method should be called for each component while its parent composite is put in the
      //! RuntimeModel::Composite::Running state. Dependent on the concrete options (SCDL
      //! attributes) specified for an implementation, onInit() will initialize necessary data
      //! structures and might also create implementation instances (for example for eagerly 
      //! initialized implementations. 
      //!
      //! onInit() can be considered as a method used to register components with the component
      //! implementation manager. Consequently, calling getInstance(), releaseInstance() or
      //! onRemove() with a component previously not registered via onInit() should be considered
      //! as undefined behavior. 
      //
      //! \param[in] component A shared pointer to the component to be processed.       
      //! \sa onRemove() 
      //*******************************************************************************************
      virtual void onInit(const Trentino::RuntimeModel::ConstComponentPtr& component) = 0;

      //*******************************************************************************************
      //                                        onInvoke()
      //*******************************************************************************************
      //! \brief invoke a method on an instance, given the invocation data and a context
      //! 
      //*******************************************************************************************
      virtual void onInvoke(void* instance, 
         const Trentino::Invocation::InvocationData& data,
         void* retVal,
         const Trentino::Invocation::InvocationContext& ctx,
         const Trentino::RuntimeModel::ServiceBasePtr& targetService) const =0;
      
      //*******************************************************************************************
      //                                    getInstance()
      //*******************************************************************************************
      //! \brief Returns an implementation instance for the given service. 
      //!
      //! \param[in] service A shared pointer the service to retrieve the instance for.
      //! \return A \c void pointer to an instance of the implementation class or nullptr if the
      //!         instance could not be retrieved. 
      //! \sa releaseInstance() 
      //*******************************************************************************************
      virtual void* getInstance(const Trentino::RuntimeModel::ConstServiceBasePtr& service) = 0;
                                                              
      //*******************************************************************************************
      //                                    releaseInstance()
      //*******************************************************************************************
      //! \brief Releases the given implementation instance.
      //!
      //! The meaning of "releasing an instance" and the steps involved depend on the concrete
      //! implementation and the specified options (SCDL attributes) and should be concretized 
      //! by derived classes. 
      //! \param[in] instance A \c void pointer the instance to be released.
      //! \param[in] service A shared pointer to the service the instance belongs to.       
      //! \sa getInstance() 
      //*******************************************************************************************
      virtual void releaseInstance( void* instance
                                  , const Trentino::RuntimeModel::ConstServiceBasePtr& service) = 0;      

      //*******************************************************************************************
      //                                        onRemove()
      //*******************************************************************************************
      //! \brief Ensures that all the currently existing implementation instances for the given
      //!        component are destroyed.
      //!
      //! This method should be called before a component is removed (e.g. during the undeployment
      //! of its parent composite).
      //!
      //! onRemove() will block until all clients of the component's implementation instances have 
      //! called releaseInstance() for every instance that is currently in use. Subsequently 
      //! onRemove() will destroy instance (if still necessary) and return. 
      //!
      //! \param[in] component A shared pointer to the component to be processed.       
      //! \sa onInit() 
      //*******************************************************************************************
      virtual void onRemove(const Trentino::RuntimeModel::ConstComponentPtr& component) = 0;

	};//class ComponentImplementationManagerBase

}//namespace Core
}//namespace Trentino

#endif //TrentinoCoreComponentImplementationManagerBaseH
