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
#include "ContributionInfo.h"

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
TRENTINO_DLLEXPORT void TRENTINO_CDECL Trentino::Gen::ValidContribution1Gen::ValidContribution1ContributionInfo::loadModel( Trentino::Core::SCAModelLoader* modelLoader )
{
   assert(modelLoader != nullptr);

   Trentino::Core::SCAModelLoader::SCAModelFactory& factory = modelLoader->scaModelFactory();
   
   									Trentino::SCA::Model::Composite* const DeployableCompositeWrapper_DeployableComposite= factory.createComposite();
 
 
									Trentino::SCA::Model::Component* const DeployableComposite_BuilderImplComponent= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const BuilderImplComponent_BuilderImplImplementation= factory.createCPPImplementation();
						BuilderImplComponent_BuilderImplImplementation->setAllowsPassByReference(false);
								BuilderImplComponent_BuilderImplImplementation->setClazz("Trentino::Example::ValidContribution1::BuilderImpl");
								BuilderImplComponent_BuilderImplImplementation->setEagerInit(false);
								BuilderImplComponent_BuilderImplImplementation->setHeader("BuilderImpl.h");
								BuilderImplComponent_BuilderImplImplementation->setLibrary("BusinessLogic");
									

				 
							DeployableComposite_BuilderImplComponent->setImplementation(BuilderImplComponent_BuilderImplImplementation);
						DeployableComposite_BuilderImplComponent->setAutowire(false);
								DeployableComposite_BuilderImplComponent->setName("BuilderImplComponent");
							

					DeployableCompositeWrapper_DeployableComposite->addComponentElement(DeployableComposite_BuilderImplComponent);
									Trentino::SCA::Model::Component* const DeployableComposite_LoggerImplComponent= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const LoggerImplComponent_LoggerImplImplementation= factory.createCPPImplementation();
						LoggerImplComponent_LoggerImplImplementation->setAllowsPassByReference(false);
								LoggerImplComponent_LoggerImplImplementation->setClazz("Trentino::Example::ValidContribution1::LoggerImpl");
								LoggerImplComponent_LoggerImplImplementation->setEagerInit(false);
								LoggerImplComponent_LoggerImplImplementation->setHeader("LoggerImpl.h");
								LoggerImplComponent_LoggerImplImplementation->setLibrary("BusinessLogic");
									

				 
							DeployableComposite_LoggerImplComponent->setImplementation(LoggerImplComponent_LoggerImplImplementation);
						DeployableComposite_LoggerImplComponent->setAutowire(false);
								DeployableComposite_LoggerImplComponent->setName("LoggerImplComponent");
							

					DeployableCompositeWrapper_DeployableComposite->addComponentElement(DeployableComposite_LoggerImplComponent);
						DeployableCompositeWrapper_DeployableComposite->setAutowire(false);
								DeployableCompositeWrapper_DeployableComposite->setLocal(false);
								DeployableCompositeWrapper_DeployableComposite->setName("DeployableComposite");
								DeployableCompositeWrapper_DeployableComposite->setTargetNamespace("ValidContribution1Namespace");
							

				 
			


				Trentino::SCA::Model::ComponentType* const BuilderImplComponentCompType= factory.createComponentType();
								Trentino::SCA::Model::ComponentService* const BuilderImplComponentCompType_Build= factory.createComponentService();
				
							Trentino::SCA::Model::CPPInterface* const Build_BuildhInterface= factory.createCPPInterface();
					Build_BuildhInterface->setClazz("Trentino::Example::ValidContribution1::Build");
					Build_BuildhInterface->setHeader("services/Build.h");
					Build_BuildhInterface->setRemotable(false);

							BuilderImplComponentCompType_Build->setInterface(Build_BuildhInterface);
					BuilderImplComponentCompType_Build->setName("Build");

					BuilderImplComponentCompType->addServiceElement(BuilderImplComponentCompType_Build);

			Trentino::SCA::Model::ComponentType* const LoggerImplComponentCompType= factory.createComponentType();
								Trentino::SCA::Model::ComponentService* const LoggerImplComponentCompType_Log= factory.createComponentService();
				
							Trentino::SCA::Model::CPPInterface* const Log_LoggerhInterface= factory.createCPPInterface();
					Log_LoggerhInterface->setClazz("Trentino::Example::ValidContribution1::Logger");
					Log_LoggerhInterface->setHeader("services/Logger.h");
					Log_LoggerhInterface->setRemotable(false);

							LoggerImplComponentCompType_Log->setInterface(Log_LoggerhInterface);
					LoggerImplComponentCompType_Log->setName("Log");

					LoggerImplComponentCompType->addServiceElement(LoggerImplComponentCompType_Log);


			Trentino::SCA::Model::ContributionType* const Trentino_Contribution= factory.createContributionType();
						Trentino::SCA::Model::DeployableType* const Contribution_Deployable= factory.createDeployableType();
				Trentino::XML::Schema::QName* Contribution_Deployable_CompositeQName = factory.createQName("DeployableComposite", "ValidContribution1Namespace", "sample");
 				Contribution_Deployable->setComposite(Contribution_Deployable_CompositeQName);

				Trentino_Contribution->addDeployableElement(Contribution_Deployable);

	 modelLoader->associate(DeployableComposite_BuilderImplComponent , BuilderImplComponentCompType); 
 modelLoader->associate(DeployableComposite_LoggerImplComponent , LoggerImplComponentCompType); 

}