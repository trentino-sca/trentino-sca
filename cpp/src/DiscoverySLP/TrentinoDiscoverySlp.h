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

#ifndef TrentinoDiscoverySlpH
#define TrentinoDiscoverySlpH
//
//#ifdef WIN32
//#ifdef DISCOVERYSLP_EXPORTS
//#define DISCOVERYSLP_IMPORT_EXPORT __declspec(dllexport)
//#else
//#define DISCOVERYSLP_IMPORT_EXPORT __declspec(dllimport)       
//#endif
//#else
//#define DISCOVERYSLP_IMPORT_EXPORT 
//#endif

#ifdef _WIN32

# include <string.h>
# include <stdio.h>
# include <stdlib.h>

#else /* ! _WIN32 */

# if HAVE_CONFIG_H
#  include "config.h"
# endif
# if HAVE_STDIO_H
#  include <stdio.h>
# endif
# if HAVE_STDLIB_H
#  include <stdlib.h>
# endif
# if HAVE_STRING_H
#  include <string.h>
# else
#  if HAVE_STRINGS_H
#   include <strings.h>
#  endif
# endif

# define SLP_VERSION VERSION

#endif /* ! _WIN32 */

#include "../OpenSLP/libslp/slp.h"

//standart
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>


//specific
#include "../Runtime/Discovery/TrentinoDiscovery.h"
#include "../Runtime/Discovery/TrentinoDiscoveryMethodInterface.h"
#include "../Runtime/Discovery/TrentinoDiscoveryTaskFindSrv.h"



namespace Trentino{
namespace Discovery{
//! \defgroup DiscoverySLP
namespace SLP{
namespace OpenSLP
{
   class DiscoveryTask;

   //class declaration
   //**********************************************************************************************
   //                             TrentinoDiscoverySlp
   //**********************************************************************************************
   //! \ingroup DiscoverySLP
   //! \brief Class that implements the generic DiscoveryMethodInterface and
   //!  provides the functionality via OpenSLP
   //**********************************************************************************************
   class TrentinoDiscoverySlp : public DiscoveryMethodInterface 
   {
      //additional
   private:
      typedef boost::shared_ptr<Metadata> MetadataSharedPtr;
      typedef boost::shared_ptr<DiscoveryTaskFindSrv> FinsSrvsTaskPtr;

      //construction
   public:
      TrentinoDiscoverySlp();

      // services
   public:
      //*******************************************************************************************
      //                                     start()                               
      //*******************************************************************************************
      //! \brief Implements the start method of DiscoveryMethodInterface. Install and start methods
      //! of openSLP daemon are triggered. Service Location Protocol Service is installed and 
      //! started. If it is already installed and started result is still perceived as a success
      //!
      //! \param  taskStart holds DiscoveryTask which is actually a DiscoveryTaskStart . 
      //!  retVal(return value) and status(boolean) members of the task are modified based on the OpenSLP
      //!  results. 
      //*******************************************************************************************
      void start(Trentino::Discovery::DiscoveryTask*  taskStart);

      //*******************************************************************************************
      //                                     stop()                               
      //*******************************************************************************************
      //! \brief Implements the top method of DiscoveryMethodInterface
      //! It stops the Service Location protocol service and removes it.
      //! TODO: enhance similar to start method
      //*******************************************************************************************
      void stop(Trentino::Discovery::DiscoveryTask*  taskStop);

      //*******************************************************************************************
      //                                     registerSrv()                               
      //*******************************************************************************************
      //! \brief Implements the registerSrv method of DiscoveryMethodInterface
      //! \param  taskRegister  holds DiscoveryTask which is actually a DiscoveryTaskRegister
      //*******************************************************************************************
      void registerSrv(Trentino::Discovery::DiscoveryTask*  taskRegister);

      //*******************************************************************************************
      //                                     deregisterSrv()                               
      //*******************************************************************************************
      //! \brief Implements the registerSrv method of DiscoveryMethodInterface
      //! \param  taskRegister  holds DiscoveryTask which is actually a DiscoveryTaskDeregister
      //*******************************************************************************************
      void deregisterSrv(Trentino::Discovery::DiscoveryTask*  taskDeregister);

      //*******************************************************************************************
      //                                     findSrv()                               
      //*******************************************************************************************
      //! \brief Implements the registerSrv method of DiscoveryMethodInterface
      //! \param  taskRegister  holds DiscoveryTask which is actually a DiscoveryTaskRegister
      //*******************************************************************************************
      void findSrv(Trentino::Discovery::DiscoveryTask* taskFindSrv);

      static TrentinoDiscoverySlp& getInstance();

      //management
   private:

      //*******************************************************************************************
      //                                     registerCB()                               
      //*******************************************************************************************
      //! \brief Callback triggered once the SLPReg call made from resgisterSrv function is 
      //!  accomplished with or without success
      //!
      //! \param  hslp  SLPHandle
      //! \param  errcode  Keeps the informative text about the result
      //! \param  cookie   registerSrv function above casts Register task as cookie and passes to 
      //! openslp to be passed to the callback once register command is accomplished. According to 
      //! result of registration success code and retVal members of register task is set.
      //*******************************************************************************************
      static void registerCB(SLPHandle hslp, SLPError errcode, void * cookie);


      //*******************************************************************************************
      //                                     findSrvsCB()                               
      //*******************************************************************************************
      //! \brief Callback triggered once the SLPFindsrv call made from findSrv function is 
      //!  accomplished with or without success
      //!
      //! \param  hslp  SLPHandle
      //! \param  errcode  Keeps the informative text about the result
      //! \param  cookie   findSrv function above casts FindSrvs task as cookie and passes to 
      //! openslp to be passed to the callback once register command is accomplished. According to 
      //! result of registration success code and retVal members of FindSrv task is set.
      //*******************************************************************************************
      static SLPBoolean findSrvsCB(SLPHandle hslp,
         const char* srvurl,
         unsigned short lifetime,
         SLPError errcode,
         void* cookie );

      //*******************************************************************************************
      //                                     deregisterCB()                               
      //*******************************************************************************************
      //! \brief Callback triggered once the SLPDereg call made from deregisterSrv function is 
      //!  accomplished with or without success
      //!
      //! \param  hslp  SLPHandle
      //! \param  errcode  Keeps the informative text about the result
      //! \param  cookie   deregisterSrv function above casts DeregisterSrv task as cookie and passes to 
      //! openslp to be passed to the callback once deregister command is accomplished. According to 
      //! result of deregistration, success code and retVal members of DeregisterSrv task is set.
      //*******************************************************************************************
      static void deregisterCB(SLPHandle hslp, SLPError errcode, void * cookie);

      //*******************************************************************************************
      //                                     getConcreteUniqueServiceID()                               
      //*******************************************************************************************
      //! \brief Used to retrieve a unique identifier for the service to be registered.
      //! Several services might have the same identifier (as we decided to have service identifier
      //! to reflect the class attribute of interface.cpp) So while registering we need to differentiate
      //! them. This differentiated identifier name will be used to be able to delete a specific service
      //!
      //*******************************************************************************************
      std::string getConcreteUniqueServiceID();

      //*******************************************************************************************
      //                                     checkOutFilterMetaData()                               
      //*******************************************************************************************
      //! \brief Checks out if the found service fits the attributes given to filter. (hosted
      //! as a member for findSrv task(first param)) 
      //!
      //! static since it is triggered from static callback functions. It also provides the 
      //! mandatory attributes of the service that fits the filter attributes.
      //!
      //! \param  taskFindSrvsCasted  FindServiceTask hosting several relevant info
      //! \param  foundServiceUrl  url of the found service to be used while querying for attributes
      //! \param  mandatoryMetaData   mandatory attributes of the found service 
      //! \return Returns true if the found service is qualifying the filter attributes, false otherwise
      //*******************************************************************************************
      static bool checkOutFilterMetaData ( 
         //boost::shared_ptr<DiscoveryTaskFindSrv> taskFindSrvsCasted,
         DiscoveryTaskFindSrv* taskFindSrvsCasted,
         std::string foundServiceUrl,
         MetadataSharedPtr mandatoryMetaData);

      static bool checkOutFilterMetaData ( Trentino::Discovery::DiscoveryTaskFindSrv* taskFindSrvs,
         std::string urlFoundService,
         Trentino::SCA::Model::Metadata& mandatoryattributes);
      //*******************************************************************************************
      //                                     populateMandatoryAttributes()                               
      //*******************************************************************************************
      //! \brief Not used now
      //!
      //*******************************************************************************************
      static void populateMandatoryAttributes ( 
         MetadataSharedPtr& foundMetadata, 
         std::string urlFoundService);

      //*******************************************************************************************
      //                                     deregisterCB()                               
      //*******************************************************************************************
      //! \brief Callback triggered once the SLPFindAttrs call made once a service is found. Callback
      //! function is triggered in any case success/unsuccess
      //!
      //! \param  hslp  SLPHandle
      //! \param  attrlist [out]  This an out param. Callback populates it with the string that represents 
      //! found attributes as a comma separated name value pairs
      //! "att1name=att1value,att2=att2value"
      //! \param  errcode  Keeps the informative text about the result
      //! \param  cookie  string of found attributes is provided via the cookie
      //*******************************************************************************************
      static SLPBoolean filterAttrCallback(
         SLPHandle hslp,
         const char* attrlist, 
         SLPError errcode, 
         void* cookie );
      
      //*******************************************************************************************
      //                                     mandatoryAttrCallback()                               
      //*******************************************************************************************
      //! \brief Not used now
      //*******************************************************************************************
      static SLPBoolean mandatoryAttrCallback(
         SLPHandle hslp, 
         const char* attrlist, 
         SLPError errcode, 
         void* cookie );

      //*******************************************************************************************
      //                                     getFilterAttributes()                               
      //*******************************************************************************************
      //! \briefreturns the come seperated list of attributes to be used as a filter
      //*******************************************************************************************
      //static std::string getFilterAttributes(FinsSrvsTaskPtr findSrvsTaskPtr);


      //*******************************************************************************************
      //                                     compareAttributes()                               
      //*******************************************************************************************
      //! \brief compares attributes by name and value.
      //! \param filterMetadata Attributes defined to be used for filtering, kept in the member of 
      //! FindSrv task
      //! \param foundAttributesMultiMap All attributes of a service converted to a map
      //*******************************************************************************************
      static bool compareAttributes(ConstMetadataConstSharedPtr filterMetadata, 
         std::multimap< std::string, std::string>& foundAttributesMultiMap);

      static void staticStart(bool& taskStart, char* resultMessage);
      //data
   private:
      //! keeps the instance of singleton DiscoverySlp class
      static TrentinoDiscoverySlp mInstanceDiscoverySlp;

      //static std::map< int, DiscoveryTaskSharedPtr > mTaskMap;

   };
} // namespace OpenSLP
} //namespace SLP
} //namespace Discovery
} //namespace Trentino

#endif TrentinoDiscoverySlpH



