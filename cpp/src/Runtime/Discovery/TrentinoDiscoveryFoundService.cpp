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
#include "TrentinoDiscoveryFoundService.h"

//specific
#include "./../../Runtime/SCAModel/TrentinoSCAModelMetadataStringAttribute.h"

using namespace Trentino::Discovery;

DiscoveryFoundService::DiscoveryFoundService(std::string serviceUrl, MetadataSharedPtr metaDatas)
   // :mMetaDatasOfService(metaDatas)
{
   mServiceUrl = serviceUrl;
   size_t mandatoryAttributeCount = metaDatas->stringAttributesElements().size();
   MetadataSharedPtr metaDatasOfService = MetadataSharedPtr (new Trentino::SCA::Model::Metadata());
   for(size_t i = 0; i < mandatoryAttributeCount ; i++)
   {
      

      Trentino::SCA::Model::MetadataStringAttribute* stringAttribute =  new Trentino::SCA::Model::MetadataStringAttribute();
      
      stringAttribute->setName(metaDatas->stringAttributesElements()[i]->name().c_str());
      stringAttribute->setValue(metaDatas->stringAttributesElements()[i]->value().c_str());
      metaDatasOfService->addStringAttributesElement(stringAttribute);
      mMetaDatasOfService = metaDatasOfService;

   }
}

DiscoveryFoundService::DiscoveryFoundService(std::string serviceUrl, Trentino::SCA::Model::Metadata& metaDatas)
   // :mMetaDatasOfService(metaDatas)
{
   mServiceUrl = serviceUrl;
   size_t mandatoryAttributeCount = metaDatas.stringAttributesElements().size();
   MetadataSharedPtr metaDatasOfService = MetadataSharedPtr (new Trentino::SCA::Model::Metadata());
   for(size_t i = 0; i < mandatoryAttributeCount ; i++)
   {
      Trentino::SCA::Model::MetadataStringAttribute* stringAttribute =  new Trentino::SCA::Model::MetadataStringAttribute();

      stringAttribute->setName(metaDatas.stringAttributesElements()[i]->name().c_str());
      stringAttribute->setValue(metaDatas.stringAttributesElements()[i]->value().c_str());
      metaDatasOfService->addStringAttributesElement(stringAttribute);
      mMetaDatasOfService = metaDatasOfService;

   }
}

DiscoveryFoundService::~DiscoveryFoundService()
{
   //mMetaDatasOfService->clear();
}
