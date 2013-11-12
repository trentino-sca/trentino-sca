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

#ifndef TrentinoReflectionReflectObjectH
#define TrentinoReflectionReflectObjectH

//standard
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
   //                             ReflectObject
   //**********************************************************************************************
   //! \ingroup ReflectionRuntime
   //! \brief Class is used for object reflection. This kind of class contains all relevant
   //! informations to query information like methods, properties, name of class and superclass
   //**********************************************************************************************
   class REFLECTION_IMPORT_EXPORT ReflectObject
   {
   friend class DataRegistry;
      //construction
   private:
      //*******************************************************************************************
      //                            ReflectObject()
      //*******************************************************************************************
      //! \brief Parameter constructor to inject MetaData information.
      //! This method is only called by a \sa DataRegistry.
      //! \param[in] \sa MetaData structure which is injected in this new instance 
      //! of ReflectObject.
      //*******************************************************************************************
      ReflectObject(const Data::Object::MetaData data);

      //operators
   private:
      //*******************************************************************************************
      //                            operator=()
      //*******************************************************************************************
      //! Assignment operator.
      //! \param[in] ReflectObject source reference to copy from.
      //*******************************************************************************************
      void operator=(const ReflectObject& source);

      //services
   public:
      //*******************************************************************************************
      //                            className()
      //*******************************************************************************************
      //! Property which returns class name of object.
      //! \return Name of reflected class.
      //*******************************************************************************************
      const char* className() const;

      //*******************************************************************************************
      //                         newInstance()
      //*******************************************************************************************
      //! \brief creates a new instance of this class type.
      //! This is a convenience method. In most of cases you will create a new object without any
      //! new parameters. So you save an extra query of a 'new' function by using
      //! \sa queryMethod function.
      //! \param[in] Determines if new instance should be registered by central registry.
      //! \return New Instance of specified class.
      //*******************************************************************************************
      void* newInstance(Trentino::Reflection::DataRegistry& registry,
         bool registerInstance = false) const;

      //*******************************************************************************************
      //                         newInstance()
      //*******************************************************************************************
      //! \brief creates a new instance of this class type with specified parameters.
      //! This is a convenience method. In most of cases you will create a new object 
      //! So you save an extra query of a 'new' function by using
      //! \sa queryMethod function.
      //! \param[in] Parameter types of new method.
      //! \param[in] Pointer to parameter values.
      //! \param[in] Determines if new instance should be registered by central registry.
      //! \return New Instance of specified class.
      //*******************************************************************************************
      void* newInstance(Trentino::Reflection::DataRegistry& registry,
                        const std::vector<std::string>& parameterTypes,
                        void* params[],
                        bool registerInstance = false) const;

      //*******************************************************************************************
      //                         newInstance()
      //*******************************************************************************************
      //! \brief creates a new instance of this class type with specified parameters.
      //! This is a convenience method. In most of cases you will create a new object 
      //! So you save an extra query of a 'new' function by using
      //! \sa queryMethod function.
      //! \param[in] Parameter types of new method.
      //! \param[in] List of values stored in variants.
      //! \param[in] Determines if new instance should be registered by central registry.
      //! \return New Instance of specified class.
      //*******************************************************************************************
      void* newInstance(Trentino::Reflection::DataRegistry& registry,
                        const std::vector<std::string>& parameterTypes,
                        const std::vector<Helpers::Variant>& params,
                        bool registerInstance = false) const;

      //*******************************************************************************************
      //                         deleteInstance()
      //*******************************************************************************************
      //! \brief deleted an existing instance of this class type.
      //! This is a convenience method.  
      //! \param[in] Determines if existing instance should be unregistered in central registry.
      //! \param[in] Determines if existing instance should be unregistered in instance registry.
      //! So you save an extra query of a 'delete' function by using \sa queryMethod function.
      //*******************************************************************************************
      void deleteInstance(Trentino::Reflection::DataRegistry& registry,
         void* object, bool unregisterInstance = false) const;

      //*******************************************************************************************
      //                         deleteRegisteredInstance()
      //*******************************************************************************************
      //! \brief deleted an existing but registered instance of this class type.
      //! This is a convenience method without any knowledge about associated reflectobject.  
      //! \param[in] Determines if existing instance should be unregistered in central registry.
      //! \return Returns true if successfull and false if not.
      //! So you save an extra query of a 'delete' function by using \sa queryMethod function.
      //*******************************************************************************************
      static bool deleteRegisteredInstance(Trentino::Reflection::DataRegistry& registry,
         void* object);

      //*******************************************************************************************
      //                        methodCount()
      //*******************************************************************************************
      //! Returns number of methods registered in this reflected class
      //! \return Number of methods.
      //*******************************************************************************************
      int methodCount() const;

      const Data::Object::MetaData& data() const;

      //*******************************************************************************************
      //                        castCall()
      //*******************************************************************************************
      //! Casts a specified class into another one if neccessary, e.g. mulitple inheritance.
      //! This is the templized version
      //! \return Casted pointer.
      //*******************************************************************************************
      template<typename TYPE>
      TYPE* castCall(void* ptr) const;

      //*******************************************************************************************
      //                        castCall()
      //*******************************************************************************************
      //! Casts a specified class into another one if neccessary, e.g. mulitple inheritance.
      //! \return Casted pointer.
      //*******************************************************************************************
      void* castCall(void* ptr, const std::string& castInto) const;

      //*******************************************************************************************
      //                        castCallRegistered()
      //*******************************************************************************************
      //! Casts a specified class into another one if neccessary, e.g. mulitple inheritance.
      //! \return Casted pointer.
      //*******************************************************************************************
      static void* castCallRegistered(Trentino::Reflection::DataRegistry& registry,
         void* ptr, const std::string& castInto);

      //*******************************************************************************************
      //                        methodAt()
      //*******************************************************************************************
      //! \brief Returns a method at specified index position.
      //! To determine number of methods call \sa methodCount.
      //! \return Method at specified index position.
      //! \reval nullptr if invalid index.
      //! Note: This is a ReflectMethod shared_ptr.
      //! Take care of calling method too much. Store \sa ReflectMethodPtr in your own structure
      //! if you use same method pointer again.
      //*******************************************************************************************
      ReflectMethodPtr methodAt(int index) const;

      //*******************************************************************************************
      //                        queryMethods()
      //*******************************************************************************************
      //! \brief Returns a vector as parameter of all found methods with corresponding methodname.
      //! Resultlist is empty if no appropriate method is found.
      //! You can get a vector which size is > 1 if methodname is equal but 
      //! signature differs.
      //! Take care of calling method too much. Store ReflectMethodPtrs in your own structure
      //! if you use same method pointers again.
      //! \param[in] Methodname to query.
      //! \param[out] resultlist which is filled with appropriate \sa ReflectMethod shared pointer.
      //! \return Status if corresponding name is found.
      //! \retval true if at least one method is found
      //! \retval false if no  method is found
      //*******************************************************************************************
      bool queryMethods(const std::string& methodName, 
                        std::vector<ReflectMethodPtr>& resultList) const;

      //*******************************************************************************************
      //                        queryMethod()
      //*******************************************************************************************
      //! Returns a shared_ptr of \sa ReflectMethod if method with 
      //! appropriate signature is found.
      //! Take care of calling method too much. Store \sa ReflectMethodPtr in your own structure
      //! if you use same method pointer again.
      //! \param[in] Methodname to query.
      //! \param[in] Vector of typename which defines the parameter type of method. All types
      //! defined in \sa TypeName are supported.
      //! \return Valid \sa ReflectMethod shared_ptr if invocable method with appropriate 
      //! signature is found. 
      //! \reval nullptr in shared_ptr if no method is found.
      //*******************************************************************************************
      ReflectMethodPtr queryMethod( const std::string& methodName, 
                                    const std::vector<std::string>& parameterTypes) const;
      //management
   private:
      //*******************************************************************************************
      //                          copyFrom()
      //*******************************************************************************************
      //! Copies content from a source \sa ReflectObject into this one.
      //! \param[in] ReflectObject to copy from.
      //********************************************************************************************
      void copyFrom(const ReflectObject& source);


      //data
   private:
      //! Internal data PODS representation of ReflectObject.
       Data::Object::MetaData mData;
   }; //class ReflectObject


   template<typename TYPE>
   static TYPE* castCall(void* ptr);


   #include "TrentinoReflectionReflectObject.inl"

} //namespace Reflection
} //namespace Trentino


#endif //TrentinoReflectionReflectObjectH
