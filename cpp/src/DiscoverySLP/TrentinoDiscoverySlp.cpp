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
#include "TrentinoDiscoverySlp.h"

//standart
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>  
#include <boost/thread.hpp>



//specific
#include "../OpenSLP/slpd/slpddll.h"
#include "../Global/TrentinoGlobal.h"
#include "TrentinoDiscoverySlpUtil.h"

#include "../Runtime/Discovery/TrentinoDiscoveryTaskRegister.h"
#include "../Runtime/Discovery/TrentinoDiscoveryTaskDeregister.h"
#include "../Runtime/Discovery/TrentinoDiscoveryTaskFindSrv.h"
#include "../Runtime/Discovery/TrentinoDiscoveryTaskStart.h"
#include "../Runtime/Discovery/TrentinoDiscoveryTask.h"

using namespace boost;
using namespace boost::this_thread;
using namespace Trentino::Discovery::SLP::OpenSLP;
using namespace std;

TrentinoDiscoverySlp TrentinoDiscoverySlp::mInstanceDiscoverySlp;


TrentinoDiscoverySlp::TrentinoDiscoverySlp()
{
   return;
}

void TrentinoDiscoverySlp::staticStart(bool& resultCode, char* resultMessage)
{
   resultCode;
   resultMessage;
   //SLPDCmdInitializeSlp(0, resultCode, resultMessage);
}

void TrentinoDiscoverySlp::start(Trentino::Discovery::DiscoveryTask*  taskStart)
{ 
    /*boost::shared_ptr<DiscoveryTaskStart> taskStartCasted = boost::static_pointer_cast<DiscoveryTaskStart>(taskStart);
     DiscoveryTaskStart* taskStartCasted = static_cast<DiscoveryTaskStart*> (taskStart);*/
   try
   {
      BOOL resultCode =  false;
      char resultMessage[500];
      resultMessage[0] = 0;

      //boost::thread t(&TrentinoDiscoverySlp::staticStart, resultCode, resultMessage);
       boost::thread t(&SLPDCmdInitializeSlp, 0, &resultCode, resultMessage);
      while(resultMessage[0] == 0)
      {
         //boost::this_thread::sleep(boost::posix_time::millisec(1000));
         Sleep(1000);
      }
      resultCode?taskStart->setSucceeded(true):taskStart->setSucceeded(false);
      //taskStart->setSucceeded(successCode);
      taskStart->setReturnVal(resultMessage);
      return;
      //BOOL successCode;
      // //to be able to exchange return messages with the c dll of openslp char array is used
      //char installServiceResult[500];
      //
      //SLPDCmdInstallService(0, successCode, installServiceResult);
   
      //std::string installServiceResultStr(installServiceResult);
   
      //// if the service is already installed successCode returns negative 
      //// but it is still a notification of installed service
      //unsigned found = installServiceResultStr.find("already exists");
      //if(found != std::string::npos)
      //{
      //   successCode = TRUE;
      //   taskStart->setSucceeded(true);
      //   taskStart->setReturnVal("oleey");
      //}

      //// service installing failed 
      //if( successCode != TRUE )
      //{
      //   taskStart->setSucceeded(false);
      //   taskStart->setReturnVal(installServiceResultStr);
      //   //taskStartCasted->mDiscoveryFrameworkCB(taskStartCasted->mTaskSharedPtr);
      //   return;
      //}
      //taskStart->setSucceeded(true);
      //   taskStart->setReturnVal("oleeey");
      //char startServiceResult[500];
      //SLPDCmdStartService(successCode, startServiceResult);
      //std::string startServiceResultStr(startServiceResult);

      //// if the service is already started successCode returns negative 
      //// but it is still a notification of started service
      //found = startServiceResultStr.find("already running");
      //if(found != std::string::npos)
      //{
      //   successCode = TRUE;
      //}
      //// starting failed while starting SLP service
      //if( successCode != TRUE )
      //{
      //   taskStart->setSucceeded(false);
      //   taskStart->setReturnVal(startServiceResult);
      //   //taskStartCasted->mDiscoveryFrameworkCB(taskStartCasted->mTaskSharedPtr);
      //   return;
      //}
      //else // Successfully started the slp service (installed + started)
      //{
      //   taskStart->setSucceeded(true);
      //   taskStart->setReturnVal(startServiceResult);
      //   //taskStartCasted->mRuntimeCB(taskStartCasted->mStatus, taskStartCasted->mReturnValue);
      //}
   }
   catch (std::exception& e)
   {
      std::string msg ("Exception -SLP start error: ");
      msg+=std::string(e.what());
      taskStart->setSucceeded(false);
      taskStart->setReturnVal(msg);
      return;
   }
   catch (...)
   {
      taskStart->setSucceeded(false);
      taskStart->setReturnVal("Exception - SLP start");
      return;
   }
}

void TrentinoDiscoverySlp::stop(Trentino::Discovery::DiscoveryTask*  taskStop)
{ 
   try
   {
      // we used to use SLP as a windows service but not any more 
      //SLPDCmdStopService();
      //SLPDCmdRemoveService();

      SLPDCmdDeinitializeSlp();

      taskStop->setSucceeded(true);
      taskStop->setReturnVal("Success - SLP stop - SLP remove");
   }
   catch (...)
   {
      taskStop->setSucceeded(false);
      taskStop->setReturnVal("Exception - SLP stop - SLP remove");
   }
}


void TrentinoDiscoverySlp::registerSrv(Trentino::Discovery::DiscoveryTask*  taskRegister)
{
   // boost::shared_ptr<DiscoveryTaskRegister> taskRegisterCasted = boost::static_pointer_cast<DiscoveryTaskRegister>(taskRegister);
   DiscoveryTaskRegister* taskRegisterCasted = static_cast<DiscoveryTaskRegister*> (taskRegister);

   SLPHandle hslp;
   try
   {
      SLPError err;
      
      // as the second attribute is false SLPFindSrvs will work synchronously
      // (SLPHandle will be opened for asynchronous operation)
      // in other words function will not return unless the callback func is 
      // called, code is relying on this
      err = SLPOpen("en", SLP_FALSE, &hslp);

      if(err != SLP_OK)
      {
         taskRegisterCasted->setSucceeded(false);
         char errBuffer [4];
         ::_itoa_s(err, errBuffer, 10);
         std::string retVal = "Error Register-OpenSLP while openning SLP handle errorcode ";
         retVal += errBuffer;
         retVal += " - service identifier1: " + taskRegisterCasted->getServiceIdentifier();

         taskRegisterCasted->setReturnVal(retVal);

         return;
      }
      //int nID = taskRegister->getID();
      //mTaskMap.insert(std::pair<int, DiscoveryTaskSharedPtr>(nID, taskRegister)); 

      // A unique service identifier is created, the service identifier given in the task 
      // represents the class attribute of the interface.cpp. To be able to differentiate 
      // services the identifier needs to be unique,esspecially to be able to delete the 
      // correct service
      std::string servcieIdentifier = taskRegisterCasted->getServiceIdentifier()+":"+ getConcreteUniqueServiceID();
      taskRegisterCasted->setServiceIdentifierUnique(servcieIdentifier);
      
      servcieIdentifier ="service:" + servcieIdentifier + "://localhost";
      //servcieIdentifier =servcieIdentifier + taskRegisterCasted->getServiceIdentifier() + "://localhost";

      std::string attList = DiscoverySlpUtil::metada2AttrList(taskRegisterCasted->getAttributes());
      /* Register a service with SLP */
      err = SLPReg(
         hslp,
         //"service:myservice.myorg://hostname.domain.com:6672",
         servcieIdentifier.c_str(),
         SLP_LIFETIME_MAXIMUM,
         0,
         attList.c_str(),
         SLP_TRUE,
         registerCB,
         &(taskRegisterCasted) );


      if(err != SLP_OK)
      {
         taskRegisterCasted->setSucceeded(false);

         char errBuffer [4];
         ::_itoa_s(err, errBuffer, 10);
         std::string retVal = "Error Register-OpenSLP  errorcode: ";
         retVal += errBuffer;

         retVal += " - service identifier2: " + taskRegisterCasted->getServiceIdentifier();

         taskRegisterCasted->setReturnVal(retVal);

      }

      SLPClose(hslp);
   }
   catch (std::exception& e)
   {
      SLPClose(hslp);
      std::string msg  = "Exception - SLP registerSrv serviceIdentifier: " + 
         taskRegisterCasted->getServiceIdentifier() +
         "error: " +
         std::string(e.what());

      taskRegisterCasted->setSucceeded(false);
      taskRegisterCasted->setReturnVal(msg);
      return;
   }
   catch(...)
   {
      SLPClose(hslp);
      taskRegisterCasted->setSucceeded(false);
      std::string retVal = "Exception Register-OpenSLP - service identifier:" + taskRegisterCasted->getServiceIdentifier();
      taskRegisterCasted->setReturnVal(retVal);
      return;
   }

}


void TrentinoDiscoverySlp::deregisterSrv(Trentino::Discovery::DiscoveryTask*  taskDeregister)
{ 
   SLPHandle hslp;
   // boost::shared_ptr<DiscoveryTaskDeregister> taskDeregisterCasted = boost::static_pointer_cast<DiscoveryTaskDeregister>(taskDeregister);
   DiscoveryTaskDeregister* taskDeregisterCasted = static_cast<DiscoveryTaskDeregister*> (taskDeregister);
   try
   {
      SLPError err;
      // as the second attribute is false SLPFindSrvs will work synchronously
      // (SLPHandle will be opened for asynchronous operation)
      // in other words function will not return unless the callback func is 
      // called, code is relying on this
      err = SLPOpen("en", SLP_FALSE, &hslp);

      if(err != SLP_OK)
      {
         taskDeregisterCasted->setSucceeded(false);

         char errBuffer [4];
         ::_itoa_s(err, errBuffer, 10);
         std::string retVal = "Error Deregister-OpenSLP while openning SLP handle errorcode: ";
         retVal += errBuffer;

         retVal += " - service identifier3: " + taskDeregisterCasted->getServiceIdentifier();

         taskDeregisterCasted->setReturnVal(retVal);

         return;
      }
      //int nID = taskDeregister->getID();
      //mTaskMap.insert(std::pair<int, DiscoveryTaskSharedPtr>(nID, taskDeregister)); 

      std::string servcieIdentifier = "service:";
      servcieIdentifier =servcieIdentifier + taskDeregisterCasted->getServiceIdentifier() + "://localhost";

      err = SLPDereg(hslp, 
         servcieIdentifier.c_str(), 
         deregisterCB, 
         &(taskDeregisterCasted));

      if (err != SLP_OK)
      {
         taskDeregisterCasted->setSucceeded(false);

         char errBuffer [4];
         ::_itoa_s(err, errBuffer, 10);
         std::string retVal = "Error Deregister-OpenSLP  errorcode: ";
         retVal += errBuffer;

         retVal += " - service identifier: " + taskDeregisterCasted->getServiceIdentifier();

         taskDeregisterCasted->setReturnVal(retVal);

      }
      SLPClose(hslp);
      
   }
   catch (std::exception& e)
   {
      SLPClose(hslp);
      std::string msg  = "Exception - SLP deregisterSrv serviceIdentifier: " + 
         taskDeregisterCasted->getServiceIdentifier() +
         "error: " +
         std::string(e.what());

      taskDeregisterCasted->setSucceeded(false);
      taskDeregisterCasted->setReturnVal(msg);
      return;
   }
   catch (...)
   {
      SLPClose(hslp);
      taskDeregisterCasted->setSucceeded(false);
      std::string retVal = "Exception deregister-OpenSLP - service identifier: " + taskDeregisterCasted->getServiceIdentifier();
      taskDeregisterCasted->setReturnVal(retVal);
      return;
   }
}


void TrentinoDiscoverySlp::findSrv(Trentino::Discovery::DiscoveryTask*  taskFindSrv)
{ 
   SLPHandle hslp;
   //boost::shared_ptr<DiscoveryTaskFindSrv> taskFindSrvCasted = boost::static_pointer_cast<DiscoveryTaskFindSrv>(taskFindSrv);
   DiscoveryTaskFindSrv* taskFindSrvCasted = static_cast<DiscoveryTaskFindSrv*> (taskFindSrv);
   try
   {
      SLPError err;
      // as the second attribute is false SLPFindSrvs will work synchronously
      // (SLPHandle will be opened for asynchronous operation)
      // in other words function will not return unless the callback func is 
      // called, code is relying on this
      err = SLPOpen("en", SLP_FALSE, &hslp);  

      if(err != SLP_OK)
      {
         taskFindSrvCasted->setSucceeded(false);
         char errBuffer [4];
         ::_itoa_s(err, errBuffer, 10);
         std::string retVal = "Error FindSrv-OpenSLP while openning SLP handle errorcode: ";
         retVal += errBuffer;

         retVal += " - service identifier: " + taskFindSrvCasted->getServiceIdentifier();

         taskFindSrvCasted->setReturnVal(retVal);

         SLPClose(hslp);
         return;
      }

      /*mTaskMap.insert(std::pair<int, DiscoveryTaskSharedPtr>(taskFindSrv->getID(), taskFindSrv));   */

      std::string servcieIdentifier = "service:";
      servcieIdentifier =servcieIdentifier + taskFindSrvCasted->getServiceIdentifier();

      err = SLPFindSrvs( hslp,
         servcieIdentifier.c_str(),
         0,  /* use configured scopes */
         0,   /* no attr filter        */
         findSrvsCB,                         
         &(taskFindSrvCasted));

      if(err != SLP_OK)
      {
         taskFindSrvCasted->setSucceeded(false);

         char buffer [4];
         ::_itoa_s(err, buffer, 10);
         std::string retVal = "Error FindSrv-OpenSLP errorcode: ";
         retVal += buffer;

         retVal += " - service identifier: " + taskFindSrvCasted->getServiceIdentifier();
         taskFindSrvCasted->setReturnVal(retVal);
         SLPClose(hslp);
         return;
      }
   }
   catch (std::exception& e)
   {
      SLPClose(hslp);
      std::string msg  = "Exception - SLP findSrv serviceIdentifier: " + 
         taskFindSrvCasted->getServiceIdentifier() +
         "error: " +
         std::string(e.what());

      taskFindSrvCasted->setSucceeded(false);
      taskFindSrvCasted->setReturnVal(msg);
      return;
   }
   catch(...)
   {
      SLPClose(hslp);
      taskFindSrvCasted->setSucceeded(false);
      std::string retVal = "Exception FindSrv-OpenSLP - service identifier:" + taskFindSrvCasted->getServiceIdentifier();
      taskFindSrvCasted->setReturnVal(retVal);
      return;
   }


}


void TrentinoDiscoverySlp::registerCB(SLPHandle hslp, SLPError errcode, void * cookie)
{
   (void)hslp;

   //boost::shared_ptr<Trentino::Discovery::DiscoveryTaskRegister>* taskRegisterSrvPtr = 
   //   static_cast< boost::shared_ptr<Trentino::Discovery::DiscoveryTaskRegister>* >(cookie);
   //boost::shared_ptr<Trentino::Discovery::DiscoveryTaskRegister> taskRegisterSrv = *taskRegisterSrvPtr;

   Trentino::Discovery::DiscoveryTaskRegister** taskRegisterSrvPtr = 
      static_cast< Trentino::Discovery::DiscoveryTaskRegister** >(cookie);
   Trentino::Discovery::DiscoveryTaskRegister* taskRegisterSrv = *taskRegisterSrvPtr;

   if(errcode != SLP_OK)
   {
      taskRegisterSrv->setSucceeded(false);

      char errBuffer [4];
      ::_itoa_s(errcode, errBuffer, 10);
      std::string retVal = "Registration errorcode: ";
      retVal += errBuffer;

      retVal += " - service identifier: " + taskRegisterSrv->getServiceIdentifier();
      taskRegisterSrv->setReturnVal(retVal);
   }
   else
   {
      taskRegisterSrv->setSucceeded(true);
      std::string retVal = "Registered service: " + taskRegisterSrv->getServiceIdentifier();
      taskRegisterSrv->setReturnVal(retVal);
   }

   // erase the task from the task map
   //mTaskMap.erase(it);

}


void TrentinoDiscoverySlp::deregisterCB(SLPHandle hslp, SLPError errcode, void * cookie)
{
   (void)hslp;

   //boost::shared_ptr<Trentino::Discovery::DiscoveryTaskDeregister>* taskDeregisterSrvsPtr = 
   //   static_cast< boost::shared_ptr<Trentino::Discovery::DiscoveryTaskDeregister>* >(cookie);
   //boost::shared_ptr<Trentino::Discovery::DiscoveryTaskDeregister> taskDeregisterSrvs = *taskDeregisterSrvsPtr;

   Trentino::Discovery::DiscoveryTaskDeregister** taskDeregisterSrvsPtr = 
      static_cast< Trentino::Discovery::DiscoveryTaskDeregister** >(cookie);
   Trentino::Discovery::DiscoveryTaskDeregister* taskDeregisterSrvs = *taskDeregisterSrvsPtr;

   if(errcode != SLP_OK)
   {
      taskDeregisterSrvs->setSucceeded(false);
      char errBuffer [4];
      ::_itoa_s(errcode, errBuffer, 10);
      std::string retVal = "Deregistration errorcode: ";
      retVal += errBuffer;

      retVal += " - service identifier: " + taskDeregisterSrvs->getServiceIdentifier();
      taskDeregisterSrvs->setReturnVal(retVal);
   }
   else
   {
      taskDeregisterSrvs->setSucceeded(true);
      std::string retVal = "Deregistered service:" + taskDeregisterSrvs->getServiceIdentifier();
      taskDeregisterSrvs->setReturnVal(retVal);
   }

   // erase the task from the task map
   //mTaskMap.erase(it);

}


SLPBoolean  TrentinoDiscoverySlp::findSrvsCB(
   SLPHandle /*hslp*/,
   const char* srvurl,
   unsigned short lifetime,
   SLPError errcode,
   void* cookie )
{
   //boost::shared_ptr<Trentino::Discovery::DiscoveryTaskFindSrv>* taskFindSrvsPtr = 
   //   static_cast< boost::shared_ptr<Trentino::Discovery::DiscoveryTaskFindSrv>* >(cookie);
   //boost::shared_ptr<Trentino::Discovery::DiscoveryTaskFindSrv> taskFindSrvs = *taskFindSrvsPtr;

   Trentino::Discovery::DiscoveryTaskFindSrv** taskFindSrvsPtr = 
      static_cast< Trentino::Discovery::DiscoveryTaskFindSrv** >(cookie);
   Trentino::Discovery::DiscoveryTaskFindSrv* taskFindSrvs = *taskFindSrvsPtr;

   lifetime;

   if(errcode == SLP_OK)
   {
      std::string foundServiceUrl = srvurl;      
      //MetadataSharedPtr foundMandatoryMetadata(new Metadata());
      Metadata foundMandatoryMetadata;

      BOOL filterMetadataExists = checkOutFilterMetaData(taskFindSrvs, foundServiceUrl, foundMandatoryMetadata);
      taskFindSrvs->setSucceeded(TRUE);
      taskFindSrvs->setReturnVal("whatever");
      if( filterMetadataExists != TRUE)
      {
         taskFindSrvs->setSucceeded(false);
         taskFindSrvs->setReturnVal("Service not found (Attribute matching failed)- service identifier: " + taskFindSrvs->getServiceIdentifier());
      }
      else
      {
         taskFindSrvs->setSucceeded(true);
         //std::string retVal = "Found service with identifier : " + taskFindSrvCasted->getServiceIdentifier();
         //taskFindSrvs->setReturnVal(retVal);
         // add the new service to the task so all the matching services can be delivered to the user of Discovery Layer
         taskFindSrvs->setReturnVal("Service found - service identifier: " + taskFindSrvs->getServiceIdentifier());
         //taskFindSrvs->onNewServiceFound(boost::make_shared<DiscoveryFoundService>(srvurl, foundMandatoryMetadata));
         taskFindSrvs->onNewServiceFound(srvurl, foundMandatoryMetadata);
      }
   }
   else
      if(errcode == SLP_LAST_CALL)
      {
         // no succeed info should be set in case of last call
         //taskFindSrvs->setSucceeded(true);
         //mTaskMap.erase(it);
      }
      else
      {
         taskFindSrvs->setSucceeded(false);
         taskFindSrvs->setReturnVal(srvurl);
      }

      return SLP_TRUE;
}


std::string TrentinoDiscoverySlp::getConcreteUniqueServiceID()
{
   boost::uuids::uuid uuid = boost::uuids::random_generator()();
   std::stringstream uuisSS;
   uuisSS << uuid;

   const std::string tmp = uuisSS.str();
   return tmp;
}


bool TrentinoDiscoverySlp::checkOutFilterMetaData ( Trentino::Discovery::DiscoveryTaskFindSrv* taskFindSrvs,
   std::string urlFoundService,
   MetadataSharedPtr mandatoryattributes)
{
   SLPError    result; 
   SLPHandle hslp;
   SLPError    err;

   // as the second attribute is false SLPFindAttrs will work synchronously
   // (SLPHandle will be opened for asynchronous operation)
   // in other words function will not return unless the callback func is 
   // called, code is relying on this
   err = SLPOpen("en", SLP_FALSE, &hslp); 

   if(err != SLP_OK)
   {
      return false;
   }

   unsigned index = urlFoundService.find("://localhost");
   urlFoundService.erase(index, std::string::npos);


   string foundAttributesStr;
   // check out filtered attributes
   result = SLPFindAttrs(
      hslp, 
      urlFoundService.c_str(),
      //filterAttributes.c_str(), /*"attr1,attr2", /* return attr1 and attr1 only */ 
      "",
      "", /* use configured scopes*/
      filterAttrCallback, 
      &foundAttributesStr);

   if(result != SLP_OK)
   { 
      // given set of metadata for filtering does not match the attributes of found service
      return false; 
   }

   std::multimap< string, string> foundAttributesMultimap;

   DiscoverySlpUtil::attrList2Metada(foundAttributesStr, foundAttributesMultimap);
      
   bool attributesMatch = compareAttributes(taskFindSrvs->getFilterAttributes(), foundAttributesMultimap);

   //retrieve mandatory attributes if the found service matches the filter attributes
   if(attributesMatch)
   {
      DiscoverySlpUtil::attrList2MetadaMandatoryAttrsOnly(foundAttributesMultimap, mandatoryattributes);
   }

   SLPClose(hslp);
   return attributesMatch;
}


