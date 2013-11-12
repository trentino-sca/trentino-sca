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

#ifndef TrentinoSCAModelCompositeH
#define TrentinoSCAModelCompositeH
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
   class Composite : public CommonExtensionBase
   {
      //construction
   public:
      Composite();
   private:
      Composite(const Composite&);
      void operator=(const Composite&);

      //services
   public:



      //element accessors  
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addComponentElement(Component* aComponent);
     const std::vector<ComponentPtr>& componentElements() const;

      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addContentElement(const char* aContent);
     const std::vector<std::string>& contentElements() const;
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addIncludeElement(Include* aInclude);
     const std::vector<IncludePtr>& includeElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment);
     const std::vector<PolicySetAttachmentPtr>& policySetAttachmentElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPropertyElement(Property* aProperty);
     const std::vector<PropertyPtr>& propertyElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addReferenceElement(Reference* aReference);
     const std::vector<ReferencePtr>& referenceElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addRequiresElement(Requires* aRequires);
     const std::vector<RequiresPtr>& requiresElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addServiceElement(Service* aService);
     const std::vector<ServicePtr>& serviceElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addWireElement(Wire* aWire);
     const std::vector<WirePtr>& wireElements() const;


      //attribute accessors
      bool isAutowire() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setAutowire(bool isAutowire);
      bool isLocal() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setLocal(bool isLocal);
      const Trentino::XML::Schema::NCName& name() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setName(const char* aName);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySets(Trentino::XML::Schema::QName* aPolicySets);
     const std::vector<QNamePtr>& policySets() const;

      const Trentino::XML::Schema::AnyURI& targetNamespace() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setTargetNamespace(const char* aTargetNamespace);


      //data
   protected:
      //elements
      std::vector<ComponentPtr> mComponentElements;
      std::vector<std::string> mContentElements;
      std::vector<IncludePtr> mIncludeElements;
      std::vector<PolicySetAttachmentPtr> mPolicySetAttachmentElements;
      std::vector<PropertyPtr> mPropertyElements;
      std::vector<ReferencePtr> mReferenceElements;
      std::vector<RequiresPtr> mRequiresElements;
      std::vector<ServicePtr> mServiceElements;
      std::vector<WirePtr> mWireElements;
 
      //attributes
      bool mIsAutowire;
      bool mIsLocal;
      Trentino::XML::Schema::NCName mName;   
      std::vector<QNamePtr> mPolicySets;
      Trentino::XML::Schema::AnyURI mTargetNamespace;   
   }; //class  Composite

   #include "TrentinoSCAModelComposite.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelCompositeH
