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

#ifndef TrentinoSCAModelBindingH
#define TrentinoSCAModelBindingH
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
   class Binding : public CommonExtensionBase
   {
      //construction
   public:
      Binding();
   private:
      Binding(const Binding&);
      void operator=(const Binding&);

      //services
   public:
      const Trentino::XML::Schema::QName& xsdType() const;



      //element accessors  
      OperationSelectorTypePtr operationSelectorElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setOperationSelector(OperationSelectorType* aOperationSelector);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment);
     const std::vector<PolicySetAttachmentPtr>& policySetAttachmentElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addScaRequiresElement(Requires* aScaRequires);
     const std::vector<RequiresPtr>& scaRequiresElements() const;

      WireFormatTypePtr wireFormatElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setWireFormat(WireFormatType* aWireFormat);

      //attribute accessors
      const Trentino::XML::Schema::NCName& name() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setName(const char* aName);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySets(Trentino::XML::Schema::QName* aPolicySets);
     const std::vector<QNamePtr>& policySets() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addRequires(Trentino::XML::Schema::QName* aRequires);
     const std::vector<QNamePtr>& requires() const;

      const Trentino::XML::Schema::AnyURI& uri() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setUri(const char* aUri);


      //data
   protected:
	  QNamePtr mXSDType;
      //elements
      OperationSelectorTypePtr mOperationSelectorElement;
      std::vector<PolicySetAttachmentPtr> mPolicySetAttachmentElements;
      std::vector<RequiresPtr> mScaRequiresElements;
      WireFormatTypePtr mWireFormatElement;
 
      //attributes
      Trentino::XML::Schema::NCName mName;   
      std::vector<QNamePtr> mPolicySets;
      std::vector<QNamePtr> mRequires;
      Trentino::XML::Schema::AnyURI mUri;   
   }; //class  Binding

   #include "TrentinoSCAModelBinding.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelBindingH
