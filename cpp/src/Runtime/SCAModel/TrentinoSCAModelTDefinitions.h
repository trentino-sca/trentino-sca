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

#ifndef TrentinoSCAModelTDefinitionsH
#define TrentinoSCAModelTDefinitionsH
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
   class TDefinitions : public CommonExtensionBase
   {
      //construction
   public:
      TDefinitions();
   private:
      TDefinitions(const TDefinitions&);
      void operator=(const TDefinitions&);

      //services
   public:



      //element accessors  
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addBindingTypeElement(BindingType* aBindingType);
     const std::vector<BindingTypePtr>& bindingTypeElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addExternalAttachmentElement(ExternalAttachment* aExternalAttachment);
     const std::vector<ExternalAttachmentPtr>& externalAttachmentElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addImplementationTypeElement(ImplementationType* aImplementationType);
     const std::vector<ImplementationTypePtr>& implementationTypeElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addIntentElement(Intent* aIntent);
     const std::vector<IntentPtr>& intentElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySetElement(PolicySet* aPolicySet);
     const std::vector<PolicySetPtr>& policySetElements() const;


      //attribute accessors
      const Trentino::XML::Schema::AnyURI& targetNamespace() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setTargetNamespace(const char* aTargetNamespace);


      //data
   protected:
      //elements
      std::vector<BindingTypePtr> mBindingTypeElements;
      std::vector<ExternalAttachmentPtr> mExternalAttachmentElements;
      std::vector<ImplementationTypePtr> mImplementationTypeElements;
      std::vector<IntentPtr> mIntentElements;
      std::vector<PolicySetPtr> mPolicySetElements;
 
      //attributes
      Trentino::XML::Schema::AnyURI mTargetNamespace;   
   }; //class  TDefinitions

   #include "TrentinoSCAModelTDefinitions.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelTDefinitionsH
