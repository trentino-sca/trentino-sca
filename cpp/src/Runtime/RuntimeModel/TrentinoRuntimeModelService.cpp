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
#include "TrentinoRuntimeModelService.h"

//standard
#include <boost/pointer_cast.hpp>
#include <boost/thread/locks.hpp>
#include <boost/foreach.hpp>

//specific
#include "../SCAModel/TrentinoSCAModelBinding.h"
#include "../SCAModel/TrentinoSCAModel.h"
#include "../SCAModel/TrentinoSCAModelComponentService.h"
#include "../SCAModel/TrentinoSCAModelCPPInterface.h"
#include "TrentinoRuntimeModelComponent.h"
#include "../Binding/TrentinoBindingBindingHelperBase.h"
#include "TrentinoRuntimeModelComposite.h"
#include "../Core/TrentinoCoreContributionInfo.h"
#include "TrentinoRuntimeModelContribution.h"

using Trentino::RuntimeModel::Service;
using namespace std;
namespace RuntimeModel = Trentino::RuntimeModel;
namespace SCAModel = Trentino::SCA::Model;


namespace {

   SCAModel::CPPInterfacePtr getCppInterface(const Trentino::RuntimeModel::Service& service)
      {
      const SCAModel::CPPInterfacePtr scaCPPInterface = 
         boost::static_pointer_cast<SCAModel::CPPInterface>(
         service.scaServiceType()->interfaceElement());
      assert(scaCPPInterface);
      return scaCPPInterface;
      }
   }

//class Service
//construction
Service::Service( const Trentino::SCA::Model::ComponentServicePtr& scaServiceType
                 ,  const Trentino::SCA::Model::ComponentServicePtr& scaService
                 , const RuntimeModel::ComponentPtr& component)
                 : mSCAServiceType(scaServiceType)
                 , mSCAService(scaService)
                 , mComponent(component)
                 , mState(ServiceBase::Unavailable)
                 , mDiscoveryId("")
   {
   // Metadata shall be joined from both scaService and scaServiceType
   mMetaData.reset(new Trentino::SCA::Model::Metadata);
   // Copy metadata from service first, if available
   if(mSCAService.get() != nullptr )
      {
      if(mSCAService->metadataElement() != nullptr)
         {
         for(size_t i = 0; i < mSCAService->metadataElement()->stringAttributesElements().size(); i++)
            {
            Trentino::SCA::Model::MetadataStringAttribute *attr = new Trentino::SCA::Model::MetadataStringAttribute();
            attr->setName(mSCAService->metadataElement()->stringAttributesElements()[i]->name().c_str());
            attr->setValue(mSCAService->metadataElement()->stringAttributesElements()[i]->value().c_str());
            mMetaData->addStringAttributesElement(attr);
            }
         }
      }
   // then goes metadata from ServiceType, but only those attributes not overridden in Service
   if (mSCAServiceType.get() != nullptr)
      {
      if(mSCAServiceType->metadataElement() != nullptr)
         {
         for(size_t i = 0; i < mSCAServiceType->metadataElement()->stringAttributesElements().size(); i++)
            {
            bool already_exist = false;
            for(size_t j = 0; j < mMetaData->stringAttributesElements().size(); j++)
               {
               if(mMetaData->stringAttributesElements()[j]->name() ==
                  mSCAServiceType->metadataElement()->stringAttributesElements()[i]->name())
                  {
                  already_exist = true;
                  break;
                  }
               }
            if(! already_exist)
               {
               Trentino::SCA::Model::MetadataStringAttribute *attr = new Trentino::SCA::Model::MetadataStringAttribute();
               attr->setName(mSCAServiceType->metadataElement()->stringAttributesElements()[i]->name().c_str());
               attr->setValue(mSCAServiceType->metadataElement()->stringAttributesElements()[i]->value().c_str());
               mMetaData->addStringAttributesElement(attr);
               }
            }
         }
      }

   }

//services
Trentino::SCA::Model::ComponentServicePtr Service::scaServiceType() const
   {
   return mSCAServiceType;
   }

Trentino::SCA::Model::ComponentServicePtr Service::scaService() const
   {
   return mSCAService;
   }

RuntimeModel::ComponentWeakPtr Service::component() const
   {
   return mComponent;
   }

Service::State Service::state() const
   {
   const RuntimeModel::ComponentPtr component = mComponent.lock();
   assert(component); 

   boost::lock_guard<boost::recursive_mutex> lock(component->mutex());   
   if(    component->state() == RuntimeModel::Component::Resolved 
      || component->state() == RuntimeModel::Component::OptionalUnresolved )
      {
      return Available;
      }
   else
      {
      return Unavailable;
      }   
   }


Trentino::Binding::BindingHelperBasePtr Service::bindingHelperByBindingId(const string& bindingId) 
   {
   std::map<std::string,Trentino::Binding::BindingHelperBasePtr>::iterator it;
   it =mHelpers.find(bindingId);
   if(it != mHelpers.end()){
      return it->second;
      }
   //if not already created, then get it from the contribution info
   Trentino::RuntimeModel::ComponentPtr component = mComponent.lock();
   Trentino::RuntimeModel::CompositePtr composite= component->composite().lock();
   Trentino::RuntimeModel::ContributionPtr contribution=  composite->contribution().lock();
   Trentino::Core::TrentinoContributionInfoPtr  contributionInfo =contribution->contributionInfo();
   std::string className =cPPInterfaceClassName();
   Trentino::Binding::BindingHelperBase* bindingHelper =contributionInfo->getBindingHelperByBindingIdAndClassName(bindingId,className);
   Trentino::Binding::BindingHelperBasePtr bindingHelperPtr(bindingHelper);
   mHelpers[bindingId]=bindingHelperPtr;
   return bindingHelperPtr;
   }

RuntimeModel::ServiceBaseWeakPtr Service::promotedTo() const
   {
   return mPromotedTo;
   }

void Service::setPromotedTo(const RuntimeModel::ServiceBasePtr& service)
   {
   mPromotedTo = service;
   }

const RuntimeModel::WeakServiceBases& Service::promotedBy() const
   {
   return mPromotedBy;
   }

void Service::addPromotedBy(const RuntimeModel::ServiceBasePtr& service)
   {
   mPromotedBy.push_back(service);
   }

RuntimeModel::Wireable& Service::wireableSupport()
   {
   return mWireableSupport;
   }

boost::recursive_mutex& Service::mutex() const
   {
   const RuntimeModel::ConstComponentPtr component = mComponent.lock();
   assert(component); 
   return component->mutex();
   } 

const Trentino::XML::Schema::NCName& Service::name() const
   {
   return mSCAServiceType->name();
   }

Trentino::XML::Schema::Name Trentino::RuntimeModel::Service::cPPInterfaceClassName() const
   {
   const SCAModel::CPPInterfacePtr scaCPPInterface =getCppInterface(*this);
   return scaCPPInterface->clazz();
   }

bool Trentino::RuntimeModel::Service::isRemotable() const
   {
   const SCAModel::CPPInterfacePtr scaCPPInterface =getCppInterface(*this);
   return scaCPPInterface->isRemotable();
   }

const std::set<std::string> Trentino::RuntimeModel::Service::bindings() const
   {

   /*Assembly spec says:
   *
   * 791 binding : Binding (0..n) - A service element has zero or more binding elements as children. If no
   * 792 binding elements are specified for the service, then the bindings specified for the equivalent service in
   * 793 the componentType of the implementation MUST be used, but if the componentType also has no
   * 794 bindings specified, then <binding.sca/> MUST be used as the binding. If binding elements are
   * 795 specified for the service, then those bindings MUST be used and they override any bindings specified
   * 796 for the equivalent service in the componentType of the implementation. [ASM50005]
   *
   * So, Component bindings OVERRIDE componentType bindings.
   * */

   vector<Trentino::SCA::Model::BindingPtr> bindings;

   if(mSCAService && this->mSCAService->bindingElements().size() > 0)
      {
      bindings = this->mSCAService->bindingElements();
      }
   else if(mSCAServiceType)
      {
      bindings = this->mSCAServiceType->bindingElements();
      }

   std::set<std::string> result;

   BOOST_FOREACH(const Trentino::SCA::Model::BindingPtr & binding, bindings)
      {
      result.insert(binding->name());
      }

   return result;

   }

const Trentino::SCA::Model::MetadataPtr Trentino::RuntimeModel::Service::metaData() const
   {
   return mMetaData;//(this->scaService()->metadataElement());
   }

const std::string Trentino::RuntimeModel::Service::discoveryId() const {

   const RuntimeModel::ComponentPtr component = mComponent.lock();
   assert(component);

   boost::lock_guard<boost::recursive_mutex> lock(component->mutex());

   return this->mDiscoveryId;
   }

void Trentino::RuntimeModel::Service::setDiscoveryId(
   const std::string id) {

      const RuntimeModel::ComponentPtr component = mComponent.lock();
      assert(component);

      boost::lock_guard<boost::recursive_mutex> lock(component->mutex());

      mDiscoveryId = id;
   }
