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

#ifndef TrentinoRuntimeModelPropertyH
#define TrentinoRuntimeModelPropertyH

//specific
#include "TrentinoRuntimeModel.h"
#include "../SCAModel/TrentinoSCAModel.h"
#include "../SCAModel/TrentinoSCAModelProperty.h"
#include "../SCAModel/TrentinoSCAModelPropertyValue.h"
#include "../ReflectionRuntime/TrentinoReflectionReflectMethod.h"

namespace Trentino{
namespace RuntimeModel
{
   //**********************************************************************************************
   //                                        Property
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief Represents an SCA property at runtime.
   //!
   //! The RuntimeModel::Property class points to the corresponding SCA::Model::Property and 
   //! eventually also to the SCA::Model::PropertyValue class and provides additional information 
   //! associated with the property. 
   //! Examples for such additional information are: 
   //! - reflection code for the property's setter method
   //**********************************************************************************************
   class RUNTIMEMODEL_IMPORT_EXPORT Property 
   {
      //additional
   public:
      typedef std::string Value;
      typedef std::vector<Value> Values;
      //construction
   public:
      //*******************************************************************************************
      //                                     Property()
      //*******************************************************************************************
      //! \brief Constructs a property and associates it with the given SCA::Model::PropertyValue.
      //! \param[in] scaPropertyValue A shared pointer to the SCA::Model::PropertyValue instance
      //!            the property should be associated with.    
      //! \param[in] component A weak pointer to the component the property is attached to (i.e.
      //!            parent component).
      //! \sa scaPropertyType(), component()
      //*******************************************************************************************
      Property( const Trentino::SCA::Model::PropertyPtr& scaPropertyType
              , const Trentino::RuntimeModel::ComponentWeakPtr& component);
   private:
      //*******************************************************************************************
      //                              Property(const Property&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copy construction.      
      //*******************************************************************************************
      Property(const Property&);

      //operators
   private:      
      //*******************************************************************************************
      //                                       operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.
      //*******************************************************************************************
      void operator=(const Property&);

      //services
   public:  
      //*******************************************************************************************
      //                                    scaPropertyType()
      //*******************************************************************************************
      //! \brief Returns the SCA::Model::Property associated with the property.
      //! \return A shared pointer to SCA::Model::Property instance the property is associated
      //!         with.
      //! \sa Property()
      //*******************************************************************************************
      Trentino::SCA::Model::PropertyPtr scaPropertyType() const;    

      //*******************************************************************************************
      //                                    scaPropertyType()
      //*******************************************************************************************
      //! \brief Returns the property's parent component. 
      //! \return A weak pointer to the property's parent component.
      //! \sa Property()
      //*******************************************************************************************
      Trentino::RuntimeModel::ComponentWeakPtr component() const;

      //*******************************************************************************************
      //                                    scaProperty()
      //*******************************************************************************************
      //! \brief Returns the SCA::Model::PropertyValue associated with the property.
      //! \return A shared pointer to SCA::Model::PropertyValue instance the property is associated
      //!         with.
      //! \sa setSCAProperty()
      //*******************************************************************************************
      Trentino::SCA::Model::PropertyValuePtr scaProperty() const;

      //*******************************************************************************************
      //                                   setSCAProperty()
      //*******************************************************************************************
      //! \brief Sets the SCA::Model::PropertyValue to be associated with the property. 
      //! \param[in] A Shared pointer to the SCA::Model::PropertyValue instance that should be 
      //!            associated with the property. 
      //*******************************************************************************************
      void setSCAProperty(const Trentino::SCA::Model::PropertyValuePtr& scaProperty);

      //*******************************************************************************************
      //                                       setSetterMethod()
      //*******************************************************************************************
      //! \brief Returns the property's setter method. 
      //! \return Shared pointer to the object to access the reflection code for the property's
      //!         setter method.   
      //! \sa setSetterMethod()
      //*******************************************************************************************
      Trentino::Reflection::ReflectMethodPtr setterMethod() const;
      
      //*******************************************************************************************
      //                                       setSetterMethod()
      //*******************************************************************************************
      //! \brief Sets the property's setter method. 
      //! \param[in] setter Shared pointer to the object to access the reflection code for the
      //!            property's setter method.   
      //! \sa setterMethod()
      //*******************************************************************************************
      void setSetterMethod(const Trentino::Reflection::ReflectMethodPtr& setter);

      //*******************************************************************************************
      //                                       values()
      //*******************************************************************************************
      //! \brief  Returns the property's values.       
      //! \return A collection of the property's values. 
      //! \sa addValue()
      //*******************************************************************************************
      const Values& values() const;   

      //*******************************************************************************************
      //                                       setValues()
      //*******************************************************************************************
      //! \brief Sets the property's values.       
      //!
      //! Values already set for the property are replaced. 
      //! \param[in] values A collection of values to set. For \c @many="false" properties only the 
      //!            first element in \c values is assigned as property value.
      //! \sa values(), addValue() 
      //*******************************************************************************************
      const void setValues(const Values& values);

      //*******************************************************************************************
      //                                       addValue()
      //*******************************************************************************************
      //! \brief  Adds a value for the property.    
      //!
      //! For \c @many="false" properties, every call to addValue() replaces the property values
      //! assigned through previous calls to addValue(). 
      //! \param[in] value The value to be added.
      //! \sa values(), setValues()
      //*******************************************************************************************
      void addValue(const Value& value);   

      //! \name convenience methods 
      //! @{
      //*******************************************************************************************
      //                                         name()
      //*******************************************************************************************
      //! \brief Convenience method to access SCA::Model property name.
      //! \return scaPropertyType()->name()
      //*******************************************************************************************
      const Trentino::XML::Schema::NCName& name() const;

      //*******************************************************************************************
      //                                         isMany()
      //*******************************************************************************************
      //! \brief Returns whether the value of the @many attribute.
      //! \return \c true if \c @many="true", \c false otherwise.
      //*******************************************************************************************
      bool isMany() const;

      //*******************************************************************************************
      //                                         type()
      //*******************************************************************************************
      //! \brief Return the XSD type of the property without a namespace prefix.
      //! \return The property's XSD type without a prefix. 
      //*******************************************************************************************
      std::string type() const;
      //! @}

      //data
   private:      
      //! the SCA::Model::Property associated with the property
      const Trentino::SCA::Model::PropertyPtr mSCAPropertyType;
      //! the property's parent component.
      const Trentino::RuntimeModel::ComponentWeakPtr mComponent;
      //! the SCA::Model::PropertyValue associated with the property
      Trentino::SCA::Model::PropertyValuePtr mSCAProperty;
      //! object to access the reflection code for the property's setter method      
      Trentino::Reflection::ReflectMethodPtr mSetter; 
      //! collection of the property's values
      Values mValues;

   }; //class Property   

   #include "TrentinoRuntimeModelProperty.inl"

   } //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelPropertyH