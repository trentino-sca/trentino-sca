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
   
   									Trentino::SCA::Model::Composite* const BasicPrinterCompositeCompositeWrapper_BasicPrinterCompositeComposite= factory.createComposite();
 
 
									Trentino::SCA::Model::Component* const BasicPrinterComposite_BasicPrinterImplComponent= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const BasicPrinterImplComponent_BasicPrinterImplImplementation= factory.createCPPImplementation();
						BasicPrinterImplComponent_BasicPrinterImplImplementation->setAllowsPassByReference(false);
								BasicPrinterImplComponent_BasicPrinterImplImplementation->setClazz("Trentino::Example::BasicPrinterImpl");
								BasicPrinterImplComponent_BasicPrinterImplImplementation->setEagerInit(false);
								BasicPrinterImplComponent_BasicPrinterImplImplementation->setHeader("TrentinoExampleBasicPrinterImpl.h");
								BasicPrinterImplComponent_BasicPrinterImplImplementation->setLibrary("BasicPrinter");
											Trentino::SCA::Model::CPPImplementationScope* const BasicPrinterImplImplementation_BasicPrinterImplImplementationScope= factory.createCPPImplementationScope("Composite");
			

				 
							BasicPrinterImplComponent_BasicPrinterImplImplementation->setScope(BasicPrinterImplImplementation_BasicPrinterImplImplementationScope);
							

				 
							BasicPrinterComposite_BasicPrinterImplComponent->setImplementation(BasicPrinterImplComponent_BasicPrinterImplImplementation);
						BasicPrinterComposite_BasicPrinterImplComponent->setAutowire(false);
								BasicPrinterComposite_BasicPrinterImplComponent->setName("BasicPrinterImpl");
							

					BasicPrinterCompositeCompositeWrapper_BasicPrinterCompositeComposite->addComponentElement(BasicPrinterComposite_BasicPrinterImplComponent);
									Trentino::SCA::Model::Component* const BasicPrinterComposite_BasicPrinterImpl2Component= factory.createComponent();
								Trentino::SCA::Model::CPPImplementation* const BasicPrinterImpl2Component_BasicPrinterImpl2Implementation= factory.createCPPImplementation();
						BasicPrinterImpl2Component_BasicPrinterImpl2Implementation->setAllowsPassByReference(false);
								BasicPrinterImpl2Component_BasicPrinterImpl2Implementation->setClazz("Trentino::Example::BasicPrinterImpl2");
								BasicPrinterImpl2Component_BasicPrinterImpl2Implementation->setEagerInit(false);
								BasicPrinterImpl2Component_BasicPrinterImpl2Implementation->setHeader("TrentinoExampleBasicPrinterImpl2.h");
								BasicPrinterImpl2Component_BasicPrinterImpl2Implementation->setLibrary("BasicPrinter");
											Trentino::SCA::Model::CPPImplementationScope* const BasicPrinterImpl2Implementation_BasicPrinterImpl2ImplementationScope= factory.createCPPImplementationScope("Composite");
			

				 
							BasicPrinterImpl2Component_BasicPrinterImpl2Implementation->setScope(BasicPrinterImpl2Implementation_BasicPrinterImpl2ImplementationScope);
							

				 
							BasicPrinterComposite_BasicPrinterImpl2Component->setImplementation(BasicPrinterImpl2Component_BasicPrinterImpl2Implementation);
						BasicPrinterComposite_BasicPrinterImpl2Component->setAutowire(false);
								BasicPrinterComposite_BasicPrinterImpl2Component->setName("BasicPrinterImpl2");
							

					BasicPrinterCompositeCompositeWrapper_BasicPrinterCompositeComposite->addComponentElement(BasicPrinterComposite_BasicPrinterImpl2Component);
						BasicPrinterCompositeCompositeWrapper_BasicPrinterCompositeComposite->setAutowire(false);
								BasicPrinterCompositeCompositeWrapper_BasicPrinterCompositeComposite->setLocal(false);
								BasicPrinterCompositeCompositeWrapper_BasicPrinterCompositeComposite->setName("BasicPrinterComposite");
								BasicPrinterCompositeCompositeWrapper_BasicPrinterCompositeComposite->setTargetNamespace("BasicPrinterNamespace");
							

				 
			


				Trentino::SCA::Model::ComponentType* const BasicPrinterImplCompType= factory.createComponentType();
			
								Trentino::SCA::Model::ComponentService* const BasicPrinterImplCompType_BasicPrinterComponentService= factory.createComponentService();
					BasicPrinterImplCompType_BasicPrinterComponentService->setRemote(false);
				
							Trentino::SCA::Model::CPPInterface* const BasicPrinterComponentService_TrentinoExampleBasicPrinterhInterface= factory.createCPPInterface();
					BasicPrinterComponentService_TrentinoExampleBasicPrinterhInterface->setClazz("Trentino::Example::BasicPrinter");
					BasicPrinterComponentService_TrentinoExampleBasicPrinterhInterface->setHeader("services/TrentinoExampleBasicPrinter.h");
					BasicPrinterComponentService_TrentinoExampleBasicPrinterhInterface->setRemotable(true);

							BasicPrinterImplCompType_BasicPrinterComponentService->setInterface(BasicPrinterComponentService_TrentinoExampleBasicPrinterhInterface);
				
							Trentino::SCA::Model::Metadata* const BasicPrinterComponentService_BasicPrinterMetaData= factory.createMetadata();
			
								Trentino::SCA::Model::MetadataStringAttribute* const BasicPrinterMetaData_floorMetaDataAtt= factory.createMetadataStringAttribute();
					BasicPrinterMetaData_floorMetaDataAtt->setName("floor");
					BasicPrinterMetaData_floorMetaDataAtt->setValue("3");

					BasicPrinterComponentService_BasicPrinterMetaData->addStringAttributesElement(BasicPrinterMetaData_floorMetaDataAtt);
								Trentino::SCA::Model::MetadataStringAttribute* const BasicPrinterMetaData_colourMetaDataAtt= factory.createMetadataStringAttribute();
					BasicPrinterMetaData_colourMetaDataAtt->setName("colour");
					BasicPrinterMetaData_colourMetaDataAtt->setValue("yellow");

					BasicPrinterComponentService_BasicPrinterMetaData->addStringAttributesElement(BasicPrinterMetaData_colourMetaDataAtt);
			

							BasicPrinterImplCompType_BasicPrinterComponentService->setMetadata(BasicPrinterComponentService_BasicPrinterMetaData);
					BasicPrinterImplCompType_BasicPrinterComponentService->setName("BasicPrinter");

					BasicPrinterImplCompType->addServiceElement(BasicPrinterImplCompType_BasicPrinterComponentService);
			

			Trentino::SCA::Model::ComponentType* const BasicPrinterImpl2CompType= factory.createComponentType();
			
								Trentino::SCA::Model::ComponentService* const BasicPrinterImpl2CompType_BasicPrinter2ComponentService= factory.createComponentService();
					BasicPrinterImpl2CompType_BasicPrinter2ComponentService->setRemote(false);
				
							Trentino::SCA::Model::CPPInterface* const BasicPrinter2ComponentService_TrentinoExampleBasicPrinterhInterface2= factory.createCPPInterface();
					BasicPrinter2ComponentService_TrentinoExampleBasicPrinterhInterface2->setClazz("Trentino::Example::BasicPrinter");
					BasicPrinter2ComponentService_TrentinoExampleBasicPrinterhInterface2->setHeader("services/TrentinoExampleBasicPrinter.h");
					BasicPrinter2ComponentService_TrentinoExampleBasicPrinterhInterface2->setRemotable(true);

							BasicPrinterImpl2CompType_BasicPrinter2ComponentService->setInterface(BasicPrinter2ComponentService_TrentinoExampleBasicPrinterhInterface2);
				
							Trentino::SCA::Model::Metadata* const BasicPrinter2ComponentService_BasicPrinter2MetaData= factory.createMetadata();
			
								Trentino::SCA::Model::MetadataStringAttribute* const BasicPrinter2MetaData_floorMetaDataAtt2= factory.createMetadataStringAttribute();
					BasicPrinter2MetaData_floorMetaDataAtt2->setName("floor");
					BasicPrinter2MetaData_floorMetaDataAtt2->setValue("4");

					BasicPrinter2ComponentService_BasicPrinter2MetaData->addStringAttributesElement(BasicPrinter2MetaData_floorMetaDataAtt2);
								Trentino::SCA::Model::MetadataStringAttribute* const BasicPrinter2MetaData_colourMetaDataAtt2= factory.createMetadataStringAttribute();
					BasicPrinter2MetaData_colourMetaDataAtt2->setName("colour");
					BasicPrinter2MetaData_colourMetaDataAtt2->setValue("yellow");

					BasicPrinter2ComponentService_BasicPrinter2MetaData->addStringAttributesElement(BasicPrinter2MetaData_colourMetaDataAtt2);
			

							BasicPrinterImpl2CompType_BasicPrinter2ComponentService->setMetadata(BasicPrinter2ComponentService_BasicPrinter2MetaData);
					BasicPrinterImpl2CompType_BasicPrinter2ComponentService->setName("BasicPrinter2");

					BasicPrinterImpl2CompType->addServiceElement(BasicPrinterImpl2CompType_BasicPrinter2ComponentService);
			


			Trentino::SCA::Model::ContributionType* const Trentino_Contribution= factory.createContributionType();
						Trentino::SCA::Model::DeployableType* const Contribution_Deployable= factory.createDeployableType();
				Trentino::XML::Schema::QName* Contribution_Deployable_CompositeQName = factory.createQName("BasicPrinterComposite", "BasicPrinterNamespace", "sample");
 				Contribution_Deployable->setComposite(Contribution_Deployable_CompositeQName);

				Trentino_Contribution->addDeployableElement(Contribution_Deployable);

	 modelLoader->associate(BasicPrinterComposite_BasicPrinterImplComponent , BasicPrinterImplCompType); 
 modelLoader->associate(BasicPrinterComposite_BasicPrinterImpl2Component , BasicPrinterImpl2CompType); 

}