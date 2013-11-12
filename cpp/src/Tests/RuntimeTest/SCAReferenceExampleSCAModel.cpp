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

//standard
#include <utility>

//specific
#include "../../Runtime/SCAModel/TrentinoSCAModelComposite.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelComponent.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelService.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelReference.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelSCABinding.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelProperty.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelCPPImplementation.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelCPPImplementationScope.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelPropertyValue.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelSCAImplementation.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelComponentType.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelComponentService.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelCPPInterface.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelComponentTypeReference.h"

//header
#include "SCAReferenceExampleSCAModel.h"

using namespace std;
using namespace Trentino::Tests::createSCAReferenceExample;
using Trentino::XML::Schema::QName;
namespace SCAModel = Trentino::SCA::Model;

SCAComponentMap Trentino::Tests::createSCAReferenceExample::createSCAReferenceExampleSCAModel()
{   
	//// *SCAReferenceExample Composite **************************************************************
	//// What about namespaces?
	//SCAModel::CompositePtr scaReferenceExample(new SCAModel::Composite());   
	//scaReferenceExample->setName("SCAReferenceCompositeExample");
	//scaReferenceExample->setLocal(true);
	//scaReferenceExample->setTargetNamespace("TrentinoNamespace");

	//// **SCAReferenceExampleService Service ********************************************************
	//SCAModel::ServicePtr scaReferenceExampleService(new SCAModel::Service());   
	//scaReferenceExampleService->setName("SCAReferenceExampleService");
	//scaReferenceExampleService->setPromote("SCAReferenceExampleComponent");
	//scaReferenceExample->serviceElements().push_back(scaReferenceExampleService);

	//// **SCAReferenceExampleReferences Reference *****************************************************
	//SCAModel::ReferencePtr scaReferenceExampleReferences(new SCAModel::Reference());   
	//scaReferenceExampleReferences->setName("SCAReferenceExampleReferences");
	//scaReferenceExampleReferences->setMultiplicity("0..n");
	//scaReferenceExampleReferences->promotes().push_back("SCAReferenceExampleComponent/SCAServicesToAttachRef");
	//scaReferenceExample->referenceElements().push_back(scaReferenceExampleReferences);

	//// ***Binding.sca Binding **********************************************************************
	//SCAModel::SCABindingPtr scaBinding(new SCAModel::SCABinding());   
	//scaReferenceExampleReferences->bindingElements().push_back(scaBinding);

	//// **Property3 Composite Property**************************************************************
	//SCAModel::PropertyPtr property3Composite(new SCAModel::Property());   
	//property3Composite->setName("Property3");
	//property3Composite->setMustSupply(true);
	//SCAModel::QNamePtr qname(new Trentino::XML::Schema::QName());
	//qname->fromString("xsd:boolean");
	//property3Composite->setType(qname);
	//scaReferenceExample->propertyElements().push_back(property3Composite);

	//// **SCAReferenceExampleComponent Component *****************************************************
	//SCAModel::ComponentPtr scaReferenceExampleComponent(new SCAModel::Component());   
	//scaReferenceExampleComponent->setName("SCAReferenceExampleComponent");
	//scaReferenceExample->componentElements().push_back(scaReferenceExampleComponent);

	//// ***SCAReferenceExampleComponent Implementation ************************************************
	//SCAModel::CPPImplementationPtr scaReferenceExampleComponentImpl(new SCAModel::CPPImplementation());
	//scaReferenceExampleComponentImpl->setHeader("SCAReferenceExampleImpl.h");
	//scaReferenceExampleComponentImpl->setLibrary("SCAReferenceExample");
	//scaReferenceExampleComponentImpl->setClazz("SCAReferenceExampleImpl");
	//scaReferenceExampleComponentImpl->setScope(SCAModel::CPPImplementationScopePtr(new SCAModel::CPPImplementationScope("composite")));
	//scaReferenceExampleComponent->setImplementation(scaReferenceExampleComponentImpl);

	//// ***Property1 Property in SCAReferenceExampleComponent ******************************************
	//SCAModel::PropertyValuePtr property1(new SCAModel::PropertyValue());
	//property1->setName("Property1");
	//property1->setValue("42");
	//scaReferenceExampleComponent->propertyElements().push_back(property1);

	//// ***Property2 Property in SCAReferenceExampleComponent ******************************************
	//SCAModel::PropertyValuePtr property2(new SCAModel::PropertyValue());
	//property2->setName("Property2");
	//property2->setValue("NewStringValueName");
	//scaReferenceExampleComponent->propertyElements().push_back(property2);

	//// ***MultiProperty Property in SCAReferenceExampleComponent ******************************************
	//// What to do when there are more than 1 value?
	//SCAModel::PropertyValuePtr multiProperty(new SCAModel::PropertyValue());
	//multiProperty->setName("MultiProperty");
	//multiProperty->setMany(true);
	//SCAModel::QNamePtr qname2(new Trentino::XML::Schema::QName());
	//qname2->fromString("xsd:string");
	//multiProperty->setType(qname2);
	//multiProperty->setValue("Value1");
	//multiProperty->setValue("Value2");
	//multiProperty->setValue("Value3");
	//scaReferenceExampleComponent->propertyElements().push_back(multiProperty);

	//// ***ValueFileProperty Property in SCAReferenceExampleComponent ******************************************
	//SCAModel::PropertyValuePtr valueFileProperty(new SCAModel::PropertyValue());
	//valueFileProperty->setName("ValueFileProperty");
	//SCAModel::QNamePtr qname3(new Trentino::XML::Schema::QName());
	//qname3->fromString("xsd:int");
	//valueFileProperty->setType(qname3);	
	//valueFileProperty->setFile("ValueFile.txt");
	//scaReferenceExampleComponent->propertyElements().push_back(valueFileProperty);

	//// ***Property3 Property in SCAReferenceExampleComponent ******************************************
	//SCAModel::PropertyValuePtr property3(new SCAModel::PropertyValue());
	//property3->setName("Property3");
	//SCAModel::QNamePtr qname4(new Trentino::XML::Schema::QName());
	//qname4->fromString("xsd:boolean");
	//property3->setType(qname4);	
	//property3->setSource("$Property3");
	//scaReferenceExampleComponent->propertyElements().push_back(property3);

	//// *SCAReferenceExample.Solution Composite **************************************************************
	//// What about namespaces?
	//SCAModel::CompositePtr scaReferenceExampleSolution(new SCAModel::Composite());   
	//scaReferenceExampleSolution->setName("SCAReferenceExample.Solution");
	//scaReferenceExampleSolution->setLocal(true);
	//scaReferenceExampleSolution->setTargetNamespace("TrentinoNamespace");

	//// **SCAReferenceExample.CompositeComponent Component *****************************************************
	//SCAModel::ComponentPtr scaReferenceExampleCompositeComponent(new SCAModel::Component());   
	//scaReferenceExampleCompositeComponent->setName("SCAReferenceExample.CompositeComponent");
	//scaReferenceExampleSolution->componentElements().push_back(scaReferenceExampleCompositeComponent);

	//// ***SCAReferenceExample.CompositeComponent Implementation ************************************************
	//SCAModel::SCAImplementationPtr scaReferenceExampleCompositeComponentImpl(new SCAModel::SCAImplementation());
	//SCAModel::QNamePtr qname5(new Trentino::XML::Schema::QName());
	//qname5->fromString("nsPrefix:SCAReferenceCompositeExample");
	//scaReferenceExampleCompositeComponentImpl->setName(qname5);
	//scaReferenceExampleCompositeComponent->setImplementation(scaReferenceExampleCompositeComponentImpl);

	//// ***Property3 Property in SCAReferenceExample.CompositeComponent ******************************************
	//SCAModel::PropertyValuePtr property3_compositeComponent(new SCAModel::PropertyValue());
	//property3_compositeComponent->setName("Property3");
	//property3_compositeComponent->setValue("false");
	//scaReferenceExampleCompositeComponent->propertyElements().push_back(property3_compositeComponent);


	//// **SCAReferenceComponentEx Component *****************************************************
	//SCAModel::ComponentPtr scaReferenceComponentEx(new SCAModel::Component());   
	//scaReferenceComponentEx->setName("SCAReferenceComponentEx");
	//scaReferenceExampleSolution->componentElements().push_back(scaReferenceComponentEx);

	//// ***SCAReferenceComponentEx Implementation ************************************************
	//SCAModel::CPPImplementationPtr scaReferenceComponentExImpl(new SCAModel::CPPImplementation());
	//scaReferenceComponentExImpl->setHeader("SCAReferenceExampleImpl.h");
	//scaReferenceComponentExImpl->setLibrary("SCAReferenceExample");
	//scaReferenceComponentExImpl->setClazz("SCAReferenceExampleImpl");
	//scaReferenceComponentExImpl->setComponentType("./SCAFolderExample");
	//scaReferenceComponentEx->setImplementation(scaReferenceComponentExImpl);

	//// ***Property3 Property in SCAReferenceComponentEx ******************************************
	//SCAModel::PropertyValuePtr property3_scaReferenceComponentEx(new SCAModel::PropertyValue());
	//property3_scaReferenceComponentEx->setName("Property3");
	//property3_scaReferenceComponentEx->setValue("true");
	//scaReferenceComponentEx->propertyElements().push_back(property3_scaReferenceComponentEx);

	//// ***MultiProperty Property in SCAReferenceComponentEx ******************************************
	//SCAModel::PropertyValuePtr MultiProperty_scaReferenceComponentEx(new SCAModel::PropertyValue());
	//MultiProperty_scaReferenceComponentEx->setName("MultiProperty");
	//MultiProperty_scaReferenceComponentEx->setValue("test");
	//scaReferenceComponentEx->propertyElements().push_back(MultiProperty_scaReferenceComponentEx);

	//// ***Property3 Property in SCAReferenceComponentEx ******************************************
	//SCAModel::PropertyValuePtr ValueFileProperty_scaReferenceComponentEx(new SCAModel::PropertyValue());
	//ValueFileProperty_scaReferenceComponentEx->setName("ValueFileProperty");
	//ValueFileProperty_scaReferenceComponentEx->setValue("23");
	//scaReferenceComponentEx->propertyElements().push_back(ValueFileProperty_scaReferenceComponentEx);

	//// SCAReferenceExampleImpl.componentType
	//SCAModel::ComponentTypePtr scaReferenceExampleImplComponentType(new SCAModel::ComponentType());
	//
	////SCAReferenceExampleService Service in SCAReferenceExampleImpl.componentType
	//SCAModel::ComponentServicePtr scaReferenceExampleService_(new SCAModel::ComponentService());
	//scaReferenceExampleService_->setName("SCAReferenceExampleService");
	//scaReferenceExampleImplComponentType->serviceElements().push_back(scaReferenceExampleService_);

	////CPPInterface of the service
	//SCAModel::CPPInterfacePtr scaReferenceExampleService_Interface(new SCAModel::CPPInterface());
	//scaReferenceExampleService_Interface->setHeader("../SCAReferenceExample.h");
	//scaReferenceExampleService_Interface->setClazz("SCAReferenceExample");
	//scaReferenceExampleService_->setInterface(scaReferenceExampleService_Interface);

	////SCAServiceToAttachRef reference in SCAReferenceExampleImpl.componentType
	//SCAModel::ComponentTypeReferencePtr SCAServiceToAttachRef(new SCAModel::ComponentTypeReference());
	//SCAServiceToAttachRef->setName("SCAServiceToAttachRef");
	//scaReferenceExampleImplComponentType->referenceElements().push_back(SCAServiceToAttachRef);
	//	
	////CPPInterface of the SCAServiceToAttachRef
	//SCAModel::CPPInterfacePtr SCAServiceToAttachRef_Interface(new SCAModel::CPPInterface());
	//SCAServiceToAttachRef_Interface->setHeader("./SCAServiceToAttach.h");
	//SCAServiceToAttachRef_Interface->setClazz("SCAServiceToAttach");
	//SCAServiceToAttachRef->setInterface(SCAServiceToAttachRef_Interface);

	////SCAServicesToAttachRef reference in SCAReferenceExampleImpl.componentType
	//SCAModel::ComponentTypeReferencePtr SCAServicesToAttachRef(new SCAModel::ComponentTypeReference());
	//SCAServicesToAttachRef->setName("SCAServicesToAttachRef");
	//scaReferenceExampleImplComponentType->referenceElements().push_back(SCAServicesToAttachRef);
	//	
	////CPPInterface of the SCAServicesToAttachRef
	//SCAModel::CPPInterfacePtr SCAServicesToAttachRef_Interface(new SCAModel::CPPInterface());
	//SCAServicesToAttachRef_Interface->setHeader("./SCAServiceToAttach.h");
	//SCAServicesToAttachRef_Interface->setClazz("SCAServiceToAttach");
	//SCAServicesToAttachRef->setInterface(SCAServicesToAttachRef_Interface);

	//// ***Property1 Property in scaReferenceExampleImplComponentType ******************************************
	//SCAModel::PropertyPtr property1_scaReferenceExampleImplComponentType(new SCAModel::Property());
	//property1_scaReferenceExampleImplComponentType->setName("Property1");
	//SCAModel::QNamePtr qname6(new Trentino::XML::Schema::QName());
	//qname6->fromString("xsd:int");
	//property1_scaReferenceExampleImplComponentType->setType(qname6);
	//scaReferenceExampleImplComponentType->propertyElements().push_back(property1_scaReferenceExampleImplComponentType);

	//// ***Property2 Property in scaReferenceExampleImplComponentType ******************************************
	//SCAModel::PropertyPtr property2_scaReferenceExampleImplComponentType(new SCAModel::Property());
	//property2_scaReferenceExampleImplComponentType->setName("Property2");
	//SCAModel::QNamePtr qname7(new Trentino::XML::Schema::QName());
	//qname7->fromString("xsd:string");
	//property2_scaReferenceExampleImplComponentType->setType(qname7);
	//property2_scaReferenceExampleImplComponentType->setValue("DefaultValue1");
	//scaReferenceExampleImplComponentType->propertyElements().push_back(property2_scaReferenceExampleImplComponentType);

	//// ***Property3 Property in scaReferenceExampleImplComponentType ******************************************
	//SCAModel::PropertyPtr property3_scaReferenceExampleImplComponentType(new SCAModel::Property());
	//property3_scaReferenceExampleImplComponentType->setName("Property3");
	//SCAModel::QNamePtr qname8(new Trentino::XML::Schema::QName());
	//qname8->fromString("xsd:boolean");
	//property3_scaReferenceExampleImplComponentType->setType(qname8);
	//property3_scaReferenceExampleImplComponentType->setMustSupply(true);
	//scaReferenceExampleImplComponentType->propertyElements().push_back(property3_scaReferenceExampleImplComponentType);
	//
	//// ***MultiProperty Property in scaReferenceExampleImplComponentType ******************************************
	//SCAModel::PropertyPtr MultiProperty_scaReferenceExampleImplComponentType(new SCAModel::Property());
	//MultiProperty_scaReferenceExampleImplComponentType->setName("MultiProperty");
	//SCAModel::QNamePtr qname9(new Trentino::XML::Schema::QName());
	//qname9->fromString("xsd:string");
	//MultiProperty_scaReferenceExampleImplComponentType->setType(qname9);
	//MultiProperty_scaReferenceExampleImplComponentType->setMustSupply(true);
	//MultiProperty_scaReferenceExampleImplComponentType->setMany(true);
	//scaReferenceExampleImplComponentType->propertyElements().push_back(MultiProperty_scaReferenceExampleImplComponentType);

	//// ***ValueFileProperty Property in scaReferenceExampleImplComponentType ******************************************
	//SCAModel::PropertyPtr ValueFileProperty_scaReferenceExampleImplComponentType(new SCAModel::Property());
	//ValueFileProperty_scaReferenceExampleImplComponentType->setName("ValueFileProperty");
	//SCAModel::QNamePtr qname10(new Trentino::XML::Schema::QName());
	//qname10->fromString("xsd:int");
	//ValueFileProperty_scaReferenceExampleImplComponentType->setType(qname10);
	//ValueFileProperty_scaReferenceExampleImplComponentType->setMustSupply(true);
	//scaReferenceExampleImplComponentType->propertyElements().push_back(ValueFileProperty_scaReferenceExampleImplComponentType);


   //create map
   SCAComponentMap scaComponentMap;

   return scaComponentMap;
}