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

//header
#include "TrentinoDiscoverySlpUtil.h"

//standart
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/algorithm/string.hpp>


//specific
#include "../Global/TrentinoGlobal.h"

using namespace std;
using namespace Trentino::Discovery::SLP::OpenSLP;
using namespace Trentino::SCA::Model;

void DiscoverySlpUtil::attrList2MetadaMandatoryAttrsOnly(std::multimap< std::string, std::string>& attributesMap, MetadataSharedPtr attributes)
{
   std::multimap<string, string>::iterator it;
   for(it = attributesMap.begin(); it != attributesMap.end(); ++it)
   {
      unsigned found=it->first.find('_');
      if (found!=0)
      {
         continue;
      }
      MetadataStringAttribute* stringAttribute =  new MetadataStringAttribute();

      stringAttribute->setName(it->first.c_str());
      stringAttribute->setValue(it->second.c_str());
      attributes->addStringAttributesElement(stringAttribute);
   }

   /* foreach(attributesMap.begin(), attributesMap.end(),  isMandatory)
   vector<string> attributes;
   boost::split( attributes, attrlist, boost::is_any_of( "," ) );
   for(unsigned i = 0; i < attributes.size(); i++)
   {
      vector<string> attribute;
      boost::split( attribute, attribute[i], boost::is_any_of( "=" ) );

      MetadataStringAttribute* stringAttribute =  new MetadataStringAttribute();
      if(attribute.size()!=2)
      {
         continue;
      }

      unsigned found=attribute[0].find('_');
      if (found!=0)
      {
         continue;
      }
      
      stringAttribute->setName(attribute[0].c_str());
      stringAttribute->setValue(attribute[1].c_str());
      metadata->addStringAttributesElement(stringAttribute);
   }*/
}

void DiscoverySlpUtil::attrList2MetadaMandatoryAttrsOnly(std::multimap< std::string, std::string>& attributesMap,
   Trentino::SCA::Model::Metadata& attributes)
{
   std::multimap<string, string>::iterator it;
   for(it = attributesMap.begin(); it != attributesMap.end(); ++it)
   {
      unsigned found=it->first.find('_');
      if (found!=0)
      {
         continue;
      }
      MetadataStringAttribute* stringAttribute =  new MetadataStringAttribute();

      stringAttribute->setName(it->first.c_str());
      stringAttribute->setValue(it->second.c_str());
      attributes.addStringAttributesElement(stringAttribute);
   }


}
void DiscoverySlpUtil::attrList2Metada(string attrlist, MetadataSharedPtr metadata)
{
   vector<string> attributes;
   boost::split( attributes, attrlist, boost::is_any_of( "," ) );
   for(unsigned i = 0; i < attributes.size(); i++)
   {
      vector<string> attribute;

      boost::split( attribute, attributes[i], boost::is_any_of( "=" ) );


      MetadataStringAttribute* stringAttribute =  new MetadataStringAttribute();
      if(attribute.size()!=2)
      {
         continue;
      }
      
      std::string::iterator end_pos = std::remove(attribute[0].begin(), attribute[0].end(), '(');
      attribute[0].erase(end_pos, attribute[0].end());
      end_pos = std::remove(attribute[1].begin(), attribute[1].end(), ')');
      attribute[1].erase(end_pos, attribute[1].end());

      stringAttribute->setName(attribute[0].c_str());
      stringAttribute->setValue(attribute[1].c_str());
      metadata->addStringAttributesElement(stringAttribute);
   }
}

void DiscoverySlpUtil::attrList2Metada(string attrlist, Trentino::SCA::Model::Metadata& metadata)
{
   vector<string> attributes;
   boost::split( attributes, attrlist, boost::is_any_of( "," ) );
   for(unsigned i = 0; i < attributes.size(); i++)
   {
      vector<string> attribute;

      boost::split( attribute, attributes[i], boost::is_any_of( "=" ) );


      MetadataStringAttribute* stringAttribute =  new MetadataStringAttribute();
      if(attribute.size()!=2)
      {
         continue;
      }

      std::string::iterator end_pos = std::remove(attribute[0].begin(), attribute[0].end(), '(');
      attribute[0].erase(end_pos, attribute[0].end());
      end_pos = std::remove(attribute[1].begin(), attribute[1].end(), ')');
      attribute[1].erase(end_pos, attribute[1].end());

      stringAttribute->setName(attribute[0].c_str());
      stringAttribute->setValue(attribute[1].c_str());
      metadata.addStringAttributesElement(stringAttribute);
   }
}

void DiscoverySlpUtil::attrList2Metada(string attrlist, std::multimap< string, string>& attributesMultiMap)
{
   vector<string> attributes;
   boost::split( attributes, attrlist, boost::is_any_of( "," ) );
   for(unsigned i = 0; i < attributes.size(); i++)
   {
      vector<string> attribute;

      boost::split( attribute, attributes[i], boost::is_any_of( "=" ) );

      if(attribute.size()!=2)
      {
         continue;
      }
   
      std::string::iterator end_pos = std::remove(attribute[0].begin(), attribute[0].end(), '(');
      attribute[0].erase(end_pos, attribute[0].end());
      end_pos = std::remove(attribute[1].begin(), attribute[1].end(), ')');
      attribute[1].erase(end_pos, attribute[1].end());
      attributesMultiMap.insert(std::pair<string, string>(attribute[0].c_str(), attribute[1].c_str() ));

   }
}

string DiscoverySlpUtil::metada2AttrList(Trentino::Discovery::ConstMetadataConstSharedPtr attributes)
{
   string retVal;
   const std::vector<MetadataStringAttributePtr> metaDataStringAttributes = attributes->stringAttributesElements();
   int sizeOfMetaDataStringattributes = metaDataStringAttributes.size();
   for(int i = 0; i < sizeOfMetaDataStringattributes; i++)
   {
      if(i!=0)
      {
         retVal += "),(";
      }
      else
      {
         retVal = "(";
      }
      retVal += metaDataStringAttributes[i]->name() +"=" + metaDataStringAttributes[i]->value();
   }
   if(retVal.empty() != true)
   {
      retVal += ")";
   }
   
   return retVal;
}

string DiscoverySlpUtil::metada2AttrListNamesOnly(MetadataSharedPtr attributes)
{
   string retVal;
   const std::vector<MetadataStringAttributePtr> metaDataStringAttributes = attributes->stringAttributesElements();
   int sizeOfMetaDataStringattributes = metaDataStringAttributes.size();
   for(int i = 0; i < sizeOfMetaDataStringattributes; i++)
   {
      if(i!=0)
      {
         retVal += ",";
      }
      
      retVal += metaDataStringAttributes[i]->name();
   }

   return retVal;
}
