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
#ifdef SAMPLECONTRIBUTIONGEN_EXPORTS
#undef SAMPLECONTRIBUTIONGEN_IMPORT_EXPORT
#define SAMPLECONTRIBUTIONGEN_IMPORT_EXPORT __declspec(dllexport)
#else
#undef SAMPLECONTRIBUTIONGEN_IMPORT_EXPORT
#define SAMPLECONTRIBUTIONGEN_IMPORT_EXPORT __declspec(dllimport)       
#endif //SAMPLECONTRIBUTIONGEN_EXPORTS
#else
#define SAMPLECONTRIBUTIONGEN_IMPORT_EXPORT
#endif //WIN32


// This is an example of an exported function.
extern "C" SAMPLECONTRIBUTIONGEN_IMPORT_EXPORT void TRENTINO_CDECL loadModels(Trentino::Core::SCAModelLoader* modelLoader)
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
								MyHelloWorldComponent_HelloWorldComponentImplementation->setPath("../HelloWorldComponent/");
									

				 
							local_MyHelloWorldComponent->setImplementation(MyHelloWorldComponent_HelloWorldComponentImplementation);
 
 									Trentino::SCA::Model::PropertyValue* const MyHelloWorldComponent_ComponentFromProperty= factory.createPropertyValue();
						MyHelloWorldComponent_ComponentFromProperty->setSource("$complexFoo");
										MyHelloWorldComponent_ComponentFromProperty->setMany(false);
								MyHelloWorldComponent_ComponentFromProperty->setName("ComponentFrom");
					

					local_MyHelloWorldComponent->addPropertyElement(MyHelloWorldComponent_ComponentFromProperty);
 									Trentino::SCA::Model::PropertyValue* const MyHelloWorldComponent_ComponentToProperty= factory.createPropertyValue();
								MyHelloWorldComponent_ComponentToProperty->setMany(false);
								MyHelloWorldComponent_ComponentToProperty->setName("ComponentTo");
		
						
						Trentino::XML::Schema::QName* MyHelloWorldComponent_ComponentToProperty_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				MyHelloWorldComponent_ComponentToProperty->setType(MyHelloWorldComponent_ComponentToProperty_TypeQName);
								MyHelloWorldComponent_ComponentToProperty->setValue("Sinop");
					

					local_MyHelloWorldComponent->addPropertyElement(MyHelloWorldComponent_ComponentToProperty);
 									Trentino::SCA::Model::PropertyValue* const MyHelloWorldComponent_ComponentCCProperty= factory.createPropertyValue();
								MyHelloWorldComponent_ComponentCCProperty->setMany(false);
								MyHelloWorldComponent_ComponentCCProperty->setName("ComponentCC");
		
						
						Trentino::XML::Schema::QName* MyHelloWorldComponent_ComponentCCProperty_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				MyHelloWorldComponent_ComponentCCProperty->setType(MyHelloWorldComponent_ComponentCCProperty_TypeQName);
					

					local_MyHelloWorldComponent->addPropertyElement(MyHelloWorldComponent_ComponentCCProperty);
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
								MyClientComponent_ClientComponentImplementation->setPath("../ClientComponent");
											Trentino::SCA::Model::CPPImplementationScope* const ClientComponentImplementation_ClientComponentScope= factory.createCPPImplementationScope("Composite");
			

				 
							MyClientComponent_ClientComponentImplementation->setScope(ClientComponentImplementation_ClientComponentScope);
							

				 
							local_MyClientComponent->setImplementation(MyClientComponent_ClientComponentImplementation);
 
 									Trentino::SCA::Model::ComponentReference* const MyClientComponent_HelloWorldService2= factory.createComponentReference();
						MyClientComponent_HelloWorldService2->setAutowire(false);
								MyClientComponent_HelloWorldService2->setMultiplicity("0..1");
								MyClientComponent_HelloWorldService2->setNonOverridable(false);
								MyClientComponent_HelloWorldService2->setWiredByImpl(false);
												Trentino::SCA::Model::CPPInterface* const HelloWorldService2_HelloWorldServiceInterface2= factory.createCPPInterface();
						HelloWorldService2_HelloWorldServiceInterface2->setClazz("HelloWorldService");
								HelloWorldService2_HelloWorldServiceInterface2->setHeader("HelloWorldService.h");
										HelloWorldService2_HelloWorldServiceInterface2->setRemotable(false);
							

				 
							MyClientComponent_HelloWorldService2->setInterface(HelloWorldService2_HelloWorldServiceInterface2);
						MyClientComponent_HelloWorldService2->setName("HelloWorldService");
							

					local_MyClientComponent->addReferenceElement(MyClientComponent_HelloWorldService2);
						local_MyClientComponent->setAutowire(false);
								local_MyClientComponent->setName("MyClientComponent");
							

					localWrapper_local->addComponentElement(local_MyClientComponent);
 									Trentino::SCA::Model::Component* const local_IncludedComponent= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const IncludedComponent_IncludedComponentImplementation= factory.createCPPImplementation();
						IncludedComponent_IncludedComponentImplementation->setAllowsPassByReference(false);
								IncludedComponent_IncludedComponentImplementation->setClazz("IncludedComponent");
								IncludedComponent_IncludedComponentImplementation->setEagerInit(false);
								IncludedComponent_IncludedComponentImplementation->setHeader("IncludedComponent.h");
								IncludedComponent_IncludedComponentImplementation->setLibrary("IncludedComponent");
								IncludedComponent_IncludedComponentImplementation->setPath("./IncludedComponent");
									

				 
							local_IncludedComponent->setImplementation(IncludedComponent_IncludedComponentImplementation);
						local_IncludedComponent->setAutowire(false);
								local_IncludedComponent->setName("IncludedComponent");
							

					localWrapper_local->addComponentElement(local_IncludedComponent);
 
 									Trentino::SCA::Model::Include* const local_{http://docsoasis-openorg/ns/opencsa/sca/200912}local_inclusionInclude= factory.createInclude();

						
						Trentino::XML::Schema::QName* local_{http://docsoasis-openorg/ns/opencsa/sca/200912}local_inclusionInclude_NameQName = factory.createQName("local_inclusion", "http", "//docs.oasis-open.org/ns/opencsa/sca/200912:");
		 				local_{http://docsoasis-openorg/ns/opencsa/sca/200912}local_inclusionInclude->setName(local_{http://docsoasis-openorg/ns/opencsa/sca/200912}local_inclusionInclude_NameQName);
							

					localWrapper_local->addIncludeElement(local_{http://docsoasis-openorg/ns/opencsa/sca/200912}local_inclusionInclude);
 
 									Trentino::SCA::Model::Property* const local_CompositeToProperty= factory.createProperty();
						local_CompositeToProperty->setMustSupply(false);
										local_CompositeToProperty->setMany(false);
								local_CompositeToProperty->setName("CompositeTo");
		
						
						Trentino::XML::Schema::QName* local_CompositeToProperty_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				local_CompositeToProperty->setType(local_CompositeToProperty_TypeQName);
								local_CompositeToProperty->setValue("Sinop");
					

					localWrapper_local->addPropertyElement(local_CompositeToProperty);
 									Trentino::SCA::Model::Property* const local_fooProperty= factory.createProperty();
						local_fooProperty->setMustSupply(false);
				
						
						Trentino::XML::Schema::QName* local_fooProperty_QName = factory.createQName("someGed", "http", "//docs.oasis-open.org/ns/opencsa/sca/200912:");
		 				local_fooProperty->set(local_fooProperty_QName);
								local_fooProperty->setMany(false);
								local_fooProperty->setName("foo");
					

					localWrapper_local->addPropertyElement(local_fooProperty);
 									Trentino::SCA::Model::Property* const local_complexFooProperty= factory.createProperty();
						local_complexFooProperty->setMustSupply(false);
										local_complexFooProperty->setMany(false);
								local_complexFooProperty->setName("complexFoo");
		
						
						Trentino::XML::Schema::QName* local_complexFooProperty_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				local_complexFooProperty->setType(local_complexFooProperty_TypeQName);
					

					localWrapper_local->addPropertyElement(local_complexFooProperty);
 
 									Trentino::SCA::Model::Reference* const local_stockQuoteServiceReference= factory.createReference();
						local_stockQuoteServiceReference->setMultiplicity("0..1");
		 
					local_stockQuoteServiceReference->addPromote("MyClientComponent/HelloWorldService");
										local_stockQuoteServiceReference->setWiredByImpl(false);
				 
 									Trentino::SCA::Model::Binding* const stockQuoteServiceReference_Binding= factory.createBinding();
					

					local_stockQuoteServiceReference->addBindingElement(stockQuoteServiceReference_Binding);
								Trentino::SCA::Model::CPPInterface* const stockQuoteServiceReference_IpekInterface= factory.createCPPInterface();
						stockQuoteServiceReference_IpekInterface->setClazz("Ipek");
								stockQuoteServiceReference_IpekInterface->setHeader("Ipek.h");
										stockQuoteServiceReference_IpekInterface->setRemotable(false);
							

				 
							local_stockQuoteServiceReference->setInterface(stockQuoteServiceReference_IpekInterface);
						local_stockQuoteServiceReference->setName("stockQuoteService");
							

					localWrapper_local->addReferenceElement(local_stockQuoteServiceReference);
						localWrapper_local->setAutowire(false);
								localWrapper_local->setLocal(false);
								localWrapper_local->setName("local");
								localWrapper_local->setTargetNamespace("TrentinoNamespace");
							

				 
			

								Trentino::SCA::Model::Composite* const local2Wrapper_local2= factory.createComposite();
 
 									Trentino::SCA::Model::Component* const local2_MyHelloWorldComponent2= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const MyHelloWorldComponent2_HelloWorldComponentImplementation2= factory.createCPPImplementation();
						MyHelloWorldComponent2_HelloWorldComponentImplementation2->setAllowsPassByReference(false);
								MyHelloWorldComponent2_HelloWorldComponentImplementation2->setClazz("HelloWorldComponent");
								MyHelloWorldComponent2_HelloWorldComponentImplementation2->setEagerInit(false);
								MyHelloWorldComponent2_HelloWorldComponentImplementation2->setHeader("HelloWorldComponent.h");
								MyHelloWorldComponent2_HelloWorldComponentImplementation2->setLibrary("HelloWorldComponent");
								MyHelloWorldComponent2_HelloWorldComponentImplementation2->setPath("./HelloWorldComponent");
									

				 
							local2_MyHelloWorldComponent2->setImplementation(MyHelloWorldComponent2_HelloWorldComponentImplementation2);
 
 									Trentino::SCA::Model::PropertyValue* const MyHelloWorldComponent2_ComponentToProperty3= factory.createPropertyValue();
								MyHelloWorldComponent2_ComponentToProperty3->setMany(false);
								MyHelloWorldComponent2_ComponentToProperty3->setName("ComponentTo");
		
						
						Trentino::XML::Schema::QName* MyHelloWorldComponent2_ComponentToProperty3_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsd");
		 				MyHelloWorldComponent2_ComponentToProperty3->setType(MyHelloWorldComponent2_ComponentToProperty3_TypeQName);
								MyHelloWorldComponent2_ComponentToProperty3->setValue("Sinop");
					

					local2_MyHelloWorldComponent2->addPropertyElement(MyHelloWorldComponent2_ComponentToProperty3);
						local2_MyHelloWorldComponent2->setAutowire(false);
								local2_MyHelloWorldComponent2->setName("MyHelloWorldComponent2");
							

					local2Wrapper_local2->addComponentElement(local2_MyHelloWorldComponent2);
 									Trentino::SCA::Model::Component* const local2_MyClientComponent2= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const MyClientComponent2_ClientComponentImplementation2= factory.createCPPImplementation();
						MyClientComponent2_ClientComponentImplementation2->setAllowsPassByReference(false);
								MyClientComponent2_ClientComponentImplementation2->setClazz("ClientComponent");
								MyClientComponent2_ClientComponentImplementation2->setEagerInit(false);
								MyClientComponent2_ClientComponentImplementation2->setHeader("ClientComponent.h");
								MyClientComponent2_ClientComponentImplementation2->setLibrary("ClientComponent");
								MyClientComponent2_ClientComponentImplementation2->setPath("./ClientComponent");
											Trentino::SCA::Model::CPPImplementationScope* const ClientComponentImplementation2_ClientComponentScope2= factory.createCPPImplementationScope("Composite");
			

				 
							MyClientComponent2_ClientComponentImplementation2->setScope(ClientComponentImplementation2_ClientComponentScope2);
							

				 
							local2_MyClientComponent2->setImplementation(MyClientComponent2_ClientComponentImplementation2);
 
 									Trentino::SCA::Model::ComponentReference* const MyClientComponent2_HelloWorldService5= factory.createComponentReference();
						MyClientComponent2_HelloWorldService5->setAutowire(false);
								MyClientComponent2_HelloWorldService5->setMultiplicity("0..1");
								MyClientComponent2_HelloWorldService5->setNonOverridable(false);
								MyClientComponent2_HelloWorldService5->setWiredByImpl(false);
												Trentino::SCA::Model::CPPInterface* const HelloWorldService5_HelloWorldServiceInterface5= factory.createCPPInterface();
						HelloWorldService5_HelloWorldServiceInterface5->setClazz("HelloWorldService");
								HelloWorldService5_HelloWorldServiceInterface5->setHeader("HelloWorldService.h");
										HelloWorldService5_HelloWorldServiceInterface5->setRemotable(false);
							

				 
							MyClientComponent2_HelloWorldService5->setInterface(HelloWorldService5_HelloWorldServiceInterface5);
						MyClientComponent2_HelloWorldService5->setName("HelloWorldService");
							

					local2_MyClientComponent2->addReferenceElement(MyClientComponent2_HelloWorldService5);
						local2_MyClientComponent2->setAutowire(false);
								local2_MyClientComponent2->setName("MyClientComponent2");
							

					local2Wrapper_local2->addComponentElement(local2_MyClientComponent2);
						local2Wrapper_local2->setAutowire(false);
								local2Wrapper_local2->setLocal(false);
								local2Wrapper_local2->setName("local2");
								local2Wrapper_local2->setTargetNamespace("TrentinoNamespace");
							

				 
			


				Trentino::SCA::Model::ComponentType* const HelloWorldComponent= factory.createComponentType();
								Trentino::SCA::Model::Property* const HelloWorldComponent_ComponentFromProperty2= factory.createProperty();
					HelloWorldComponent_ComponentFromProperty2->setMustSupply(false);
					HelloWorldComponent_ComponentFromProperty2->setMany(false);
					HelloWorldComponent_ComponentFromProperty2->setName("ComponentFrom");
					
						
						Trentino::XML::Schema::QName* HelloWorldComponent_ComponentFromProperty2_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsdX");
		 				HelloWorldComponent_ComponentFromProperty2->setType(HelloWorldComponent_ComponentFromProperty2_TypeQName);

					HelloWorldComponent->addPropertyElement(HelloWorldComponent_ComponentFromProperty2);
								Trentino::SCA::Model::Property* const HelloWorldComponent_ComponentToProperty2= factory.createProperty();
					HelloWorldComponent_ComponentToProperty2->setMustSupply(true);
					HelloWorldComponent_ComponentToProperty2->setMany(false);
					HelloWorldComponent_ComponentToProperty2->setName("ComponentTo");
					
						
						Trentino::XML::Schema::QName* HelloWorldComponent_ComponentToProperty2_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsdX");
		 				HelloWorldComponent_ComponentToProperty2->setType(HelloWorldComponent_ComponentToProperty2_TypeQName);

					HelloWorldComponent->addPropertyElement(HelloWorldComponent_ComponentToProperty2);
								Trentino::SCA::Model::Property* const HelloWorldComponent_ComponentCCProperty2= factory.createProperty();
					HelloWorldComponent_ComponentCCProperty2->setMustSupply(false);
					HelloWorldComponent_ComponentCCProperty2->setMany(false);
					HelloWorldComponent_ComponentCCProperty2->setName("ComponentCC");
					
						
						Trentino::XML::Schema::QName* HelloWorldComponent_ComponentCCProperty2_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsdX");
		 				HelloWorldComponent_ComponentCCProperty2->setType(HelloWorldComponent_ComponentCCProperty2_TypeQName);

					HelloWorldComponent->addPropertyElement(HelloWorldComponent_ComponentCCProperty2);
								Trentino::SCA::Model::ComponentService* const HelloWorldComponent_HelloWorldService= factory.createComponentService();
				
							Trentino::SCA::Model::CPPInterface* const HelloWorldService_HelloWorldServiceInterface= factory.createCPPInterface();
					HelloWorldService_HelloWorldServiceInterface->setClazz("HelloWorldService");
					HelloWorldService_HelloWorldServiceInterface->setHeader("HelloWorldService.h");
					HelloWorldService_HelloWorldServiceInterface->setRemotable(false);

							HelloWorldComponent_HelloWorldService->setInterface(HelloWorldService_HelloWorldServiceInterface);
					HelloWorldComponent_HelloWorldService->setName("HelloWorldService");

					HelloWorldComponent->addServiceElement(HelloWorldComponent_HelloWorldService);

			Trentino::SCA::Model::ComponentType* const ClientComponent= factory.createComponentType();
								Trentino::SCA::Model::ComponentTypeReference* const ClientComponent_HelloWorldService3= factory.createComponentTypeReference();
					ClientComponent_HelloWorldService3->setAutowire(false);
					ClientComponent_HelloWorldService3->setMultiplicity("0..1");
					ClientComponent_HelloWorldService3->setNonOverridable(false);
					ClientComponent_HelloWorldService3->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const HelloWorldService3_HelloWorldServiceInterface3= factory.createCPPInterface();
					HelloWorldService3_HelloWorldServiceInterface3->setClazz("HelloWorldService");
					HelloWorldService3_HelloWorldServiceInterface3->setHeader("HelloWorldService.h");
					HelloWorldService3_HelloWorldServiceInterface3->setRemotable(false);

							ClientComponent_HelloWorldService3->setInterface(HelloWorldService3_HelloWorldServiceInterface3);
					ClientComponent_HelloWorldService3->setName("HelloWorldService");

					ClientComponent->addReferenceElement(ClientComponent_HelloWorldService3);

			Trentino::SCA::Model::ComponentType* const IncludedComponent= factory.createComponentType();
								Trentino::SCA::Model::ComponentTypeReference* const IncludedComponent_Ipek= factory.createComponentTypeReference();
					IncludedComponent_Ipek->setAutowire(false);
					IncludedComponent_Ipek->setMultiplicity("0..1");
					IncludedComponent_Ipek->setNonOverridable(false);
					IncludedComponent_Ipek->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const Ipek_IpekInterface2= factory.createCPPInterface();
					Ipek_IpekInterface2->setClazz("Ipek");
					Ipek_IpekInterface2->setHeader("Ipek.h");
					Ipek_IpekInterface2->setRemotable(false);

							IncludedComponent_Ipek->setInterface(Ipek_IpekInterface2);
					IncludedComponent_Ipek->setName("Ipek");

					IncludedComponent->addReferenceElement(IncludedComponent_Ipek);

			Trentino::SCA::Model::ComponentType* const HelloWorldComponent2= factory.createComponentType();
								Trentino::SCA::Model::Property* const HelloWorldComponent2_ComponentFromProperty3= factory.createProperty();
					HelloWorldComponent2_ComponentFromProperty3->setMustSupply(false);
					HelloWorldComponent2_ComponentFromProperty3->setMany(false);
					HelloWorldComponent2_ComponentFromProperty3->setName("ComponentFrom");
					
						
						Trentino::XML::Schema::QName* HelloWorldComponent2_ComponentFromProperty3_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsdX");
		 				HelloWorldComponent2_ComponentFromProperty3->setType(HelloWorldComponent2_ComponentFromProperty3_TypeQName);

					HelloWorldComponent2->addPropertyElement(HelloWorldComponent2_ComponentFromProperty3);
								Trentino::SCA::Model::Property* const HelloWorldComponent2_ComponentToProperty4= factory.createProperty();
					HelloWorldComponent2_ComponentToProperty4->setMustSupply(true);
					HelloWorldComponent2_ComponentToProperty4->setMany(false);
					HelloWorldComponent2_ComponentToProperty4->setName("ComponentTo");
					
						
						Trentino::XML::Schema::QName* HelloWorldComponent2_ComponentToProperty4_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsdX");
		 				HelloWorldComponent2_ComponentToProperty4->setType(HelloWorldComponent2_ComponentToProperty4_TypeQName);

					HelloWorldComponent2->addPropertyElement(HelloWorldComponent2_ComponentToProperty4);
								Trentino::SCA::Model::Property* const HelloWorldComponent2_ComponentCCProperty3= factory.createProperty();
					HelloWorldComponent2_ComponentCCProperty3->setMustSupply(false);
					HelloWorldComponent2_ComponentCCProperty3->setMany(false);
					HelloWorldComponent2_ComponentCCProperty3->setName("ComponentCC");
					
						
						Trentino::XML::Schema::QName* HelloWorldComponent2_ComponentCCProperty3_TypeQName = factory.createQName("string", "http", "//www.w3.org/2001/XMLSchema:xsdX");
		 				HelloWorldComponent2_ComponentCCProperty3->setType(HelloWorldComponent2_ComponentCCProperty3_TypeQName);

					HelloWorldComponent2->addPropertyElement(HelloWorldComponent2_ComponentCCProperty3);
								Trentino::SCA::Model::ComponentService* const HelloWorldComponent2_HelloWorldService4= factory.createComponentService();
				
							Trentino::SCA::Model::CPPInterface* const HelloWorldService4_HelloWorldServiceInterface4= factory.createCPPInterface();
					HelloWorldService4_HelloWorldServiceInterface4->setClazz("HelloWorldService");
					HelloWorldService4_HelloWorldServiceInterface4->setHeader("HelloWorldService.h");
					HelloWorldService4_HelloWorldServiceInterface4->setRemotable(false);

							HelloWorldComponent2_HelloWorldService4->setInterface(HelloWorldService4_HelloWorldServiceInterface4);
					HelloWorldComponent2_HelloWorldService4->setName("HelloWorldService");

					HelloWorldComponent2->addServiceElement(HelloWorldComponent2_HelloWorldService4);

			Trentino::SCA::Model::ComponentType* const ClientComponent2= factory.createComponentType();
								Trentino::SCA::Model::ComponentTypeReference* const ClientComponent2_HelloWorldService6= factory.createComponentTypeReference();
					ClientComponent2_HelloWorldService6->setAutowire(false);
					ClientComponent2_HelloWorldService6->setMultiplicity("0..1");
					ClientComponent2_HelloWorldService6->setNonOverridable(false);
					ClientComponent2_HelloWorldService6->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const HelloWorldService6_HelloWorldServiceInterface6= factory.createCPPInterface();
					HelloWorldService6_HelloWorldServiceInterface6->setClazz("HelloWorldService");
					HelloWorldService6_HelloWorldServiceInterface6->setHeader("HelloWorldService.h");
					HelloWorldService6_HelloWorldServiceInterface6->setRemotable(false);

							ClientComponent2_HelloWorldService6->setInterface(HelloWorldService6_HelloWorldServiceInterface6);
					ClientComponent2_HelloWorldService6->setName("HelloWorldService");

					ClientComponent2->addReferenceElement(ClientComponent2_HelloWorldService6);


			Trentino::SCA::Model::ContributionType* const Trentino_Contribution= factory.createContributionType();
						Trentino::SCA::Model::DeployableType* const Contribution_Deployable= factory.createDeployableType();
				Trentino::XML::Schema::QName* Contribution_Deployable_CompositeQName = factory.createQName("local", "TrentinoNamespace", "sample");
 				Contribution_Deployable->setComposite(Contribution_Deployable_CompositeQName);

				Trentino_Contribution->addDeployableElement(Contribution_Deployable);
						Trentino::SCA::Model::DeployableType* const Contribution_Deployable2= factory.createDeployableType();
				Trentino::XML::Schema::QName* Contribution_Deployable2_CompositeQName = factory.createQName("local2", "TrentinoNamespace", "sample");
 				Contribution_Deployable2->setComposite(Contribution_Deployable2_CompositeQName);

				Trentino_Contribution->addDeployableElement(Contribution_Deployable2);

	 modelLoader->associate(local_MyHelloWorldComponent , HelloWorldComponent); 
 modelLoader->associate(local_MyClientComponent , ClientComponent); 
 modelLoader->associate(local_IncludedComponent , IncludedComponent); 
 modelLoader->associate(local2_MyHelloWorldComponent2 , HelloWorldComponent2); 
 modelLoader->associate(local2_MyClientComponent2 , ClientComponent2); 

}
