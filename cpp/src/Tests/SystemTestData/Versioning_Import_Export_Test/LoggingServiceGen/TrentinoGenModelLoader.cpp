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
   
   									Trentino::SCA::Model::Composite* const LoggingServiceCompositeCompositeWrapper_LoggingServiceCompositeComposite= factory.createComposite();
 
 
									Trentino::SCA::Model::Component* const LoggingServiceComposite_LoggingServiceImplComponent= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const LoggingServiceImplComponent_LoggingServiceImplImplementation= factory.createCPPImplementation();
						LoggingServiceImplComponent_LoggingServiceImplImplementation->setAllowsPassByReference(false);
								LoggingServiceImplComponent_LoggingServiceImplImplementation->setClazz("Trentino::Example::Logging::LoggingServiceImpl");
								LoggingServiceImplComponent_LoggingServiceImplImplementation->setEagerInit(false);
								LoggingServiceImplComponent_LoggingServiceImplImplementation->setHeader("services/TrentinoExampleLoggingLoggingServiceImpl.h");
								LoggingServiceImplComponent_LoggingServiceImplImplementation->setLibrary("LoggingService");
								LoggingServiceImplComponent_LoggingServiceImplImplementation->setPath("bin");
									

				 
							LoggingServiceComposite_LoggingServiceImplComponent->setImplementation(LoggingServiceImplComponent_LoggingServiceImplImplementation);
 
 
									Trentino::SCA::Model::PropertyValue* const LoggingServiceImpl_loggerNameProperty= factory.createPropertyValue();
								LoggingServiceImpl_loggerNameProperty->setMany(false);
								LoggingServiceImpl_loggerNameProperty->setName("loggerName");
								Trentino::XML::Schema::QName* LoggingServiceImpl_loggerNameProperty_TypeQName = factory.createQName("string", "http://docs.oasis-open.org/ns/opencsa/sca/200912", "");
		 				LoggingServiceImpl_loggerNameProperty->setType(LoggingServiceImpl_loggerNameProperty_TypeQName);
								LoggingServiceImpl_loggerNameProperty->setValue("defaultLogger");
					

					LoggingServiceComposite_LoggingServiceImplComponent->addPropertyElement(LoggingServiceImpl_loggerNameProperty);
						LoggingServiceComposite_LoggingServiceImplComponent->setAutowire(false);
								LoggingServiceComposite_LoggingServiceImplComponent->setName("LoggingServiceImpl");
							

					LoggingServiceCompositeCompositeWrapper_LoggingServiceCompositeComposite->addComponentElement(LoggingServiceComposite_LoggingServiceImplComponent);
						LoggingServiceCompositeCompositeWrapper_LoggingServiceCompositeComposite->setAutowire(false);
								LoggingServiceCompositeCompositeWrapper_LoggingServiceCompositeComposite->setLocal(false);
								LoggingServiceCompositeCompositeWrapper_LoggingServiceCompositeComposite->setName("LoggingServiceComposite");
								LoggingServiceCompositeCompositeWrapper_LoggingServiceCompositeComposite->setTargetNamespace("LoggingServiceNamespace");
							

				 
			


				Trentino::SCA::Model::ComponentType* const LoggingServiceImplCompType= factory.createComponentType();
			
								Trentino::SCA::Model::Property* const LoggingServiceImplCompType_loggerNameProperty2= factory.createProperty();
					LoggingServiceImplCompType_loggerNameProperty2->setMustSupply(false);
					LoggingServiceImplCompType_loggerNameProperty2->setMany(false);
					LoggingServiceImplCompType_loggerNameProperty2->setName("loggerName");
					
						
						Trentino::XML::Schema::QName* LoggingServiceImplCompType_loggerNameProperty2_TypeQName = factory.createQName("string", "http://www.w3.org/2001/XMLSchema", "xsd");
		 				LoggingServiceImplCompType_loggerNameProperty2->setType(LoggingServiceImplCompType_loggerNameProperty2_TypeQName);

					LoggingServiceImplCompType->addPropertyElement(LoggingServiceImplCompType_loggerNameProperty2);
			
			
								Trentino::SCA::Model::ComponentService* const LoggingServiceImplCompType_LoggingServiceComponentService= factory.createComponentService();
					LoggingServiceImplCompType_LoggingServiceComponentService->setRemote(false);
				
							Trentino::SCA::Model::CPPInterface* const LoggingServiceComponentService_TrentinoExampleLoggingLoggingServicehInterface= factory.createCPPInterface();
					LoggingServiceComponentService_TrentinoExampleLoggingLoggingServicehInterface->setClazz("Trentino::Example::Logging::LoggingService");
					LoggingServiceComponentService_TrentinoExampleLoggingLoggingServicehInterface->setHeader("services/TrentinoExampleLoggingLoggingService.h");
					LoggingServiceComponentService_TrentinoExampleLoggingLoggingServicehInterface->setRemotable(false);

							LoggingServiceImplCompType_LoggingServiceComponentService->setInterface(LoggingServiceComponentService_TrentinoExampleLoggingLoggingServicehInterface);
					LoggingServiceImplCompType_LoggingServiceComponentService->setName("LoggingService");

					LoggingServiceImplCompType->addServiceElement(LoggingServiceImplCompType_LoggingServiceComponentService);
			


			Trentino::SCA::Model::ContributionType* const Trentino_Contribution= factory.createContributionType();
						Trentino::SCA::Model::DeployableType* const Contribution_Deployable= factory.createDeployableType();
				Trentino::XML::Schema::QName* Contribution_Deployable_CompositeQName = factory.createQName("LoggingServiceComposite", "LoggingServiceNamespace", "logging");
 				Contribution_Deployable->setComposite(Contribution_Deployable_CompositeQName);

				Trentino_Contribution->addDeployableElement(Contribution_Deployable);

	 modelLoader->associate(LoggingServiceComposite_LoggingServiceImplComponent , LoggingServiceImplCompType); 

}