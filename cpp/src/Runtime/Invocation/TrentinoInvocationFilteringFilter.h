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

#ifndef TrentinoInvocationFilteringFilterH
#define TrentinoInvocationFilteringFilterH

#include <boost/shared_ptr.hpp>


//specific
#include "TrentinoAPIInvocationContext.h"
#include "TrentinoAPIInvocationData.h"
#include "TrentinoAPIInvocationException.h"

namespace Trentino{
namespace Invocation{
namespace Filtering
{		
	//class declaration
   //**********************************************************************************************
   //                                  Filter 
   //**********************************************************************************************
   //! \ingroup Invocation
   //! \brief Filtering class.
   //**********************************************************************************************
   class Filter 
   {
   public:
      //*******************************************************************************************
      //                            init()
      //*******************************************************************************************
      //! Called by the container to indicate to a filter that it is being
      //! placed into service. The container calls the init method exactly
      //! once after instantiating the filter. The init method must complete
      //! successfully before the filter is asked to do any filtering work.
      //!       
      //! The container cannot place the filter into service if the init method
      //! either 1.Throws a InvocationException 2.Does not return within a time period
      //! defined by the container
      //! 
      //! \param filterConfig
      //*******************************************************************************************
      virtual void init(const FilterConfigPtr& filterConfig);

      //*******************************************************************************************
      //                            doFilter()
      //*******************************************************************************************
      //! The doFilter method of the Filter is called by the container each time a
      //! request/response pair is passed through the chain due to a client request
      //! for a resource at the end of the chain. The FilterChain passed in to this
      //! method allows the Filter to pass on the request and response to the next
      //! entity in the chain.
      //!  
      //! A typical implementation of this method would follow the following
      //! pattern:- 1. Examine the request 2. Optionally wrap the request object
      //! with a custom implementation to filter content or headers for input
      //! filtering 3. Optionally wrap the response object with a custom
      //! implementation to filter content or headers for output filtering 4. a)
      //! Either invoke the next entity in the chain using the FilterChain object
      //! (chain.doFilter()), 4. b) or not pass on the request/response pair to the
      //! next entity in the filter chain to block the request processing 5.
      //! Directly set headers on the response after invokation of the next entity
      //! in ther filter chain.
      //!  
      //! \param[in] data
      //! \param[in] ctx
      //! \param[in] chain
      //*******************************************************************************************
      virtual  void doFilter(const Trentino::Invocation::InvocationDataPtr& data, 
                             const Trentino::Invocation::InvocationContextPtr ctx,
	                          const FilterChainPtr& chain) = 0;

      //*******************************************************************************************
      //                            destroy()
      //*******************************************************************************************
      //! Called by the web container to indicate to a filter that it is being
      //! taken out of service. This method is only called once all threads within
      //! the filter's doFilter method have exited or after a timeout period has
      //! passed. After the web container calls this method, it will not call the
      //! doFilter method again on this instance of the filter.
      //!  
      //! This method gives the filter an opportunity to clean up any resources
      //! that are being held (for example, memory, file handles, threads) and make
      //! sure that any persistent state is synchronized with the filter's current
      //! state in memory.
      //*******************************************************************************************
      virtual void destroy() = 0;
	}; //class Filter 

	//class declaration
   //**********************************************************************************************
   //                                  FilterChain 
   //**********************************************************************************************
   //! \ingroup Invocation
   //! \brief Filter chain class.
   //! \todo move class in separate file
   //**********************************************************************************************
   class FilterChain 
   {
	public :
      //*******************************************************************************************
      //                         doFilter()
      //*******************************************************************************************
      //! Execute the filters defined in this chain.
      //! \param[in] Shared_ptr of InvocationData.
      //! \param[in] Shared_ptr of InvocationContext.
      //*******************************************************************************************
		virtual void doFilter(Trentino::Invocation::InvocationDataPtr& data, 
                            Trentino::Invocation::InvocationContextPtr& ctx) = 0;
	}; //class FilterChain 
	
	//class declaration
   //**********************************************************************************************
   //                                  FilterConfig
   //**********************************************************************************************
   //! \ingroup Invocation
   //! \brief Filter config class.
   //! \todo move class in separate file
   //**********************************************************************************************
   class FilterConfig 
   {
   public:
      //*******************************************************************************************
      //                        filterName()
      //*******************************************************************************************
      //! Returns filtername.
      //! \return Name of filter.
      //*******************************************************************************************
	   virtual std::string filterName() const = 0;
	}; //class FilterConfig 

}//namespace Filtefing
}//namespace Invocation
}//namespace Trentino

#endif //TrentinoInvocationFilteringFilterH
