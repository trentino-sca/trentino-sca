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

#ifndef TrentinoDiscoverySlpUtilH
#define TrentinoDiscoverySlpUtilH

//standart
#include <string>
#include <boost/shared_ptr.hpp>

//specific
#include "../Runtime/SCAModel/TrentinoSCAModelMetadata.h"
#include "../Runtime/SCAModel/TrentinoSCAModelMetadataStringAttribute.h"
#include "../Runtime/Discovery/TrentinoDiscovery.h"

namespace Trentino{
namespace Discovery{
namespace SLP{
namespace OpenSLP
{

   //class declaration
   //**********************************************************************************************
   //                             DiscoverySlpUtil
   //**********************************************************************************************
   //! \ingroup DiscoverySLP
   //! \brief Class that provides parsing related utilities to be used by the DiscoverySLp class
   //! (i.e. metadata-> attribute list(string), attrlist->metadat)
   //**********************************************************************************************
   class DiscoverySlpUtil 
   {
      //additional
   private:
      typedef boost::shared_ptr<Trentino::SCA::Model::Metadata> MetadataSharedPtr;
      typedef boost::shared_ptr<Trentino::SCA::Model::MetadataStringAttribute> MetadataStringAttributePtr;

      //construction
   private:
	   DiscoverySlpUtil();
      
      // services
   public:
      //*******************************************************************************************
      //                                     attrList2MetadaMandatoryAttrsOnly()                               
      //*******************************************************************************************
      //! \brief Fills the attributes(param2) with the mandatory attributes hosted in attributesMap
      //!
      //! \param attributesMap attributes map (key is the attribute name)
      //! \param [out] attributes This param will be filled with the mandatory attributes of the 
      //! attributeMap. It is decided that mandatory attributes of a service should have a name
      //! starting with an underscore (i.e. _bindingScaURi)
      //*******************************************************************************************
      static void attrList2MetadaMandatoryAttrsOnly(std::multimap< std::string, 
         std::string>& attributesMap, 
         MetadataSharedPtr attributes);
      
      static void attrList2MetadaMandatoryAttrsOnly(std::multimap< std::string, 
         std::string>& attributesMap, 
         Trentino::SCA::Model::Metadata& attributes);

      //*******************************************************************************************
      //                                     attrList2Metada()                               
      //*******************************************************************************************
      //! \brief Fills the attributes(param2) according to the comma separated string representation
      //! (att1Name=att1VAlue,att2NAme=att2value) of attrlist
      //! \param attrlist comma separated name,value pairs of attributes
      //! \param [out] metadata Metadata structure to be filled
      //*******************************************************************************************
      static void attrList2Metada(std::string attrlist, MetadataSharedPtr metadata);

      static void attrList2Metada(std::string attrlist, Trentino::SCA::Model::Metadata& metadata);

      //*******************************************************************************************
      //                                     attrList2Metada()                               
      //*******************************************************************************************
      //! \brief Fills the attributesMultiMap(param2) according to the comma separated string representation
      //! (att1Name=att1VAlue,att2NAme=att2value) of attrlist
      //! \param attrlist comma separated name,value pairs of attributes
      //! \param [out] attributesMultiMap Multimap representation of the Metadata 
      //*******************************************************************************************
      static void attrList2Metada(std::string attrlist, 
         std::multimap< std::string, 
         std::string>& attributesMultiMap);

      //*******************************************************************************************
      //                                     metada2AttrList()                               
      //*******************************************************************************************
      //! \brief Provides comma separated names, value pairs of the attributes  given as param.
      //! i.e. att1Name=att1VAlue,att2NAme=att2value...
      //*******************************************************************************************
      static std::string metada2AttrList(ConstMetadataConstSharedPtr attributes);

      //*******************************************************************************************
      //                                     metada2AttrListNamesOnly()                               
      //*******************************************************************************************
      //! \brief Provides comma separated names of the attributes given as param.
      //!
      //*******************************************************************************************
      static std::string metada2AttrListNamesOnly(MetadataSharedPtr attributes);

      //management
   private:

      //data
   private:


   }; // class DiscoverySlpUtil


} // namespace OpenSLP
} //namespace SLP
} //namespace Discovery
} //namespace Trentino

#endif TrentinoDiscoverySlpUtilH



