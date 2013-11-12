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
#include "TrentinoBindingSCATrentinoBindingSCATest.h"

//standard
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem/path.hpp>

//specific
#include "../../BindingSCA/TrentinoBindingSCATrentinoBindingSCA.h"
#include "../../Runtime/Binding/TrentinoBinding.h"
#include "../../Runtime/Invocation/TrentinoInvocationInvokerBase.h"
#include "TrentinoInvocationMocks.h"
#include "TrentinoBindingSCACompactSoapDataHandler.h"
#include "TrentinoBindingSCAZeroMqServer.h"
#include "Utils/TrentinoUtilsEnvironment.h"
#include "Utils/TrentinoUtilsConfiguration.h"
//class TrentinoBindingSCATest

using namespace Trentino::Binding;
using namespace Trentino::Binding::SCA;
using namespace Trentino::Binding::SCA::Tests;
using namespace Trentino::Invocation::Tests;
namespace fs = boost::filesystem;
namespace po = boost::program_options;
namespace Environment = Trentino::Utils::Environment;
using namespace std;

namespace{
   const string DefaultConfigFilePath = "../cfg/Binding.conf";
   const char* mBindingScaPort= "binding.sca.port";
   const char* mBindingScaMaxThreadNumber= "binding.sca.thread.number";  
   std::string configFilePath()
      {
      return ( fs::path(Environment::executablePath()).parent_path() / fs::path(DefaultConfigFilePath) ).string();
      }
   }


//class Worker
Trentino::Binding::SCA::Tests::Worker::~Worker()
   {
   mBindingSCA->stop();
   }

Trentino::Binding::SCA::Tests::Worker::Worker( Trentino::Binding::SCA::TrentinoBindingSCAPtr bindingSCA ) :  mBindingSCA(bindingSCA)
   {

   }

void Trentino::Binding::SCA::Tests::Worker::operator()()
   {
   mBindingSCA->start();
   }


class DummyHandler : public CompactSoapDataHandler {
public:

    DummyHandler(){}
   ~DummyHandler(){}

   virtual void handle(const trentino::bindingsca::csoap::Soap& /*request*/, trentino::bindingsca::csoap::Soap& response) const
      {
     trentino::bindingsca::csoap::Soap_Envelope* envelop = response.mutable_envelope();
     trentino::bindingsca::csoap::Soap_Body* body = envelop->mutable_body();
     std::string content("OK");
     body->set_content(content);
    trentino::bindingsca::csoap::Soap_Header* header= envelop->mutable_header();
    trentino::bindingsca::csoap::Addressing* address = header->mutable_addressing();
    address->set_to("ME");

      }
      
   };



TEST_F(TrentinoBindingSCATest, start_0MqServer_send_request_server_can_responsed) {
   Trentino::Utils::Configuration mConfiguration(configFilePath());
   mConfiguration.configOptions().add_options()
      ("binding.sca.dll", po::value<string>()->default_value( ""));

   if(mConfiguration.configOptions().find_nothrow(mBindingScaPort,false)==nullptr){
     mConfiguration.configOptions().add_options()
         (mBindingScaPort, po::value<int>()->default_value(0));
      }
   if(mConfiguration.configOptions().find_nothrow(mBindingScaMaxThreadNumber,false)==nullptr){
      mConfiguration.configOptions().add_options()
         (mBindingScaMaxThreadNumber, po::value<int>()->default_value(1));
      }
   mConfiguration.parse(true);
   Options options = mConfiguration.optionsMap();
   CompactSoapDataHandlerPtr handler(new DummyHandler());
   zmq::context_t context (1);
   ZeroMqServerPtr server(new ZeroMqServer(context,options,handler));
   //server->start();
  // boost::this_thread::sleep(boost::posix_time::minutes((long)1));
   //server->stop();
   }

