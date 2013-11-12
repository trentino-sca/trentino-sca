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

#ifndef TrentinoSCAModelEnumH
#define TrentinoSCAModelEnumH

//specific
#include "TrentinoSCAModel.h"

namespace Trentino{
namespace SCA{
namespace Model
{
   class Enum
   {
      //construction
   public:
      Enum();      
   private:
      Enum(const Enum&);
      void operator=(const Enum&);

      //services
   public:
      virtual const Trentino::XML::Schema::QName& xsdType() const;

      //element accessors  
      int ordinalElement() const;
      void setOrdinal(int ordinal);
      const std::string& nameElement() const;
      void setName(const std::string& name);

      //data
   protected:
      //elements
      int mOrdinalElement;
      std::string mNameElement;
 
   }; //class  Enum

   #include "TrentinoSCAModelEnum.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino 
 
 #endif
