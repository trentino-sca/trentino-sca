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

#include "TrentinoBindingIpcClientCommon.h"
#include "../Utils/TrentinoUtilsEnvironment.h"

#include <string>
#include <boost/filesystem/path.hpp>

//standard
#pragma warning(push)
#pragma warning(disable:4512)
#include <boost/program_options.hpp>
#pragma warning(pop)

using namespace Trentino::Binding::IPC::Client;
using namespace Trentino::Utils;
using namespace std;
namespace fs = boost::filesystem;
namespace Environment = Trentino::Utils::Environment;

TrentinoBindingIpcClientCommon TrentinoBindingIpcClientCommon::mInstance;

TrentinoBindingIpcClientCommon& TrentinoBindingIpcClientCommon::getInstance()
{
   return mInstance;
}

TrentinoBindingIpcClientCommon::~TrentinoBindingIpcClientCommon(void)
{
   //mContext.close();
}

TrentinoBindingIpcClientCommon::TrentinoBindingIpcClientCommon(const TrentinoBindingIpcClientCommon&)
{
}

TrentinoBindingIpcClientCommon::TrentinoBindingIpcClientCommon(void):mConfiguration(configFilePath())
{
   mConfiguration.configOptions().add_options()("binding.ipc.client.timeout", boost::program_options::value<int>()->default_value(1500));
   mConfiguration.configOptions().add_options()("binding.ipc.sharedmemorysize", boost::program_options::value<int>()->default_value(1024));
   mConfiguration.parse(true);
   mTimeOutPeriod = mConfiguration.optionsMap()["binding.ipc.client.timeout"].as<int>();
   mSharedMemorySize = mConfiguration.optionsMap()["binding.ipc.sharedmemorysize"].as<int>();
}

int TrentinoBindingIpcClientCommon::getTimeOutPeriod()
{
   return mTimeOutPeriod;
}

string TrentinoBindingIpcClientCommon::configFilePath() const
{
   return ( fs::path(Trentino::Utils::Environment::executablePath()).parent_path() / fs::path("../cfg/Binding.conf") ).string();
}

int TrentinoBindingIpcClientCommon::getSharedMemorySize()
{
   return mSharedMemorySize;
}
