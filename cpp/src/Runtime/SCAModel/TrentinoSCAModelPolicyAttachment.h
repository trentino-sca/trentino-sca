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

#ifndef TrentinoSCAModelPolicyAttachmentH
#define TrentinoSCAModelPolicyAttachmentH
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class PolicyAttachment
   {
      //construction
   public:
      PolicyAttachment();
   private:
      PolicyAttachment(const PolicyAttachment&);
      void operator=(const PolicyAttachment&);

      //services
   public:



      //element accessors  
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicyElement(Policy* aPolicy);
     const std::vector<PolicyPtr>& policyElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicyReferenceElement(PolicyReference* aPolicyReference);
     const std::vector<PolicyReferencePtr>& policyReferenceElements() const;

      AppliesToPtr appliesToElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setAppliesTo(AppliesTo* aAppliesTo);
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addContentElement(const char* aContent);
     const std::vector<std::string>& contentElements() const;



      //data
   protected:
      //elements
      std::vector<PolicyPtr> mPolicyElements;
      std::vector<PolicyReferencePtr> mPolicyReferenceElements;
      AppliesToPtr mAppliesToElement;
      std::vector<std::string> mContentElements;
 
   }; //class  PolicyAttachment

   #include "TrentinoSCAModelPolicyAttachment.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelPolicyAttachmentH
