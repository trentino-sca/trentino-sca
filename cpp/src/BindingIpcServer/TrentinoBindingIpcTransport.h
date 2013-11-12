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
#ifndef TrentinoBindingIpcTransportH
#define TrentinoBindingIpcTransportH

//standard
#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include <boost/thread.hpp>
#pragma warning(push)
#pragma warning(disable:4512)
#include <boost/program_options.hpp>
#pragma warning(pop)

//specific
#include "TrentinoBindingIpcDataHandler.h"
#include "../Utils/TrentinoUtilsConfiguration.h"

namespace Trentino{
	namespace Binding {
		namespace IPC
		{

			typedef boost::shared_ptr<DataHandlerIpc> IpcDataHandlerPtr;
			typedef boost::program_options::variables_map Options;


			class BINDINGIPC_IMPORT_EXPORT BindingIpcServerTransport
			{
				//construction
			public:
				//IpcMemoryChecker(const Options options, const IpcDataHandlerPtr& handler);
				BindingIpcServerTransport(string memoryID);
				~BindingIpcServerTransport();

				void operator () ();
				void checkMemory();
				//services
			public:
				void start();
				void stop();
				bool isStarted();
				static void setHandler(DataHandlerIpc* handler)
				{
					handler;
					mDataHandler.reset(handler);
				}

			private:
				std::string configFilePath() const;
				//data
			private:
				Options mOptions;
				bool mStarted;
				bool mStoped;

				static IpcDataHandlerPtr mDataHandler;
				int mThreadNumber;
				string mMemoryID;

				//boost::interprocess::managed_shared_memory mManaged_shm;
				//boost::interprocess::named_condition mConditionClientData; 
				//boost::interprocess::named_mutex mNamed_mtx; 
				//boost::interprocess::named_condition mConditionServerData; 
				//boost::interprocess::scoped_lock<boost::interprocess::named_mutex> mLock;

				//! Object providing the logic for parsing options from config files (and the cmd line)
				Trentino::Utils::Configuration mConfiguration;

			}; //BindingIpcServerTransport

		} //namespace IPC
	} //namespace Binding
} // namespace Trentino
#endif //TrentinoBindingIpcTransportH

