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

#ifndef TrentinoSCAModelPolicyReferenceH
#define TrentinoSCAModelPolicyReferenceH
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class PolicyReference
   {
      //construction
   public:
      PolicyReference();
   private:
      PolicyReference(const PolicyReference&);
      void operator=(const PolicyReference&);

      //services
   public:



      //element accessors  
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addContentElement(const char* aContent);
     const std::vector<std::string>& contentElements() const;

      //attribute accessors
      const Trentino::XML::Schema::AnyURI& digestAlgorithm() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setDigestAlgorithm(const char* aDigestAlgorithm);
      const Trentino::XML::Schema::AnyURI& uri() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setUri(const char* aUri);


      //data
   protected:
      //elements
      std::vector<std::string> mContentElements;
 
      //attributes
      Trentino::XML::Schema::AnyURI mDigestAlgorithm;   
      Trentino::XML::Schema::AnyURI mUri;   
   }; //class  PolicyReference

   #include "TrentinoSCAModelPolicyReference.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelPolicyReferenceH
