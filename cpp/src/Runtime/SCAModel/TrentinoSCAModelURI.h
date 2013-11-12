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

#ifndef TrentinoSCAModelURIH
#define TrentinoSCAModelURIH

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class URI
   {
      //construction
   public:
      URI();
   private:
      URI(const URI&);
      void operator=(const URI&);

      //services
   public:



      //element accessors  
      const Trentino::XML::Schema::AnyURI& valueElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setValue(const char* aValue);



      //data
   protected:
      //elements
      Trentino::XML::Schema::AnyURI mValueElement;   
 
   }; //class  URI

   #include "TrentinoSCAModelURI.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelURIH
