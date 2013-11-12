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

#ifndef TrentinoReflectionDataRegistryH
#define TrentinoReflectionDataRegistryH

//standard
#include <string>
#include <map>
#include <vector>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>

//specific
#include "./../../Global/TrentinoGlobal.h"
#include "TrentinoReflectionIncludes.h"


namespace Trentino{
namespace Reflection
{
   //class declaration
   //**********************************************************************************************
   //                             DataRegistry                             
   //**********************************************************************************************
   //! \ingroup ReflectionRuntime
   //! \brief Central data registry to store all \sa ReflectObject::MetaData information 
   //! of reflection objects.
   //! Supports query and registation functionality
   //**********************************************************************************************
   class REFLECTION_IMPORT_EXPORT DataRegistry
   {
      friend struct Registration;
      friend class ReflectObject;
      //additional
   private:
      //! Type definition for internal pair representation to store 
      //! reflection runtime data into a std::map
      typedef std::pair<std::string, const Data::Object::MetaData> ReflectionObjectPair;

      typedef std::pair<void*, std::string> InstanceReflectObjectPair;
      typedef std::map<void*, std::string> RegisteredInstances;
      typedef std::map<std::string, const Data::Object::MetaData> ReflectionObjects;

      //construction
   private:
      //*******************************************************************************************
      //                            DataRegistry()
      //*******************************************************************************************
      //! Copy constructor.
      //! \param[in] source DataRegistry source reference to copy from.
      //*******************************************************************************************
      DataRegistry(const DataRegistry& source);

      //operators
   private:
      //*******************************************************************************************
      //                            operator=()
      //*******************************************************************************************
      //! Assignment operator.
      //! \param[in] source DataRegistry source reference to copy from.
      //*******************************************************************************************
      void operator=(const DataRegistry& source);

   public:
      //*******************************************************************************************
      //                            DataRegistry()
      //*******************************************************************************************
      //! Default constructor.
      //*******************************************************************************************
      DataRegistry();
      
      //*******************************************************************************************
      //                            ~DataRegistry()
      //*******************************************************************************************
      //! Destructor.
      //*******************************************************************************************
      ~DataRegistry();
      //services
   public:

      //*******************************************************************************************
      //                            cleanUp()
      //*******************************************************************************************
      //! Clean up the registry. This method is called by the destructor
      //*******************************************************************************************
      void cleanUp();

      //*******************************************************************************************
      //                              queryReflectObject()
      //*******************************************************************************************
      //! \brief Queries a specified reflectobject by classname.
      //! Classname must be a fully qualified name with namespace if present.
      //! Returns a shared pointer with a \sa ReflectObject.
      //! Take care of calling method too much. Store \sa ReflectObjectPtr in your own structure
      //! if you use same object pointer again.
      //! \param[in] className name of relfectobject to query.
      //! \return shared ptr containing an existing reflect object or a null pointer if not found.
      //*******************************************************************************************
      ReflectObjectPtr queryReflectObject(const std::string& className) const;

      //*******************************************************************************************
      //                              reflectObjectCount()
      //*******************************************************************************************
      //! \brief Returns number of registered reflectobjects.
      //! \return number of reflect objects.
      //*******************************************************************************************
      int reflectObjectCount() const;


      //*******************************************************************************************
      //                              instance()
      //*******************************************************************************************
      //! \brief Returns a reflectobject by given instance pointer.
      //! \param[in] inst Instance to retrieve a specified reflectobject from.
      //! \return Returns a corresponding reflectobject.
      //*******************************************************************************************
       ReflectObjectPtr queryReflectObjectByInstance(void* inst) const;

       //management
   private:
      //*******************************************************************************************
      //                              registerInstance()
      //*******************************************************************************************
      //! \brief Registers all instances which can be searched globally by instance pointer.
      //! \param[in] inst Instances to register.
      //! \param[in] reflectObject ReflectObject which corresponds to instance.
      //*******************************************************************************************
      void registerInstance(void* inst, const ReflectObject& reflectObject);

      //*******************************************************************************************
      //                              unregisterInstance()
      //*******************************************************************************************
      //! \brief Unregisters a specified instance for a reflectobject.
      //! \param[in] inst Instance to unregister.
      //! \return Returns if unregistering was successfull.
      //*******************************************************************************************
      bool unregisterInstance(void* inst);

      //*******************************************************************************************
      //                              constructReflectObject()
      //*******************************************************************************************
      //! \brief constructs from \sa ReflectObject::MetaData a shared_ptr of ReflectObject type
      //! \param[in] metaData MetaData structure which constructs a corresponding shared_ptr of 
      //!                     ReflectObject
      //! \return shared_ptr of a \sa ReflectObject, null if structure isn´t valid.
      //*******************************************************************************************
      ReflectObjectPtr constructReflectObject
                                          (const Data::Object::MetaData& metaData) const;

      //! \todo implement iteration methods etc
      //*******************************************************************************************
      //                              registerReflectObject()
      //*******************************************************************************************
      //! \brief Registers a new ReflectObject by using \sa ReflectObject::MetaData POD structure.
      //! \param[in] MetaData structure to register a new object
      //*******************************************************************************************
      void registerReflectObject(const Data::Object::MetaData& data);

      //*******************************************************************************************
      //                              unregisterReflectObject()
      //*******************************************************************************************
      //! \brief Unregisters a new ReflectObject by using \sa ReflectObject::MetaData 
      //! POD structure.
      //! \param[in] MetaData structure to unregister a new object
      //*******************************************************************************************
      void unregisterReflectObject(const Data::Object::MetaData& data);

      //data
   private:
      //! Holds all registered instances of \sa ReflectObject in a map 
      ReflectionObjects mReflectionObjects;
      //! Holds all instances which should be registered/unregistered
      RegisteredInstances mRegisteredInstances;

      mutable boost::mutex mMetaDataChangesMutex;
      mutable boost::mutex mRegInstanceChangesMutex;
   }; //class DataRegistry

} //namespace Reflection
} //namespace Trentino


#endif //TrentinoReflectionDataRegistryH

