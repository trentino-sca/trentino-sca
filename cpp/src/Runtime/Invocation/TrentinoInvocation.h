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
#ifndef TrentinoInvocationH
#define TrentinoInvocationH

//standard
#include <boost/shared_ptr.hpp>
#include <vector>

#ifdef WIN32
   #ifdef INVOCATION_EXPORTS
      #define INVOCATION_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define INVOCATION_IMPORT_EXPORT __declspec(dllimport)       
   #endif //INVOCATION_EXPORTS
#else
   #define INVOCATION_IMPORT_EXPORT
#endif //WIN32

namespace Trentino{
//! \defgroup Invocation
namespace Invocation
{
   class InvokerBase;
   
	typedef boost::shared_ptr<InvokerBase> InvokerPtr;

   namespace Filtering
   {
      class Filter;
      class FilterChain;
	   class FilterConfig;

      typedef boost::shared_ptr<Filter> FilterPtr;
	   typedef boost::shared_ptr<FilterChain> FilterChainPtr;
	   typedef boost::shared_ptr<FilterConfig> FilterConfigPtr;
   } //namespace Filtering
      
   class InvocationContext;
   class InvocationData;
   class ServiceInvocationWrapperBase;
   class InvocationException;
      
   typedef boost::shared_ptr<InvocationContext> InvocationContextPtr;
   typedef boost::shared_ptr<InvocationData> InvocationDataPtr;  
   typedef boost::shared_ptr<ServiceInvocationWrapperBase> ServiceInvocationWrapperBasePtr;
   typedef std::vector<void*> Parameters;

} //namespace Invocation
} //namespace Trentino

#endif //TrentinoInvocationH
