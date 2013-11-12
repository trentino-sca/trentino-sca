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

#ifndef TrentinoUtilsDynamicLibraryH
#define TrentinoUtilsDynamicLibraryH

//standard
#include <string>
#include <stdexcept>
#include <set>

//specific
#include "../Global/TrentinoGlobal.h"

#ifdef WIN32
   #ifdef UTILS_EXPORTS
      #define DYNAMICLIBRARY_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define DYNAMICLIBRARY_IMPORT_EXPORT __declspec(dllimport)       
   #endif
#else
   #define DYNAMICLIBRARY_IMPORT_EXPORT 
#endif

namespace Trentino{
namespace Utils
{
   //**********************************************************************************************
   //                                     DynamicLibrary                               
   //**********************************************************************************************
   //! \ingroup Utils
   //! \brief Encapsulates platform specific functionality for handling dynamic and shared 
   //!        libraries and offers a platform independent interface to access this functionality. 
   //**********************************************************************************************
   class DYNAMICLIBRARY_IMPORT_EXPORT DynamicLibrary
   {
      //additional
   public:
      enum UnloadAction
      {
         //! The library will be unloaded only once. This will decrement the usage/reference 
         //! count of the library and unload it only if the usage/reference count drops to 0. 
         //! Consequently, if the usage/reference count is greater than 0 after the decrement,
         //! the library will not be unloaded from the current process.
         Once, 
         //! The library will be unloaded for sure independently of its usage/reference count.
         Complete
      };

      //construction
   public:
      //*******************************************************************************************
      //                                     DynamicLibrary()                               
      //*******************************************************************************************      
      //! \brief Constructs a DynamicLibrary object for the library with the given path.
      //! \param[in] filePath Path to a dynamic or shared library. 
      //! \note The constructor does not perform any actions to load the library.
      //! \note The search order and the default paths used to locate the library with the given
      //!       path are platform dependent.
      //! \sa filePath(), load()
      //*******************************************************************************************
      explicit DynamicLibrary(const std::string& filePath);

      //*******************************************************************************************
      //                                     ~DynamicLibrary()                               
      //*******************************************************************************************      
      //! \brief Empty destructor.
      //!
      //! \note The destructor does not perform any actions to unload the library.
      //*******************************************************************************************
      ~DynamicLibrary(void);
   private:
      //*******************************************************************************************
      //                                    const DynamicLibrary&()                               
      //*******************************************************************************************      
      //! \brief Disallow inadvertent copy construction. 
      //*******************************************************************************************
      DynamicLibrary(const DynamicLibrary&);

      //operators
   private:
      //*******************************************************************************************
      //                            operator=(const DynamicLibrary&)
      //*******************************************************************************************
      //! \brief Explicitly disallow assignment (because of const members).    
      //*******************************************************************************************
      void operator=(const DynamicLibrary&);

      //services
   public:
      //*******************************************************************************************
      //                                           load()
      //*******************************************************************************************
      //! \brief Loads the library.
      //!
      //! \throw std::runtime_error In case any error occures. 
      //! \sa unload(), isLoaded()
      //*******************************************************************************************
      void load();

      //*******************************************************************************************
      //                                           load()
      //*******************************************************************************************
      //! \brief Loads the library.
      //!
      //! param[in] a set of directories where dll dependencies can be found
      //! \throw std::runtime_error In case any error occures. 
      //! \sa unload(), isLoaded()
      //*******************************************************************************************
      void load(std::set<std::string> dllDirectoryList);
      //void attach();
      //*******************************************************************************************
      //                                           unload()
      //*******************************************************************************************
      //! \brief Unloads the library.
      //! \param[in] unloadAction Enumeration value specifying how the library should be unloaded.
      //!            See DynamicLibrary::UnloadAction for a description of the supported values.
      //!            The default value is DynamicLibrary::Once.
      //! \throw std::runtime_error In case any error occures. 
      //! \sa load(), isLoaded()
      //*******************************************************************************************
      void unload(UnloadAction unloadAction = Once);

      //*******************************************************************************************
      //                                           isLoaded()
      //*******************************************************************************************
      //! \brief Checks whether the library is currently loaded (i.e. 
      //!         mapped into the current process)       
      //!
      //! \return \c true if the library is loaded, otherwise \c false.
      //! \sa load(), undload()
      //*******************************************************************************************
      bool isLoaded() const;

      //*******************************************************************************************
      //                                           filePath()
      //*******************************************************************************************
      //! \brief Returns the the path to the library file.     
      //!
      //! \return Path to the library file.
      //! \sa DynamicLibrary()
      //*******************************************************************************************
      std::string filePath() const;

      //*******************************************************************************************
      //                                     functionAddress()
      //*******************************************************************************************
      //! \brief Returns a pointer to the function with the given name.   
      //!
      //! idea from: 
      //! http://wcqtff.willcodejoomlaforfood.de/stl-boost/dll-loader-loadlibrary-getprocaddress-freelibrary.html
      //! (23.03.11)
      //! 
      //! \tparam Func Function pointer type of the function to retrieve the pointer for.
      //! \param[in] funcName Name of the function to retrieve the pointer for.
      //! \return Pointer to the function from the library. 
      //! \throw runtime_error If any error occurs.
      //! \sa DynamicLibrary()
      //*******************************************************************************************
      template<typename Func>
      Func functionAddress(const std::string& funcName) const;

      //management
   private:
      //*******************************************************************************************
      //                                     functionAddress()
      //*******************************************************************************************
      //! \brief Internally used by functionAddress().
      //*******************************************************************************************
      void* getProcAddress(const std::string& funcName) const;

      //data
   private:
      //! Path to the library.
      const std::string mFilePath;
      //! Platform specific handle to the library.
      void* mLibHandle;

   }; //class DynamicLibrary

   #include "TrentinoUtilsDynamicLibrary.inl"

} //namespace Utils
} //namespace Trentino

#endif //TrentinoUtilsDynamicLibraryH
