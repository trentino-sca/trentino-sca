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

#ifndef TrentinoDiscoveryFoundServiceH
#define TrentinoDiscoveryFoundServiceH

// standart
#include <string>

// specific
#include "../SCAModel/TrentinoSCAModelMetadata.h"


namespace Trentino{
namespace Discovery
{
   
   //class declaration
   //**********************************************************************************************
   //                             DiscoveryFoundService
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief Keeps one of the services found based on the findserver request of runtime core
   //
   //**********************************************************************************************
   class DiscoveryFoundService
   {
      //additional
   private:
     typedef boost::shared_ptr<Trentino::SCA::Model::Metadata> MetadataSharedPtr;
      //construction
   public:
      DiscoveryFoundService(std::string serviceUrl, MetadataSharedPtr metaDatas);
      DiscoveryFoundService(std::string serviceUrl, Trentino::SCA::Model::Metadata& metaDatas);
      DiscoveryFoundService(std::string){};
      virtual ~DiscoveryFoundService();

      std::string getServiceUrl()
      {
         return mServiceUrl;
      }
      // services
   public:
      MetadataSharedPtr mMetaDatasOfService;
            
      //data
   private:
      std::string mServiceUrl;

   }; // class DiscoveryFoundService


} // namespace Discovery
} // namespace Trentino
#endif //TrentinoDiscoveryFoundServiceH