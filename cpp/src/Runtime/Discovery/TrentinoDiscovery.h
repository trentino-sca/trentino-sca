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

#ifndef TrentinoDiscoveryH
#define TrentinoDiscoveryH


#include "../SCAModel/TrentinoSCAModelMetadata.h"
#include <list>

namespace Trentino{
namespace Discovery
{
   class DiscoveryFoundService;
   typedef boost::shared_ptr<const Trentino::SCA::Model::Metadata> const ConstMetadataConstSharedPtr;

   //! /param reqID: used by the owner of the callback to associate the callback with any of its requests
   //! /param status: if the registration task succeeded or not
   //! /param returnValOrStatusInfo: if the stat is true, carries the unique identifier otherwise
   //! just the descriptive info about the failure
   typedef void (*onDiscoveryTaskFindSrvCB)(int reqID, bool status, std::string returnValOrStatusInfo);

   //! /param reqID: used by the owner of the callback to associate the callback with any of its requests
   //! /param status: if the registration task succeeded or not
   //! /param returnValOrStatusInfo: if the stat is true, carries the unique identifier otherwise
   //! just the descriptive info about the failure
   typedef void (*onDiscoveryTaskRegsiterCB)(int reqID, bool status, std::string returnValOrStatusInfo);

   //! /param status: if the start task succeeded or not
   //! /param returnValOrStatusInfo: if the stat is true, carries the unique identifier otherwise
   //! just the descriptive info about the failure
   typedef void (*onDiscoveryStartCBPtr)(bool status, std::string returnValOrStatusInfodata);

   typedef void (*onDiscoveryStopCBPtr)();

   //typedef std::vector< DiscoveryFoundService* > listFoundServices;
   //typedef std::list< boost::shared_ptr<DiscoveryFoundService> > listFoundServices;
   typedef std::list< DiscoveryFoundService* > listFoundServices;
} // namespace Discovery
} // namespace Trentino
#endif //TrentinoDiscoveryH