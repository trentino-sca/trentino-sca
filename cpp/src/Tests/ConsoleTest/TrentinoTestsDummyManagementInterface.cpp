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

#include "TrentinoTestsDummyManagementInterface.h"

using Trentino::ManagementInterface;
using Trentino::Tests::Console::DummyManagementInterface;
using namespace std;

typedef ManagementInterface MI;
typedef DummyManagementInterface DummyRMI;

//Runtime management
MI::ErrorMessage DummyRMI::install(const std::string& /*contributionDirectoryPath*/,
   const std::string& /*contributionBaseURI*/)
{
   string err;

   pullTheTrigger();

   if (trigger)
      err = "installation failed due to damned curved hands";  

   return err;
}

MI::ErrorMessage DummyRMI::deploy(const std::string& /*contributionBaseURI*/)
{
   string err;

   if (trigger)
      err = "deployment failed";

   return err;
}

MI::ErrorMessage DummyRMI::remove(const std::string& /*contributionIdentifier*/)
{
   string err;

   pullTheTrigger();

   if (trigger)
      err = "contribution remove failed";

   return err;
}

MI::ErrorMessage DummyRMI::removeComponent(const std::string& /*componentURI*/)
{
   string err;

   pullTheTrigger();

   if (trigger)
      err = "component remove failed";

   return err;
}

MI::ErrorMessage DummyRMI::rewire(const std::string& /*referenceURI*/,
   const std::string& /*target*/,
   const std::string& /*bindingType*/)
{
   string err;

   pullTheTrigger();

   if (trigger)
      err = "rewire failed";

   return err;
}

MI::ErrorMessage DummyRMI::setProperty(const std::string& /*propertyURI*/, 
   const MI::PropertyValues& /*newValues*/)
{
   string err;

   pullTheTrigger();

   if (trigger)
      err = "property set failed";

   return err;
}

//Information retrieve
Trentino::ManagementInterface::ContributionDatas DummyRMI::getContributions() const
{
   Trentino::ManagementInterface::ContributionDatas baseURIs;
   Trentino::ManagementInterface::ContributionData data1 = Trentino::ManagementInterface::ContributionData::newInstance("base.uri.1");
   Trentino::ManagementInterface::ContributionData data2 = Trentino::ManagementInterface::ContributionData::newInstance("base.uri.2");
   baseURIs.push_back(data1);
   baseURIs.push_back(data2);
   return baseURIs;
}



MI::Attributes DummyRMI::getAttributes(const std::string& /*artifactURI*/) const
{
   MI::Attributes attrs;

   attrs["name"] = "attribute";
   attrs["size"] = "huge";

   return attrs;
}

MI::Services DummyRMI::getServices(const std::string& /*componentURI*/) const
{
   MI::Services servs;

   servs.push_back("service1");
   servs.push_back("service2");

   return servs;
}

MI::References DummyRMI::getReferences(const std::string& /*componentURI*/) const
{
   MI::References refs;

   refs.push_back("reference1");
   refs.push_back("reference2");
   refs.push_back("reference3");

   return refs;
}

MI::PropertiesNames DummyRMI::getPropertiesNames(const std::string& /*componentURI*/) const
{
   MI::PropertiesNames names;

   names.push_back("currency");

   return names;
}

MI::ImplementationType DummyRMI::getImplementationType(const std::string& /*componentURI*/) const
{
   MI::ImplementationType impl;

   impl = "C++ class";

   return impl;
}

MI::PropertyValues DummyRMI::getPropertyValues(const std::string& /*propertyURI*/) const
{
   MI::PropertyValues vals;

   vals.push_back("euro");
   vals.push_back("dollar");
   vals.push_back("ruble");

   return vals;
}

MI::ServiceState DummyRMI::getServiceState(const std::string& /*serviceURI*/) const
{
   MI::ServiceState state;

   state = "WIRED";

   return state;
}

MI::ServicesStates DummyRMI::getServicesStates(const std::string& /*componentURI*/) const
{
   MI::ServicesStates states;

   states["service1"] = "WIRED";
   states["service2"] = "UNWIRED";

   return states;
}

MI::ReferenceState DummyRMI::getReferenceState(const std::string& /*referenceURI*/) const
{
   MI::ReferenceState state;

   state = "WIRED";

   return state;
}

MI::ReferencesStates DummyRMI::getReferencesStates(const std::string& /*componentURI*/) const
{
   MI::ReferencesStates states;

   states["reference1"] = "WIRED";
   states["reference2"] = "UNWIRED";
   states["reference3"] = "REFERENCED";

   return states;
}

MI::ReferenceTargets DummyRMI::getReferenceTargets(const std::string& /*referenceURI*/) const
{
   MI::ReferenceTargets targets;

   targets.push_back("yandex");
   targets.push_back("google");
   targets.push_back("yahoo");

   return targets;
}

MI::ComponentState DummyRMI::getComponentState(const std::string& /*componentURI*/) const
{
   MI::ComponentState state;

   state = "RUNNING";

   return state;
}


Trentino::ManagementInterface::ContributionData DummyRMI::getContribution(const std::string &) const
{
   Trentino::ManagementInterface::ContributionData data = Trentino::ManagementInterface::ContributionData::newInstance("test");
   return data;
}

void DummyRMI::update(const std::string &,const std::string &,Trentino::Utils::DataObject &)
{
    //not implemented
}