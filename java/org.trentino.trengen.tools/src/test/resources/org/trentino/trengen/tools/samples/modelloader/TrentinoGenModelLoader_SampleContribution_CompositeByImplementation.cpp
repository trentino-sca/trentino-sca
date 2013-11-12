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
#ifdef SAMPLECONTRIBUTIONCOMPOSITEBYIMPLGEN_EXPORTS
#undef SAMPLECONTRIBUTIONCOMPOSITEBYIMPLGEN_IMPORT_EXPORT
#define SAMPLECONTRIBUTIONCOMPOSITEBYIMPLGEN_IMPORT_EXPORT __declspec(dllexport)
#else
#undef SAMPLECONTRIBUTIONCOMPOSITEBYIMPLGEN_IMPORT_EXPORT
#define SAMPLECONTRIBUTIONCOMPOSITEBYIMPLGEN_IMPORT_EXPORT __declspec(dllimport)       
#endif //SAMPLECONTRIBUTIONCOMPOSITEBYIMPLGEN_EXPORTS
#else
#define SAMPLECONTRIBUTIONCOMPOSITEBYIMPLGEN_IMPORT_EXPORT
#endif //WIN32


// This is an example of an exported function.
extern "C" SAMPLECONTRIBUTIONCOMPOSITEBYIMPLGEN_IMPORT_EXPORT void TRENTINO_CDECL loadModels(Trentino::Core::SCAModelLoader* modelLoader)
{
   assert(modelLoader != nullptr);

   Trentino::Core::SCAModelLoader::SCAModelFactory& factory = modelLoader->scaModelFactory();
   
   									Trentino::SCA::Model::Composite* const localWrapper_local= factory.createComposite();
 
 									Trentino::SCA::Model::Component* const local_MyHelloWorldComponent= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const MyHelloWorldComponent_HelloWorldComponentImplementation= factory.createCPPImplementation();
						MyHelloWorldComponent_HelloWorldComponentImplementation->setAllowsPassByReference(false);
								MyHelloWorldComponent_HelloWorldComponentImplementation->setClazz("HelloWorldComponent");
								MyHelloWorldComponent_HelloWorldComponentImplementation->setEagerInit(false);
								MyHelloWorldComponent_HelloWorldComponentImplementation->setHeader("HelloWorldComponent.h");
								MyHelloWorldComponent_HelloWorldComponentImplementation->setLibrary("HelloWorldComponent");
								MyHelloWorldComponent_HelloWorldComponentImplementation->setPath("./HelloWorldComponent");
									

				 
							local_MyHelloWorldComponent->setImplementation(MyHelloWorldComponent_HelloWorldComponentImplementation);
 
 									Trentino::SCA::Model::ComponentService* const MyHelloWorldComponent_HelloWorldService= factory.createComponentService();
										Trentino::SCA::Model::CPPInterface* const HelloWorldService_HelloWorldServiceInterface= factory.createCPPInterface();
						HelloWorldService_HelloWorldServiceInterface->setClazz("HelloWorldService");
								HelloWorldService_HelloWorldServiceInterface->setHeader("/Services/HelloWorldService.h");
										HelloWorldService_HelloWorldServiceInterface->setRemotable(true);
							

				 
							MyHelloWorldComponent_HelloWorldService->setInterface(HelloWorldService_HelloWorldServiceInterface);
						MyHelloWorldComponent_HelloWorldService->setName("HelloWorldService");
							

					local_MyHelloWorldComponent->addServiceElement(MyHelloWorldComponent_HelloWorldService);
						local_MyHelloWorldComponent->setAutowire(false);
								local_MyHelloWorldComponent->setName("MyHelloWorldComponent");
							

					localWrapper_local->addComponentElement(local_MyHelloWorldComponent);
 									Trentino::SCA::Model::Component* const local_MyClientComponent= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const MyClientComponent_ClientComponentImplementation= factory.createCPPImplementation();
						MyClientComponent_ClientComponentImplementation->setAllowsPassByReference(false);
								MyClientComponent_ClientComponentImplementation->setClazz("ClientComponent");
								MyClientComponent_ClientComponentImplementation->setEagerInit(false);
								MyClientComponent_ClientComponentImplementation->setHeader("ClientComponent.h");
								MyClientComponent_ClientComponentImplementation->setLibrary("ClientComponent");
								MyClientComponent_ClientComponentImplementation->setPath("./ClientComponent");
											Trentino::SCA::Model::CPPImplementationScope* const ClientComponentImplementation_ClientComponentScope= factory.createCPPImplementationScope("Composite");
			

				 
							MyClientComponent_ClientComponentImplementation->setScope(ClientComponentImplementation_ClientComponentScope);
							

				 
							local_MyClientComponent->setImplementation(MyClientComponent_ClientComponentImplementation);
						local_MyClientComponent->setAutowire(false);
								local_MyClientComponent->setName("MyClientComponent");
							

					localWrapper_local->addComponentElement(local_MyClientComponent);
 									Trentino::SCA::Model::Component* const local_AccountDataService= factory.createComponent();
								Trentino::SCA::Model::SCAImplementation* const AccountDataService_CompositeByImpl= factory.createSCAImplementation();

						
						Trentino::XML::Schema::QName* AccountDataService_CompositeByImpl_NameQName = factory.createQName("CompositeByImpl", "http", "//docs.oasis-open.org/ns/opencsa/sca/200912:");
		 				AccountDataService_CompositeByImpl->setName(AccountDataService_CompositeByImpl_NameQName);
									

				 
							local_AccountDataService->setImplementation(AccountDataService_CompositeByImpl);
						local_AccountDataService->setAutowire(false);
								local_AccountDataService->setName("AccountDataService");
							

					localWrapper_local->addComponentElement(local_AccountDataService);
 
 									Trentino::SCA::Model::Reference* const local_compositeRefReference= factory.createReference();
						local_compositeRefReference->setMultiplicity("0..n");
		 
					local_compositeRefReference->addPromote("MyClientComponent/HelloWorldService");
										local_compositeRefReference->setWiredByImpl(false);
										local_compositeRefReference->setName("compositeRef");
							

					localWrapper_local->addReferenceElement(local_compositeRefReference);
						localWrapper_local->setAutowire(false);
								localWrapper_local->setLocal(false);
								localWrapper_local->setName("local");
								localWrapper_local->setTargetNamespace("TrentinoNamespace");
							

				 
			


				Trentino::SCA::Model::ComponentType* const HelloWorldComponent= factory.createComponentType();
								Trentino::SCA::Model::ComponentService* const HelloWorldComponent_HelloWorldService2= factory.createComponentService();
				
							Trentino::SCA::Model::CPPInterface* const HelloWorldService2_HelloWorldServiceInterface2= factory.createCPPInterface();
					HelloWorldService2_HelloWorldServiceInterface2->setClazz("HelloWorldService");
					HelloWorldService2_HelloWorldServiceInterface2->setHeader("/Services/HelloWorldService.h");
					HelloWorldService2_HelloWorldServiceInterface2->setRemotable(true);

							HelloWorldComponent_HelloWorldService2->setInterface(HelloWorldService2_HelloWorldServiceInterface2);
					HelloWorldComponent_HelloWorldService2->setName("HelloWorldService");

					HelloWorldComponent->addServiceElement(HelloWorldComponent_HelloWorldService2);

			Trentino::SCA::Model::ComponentType* const ClientComponent= factory.createComponentType();
								Trentino::SCA::Model::ComponentTypeReference* const ClientComponent_HelloWorldService3= factory.createComponentTypeReference();
					ClientComponent_HelloWorldService3->setAutowire(false);
					ClientComponent_HelloWorldService3->setMultiplicity("0..n");
					ClientComponent_HelloWorldService3->setNonOverridable(false);
					ClientComponent_HelloWorldService3->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const HelloWorldService3_HelloWorldServiceInterface3= factory.createCPPInterface();
					HelloWorldService3_HelloWorldServiceInterface3->setClazz("HelloWorldService");
					HelloWorldService3_HelloWorldServiceInterface3->setHeader("Services/HelloWorldService.h");
					HelloWorldService3_HelloWorldServiceInterface3->setRemotable(false);

							ClientComponent_HelloWorldService3->setInterface(HelloWorldService3_HelloWorldServiceInterface3);
					ClientComponent_HelloWorldService3->setName("HelloWorldService");

					ClientComponent->addReferenceElement(ClientComponent_HelloWorldService3);

			Trentino::SCA::Model::ComponentType* const AccountDataServiceCompTypeOfCompByImp= factory.createComponentType();
								Trentino::SCA::Model::Property* const AccountDataServiceCompTypeOfCompByImp_compositePropertyProperty= factory.createProperty();
					AccountDataServiceCompTypeOfCompByImp_compositePropertyProperty->setMustSupply(false);
					AccountDataServiceCompTypeOfCompByImp_compositePropertyProperty->setMany(false);
					AccountDataServiceCompTypeOfCompByImp_compositePropertyProperty->setName("compositeProperty");
					
						
						Trentino::XML::Schema::QName* AccountDataServiceCompTypeOfCompByImp_compositePropertyProperty_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				AccountDataServiceCompTypeOfCompByImp_compositePropertyProperty->setType(AccountDataServiceCompTypeOfCompByImp_compositePropertyProperty_TypeQName);

					AccountDataServiceCompTypeOfCompByImp->addPropertyElement(AccountDataServiceCompTypeOfCompByImp_compositePropertyProperty);
								Trentino::SCA::Model::ComponentTypeReference* const AccountDataServiceCompTypeOfCompByImp_compositeRef= factory.createComponentTypeReference();
					AccountDataServiceCompTypeOfCompByImp_compositeRef->setAutowire(false);
					AccountDataServiceCompTypeOfCompByImp_compositeRef->setMultiplicity("0..n");
					AccountDataServiceCompTypeOfCompByImp_compositeRef->setNonOverridable(false);
					AccountDataServiceCompTypeOfCompByImp_compositeRef->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const compositeRef_HelloWorldServiceInterface4= factory.createCPPInterface();
					compositeRef_HelloWorldServiceInterface4->setClazz("HelloWorldService");
					compositeRef_HelloWorldServiceInterface4->setHeader("Services/HelloWorldService.h");
					compositeRef_HelloWorldServiceInterface4->setRemotable(false);

							AccountDataServiceCompTypeOfCompByImp_compositeRef->setInterface(compositeRef_HelloWorldServiceInterface4);
					AccountDataServiceCompTypeOfCompByImp_compositeRef->setName("compositeRef");

					AccountDataServiceCompTypeOfCompByImp->addReferenceElement(AccountDataServiceCompTypeOfCompByImp_compositeRef);


			Trentino::SCA::Model::ContributionType* const Trentino_Contribution= factory.createContributionType();
						Trentino::SCA::Model::DeployableType* const Contribution_Deployable= factory.createDeployableType();
				Trentino::XML::Schema::QName* Contribution_Deployable_CompositeQName = factory.createQName("local", "TrentinoNamespace", "sample");
 				Contribution_Deployable->setComposite(Contribution_Deployable_CompositeQName);

				Trentino_Contribution->addDeployableElement(Contribution_Deployable);

	 modelLoader->associate(local_MyHelloWorldComponent , HelloWorldComponent); 
 modelLoader->associate(local_MyClientComponent , ClientComponent); 
 modelLoader->associate(local_AccountDataService , AccountDataServiceCompTypeOfCompByImp); 

}
