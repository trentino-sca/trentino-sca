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
#include <TrentinoGlobal.h>
#include <Core/TrentinoCoreSCAModelLoader.h>

#include <SCAModel/TrentinoSCAModel.h>
#include <SCAModel/TrentinoSCAModelAppliesTo.h>
#include <SCAModel/TrentinoSCAModelAttributedQNameType.h>
#include <SCAModel/TrentinoSCAModelAttributedUnsignedLongType.h>
#include <SCAModel/TrentinoSCAModelAttributedURIType.h>
#include <SCAModel/TrentinoSCAModelBinding.h>
#include <SCAModel/TrentinoSCAModelBindingType.h>
#include <SCAModel/TrentinoSCAModelCallback.h>
#include <SCAModel/TrentinoSCAModelCommonExtensionBase.h>
#include <SCAModel/TrentinoSCAModelComponent.h>
#include <SCAModel/TrentinoSCAModelComponentReference.h>
#include <SCAModel/TrentinoSCAModelComponentService.h>
#include <SCAModel/TrentinoSCAModelComponentType.h>
#include <SCAModel/TrentinoSCAModelComponentTypeReference.h>
#include <SCAModel/TrentinoSCAModelComposite.h>
#include <SCAModel/TrentinoSCAModelContract.h>
#include <SCAModel/TrentinoSCAModelContributionType.h>
#include <SCAModel/TrentinoSCAModelCPPExport.h>
#include <SCAModel/TrentinoSCAModelCPPFunction.h>
#include <SCAModel/TrentinoSCAModelCPPImplementation.h>
#include <SCAModel/TrentinoSCAModelCPPImplementationFunction.h>
#include <SCAModel/TrentinoSCAModelCPPImplementationScope.h>
#include <SCAModel/TrentinoSCAModelCPPImport.h>
#include <SCAModel/TrentinoSCAModelCPPInterface.h>
#include <SCAModel/TrentinoSCAModelCreateResource.h>
#include <SCAModel/TrentinoSCAModelDeployableType.h>
#include <SCAModel/TrentinoSCAModelDocumentation.h>
#include <SCAModel/TrentinoSCAModelEndpointReferenceType.h>
#include <SCAModel/TrentinoSCAModelEnum.h>
#include <SCAModel/TrentinoSCAModelExport.h>
#include <SCAModel/TrentinoSCAModelExportType.h>
#include <SCAModel/TrentinoSCAModelExtensions.h>
#include <SCAModel/TrentinoSCAModelExternalAttachment.h>
#include <SCAModel/TrentinoSCAModelFactory.h>
#include <SCAModel/TrentinoSCAModelImplementation.h>
#include <SCAModel/TrentinoSCAModelImplementationType.h>
#include <SCAModel/TrentinoSCAModelImport.h>
#include <SCAModel/TrentinoSCAModelImportType.h>
#include <SCAModel/TrentinoSCAModelInclude.h>
#include <SCAModel/TrentinoSCAModelIntent.h>
#include <SCAModel/TrentinoSCAModelIntentMap.h>
#include <SCAModel/TrentinoSCAModelIntentQualifier.h>
#include <SCAModel/TrentinoSCAModelInteractionOrImplementation.h>
#include <SCAModel/TrentinoSCAModelInterface.h>
#include <SCAModel/TrentinoSCAModelMetadataType.h>
#include <SCAModel/TrentinoSCAModelObject.h>
#include <SCAModel/TrentinoSCAModelOperationSelectorType.h>
#include <SCAModel/TrentinoSCAModelOperatorContentType.h>
#include <SCAModel/TrentinoSCAModelOverrideOptions.h>
#include <SCAModel/TrentinoSCAModelPolicy.h>
#include <SCAModel/TrentinoSCAModelPolicyAttachment.h>
#include <SCAModel/TrentinoSCAModelPolicyreference.h>
#include <SCAModel/TrentinoSCAModelPolicySet.h>
#include <SCAModel/TrentinoSCAModelPolicySetAttachment.h>
#include <SCAModel/TrentinoSCAModelPolicySetReference.h>
#include <SCAModel/TrentinoSCAModelProblemActionType.h>
#include <SCAModel/TrentinoSCAModelProperty.h>
#include <SCAModel/TrentinoSCAModelPropertyValue.h>
#include <SCAModel/TrentinoSCAModelQualifier.h>
#include <SCAModel/TrentinoSCAModelReference.h>
#include <SCAModel/TrentinoSCAModelReferenceParametersType.h>
#include <SCAModel/TrentinoSCAModelRelatesToType.h>
#include <SCAModel/TrentinoSCAModelRequires.h>
#include <SCAModel/TrentinoSCAModelSCABinding.h>
#include <SCAModel/TrentinoSCAModelSCAImplementation.h>
#include <SCAModel/TrentinoSCAModelSCAPropertyBase.h>
#include <SCAModel/TrentinoSCAModelService.h>
#include <SCAModel/TrentinoSCAModelURI.h>
#include <SCAModel/TrentinoSCAModelValueType.h>
#include <SCAModel/TrentinoSCAModelWire.h>
#include <SCAModel/TrentinoSCAModelWireFormattype.h>

#ifdef WIN32
#ifdef SCAREFERENCEEXAMPLEGEN_EXPORTS
#undef SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT
#define SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT __declspec(dllexport)
#else
#undef SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT
#define SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT __declspec(dllimport)       
#endif //SCAREFERENCEEXAMPLEGEN_EXPORTS
#else
#define SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT
#endif //WIN32


// This is an example of an exported function.
extern "C" SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT void TRENTINO_CDECL loadModels(Trentino::Core::SCAModelLoader* modelLoader)
{
   assert(modelLoader != nullptr);

   Trentino::Core::SCAModelLoader::SCAModelFactory& factory = modelLoader->scaModelFactory();
   
   									Trentino::SCA::Model::Composite* const SCAReferenceExampleSolutionWrapper_SCAReferenceExampleSolution= factory.createComposite();
 
 									Trentino::SCA::Model::Component* const SCAReferenceExampleSolution_SCAReferenceExampleCompositeComponent= factory.createComponent();
								Trentino::SCA::Model::SCAImplementation* const SCAReferenceExampleCompositeComponent_SCAReferenceCompositeExample= factory.createSCAImplementation();

						
						Trentino::XML::Schema::QName* SCAReferenceExampleCompositeComponent_SCAReferenceCompositeExample_NameQName = factory.createQName("SCAReferenceCompositeExample", "TrentinoNamespace", "nsPrefix");
		 				SCAReferenceExampleCompositeComponent_SCAReferenceCompositeExample->setName(SCAReferenceExampleCompositeComponent_SCAReferenceCompositeExample_NameQName);
									

				 
							SCAReferenceExampleSolution_SCAReferenceExampleCompositeComponent->setImplementation(SCAReferenceExampleCompositeComponent_SCAReferenceCompositeExample);
 
 									Trentino::SCA::Model::PropertyValue* const SCAReferenceExampleCompositeComponent_Property3Property= factory.createPropertyValue();
								SCAReferenceExampleCompositeComponent_Property3Property->setMany(false);
								SCAReferenceExampleCompositeComponent_Property3Property->setName("Property3");
								SCAReferenceExampleCompositeComponent_Property3Property->setValue("false");
					

					SCAReferenceExampleSolution_SCAReferenceExampleCompositeComponent->addPropertyElement(SCAReferenceExampleCompositeComponent_Property3Property);
						SCAReferenceExampleSolution_SCAReferenceExampleCompositeComponent->setAutowire(false);
								SCAReferenceExampleSolution_SCAReferenceExampleCompositeComponent->setName("SCAReferenceExample.CompositeComponent");
							

					SCAReferenceExampleSolutionWrapper_SCAReferenceExampleSolution->addComponentElement(SCAReferenceExampleSolution_SCAReferenceExampleCompositeComponent);
 									Trentino::SCA::Model::Component* const SCAReferenceExampleSolution_SCAReferenceComponentEx= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const SCAReferenceComponentEx_SCAReferenceExampleImplImplementation= factory.createCPPImplementation();
						SCAReferenceComponentEx_SCAReferenceExampleImplImplementation->setAllowsPassByReference(false);
								SCAReferenceComponentEx_SCAReferenceExampleImplImplementation->setClazz("SCAReferenceExampleImpl");
								SCAReferenceComponentEx_SCAReferenceExampleImplImplementation->setComponentType("./SCAFolderExample");
								SCAReferenceComponentEx_SCAReferenceExampleImplImplementation->setEagerInit(false);
								SCAReferenceComponentEx_SCAReferenceExampleImplImplementation->setHeader("SCAReferenceExampleImpl.h");
								SCAReferenceComponentEx_SCAReferenceExampleImplImplementation->setLibrary("SCAReferenceExample");
									

				 
							SCAReferenceExampleSolution_SCAReferenceComponentEx->setImplementation(SCAReferenceComponentEx_SCAReferenceExampleImplImplementation);
 
 									Trentino::SCA::Model::PropertyValue* const SCAReferenceComponentEx_Property3Property3= factory.createPropertyValue();
								SCAReferenceComponentEx_Property3Property3->setMany(false);
								SCAReferenceComponentEx_Property3Property3->setName("Property3");
								SCAReferenceComponentEx_Property3Property3->setValue("true");
					

					SCAReferenceExampleSolution_SCAReferenceComponentEx->addPropertyElement(SCAReferenceComponentEx_Property3Property3);
 									Trentino::SCA::Model::PropertyValue* const SCAReferenceComponentEx_MultiPropertyProperty= factory.createPropertyValue();
								SCAReferenceComponentEx_MultiPropertyProperty->setMany(false);
								SCAReferenceComponentEx_MultiPropertyProperty->setName("MultiProperty");
								SCAReferenceComponentEx_MultiPropertyProperty->setValue("test");
					

					SCAReferenceExampleSolution_SCAReferenceComponentEx->addPropertyElement(SCAReferenceComponentEx_MultiPropertyProperty);
 									Trentino::SCA::Model::PropertyValue* const SCAReferenceComponentEx_ValueFilePropertyProperty= factory.createPropertyValue();
								SCAReferenceComponentEx_ValueFilePropertyProperty->setMany(false);
								SCAReferenceComponentEx_ValueFilePropertyProperty->setName("ValueFileProperty");
								SCAReferenceComponentEx_ValueFilePropertyProperty->setValue("23");
					

					SCAReferenceExampleSolution_SCAReferenceComponentEx->addPropertyElement(SCAReferenceComponentEx_ValueFilePropertyProperty);
						SCAReferenceExampleSolution_SCAReferenceComponentEx->setAutowire(false);
								SCAReferenceExampleSolution_SCAReferenceComponentEx->setName("SCAReferenceComponentEx");
							

					SCAReferenceExampleSolutionWrapper_SCAReferenceExampleSolution->addComponentElement(SCAReferenceExampleSolution_SCAReferenceComponentEx);
						SCAReferenceExampleSolutionWrapper_SCAReferenceExampleSolution->setAutowire(false);
								SCAReferenceExampleSolutionWrapper_SCAReferenceExampleSolution->setLocal(true);
								SCAReferenceExampleSolutionWrapper_SCAReferenceExampleSolution->setName("SCAReferenceExample.Solution");
								SCAReferenceExampleSolutionWrapper_SCAReferenceExampleSolution->setTargetNamespace("TrentinoNamespace");
							

				 
			


				Trentino::SCA::Model::ComponentType* const SCAReferenceExampleCompositeComponentCompTypeOfCompByImp= factory.createComponentType();
								Trentino::SCA::Model::Property* const SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_Property3Property2= factory.createProperty();
					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_Property3Property2->setMustSupply(true);
					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_Property3Property2->setMany(false);
					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_Property3Property2->setName("Property3");
					
						
						Trentino::XML::Schema::QName* SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_Property3Property2_TypeQName = factory.createQName("boolean", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_Property3Property2->setType(SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_Property3Property2_TypeQName);

					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp->addPropertyElement(SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_Property3Property2);
								Trentino::SCA::Model::ComponentTypeReference* const SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleReferences= factory.createComponentTypeReference();
					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleReferences->setAutowire(false);
					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleReferences->setMultiplicity("0..n");
					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleReferences->setNonOverridable(false);
					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleReferences->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const SCAReferenceExampleReferences_SCAServiceToAttachInterface= factory.createCPPInterface();
					SCAReferenceExampleReferences_SCAServiceToAttachInterface->setClazz("SCAServiceToAttach");
					SCAReferenceExampleReferences_SCAServiceToAttachInterface->setHeader("./SCAServiceToAttach.h");
					SCAReferenceExampleReferences_SCAServiceToAttachInterface->setRemotable(false);

							SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleReferences->setInterface(SCAReferenceExampleReferences_SCAServiceToAttachInterface);
					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleReferences->setName("SCAReferenceExampleReferences");

					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp->addReferenceElement(SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleReferences);
								Trentino::SCA::Model::ComponentService* const SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleService= factory.createComponentService();
				
							Trentino::SCA::Model::CPPInterface* const SCAReferenceExampleService_SCAReferenceExampleInterface= factory.createCPPInterface();
					SCAReferenceExampleService_SCAReferenceExampleInterface->setClazz("SCAReferenceExample");
					SCAReferenceExampleService_SCAReferenceExampleInterface->setHeader("./SCAReferenceExample.h");
					SCAReferenceExampleService_SCAReferenceExampleInterface->setRemotable(false);

							SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleService->setInterface(SCAReferenceExampleService_SCAReferenceExampleInterface);
					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleService->setName("SCAReferenceExampleService");

					SCAReferenceExampleCompositeComponentCompTypeOfCompByImp->addServiceElement(SCAReferenceExampleCompositeComponentCompTypeOfCompByImp_SCAReferenceExampleService);

			Trentino::SCA::Model::ComponentType* const SCAReferenceExampleImpl= factory.createComponentType();
								Trentino::SCA::Model::Property* const SCAReferenceExampleImpl_Property1Property= factory.createProperty();
					SCAReferenceExampleImpl_Property1Property->setMustSupply(false);
					SCAReferenceExampleImpl_Property1Property->setMany(false);
					SCAReferenceExampleImpl_Property1Property->setName("Property1");
					
						
						Trentino::XML::Schema::QName* SCAReferenceExampleImpl_Property1Property_TypeQName = factory.createQName("int", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				SCAReferenceExampleImpl_Property1Property->setType(SCAReferenceExampleImpl_Property1Property_TypeQName);

					SCAReferenceExampleImpl->addPropertyElement(SCAReferenceExampleImpl_Property1Property);
								Trentino::SCA::Model::Property* const SCAReferenceExampleImpl_Property2Property= factory.createProperty();
					SCAReferenceExampleImpl_Property2Property->setMustSupply(false);
					SCAReferenceExampleImpl_Property2Property->setMany(false);
					SCAReferenceExampleImpl_Property2Property->setName("Property2");
					
						
						Trentino::XML::Schema::QName* SCAReferenceExampleImpl_Property2Property_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				SCAReferenceExampleImpl_Property2Property->setType(SCAReferenceExampleImpl_Property2Property_TypeQName);
					SCAReferenceExampleImpl_Property2Property->setValue("DefaultValue1");

					SCAReferenceExampleImpl->addPropertyElement(SCAReferenceExampleImpl_Property2Property);
								Trentino::SCA::Model::Property* const SCAReferenceExampleImpl_Property3Property4= factory.createProperty();
					SCAReferenceExampleImpl_Property3Property4->setMustSupply(true);
					SCAReferenceExampleImpl_Property3Property4->setMany(false);
					SCAReferenceExampleImpl_Property3Property4->setName("Property3");
					
						
						Trentino::XML::Schema::QName* SCAReferenceExampleImpl_Property3Property4_TypeQName = factory.createQName("boolean", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				SCAReferenceExampleImpl_Property3Property4->setType(SCAReferenceExampleImpl_Property3Property4_TypeQName);

					SCAReferenceExampleImpl->addPropertyElement(SCAReferenceExampleImpl_Property3Property4);
								Trentino::SCA::Model::Property* const SCAReferenceExampleImpl_MultiPropertyProperty2= factory.createProperty();
					SCAReferenceExampleImpl_MultiPropertyProperty2->setMustSupply(true);
					SCAReferenceExampleImpl_MultiPropertyProperty2->setMany(true);
					SCAReferenceExampleImpl_MultiPropertyProperty2->setName("MultiProperty");
					
						
						Trentino::XML::Schema::QName* SCAReferenceExampleImpl_MultiPropertyProperty2_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				SCAReferenceExampleImpl_MultiPropertyProperty2->setType(SCAReferenceExampleImpl_MultiPropertyProperty2_TypeQName);

					SCAReferenceExampleImpl->addPropertyElement(SCAReferenceExampleImpl_MultiPropertyProperty2);
								Trentino::SCA::Model::Property* const SCAReferenceExampleImpl_ValueFilePropertyProperty2= factory.createProperty();
					SCAReferenceExampleImpl_ValueFilePropertyProperty2->setMustSupply(true);
					SCAReferenceExampleImpl_ValueFilePropertyProperty2->setMany(false);
					SCAReferenceExampleImpl_ValueFilePropertyProperty2->setName("ValueFileProperty");
					
						
						Trentino::XML::Schema::QName* SCAReferenceExampleImpl_ValueFilePropertyProperty2_TypeQName = factory.createQName("int", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				SCAReferenceExampleImpl_ValueFilePropertyProperty2->setType(SCAReferenceExampleImpl_ValueFilePropertyProperty2_TypeQName);

					SCAReferenceExampleImpl->addPropertyElement(SCAReferenceExampleImpl_ValueFilePropertyProperty2);
								Trentino::SCA::Model::ComponentTypeReference* const SCAReferenceExampleImpl_SCAServiceToAttachRef= factory.createComponentTypeReference();
					SCAReferenceExampleImpl_SCAServiceToAttachRef->setAutowire(true);
					SCAReferenceExampleImpl_SCAServiceToAttachRef->setMultiplicity("0..1");
					SCAReferenceExampleImpl_SCAServiceToAttachRef->setNonOverridable(false);
					SCAReferenceExampleImpl_SCAServiceToAttachRef->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const SCAServiceToAttachRef_SCAServiceToAttachInterface2= factory.createCPPInterface();
					SCAServiceToAttachRef_SCAServiceToAttachInterface2->setClazz("SCAServiceToAttach");
					SCAServiceToAttachRef_SCAServiceToAttachInterface2->setHeader("./SCAServiceToAttach.h");
					SCAServiceToAttachRef_SCAServiceToAttachInterface2->setRemotable(false);

							SCAReferenceExampleImpl_SCAServiceToAttachRef->setInterface(SCAServiceToAttachRef_SCAServiceToAttachInterface2);
					SCAReferenceExampleImpl_SCAServiceToAttachRef->setName("SCAServiceToAttachRef");

					SCAReferenceExampleImpl->addReferenceElement(SCAReferenceExampleImpl_SCAServiceToAttachRef);
								Trentino::SCA::Model::ComponentTypeReference* const SCAReferenceExampleImpl_SCAServicesToAttachRef= factory.createComponentTypeReference();
					SCAReferenceExampleImpl_SCAServicesToAttachRef->setAutowire(false);
					SCAReferenceExampleImpl_SCAServicesToAttachRef->setMultiplicity("0..n");
					SCAReferenceExampleImpl_SCAServicesToAttachRef->setNonOverridable(false);
					SCAReferenceExampleImpl_SCAServicesToAttachRef->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const SCAServicesToAttachRef_SCAServiceToAttachInterface3= factory.createCPPInterface();
					SCAServicesToAttachRef_SCAServiceToAttachInterface3->setClazz("SCAServiceToAttach");
					SCAServicesToAttachRef_SCAServiceToAttachInterface3->setHeader("./SCAServiceToAttach.h");
					SCAServicesToAttachRef_SCAServiceToAttachInterface3->setRemotable(false);

							SCAReferenceExampleImpl_SCAServicesToAttachRef->setInterface(SCAServicesToAttachRef_SCAServiceToAttachInterface3);
					SCAReferenceExampleImpl_SCAServicesToAttachRef->setName("SCAServicesToAttachRef");

					SCAReferenceExampleImpl->addReferenceElement(SCAReferenceExampleImpl_SCAServicesToAttachRef);
								Trentino::SCA::Model::ComponentService* const SCAReferenceExampleImpl_SCAReferenceExampleService2= factory.createComponentService();
				
							Trentino::SCA::Model::CPPInterface* const SCAReferenceExampleService2_SCAReferenceExampleInterface2= factory.createCPPInterface();
					SCAReferenceExampleService2_SCAReferenceExampleInterface2->setClazz("SCAReferenceExample");
					SCAReferenceExampleService2_SCAReferenceExampleInterface2->setHeader("./SCAReferenceExample.h");
					SCAReferenceExampleService2_SCAReferenceExampleInterface2->setRemotable(false);

							SCAReferenceExampleImpl_SCAReferenceExampleService2->setInterface(SCAReferenceExampleService2_SCAReferenceExampleInterface2);
					SCAReferenceExampleImpl_SCAReferenceExampleService2->setName("SCAReferenceExampleService");

					SCAReferenceExampleImpl->addServiceElement(SCAReferenceExampleImpl_SCAReferenceExampleService2);


			Trentino::SCA::Model::ContributionType* const Trentino_Contribution= factory.createContributionType();
						Trentino::SCA::Model::DeployableType* const Contribution_Deployable= factory.createDeployableType();
				Trentino::XML::Schema::QName* Contribution_Deployable_CompositeQName = factory.createQName("SCAReferenceExample.Solution", "TrentinoNamespace", "nsPrefix");
 				Contribution_Deployable->setComposite(Contribution_Deployable_CompositeQName);

				Trentino_Contribution->addDeployableElement(Contribution_Deployable);

	 modelLoader->associate(SCAReferenceExampleSolution_SCAReferenceExampleCompositeComponent , SCAReferenceExampleCompositeComponentCompTypeOfCompByImp); 
 modelLoader->associate(SCAReferenceExampleSolution_SCAReferenceComponentEx , SCAReferenceExampleImpl); 

}
