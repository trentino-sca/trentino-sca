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
#include "TrentinoThriftBindingThriftBindingImpl.h"
#include <Utils/TrentinoUtilsConfiguration.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <boost/thread.hpp>

using namespace Trentino::ThriftBinding;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

namespace po = boost::program_options;

namespace{

   const char* bindingThriftPort= "binding.thrift.port";
   const char* mBindingMaxThreadNumber= "binding.thrift.thread.number"; 
   
void configure(Trentino::Utils::Configuration& configuration)
{
   if(configuration.configOptions().find_nothrow(bindingThriftPort,false)==nullptr){
      configuration.configOptions().add_options()
         (bindingThriftPort, po::value<int>()->default_value(9090));
      }
   if(configuration.configOptions().find_nothrow(mBindingMaxThreadNumber,false)==nullptr){
     configuration.configOptions().add_options()
         (mBindingMaxThreadNumber, po::value<int>()->default_value(1));
      }

}

void start (ThriftBindingImpl* impl)
{
	Trentino::Utils::Configuration mConfiguration (impl->configurationFile());
	
	configure(mConfiguration);
	int port = mConfiguration.optionsMap()[bindingThriftPort].as<int>();
  
  shared_ptr<TProcessor> processor = impl->processor();
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
}

}

//Services
ThriftBindingImpl::~ThriftBindingImpl()
{
}

ThriftBindingImpl::ThriftBindingImpl(): mProcessor(new TMultiplexedProcessor)
{
}
void ThriftBindingImpl::onInit()
{
boost::thread workerThread(start, this);
}

void ThriftBindingImpl::onDestroy()
{
}

void ThriftBindingImpl::setConfigurationFile(const std::string& configfilePath)
{
    mConfigurationFile = mRootDir+"/"+ configfilePath;
}

const std::string& ThriftBindingImpl::configurationFile() const
{
  return mConfigurationFile;
}

shared_ptr<TProcessor> ThriftBindingImpl::processor()
{
 return mProcessor;
}

void ThriftBindingImpl::registerProcessor(const std::string& serviceName,apache::thrift::TProcessor* processor)
{
 boost::shared_ptr<apache::thrift::TProcessor> managedProcessor(processor);
 mProcessor->registerProcessor(serviceName, managedProcessor);
}

void ThriftBindingImpl::unregisterProcessor(const std::string& serviceName)
{
mProcessor->unregisterProcessor(serviceName);
}