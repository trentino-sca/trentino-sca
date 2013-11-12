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
#include "TrentinoRuntimeModelWire.h"

//standard
#include <queue>
#include <boost/foreach.hpp>

//specific
#include "../../Global/TrentinoGlobal.h"
#include "TrentinoRuntimeModelReference.h"
#include "TrentinoRuntimeModelService.h"
#include "TrentinoRuntimeModelWireable.h"
#include "TrentinoRuntimeModelComponent.h"

using namespace std;
using Trentino::RuntimeModel::Wire;
namespace RuntimeModel = Trentino::RuntimeModel;

//class Wire
   //construction
Wire::Wire( const RuntimeModel::ReferenceBasePtr& reference
          , const RuntimeModel::ServiceBasePtr& service)
: mOriginalReference(reference)
, mOriginalService(service)
, mWired(false)
{}

Wire::~Wire()
{
   if(mWired)
      unwire();
}

   //services
RuntimeModel::WirePtr Wire::create( const RuntimeModel::ReferenceBasePtr& reference
                                  , const RuntimeModel::ServiceBasePtr& service)
{
   //cannot use boost::make_shared because Wire's constructor is private
   return RuntimeModel::WirePtr(new Wire(reference, service));   
}

void Wire::wire()
{
   if(mWired)
      return;

   //attach wire to reference
   const RuntimeModel::ReferenceBasePtr reference = mOriginalReference.lock();
   assert(reference);  
   queue<RuntimeModel::ReferenceBaseWeakPtr> toVisit;
   toVisit.push(reference);      
   do
   {  
      const RuntimeModel::ReferenceBasePtr ref = toVisit.front().lock();
      assert(ref);      
      toVisit.pop();
      ref->wireableSupport().attatchWire(shared_from_this());      

      BOOST_FOREACH(const RuntimeModel::ReferenceBaseWeakPtr& promotedRef, ref->promotedTo() )
      {
         toVisit.push(promotedRef);
      }
   }while(!toVisit.empty());

   //attach wire to service   
   RuntimeModel::ServiceBasePtr service = mOriginalService.lock();  
   assert(service);
   do
   {
      service->wireableSupport().attatchWire(shared_from_this());
      mFinalService = service->component().lock()->name()+"/"+service->name();
      service = service->promotedTo().lock();
   }while(service);

   mWired = true;
}

//void Wire::rewire(const ServiceBasePtr& newService)
//{
//   const ServiceBasePtr service = mService.lock();   
//   if(service)
//   {      
//      service->wireableSupport().detatchWire(shared_from_this());      
//   }
//  
//   service->wireableSupport().attatchWire(shared_from_this());  
//   mService = newService;   
//}
void Wire::unwire()
{
   if(!mWired)
      return;

   const RuntimeModel::ReferenceBasePtr reference = mOriginalReference.lock(); 
   if(!reference)
      return;

   queue<RuntimeModel::ReferenceBaseWeakPtr> toVisit;
   toVisit.push(reference);      
   do
   {  
      const RuntimeModel::ReferenceBasePtr ref = toVisit.front().lock();
      assert(ref);      
      toVisit.pop();
      ref->wireableSupport().detatchWire(shared_from_this());      

      BOOST_FOREACH(const RuntimeModel::ReferenceBaseWeakPtr& promotedRef, ref->promotedTo() )
      {
         toVisit.push(promotedRef);
      }
   }while(!toVisit.empty());

   mOriginalReference.reset();
   unwireService();

   mWired = false;
}

void Wire::unwireService()
{
   if(!mWired)
      return;

   RuntimeModel::ServiceBasePtr service = mOriginalService.lock();   
   if(!service)
      return;

   do
   {
      service->wireableSupport().detatchWire(shared_from_this());      
      service = service->promotedTo().lock();
   }while(service);         
   
   mOriginalService.reset();
}



RuntimeModel::ReferenceBaseWeakPtr Wire::reference() const
{
   return mOriginalReference;
}

const std::string& Wire::service() const
{
   return mFinalService;
}

RuntimeModel::ServiceBaseWeakPtr Wire::originalService() const
{
   return mOriginalService;
}

Trentino::Invocation::InvocationContextPtr Wire::invocationContext() const
{
   return mInvocationContext;
}

void Wire::setInvocationContext(const Trentino::Invocation::InvocationContextPtr& invocationContext)
{
   mInvocationContext = invocationContext;
}

void Wire::setProxy(const RuntimeModel::ProxyPtr& proxy)
{
   mProxy = proxy;
}

RuntimeModel::ProxyPtr Wire::proxy() const
{
   return mProxy;
}
