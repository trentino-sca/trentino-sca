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


//specific
#include "TrentinoSCAModelAppliesTo.h"
#include "TrentinoSCAModelAttributedQNameType.h"
#include "TrentinoSCAModelAttributedURIType.h"
#include "TrentinoSCAModelAttributedUnsignedLongType.h"
#include "TrentinoSCAModelBinding.h"
#include "TrentinoSCAModelBindingType.h"
#include "TrentinoSCAModelCPPExport.h"
#include "TrentinoSCAModelCPPFunction.h"
#include "TrentinoSCAModelCPPImplementation.h"
#include "TrentinoSCAModelCPPImplementationFunction.h"
#include "TrentinoSCAModelCPPImplementationScope.h"
#include "TrentinoSCAModelCPPImport.h"
#include "TrentinoSCAModelCPPInterface.h"
#include "TrentinoSCAModelCallback.h"
#include "TrentinoSCAModelCommonExtensionBase.h"
#include "TrentinoSCAModelComponent.h"
#include "TrentinoSCAModelComponentReference.h"
#include "TrentinoSCAModelComponentService.h"
#include "TrentinoSCAModelComponentType.h"
#include "TrentinoSCAModelComponentTypeReference.h"
#include "TrentinoSCAModelComposite.h"
#include "TrentinoSCAModelContract.h"
#include "TrentinoSCAModelContributionType.h"
#include "TrentinoSCAModelCreateResource.h"
#include "TrentinoSCAModelDeployableType.h"
#include "TrentinoSCAModelDocumentation.h"
#include "TrentinoSCAModelEndpointReferenceType.h"
#include "TrentinoSCAModelExport.h"
#include "TrentinoSCAModelExportType.h"
#include "TrentinoSCAModelExtensions.h"
#include "TrentinoSCAModelExternalAttachment.h"
#include "TrentinoSCAModelIPCBinding.h"
#include "TrentinoSCAModelImplementation.h"
#include "TrentinoSCAModelImplementationType.h"
#include "TrentinoSCAModelImport.h"
#include "TrentinoSCAModelImportType.h"
#include "TrentinoSCAModelInclude.h"
#include "TrentinoSCAModelIntent.h"
#include "TrentinoSCAModelIntentMap.h"
#include "TrentinoSCAModelIntentQualifier.h"
#include "TrentinoSCAModelInteractionOrImplementation.h"
#include "TrentinoSCAModelInterface.h"
#include "TrentinoSCAModelMetadata.h"
#include "TrentinoSCAModelMetadataStringAttribute.h"
#include "TrentinoSCAModelMetadataType.h"
#include "TrentinoSCAModelObject.h"
#include "TrentinoSCAModelOperationSelectorType.h"
#include "TrentinoSCAModelOperatorContentType.h"
#include "TrentinoSCAModelOverrideOptions.h"
#include "TrentinoSCAModelPolicy.h"
#include "TrentinoSCAModelPolicyAttachment.h"
#include "TrentinoSCAModelPolicyReference.h"
#include "TrentinoSCAModelPolicySet.h"
#include "TrentinoSCAModelPolicySetAttachment.h"
#include "TrentinoSCAModelPolicySetReference.h"
#include "TrentinoSCAModelProblemActionType.h"
#include "TrentinoSCAModelProperty.h"
#include "TrentinoSCAModelPropertyValue.h"
#include "TrentinoSCAModelQualifier.h"
#include "TrentinoSCAModelReference.h"
#include "TrentinoSCAModelReferenceParametersType.h"
#include "TrentinoSCAModelRelatesToType.h"
#include "TrentinoSCAModelRequires.h"
#include "TrentinoSCAModelSCABinding.h"
#include "TrentinoSCAModelSCAImplementation.h"
#include "TrentinoSCAModelSCAPropertyBase.h"
#include "TrentinoSCAModelService.h"
#include "TrentinoSCAModelTDefinitions.h"
#include "TrentinoSCAModelURI.h"
#include "TrentinoSCAModelValueType.h"
#include "TrentinoSCAModelWSCallback.h"
#include "TrentinoSCAModelWire.h"
#include "TrentinoSCAModelWireFormatType.h"

//header
#include "TrentinoSCAModelFactory.h"

using namespace Trentino::SCA::Model;
using Trentino::XML::Schema::QName;

//class Factory
   //services
Trentino::XML::Schema::QName* Factory::createQName( const char* localPart 
                                                  , const char* namespaceName
                                                  , const char* prefix )
{
   return new QName(localPart, namespaceName, prefix);
}

  AppliesTo* TRENTINO_STDCALL Factory::createAppliesTo()
{
    return new AppliesTo();
}
  AttributedQNameType* TRENTINO_STDCALL Factory::createAttributedQNameType()
{
    return new AttributedQNameType();
}
  AttributedURIType* TRENTINO_STDCALL Factory::createAttributedURIType()
{
    return new AttributedURIType();
}
  AttributedUnsignedLongType* TRENTINO_STDCALL Factory::createAttributedUnsignedLongType()
{
    return new AttributedUnsignedLongType();
}
  BindingType* TRENTINO_STDCALL Factory::createBindingType()
{
    return new BindingType();
}
  CPPExport* TRENTINO_STDCALL Factory::createCPPExport()
{
    return new CPPExport();
}
  CPPFunction* TRENTINO_STDCALL Factory::createCPPFunction()
{
    return new CPPFunction();
}
  CPPImplementation* TRENTINO_STDCALL Factory::createCPPImplementation()
{
    return new CPPImplementation();
}
  CPPImplementationFunction* TRENTINO_STDCALL Factory::createCPPImplementationFunction()
{
    return new CPPImplementationFunction();
}
       CPPImplementationScope* TRENTINO_STDCALL Factory::createCPPImplementationScope(const char* valueStr)
{
    return new CPPImplementationScope(valueStr);
}
  CPPImport* TRENTINO_STDCALL Factory::createCPPImport()
{
    return new CPPImport();
}
  CPPInterface* TRENTINO_STDCALL Factory::createCPPInterface()
{
    return new CPPInterface();
}
  Callback* TRENTINO_STDCALL Factory::createCallback()
{
    return new Callback();
}
  CommonExtensionBase* TRENTINO_STDCALL Factory::createCommonExtensionBase()
{
    return new CommonExtensionBase();
}
  Component* TRENTINO_STDCALL Factory::createComponent()
{
    return new Component();
}
  ComponentReference* TRENTINO_STDCALL Factory::createComponentReference()
{
    return new ComponentReference();
}
  ComponentService* TRENTINO_STDCALL Factory::createComponentService()
{
    return new ComponentService();
}
  ComponentType* TRENTINO_STDCALL Factory::createComponentType()
{
    return new ComponentType();
}
  ComponentTypeReference* TRENTINO_STDCALL Factory::createComponentTypeReference()
{
    return new ComponentTypeReference();
}
  Composite* TRENTINO_STDCALL Factory::createComposite()
{
    return new Composite();
}
  ContributionType* TRENTINO_STDCALL Factory::createContributionType()
{
    return new ContributionType();
}
       CreateResource* TRENTINO_STDCALL Factory::createCreateResource(const char* valueStr)
{
    return new CreateResource(valueStr);
}
  DeployableType* TRENTINO_STDCALL Factory::createDeployableType()
{
    return new DeployableType();
}
  Documentation* TRENTINO_STDCALL Factory::createDocumentation()
{
    return new Documentation();
}
  EndpointReferenceType* TRENTINO_STDCALL Factory::createEndpointReferenceType()
{
    return new EndpointReferenceType();
}
  ExportType* TRENTINO_STDCALL Factory::createExportType()
{
    return new ExportType();
}
  Extensions* TRENTINO_STDCALL Factory::createExtensions()
{
    return new Extensions();
}
  ExternalAttachment* TRENTINO_STDCALL Factory::createExternalAttachment()
{
    return new ExternalAttachment();
}
  IPCBinding* TRENTINO_STDCALL Factory::createIPCBinding()
{
    return new IPCBinding();
}
  ImplementationType* TRENTINO_STDCALL Factory::createImplementationType()
{
    return new ImplementationType();
}
  ImportType* TRENTINO_STDCALL Factory::createImportType()
{
    return new ImportType();
}
  Include* TRENTINO_STDCALL Factory::createInclude()
{
    return new Include();
}
  Intent* TRENTINO_STDCALL Factory::createIntent()
{
    return new Intent();
}
  IntentMap* TRENTINO_STDCALL Factory::createIntentMap()
{
    return new IntentMap();
}
  IntentQualifier* TRENTINO_STDCALL Factory::createIntentQualifier()
{
    return new IntentQualifier();
}
       InteractionOrImplementation* TRENTINO_STDCALL Factory::createInteractionOrImplementation(const char* valueStr)
{
    return new InteractionOrImplementation(valueStr);
}
  Metadata* TRENTINO_STDCALL Factory::createMetadata()
{
    return new Metadata();
}
  MetadataStringAttribute* TRENTINO_STDCALL Factory::createMetadataStringAttribute()
{
    return new MetadataStringAttribute();
}
  MetadataType* TRENTINO_STDCALL Factory::createMetadataType()
{
    return new MetadataType();
}
  Object* TRENTINO_STDCALL Factory::createObject()
{
    return new Object();
}
  OperatorContentType* TRENTINO_STDCALL Factory::createOperatorContentType()
{
    return new OperatorContentType();
}
       OverrideOptions* TRENTINO_STDCALL Factory::createOverrideOptions(const char* valueStr)
{
    return new OverrideOptions(valueStr);
}
  Policy* TRENTINO_STDCALL Factory::createPolicy()
{
    return new Policy();
}
  PolicyAttachment* TRENTINO_STDCALL Factory::createPolicyAttachment()
{
    return new PolicyAttachment();
}
  PolicyReference* TRENTINO_STDCALL Factory::createPolicyReference()
{
    return new PolicyReference();
}
  PolicySet* TRENTINO_STDCALL Factory::createPolicySet()
{
    return new PolicySet();
}
  PolicySetAttachment* TRENTINO_STDCALL Factory::createPolicySetAttachment()
{
    return new PolicySetAttachment();
}
  PolicySetReference* TRENTINO_STDCALL Factory::createPolicySetReference()
{
    return new PolicySetReference();
}
  ProblemActionType* TRENTINO_STDCALL Factory::createProblemActionType()
{
    return new ProblemActionType();
}
  Property* TRENTINO_STDCALL Factory::createProperty()
{
    return new Property();
}
  PropertyValue* TRENTINO_STDCALL Factory::createPropertyValue()
{
    return new PropertyValue();
}
  Qualifier* TRENTINO_STDCALL Factory::createQualifier()
{
    return new Qualifier();
}
  Reference* TRENTINO_STDCALL Factory::createReference()
{
    return new Reference();
}
  ReferenceParametersType* TRENTINO_STDCALL Factory::createReferenceParametersType()
{
    return new ReferenceParametersType();
}
  RelatesToType* TRENTINO_STDCALL Factory::createRelatesToType()
{
    return new RelatesToType();
}
  Requires* TRENTINO_STDCALL Factory::createRequires()
{
    return new Requires();
}
  SCABinding* TRENTINO_STDCALL Factory::createSCABinding()
{
    return new SCABinding();
}
  SCAImplementation* TRENTINO_STDCALL Factory::createSCAImplementation()
{
    return new SCAImplementation();
}
  SCAPropertyBase* TRENTINO_STDCALL Factory::createSCAPropertyBase()
{
    return new SCAPropertyBase();
}
  Service* TRENTINO_STDCALL Factory::createService()
{
    return new Service();
}
  TDefinitions* TRENTINO_STDCALL Factory::createTDefinitions()
{
    return new TDefinitions();
}
  URI* TRENTINO_STDCALL Factory::createURI()
{
    return new URI();
}
  ValueType* TRENTINO_STDCALL Factory::createValueType()
{
    return new ValueType();
}
  WSCallback* TRENTINO_STDCALL Factory::createWSCallback()
{
    return new WSCallback();
}
  Wire* TRENTINO_STDCALL Factory::createWire()
{
    return new Wire();
}
