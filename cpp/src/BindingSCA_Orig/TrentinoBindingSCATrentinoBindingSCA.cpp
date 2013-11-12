// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************

//header
#include "TrentinoBindingSCATrentinoBindingSCA.h"

//standard
#include <exception>
#include <boost/program_options.hpp>


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

using namespace Trentino::Binding;
using namespace Trentino::Binding::SCA;
namespace po = boost::program_options;

namespace {
   const char* bindingScaPort= "binding.sca.port";
   const char* mBindingScaMaxThreadNumber= "binding.sca.thread.number"; 
   }

//class TrentinoBindingSCA

TrentinoBindingSCA::TrentinoBindingSCA
   ( const std::string& bindingId)
    : mBindingId (bindingId),
    mContext(1)
   {
   }





Trentino::Binding::SCA::TrentinoBindingSCA::~TrentinoBindingSCA()
   {
   stop();
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
            logError("SCA Binding not started: Port value should be positive: SCA Binding: port "+portValue);
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
         mServer.reset(new ZeroMqServer(mContext, mTrentinoBindingContext,mDataHandler));
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
      logError("Server allready started");
      }


   }

void TrentinoBindingSCA::stop()
   {
   if(mServer && mServer->isStarted()){
      mServer->stop();
      }
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



