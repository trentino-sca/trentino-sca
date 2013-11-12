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

#ifndef TrentinoRuntimeModelReferenceH
#define TrentinoRuntimeModelReferenceH

//baseclass
#include "TrentinoRuntimeModelReferenceBase.h"

//standard
#include <string>

//specific
#include "../SCAModel/TrentinoSCAModel.h"
#include "../SCAModel/TrentinoSCAModelReference.h"
#include "TrentinoRuntimeModel.h"
#include "../XML/TrentinoXMLSchema.h"
#include "TrentinoRuntimeModelWireable.h"

namespace Trentino{
namespace RuntimeModel
{  
   //**********************************************************************************************
   //                                        Reference
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief Represents an SCA reference at runtime.
   //!
   //! The RuntimeModel::Reference class points to the corresponding  
   //! SCA::Model::ComponentTypeReference and eventually also to the SCA::Model::ComponentReference
   //! class and provides additional information associated with a reference.
   //! Examples for such additional information are:    
   //! - the reference's state
   //! - the reference's parent component
   //! - collection of wires connected to the reference 
   //! - etc.
   //! \todo specify exceptions thrown by all the methods/constructors
   //**********************************************************************************************
   class RUNTIMEMODEL_IMPORT_EXPORT Reference : public ReferenceBase
   {
      //construction
   public:
      //*******************************************************************************************
      //                                     Reference()
      //*******************************************************************************************
      //! \brief Constructs a reference with the given parent component and associates it with the
      //!        given SCA::Model::ComponentTypeReference.
      //! \param[in] scaReferenceType A shared pointer to an instance of  
      //!            SCA::Model::ComponentTypeReference the reference should be associated with.      
      //! \param[in] A shared pointer to the reference's parent component.            
      //*******************************************************************************************
      Reference( const Trentino::SCA::Model::ComponentTypeReferencePtr& scaReferenceType               
               , const ComponentPtr& component);
   private:
      //*******************************************************************************************
      //                              Reference(const Reference&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copy construction.      
      //*******************************************************************************************
      Reference(const Reference&);

      //operators
   private:      
      //*******************************************************************************************
      //                                       operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.
      //*******************************************************************************************
      void operator=(const Reference&);

      //services
   public:            
      //*******************************************************************************************
      //                                    scaReferenceType()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //! \copydoc RuntimeModel::ReferenceBase::scaReferenceType()
      //! \sa Reference()
      //*******************************************************************************************
      Trentino::SCA::Model::ComponentTypeReferencePtr scaReferenceType() const;      

      //*******************************************************************************************
      //                                    scaReference()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //! \copydoc RuntimeModel::ReferenceBase::scaReference() 
      //! \sa setSCAReference()
      //*******************************************************************************************
      Trentino::SCA::Model::ComponentReferencePtr scaReference() const;      

      //*******************************************************************************************
      //                                   setSCAReference()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)      
      //*******************************************************************************************
      virtual void setSCAReference(const Trentino::SCA::Model::ComponentReferencePtr& scaReference);

      //*******************************************************************************************
      //                                       component()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)     
      //*******************************************************************************************
      virtual ComponentWeakPtr component() const;

      //*******************************************************************************************
      //                                        state()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual Reference::State state() const;

      //*******************************************************************************************
      //                                         setState()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual void setState(Reference::State state);

      virtual const std::vector<std::string>& targets() const;

            //*******************************************************************************************
      //                                         multiplicity()
      //*******************************************************************************************
      //! \brief return the multiplicity of this reference
      //*******************************************************************************************
      virtual const std::string multiplicity() const;

      //*******************************************************************************************
      //                                         multiplicity()
      //*******************************************************************************************
      //! \brief return the interface element of this reference
      //*******************************************************************************************
      virtual const Trentino::SCA::Model::InterfacePtr interfaceElement() const;

      virtual Trentino::SCA::Model::MetadataPtr metadataElement() const;

      //*******************************************************************************************
      //                                         isNonOverridable()
      //*******************************************************************************************
      //! \brief return the isNonOverridable attribute of this reference
      //*******************************************************************************************
      virtual const bool isNonOverridable() const;
      
      //*******************************************************************************************
      //                                       setSetterMethod()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual void setSetterMethod(const Trentino::Reflection::ReflectMethodPtr& setter);

      //*******************************************************************************************
      //                                  invokeSetter(void*, void*)
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual void invokeSetter(void* instance, void* value) const;

      //*******************************************************************************************
      //                               invokeSetter(void*, const VoidPtrList&)
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual void invokeSetter(void* instance, const VoidPtrList& valueList) const;

      //*******************************************************************************************
      //                                       proxyReflectObject()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual Trentino::Reflection::ReflectObjectPtr proxyReflectObject() const;
      
      //*******************************************************************************************
      //                                       setProxyReflectObject()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual void setProxyReflectObject(
         const Trentino::Reflection::ReflectObjectPtr& proxyReflectObject);

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
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual const WeakReferenceBases& promotedTo() const;

      //*******************************************************************************************
      //                                 addPromotedTo()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual void addPromotedTo(const ReferenceBasePtr& reference);

      //*******************************************************************************************
      //                                 promotedBy()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual const WeakReferenceBases& promotedBy() const;

      //*******************************************************************************************
      //                                 addPromotedBy()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual void addPromotedBy(const ReferenceBasePtr& reference);
      //! @}

      //*******************************************************************************************
      //                                 wireableSupport()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual Wireable& wireableSupport();

      //*******************************************************************************************
      //                                 wireableSupport() const
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual const Wireable& wireableSupport() const;

      //! \name convenience methods 
      //! @{
      //*******************************************************************************************
      //                                         name()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //! //! \copydoc RuntimeModel::ReferenceBase::name()
      //! \return scaServiceType()->name()
      //*******************************************************************************************
      virtual const Trentino::XML::Schema::NCName& name() const;
      
      //*******************************************************************************************
      //                                    getTargetServices()
      //*******************************************************************************************
      // override from ReferenceBase (see documentation in ReferenceBase)
      //*******************************************************************************************
      virtual const ServiceBases getTargetServices() const;
      //! @}      

      virtual const Trentino::SCA::Model::MetadataPtr metaData() const;

      //data
   private:      
      //! the SCA::Model::ComponentTypeReference associated with the reference
      const Trentino::SCA::Model::ComponentTypeReferencePtr mSCAReferenceType;            
      //! the reference's parent component
      const ComponentWeakPtr mComponent;
      //! the reference state
      ReferenceBase::State mState;
      //! object to access the reflection code for the reference's setter method
      Trentino::Reflection::ReflectMethodPtr mSetter; 
      //! object to access the reflection code for the reference's proxy
      Trentino::Reflection::ReflectObjectPtr mProxyReflectObject;
      //! the SCA::Model::ComponentReference associated with the reference
      Trentino::SCA::Model::ComponentReferencePtr mSCAReference;       
      //! collection of references the current reference is promoted to
      WeakReferenceBases mPromotedTo;
      //! collection of references that are promoted to the current reference
      WeakReferenceBases mPromotedBy;
      //! object managing the wire handling for the reference  
      Wireable mWireableSupport;
      //! Metadata member: joined from scaReference and scaReferenceType
      Trentino::SCA::Model::MetadataPtr mMetaData;

   }; //class Reference   

} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelReferenceH
