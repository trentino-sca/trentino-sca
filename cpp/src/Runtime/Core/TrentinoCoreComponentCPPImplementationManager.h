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

#ifndef TrentinoCoreComponentCPPImplementationManagerH
#define TrentinoCoreComponentCPPImplementationManagerH

//baseclass
#include "TrentinoCoreComponentImplementationManagerBase.h"

//standard
#include <set>
#include <map>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

//specific
#include "TrentinoCore.h"

namespace Trentino{
namespace Core
{	
   //**********************************************************************************************
   //                             ComponentCPPImplementationManager
   //**********************************************************************************************
   //! \ingroup Core
   //! \brief Responsible for creating and managing instances of component implementations of type
   //!        <implmentation.cpp>.
   //**********************************************************************************************   
   class CORE_IMPORT_EXPORT ComponentCPPImplementationManager :
      public Trentino::Core::ComponentImplementationManagerBase 
   {
      //additional
   private:
      //*******************************************************************************************
      //                                  ImplInfo
      //*******************************************************************************************
      //! Data structure containing information associated with an implementation. 
      //*******************************************************************************************
      struct ImplInfo
      {  
         //construction      
         ImplInfo();

         //data      
         //! \brief Stores a pointer to the eagerly initialized instance. 
         //!
         //! Used only for \c scope="composite" implementations. 
         void* instance;
         //! \brief Instance usage count.
         //!
         //!For \c scope="composite" implementations represents the usage count of the single
         //! instance (i.e.: how many invocations are currently using the instance). For 
         //! \c scope="stateless" implementations contains a value indicating how many instances
         //! are currently in use (since there can be only one user per instance).          
         unsigned int usageCount;                          
         //! \brief Mutex to guard access to a single ImplInfo instance
         boost::mutex mutex;
         //! \brief Conditional variable used to wait for the usage count to drop to 0
         boost::condition_variable noUsers;

      private:
         //! Disallow inadvertent copy construction
         ImplInfo(const ImplInfo&);

         //! Disallow assignment
         void operator=(const ImplInfo&);         
      };

      typedef boost::shared_ptr<ImplInfo> ImplInfoPtr;                                                  
      typedef std::map<const void*, ImplInfoPtr> ImplInfoMap;     

      //construction
   public:
      //*******************************************************************************************
      //                         ComponentCPPImplementationManager()
      //*******************************************************************************************
      //! \brief Empty constructor.     
      //*******************************************************************************************
      ComponentCPPImplementationManager();

   private:
      //*******************************************************************************************
      //          ComponentCPPImplementationManager(const ComponentCPPImplementationManager&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copy construction.      
      //*******************************************************************************************
      ComponentCPPImplementationManager(const ComponentCPPImplementationManager&);

      //operators
   private:
      //*******************************************************************************************
      //                                       operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.      
      //*******************************************************************************************
      void operator=(const ComponentCPPImplementationManager&);
      
      //services
   public:
      //*******************************************************************************************
      //                                        onInit()
      //*******************************************************************************************
      // override from ComponentImplementationManagerBase (see documentation also in 
      // ComponentImplementationManagerBase)
      //! \copydoc Core::ComponentImplementationManagerBase::onInit()
      //! 
      //! - For \c eagerInit="true"  \c composite scoped implementations  onInit() will immediately 
      //!   create an instance for later use. Dependency injection will be performed on the created 
      //!   instance: setter methods for all the references and properties will be called. 
      //! - For \c egarInit="false" or \c stateless scoped implementations onInit() has not effect. 
      //!
      //! \throw std::runtime_error If in case of \c eagerInit="true" implementations, the instance
      //!        couldn't be created for some reasons.  
      //*******************************************************************************************
      virtual void onInit(const Trentino::RuntimeModel::ConstComponentPtr& component);

      //*******************************************************************************************
      //              getInstance(const Trentino::RuntimeModel::ConstServiceBasePtr&)
      //*******************************************************************************************
      // override from ComponentImplementationManagerBase (see documentation also in 
      // ComponentImplementationManagerBase)
      //! \copydoc Core::ComponentImplementationManagerBase::getInstance()
      //! 
      //! \return If the corresponding component is neither in RuntimeModel::Component::Resolved
      //!         nor in RuntimeModel::Component::OptionsUnresolved states, \c nullptr is returned.
      //!         The component's state is accessed thread safely. 
      //!
      //! The behavior of this method depends on the values of the \c scope and \c eagerInit
      //! attributes.
      //! - \c scope="composite", \c eagerInit="false" \n
      //!   The first call to getInstance() for the given service creates an instance of the
      //!   service's parent component implementations and performs dependency injection. All
      //!   subsequent calls just return the instance created by the first call.
      //! - \c scope="composite", \c eagerInit="true" \n
      //!   Every call to getInstance() returns the instance already created by onInit().      
      //*******************************************************************************************
      virtual void* getInstance(const Trentino::RuntimeModel::ConstServiceBasePtr& service);

      //*******************************************************************************************
      //                                     releaseInstance()
      //*******************************************************************************************
      // override from ComponentImplementationManagerBase (see documentation also in 
      // ComponentImplementationManagerBase)
      //! \copydoc Core::ComponentImplementationManagerBase::releaseInstance()
      //! 
      //! The behavior of this method depends on the values of the \c scope and \c eagerInit
      //! attributes.
      //! - \c scope="composite", \c eagerInit="false" or \c eagerInit="true" \n
      //!   Decrements the usage count for the given instance. I.e. never destroys any instance. 
      //! - \c scope="stateless"  \n
      //!   Always destroys the given instance.       
      //!
      //! \attention Valid values for the \c instance argument are only those previously returned
      //!            by getInstance(). Passing something else will cause undefined behavior.
      //! \attention The passed instance and the passed service must match, i.e. calling 
      //!            releaseInstance() is allowed only for instance/service combinations priviously
      //!            process by getInstance(): 
      //!            \c instanceB=getService(serviceA)=>releaseInsatance(instanceB, serviceA). Any
      //!            other combinations will cause undefined behavior.
      //! \attention For \c scope="stateless" implementations, calling releaseInstance() 
      //!            subsequently more that once (without interim calls to getInstance()) for the 
      //!            same instance causes undefined behavior. 
      //*******************************************************************************************
      virtual void releaseInstance( void* instance
                                  , const Trentino::RuntimeModel::ConstServiceBasePtr& service);        

      //*******************************************************************************************
      //                                     onRemove()
      //*******************************************************************************************
      // override from ComponentImplementationManagerBase (see documentation also in 
      // ComponentImplementationManagerBase)
      //! \copydoc Core::ComponentImplementationManagerBase::onRemove()
      //! 
      //! The behavior of this method depends on the values of the \c scope and \c eagerInit
      //! attributes.
      //! - \c scope="composite", \c eagerInit="false" or \c eagerInit="true" \n
      //!   Blocks while the usage count for the instance is > 0, i.e. waits until all the clients
      //!   have released the instance by calling releaseInstance() as often as getInstance() was
      //!   called. When the usage count drops to 0 (or is already 0), the instance is destroyed,
      //!   and the method returns. 
      //! - \c scope="stateless" \n
      //!   Blocks until all the instances in use have been released, i.e. waits until 
      //!   releaseInstance() have been called for all instances. When this happens (or is already
      //!   the case), the methods returns).     
      //!
      //! \attention onRemove() relies on a cooperative behavior of the business logic. I.e. if
      //!            a service implementations has a deadlock or hangs for some other reasons,
      //!            onRemove() will never return since it will wait until the given instance
      //!            is released that in turn will happen only after the invocation completes
      //!            (what is not the case if the business logic hangs). 
      //! \note To achieve the desired behaviour for onRemove(), it should be ensured that while
      //!       onRemove() is executed (i.e. waits for all the invocations to complete and the
      //!       instances in use to be released) no new invocations are started (i.e. no 
      //!       instances are requested via getInstance()). This can be achived by putting the
      //!       corresponding component in some inaccessible state (a state different from 
      //!       RuntimeModel::Component::Resolved or RuntimeModel::Component::OptionalUnresolved).
      //!       Once this is the case, getInstance() will not return new instances and will not
      //!       increment the usage count, thus ensuring the onRemove() will return. \n
      //!       On the other side, allowing new invocations to be started (i.e. new instances to 
      //!       be allocated via getInstance()) while onRemove() is executed, is not an error and
      //!       might be also a kind of desired behavior in some situations. 
      //*******************************************************************************************
      virtual void onRemove(const Trentino::RuntimeModel::ConstComponentPtr& component);

      virtual void onInvoke(void* instance, 
         const Trentino::Invocation::InvocationData& data,
         void* retVal,
         const Trentino::Invocation::InvocationContext& ctx,
         const Trentino::RuntimeModel::ServiceBasePtr& targetService) const;

      //management
   private:      
      //*******************************************************************************************
      //               getInstance(const Trentino::RuntimeModel::ConstComponentPtr&)
      //*******************************************************************************************
      //! \brief Returns an instance of the given component's implementation.
      //!
      //! This method is called by getInstance(const Trentino::RuntimeModel::ServiceBasePtr&) and
      //! executes the greatest part of the actual logic. 
      //! \param[in] component Shared pointer to the component to retrieve the instance for. 
      //! \return A \c void pointer to an instance of the implementation class or an nullptr if
      //!         get instance could not be retrieved. 
      //! \sa getInstance(const Trentino::RuntimeModel::ServiceBasePtr&) 
      //*******************************************************************************************
	   void* getInstance(const Trentino::RuntimeModel::ConstComponentPtr& component);

      //*******************************************************************************************
      //                                          getImplInfo()
      //*******************************************************************************************
      //! \brief Returns an ImplInfo object containing information associated with an 
      //!        implementation.
      //!
      //! If no ImplInfo is associated with the given \c key, a new ImplInfo object is created and
      //! returned. 
      //! \param[in] key A \c void pointer to the Implementation object of a component. I.e.
      //!            \c component->implementation().get()
      //! \return A shared pointer to the ImplInfo object for the given \c key.      
      //*******************************************************************************************
      ImplInfoPtr getImplInfo(const void* key);

      //data
   private:
      //! Map containing ImplInfo objects for every registered implementation
      ImplInfoMap mImplInfoMap;                   
      //! Mutes to guard access to mImplInfoMap
      boost::mutex mImplInfoMapMutex;      

	};//class ComponentCPPImplementationManager

}//namespace Core
}//namespace Trentino

#endif //TrentinoCoreComponentCPPImplementationManagerH
