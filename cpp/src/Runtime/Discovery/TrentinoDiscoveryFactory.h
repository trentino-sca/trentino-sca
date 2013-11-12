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

#ifndef TrentinoDiscoveryFactoryH
#define TrentinoDiscoveryFactoryH

//standard
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

//specific
#include "TrentinoDiscoveryManagementInterface.h"
#include "../../Utils/TrentinoUtilsLogging.h"
#include "../../Utils/TrentinoUtilsDynamicLibrary.h"


namespace Trentino{
//! \defgroup Discovery
namespace Discovery
{
   class DiscoveryMethodInterface;
   class DiscoveryInterface;
   const std::string GetDiscoveryMethodInterfaceFuncName = "getDiscoveryMethodInterface";
   typedef DiscoveryMethodInterface* (TRENTINO_CDECL *getDiscoveryMethodInterfaceFunc)  ();

   typedef DiscoveryInterface* (*GetDiscoveryInterfaceFn)(void); 
      

   //class declaration

   //**********************************************************************************************
   //                             DiscoveryFactory
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief Class for creating discovery implementations and passing them the appropriate 
   //! discovery dll
   //**********************************************************************************************
   class DiscoveryFactory :public DiscoveryManagementInterface
   { 
      //additionals
   private:
      enum DiscoveryFactoryStates
      {
         NOT_STARTED,
         STARTED
      };
      //construction
   private:
      //****************************************************************************************
      //                                DiscoveryFactory()
      //****************************************************************************************
      //! \brief Disallow construction.  
      //****************************************************************************************
      DiscoveryFactory(); 

      //****************************************************************************************
      //                                !DiscoveryFactory()
      //****************************************************************************************
      //! \brief Disallow distuction.  
      //****************************************************************************************
      ~DiscoveryFactory() 
      { 
        // stop();
         if(mDiscoveryInterface != nullptr)
            assert(false);
         
         //mDiscoveryDll->unload();
         //mDiscoveryDll.reset();
         //m_FactoryMap.clear(); 
      }

      //****************************************************************************************
      //                                DiscoveryFactory()
      //****************************************************************************************
      //! \brief Disallow copy construction.  
      //****************************************************************************************
      DiscoveryFactory(const DiscoveryFactory &) 
      { 
      }

      //operators
   private:
      //****************************************************************************************
      //                                operator=()
      //****************************************************************************************
      //! \brief Disallow assignment
      //****************************************************************************************
      DiscoveryFactory &operator=(const DiscoveryFactory &);
 
      //services
   public:
      //****************************************************************************************
      //                                GetDiscoveryManagementInterface
      //****************************************************************************************
      //! \brief Return a pointer to the ManagemenInterface 
      //****************************************************************************************
      static DiscoveryManagementInterface* getDiscoveryManagementInterface(DiscoveryMethod chosenDiscoveryMethod);

      //****************************************************************************************
      //                                onDiscoveryLayerStopped
      //****************************************************************************************
      //! \brief Callback function to be passed to the discovery layer to get the notification of 
      //! ending stop task
      //****************************************************************************************
      void onDiscoveryLayerStopped();
   
   private:
      
      // Discovery Framework Management Functions to be accessed via base class(DiscoveryManagementInterface)
      // (see documentation in DiscoveryManagementInterface)
      void start(bool isDA, int retryCount,int retryInterval, onDiscoveryStartCBPtr discoveryTaskCB);
      void stop(bool isDA); 


      Trentino::Discovery::DiscoveryInterfacePtr getDiscoveryInterface();
  
      //internal management functions
      void setDynamicLibrary(const Trentino::Utils::DynamicLibraryPtr& dll ) 
      {
	      mDiscoveryDll=dll;
      }

      //void registerDiscoveryMethod(DiscoveryMethod discoveryMethod, GetDiscoveryInterfaceFn pfnCreate);
      

      //data members
   private:  
      //typedef map<DiscoveryMethod,GetDiscoveryInterfaceFn> FactoryMap;
      // typedef map<DiscoveryMethod,DiscoveryInterface*> FactoryMap;
      //FactoryMap m_FactoryMap;
     
      //GetDiscoveryInterfaceFn mDiscoveryInterface;
      
      //! Discovery interface wrapping the current discoverydll
      DiscoveryInterface* mDiscoveryInterface;

      //! current discoveryMethod (i.e SLP)
      static DiscoveryMethod mDiscoveryMethod;
      
      //! current active dll
      Trentino::Utils::DynamicLibraryPtr mDiscoveryDll;

      //! Array that keeps the names of the Discovery method dlls currently used
      const char* mDiscoveryMethodDllNames[1];

      //! Keeps the state of DiscoveryFramework : STARTED or NOT_STARTED
      DiscoveryFactoryStates mDiscoveryFrameworkState;

      // main instance of the singleton
      static DiscoveryFactory *mInstance;

      static bool mInstantiated;
 
   }; // class DiscoveryFactory


} // namespace Discovery
} // namespace Trentino
#endif //TrentinoDiscoveryFactoryH