bool TrentinoDiscoverySlp::checkOutFilterMetaData ( Trentino::Discovery::DiscoveryTaskFindSrv* taskFindSrvs,
   std::string urlFoundService,
   Trentino::SCA::Model::Metadata& mandatoryattributes)
{
   SLPError    result; 
   SLPHandle hslp;
   SLPError    err;

   // as the second attribute is false SLPFindAttrs will work synchronously
   // (SLPHandle will be opened for asynchronous operation)
   // in other words function will not return unless the callback func is 
   // called, code is relying on this
   err = SLPOpen("en", SLP_FALSE, &hslp); 

   if(err != SLP_OK)
   {
      return false;
   }

   unsigned index = urlFoundService.find("://localhost");
   urlFoundService.erase(index, std::string::npos);


   string foundAttributesStr;
   // check out filtered attributes
   result = SLPFindAttrs(
      hslp, 
      urlFoundService.c_str(),
      //filterAttributes.c_str(), /*"attr1,attr2", /* return attr1 and attr1 only */ 
      "",
      "", /* use configured scopes*/
      filterAttrCallback, 
      &foundAttributesStr);

   if(result != SLP_OK)
   { 
      // given set of metadata for filtering does not match the attributes of found service
      return false; 
   }

   std::multimap< string, string> foundAttributesMultimap;

   DiscoverySlpUtil::attrList2Metada(foundAttributesStr, foundAttributesMultimap);

   bool attributesMatch = compareAttributes(taskFindSrvs->getFilterAttributes(), foundAttributesMultimap);

   //retrieve mandatory attributes if the found service matches the filter attributes
   if(attributesMatch)
   {
      DiscoverySlpUtil::attrList2MetadaMandatoryAttrsOnly(foundAttributesMultimap, mandatoryattributes);
   }

   SLPClose(hslp);
   return attributesMatch;
}

SLPBoolean TrentinoDiscoverySlp::filterAttrCallback(
   SLPHandle /*hslp*/, 
   const char* attrlist, 
   SLPError errcode, 
   void* cookie ) 
{ 

   //boost::shared_ptr<Trentino::Discovery::DiscoveryTaskFindSrv>* taskFindSrvsPtr = static_cast< boost::shared_ptr<Trentino::Discovery::DiscoveryTaskFindSrv>* >(cookie);
   //boost::shared_ptr<Trentino::Discovery::DiscoveryTaskFindSrv> taskFindSrvs = *taskFindSrvsPtr;

   string* foundAttributesStr = static_cast<string*> (cookie);

   if(errcode == SLP_OK) 
   { 
      foundAttributesStr->assign(attrlist);

      return SLP_TRUE; 
   }

   return SLP_FALSE; 
} 


//std::string TrentinoDiscoverySlp::getFilterAttributes(FinsSrvsTaskPtr findSrvsTaskPtr)
//{
//   
//   std::string retVal = DiscoverySlpUtil::metada2AttrListNamesOnly(findSrvsTaskPtr->getFilterAttributes());
//   return retVal;
//}

bool TrentinoDiscoverySlp::compareAttributes(Trentino::Discovery::ConstMetadataConstSharedPtr filterMetadata, 
   multimap< string, 
   string>& attributesMultiMap)
{
   const std::vector< boost::shared_ptr<MetadataStringAttribute> >&  attributes = filterMetadata->stringAttributesElements();
   int sizeOfAttributes = attributes.size();
   for(int i = 0; i < sizeOfAttributes; i++)
   {
      std::multimap<string, string>::iterator it = attributesMultiMap.find(attributes[i]->name());
      if(it == attributesMultiMap.end())
      {
         return false;
      }

      if(it->second.compare(attributes[i]->value()) != 0)
      {
         return false;
      }
   }
   return true;
}


TrentinoDiscoverySlp& TrentinoDiscoverySlp::getInstance(void) 
{ 
   return mInstanceDiscoverySlp; 
}  


extern "C" TRENTINO_DLLEXPORT Trentino::Discovery::DiscoveryMethodInterface* TRENTINO_CDECL getDiscoveryMethodInterface()
{
   return (Trentino::Discovery::DiscoveryMethodInterface*) &(TrentinoDiscoverySlp::getInstance());
}
