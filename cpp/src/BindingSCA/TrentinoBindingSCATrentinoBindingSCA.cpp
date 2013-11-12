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
#include "TrentinoBindingSCATrentinoBindingSCA.h"

//standard
#include <exception>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <boost/asio.hpp>

//specific

//Logging
#include "../Utils/TrentinoUtilsLogging.h"

//compact soap
#include <Binding/CompactSoap/BindingCompactSoapProtobufMessages.h>

#include "../Runtime/Binding/TrentinoBindingBindingException.h"
#include "Global/TrentinoGlobal.h"
#include "TrentinoBindingSCASCABindingFactory.h"
#include "TrentinoBindingSCAZeroMqServer.h"
#include "TrentinoBindingSCADataHandler.h"
#include "../Runtime/SCAModel/TrentinoSCAModelComponent.h"
#include "../Runtime/SCAModel/TrentinoSCAModelMetadataStringAttribute.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModel.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModelComponent.h"


using namespace Trentino::Binding;
using namespace Trentino::Binding::SCA;
namespace po = boost::program_options;

namespace {
   const char* bindingScaPort= "binding.sca.port";
   const char* mBindingScaMaxThreadNumber= "binding.sca.thread.number"; 
   }

namespace SCAModel = Trentino::SCA::Model;

//class TrentinoBindingSCA

TrentinoBindingSCA::TrentinoBindingSCA
   ( const std::string& bindingId)
    : mBindingId (bindingId)    
   {
   mContext = new zmq::context_t(1);
   }





Trentino::Binding::SCA::TrentinoBindingSCA::~TrentinoBindingSCA()
   {
   }

void Trentino::Binding::SCA::TrentinoBindingSCA::configure( Trentino::Binding::ConfigOptions& configOptions,const Trentino::ServiceRegistry::ServiceRegistryPtr& registry, const Trentino::Invocation::InvokerPtr& invoker )
   {
      //allways check that the option is not allready added before adding it
   if(configOptions.find_nothrow(bindingScaPort,false)==nullptr){
      configOptions.add_options()
         (bindingScaPort, po::value<int>()->default_value(0));
      }
   if(configOptions.find_nothrow(mBindingScaMaxThreadNumber,false)==nullptr){
     configOptions.add_options()
         (mBindingScaMaxThreadNumber, po::value<int>()->default_value(1));
      }
   setInvoker(invoker);
   setServiceRegistry(registry);
   }



//! read port number from binding Context and start the server on that port
void TrentinoBindingSCA::start()
   {
   if(!mServer || !mServer->isStarted()){
      try
         {
      
         int portValue =-1;
         try {
            portValue = mTrentinoBindingContext[bindingScaPort].as<int>();
            }catch(...){
               logError("Port not specified or invalid: please specify SCA Binding default port using attribute:" 
                  "binding.sca.port in the Binding.conf file. Then restart Trentino\n SCA Binding not started");
               return;
            }
          

         if(portValue < 0){
            logError("SCA Binding not started: Port value should be positive: SCA Binding: port %d",portValue);
            return;
            }

         ContextPtr mSCAContext(new Context);
         mSCAContext->setServiceRegistry(mServiceRegistry);
         mSCAContext->setInvoker(mInvoker);
         boost::shared_ptr<DataHandlerDependencies> deps(new DataHandlerDependencies());
         deps->setServiceInfoReader(ServiceInfoReaderPtr(new ServiceInfoReaderImpl()));
         deps->setInvokerProxy(InvokerProxyPtr(new InvokerProxy(mSCAContext->invoker())));
         deps->setBindingId("binding.sca");
         DataHandler* dataHandler = new DataHandler();
         dataHandler->setDependencies(deps);
         dataHandler->setSCAContext(mSCAContext);
         mDataHandler.reset(dataHandler);
         mServer.reset(new ZeroMqServer(*mContext, mTrentinoBindingContext,mDataHandler));
         mServer->start();
         }
      catch (std::exception& e)
         {
           std::string msg ("Unknown exception occurred: ");
           msg+=std::string(e.what());
           logError(msg.c_str());
         }
      }
   else {
      logInfo("Server already started");
      }

   }

void TrentinoBindingSCA::stop()
   {
   if(mServer && mServer->isStarted())
   {
      mServer.reset();
     delete mContext;
     }
   }

boost::shared_ptr<SCAModel::Metadata> TrentinoBindingSCA::getServiceMetadata(Trentino::RuntimeModel::ServiceBasePtr service)
   {
   boost::shared_ptr<SCAModel::Metadata> retval;
   retval.reset(new SCAModel::Metadata);

   SCAModel::MetadataStringAttribute *x = new SCAModel::MetadataStringAttribute() ;
   x->setName("_binding");
   x->setValue("sca");
   retval->addStringAttributesElement(x);

   x = new SCAModel::MetadataStringAttribute() ;
   x->setName("_binding.sca.host");
   std::string host_str = boost::asio::ip::host_name();
   x->setValue(host_str.c_str());
   retval->addStringAttributesElement(x);

   x = new SCAModel::MetadataStringAttribute() ;
   x->setName("_binding.sca.port");
   std::string port_str = boost::lexical_cast<std::string>(mTrentinoBindingContext[bindingScaPort].as<int>());
   x->setValue(port_str.c_str());
   retval->addStringAttributesElement(x);

   Trentino::RuntimeModel::ComponentPtr comp(service->component());

   x = new SCAModel::MetadataStringAttribute() ;
   x->setName("_binding.sca.component");
   x->setValue(comp->scaComponent()->name().c_str());
   retval->addStringAttributesElement(x);

   x = new SCAModel::MetadataStringAttribute() ;
   x->setName("_binding.sca.service");
   x->setValue(service->name().c_str());
   retval->addStringAttributesElement(x);

   x = new SCAModel::MetadataStringAttribute() ;
   x->setName("_binding.sca.component.uri");
   x->setValue(comp->uri().c_str());
   retval->addStringAttributesElement(x);


   return retval;

   }

//****************************************************************************************************
//                                         getBindingFactory()
//****************************************************************************************************
//! \brief main entry point for a Binding. Return a Binding Factory used to instantiate Bindings
//! \return extern "C" TRENTINO_DLLEXPORT Trentino::Binding::BindingFactory* TRENTINO_CDECL
//****************************************************************************************************
extern "C" TRENTINO_DLLEXPORT void TRENTINO_CDECL getBindingFactory(Trentino::Binding::BindingFactory * factory,const char * /*bindingId*/)
  {
   SCABindingFactory* implementation= new Trentino::Binding::SCA::SCABindingFactory();
   factory->setImplementor(implementation);
   factory->setGetBinding(&Trentino::Binding::SCA::SCABindingFactory::getBinding);
   factory->setCreateBinding(&Trentino::Binding::SCA::SCABindingFactory::createBinding);
  }

std::string Trentino::Binding::SCA::TrentinoBindingSCA::getServiceUri(
      Trentino::SCA::Model::Metadata & metadata) {

   std::string host = "", port="", service="", component = "";

   BOOST_FOREACH(const SCAModel::MetadataStringAttributePtr &attr, metadata.stringAttributesElements())
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

}
