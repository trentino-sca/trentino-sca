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

#ifndef TrentinoSCAModelComponentH
#define TrentinoSCAModelComponentH
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
   class Component : public CommonExtensionBase
   {
      //construction
   public:
      Component();
   private:
      Component(const Component&);
      void operator=(const Component&);

      //services
   public:



      //element accessors  
      ExtensionsPtr extensionsElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setExtensions(Extensions* aExtensions);
      ImplementationPtr implementationElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setImplementation(Implementation* aImplementation);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment);
     const std::vector<PolicySetAttachmentPtr>& policySetAttachmentElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPropertyElement(PropertyValue* aProperty);
     const std::vector<PropertyValuePtr>& propertyElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addReferenceElement(ComponentReference* aReference);
     const std::vector<ComponentReferencePtr>& referenceElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addRequiresElement(Requires* aRequires);
     const std::vector<RequiresPtr>& requiresElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addServiceElement(ComponentService* aService);
     const std::vector<ComponentServicePtr>& serviceElements() const;


      //attribute accessors
      bool isAutowire() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setAutowire(bool isAutowire);
      const Trentino::XML::Schema::NCName& name() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setName(const char* aName);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySets(Trentino::XML::Schema::QName* aPolicySets);
     const std::vector<QNamePtr>& policySets() const;



      //data
   protected:
      //elements
      ExtensionsPtr mExtensionsElement;
      ImplementationPtr mImplementationElement;
      std::vector<PolicySetAttachmentPtr> mPolicySetAttachmentElements;
      std::vector<PropertyValuePtr> mPropertyElements;
      std::vector<ComponentReferencePtr> mReferenceElements;
      std::vector<RequiresPtr> mRequiresElements;
      std::vector<ComponentServicePtr> mServiceElements;
 
      //attributes
      bool mIsAutowire;
      Trentino::XML::Schema::NCName mName;   
      std::vector<QNamePtr> mPolicySets;
   }; //class  Component

   #include "TrentinoSCAModelComponent.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelComponentH
