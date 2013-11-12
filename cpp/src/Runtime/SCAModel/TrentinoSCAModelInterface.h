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

#ifndef TrentinoSCAModelInterfaceH
#define TrentinoSCAModelInterfaceH
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
   class Interface : public CommonExtensionBase
   {
      //construction
   public:
      Interface();
   private:
      Interface(const Interface&);
      void operator=(const Interface&);

      //services
   public:
      const Trentino::XML::Schema::QName& xsdType() const;



      //element accessors  
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment);
     const std::vector<PolicySetAttachmentPtr>& policySetAttachmentElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addRequiresElement(Requires* aRequires);
     const std::vector<RequiresPtr>& requiresElements() const;


      //attribute accessors
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySets(Trentino::XML::Schema::QName* aPolicySets);
     const std::vector<QNamePtr>& policySets() const;

      bool isRemotable() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setRemotable(bool isRemotable);


      //data
   protected:
	  QNamePtr mXSDType;
      //elements
      std::vector<PolicySetAttachmentPtr> mPolicySetAttachmentElements;
      std::vector<RequiresPtr> mRequiresElements;
 
      //attributes
      std::vector<QNamePtr> mPolicySets;
      bool mIsRemotable;
   }; //class  Interface

   #include "TrentinoSCAModelInterface.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelInterfaceH
