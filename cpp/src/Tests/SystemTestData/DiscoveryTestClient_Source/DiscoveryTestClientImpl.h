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

#ifndef DiscoveryTestClientImplH
#define DiscoveryTestClientImplH


//specific
#include "services/DiscoveryTestServer.h"


#ifdef WIN32
   #ifdef DiscoveryTestClient_EXPORTS
      #undef DiscoveryTestClient_IMPORT_EXPORT
      #define DiscoveryTestClient_IMPORT_EXPORT __declspec(dllexport)
   #else
      #undef DiscoveryTestClient_IMPORT_EXPORT
      //#define DiscoveryTestClient_IMPORT_EXPORT __declspec(dllimport)       
      #define DiscoveryTestClient_IMPORT_EXPORT     
   #endif //DiscoveryTestClient_EXPORTS
   #else
      #define DiscoveryTestClient_IMPORT_EXPORT
#endif //WIN32

#ifndef nullptr
   #define nullptr 0
#endif



namespace Trentino{
namespace Example{

   class DiscoveryTestClient_IMPORT_EXPORT DiscoveryTestClientImpl 
   {
   public:
      DiscoveryTestClientImpl();
      virtual ~DiscoveryTestClientImpl();

	  virtual void setDiscoveryTestServerRef(DiscoveryTestServer* server);
	  //lifecycle methods
	  void onInit();
      
      void callTheService(void);
      void setColor(const std::string color);
      void start(void);
   private :
		DiscoveryTestServer* mDiscoveryTestServer;
      std::string mColor;

   };//class BasicPrinterClientImpl

}//namespace Example
}//namespace Trentino



#endif //TrentinoExampleBasicPrinterClientCalculatorH