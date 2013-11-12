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

#ifndef TrentinoRuntimeModelReferenceBaseH
#define TrentinoRuntimeModelReferenceBaseH

//standard
#include <list>

//specific
#include "TrentinoRuntimeModel.h"
#include "../SCAModel/TrentinoSCAModel.h"
#include "../../Utils/TrentinoUtilsURI.h"
#include "../ReflectionRuntime/TrentinoReflectionIncludes.h"

namespace Trentino{
namespace RuntimeModel
{
   class Wireable;

   //**********************************************************************************************
   //                                        ReferenceBase
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief Interface for the RuntimeModel::Reference class to make it easy mockable. 
   //!
   //! The RuntimeModel::ReferenceBase class exist for only one real purpose: to facilitate testing
   //! by making the Runtime::Reference class easily mockable.
   //**********************************************************************************************
   class ReferenceBase
   {
      //additional
   public:
      enum State{
         //! \brief The reference's initial state
         Initial,
         //! \brief This reference is currently being resolved. 
         //! \sa Trentino::RuntimeModel::Component::Resolving
         Resolving,
         //! brief This reference is wired to a service that is available.
         Resolved,
         //! \brief This Reference is not wired to a target service. But wiring is optional.
         OptionalUnresolved,
         //! \brief This Reference is not wired to a service or it is wired to a service that 
         //!        is not in Available state.
         Unresolved,
         //! \brief The reference is currently being unresolved.
         Unresolving };

      typedef std::list<void*> VoidPtrList;
      
      //construction
   public:
      virtual ~ReferenceBase(){}

      //services
   public:

      //*******************************************************************************************
      //                                    scaReferenceType()
      //*******************************************************************************************
      //! \brief Returns the SCA::Model::ComponentTypeReference associated with the reference.
      //! \return A shared pointer to SCA::Model::ComponentTypeReference instance the reference is
      //!         associated with.
      //*******************************************************************************************
      virtual Trentino::SCA::Model::ComponentTypeReferencePtr scaReferenceType() const = 0;

      //*******************************************************************************************
      //                                    scaReference()
      //*******************************************************************************************
      //! \brief Returns the SCA::Model::ComponentReference associated with the reference.
      //! \return A shared pointer to SCA::Model::ComponentReference instance the reference is
      //!         associated with. An empty shared pointer is returned in case there is no such
      //!         association.
      //*******************************************************************************************
      virtual Trentino::SCA::Model::ComponentReferencePtr scaReference() const = 0;

      //*******************************************************************************************
      //                                   setSCAReference()
      //*******************************************************************************************
      //! \brief Sets the SCA::Model::ComponentReference to be associated with the reference. 
      //! \param[in] A Shared pointer to the SCA::Model::ComponentReference that should be 
      //!            associated with the reference. 
      //*******************************************************************************************
      virtual void setSCAReference(
         const Trentino::SCA::Model::ComponentReferencePtr& scaReference) = 0;

      //*******************************************************************************************
      //                                       component()
      //*******************************************************************************************
      //! \brief Returns the reference's parent component.
      //! \return A shared pointer to the reference's URI.      
      //*******************************************************************************************
      virtual ComponentWeakPtr component() const = 0;

      //*******************************************************************************************
      //                                        state()
      //*******************************************************************************************
      //! \brief Returns the reference's state.
      //! \return The reference's state.
      //! \sa setState()
      //*******************************************************************************************
      virtual ReferenceBase::State state() const = 0;

      //*******************************************************************************************
      //                                         setState()
      //*******************************************************************************************
      //! \brief Sets the reference's state.
      //! \param[in] state The state to set. 
      //! \sa state()
      //*******************************************************************************************
      virtual void setState(ReferenceBase::State state) = 0;

      //*******************************************************************************************
      //                                         targets()
      //*******************************************************************************************
      //! \brief get the reference targets.
      //*******************************************************************************************
      virtual const std::vector<std::string>& targets() const =0;

     
      //*******************************************************************************************
      //                                         multiplicity()
      //*******************************************************************************************
      //! \brief return the multiplicity of this reference
      //*******************************************************************************************
      virtual const std::string multiplicity() const =0;

      //*******************************************************************************************
      //                                         multiplicity()
      //*******************************************************************************************
      //! \brief return the interface element of this reference
      //*******************************************************************************************
      virtual const Trentino::SCA::Model::InterfacePtr interfaceElement() const=0;

      //*******************************************************************************************
      //                                         isNonOverridable()
      //*******************************************************************************************
      //! \brief return the isNonOverridable attribute of this reference
      //*******************************************************************************************
      virtual const bool isNonOverridable() const=0;

      virtual Trentino::SCA::Model::MetadataPtr metadataElement() const=0;

      //*******************************************************************************************
      //                                       setSetterMethod()
      //*******************************************************************************************
      //! \brief Sets the reference's setter method. 
      //! \param[in] setter Shared pointer to the object to access the reflection code for the
      //!            reference's setter method.
      //! \sa invokeSetter(void*, void*) const, invokeSetter(void*, const VoidPtrList&) const
      //*******************************************************************************************
      virtual void setSetterMethod(const Trentino::Reflection::ReflectMethodPtr& setter) = 0;

      //*******************************************************************************************
      //                                  invokeSetter(void*, void*)
      //*******************************************************************************************
      //! \brief Invokes the reference's setter method for references with multiplicity <= 1.
      //!
      //! This method is used to perform dependency injection. A component implementation is 
      //! supposed to define setter methods (such as setServiceA() etc.) which will be called by 
      //! Trentino to provide the component with pointers to the depended services. In order to 
      //! perform this callback Trentino will use the invokeSetter() method. 
      //!
      //! In a simplified, schematic view invokeSetter() performs the following:      
      //! \code instance->someSetterMethod(setterValue); \endcode
      //! where "someSetterMethod" is determined by the reflect object provided via 
      //! setSetterMethod(). 
      //! \param[in] instance Pointer to the instance of a component's implementation to call the
      //!            setter method for.
      //! \param[in] setterValue Pointer to the object to be passed as argument to the setter 
      //!            method. In real situations this should be a pointer to a proxy object 
      //!            representing the dependent service.
      //! \attention Calling this method for a reference with multiplicity > 1 will cause 
      //!            undefined behavior.
      //! \attention If no setter method was set by a previous call to setSetterMethod()
      //!            calling this method has no effect. 
      //! \sa invokeSetter(void*, const VoidPtrList&) const, setSetterMethod()
      //*******************************************************************************************
      virtual void invokeSetter(void* instance, void* value) const = 0;

      //*******************************************************************************************
      //                               invokeSetter(void*, const VoidPtrList&)
      //*******************************************************************************************
      //! \brief Invokes the reference's setter method for references with multiplicity > 1
      //!
      //! This is an overload of the invokeSetter(void*, void*) const method to be used for
      //! references with multiplicity > 1.
      //! \param[in] instance Pointer to the instance of a component's implementation to call the
      //!            setter method for. 
      //! \param[in] valueList List of pointers to the objects to be passes as argument to the
      //!            setter method. In real situation this should be a list of pointer to proxy
      //!            objects representing the dependent services. 
      //! \attention Calling this method for a reference with multiplicity <= 1 will cause 
      //!            undefined behavior.
      //! \attention If no setter method was set by a previous call to setSetterMethod()
      //!            calling this method has no effect. 
      //! \sa invokeSetter(void*, void*) const, setSetterMethod()
      //*******************************************************************************************
      virtual void invokeSetter(void* instance, const VoidPtrList& valueList) const = 0;

      //*******************************************************************************************
      //                                       proxyReflectObject()
      //*******************************************************************************************
      //! \brief Returns the reference's proxy reflect object.
      //!
      //! The proxy reflect object can be used to create instances of proxy classes that are used
      //! to perform invocations through this reference. 
      //! \return Shared pointer to the object for accessing the reflection code for the 
      //!         reference's proxy. 
      //! \sa setProxyReflectObject()
      //*******************************************************************************************
      virtual Trentino::Reflection::ReflectObjectPtr proxyReflectObject() const = 0;

      //*******************************************************************************************
      //                                       setProxyReflectObject()
      //*******************************************************************************************
      //! \brief Sets the reference's proxy reflect object.
      //!
      //! The proxy reflect object will be used to create instances of proxy classes that are 
      //! used to perform invocations through this reference. 
      //! \param[in] proxyReflectObject Shared pointer to the object for accessing the reflection 
      //!            code for the reference's proxy. 
      //! \sa proxyReflectObject()
      //*******************************************************************************************
      virtual void setProxyReflectObject(
         const Trentino::Reflection::ReflectObjectPtr& proxyReflectObject) = 0;

      //*******************************************************************************************
      //! \name Promotion      
      //! @{
      //! A reference that is attached to a component which is implemented by a composite can be 
      //! promoted to one or more references contained in the implementing composite. It is also 
      //! allowed for one reference to be the target for an arbitrary number of promotions (see
      //! also Assembly Spec 1.1, chapters 5.1 and 5.6)      
      //!
      //! The admissible promotion relations are illustrated in the following graph.
      //! \image html ReferencePromotionGraph.png
      //! The four methods in this group serve for accessing and modifying the promotion relations
      //! for the current reference: for the given example graph promotedTo() will return ServiceC
      //! and promotedBy() will return ca collection containg ServiceA and ServiceB. 
      //*******************************************************************************************

      //*******************************************************************************************
      //                                 promotedTo()
      //*******************************************************************************************
      //! \brief Returns the references the current reference is promoted to. 
      //! \return A collection of weak pointers to references the current reference is promoted to. 
      //!         An empty collection is returned in case the current reference is not promoted to
      //!         any reference.
      //! \sa addPromotedTo()
      //*******************************************************************************************
      virtual const WeakReferenceBases& promotedTo() const = 0;

      //*******************************************************************************************
      //                                 addPromotedTo()
      //*******************************************************************************************
      //! \brief Adds a reference to the collection of reference the current reference is promoted
      //!        to 
      //! \param[in] reference A shared pointer to the reference that should be added to the 
      //!            collection of reference the current reference is promote to.
      //! \sa promotedTo()
      //*******************************************************************************************
      virtual void addPromotedTo(const ReferenceBasePtr& reference) = 0;

      //*******************************************************************************************
      //                                 promotedBy()
      //*******************************************************************************************
      //! \brief Returns a collection of reference that are promoted to the current reference. 
      //! \return A collection of weak pointers to references that are promoted to the current 
      //!         reference. An empty collection is returned in case the current reference is not
      //!         promoted by any reference. 
      //! \sa addPromotedBy()
      //*******************************************************************************************
      virtual const WeakReferenceBases& promotedBy() const = 0;

      //*******************************************************************************************
      //                                 addPromotedBy()
      //*******************************************************************************************
      //! \brief Adds a reference to the collection of references that are promoted the the current
      //!        reference. 
      //! \param[in] reference A shared pointer to the reference that should be added to the 
      //!            collection of reference that are promoted to the current reference.
      //! \sa promotedBy()
      //*******************************************************************************************
      virtual void addPromotedBy(const ReferenceBasePtr& reference) = 0;
      //! @}

      //*******************************************************************************************
      //                                 wireableSupport()
      //*******************************************************************************************
      //! \brief Returns the RuntimeModel::Wirable object associated with this reference.
      //! \return Reference to the RuntimeModel::Wirable object associated with this reference.      
      //*******************************************************************************************
      virtual Wireable& wireableSupport() = 0;      

      //*******************************************************************************************
      //                                 wireableSupport() const
      //*******************************************************************************************
      //! \overload wireableSupport()     
      //*******************************************************************************************
      virtual const Wireable& wireableSupport() const = 0;

      //! \name convenience methods 
      //! @{
      //*******************************************************************************************
      //                                         name()
      //*******************************************************************************************
      //! \brief Convenience method to access SCA::Model reference name. 
      //! \return The reference's name. 
      //*******************************************************************************************
      virtual const Trentino::XML::Schema::NCName& name() const = 0;
      
      //*******************************************************************************************
      //                                    getTargetServices()
      //*******************************************************************************************
      //! \brief Returns a list of target services which the reference is wired to.
      //! \return A collection of services the references is wired to.
      //*******************************************************************************************
      virtual const ServiceBases getTargetServices() const = 0;
      //! @}      
      //*******************************************************************************************
      //                                 metaData()
      //*******************************************************************************************
      //! \brief Returns reference metadata used for service discovery purposes,
      //! \return Joined metadata containing all attributes from both scaReference and
      //!  scaReferenceType
      //*******************************************************************************************
      virtual const Trentino::SCA::Model::MetadataPtr metaData() const = 0;


   };//class ReferenceBase

} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelReferenceBaseH
