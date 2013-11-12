// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2012 by Siemens AG. All rights reserved.
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
#include <Global/TrentinoGlobal.h>
#include <Runtime/Core/TrentinoCoreSCAModelLoader.h>

#include <Runtime/SCAModel/TrentinoSCAModel.h>
#include <Runtime/SCAModel/TrentinoSCAModelAppliesTo.h>
#include <Runtime/SCAModel/TrentinoSCAModelAttributedQNameType.h>
#include <Runtime/SCAModel/TrentinoSCAModelAttributedUnsignedLongType.h>
#include <Runtime/SCAModel/TrentinoSCAModelAttributedURIType.h>
#include <Runtime/SCAModel/TrentinoSCAModelBinding.h>
#include <Runtime/SCAModel/TrentinoSCAModelBindingType.h>
#include <Runtime/SCAModel/TrentinoSCAModelCallback.h>
#include <Runtime/SCAModel/TrentinoSCAModelCommonExtensionBase.h>
#include <Runtime/SCAModel/TrentinoSCAModelComponent.h>
#include <Runtime/SCAModel/TrentinoSCAModelComponentReference.h>
#include <Runtime/SCAModel/TrentinoSCAModelComponentService.h>
#include <Runtime/SCAModel/TrentinoSCAModelComponentType.h>
#include <Runtime/SCAModel/TrentinoSCAModelComponentTypeReference.h>
#include <Runtime/SCAModel/TrentinoSCAModelComposite.h>
#include <Runtime/SCAModel/TrentinoSCAModelContract.h>
#include <Runtime/SCAModel/TrentinoSCAModelContributionType.h>
#include <Runtime/SCAModel/TrentinoSCAModelCPPExport.h>
#include <Runtime/SCAModel/TrentinoSCAModelCPPFunction.h>
#include <Runtime/SCAModel/TrentinoSCAModelCPPImplementation.h>
#include <Runtime/SCAModel/TrentinoSCAModelCPPImplementationFunction.h>
#include <Runtime/SCAModel/TrentinoSCAModelCPPImplementationScope.h>
#include <Runtime/SCAModel/TrentinoSCAModelCPPImport.h>
#include <Runtime/SCAModel/TrentinoSCAModelCPPInterface.h>
#include <Runtime/SCAModel/TrentinoSCAModelCreateResource.h>
#include <Runtime/SCAModel/TrentinoSCAModelDeployableType.h>
#include <Runtime/SCAModel/TrentinoSCAModelDocumentation.h>
#include <Runtime/SCAModel/TrentinoSCAModelEndpointReferenceType.h>
#include <Runtime/SCAModel/TrentinoSCAModelEnum.h>
#include <Runtime/SCAModel/TrentinoSCAModelExport.h>
#include <Runtime/SCAModel/TrentinoSCAModelExportType.h>
#include <Runtime/SCAModel/TrentinoSCAModelExtensions.h>
#include <Runtime/SCAModel/TrentinoSCAModelExternalAttachment.h>
#include <Runtime/SCAModel/TrentinoSCAModelFactory.h>
#include <Runtime/SCAModel/TrentinoSCAModelImplementation.h>
#include <Runtime/SCAModel/TrentinoSCAModelImplementationType.h>
#include <Runtime/SCAModel/TrentinoSCAModelImport.h>
#include <Runtime/SCAModel/TrentinoSCAModelImportType.h>
#include <Runtime/SCAModel/TrentinoSCAModelInclude.h>
#include <Runtime/SCAModel/TrentinoSCAModelIntent.h>
#include <Runtime/SCAModel/TrentinoSCAModelIntentMap.h>
#include <Runtime/SCAModel/TrentinoSCAModelIntentQualifier.h>
#include <Runtime/SCAModel/TrentinoSCAModelInteractionOrImplementation.h>
#include <Runtime/SCAModel/TrentinoSCAModelInterface.h>
#include <Runtime/SCAModel/TrentinoSCAModelMetadataType.h>
#include <Runtime/SCAModel/TrentinoSCAModelObject.h>
#include <Runtime/SCAModel/TrentinoSCAModelOperationSelectorType.h>
#include <Runtime/SCAModel/TrentinoSCAModelOperatorContentType.h>
#include <Runtime/SCAModel/TrentinoSCAModelOverrideOptions.h>
#include <Runtime/SCAModel/TrentinoSCAModelPolicy.h>
#include <Runtime/SCAModel/TrentinoSCAModelPolicyAttachment.h>
#include <Runtime/SCAModel/TrentinoSCAModelPolicyreference.h>
#include <Runtime/SCAModel/TrentinoSCAModelPolicySet.h>
#include <Runtime/SCAModel/TrentinoSCAModelPolicySetAttachment.h>
#include <Runtime/SCAModel/TrentinoSCAModelPolicySetReference.h>
#include <Runtime/SCAModel/TrentinoSCAModelProblemActionType.h>
#include <Runtime/SCAModel/TrentinoSCAModelProperty.h>
#include <Runtime/SCAModel/TrentinoSCAModelPropertyValue.h>
#include <Runtime/SCAModel/TrentinoSCAModelQualifier.h>
#include <Runtime/SCAModel/TrentinoSCAModelReference.h>
#include <Runtime/SCAModel/TrentinoSCAModelReferenceParametersType.h>
#include <Runtime/SCAModel/TrentinoSCAModelRelatesToType.h>
#include <Runtime/SCAModel/TrentinoSCAModelRequires.h>
#include <Runtime/SCAModel/TrentinoSCAModelSCABinding.h>
#include <Runtime/SCAModel/TrentinoSCAModelSCAImplementation.h>
#include <Runtime/SCAModel/TrentinoSCAModelSCAPropertyBase.h>
#include <Runtime/SCAModel/TrentinoSCAModelService.h>
#include <Runtime/SCAModel/TrentinoSCAModelURI.h>
#include <Runtime/SCAModel/TrentinoSCAModelValueType.h>
#include <Runtime/SCAModel/TrentinoSCAModelWire.h>
#include <Runtime/SCAModel/TrentinoSCAModelWireFormattype.h>

#ifdef WIN32
#ifdef LOCALCALLDATAEXCHANGEGEN_EXPORTS
#undef LOCALCALLDATAEXCHANGEGEN_IMPORT_EXPORT
#define LOCALCALLDATAEXCHANGEGEN_IMPORT_EXPORT __declspec(dllexport)
#else
#undef LOCALCALLDATAEXCHANGEGEN_IMPORT_EXPORT
#define LOCALCALLDATAEXCHANGEGEN_IMPORT_EXPORT __declspec(dllimport)       
#endif //LOCALCALLDATAEXCHANGEGEN_EXPORTS
#else
#define LOCALCALLDATAEXCHANGEGEN_IMPORT_EXPORT
#endif //WIN32


// This is an example of an exported function.
extern "C" LOCALCALLDATAEXCHANGEGEN_IMPORT_EXPORT void TRENTINO_CDECL loadModels(Trentino::Core::SCAModelLoader* modelLoader)
{
   assert(modelLoader != nullptr);

   Trentino::Core::SCAModelLoader::SCAModelFactory& factory = modelLoader->scaModelFactory();
   
   									Trentino::SCA::Model::Composite* const LocalCallDataExchangeCompositeWrapper_LocalCallDataExchangeComposite= factory.createComposite();
 
 
									Trentino::SCA::Model::Component* const LocalCallDataExchangeComposite_ServiceAImpl= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const ServiceAImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation= factory.createCPPImplementation();
						ServiceAImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation->setAllowsPassByReference(false);
								ServiceAImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation->setClazz("Trentino::LocalCallDataExchange::ServiceAImpl");
								ServiceAImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation->setEagerInit(false);
								ServiceAImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation->setHeader("TrentinoLocalCallDataExchangeServiceABImpl.h");
								ServiceAImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation->setLibrary("LocalCallDataExchange");
											Trentino::SCA::Model::CPPImplementationScope* const TrentinoLocalCallDataExchangeServiceABImplImplementation_TrentinoLocalCallDataExchangeServiceABImplScope= factory.createCPPImplementationScope("Composite");
			

				 
							ServiceAImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation->setScope(TrentinoLocalCallDataExchangeServiceABImplImplementation_TrentinoLocalCallDataExchangeServiceABImplScope);
							

				 
							LocalCallDataExchangeComposite_ServiceAImpl->setImplementation(ServiceAImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation);
 
 
									Trentino::SCA::Model::ComponentReference* const ServiceAImpl_ServiceB= factory.createComponentReference();
						ServiceAImpl_ServiceB->setAutowire(false);
								ServiceAImpl_ServiceB->setMultiplicity("1..1");
								ServiceAImpl_ServiceB->setNonOverridable(false);
								ServiceAImpl_ServiceB->setWiredByImpl(false);
												Trentino::SCA::Model::CPPInterface* const ServiceB_TrentinoLocalCallDataExchangeServiceABInterface2= factory.createCPPInterface();
						ServiceB_TrentinoLocalCallDataExchangeServiceABInterface2->setClazz("Trentino::LocalCallDataExchange::ServiceB");
								ServiceB_TrentinoLocalCallDataExchangeServiceABInterface2->setHeader("TrentinoLocalCallDataExchangeServiceAB.h");
										ServiceB_TrentinoLocalCallDataExchangeServiceABInterface2->setRemotable(false);
							

				 
							ServiceAImpl_ServiceB->setInterface(ServiceB_TrentinoLocalCallDataExchangeServiceABInterface2);
						ServiceAImpl_ServiceB->setName("ServiceB");
							

					LocalCallDataExchangeComposite_ServiceAImpl->addReferenceElement(ServiceAImpl_ServiceB);
 
 
									Trentino::SCA::Model::ComponentService* const ServiceAImpl_ServiceA= factory.createComponentService();
										Trentino::SCA::Model::CPPInterface* const ServiceA_TrentinoLocalCallDataExchangeServiceABInterface= factory.createCPPInterface();
						ServiceA_TrentinoLocalCallDataExchangeServiceABInterface->setClazz("Trentino::LocalCallDataExchange::ServiceA");
								ServiceA_TrentinoLocalCallDataExchangeServiceABInterface->setHeader("TrentinoLocalCallDataExchangeServiceAB.h");
										ServiceA_TrentinoLocalCallDataExchangeServiceABInterface->setRemotable(false);
							

				 
							ServiceAImpl_ServiceA->setInterface(ServiceA_TrentinoLocalCallDataExchangeServiceABInterface);
						ServiceAImpl_ServiceA->setName("ServiceA");
							

					LocalCallDataExchangeComposite_ServiceAImpl->addServiceElement(ServiceAImpl_ServiceA);
						LocalCallDataExchangeComposite_ServiceAImpl->setAutowire(false);
								LocalCallDataExchangeComposite_ServiceAImpl->setName("ServiceAImpl");
							

					LocalCallDataExchangeCompositeWrapper_LocalCallDataExchangeComposite->addComponentElement(LocalCallDataExchangeComposite_ServiceAImpl);
									Trentino::SCA::Model::Component* const LocalCallDataExchangeComposite_ServiceBImpl= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const ServiceBImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation2= factory.createCPPImplementation();
						ServiceBImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation2->setAllowsPassByReference(false);
								ServiceBImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation2->setClazz("Trentino::LocalCallDataExchange::ServiceBImpl");
								ServiceBImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation2->setEagerInit(false);
								ServiceBImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation2->setHeader("TrentinoLocalCallDataExchangeServiceABImpl.h");
								ServiceBImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation2->setLibrary("LocalCallDataExchange");
											Trentino::SCA::Model::CPPImplementationScope* const TrentinoLocalCallDataExchangeServiceABImplImplementation2_TrentinoLocalCallDataExchangeServiceABImplScope2= factory.createCPPImplementationScope("Composite");
			

				 
							ServiceBImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation2->setScope(TrentinoLocalCallDataExchangeServiceABImplImplementation2_TrentinoLocalCallDataExchangeServiceABImplScope2);
							

				 
							LocalCallDataExchangeComposite_ServiceBImpl->setImplementation(ServiceBImpl_TrentinoLocalCallDataExchangeServiceABImplImplementation2);
 
 
									Trentino::SCA::Model::ComponentReference* const ServiceBImpl_ServiceA3= factory.createComponentReference();
						ServiceBImpl_ServiceA3->setAutowire(false);
								ServiceBImpl_ServiceA3->setMultiplicity("1..1");
								ServiceBImpl_ServiceA3->setNonOverridable(false);
								ServiceBImpl_ServiceA3->setWiredByImpl(false);
												Trentino::SCA::Model::CPPInterface* const ServiceA3_TrentinoLocalCallDataExchangeServiceABInterface6= factory.createCPPInterface();
						ServiceA3_TrentinoLocalCallDataExchangeServiceABInterface6->setClazz("Trentino::LocalCallDataExchange::ServiceA");
								ServiceA3_TrentinoLocalCallDataExchangeServiceABInterface6->setHeader("TrentinoLocalCallDataExchangeServiceAB.h");
										ServiceA3_TrentinoLocalCallDataExchangeServiceABInterface6->setRemotable(false);
							

				 
							ServiceBImpl_ServiceA3->setInterface(ServiceA3_TrentinoLocalCallDataExchangeServiceABInterface6);
						ServiceBImpl_ServiceA3->setName("ServiceA");
							

					LocalCallDataExchangeComposite_ServiceBImpl->addReferenceElement(ServiceBImpl_ServiceA3);
 
 
									Trentino::SCA::Model::ComponentService* const ServiceBImpl_ServiceB3= factory.createComponentService();
										Trentino::SCA::Model::CPPInterface* const ServiceB3_TrentinoLocalCallDataExchangeServiceABInterface5= factory.createCPPInterface();
						ServiceB3_TrentinoLocalCallDataExchangeServiceABInterface5->setClazz("Trentino::LocalCallDataExchange::ServiceB");
								ServiceB3_TrentinoLocalCallDataExchangeServiceABInterface5->setHeader("TrentinoLocalCallDataExchangeServiceAB.h");
										ServiceB3_TrentinoLocalCallDataExchangeServiceABInterface5->setRemotable(false);
							

				 
							ServiceBImpl_ServiceB3->setInterface(ServiceB3_TrentinoLocalCallDataExchangeServiceABInterface5);
						ServiceBImpl_ServiceB3->setName("ServiceB");
							

					LocalCallDataExchangeComposite_ServiceBImpl->addServiceElement(ServiceBImpl_ServiceB3);
						LocalCallDataExchangeComposite_ServiceBImpl->setAutowire(false);
								LocalCallDataExchangeComposite_ServiceBImpl->setName("ServiceBImpl");
							

					LocalCallDataExchangeCompositeWrapper_LocalCallDataExchangeComposite->addComponentElement(LocalCallDataExchangeComposite_ServiceBImpl);
						LocalCallDataExchangeCompositeWrapper_LocalCallDataExchangeComposite->setAutowire(false);
								LocalCallDataExchangeCompositeWrapper_LocalCallDataExchangeComposite->setLocal(false);
								LocalCallDataExchangeCompositeWrapper_LocalCallDataExchangeComposite->setName("LocalCallDataExchangeComposite");
								LocalCallDataExchangeCompositeWrapper_LocalCallDataExchangeComposite->setTargetNamespace("LocalCallDataExchangeNamespace");
							

				 
			


				Trentino::SCA::Model::ComponentType* const ServiceAImpl= factory.createComponentType();
								Trentino::SCA::Model::ComponentTypeReference* const ServiceAImpl_ServiceB2= factory.createComponentTypeReference();
					ServiceAImpl_ServiceB2->setAutowire(false);
					ServiceAImpl_ServiceB2->setMultiplicity("1..1");
					ServiceAImpl_ServiceB2->setNonOverridable(false);
					ServiceAImpl_ServiceB2->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const ServiceB2_TrentinoLocalCallDataExchangeServiceABInterface4= factory.createCPPInterface();
					ServiceB2_TrentinoLocalCallDataExchangeServiceABInterface4->setClazz("Trentino::LocalCallDataExchange::ServiceB");
					ServiceB2_TrentinoLocalCallDataExchangeServiceABInterface4->setHeader("TrentinoLocalCallDataExchangeServiceAB.h");
					ServiceB2_TrentinoLocalCallDataExchangeServiceABInterface4->setRemotable(false);

							ServiceAImpl_ServiceB2->setInterface(ServiceB2_TrentinoLocalCallDataExchangeServiceABInterface4);
					ServiceAImpl_ServiceB2->setName("ServiceB");

					ServiceAImpl->addReferenceElement(ServiceAImpl_ServiceB2);
								Trentino::SCA::Model::ComponentService* const ServiceAImpl_ServiceA2= factory.createComponentService();
				
							Trentino::SCA::Model::CPPInterface* const ServiceA2_TrentinoLocalCallDataExchangeServiceABInterface3= factory.createCPPInterface();
					ServiceA2_TrentinoLocalCallDataExchangeServiceABInterface3->setClazz("Trentino::LocalCallDataExchange::ServiceA");
					ServiceA2_TrentinoLocalCallDataExchangeServiceABInterface3->setHeader("TrentinoLocalCallDataExchangeServiceAB.h");
					ServiceA2_TrentinoLocalCallDataExchangeServiceABInterface3->setRemotable(false);

							ServiceAImpl_ServiceA2->setInterface(ServiceA2_TrentinoLocalCallDataExchangeServiceABInterface3);
					ServiceAImpl_ServiceA2->setName("ServiceA");

					ServiceAImpl->addServiceElement(ServiceAImpl_ServiceA2);

			Trentino::SCA::Model::ComponentType* const ServiceBImpl= factory.createComponentType();
								Trentino::SCA::Model::ComponentTypeReference* const ServiceBImpl_ServiceA4= factory.createComponentTypeReference();
					ServiceBImpl_ServiceA4->setAutowire(false);
					ServiceBImpl_ServiceA4->setMultiplicity("1..1");
					ServiceBImpl_ServiceA4->setNonOverridable(false);
					ServiceBImpl_ServiceA4->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const ServiceA4_TrentinoLocalCallDataExchangeServiceABInterface8= factory.createCPPInterface();
					ServiceA4_TrentinoLocalCallDataExchangeServiceABInterface8->setClazz("Trentino::LocalCallDataExchange::ServiceA");
					ServiceA4_TrentinoLocalCallDataExchangeServiceABInterface8->setHeader("TrentinoLocalCallDataExchangeServiceAB.h");
					ServiceA4_TrentinoLocalCallDataExchangeServiceABInterface8->setRemotable(false);

							ServiceBImpl_ServiceA4->setInterface(ServiceA4_TrentinoLocalCallDataExchangeServiceABInterface8);
					ServiceBImpl_ServiceA4->setName("ServiceA");

					ServiceBImpl->addReferenceElement(ServiceBImpl_ServiceA4);
								Trentino::SCA::Model::ComponentService* const ServiceBImpl_ServiceB4= factory.createComponentService();
				
							Trentino::SCA::Model::CPPInterface* const ServiceB4_TrentinoLocalCallDataExchangeServiceABInterface7= factory.createCPPInterface();
					ServiceB4_TrentinoLocalCallDataExchangeServiceABInterface7->setClazz("Trentino::LocalCallDataExchange::ServiceB");
					ServiceB4_TrentinoLocalCallDataExchangeServiceABInterface7->setHeader("TrentinoLocalCallDataExchangeServiceAB.h");
					ServiceB4_TrentinoLocalCallDataExchangeServiceABInterface7->setRemotable(false);

							ServiceBImpl_ServiceB4->setInterface(ServiceB4_TrentinoLocalCallDataExchangeServiceABInterface7);
					ServiceBImpl_ServiceB4->setName("ServiceB");

					ServiceBImpl->addServiceElement(ServiceBImpl_ServiceB4);


			Trentino::SCA::Model::ContributionType* const Trentino_Contribution= factory.createContributionType();
						Trentino::SCA::Model::DeployableType* const Contribution_Deployable= factory.createDeployableType();
				Trentino::XML::Schema::QName* Contribution_Deployable_CompositeQName = factory.createQName("LocalCallDataExchangeComposite", "LocalCallDataExchangeNamespace", "sample");
 				Contribution_Deployable->setComposite(Contribution_Deployable_CompositeQName);

				Trentino_Contribution->addDeployableElement(Contribution_Deployable);

	 modelLoader->associate(LocalCallDataExchangeComposite_ServiceAImpl , ServiceAImpl); 
 modelLoader->associate(LocalCallDataExchangeComposite_ServiceBImpl , ServiceBImpl); 

}