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

#ifndef TrentinoSCAModelMetadataStringAttributeH
#define TrentinoSCAModelMetadataStringAttributeH

//specific
#include "TrentinoSCAModel.h"

 
namespace Trentino{
namespace SCA{
namespace Model
{
   class MetadataStringAttribute
   {
      //construction
   public:
      SCAMODEL_IMPORT_EXPORT  MetadataStringAttribute();
   private:
      MetadataStringAttribute(const MetadataStringAttribute&);
      void operator=(const MetadataStringAttribute&);

      //services
   public:



      //attribute accessors
      const std::string& name() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setName(const char* aName);
      const std::string& value() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setValue(const char* aValue);


      //data
   protected:
 
      //attributes
      std::string mName;
      std::string mValue;
   }; //class  MetadataStringAttribute

   #include "TrentinoSCAModelMetadataStringAttribute.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelMetadataStringAttributeH
