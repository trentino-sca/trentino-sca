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

#ifndef TrentinoSCAModelWireH
#define TrentinoSCAModelWireH
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
   class Wire : public CommonExtensionBase
   {
      //construction
   public:
      Wire();
   private:
      Wire(const Wire&);
      void operator=(const Wire&);

      //services
   public:



      //element accessors  
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addContentElement(const char* aContent);
     const std::vector<std::string>& contentElements() const;

      //attribute accessors
      bool isReplace() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setReplace(bool isReplace);
      const Trentino::XML::Schema::AnyURI& source() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setSource(const char* aSource);
      const Trentino::XML::Schema::AnyURI& target() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setTarget(const char* aTarget);


      //data
   protected:
      //elements
      std::vector<std::string> mContentElements;
 
      //attributes
      bool mIsReplace;
      Trentino::XML::Schema::AnyURI mSource;   
      Trentino::XML::Schema::AnyURI mTarget;   
   }; //class  Wire

   #include "TrentinoSCAModelWire.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelWireH
