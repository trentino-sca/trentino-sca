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

#ifndef TrentinoSCAModelContractH
#define TrentinoSCAModelContractH
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
   class Contract : public CommonExtensionBase
   {
      //construction
   public:
      Contract();
   private:
      Contract(const Contract&);
      void operator=(const Contract&);

      //services
   public:



      //element accessors  
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addBindingElement(Binding* aBinding);
     const std::vector<BindingPtr>& bindingElements() const;

      CallbackPtr callbackElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setCallback(Callback* aCallback);
      ExtensionsPtr extensionsElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setExtensions(Extensions* aExtensions);
      InterfacePtr interfaceElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setInterface(Interface* aInterface);
      MetadataPtr metadataElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setMetadata(Metadata* aMetadata);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment);
     const std::vector<PolicySetAttachmentPtr>& policySetAttachmentElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addScaRequiresElement(Requires* aScaRequires);
     const std::vector<RequiresPtr>& scaRequiresElements() const;


      //attribute accessors
      const Trentino::XML::Schema::NCName& name() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setName(const char* aName);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySets(Trentino::XML::Schema::QName* aPolicySets);
     const std::vector<QNamePtr>& policySets() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addRequires(Trentino::XML::Schema::QName* aRequires);
     const std::vector<QNamePtr>& requires() const;



      //data
   protected:
      //elements
      std::vector<BindingPtr> mBindingElements;
      CallbackPtr mCallbackElement;
      ExtensionsPtr mExtensionsElement;
      InterfacePtr mInterfaceElement;
      MetadataPtr mMetadataElement;
      std::vector<PolicySetAttachmentPtr> mPolicySetAttachmentElements;
      std::vector<RequiresPtr> mScaRequiresElements;
 
      //attributes
      Trentino::XML::Schema::NCName mName;   
      std::vector<QNamePtr> mPolicySets;
      std::vector<QNamePtr> mRequires;
   }; //class  Contract

   #include "TrentinoSCAModelContract.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelContractH
