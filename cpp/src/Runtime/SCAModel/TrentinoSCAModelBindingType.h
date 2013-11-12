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

#ifndef TrentinoSCAModelBindingTypeH
#define TrentinoSCAModelBindingTypeH
//baseclass
#include "TrentinoSCAModelCommonExtensionBase.h"
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class BindingType : public CommonExtensionBase
   {
      //construction
   public:
      BindingType();
   private:
      BindingType(const BindingType&);
      void operator=(const BindingType&);

      //services
   public:



      //element accessors  
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addContentElement(const char* aContent);
     const std::vector<std::string>& contentElements() const;

      //attribute accessors
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addAlwaysProvides(Trentino::XML::Schema::QName* aAlwaysProvides);
     const std::vector<QNamePtr>& alwaysProvides() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addMayProvide(Trentino::XML::Schema::QName* aMayProvide);
     const std::vector<QNamePtr>& mayProvides() const;

      QNamePtr type() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setType(Trentino::XML::Schema::QName* aType);


      //data
   protected:
      //elements
      std::vector<std::string> mContentElements;
 
      //attributes
      std::vector<QNamePtr> mAlwaysProvides;
      std::vector<QNamePtr> mMayProvides;
      QNamePtr mType;
   }; //class  BindingType

   #include "TrentinoSCAModelBindingType.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelBindingTypeH
