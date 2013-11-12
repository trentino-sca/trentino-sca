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

#ifndef TrentinoSCAModelSCAPropertyBaseH
#define TrentinoSCAModelSCAPropertyBaseH
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class SCAPropertyBase
   {
      //construction
   public:
      SCAPropertyBase();
   private:
      SCAPropertyBase(const SCAPropertyBase&);
      void operator=(const SCAPropertyBase&);

      //services
   public:



      //element accessors  
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addContentElement(const char* aContent);
     const std::vector<std::string>& contentElements() const;

      //attribute accessors
      QNamePtr element() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setElement(Trentino::XML::Schema::QName* aElement);
      bool isMany() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setMany(bool isMany);
      const Trentino::XML::Schema::NCName& name() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setName(const char* aName);
      QNamePtr type() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setType(Trentino::XML::Schema::QName* aType);
      const std::string& value() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setValue(const char* aValue);


      //data
   protected:
      //elements
      std::vector<std::string> mContentElements;
 
      //attributes
      QNamePtr mElement;
      bool mIsMany;
      Trentino::XML::Schema::NCName mName;   
      QNamePtr mType;
      std::string mValue;
   }; //class  SCAPropertyBase

   #include "TrentinoSCAModelSCAPropertyBase.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelSCAPropertyBaseH
