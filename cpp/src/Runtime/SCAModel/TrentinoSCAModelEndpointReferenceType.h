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

#ifndef TrentinoSCAModelEndpointReferenceTypeH
#define TrentinoSCAModelEndpointReferenceTypeH
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class EndpointReferenceType
   {
      //construction
   public:
      EndpointReferenceType();
   private:
      EndpointReferenceType(const EndpointReferenceType&);
      void operator=(const EndpointReferenceType&);

      //services
   public:



      //element accessors  
      AttributedURITypePtr addressElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setAddress(AttributedURIType* aAddress);
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addContentElement(const char* aContent);
     const std::vector<std::string>& contentElements() const;
      MetadataTypePtr metadataElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setMetadata(MetadataType* aMetadata);
      ReferenceParametersTypePtr referenceParametersElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setReferenceParameters(ReferenceParametersType* aReferenceParameters);



      //data
   protected:
      //elements
      AttributedURITypePtr mAddressElement;
      std::vector<std::string> mContentElements;
      MetadataTypePtr mMetadataElement;
      ReferenceParametersTypePtr mReferenceParametersElement;
 
   }; //class  EndpointReferenceType

   #include "TrentinoSCAModelEndpointReferenceType.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelEndpointReferenceTypeH
