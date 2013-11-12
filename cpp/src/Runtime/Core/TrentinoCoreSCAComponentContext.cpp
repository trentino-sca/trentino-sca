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
#include "TrentinoCoreSCAComponentContext.h"

//standard
#include <boost/thread/tss.hpp>
#include <boost/foreach.hpp>

//specific
#include "../../Utils/TrentinoUtilsPatternStaticClass.h"
#include "TrentinoCoreDomain.h"
#include "./../RuntimeModel/TrentinoRuntimeModelServiceBase.h"
#include "TrentinoCoreSCAServiceProxy.h"
#include "TrentinoCoreSCAServiceReference.h"
#include "TrentinoCoreBootstrappingRuntimeBootstrapper.h"


using namespace std;
using namespace Trentino::Core;

boost::thread_specific_ptr<oasis::sca::ComponentContextPtr> SCAComponentContext::ComponentContext;


SCAComponentContext::SCAComponentContext() : mRefCount(0)
{
}

SCAComponentContext::SCAComponentContext(std::string uri) : mRefCount(0), mUri(uri)
{
}

SCAComponentContext::~SCAComponentContext()
{
}

void SCAComponentContext::setCurrent(oasis::sca::ComponentContextPtr componentPtr)
{
   ComponentContext.reset(new oasis::sca::ComponentContextPtr(componentPtr));
}

oasis::sca::ComponentContextPtr SCAComponentContext::current()
{
   if(ComponentContext.get() != nullptr)
      return *ComponentContext.get();
   else
      return oasis::sca::ComponentContextPtr();
}

string SCAComponentContext::getURI() const
{
   return mUri;
}

oasis::sca::ServiceProxyPtr SCAComponentContext::getService(const string& referenceName) const
{
     Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =
      Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
  const RuntimeModel::ServiceBases services = 
     booter.domain().findDomandLevelServicesByName(referenceName);   
   if(services.empty())
      return oasis::sca::ServiceProxyPtr();
   else
   {
      return oasis::sca::ServiceProxyPtr(new SCAServiceProxy(services[0]->name()));
   }
}

vector<oasis::sca::ServiceProxyPtr> SCAComponentContext::getServices
   (const string& referenceName) const
{
   vector<oasis::sca::ServiceProxyPtr> result;
        Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =
      Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();

   Trentino::ManagementInterface::Services services = 
       booter.domain().managementInterface().getServices(referenceName);
   BOOST_FOREACH(const string& service, services)
   {
      oasis::sca::ServiceProxyPtr foundService = getService(service);
      if(foundService.get() != nullptr)
         result.push_back(foundService);
   }

   return result;
}

oasis::sca::ServiceReferencePtr SCAComponentContext::getServiceReference
   (const string& referenceName) const
{
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =
      Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();

   Trentino::ManagementInterface::References references = 
       booter.domain().managementInterface().getReferences(referenceName);
   if(references.empty())
      return oasis::sca::ServiceReferencePtr();
   else
   {
      //return the first one
      return oasis::sca::ServiceReferencePtr(new SCAServiceReference(references[0]));
   }
}

vector<oasis::sca::ServiceReferencePtr> SCAComponentContext::getServiceReferences
   (const string& referenceName) const
{
   vector<oasis::sca::ServiceReferencePtr> result;
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =
      Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();

   Trentino::ManagementInterface::References references = 
       booter.domain().managementInterface().getReferences(referenceName);

   BOOST_FOREACH(const string& reference, references)
   {
      result.push_back(oasis::sca::ServiceReferencePtr(new SCAServiceReference(reference)));
   }

   return result;
}

oasis::sca::ServiceReferencePtr SCAComponentContext::getSelfReference() const
{
   return getServiceReference(mUri);
}

oasis::sca::ServiceReferencePtr SCAComponentContext::getSelfReference
   (const string& serviceName) const
{
   return getServiceReference(serviceName);
}

uint32_t SCAComponentContext::addRef()
{
   return ++mRefCount;
}

uint32_t SCAComponentContext::releaseRef()
{
   if(mRefCount > 1)
      return --mRefCount;
   else
   {
      delete this;
      return 0;
   }
}
