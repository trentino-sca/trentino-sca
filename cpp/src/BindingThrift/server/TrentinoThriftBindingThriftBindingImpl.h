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

#ifndef TrentinoThriftBindingThriftBindingImplH
#define TrentinoThriftBindingThriftBindingImplH

//standard
#include <string>
#include <boost/shared_ptr.hpp>

//specific
#include "TrentinoThriftBinding.h"
#include "TrentinoThriftBindingThriftBinding.h"
#include <thrift/processor/TMultiplexedProcessor.h>

namespace Trentino{
namespace ThriftBinding
{
 
class THRIFTBINDING_IMPORT_EXPORT ThriftBindingImpl: public ThriftBinding {


//constructors
public:
ThriftBindingImpl();
~ThriftBindingImpl();
//services
public:
    virtual void registerProcessor(const std::string& serviceName,apache::thrift::TProcessor* processor);
	virtual void unregisterProcessor(const std::string& serviceName);
	void setConfigurationFile(const std::string& configfilePath);
	const std::string& configurationFile() const;
	void setRootDir(const std::string& root){mRootDir = root;}
	void onInit();
	void onDestroy();
	boost::shared_ptr<apache::thrift::TProcessor> processor(); 

private:
	std::string mConfigurationFile;
	std::string mRootDir;
	boost::shared_ptr<apache::thrift::TMultiplexedProcessor> mProcessor;
}; //ThriftBindingImpl

} //namespace ThriftBinding
} //namespace Trentino

#endif //TrentinoThriftBindingThriftBindingImplH