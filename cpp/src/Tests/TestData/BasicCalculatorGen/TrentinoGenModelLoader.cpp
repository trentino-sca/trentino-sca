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
#ifdef BASICCALCULATORGEN_EXPORTS
#undef BASICCALCULATORGEN_IMPORT_EXPORT
#define BASICCALCULATORGEN_IMPORT_EXPORT __declspec(dllexport)
#else
#undef BASICCALCULATORGEN_IMPORT_EXPORT
#define BASICCALCULATORGEN_IMPORT_EXPORT __declspec(dllimport)       
#endif //BASICCALCULATORGEN_EXPORTS
#else
#define BASICCALCULATORGEN_IMPORT_EXPORT
#endif //WIN32


// This is an example of an exported function.
extern "C" BASICCALCULATORGEN_IMPORT_EXPORT void TRENTINO_CDECL loadModels(Trentino::Core::SCAModelLoader* modelLoader)
{
   assert(modelLoader != nullptr);

   Trentino::Core::SCAModelLoader::SCAModelFactory& factory = modelLoader->scaModelFactory();
   
   									Trentino::SCA::Model::Composite* const BasicCalculatorCompositeWrapper_BasicCalculatorComposite= factory.createComposite();
 
 
									Trentino::SCA::Model::Component* const BasicCalculatorComposite_CalculatorImpl= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const CalculatorImpl_TrentinoExampleBasicCalculatorCalculatorImplImplementation= factory.createCPPImplementation();
						CalculatorImpl_TrentinoExampleBasicCalculatorCalculatorImplImplementation->setAllowsPassByReference(false);
								CalculatorImpl_TrentinoExampleBasicCalculatorCalculatorImplImplementation->setClazz("Trentino::Example::BasicCalculator::CalculatorImpl");
								CalculatorImpl_TrentinoExampleBasicCalculatorCalculatorImplImplementation->setEagerInit(false);
								CalculatorImpl_TrentinoExampleBasicCalculatorCalculatorImplImplementation->setHeader("TrentinoExampleBasicCalculatorCalculatorImpl.h");
								CalculatorImpl_TrentinoExampleBasicCalculatorCalculatorImplImplementation->setLibrary("BasicCalculator");
											Trentino::SCA::Model::CPPImplementationScope* const TrentinoExampleBasicCalculatorCalculatorImplImplementation_TrentinoExampleBasicCalculatorCalculatorImplScope= factory.createCPPImplementationScope("Composite");
			

				 
							CalculatorImpl_TrentinoExampleBasicCalculatorCalculatorImplImplementation->setScope(TrentinoExampleBasicCalculatorCalculatorImplImplementation_TrentinoExampleBasicCalculatorCalculatorImplScope);
							

				 
							BasicCalculatorComposite_CalculatorImpl->setImplementation(CalculatorImpl_TrentinoExampleBasicCalculatorCalculatorImplImplementation);
 
 
									Trentino::SCA::Model::ComponentReference* const CalculatorImpl_Divider= factory.createComponentReference();
						CalculatorImpl_Divider->setAutowire(false);
								CalculatorImpl_Divider->setMultiplicity("1..1");
								CalculatorImpl_Divider->setNonOverridable(false);
								CalculatorImpl_Divider->setWiredByImpl(false);
												Trentino::SCA::Model::CPPInterface* const Divider_DividerInterface= factory.createCPPInterface();
						Divider_DividerInterface->setClazz("Trentino::Example::BasicCalculator::Divider");
								Divider_DividerInterface->setHeader("Divider.h");
										Divider_DividerInterface->setRemotable(false);
							

				 
							CalculatorImpl_Divider->setInterface(Divider_DividerInterface);
						CalculatorImpl_Divider->setName("Divider");
							

					BasicCalculatorComposite_CalculatorImpl->addReferenceElement(CalculatorImpl_Divider);
 
 
									Trentino::SCA::Model::ComponentService* const CalculatorImpl_Calculator= factory.createComponentService();
										Trentino::SCA::Model::CPPInterface* const Calculator_CalculatorInterface= factory.createCPPInterface();
						Calculator_CalculatorInterface->setClazz("Trentino::Example::BasicCalculator::Calculator");
								Calculator_CalculatorInterface->setHeader("Calculator.h");
										Calculator_CalculatorInterface->setRemotable(false);
							

				 
							CalculatorImpl_Calculator->setInterface(Calculator_CalculatorInterface);
						CalculatorImpl_Calculator->setName("Calculator");
							

					BasicCalculatorComposite_CalculatorImpl->addServiceElement(CalculatorImpl_Calculator);
						BasicCalculatorComposite_CalculatorImpl->setAutowire(false);
								BasicCalculatorComposite_CalculatorImpl->setName("CalculatorImpl");
							

					BasicCalculatorCompositeWrapper_BasicCalculatorComposite->addComponentElement(BasicCalculatorComposite_CalculatorImpl);
									Trentino::SCA::Model::Component* const BasicCalculatorComposite_DividerImpl= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const DividerImpl_TrentinoExampleBasicCalculatorDividerImplImplementation= factory.createCPPImplementation();
						DividerImpl_TrentinoExampleBasicCalculatorDividerImplImplementation->setAllowsPassByReference(false);
								DividerImpl_TrentinoExampleBasicCalculatorDividerImplImplementation->setClazz("Trentino::Example::BasicCalculator::DividerImpl");
								DividerImpl_TrentinoExampleBasicCalculatorDividerImplImplementation->setEagerInit(false);
								DividerImpl_TrentinoExampleBasicCalculatorDividerImplImplementation->setHeader("TrentinoExampleBasicCalculatorDividerImpl.h");
								DividerImpl_TrentinoExampleBasicCalculatorDividerImplImplementation->setLibrary("BasicCalculator");
											Trentino::SCA::Model::CPPImplementationScope* const TrentinoExampleBasicCalculatorDividerImplImplementation_TrentinoExampleBasicCalculatorDividerImplScope= factory.createCPPImplementationScope("Composite");
			

				 
							DividerImpl_TrentinoExampleBasicCalculatorDividerImplImplementation->setScope(TrentinoExampleBasicCalculatorDividerImplImplementation_TrentinoExampleBasicCalculatorDividerImplScope);
							

				 
							BasicCalculatorComposite_DividerImpl->setImplementation(DividerImpl_TrentinoExampleBasicCalculatorDividerImplImplementation);
 
 
									Trentino::SCA::Model::ComponentService* const DividerImpl_Divider3= factory.createComponentService();
										Trentino::SCA::Model::CPPInterface* const Divider3_DividerInterface3= factory.createCPPInterface();
						Divider3_DividerInterface3->setClazz("Trentino::Example::BasicCalculator::Divider");
								Divider3_DividerInterface3->setHeader("Divider.h");
										Divider3_DividerInterface3->setRemotable(false);
							

				 
							DividerImpl_Divider3->setInterface(Divider3_DividerInterface3);
						DividerImpl_Divider3->setName("Divider");
							

					BasicCalculatorComposite_DividerImpl->addServiceElement(DividerImpl_Divider3);
						BasicCalculatorComposite_DividerImpl->setAutowire(false);
								BasicCalculatorComposite_DividerImpl->setName("DividerImpl");
							

					BasicCalculatorCompositeWrapper_BasicCalculatorComposite->addComponentElement(BasicCalculatorComposite_DividerImpl);
						BasicCalculatorCompositeWrapper_BasicCalculatorComposite->setAutowire(false);
								BasicCalculatorCompositeWrapper_BasicCalculatorComposite->setLocal(false);
								BasicCalculatorCompositeWrapper_BasicCalculatorComposite->setName("BasicCalculatorComposite");
								BasicCalculatorCompositeWrapper_BasicCalculatorComposite->setTargetNamespace("BasicCalculatorNamespace");
							

				 
			


				Trentino::SCA::Model::ComponentType* const CalculatorImpl= factory.createComponentType();
								Trentino::SCA::Model::ComponentTypeReference* const CalculatorImpl_Divider2= factory.createComponentTypeReference();
					CalculatorImpl_Divider2->setAutowire(false);
					CalculatorImpl_Divider2->setMultiplicity("1..1");
					CalculatorImpl_Divider2->setNonOverridable(false);
					CalculatorImpl_Divider2->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const Divider2_DividerInterface2= factory.createCPPInterface();
					Divider2_DividerInterface2->setClazz("Trentino::Example::BasicCalculator::Divider");
					Divider2_DividerInterface2->setHeader("Divider.h");
					Divider2_DividerInterface2->setRemotable(false);

							CalculatorImpl_Divider2->setInterface(Divider2_DividerInterface2);
					CalculatorImpl_Divider2->setName("Divider");

					CalculatorImpl->addReferenceElement(CalculatorImpl_Divider2);
								Trentino::SCA::Model::ComponentService* const CalculatorImpl_Calculator2= factory.createComponentService();
				
							Trentino::SCA::Model::CPPInterface* const Calculator2_CalculatorInterface2= factory.createCPPInterface();
					Calculator2_CalculatorInterface2->setClazz("Trentino::Example::BasicCalculator::Calculator");
					Calculator2_CalculatorInterface2->setHeader("Calculator.h");
					Calculator2_CalculatorInterface2->setRemotable(false);

							CalculatorImpl_Calculator2->setInterface(Calculator2_CalculatorInterface2);
					CalculatorImpl_Calculator2->setName("Calculator");

					CalculatorImpl->addServiceElement(CalculatorImpl_Calculator2);

			Trentino::SCA::Model::ComponentType* const DividerImpl= factory.createComponentType();
								Trentino::SCA::Model::ComponentService* const DividerImpl_Divider4= factory.createComponentService();
				
							Trentino::SCA::Model::CPPInterface* const Divider4_DividerInterface4= factory.createCPPInterface();
					Divider4_DividerInterface4->setClazz("Trentino::Example::BasicCalculator::Divider");
					Divider4_DividerInterface4->setHeader("Divider.h");
					Divider4_DividerInterface4->setRemotable(false);

							DividerImpl_Divider4->setInterface(Divider4_DividerInterface4);
					DividerImpl_Divider4->setName("Divider");

					DividerImpl->addServiceElement(DividerImpl_Divider4);


			Trentino::SCA::Model::ContributionType* const Trentino_Contribution= factory.createContributionType();
						Trentino::SCA::Model::DeployableType* const Contribution_Deployable= factory.createDeployableType();
				Trentino::XML::Schema::QName* Contribution_Deployable_CompositeQName = factory.createQName("BasicCalculatorComposite", "BasicCalculatorNamespace", "sample");
 				Contribution_Deployable->setComposite(Contribution_Deployable_CompositeQName);

				Trentino_Contribution->addDeployableElement(Contribution_Deployable);

	 modelLoader->associate(BasicCalculatorComposite_CalculatorImpl , CalculatorImpl); 
 modelLoader->associate(BasicCalculatorComposite_DividerImpl , DividerImpl); 

}