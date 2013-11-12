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

#ifndef TrentinoRuntimeModelComponentH
#define TrentinoRuntimeModelComponentH

//standard
#include <string>
#include <boost/thread/recursive_mutex.hpp>

//specific
#include "TrentinoRuntimeModel.h"
#include "../SCAModel/TrentinoSCAModel.h"
#include "../SCAModel/TrentinoSCAModelComponent.h"
#include "../../Utils/TrentinoUtilsURI.h"
#include "../ReflectionRuntime/TrentinoReflectionDataRegistry.h"

namespace Trentino{
namespace RuntimeModel
{
   //**********************************************************************************************
   //                                        Component
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief Represents an SCA component at runtime.
   //!
   //! The RuntimeModel::Component class points to the corresponding SCA::Model::Component class 
   //! and provides additional information associated with a component. 
   //! Examples for such additional information are: 
   //! - the component's structural URI
   //! - the component's state
   //! - a pointer to the RuntimeModel::Composite in which the component is contained 
   //! - a collection of services, references and properties contained in the component
   //! - etc.
   //! \todo specify exceptions thrown by all the methods/constructors
   //**********************************************************************************************
   class RUNTIMEMODEL_IMPORT_EXPORT Component
   {
      //additional
   public:
      enum State{
         //! \brief the component's initial state
         Initial,
         //! The references of the component are currently being resolved. This is a pending state
         //! in which certain references might haven been already processed and set to a fixed
         //! state (Resolved, OptionalUnresolved or Unresolved), others are currently being 
         //! resolved and thus are also in Resolving state, and still others will be processed 
         //! in future and therefore are in the initial default state (Unresolved). 
         //! This state is in particular needed to handle circular dependencies. Consider the 
         //! following constellation:
         //! \verbatim
         //! ------------------------------------------
         //! |   -------       -------       -------   |
         //! |  |       |     |       |     |       |  |
         //!  ->|   A   |---->|   B   |---->|   C   |--
         //!    |       |     |       |     |       |
         //!     -------       -------       -------
         //! \endverbatim
         //! Resolving A will cause resolving B will cause resolving C. Before A has been
         //! resolved completely C already needs A. So either C will try to resolve A twice since
         //! it is currently already being resolved (bad thing!) or it will give up and issue an
         //! error because it's not possible to wire to unresolved components and thus making
         //! circular dependencies impossible (also a band thing). The 'Resolving' state allows
         //! for handling such situation correctly. 
         Resolving,
         //! All of the component's references are in Resolved state.
         //! Additional condition for components implemented by composites: all the components in
         //! the composite used as implementation are in Resolved state. 
         Resolved,
         //! At least one of the component's references is in OptionalUnresolved state.
         OptionalUnresolved,
         //! At least one of the component's references is in Unresolved state.
         //! Additional condition for components implemented by composites: at least one component 
         //! in the composite used as implementation is in Unresolved state.
         Unresolved,
         //! The component's implementation instances are about to be destroyed.
         Stopping };

      //construction
   public:
      //*******************************************************************************************
      //                                     Component()
      //*******************************************************************************************
      //! \brief Constructs a component with the given URI, parent composite, implementation and 
      //!        associates it with the given SCA::Model::Component.
      //! \param[in] scaComponent A shared pointer to the SCA::Model::Component instance the
      //!            component should be associated with.      
      //! \param[in] A shared pointer to the component's parent composite.
      //! \param[in] A shared pointer to the component's implementation. An instance of a derived
      //!            class of RuntimeModel::Implementation (such as RuntimeModel::Composite or
      //!            RuntimeModel::CPPImplementation) should be passed.
      //! \sa scaComponent(), composite(), uri()
      //*******************************************************************************************
      Component( const Trentino::SCA::Model::ComponentPtr& scaComponent               
               , const CompositePtr& composite
               , const ImplementationPtr& implementation);
   private:      
      //*******************************************************************************************
      //                              Component(const Component&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copy construction.      
      //*******************************************************************************************
      Component(const Component&);

      //operators
   private:
      //*******************************************************************************************
      //                                       operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.
      //*******************************************************************************************
      void operator=(const Component&);

      //services
   public:

      const std::string& name() const;
      //*******************************************************************************************
      //                                    scaComponent()
      //*******************************************************************************************
      //! \brief Returns the SCA::Model::Component associated with the component.
      //! \return A shared pointer to SCA::Model::Component instance the component is associated
      //!         with.
      //! \sa Component()
      //*******************************************************************************************
      Trentino::SCA::Model::ComponentPtr scaComponent() const;

      //*******************************************************************************************
      //                                         uri()
      //*******************************************************************************************
      //! \brief Returns the component's structural URI.
      //! \return A const reference to the component's structural URI.      
      //*******************************************************************************************
      const Trentino::Utils::URI& uri() const;
      
      //*******************************************************************************************
      //                                       composite()
      //*******************************************************************************************
      //! \brief Returns the component's parent composite.
      //! \return A weak pointer to the component's parent composite.
      //! \sa Component()
      //*******************************************************************************************
      CompositeWeakPtr composite() const;

      //*******************************************************************************************
      //                                     implementation()
      //*******************************************************************************************
      //! \brief Returns the component's implementation.
      //! \return A shared pointer to the component's implementation.
      //! \sa Component()
      //*******************************************************************************************
      ImplementationPtr implementation() const;

      //*******************************************************************************************
      //                                         services()
      //*******************************************************************************************
      //! \brief Returns a collection of the component's services.
      //! \return A const reference to the collection of the component's services.
      //! \sa addService()
      //*******************************************************************************************
      const ServiceBases& services() const;

      //*******************************************************************************************
      //                                        references()
      //*******************************************************************************************
      //! \brief Returns a collection of the component's references.
      //! \return A const reference to the collection of the component's references.
      //! \sa addReference()
      //*******************************************************************************************
      const ReferenceBases& references() const;

      //*******************************************************************************************
      //                                        properties()
      //*******************************************************************************************
      //! \brief Returns a collection of the component's properties.
      //! \return A const reference to the collection of the component's properties.
      //! \sa addProperties()
      //*******************************************************************************************
      const Properties& properties() const;

      //*******************************************************************************************
      //                                        properties()
      //*******************************************************************************************
      //! \brief get the regiytry that hold this component instances
      //*******************************************************************************************
      Trentino::Reflection::DataRegistry& dataRegistry()const;

      //*******************************************************************************************
      //                                           state()
      //*******************************************************************************************
      //! \brief Returns the component's state.
      //! \return The component's state.
      //! \sa setState()
      //*******************************************************************************************
      State state() const;

      //*******************************************************************************************
      //                                         setState()
      //*******************************************************************************************
      //! \brief Sets the component's state.
      //! \param[in] The state to set. 
      //! \sa state()
      //*******************************************************************************************
      void setState(State state);

      //*******************************************************************************************
      //                                         addService()
      //*******************************************************************************************
      //! \brief Adds a service to the component.
      //! \param[in] A shared pointer to the service to add. 
      //! \sa services()
      //*******************************************************************************************
      void addService(const ServiceBasePtr& service);

      //*******************************************************************************************
      //                                         addReference()
      //*******************************************************************************************
      //! \brief Adds a reference to the component.
      //! \param[in] A shared pointer to the reference to add. 
      //! \sa references()
      //*******************************************************************************************
      void addReference(const ReferenceBasePtr& reference);

      //*******************************************************************************************
      //                                         addProperty()
      //*******************************************************************************************
      //! \brief Adds a property to the component.
      //! \param[in] A shared pointer to the property to add. 
      //! \sa properties()
      //*******************************************************************************************
      void addProperty(const PropertyPtr& property);

      //*******************************************************************************************
      //                                     findServiceByName()
      //*******************************************************************************************
      //! \brief Finds a service by name.
      //! \param[in] name Name of the service to search for.
      //! \return A shared pointer to the found service or an empty shared pointer if no 
      //!         service with the given name could be found.
      //*******************************************************************************************
      ServiceBasePtr findServiceByName(const std::string& name) const;

      //*******************************************************************************************
      //                                     findServiceByName()
      //*******************************************************************************************
      //! \brief Finds a reference by name.
      //! \param[in] name Name of the reference to search for.
      //! \return A shared pointer to the found reference or an empty shared pointer if no 
      //!         reference with the given name could be found.
      //*******************************************************************************************
      ReferenceBasePtr findReferenceByName(const std::string& name) const;

      //*******************************************************************************************
      //                                     findPropertyByName()
      //*******************************************************************************************
      //! \brief Finds a property by name.
      //! \param[in] name Name of the property to search for.
      //! \return A shared pointer to the found property or an empty shared pointer if no 
      //!         property with the given name could be found.
      //*******************************************************************************************
      PropertyPtr findPropertyByName(const std::string& name) const;
      
      //*******************************************************************************************
      //                                     getImplementationType()
      //*******************************************************************************************
      //! \brief convenience method to get the implementationType of this component
      //! \return const Trentino::XML::Schema::QName& return a QName of the ImplementationType
      //*******************************************************************************************
      const Trentino::XML::Schema::QName& getImplementationType() const;

      //*******************************************************************************************
      //                                           mutex()
      //*******************************************************************************************
      //! \brief Returns a shared mutex to be used for accessing the component's data in a one
      //!        writer multiple reader manner.            
      //! \return Reference to a shared mutex.
      //*******************************************************************************************
      boost::recursive_mutex& mutex() const;

      //****************************************************************************************************
      //                                         visit()
      //****************************************************************************************************
      //! \brief visit this component
      //! \param VisitorPtr & visitor
      //! \return void
      //****************************************************************************************************
      bool visit( VisitorPtr& visitor );
      //management
   private:
      //*******************************************************************************************
      //                                     computeStructuralURI
      //*******************************************************************************************
      //! \brief Returns the component's structural URI (see Assembly Spec 1.1, chapter 5.8) .
      //! \return The component's structural URI.
      //! \attention Correct results are retrieved only in case the complete object hierarchy 
      //!            starting at the component's parent composite (i.e. \c 
      //!            this->composite()->component()->composite()()...) is set up
      //!            correctly. 
      //! \attention In case, at some point in the hierarchy at least one parent composite of a
      //!            component is an empty pointer, the result is undefined behavior.
      //*******************************************************************************************
      Trentino::Utils::URI computeStructuralURI() const;

      //data
   private: 
      //! the SCA::Model::Component associated with the component
      const Trentino::SCA::Model::ComponentPtr mSCAComponent;      
      //! the component's parent composite
      const CompositeWeakPtr mComposite;
      //! the component's implementation
      const ImplementationPtr mImplementation;
      //! the component's structural uri
      mutable Trentino::Utils::URI mURI;
      //! a collection of the component's services
      ServiceBases mServices;
      //! a collection of the component's references
      ReferenceBases mReferences;
      //! a collection of the component's properties
      Properties mProperties;      
      //! the component's state
      State mState;
      //! mutex to be used for accessing the component in a consistent state
      mutable boost::recursive_mutex mRecursiveMutex;

   }; //class Component

   #include  "TrentinoRuntimeModelComponent.inl"

} //namespace RuntimeModel
} //namespace Trentino


#endif //TrentinoRuntimeModelComponentH

