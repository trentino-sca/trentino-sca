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

#ifndef TrentinoUtilsStaticMapH
#define TrentinoUtilsStaticMapH

#ifdef WIN32
#ifdef UTILS_EXPORTS
#define STATICMAP_IMPORT_EXPORT __declspec(dllexport)
#else
#define STATICMAP_IMPORT_EXPORT __declspec(dllimport)       
#endif //UTILS_EXPORTS
#else
#define STATICMAP_IMPORT_EXPORT
#endif //WIN32


//standard
#include <string>
#include <map>

//specific
#include "../Global/TrentinoGlobal.h"

namespace Trentino{
namespace Utils
{

   //class declaration
   //**********************************************************************************************
   //                             StaticMap
   //**********************************************************************************************
   //! \brief The StaticMap maps dependencies between 32bit hashvalues and pointer.
   //! \sa StaticClass uses this map to retrieve information if objects are still created
   //! with corresponding hashvalues. 
   //**********************************************************************************************
   class StaticMap
   {
      //additional
   public:
   //**********************************************************************************************
   //                             Value
   //**********************************************************************************************
   //! \brief Used by HashMapPair to store a valid pointer and a refcounter.
   //! to track referencecounting, how much StaticClass owns this type of object.
   //**********************************************************************************************
      struct Value
      {
         //! Valid pointer bound with \sa StaticClass.
         void* mPtr;
         //! Reference counter how much \sa StaticClass instances are bound to this \sa mPtr.
         unsigned long mRefCount;
         Value() : mPtr(nullptr), mRefCount(1) {}
      };
      //! HashMapPair to store \value in std::map.
      typedef std::pair<unsigned long, Value> HashMapPair;

      //service
   public:
      //*******************************************************************************************
      //                                     retainNamedMemory()                               
      //*******************************************************************************************
      //! Determines if a hashindex is still stored in internal map and returns a valid pointer
      //! if found. Increments internal refcounter, of corresponding structure.
      //! \param[in] HashIndex to retain.
      //! \return Returns a pointer if hashIndex points to a valid object.
      //! \retval a valid pointer if hashIndex still exists.
      //! \retval nullptr is no reference is found.
      //*******************************************************************************************
      STATICMAP_IMPORT_EXPORT static void* TRENTINO_STDCALL retainNamedMemory(unsigned long hashIndex);

      //*******************************************************************************************
      //                                     releaseNamedMemory()                               
      //*******************************************************************************************
      //! Releases a reference if a hashindex is still found in internal map and returns
      //! a valid pointer if structures internal refcount is 0, so \sa StaticClass can destroy 
      //! the object.
      //! \param[in] HashIndex to release.
      //! \return Returns a pointer if internal refcount (last StaticClass) 
      //! calls releaseNamedMemory by destructor.
      //! \retval a valid pointer if internal refcounter is 0 after calling releaseNamedMemory.
      //! \retval nullptr if internal recounter is still greater 0.
      //*******************************************************************************************
      STATICMAP_IMPORT_EXPORT static void* TRENTINO_STDCALL releaseNamedMemory(unsigned long hashIndex);

      //*******************************************************************************************
      //                                     registerNamedMemory()                               
      //*******************************************************************************************
      //! Registers a pointer by using a corresponding hashindex.
      //! Internal refcounter has value of one after registration.
      //! \param[in] HashIndex to register.
      //! \param[in] Class pointer to register.
      //*******************************************************************************************
      STATICMAP_IMPORT_EXPORT static void TRENTINO_STDCALL
         registerNamedMemory(unsigned long hashIndex, void* classPtr);

      //*******************************************************************************************
      //                                     refCount()                               
      //*******************************************************************************************
      //! Returns reference counter of structure, corresponding with given hashindex.
      //! Could be used for debugging purposes for example.
      //! \param[in] HashIndex to ask.
      //! \return Returns reference counter of associated structure.
      //*******************************************************************************************
      STATICMAP_IMPORT_EXPORT static unsigned long TRENTINO_STDCALL 
         refCount(unsigned long hashIndex);

      //*******************************************************************************************
      //                                isNamedMemoryRegistered()                               
      //*******************************************************************************************
      //! Determines if a structure is found by given hashindex.
      //! \param[in] HashIndex to ask.
      //! \return Determines if a hashindex exists in map.
      //! \retval true if hashIndex still exists
      //! \retval false if hashIndex doesn´t exists
      //*******************************************************************************************
      STATICMAP_IMPORT_EXPORT static bool TRENTINO_STDCALL 
         isNamedMemoryRegistered(unsigned long hashIndex);
      //data
   private:
   }; //class StaticMap

} //namespace Utils
} //namespace Trentino


#endif //TrentinoUtilsStaticMapH