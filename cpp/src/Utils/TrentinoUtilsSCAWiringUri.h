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

#ifndef TrentinoUtilsWiringUriH
#define TrentinoUtilsWiringUriH

//specific
#include "TrentinoUtilsUriHelper.h"

//standard
#include <string>

namespace Trentino{
namespace Utils
{
   class URIUTIL_IMPORT_EXPORT SCAWiringUri
   {
      //construction
   public:
      explicit SCAWiringUri(const std::string& uri);
      SCAWiringUri(const SCAWiringUri& source);
   private:
      SCAWiringUri(const UriHelper& uriHelper);
      //operators
   public:
      const SCAWiringUri& operator=(const SCAWiringUri& source);

      //services
   public:
      std::string serviceOrReferenceName() const;
      std::string componentName() const;
      bool hasServiceOrReferenceName() const;
      SCAWiringUri parent() const;
      std::string name() const;
      
      //data
   private:
      UriHelper mUriHelper;
   }; //class SCAWiringUri

} //namespace Utils
} //namespace Trentino


#endif//TrentinoUtilsWiringUriH
