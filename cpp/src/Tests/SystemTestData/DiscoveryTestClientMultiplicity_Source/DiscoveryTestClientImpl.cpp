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

#define TRENTINO_EXAMPLE_DiscoveryTestClient_IMPORT_EXPORT

//specific
#include "DiscoveryTestClientImpl.h"
#include <iostream>


using namespace Trentino::Example;



//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================

DiscoveryTestClientImpl::DiscoveryTestClientImpl()
{

}

DiscoveryTestClientImpl::~DiscoveryTestClientImpl()
{
   //does nothing here
   
}

void DiscoveryTestClientImpl::setDiscoveryTestServerRef(std::list<DiscoveryTestServer*> server)
{
	mDiscoveryTestServer = server;
}

void DiscoveryTestClientImpl::onInit()
{		 
		  std::cout << "Calling initialization method "<< std::endl;	
}

void DiscoveryTestClientImpl::callTheService(void )
{
    
   if(mDiscoveryTestServer.size() > 0)
    {
        try{
         for (std::list<DiscoveryTestServer*>::iterator it = mDiscoveryTestServer.begin(); it != mDiscoveryTestServer.end(); it++)
            (*it)->doTheJob("");

		 }
		 catch(std::runtime_error& e){
		 std::cout << "Unexpected error during remote access of Service " << e.what()<< std::endl;
		 }catch (...){
		 std::cout << "Unexpected error during remote access of Service "<< std::endl;
		 }
        
    }
    else
    {
        std::cout << "No server injected";
    }
    std::cout << std::endl;

    
    
}
