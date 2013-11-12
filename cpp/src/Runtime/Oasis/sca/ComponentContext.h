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
 
#ifndef Oasis_sca_ComponentContextH
#define Oasis_sca_ComponentContextH
 
#include "ServiceReference.h"
#include "ServiceProxy.h"

//#include "commonj/sdo/sdo.h"
#include <string>
#include <vector>
 
#ifdef WIN32
#ifdef CORE_EXPORTS
#define OASISSCA_IMPORT_EXPORT __declspec(dllexport)
#else
#define OASISSCA_IMPORT_EXPORT __declspec(dllimport)       
#endif //CORE_EXPORTS
#else
#define OASISSCA_IMPORT_EXPORT
#endif //WIN32


namespace oasis{
namespace sca 
{
   //forward declarations
   class ComponentContext;
   typedef RefCountingPointer<ComponentContext> ComponentContextPtr;
 
   //class declaration
   //**********************************************************************************************
   //                             ComponentContext                          
   //**********************************************************************************************
   //! \brief ComponentContext is used to get all relevant information about the component.
   //**********************************************************************************************
   class ComponentContext 
   {
     //construction
   public:
      //*******************************************************************************************
      //                                     ~ComponentContext()                               
      //*******************************************************************************************
      //! Destructor.
      //*******************************************************************************************
      virtual ~ComponentContext() {}

      //services
   public:
      //*******************************************************************************************
      //                                     getCurrent()              
      //*******************************************************************************************
		//! \brief  A C++ component implementation uses ComponentContext::getCurrent() to get a 
      //!         ComponentContext object for itself.
      //! \return ComponentContext for the current component.
      //*******************************************************************************************
      OASISSCA_IMPORT_EXPORT static ComponentContextPtr getCurrent();

      //*******************************************************************************************
      //                                     getURI()              
      //*******************************************************************************************
		//! \brief  A C++ component implementation uses getURI() to get a structural URI for itself.
      //! \return Structural URI for the current component
      //*******************************************************************************************
      virtual std::string getURI() const = 0;

      //*******************************************************************************************
      //                                     getService()              
      //*******************************************************************************************
		//! \brief  A C++ component implementation uses getService() to get a service proxy 
      //!         implementing the interface defined for a Reference.
      //!         Throws MultipleServicesException if the reference resolves 
      //!         to more than one service.
      //! \param  Name of the Reference to get an interface object for.
      //! \return Pointer to a \sa ServiceProxy implementing the interface of the Reference. 
      //!         This will be nullptr if referenceName is not defined for the component.
      //*******************************************************************************************
      virtual ServiceProxyPtr getService(const std::string& referenceName) const = 0;

      //*******************************************************************************************
      //                                     getServices()              
      //*******************************************************************************************
		//! \brief  A C++ component implementation uses getServices() to get a vector 
      //!         of service proxies implementing 1232 the interface defined for a Reference.
      //! \param  Name of the Reference to get an interface object for.
      //! \return Vector of pointers to ServiceProxy objects implementing 
      //!         the interface of the Reference. 
      //!         This vector will be empty if referenceName is not defined for the component. 
      //!         Operations need to be invoked on each object in the vector.
      //*******************************************************************************************
      virtual std::vector<ServiceProxyPtr> getServices(const std::string& referenceName) const = 0;

      //*******************************************************************************************
      //                                     getServiceReference()              
      //*******************************************************************************************
		//! \brief  A C++ component implementation uses getServiceReference() to get a 
      //!         \sa ServiceReference for a Reference.
      //!         Throws a \sa MultipleServicesException 
      //!         if the reference resolves to more than one service.
      //! \param  Name of the Reference to get a ServiceReference for.
      //! \return \sa ServiceReference for the Reference. 
      //!         This will be nullptr if referenceName is not defined for the component.
      //*******************************************************************************************
      virtual ServiceReferencePtr getServiceReference(const std::string& referenceName) const = 0;

      //*******************************************************************************************
      //                                     getServiceReferences()              
      //*******************************************************************************************
		//! \brief  A C++ component implementation uses getServiceReferences() to get a vector 
      //!         of \sa ServiceReference for a Reference.
      //! \param  Name of the Reference to get a list of ServiceReferences for.
      //! \return Vector of ServiceReferences for the Reference. 
      //!         This vector will be empty if referenceName is not defined for the component.
      //*******************************************************************************************
      virtual std::vector<ServiceReferencePtr> getServiceReferences(
         const std::string& referenceName) const = 0;

      //*******************************************************************************************
      //                                     getSelfReference()              
      //*******************************************************************************************
		//! \brief  A C++ component implementation uses getSelfReference()to get a 
      //!         \sa ServiceReference for use with some callback APIs.
      //!         Throws MultipleServicesException if the component implements more than one Service
      //! \return A ServiceReference for the service provided by this component.
      //*******************************************************************************************
      virtual ServiceReferencePtr getSelfReference() const = 0;

      //*******************************************************************************************
      //                                     getSelfReference()              
      //*******************************************************************************************
		//! \brief  A C++ component implementation uses getSelfReference()to get a 
      //!         \sa ServiceReference for use with some callback APIs.
      //! \param  Name of the Service to get a ServiceReference
      //! \return A ServiceReference for the service provided by this component.
      //*******************************************************************************************
      virtual ServiceReferencePtr getSelfReference(const std::string& serviceName) const = 0;
      
      //! \todo property support in Trentino
      // virtual commonj::sdo::DataObjectPtr getProperties() const = 0;
      // virtual commonj::sdo::DataFactoryPtr getDataFactory() const = 0;

      //*******************************************************************************************
      //                                     addRef()              
      //*******************************************************************************************
      //! \brief  Adds internal reference of object by one.
      //! \return Returns number of used references. 
      //*******************************************************************************************
      virtual uint32_t addRef() = 0;

      //*******************************************************************************************
      //                                     releaseRef()              
      //*******************************************************************************************
      //! \brief  Reduces internal reference of object by one.
      //!         If object reference is 0, object will be deleted by releaseRef().
      //! \return Returns number of used references. Returns 0 if object is destroyed.
      //*******************************************************************************************
      virtual uint32_t releaseRef() = 0;
   }; //class ComponentContext 

   //! Support function for \sa RefCountingPointer, increments internal object reference by one.
   void TrentinoFuncPtrAddRef(ComponentContext* ctx);

   //! Support function for \sa RefCountingPointer, decrements internal object reference by one.
   void TrentinoFuncPtrReleaseRef(ComponentContext* ctx);

   #include "ComponentContext.inl"
} // namespace sca
} // namespace oasis
 
#endif //Oasis_sca_ComponentContextH
