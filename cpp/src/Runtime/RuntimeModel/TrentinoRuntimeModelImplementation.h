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

#ifndef TrentinoRuntimeModelImplementationH
#define TrentinoRuntimeModelImplementationH

//specific
#include "TrentinoRuntimeModel.h"
#include "../Invocation/TrentinoInvocation.h"
#include "../ReflectionRuntime/TrentinoReflectionIncludes.h"

namespace Trentino{
namespace RuntimeModel
{
   //**********************************************************************************************
   //                                    Implementation
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief Base class for the different implementations of a component. 
   //**********************************************************************************************
   class Implementation
   {
      //construction
   public: 
      virtual ~Implementation(){}

      //services
   public:
      //*******************************************************************************************
      //                                     Implemenation()
      //*******************************************************************************************
      //! \brief Sets the implementation's parent component.      
      //! \param[in] A shared pointer to the implementation's parent component.   
      //*******************************************************************************************
      void setComponent(const ComponentPtr& component);

      //*******************************************************************************************
      //                                       component()
      //*******************************************************************************************
      //! \brief Returns the implementation's parent component.
      //! \return A weak pointer to the implementation's parent component.
      //! \sa Implemenation()
      //*******************************************************************************************
      ComponentWeakPtr component() const;

      //*******************************************************************************************
      //                                    querySetterMethod()
      //*******************************************************************************************
      //! \brief Returns the reflection object for the setter method for the given reference.
      //!
      //! This methods should be implemented by each concrete (=derived) implementation because a 
      //! setter method is implementation specific.
      //! \return A shared pointer to the reflection object for the setter method.  
      //*******************************************************************************************
      virtual Trentino::Reflection::ReflectMethodPtr
         querySetterMethod(const ConstReferenceBasePtr& reference) = 0;

      //*******************************************************************************************
      //                                 queryPropertySetterMethod()
      //*******************************************************************************************
      //! \brief Returns the reflection object for the setter method for the given property.
      //!
      //! This methods should be implemented by each concrete (=derived) implementation because a 
      //! setter method is implementation specific.
      //! \return A shared pointer to the reflection object for the setter method.  
      //*******************************************************************************************
      virtual Trentino::Reflection::ReflectMethodPtr
         queryPropertySetterMethod(const ConstPropertyPtr& property) = 0;

      //data
   private:
      //! the implementation's parent component
      ComponentWeakPtr mComponent;

   }; //class Implementation

   //services
   inline void Implementation::setComponent(const ComponentPtr& component)
   {
      mComponent = component;
   }

   inline ComponentWeakPtr Implementation::component() const
   {
      return mComponent;
   }

} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelImplementationH