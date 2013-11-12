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

#ifndef TrentinoUtilsURIH
#define TrentinoUtilsURIH
//standard
#include <vector>


//specific
#include "TrentinoUtilsUriHelper.h"

//standard
#include <string>

namespace Trentino{
namespace Utils
{
   typedef std::string URI;

   class URIUTIL_IMPORT_EXPORT URIUtil {

   //constructors
   //services
   //****************************************************************************************************
   //                                         getPartsOfURI()
   //****************************************************************************************************
   //! \brief Given the structural URI of an entity belonging to a component (e.g service, reference and property),
   //! return a vector containing as first parameter the name of the entity, and as second parameter the
   //! component URI
   //! \param const std::string & aURI: The STRUCTURAL of the entity
   //! \return std::vector<std::string> vector wit two values. The fist is a entity name, the second is a
   //! the component URI 
   //****************************************************************************************************
      //services
   public:
     static std::vector<std::string> getNameAndComponentURIByEntityURI(const URI& aURI);
   }; //class URIUtil

} //namespace Utils
} //namespace Trentino

#endif //TrentinoUtilsURIH
