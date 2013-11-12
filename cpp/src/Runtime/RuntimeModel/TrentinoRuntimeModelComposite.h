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

#ifndef TrentinoRuntimeModelCompositeH
#define TrentinoRuntimeModelCompositeH

//standard
#include <string>

//baseclass
#include "TrentinoRuntimeModelImplementation.h"

//specific
#include "TrentinoRuntimeModel.h"
#include "../SCAModel/TrentinoSCAModel.h"
#include "../XML/TrentinoXMLSchemaQName.h"

namespace Trentino{
namespace RuntimeModel
{
   //**********************************************************************************************
   //                                        Composite
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief Represents an SCA composite at runtime.
   //!
   //! The RuntimeModel::Composite class points to the corresponding SCA::Model::Composite class 
   //! and provides additional information associated with a composite. 
   //! Examples for such additional information are: 
   //! - the composite's QName
   //! - a pointer to the composite's parent RuntimeModel::Contribution
   //! - a pointer to the composite's parent RuntimeModel::Component (in case it is uses as some 
   //!   component's implementation)
   //! - a collection of the components contained in the composite
   //! - etc.
   //! \todo specify exceptions thrown by all the methods/constructors
   //**********************************************************************************************
   class RUNTIMEMODEL_IMPORT_EXPORT Composite : public Implementation
   {
      //additional
   public:      
      enum State { None //!< represents an invalid state
                 , Installed
                 , Deployed
                 , Running }; 

      //construction
   public:
      //*******************************************************************************************
      //                                     Composite()
      //*******************************************************************************************
      //! \brief Constructs a composite with the given parent contribution and associates it with 
      //!        the given SCA::Model::Composite.
      //! \param[in] scaComposite A shared pointer to the SCA::Model::Composite instance
      //!            the composite should be associated with.
      //! \param[in] contribution The composite's parent contribution.          
      //*******************************************************************************************
      Composite( const Trentino::SCA::Model::CompositePtr& scaComposite
               , const ContributionPtr& contribution);
      
   private:      
      //*******************************************************************************************
      //                              Composite(const Composite&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copy construction.      
      //*******************************************************************************************
      Composite(const Composite&);

      //operators
   private:
      //*******************************************************************************************
      //                                       operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.
      //*******************************************************************************************
      void operator=(const Composite&);

      //services
   public:      
      //*******************************************************************************************
      //                                    querySetterMethod()
      //*******************************************************************************************
      //override from Implementation (see documentation in Implementation)
      //! \copydoc RuntimeModel::Implementation::querySetterMethod()
      //! \return Always returns an empty shared pointer because a composite used as implementation
      //!         does not define any setter methods.
      //! \remark References defined on composite level (or synonymously: in a component using this 
      //!         composite as implementation) are finally always promoted to a component having a  
      //!         real implementation (i.e. a non-composite implementation). Once the promotion 
      //!         path is completely resolved the reflection object for the setter method can be 
      //!         retrieved from  this component's implementation.
      //!         An exemplary situation is illustrated in the following picture: There is no 
      //!         special setter method associated with the \c CompositeReference reference,  
      //!         instead the corresponding setter method is the one from \c MyReference and can be 
      //!         retrieved from \c Component2's implementation following the promotion path.
      //!         \image html CompositeReferenceSetterMethodExample.png
      //!         \sa RuntimeModel::Reference::promotedTo(),
      //!             RuntimeModel::CPPImplementation::querySetterMethod()
      //*******************************************************************************************
      virtual Trentino::Reflection::ReflectMethodPtr querySetterMethod(
         const ConstReferenceBasePtr& reference);

      //*******************************************************************************************
      //                                  queryPropertySetterMethod()
      //*******************************************************************************************
      //override from Implementation (see documentation in Implementation)
      //! \copydoc RuntimeModel::Implementation::queryPropertySetterMethod()
      //! \return Always returns an empty shared pointer because a composite used as implementation
      //!         does not define any setter methods.
      //*******************************************************************************************
      virtual Trentino::Reflection::ReflectMethodPtr queryPropertySetterMethod(
         const ConstPropertyPtr& property); 
      
      //*******************************************************************************************
      //                                     scaComposite()
      //*******************************************************************************************
      //! \brief Returns the SCA::Model::Composite associated with the composite.
      //! \return A shared pointer to SCA::Model::Composite instance the composite is associated
      //!         with.
      //! \sa Composite()      
      //*******************************************************************************************
      Trentino::SCA::Model::CompositePtr scaComposite() const;

      //*******************************************************************************************
      //                                         qName()
      //*******************************************************************************************
      //! \brief Convenience method for retrieving the composites's QName.
      //!
      //! It is allowed to have more than one RuntimeModel::Composite with the same QName since
      //! a RuntimeModel::Composite represents an instance of a physical composite that could be
      //! used more than once, for example as an implementation of several components.
      //! \return A const reference to the composite's QName.
      //*******************************************************************************************
      const Trentino::XML::Schema::QName& qName() const;

      //*******************************************************************************************
      //                                      contribution()
      //*******************************************************************************************
      //! \brief Returns the composite's parent contribution.
      //! \return A shared pointer to the composite's parent contribution.
      //! \sa Composite()
      //*******************************************************************************************
      ContributionWeakPtr contribution() const;
      
      //*******************************************************************************************
      //                                         components()
      //*******************************************************************************************
      //! \brief Returns a collection of the components contained in the composite.
      //! \return A const reference to the collection of components contained in the composite.
      //! \sa addComponent()
      //*******************************************************************************************
      const Components& components() const;

      //*******************************************************************************************
      //                                       addComponent()
      //*******************************************************************************************
      //! \brief Adds a component to the composite.
      //! \param[in] component A shared pointer to the component to add. 
      //! \sa components()
      //*******************************************************************************************
      void addComponent(const ComponentPtr& component);

      //*******************************************************************************************
      //                                     findComponentByName()
      //*******************************************************************************************
      //! \brief Finds a component by name.
      //! \param[in] name Name of the component to search for.
      //! \return A shared pointer to the found component or an empty shared pointer if no 
      //!         component with the given name could be found.
      //*******************************************************************************************
      ComponentPtr findComponentByName(const std::string& name) const;

      //*******************************************************************************************
      //                                           state()
      //*******************************************************************************************
      //! \brief Returns the composites's state.
      //! \return The composites's state.
      //! \sa setState()
      //*******************************************************************************************
      State state() const;

      //*******************************************************************************************
      //                                         setState()
      //*******************************************************************************************
      //! \brief Sets the composite's state.
      //! \param[in] state The state to set. 
      //! \sa state()
      //*******************************************************************************************
      void setState(State state);
      
      //*******************************************************************************************
      //                                       isDeployable()
      //*******************************************************************************************
      //! \brief Returns whether the composite is a deployable one or not. 
      //! \return \c true if the composite is deployable (i.e. not used as implementation), 
      //!         otherwise \c false.
      //! \sa setDeployable()
      //*******************************************************************************************
      bool isDeployable() const;

      //*******************************************************************************************
      //                                       setDeployable()
      //*******************************************************************************************
      //! \brief Sets whether the composite is a deployable one or not.
      //! \param[in] isDeployable A boolean value specifying whether the composite is deployable
      //!            or not.       
      //! \sa isDeployable()
      //*******************************************************************************************
      void setDeployable(bool isDeployable);

      //****************************************************************************************************
      //                                         visit()
      //****************************************************************************************************
      //! \brief visit this composite
      //! \param VisitorPtr & visitor
      //! \return void
      //****************************************************************************************************
      bool visit( VisitorPtr& visitor );
      //data
   private:      
      //! the SCA::Model::Composite associated with the composite
      const Trentino::SCA::Model::CompositePtr mSCAComposite;
      //! the composite's QName
      const Trentino::XML::Schema::QName mQName; 
      //! the composite's parent contribution
      const ContributionWeakPtr mContribution;      
      //! a collection of the composite's components
      Components mComponents;
      //! the composite's state
      State mState;
      //! boolean flag identifying whether the composite is deployable or not
      bool mIsDeployable;      

   }; //class Composite

   #include "TrentinoRuntimeModelComposite.inl"

} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelCompositeH