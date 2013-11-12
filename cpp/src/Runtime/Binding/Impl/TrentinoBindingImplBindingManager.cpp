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
#include "TrentinoBindingImplBindingManager.h"

//standard
#include <vector>
#include <boost/program_options.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/thread.hpp>

//specific
#include "../TrentinoBindingBindingFactory.h"
#include "../TrentinoBindingBindingException.h"
#include "../TrentinoBindingTrentinoBinding.h"
#include "../../RuntimeModel/TrentinoRuntimeModelService.h"
#include "./../../../Utils/TrentinoUtilsLogging.h"
#include "../../RuntimeModel/TrentinoRuntimeModelVisitor.h"
#include "../../../Utils/TrentinoUtilsEnvironment.h"
#include "../../../Utils/TrentinoUtilsDynamicLibrary.h"
#include "../../Core/TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "../../Core/TrentinoCoreBootstrappingRuntimeConfiguration.h"

using namespace Trentino::Core;
using namespace Trentino::Utils;
using namespace Trentino::RuntimeModel;
using namespace Trentino::Binding;
using namespace Trentino::Binding::Impl;
namespace po = boost::program_options;
namespace fs = boost::filesystem;
namespace Environment = Trentino::Utils::Environment;
using namespace std;

//global functions
void deleterBindingDynamicDll(DynamicLibrary* ptr)
   {
   assert(ptr != nullptr);

   if(ptr->isLoaded())
      {
      // once should be sufficient
      ptr->unload(DynamicLibrary::Once);
      }

   delete ptr;
   }

class Worker  
   {  
   public:   

      Worker(TrentinoBindingPtr binding):mBinding(binding)
         { 
         if(mBinding == nullptr)
            {
            throw std::runtime_error("Binding is null");
            }
         }  

      void operator()()  
         {  
         mBinding->start();
         }  

   private:  
      TrentinoBindingPtr mBinding;
   }; 

namespace
   {

   const string GetBindingFactoryName  = "getBindingFactory";
   void getBindings(std::vector<std::string>& bindingsVect, const char* bindings)
      {
      std::string temp = bindings;
      size_t index = std::string::npos;
      do {
         index = temp.find_first_of(',', 0);
         if(index==std::string::npos)
            {
            bindingsVect.push_back(temp);
            break;
            } 
         else 
            {
            std::string aBinding = temp.substr(0, index);
            if(aBinding!="" && aBinding!=",")
               {
               bindingsVect.push_back(aBinding);
               }
            if(index+1 <= temp.size())
               {
               index = index+1;
               }
            temp = temp.substr(index);
            }
         } while (temp!="");
      }

   Trentino::Binding::BindingFactory* loadBindings(const std::string bindingId, Trentino::Utils::Configuration& mConfiguration)
      {
      //the binding is new then
      //1 load the binding dll
      std::string bindingdll = bindingId+".dll";
      //check if this option is in the configoptions
      if(mConfiguration.configOptions().find_nothrow(bindingdll.data(), false)==nullptr)
         {
         mConfiguration.configOptions().add_options()
            (bindingdll.data(), po::value<string>()->default_value(""));
         mConfiguration.parse(true);
         }

      const po::variable_value&  bindingdllValueObj = mConfiguration.optionsMap()[bindingdll];
      if(bindingdllValueObj.empty())
         {
         //then add the option to the config and find again
         logError("no dll name found for binding %s", bindingdll.c_str());
         return nullptr;
         }

      std::string bindingdllValue = bindingdllValueObj.as<std::string>();
      DynamicLibraryPtr dll(new DynamicLibrary(bindingdllValue), deleterBindingDynamicDll);
      dll->load();
      assert(dll->isLoaded());
      const Trentino::Binding::GetBindingFactory getBindingFactory = 
         dll->functionAddress<Trentino::Binding::GetBindingFactory>(GetBindingFactoryName);
      assert(getBindingFactory);
      Trentino::Binding::BindingFactory* bindingFactory = new Trentino::Binding::BindingFactory();
      getBindingFactory(bindingFactory, bindingId.data());
      assert(bindingFactory);
      bindingFactory->setDynamicLibrary(dll);      
      return bindingFactory;
      }
   }

//class BindingManager

//static memmber initialization
const string BindingManager::DefaultConfigFilePath = "../cfg/Binding.conf";

BindingManager::BindingManager():mConfiguration(configFilePath())
   {
   //parse the configuration. at least one option is added since the parser read the ini 
   //file only when options are available.
   //the binding.sca.dll should allways be available since it is the default binding
   mConfiguration.configOptions().add_options()
      ("binding.sca.dll", po::value<string>()->default_value( ""));
   mConfiguration.parse(true);
   }

BindingManager::~BindingManager()
   {
   }


//! \ingroup TrentinoBinding
//! load a Trentino Binding configuration from file system
//! \param[bindingId] The id of the binding whose context have to be loaded

const TrentinoBindingContextPtr& BindingManager::loadDefaultBindingContext( const std::string& /*bindingId*/ ) 
   {
   return mConfiguration.optionsMap();
   }

boost::shared_ptr<Metadata> Trentino::Binding::Impl::BindingManager::getServiceMetadata(
      string bindingId, Trentino::RuntimeModel::ServiceBasePtr service) {

   if(bindingId == "")
   {
      std::map<std::string, Trentino::Binding::TrentinoBindingPtr>::iterator it;
      boost::shared_ptr<Metadata> retval;
      retval.reset(new Metadata());
      //Iterate through all available bindings
      for (it = mBindings.begin(); it != mBindings.end(); ++it)
      {  // Recursion goes here: requesting metadata from individual binding
         boost::shared_ptr<Metadata> md = getServiceMetadata(it->first, service);
         const std::vector<MetadataStringAttributePtr> temp= md->stringAttributesElements();
         // Iterate through obtained metadata

         for(size_t i = 0; i < temp.size(); i++)
         { // And store them in the return value
            MetadataStringAttribute *attr = new  MetadataStringAttribute;

            attr->setName( temp[i]->name().c_str());
            attr->setValue( temp[i]->value().c_str());

            retval->addStringAttributesElement( attr);
         }

      }
      return retval;
   }
   else
   {
      TrentinoBindingPtr binding;

      if( mBindings.find(bindingId) == mBindings.end())
      {
         std::string message = "No Binding \""+bindingId+"\" found for service "+service->name();
         throw new std::runtime_error(message.data());
      }
      binding = mBindings[bindingId];
      return binding->getServiceMetadata(service);
   }


}

std::string BindingManager::configFilePath() const
   {
   using namespace Trentino::Core::Bootstrapping;
   const RuntimeBootstrapper&  bootstrapper = RuntimeBootstrapper::instance();
   RuntimeBootstrapper::RuntimeConfigurationConstPtr conf= bootstrapper.configuration();
   const std::string fn = conf->bindingConfigFilename();
   const std::string path = conf->getConfiguration().getConfigFilepath();
   return ( fs::path(path).parent_path() / fs::path(fn) ).string();
   }


bool Trentino::Binding::Impl::BindingManager::onDeploy( const Trentino::RuntimeModel::ContributionPtr& contribution )
   {
   logInfo("binding manager start handling new contribution %s", contribution->baseURI().c_str() );
   const TrentinoContributionInfoPtr& info = contribution->contributionInfo();
   const char* bindings = info->getAllDeclaredBindings();

   if(bindings == nullptr)
      {
      return true;
      }

   if(std::string(bindings) =="")
      {
      return true;
      }

   std::vector<std::string> bindingsVect;
   getBindings(bindingsVect, bindings);
   std::vector<std::string>::const_iterator it;
   for(it=bindingsVect.begin();it!=bindingsVect.end();++it)
      {
      const std::string bindingId =*it;
      if(mBindings.find(bindingId) == mBindings.end())
         {

         Trentino::Binding::BindingFactory* factory= loadBindings(bindingId, mConfiguration);

         if(factory == nullptr)
            {
            std::string message = "No Binding factory found for binding "+bindingId;
            throw new std::runtime_error(message.data());
            }

         Trentino::Binding::BindingFactoryPtr factoryPtr(factory);
         mBindingFactories.push_back(factoryPtr);
         createBinding(bindingId);
         }
      startBinding(bindingId);
      }
   return true;
   }


void BindingManager::createBinding( const std::string& bindingId )
   {
   if(mBindings.find(bindingId) == mBindings.end())
      {
      BindingFactories::iterator it;
      BindingFactoryPtr factory;

      for(it = mBindingFactories.begin(); it != mBindingFactories.end();++it)
         {
         BindingFactoryPtr temp = *it;
         std::string sourceBindingId =temp->getBindingId();
         if(sourceBindingId == bindingId)
            {
            //The corresponding factory was found
            factory = temp;
            break;
            }
         }

      if(factory == nullptr)
         {
         //Factory not found. the Binding module should be loaded, 
         //so that it can register his factory to the manager
         //that part is not implemented yet since the Module loading strategy is unknown
         throw BindingException("BindingFacory for binding :"+bindingId+" does not exist");
         }
      //Factory is available, so we can create the context and then the binding

      TrentinoBindingPtr binding = factory->createBinding();
      binding->configure(mConfiguration.configOptions(), 
         Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance().serviceRegistry(), 
         Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance().invoker());
      mConfiguration.parse(true);
      binding->setContext(loadDefaultBindingContext(bindingId));
      mBindings[bindingId]= binding;
      }

   }

void BindingManager::startBinding( const std::string& bindingId )
   {
   const char* errorMassage ="Binding is not declared";
   if(mBindings.find(bindingId) == mBindings.end())
      {
      throw BindingException(errorMassage);
      }
   TrentinoBindingPtr binding = mBindings[bindingId];
   if(binding == nullptr)
      {
      throw BindingException(errorMassage);
      }
   Worker w(binding);
   boost::thread workerThread(w);
   logInfo("Binding successfully launched");
   }


  void BindingManager::stop()
     {
     //stop all Bindings
     std::map<std::string, Trentino::Binding::TrentinoBindingPtr>::iterator it;
     for(it = mBindings.begin();it!=mBindings.end();++it)
        {
        TrentinoBindingPtr binding = it->second;
        if(binding)
           {
           binding->stop();
           binding.reset();
           }
        }
     mBindings.clear();

     //now unload the libraries
     BindingFactories::iterator bit;
     for(bit = mBindingFactories.begin(); bit != mBindingFactories.end();++bit)
        {
        BindingFactoryPtr temp = *bit;
        temp.reset();
        }
     }

  
/*!
 * \todo The code is copied from NindingSCA. It is to be completely refactored to return to original verision.
 * Where the BindingManager only identifies the binfing and dispatches the request to corresponding class.
 *
 */
std::string Trentino::Binding::Impl::BindingManager::getServiceUri(string bindingId, Metadata& metadata)
{

   std::string host = "", port="", service="", component = "";

   BOOST_FOREACH(const MetadataStringAttributePtr &attr, metadata.stringAttributesElements())
   {
      if(attr->name() == "_binding.sca.host")
      {
         host = attr->value();
      }else if(attr->name() == "_binding.sca.port")
      {
         port = attr->value();

      }else if(attr->name() == "_binding.sca.service")
      {
         service = attr->value();
      }
      else if(attr->name() == "_binding.sca.component")
      {
         component = attr->value();
      }
   }
   std::string retval = "";

   if ( (host != "") && (port != "") && (service != "")  )
   {
      retval = "tcp://"+host+":"+port+"/"+component+"/"+service+"/";
   }

   return retval;

#if 0
   TrentinoBindingPtr binding;
   std::string retval;
      if (bindingId == "")
   {
      bindingId = "binding.sca";
   }

   if( mBindings.count(bindingId) < 1)
   {
      retval = "";
   }
   else
   {
      binding = mBindings[bindingId];
      retval = binding->getServiceUri(metadata);
   }


   return retval;
#endif

}
