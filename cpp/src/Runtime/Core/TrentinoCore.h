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

//standard
#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>

#ifdef WIN32
   #ifdef CORE_EXPORTS
      #define CORE_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define CORE_IMPORT_EXPORT __declspec(dllimport)       
   #endif //CORE_EXPORTS
#else
   #define CORE_IMPORT_EXPORT
#endif //WIN32
namespace Trentino
{
   class ManagementInterface;
} //namespace Trentino

namespace Trentino{
//! \defgroup Core
namespace Core
{
   class ComponentImplementationManagerBase;
   class ComponentCPPImplementationManager;
   class ContributionLoader;
   class TrentinoContributionInfo;
   class RuntimeAPI;
   
   typedef boost::shared_ptr<ComponentImplementationManagerBase> 
      ComponentImplementationManagerBasePtr;
   typedef boost::shared_ptr<ComponentCPPImplementationManager> 
      ComponentCPPImplementationManagerPtr;
   typedef boost::shared_ptr<ContributionLoader> 
      ContributionLoaderPtr;
   typedef boost::shared_ptr<ManagementInterface>
      ManagementInterfacePtr;
   typedef boost::shared_ptr<TrentinoContributionInfo> TrentinoContributionInfoPtr;
   typedef boost::shared_ptr<RuntimeAPI> RuntimeAPIPtr;

   //! \defgroup Bootstrapping
   namespace Bootstrapping
   {
      class ModuleBase;
      class BootstrapperBase;

      //! Convenience typedef to work with a \sa ModuleBase intrusive_ptr. 
      typedef boost::intrusive_ptr<ModuleBase> ModulePtr;

   } //namespace Bootstrapping

} //namespace Core
} //namespace Trentino
