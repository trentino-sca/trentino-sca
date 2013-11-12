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
//header
#include "TrentinoGenContributionInfo.h"

//standard
#include <Global/TrentinoGlobal.h>
#include <Runtime/Core/TrentinoCoreContributionLoadingSCAModelLoader.h>

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
#include <Runtime/SCAModel/TrentinoSCAModelPolicyReference.h>
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
#include <Runtime/SCAModel/TrentinoSCAModelIPCBinding.h>
#include <Runtime/SCAModel/TrentinoSCAModelSCAImplementation.h>
#include <Runtime/SCAModel/TrentinoSCAModelSCAPropertyBase.h>
#include <Runtime/SCAModel/TrentinoSCAModelService.h>
#include <Runtime/SCAModel/TrentinoSCAModelURI.h>
#include <Runtime/SCAModel/TrentinoSCAModelValueType.h>
#include <Runtime/SCAModel/TrentinoSCAModelWire.h>
#include <Runtime/SCAModel/TrentinoSCAModelWireFormatType.h>


//! the model loader for this contribution
TRENTINO_DLLEXPORT void TRENTINO_CDECL Trentino::Gen::GenContributionInfo::loadModel( Trentino::Core::ContributionLoading::SCAModelLoader* modelLoader )
{
   assert(modelLoader != nullptr);

   Trentino::Core::ContributionLoading::SCAModelLoader::SCAModelFactory& factory = modelLoader->scaModelFactory();
   
   									Trentino::SCA::Model::Composite* const BasicCalculatorCompositeCompositeWrapper_BasicCalculatorCompositeComposite= factory.createComposite();
 
 
									Trentino::SCA::Model::Component* const BasicCalculatorComposite_CalculatorImplComponent= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const CalculatorImplComponent_CalculatorImplImplementation= factory.createCPPImplementation();
 
 
									Trentino::SCA::Model::CPPImplementationFunction* const CalculatorImplImplementation_onInitFunc= factory.createCPPImplementationFunction();
						CalculatorImplImplementation_onInitFunc->setAllowsPassByReference(false);
								CalculatorImplImplementation_onInitFunc->setDestroy(false);
								CalculatorImplImplementation_onInitFunc->setInit(true);
								CalculatorImplImplementation_onInitFunc->setName("onInit");
					

					CalculatorImplComponent_CalculatorImplImplementation->addFunctionElement(CalculatorImplImplementation_onInitFunc);
						CalculatorImplComponent_CalculatorImplImplementation->setAllowsPassByReference(false);
								CalculatorImplComponent_CalculatorImplImplementation->setClazz("Trentino::Example::BasicCalculator::CalculatorImpl");
								CalculatorImplComponent_CalculatorImplImplementation->setEagerInit(true);
								CalculatorImplComponent_CalculatorImplImplementation->setHeader("TrentinoExampleBasicCalculatorCalculatorImpl.h");
								CalculatorImplComponent_CalculatorImplImplementation->setLibrary("BasicCalculator");
											Trentino::SCA::Model::CPPImplementationScope* const CalculatorImplImplementation_CalculatorImplImplementationScope= factory.createCPPImplementationScope("Composite");
			

				 
							CalculatorImplComponent_CalculatorImplImplementation->setScope(CalculatorImplImplementation_CalculatorImplImplementationScope);
							

				 
							BasicCalculatorComposite_CalculatorImplComponent->setImplementation(CalculatorImplComponent_CalculatorImplImplementation);
						BasicCalculatorComposite_CalculatorImplComponent->setAutowire(false);
								BasicCalculatorComposite_CalculatorImplComponent->setName("CalculatorImpl");
							

					BasicCalculatorCompositeCompositeWrapper_BasicCalculatorCompositeComposite->addComponentElement(BasicCalculatorComposite_CalculatorImplComponent);
						BasicCalculatorCompositeCompositeWrapper_BasicCalculatorCompositeComposite->setAutowire(false);
								BasicCalculatorCompositeCompositeWrapper_BasicCalculatorCompositeComposite->setLocal(false);
								BasicCalculatorCompositeCompositeWrapper_BasicCalculatorCompositeComposite->setName("BasicCalculatorComposite");
								BasicCalculatorCompositeCompositeWrapper_BasicCalculatorCompositeComposite->setTargetNamespace("BasicCalculatorNamespace");
							

				 
			


				Trentino::SCA::Model::ComponentType* const CalculatorImplCompType= factory.createComponentType();
			
								Trentino::SCA::Model::ComponentTypeReference* const CalculatorImplCompType_LoggingServiceComponentTypeRef= factory.createComponentTypeReference();
					CalculatorImplCompType_LoggingServiceComponentTypeRef->setAutowire(false);
					CalculatorImplCompType_LoggingServiceComponentTypeRef->setMultiplicity("1..1");
					CalculatorImplCompType_LoggingServiceComponentTypeRef->setNonOverridable(false);
			
					 CalculatorImplCompType_LoggingServiceComponentTypeRef->addTarget("LoggingServiceImpl/LoggingService");
			
					CalculatorImplCompType_LoggingServiceComponentTypeRef->setWiredByImpl(false);
				
							Trentino::SCA::Model::CPPInterface* const LoggingServiceComponentTypeRef_loggingmetadataTrentinoExampleLoggingLoggingServicehInterface= factory.createCPPInterface();
					LoggingServiceComponentTypeRef_loggingmetadataTrentinoExampleLoggingLoggingServicehInterface->setClazz("Trentino::Example::Logging::LoggingService");
					LoggingServiceComponentTypeRef_loggingmetadataTrentinoExampleLoggingLoggingServicehInterface->setHeader("loggingmetadata:TrentinoExampleLoggingLoggingService.h");
					LoggingServiceComponentTypeRef_loggingmetadataTrentinoExampleLoggingLoggingServicehInterface->setRemotable(false);

							CalculatorImplCompType_LoggingServiceComponentTypeRef->setInterface(LoggingServiceComponentTypeRef_loggingmetadataTrentinoExampleLoggingLoggingServicehInterface);
					CalculatorImplCompType_LoggingServiceComponentTypeRef->setName("LoggingService");

					CalculatorImplCompType->addReferenceElement(CalculatorImplCompType_LoggingServiceComponentTypeRef);
			
			
								Trentino::SCA::Model::ComponentService* const CalculatorImplCompType_CalculatorComponentService= factory.createComponentService();
					CalculatorImplCompType_CalculatorComponentService->setRemote(false);
				
							Trentino::SCA::Model::CPPInterface* const CalculatorComponentService_TrentinoExampleBasicCalculatorCalculatorhInterface= factory.createCPPInterface();
					CalculatorComponentService_TrentinoExampleBasicCalculatorCalculatorhInterface->setClazz("Trentino::Example::BasicCalculator::Calculator");
					CalculatorComponentService_TrentinoExampleBasicCalculatorCalculatorhInterface->setHeader("services/TrentinoExampleBasicCalculatorCalculator.h");
					CalculatorComponentService_TrentinoExampleBasicCalculatorCalculatorhInterface->setRemotable(false);

							CalculatorImplCompType_CalculatorComponentService->setInterface(CalculatorComponentService_TrentinoExampleBasicCalculatorCalculatorhInterface);
					CalculatorImplCompType_CalculatorComponentService->setName("Calculator");

					CalculatorImplCompType->addServiceElement(CalculatorImplCompType_CalculatorComponentService);
			


			Trentino::SCA::Model::ContributionType* const Trentino_Contribution= factory.createContributionType();
						Trentino::SCA::Model::DeployableType* const Contribution_Deployable= factory.createDeployableType();
				Trentino::XML::Schema::QName* Contribution_Deployable_CompositeQName = factory.createQName("BasicCalculatorComposite", "BasicCalculatorNamespace", "sample");
 				Contribution_Deployable->setComposite(Contribution_Deployable_CompositeQName);

				Trentino_Contribution->addDeployableElement(Contribution_Deployable);

	 modelLoader->associate(BasicCalculatorComposite_CalculatorImplComponent , CalculatorImplCompType); 

}