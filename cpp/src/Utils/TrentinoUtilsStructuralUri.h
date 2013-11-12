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

#ifndef TrentinoUtilsStructuralUriH
#define TrentinoUtilsStructuralUriH

//specific
#include "TrentinoUtilsUriHelper.h"

//standard
#include <string>

namespace Trentino{
namespace Utils
{
   class URIUTIL_IMPORT_EXPORT StructuralUri
   {
      //construction
   public:
      explicit StructuralUri(const std::string& uri);
      StructuralUri(const StructuralUri& source);
      StructuralUri();
   private:
      StructuralUri(const UriHelper& uriHelper);
      //operators
   public:
      const StructuralUri& operator=(const StructuralUri& source);

      //services
   public:
      bool isReferenceUri() const;
      bool isReferenceBindingUri() const;
      bool isPropertyUri() const;
      bool isServiceUri() const;
      bool isServiceBindingUri() const;
      bool isComponentUri() const;
      StructuralUri parent() const;
      std::string name() const;
      std::string toString() const;

      //management
   private:
      std::string trimFragment(const std::string& element) const;
      //data
   private:
      UriHelper mUriHelper;
   }; //class StructuralUri

} //namespace Utils
} //namespace Trentino


#endif//TrentinoUtilsStructuralUriH
