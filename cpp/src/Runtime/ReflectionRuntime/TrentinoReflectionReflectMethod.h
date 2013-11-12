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

#ifndef TrentinoReflectionReflectMethodH
#define TrentinoReflectionReflectMethodH

//standard
#include <boost/smart_ptr/scoped_array.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <vector>

//specific
#include "./../../Global/TrentinoGlobal.h"
#include "TrentinoReflectionIncludes.h"

namespace Trentino{
namespace Reflection
{
   //class declaration
   //**********************************************************************************************
   //                             ReflectMethod
   //**********************************************************************************************
   //! \ingroup ReflectionRuntime
   //! \brief Class is used for method invocation. Class contains all relevant
   //! information to call and to query information about methodname and
   //! its parameters.
   //**********************************************************************************************
   class ReflectMethod
   {
   friend class ReflectObject;
   
      //construction
   private:
      //*******************************************************************************************
      //                            ReflectMethod()
      //*******************************************************************************************
      //! \brief Parameter constructor to inject MetaData information.
      //! This method is only called by a \sa ReflectObject.
      //! \param[in] \sa MetaData structure which is injected in this new instance 
      //! of ReflectMethod.
      //*******************************************************************************************
      ReflectMethod(const Data::Method::MetaData* data);

      //*******************************************************************************************
      //                            ReflectMethod()
      //*******************************************************************************************
      //! Copy constructor.
      //! \param[in] ReflectMethod source reference to copy from.
      //*******************************************************************************************
      ReflectMethod(const ReflectMethod& source);

      //*******************************************************************************************
      //                            ReflectMethod()
      //*******************************************************************************************
      //! Default constructor.
      //*******************************************************************************************
      ReflectMethod();

      //operators
   private:
      //*******************************************************************************************
      //                            operator=()
      //*******************************************************************************************
      //! Assignment operator.
      //! \param[in] ReflectMethod source reference to copy from.
      //*******************************************************************************************
      void operator=(const ReflectMethod& source);

      //services
   public:
      //*******************************************************************************************
      //                            name()
      //*******************************************************************************************
      //! Property which returns name of method.
      //! \return name of method.
      //*******************************************************************************************
      REFLECTION_IMPORT_EXPORT const char* name() const;

      //*******************************************************************************************
      //                           returnType()
      //*******************************************************************************************
      //! \brief Property which returns returntype of method.
      //! Returntype name must be supported by \sa TypeName template.
      //! \return RTTI name of method.
      //*******************************************************************************************
      REFLECTION_IMPORT_EXPORT const char* returnType( ) const;

      //*******************************************************************************************
      //                          paramsCount()
      //*******************************************************************************************
      //! Number of parameters in method.
      //! \return Count of parameters.
      //*******************************************************************************************
      REFLECTION_IMPORT_EXPORT int paramsCount() const;

      //*******************************************************************************************
      //                          paramsAt()
      //*******************************************************************************************
      //! \brief Returns a parameter at specified index position.
      //! To determine number of parameters call \sa paramsCount.
      //! \return Parameter at specified index position.
      //! \retval nullptr if invalid index.
      //*******************************************************************************************
      REFLECTION_IMPORT_EXPORT const Data::Method::Param* paramsAt(int index) const;

      //*******************************************************************************************
      //                          Invoke()
      //*******************************************************************************************
      //! \brief Calls method with corresponding parameterlist and a valid 
      //! 'this' pointer.
      //! To get number of parameters and parameter types, \sa paramsCount and
      //! \sa paramsAt can be used.
      //! \param[in] 'this' pointer of object, which should be called.
      //! \param[in] Parameterlist committed by Invoke() method
      //! \return If method has a return value it will be returned by a 
      //! \sa non invalid type Variant.
      //*******************************************************************************************
      REFLECTION_IMPORT_EXPORT Helpers::Variant invoke(void* thisPtr, void* params[]) const;

      //*******************************************************************************************
      //                          Invoke()
      //*******************************************************************************************
      //! \brief Calls method with corresponding parameterlist and a valid 
      //! 'this' pointer.
      //! To get number of parameters and parameter types, \sa paramsCount and
      //! \sa paramsAt can be used.
      //! Instead of parsing a list of void pointers you can here use a list
      //! of variants which must contain the appropriate values.
      //! \param[in] 'this' pointer of object, which should be called.
      //! \param[in] Parameterlist committed by Invoke() method
      //! \return If method has a return value it will be returned by a 
      //! \sa Variant.
      //*******************************************************************************************
      REFLECTION_IMPORT_EXPORT Helpers::Variant invoke(
         void* thisPtr, const std::vector<Helpers::Variant>& params) const;

      //management
   private:
      //*******************************************************************************************
      //                          constructReflectMethod()
      //*******************************************************************************************
      //! \brief constructs from \sa ReflectMethod::MetaData a shared_ptr of ReflectMethod type.
      //! \param[in] MetaData structure which constructs a corresponding 
      //!  ReflectMethod shared_ptr.
      //! \return shared_ptr of a \sa ReflectMethod.
      //! \retval null if structure isn´t valid.
      //*******************************************************************************************
      static boost::shared_ptr<ReflectMethod> constructReflectMethod
                                                (const Data::Method::MetaData& metaData);

      //*******************************************************************************************
      //                          copyFrom()
      //*******************************************************************************************
      //! Copies content from a source \sa ReflectMethod into this one.
      //! \param[in] \sa ReflectMethod to copy from.
      //*******************************************************************************************
      void copyFrom(const ReflectMethod& source);

      //data
   private:
      //! Internal data PODS representation of method.
      const Data::Method::MetaData* mData;

   }; //class ReflectMethod

} //namespace Reflection
} //namespace Trentino


#endif // TrentinoReflectionReflectMethodH