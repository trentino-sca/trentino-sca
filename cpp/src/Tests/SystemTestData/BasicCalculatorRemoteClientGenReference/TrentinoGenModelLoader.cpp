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

#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif
//header
#include "TrentinoGenContributionInfo.h"

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
#include <Runtime/SCAModel/TrentinoSCAModelSCAImplementation.h>
#include <Runtime/SCAModel/TrentinoSCAModelSCAPropertyBase.h>
#include <Runtime/SCAModel/TrentinoSCAModelService.h>
#include <Runtime/SCAModel/TrentinoSCAModelURI.h>
#include <Runtime/SCAModel/TrentinoSCAModelValueType.h>
#include <Runtime/SCAModel/TrentinoSCAModelWire.h>
#include <Runtime/SCAModel/TrentinoSCAModelWireFormattype.h>


//! the model loader for this contribution
TRENTINO_DLLEXPORT void TRENTINO_CDECL Trentino::Gen::GenContributionInfo::loadModel( Trentino::Core::SCAModelLoader* modelLoader )
{
   assert(modelLoader != nullptr);

   Trentino::Core::SCAModelLoader::SCAModelFactory& factory = modelLoader->scaModelFactory();
   
   									Trentino::SCA::Model::Composite* const BasicCalculatorRemoteClientCompositeWrapper_BasicCalculatorRemoteClientComposite= factory.createComposite();
 
 
									Trentino::SCA::Model::Component* const BasicCalculatorRemoteClientComposite_BasicCalculatorRemoteClientImpl= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const BasicCalculatorRemoteClientImpl_BasicCalculatorRemoteClientImplImplementation= factory.createCPPImplementation();
						BasicCalculatorRemoteClientImpl_BasicCalculatorRemoteClientImplImplementation->setAllowsPassByReference(false);
								BasicCalculatorRemoteClientImpl_BasicCalculatorRemoteClientImplImplementation->setClazz("Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorRemoteClientImpl");
								BasicCalculatorRemoteClientImpl_BasicCalculatorRemoteClientImplImplementation->setEagerInit(false);
								BasicCalculatorRemoteClientImpl_BasicCalculatorRemoteClientImplImplementation->setHeader("TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorImpl.h");
								BasicCalculatorRemoteClientImpl_BasicCalculatorRemoteClientImplImplementation->setLibrary("BasicCalculatorRemoteClient");
											Trentino::SCA::Model::CPPImplementationScope* const BasicCalculatorRemoteClientImplImplementation_BasicCalculatorRemoteClientImplImplementationScope= factory.createCPPImplementationScope("Composite");
			

				 
							BasicCalculatorRemoteClientImpl_BasicCalculatorRemoteClientImplImplementation->setScope(BasicCalculatorRemoteClientImplImplementation_BasicCalculatorRemoteClientImplImplementationScope);
							

				 
							BasicCalculatorRemoteClientComposite_BasicCalculatorRemoteClientImpl->setImplementation(BasicCalculatorRemoteClientImpl_BasicCalculatorRemoteClientImplImplementation);
						BasicCalculatorRemoteClientComposite_BasicCalculatorRemoteClientImpl->setAutowire(false);
								BasicCalculatorRemoteClientComposite_BasicCalculatorRemoteClientImpl->setName("BasicCalculatorRemoteClientImpl");
							

					BasicCalculatorRemoteClientCompositeWrapper_BasicCalculatorRemoteClientComposite->addComponentElement(BasicCalculatorRemoteClientComposite_BasicCalculatorRemoteClientImpl);
						BasicCalculatorRemoteClientCompositeWrapper_BasicCalculatorRemoteClientComposite->setAutowire(false);
								BasicCalculatorRemoteClientCompositeWrapper_BasicCalculatorRemoteClientComposite->setLocal(false);
								BasicCalculatorRemoteClientCompositeWrapper_BasicCalculatorRemoteClientComposite->setName("BasicCalculatorRemoteClientComposite");
								BasicCalculatorRemoteClientCompositeWrapper_BasicCalculatorRemoteClientComposite->setTargetNamespace("BasicCalculatorNamespace");
							

				 
			


				Trentino::SCA::Model::ComponentType* const BasicCalculatorRemoteClientImplCompType= factory.createComponentType();
			
								Trentino::SCA::Model::ComponentTypeReference* const BasicCalculatorRemoteClientImplCompType_BasicCalculatorRef= factory.createComponentTypeReference();
					BasicCalculatorRemoteClientImplCompType_BasicCalculatorRef->setAutowire(false);
					BasicCalculatorRemoteClientImplCompType_BasicCalculatorRef->setMultiplicity("1..1");
					BasicCalculatorRemoteClientImplCompType_BasicCalculatorRef->setNonOverridable(false);
					BasicCalculatorRemoteClientImplCompType_BasicCalculatorRef->setWiredByImpl(false);
			
								Trentino::SCA::Model::SCABinding* const BasicCalculatorRef_Binding= factory.createSCABinding();
					BasicCalculatorRef_Binding->setHost("www.ipek.com");
					BasicCalculatorRef_Binding->setPort("8080");

					BasicCalculatorRemoteClientImplCompType_BasicCalculatorRef->addBindingElement(BasicCalculatorRef_Binding);
			
				
							Trentino::SCA::Model::CPPInterface* const BasicCalculatorRef_TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorhInterface= factory.createCPPInterface();
					BasicCalculatorRef_TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorhInterface->setClazz("Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator");
					BasicCalculatorRef_TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorhInterface->setHeader("services/TrentinoExampleBasicCalculatorRemoteClientBasicCalculator.h");
					BasicCalculatorRef_TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorhInterface->setRemotable(true);

							BasicCalculatorRemoteClientImplCompType_BasicCalculatorRef->setInterface(BasicCalculatorRef_TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorhInterface);
					BasicCalculatorRemoteClientImplCompType_BasicCalculatorRef->setName("BasicCalculatorRef");

					BasicCalculatorRemoteClientImplCompType->addReferenceElement(BasicCalculatorRemoteClientImplCompType_BasicCalculatorRef);
			


			Trentino::SCA::Model::ContributionType* const Trentino_Contribution= factory.createContributionType();
						Trentino::SCA::Model::DeployableType* const Contribution_Deployable= factory.createDeployableType();
				Trentino::XML::Schema::QName* Contribution_Deployable_CompositeQName = factory.createQName("BasicCalculatorRemoteClientComposite", "BasicCalculatorNamespace", "sample");
 				Contribution_Deployable->setComposite(Contribution_Deployable_CompositeQName);

				Trentino_Contribution->addDeployableElement(Contribution_Deployable);

	 modelLoader->associate(BasicCalculatorRemoteClientComposite_BasicCalculatorRemoteClientImpl , BasicCalculatorRemoteClientImplCompType); 

}