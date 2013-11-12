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

#ifndef TrentinoSCAComponentContextH
#define TrentinoSCAComponentContextH

//standard
#include <string>
#include <vector>
#include <boost/thread/tss.hpp>

//specific
#include "./../../Global/TrentinoGlobal.h"
#include "./../Oasis/sca/ComponentContext.h"
#include "TrentinoCoreDomain.h"

namespace Trentino{
namespace Core
{
   class SCAComponentContext : public oasis::sca::ComponentContext
   {
      //construction
   public:
      OASISSCA_IMPORT_EXPORT SCAComponentContext();
      OASISSCA_IMPORT_EXPORT SCAComponentContext(std::string uri);
      virtual ~SCAComponentContext();
      //services
   public:
      virtual std::string getURI() const;

      virtual oasis::sca::ServiceProxyPtr getService(const std::string& referenceName) const;

      virtual std::vector<oasis::sca::ServiceProxyPtr> getServices
         (const std::string& referenceName) const;

      virtual oasis::sca::ServiceReferencePtr getServiceReference
         (const std::string& referenceName) const;

      virtual std::vector<oasis::sca::ServiceReferencePtr> getServiceReferences
         (const std::string& referenceName) const;

      virtual oasis::sca::ServiceReferencePtr getSelfReference() const;

      virtual oasis::sca::ServiceReferencePtr getSelfReference(const std::string& serviceName) const;

      virtual uint32_t addRef();
      virtual uint32_t releaseRef();

      static OASISSCA_IMPORT_EXPORT void setCurrent(oasis::sca::ComponentContextPtr componentPtr = 
         oasis::sca::ComponentContextPtr());
      static oasis::sca::ComponentContextPtr current();
      //data
   private:
      uint32_t mRefCount;
      std::string mUri;
      static boost::thread_specific_ptr<oasis::sca::ComponentContextPtr> ComponentContext;
   }; //class SCAComponentContext

} //namespace Core
} //namespace Trentino

#endif //TrentinoSCAComponentContextH
