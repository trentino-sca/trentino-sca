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
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace Trentino::Example;


class Periodic_caller{

public:
    static void add_callee(DiscoveryTestClientImpl *c);
    static void start(void);
    static void stop(void);
private:

    static void handler(const boost::system::error_code& error  );
    static void thread_func(void);

    static std::vector<DiscoveryTestClientImpl *> callee;
    static std::vector<DiscoveryTestClientImpl *>::iterator it;
    
    static boost::asio::io_service *io;
    static boost::asio::deadline_timer *timer;
    static bool started;
    static boost::thread *bt;
    static boost::mutex mMutex;
};

    std::vector<DiscoveryTestClientImpl *> Periodic_caller::callee;
    std::vector<DiscoveryTestClientImpl *>::iterator Periodic_caller::it;
    boost::asio::io_service *Periodic_caller::io = nullptr;
    //boost::asio::deadline_timer* Periodic_caller::t;
    boost::asio::deadline_timer *Periodic_caller::timer = nullptr;
    
    bool Periodic_caller::started = false;
    boost::thread * Periodic_caller::bt;
    boost::mutex Periodic_caller::mMutex;

void Periodic_caller::add_callee(DiscoveryTestClientImpl *c)
{
    mMutex.lock();
    callee.push_back(c);
    it = callee.begin();
    if (callee.size() >= 3) start() ;
    mMutex.unlock();
}



void Periodic_caller::handler(const boost::system::error_code& error)
{
#if 1
   mMutex.lock();
   if (started)
   {
      (*it)->callTheService();
      ++it;
      if(it == callee.end())
      {
        it = callee.begin();
      }
      timer->expires_from_now(boost::posix_time::seconds( 5 ));
      timer->async_wait(&Periodic_caller::handler);
   mMutex.unlock();
    //io.run();
   }
#endif    
}

void Periodic_caller::thread_func(void)
{
   io->run();

   std::cout<< "Thread stopped" << std::endl;
}

void Periodic_caller::start(void)
{
   if(!started)
   {
      started = true;
      if (timer == nullptr) 
      {  
         io = new boost::asio::io_service();
         timer = new boost::asio::deadline_timer(*io);
      }
      timer->expires_from_now(boost::posix_time::seconds( 5 ));
      timer->async_wait(&Periodic_caller::handler);
      bt = new boost::thread(Periodic_caller::thread_func);
   }

}

void Periodic_caller::stop(void)
{
   mMutex.lock();
   if( started)
   {
      started = false;
      io->stop();
      delete timer;
      delete io;
   }
   mMutex.unlock();
}

//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================

DiscoveryTestClientImpl::DiscoveryTestClientImpl()
{
   mDiscoveryTestServer = nullptr;
   Periodic_caller::add_callee(this);
}

DiscoveryTestClientImpl::~DiscoveryTestClientImpl()
{
   //does nothing here
   
   Periodic_caller::stop();
}

void DiscoveryTestClientImpl::setDiscoveryTestServerRef(DiscoveryTestServer* server)
{
	mDiscoveryTestServer = server;
}

void DiscoveryTestClientImpl::onInit()
{
	     try{
		 
		  std::cout << "Calling initialization method "<< std::endl;	

		 }
		 catch(std::runtime_error& e){
		 std::cout << "Unexpected error during remote access of BasicPrinter Service " << e.what()<< std::endl;
		 }catch (...){
		 std::cout << "Unexpected error during remote access of BasicPrinter Service "<< std::endl;
		 }
}

void DiscoveryTestClientImpl::callTheService(void )
{
    std::cout << "Client: " << mColor << ": ";
    
    if(mDiscoveryTestServer != nullptr)
    {
        try{
		  mDiscoveryTestServer->doTheJob(mColor);
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

void DiscoveryTestClientImpl::setColor(const std::string color)
{
      mColor = color;
}

void DiscoveryTestClientImpl::start(void)
{

   Periodic_caller::start();

}
