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

#ifndef TrentinoSCAModelH
#define TrentinoSCAModelH

//standard 
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

//specific
#include "../../Global/TrentinoGlobal.h"
#include "../XML/TrentinoXMLSchema.h"
#include "../XML/TrentinoXMLSchemaQName.h"

namespace Trentino{
namespace SCA{
namespace Model
{
   class AppliesTo;
   class AttributedQNameType;
   class AttributedURIType;
   class AttributedUnsignedLongType;
   class Binding;
   class BindingType;
   class CPPExport;
   class CPPFunction;
   class CPPImplementation;
   class CPPImplementationFunction;
   class CPPImplementationScope;
   class CPPImport;
   class CPPInterface;
   class Callback;
   class CommonExtensionBase;
   class Component;
   class ComponentReference;
   class ComponentService;
   class ComponentType;
   class ComponentTypeReference;
   class Composite;
   class Contract;
   class ContributionType;
   class CreateResource;
   class DeployableType;
   class Documentation;
   class EndpointReferenceType;
   class Export;
   class ExportType;
   class Extensions;
   class ExternalAttachment;
   class IPCBinding;
   class Implementation;
   class ImplementationType;
   class Import;
   class ImportType;
   class Include;
   class Intent;
   class IntentMap;
   class IntentQualifier;
   class InteractionOrImplementation;
   class Interface;
   class Metadata;
   class MetadataStringAttribute;
   class MetadataType;
   class Object;
   class OperationSelectorType;
   class OperatorContentType;
   class OverrideOptions;
   class Policy;
   class PolicyAttachment;
   class PolicyReference;
   class PolicySet;
   class PolicySetAttachment;
   class PolicySetReference;
   class ProblemActionType;
   class Property;
   class PropertyValue;
   class Qualifier;
   class Reference;
   class ReferenceParametersType;
   class RelatesToType;
   class Requires;
   class SCABinding;
   class SCAImplementation;
   class SCAPropertyBase;
   class Service;
   class TDefinitions;
   class URI;
   class ValueType;
   class WSCallback;
   class Wire;
   class WireFormatType;

   typedef boost::shared_ptr<Trentino::XML::Schema::QName> QNamePtr;  
   typedef boost::shared_ptr<AppliesTo> AppliesToPtr;
   typedef boost::shared_ptr<AttributedQNameType> AttributedQNameTypePtr;
   typedef boost::shared_ptr<AttributedURIType> AttributedURITypePtr;
   typedef boost::shared_ptr<AttributedUnsignedLongType> AttributedUnsignedLongTypePtr;
   typedef boost::shared_ptr<Binding> BindingPtr;
   typedef boost::shared_ptr<BindingType> BindingTypePtr;
   typedef boost::shared_ptr<CPPExport> CPPExportPtr;
   typedef boost::shared_ptr<CPPFunction> CPPFunctionPtr;
   typedef boost::shared_ptr<CPPImplementation> CPPImplementationPtr;
   typedef boost::shared_ptr<CPPImplementationFunction> CPPImplementationFunctionPtr;
   typedef boost::shared_ptr<CPPImplementationScope> CPPImplementationScopePtr;
   typedef boost::shared_ptr<CPPImport> CPPImportPtr;
   typedef boost::shared_ptr<CPPInterface> CPPInterfacePtr;
   typedef boost::shared_ptr<Callback> CallbackPtr;
   typedef boost::shared_ptr<CommonExtensionBase> CommonExtensionBasePtr;
   typedef boost::shared_ptr<Component> ComponentPtr;
   typedef boost::shared_ptr<ComponentReference> ComponentReferencePtr;
   typedef boost::shared_ptr<ComponentService> ComponentServicePtr;
   typedef boost::shared_ptr<ComponentType> ComponentTypePtr;
   typedef boost::shared_ptr<ComponentTypeReference> ComponentTypeReferencePtr;
   typedef boost::shared_ptr<Composite> CompositePtr;
   typedef boost::shared_ptr<Contract> ContractPtr;
   typedef boost::shared_ptr<ContributionType> ContributionTypePtr;
   typedef boost::shared_ptr<CreateResource> CreateResourcePtr;
   typedef boost::shared_ptr<DeployableType> DeployableTypePtr;
   typedef boost::shared_ptr<Documentation> DocumentationPtr;
   typedef boost::shared_ptr<EndpointReferenceType> EndpointReferenceTypePtr;
   typedef boost::shared_ptr<Export> ExportPtr;
   typedef boost::shared_ptr<ExportType> ExportTypePtr;
   typedef boost::shared_ptr<Extensions> ExtensionsPtr;
   typedef boost::shared_ptr<ExternalAttachment> ExternalAttachmentPtr;
   typedef boost::shared_ptr<IPCBinding> IPCBindingPtr;
   typedef boost::shared_ptr<Implementation> ImplementationPtr;
   typedef boost::shared_ptr<ImplementationType> ImplementationTypePtr;
   typedef boost::shared_ptr<Import> ImportPtr;
   typedef boost::shared_ptr<ImportType> ImportTypePtr;
   typedef boost::shared_ptr<Include> IncludePtr;
   typedef boost::shared_ptr<Intent> IntentPtr;
   typedef boost::shared_ptr<IntentMap> IntentMapPtr;
   typedef boost::shared_ptr<IntentQualifier> IntentQualifierPtr;
   typedef boost::shared_ptr<InteractionOrImplementation> InteractionOrImplementationPtr;
   typedef boost::shared_ptr<Interface> InterfacePtr;
   typedef boost::shared_ptr<Metadata> MetadataPtr;
   typedef boost::shared_ptr<MetadataStringAttribute> MetadataStringAttributePtr;
   typedef boost::shared_ptr<MetadataType> MetadataTypePtr;
   typedef boost::shared_ptr<Object> ObjectPtr;
   typedef boost::shared_ptr<OperationSelectorType> OperationSelectorTypePtr;
   typedef boost::shared_ptr<OperatorContentType> OperatorContentTypePtr;
   typedef boost::shared_ptr<OverrideOptions> OverrideOptionsPtr;
   typedef boost::shared_ptr<Policy> PolicyPtr;
   typedef boost::shared_ptr<PolicyAttachment> PolicyAttachmentPtr;
   typedef boost::shared_ptr<PolicyReference> PolicyReferencePtr;
   typedef boost::shared_ptr<PolicySet> PolicySetPtr;
   typedef boost::shared_ptr<PolicySetAttachment> PolicySetAttachmentPtr;
   typedef boost::shared_ptr<PolicySetReference> PolicySetReferencePtr;
   typedef boost::shared_ptr<ProblemActionType> ProblemActionTypePtr;
   typedef boost::shared_ptr<Property> PropertyPtr;
   typedef boost::shared_ptr<PropertyValue> PropertyValuePtr;
   typedef boost::shared_ptr<Qualifier> QualifierPtr;
   typedef boost::shared_ptr<Reference> ReferencePtr;
   typedef boost::shared_ptr<ReferenceParametersType> ReferenceParametersTypePtr;
   typedef boost::shared_ptr<RelatesToType> RelatesToTypePtr;
   typedef boost::shared_ptr<Requires> RequiresPtr;
   typedef boost::shared_ptr<SCABinding> SCABindingPtr;
   typedef boost::shared_ptr<SCAImplementation> SCAImplementationPtr;
   typedef boost::shared_ptr<SCAPropertyBase> SCAPropertyBasePtr;
   typedef boost::shared_ptr<Service> ServicePtr;
   typedef boost::shared_ptr<TDefinitions> TDefinitionsPtr;
   typedef boost::shared_ptr<URI> URIPtr;
   typedef boost::shared_ptr<ValueType> ValueTypePtr;
   typedef boost::shared_ptr<WSCallback> WSCallbackPtr;
   typedef boost::shared_ptr<Wire> WirePtr;
   typedef boost::shared_ptr<WireFormatType> WireFormatTypePtr;
   
} //namespace Model
} //namespace SCA
} //namespace Trentino

#include "TrentinoSCAModelFixed.h"

#endif //TrentinoSCAModelH