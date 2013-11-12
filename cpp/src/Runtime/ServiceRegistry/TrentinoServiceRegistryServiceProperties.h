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
#ifndef TrentinoServiceRegistryServicePropertiesH
#define  TrentinoServiceRegistryServicePropertiesH

//standard
#include <string>
#include <map>

namespace Trentino{
namespace ServiceRegistry{
   //class declaration

   //****************************************************************************************************
   //                                         ServiceProperties
   //****************************************************************************************************
   //! \ingroup ServiceRegistry
   //! \brief Content service properties, used during service query
   //! it is backed by a map
   //****************************************************************************************************
      class ServiceProperties{
      public:
         //services

         //****************************************************************************************************
         //                                         put()
         //****************************************************************************************************
         //! \brief but a property with the given key in the Map
         //! \param const std::string key
         //! \param std::string value
         //! \return void
         //****************************************************************************************************
         void put(const std::string& key, const std::string& value );


         //****************************************************************************************************
         //                                         get()
         //****************************************************************************************************
         //! \brief get the property with the given key
         //! \param const std::string & key
         //! \return std::string
         //****************************************************************************************************
         std::string get (const std::string& key) const;


         //****************************************************************************************************
         //                                         size()
         //****************************************************************************************************
         //! \brief return the number of properties
         //! \return int
         //****************************************************************************************************
         int size() const;


         //****************************************************************************************************
         //                                         properties()
         //****************************************************************************************************
         //! \brief return an iterator starting at the beginning of the Properties map
         //! \return const std::map<std::string,std::string>&
         //****************************************************************************************************
         const std::map<std::string,std::string>& properties() const;

      private:
         std::map<std::string, std::string> mProperties;

      }; //class ServiceProperties

     #include "TrentinoServiceRegistryServiceProperties.inl"

} //namespace ServiceRegistry
} //namespace Trentino

#endif //TrentinoServiceRegistryServicePropertiesH

