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

#ifndef TrentinoSCAModelFactoryH
#define TrentinoSCAModelFactoryH

//specific
#include "TrentinoSCAModel.h"
#include "TrentinoSCAModelMetadata.h"
#include "TrentinoSCAModelMetadataStringAttribute.h"

namespace Trentino{
namespace SCA{
namespace Model
{
   //class MetadataStringAttribute;

   const char* const DefaultNamespaceNameCStr = Trentino::XML::Schema::defaultNamespaceName().c_str();
   const char* const DefaultNamespacePrefixCStr = Trentino::XML::Schema::defaultNamespacePrefix().c_str();


   class SCAMODEL_IMPORT_EXPORT Factory
   {
   public:
	  Trentino::XML::Schema::QName* createQName( const char* localPart = ""
											   , const char* namespaceName = DefaultNamespaceNameCStr
											   , const char* prefix = DefaultNamespacePrefixCStr);
      
	  AppliesTo* TRENTINO_STDCALL createAppliesTo();
	  AttributedQNameType* TRENTINO_STDCALL createAttributedQNameType();
	  AttributedURIType* TRENTINO_STDCALL createAttributedURIType();
	  AttributedUnsignedLongType* TRENTINO_STDCALL createAttributedUnsignedLongType();
	  BindingType* TRENTINO_STDCALL createBindingType();
	  CPPExport* TRENTINO_STDCALL createCPPExport();
	  CPPFunction* TRENTINO_STDCALL createCPPFunction();
	  CPPImplementation* TRENTINO_STDCALL createCPPImplementation();
	  CPPImplementationFunction* TRENTINO_STDCALL createCPPImplementationFunction();
	  CPPImplementationScope* TRENTINO_STDCALL createCPPImplementationScope(const char* valueStr);
	  CPPImport* TRENTINO_STDCALL createCPPImport();
	  CPPInterface* TRENTINO_STDCALL createCPPInterface();
	  Callback* TRENTINO_STDCALL createCallback();
	  CommonExtensionBase* TRENTINO_STDCALL createCommonExtensionBase();
	  Component* TRENTINO_STDCALL createComponent();
	  ComponentReference* TRENTINO_STDCALL createComponentReference();
	  ComponentService* TRENTINO_STDCALL createComponentService();
	  ComponentType* TRENTINO_STDCALL createComponentType();
	  ComponentTypeReference* TRENTINO_STDCALL createComponentTypeReference();
	  Composite* TRENTINO_STDCALL createComposite();
	  ContributionType* TRENTINO_STDCALL createContributionType();
	  CreateResource* TRENTINO_STDCALL createCreateResource(const char* valueStr);
	  DeployableType* TRENTINO_STDCALL createDeployableType();
	  Documentation* TRENTINO_STDCALL createDocumentation();
	  EndpointReferenceType* TRENTINO_STDCALL createEndpointReferenceType();
	  ExportType* TRENTINO_STDCALL createExportType();
	  Extensions* TRENTINO_STDCALL createExtensions();
	  ExternalAttachment* TRENTINO_STDCALL createExternalAttachment();
	  IPCBinding* TRENTINO_STDCALL createIPCBinding();
	  ImplementationType* TRENTINO_STDCALL createImplementationType();
	  ImportType* TRENTINO_STDCALL createImportType();
	  Include* TRENTINO_STDCALL createInclude();
	  Intent* TRENTINO_STDCALL createIntent();
	  IntentMap* TRENTINO_STDCALL createIntentMap();
	  IntentQualifier* TRENTINO_STDCALL createIntentQualifier();
	  InteractionOrImplementation* TRENTINO_STDCALL createInteractionOrImplementation(const char* valueStr);
	  Metadata* TRENTINO_STDCALL createMetadata();
	  MetadataStringAttribute* TRENTINO_STDCALL createMetadataStringAttribute();
	  MetadataType* TRENTINO_STDCALL createMetadataType();
	  Object* TRENTINO_STDCALL createObject();
	  OperatorContentType* TRENTINO_STDCALL createOperatorContentType();
	  OverrideOptions* TRENTINO_STDCALL createOverrideOptions(const char* valueStr);
	  Policy* TRENTINO_STDCALL createPolicy();
	  PolicyAttachment* TRENTINO_STDCALL createPolicyAttachment();
	  PolicyReference* TRENTINO_STDCALL createPolicyReference();
	  PolicySet* TRENTINO_STDCALL createPolicySet();
	  PolicySetAttachment* TRENTINO_STDCALL createPolicySetAttachment();
	  PolicySetReference* TRENTINO_STDCALL createPolicySetReference();
	  ProblemActionType* TRENTINO_STDCALL createProblemActionType();
	  Property* TRENTINO_STDCALL createProperty();
	  PropertyValue* TRENTINO_STDCALL createPropertyValue();
	  Qualifier* TRENTINO_STDCALL createQualifier();
	  Reference* TRENTINO_STDCALL createReference();
	  ReferenceParametersType* TRENTINO_STDCALL createReferenceParametersType();
	  RelatesToType* TRENTINO_STDCALL createRelatesToType();
	  Requires* TRENTINO_STDCALL createRequires();
	  SCABinding* TRENTINO_STDCALL createSCABinding();
	  SCAImplementation* TRENTINO_STDCALL createSCAImplementation();
	  SCAPropertyBase* TRENTINO_STDCALL createSCAPropertyBase();
	  Service* TRENTINO_STDCALL createService();
	  TDefinitions* TRENTINO_STDCALL createTDefinitions();
	  URI* TRENTINO_STDCALL createURI();
	  ValueType* TRENTINO_STDCALL createValueType();
	  WSCallback* TRENTINO_STDCALL createWSCallback();
	  Wire* TRENTINO_STDCALL createWire();
   }; //class Factory 

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelFactoryH