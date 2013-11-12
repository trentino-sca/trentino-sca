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
#include "TrentinoBindingIpcBinding.h"

//standard
#include <exception>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <boost/asio.hpp>

//specific
#include "../Utils/TrentinoUtilsLogging.h"
#include "../Runtime/Binding/TrentinoBindingBindingException.h"
#include "Global/TrentinoGlobal.h"
//#include "TrentinoBindingSCASCABindingFactory.h"
#include "TrentinoBindingIpcDataHandler.h"
#include "../Runtime/SCAModel/TrentinoSCAModelComponent.h"
#include "../Runtime/SCAModel/TrentinoSCAModelMetadataStringAttribute.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModel.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModelComponent.h"

using namespace Trentino::Binding;
using namespace Trentino::Binding::IPC;
namespace po = boost::program_options;
namespace SCAModel = Trentino::SCA::Model;

namespace 
{
   const char* bindingIpcMemoryID= "binding.ipc.memory.id";
}

BindingIpc::BindingIpc(const std::string& bindingId)
   :mBindingId(bindingId)
{
}

BindingIpc::~BindingIpc()
{
   stop();
}

void BindingIpc::configure(Trentino::Binding::ConfigOptions& configOptions,
   const Trentino::ServiceRegistry::ServiceRegistryPtr& registry, 
   const Trentino::Invocation::InvokerPtr& invoker )
{
   configOptions;
   // allways check that the option is not allready added before adding it
   if(configOptions.find_nothrow(bindingIpcMemoryID, false)==nullptr)
   {
      configOptions.add_options()(bindingIpcMemoryID, po::value<string>()->default_value("3148"));
   }

   setInvoker(invoker);
   setServiceRegistry(registry);
}

// start the data handler thread
void BindingIpc::start()
{
   if(!mIpcServerTransport || !mIpcServerTransport->isStarted())//TODO
   {
      try
      {
         ContextPtr mIpcContext(new Context);
         mIpcContext->setServiceRegistry(mServiceRegistry);
         mIpcContext->setInvoker(mInvoker);

         DataHandlerIpc* dataHandlerIpc = new DataHandlerIpc();
         dataHandlerIpc->setServiceInfoReader(IpcServiceInfoReaderFromIpcSoapPtr(new IpcServiceInfoReaderFromIpcSoap()));
         dataHandlerIpc->setInvokerProxy(InvokerProxyPtr(new InvokerProxy(mIpcContext->invoker())));
         dataHandlerIpc->setBindingId("binding.ipc");
         
         dataHandlerIpc->setIpcContext(mIpcContext);
         mDataHandler.reset(dataHandlerIpc);
         string memoryID = mTrentinoBindingContext[bindingIpcMemoryID].as<string>();
         // 3178 is a key to identify the shared memory could be changed possibly with a more unique identifier
         mIpcServerTransport.reset(new BindingIpcServerTransport("3178"));
         BindingIpcServerTransport::setHandler(dataHandlerIpc);
         mIpcServerTransport->start();
      }
      catch (std::exception& e)
      {
         std::string msg ("Unknown exception occurred: ");
         msg+=std::string(e.what());
         logError(msg.c_str());
      }
   }
   else 
   {
      logInfo("Server allready started");
   }
}

void BindingIpc::stop()
{

}


boost::shared_ptr<SCAModel::Metadata> BindingIpc::getServiceMetadata(Trentino::RuntimeModel::ServiceBasePtr service)
{
   boost::shared_ptr<SCAModel::Metadata> retval;
   retval.reset(new SCAModel::Metadata);

   SCAModel::MetadataStringAttribute *x = new SCAModel::MetadataStringAttribute();
   x->setName("_binding");
   x->setValue("ipc");
   retval->addStringAttributesElement(x);

   Trentino::RuntimeModel::ComponentPtr comp(service->component());

   x = new SCAModel::MetadataStringAttribute();
   x->setName("_binding.ipc.component");
   x->setValue(comp->scaComponent()->name().c_str());
   retval->addStringAttributesElement(x);

   x = new SCAModel::MetadataStringAttribute();
   x->setName("_binding.ipc.service");
   x->setValue(service->name().c_str());
   retval->addStringAttributesElement(x);

   x = new SCAModel::MetadataStringAttribute();
   x->setName("_binding.ipc.component.uri");
   x->setValue(comp->uri().c_str());
   retval->addStringAttributesElement(x);

   return retval;
}

std::string BindingIpc::getServiceUri(Trentino::SCA::Model::Metadata & metadata) 
{
      std::string  service="", component = "";

      BOOST_FOREACH(const SCAModel::MetadataStringAttributePtr &attr, metadata.stringAttributesElements())
      {
         if(attr->name() == "_binding.ipc.service")
         {
            service = attr->value();
         }
         else if(attr->name() == "_binding.ipc.component")
         {
            component = attr->value();
         }
      }
      std::string retval = "";

      if ( (service != "")  )
      {
         retval = "ipc://"+component+"/"+service+"/";
      }

      return retval;
}
