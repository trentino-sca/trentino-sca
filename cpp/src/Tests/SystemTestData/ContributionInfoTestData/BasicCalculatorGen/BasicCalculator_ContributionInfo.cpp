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
#include "BasicCalculator_ContributionInfo.h"

//standard+
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
#include "TrentinoGenProxiesWrappers.h"



// This is an example of an exported function.
extern "C" TRENTINO_DLLEXPORT Trentino::Core::TrentinoContributionInfo* TRENTINO_CDECL getContributionInfo()
{
 return new Trentino::Gen::BasicCalculatorGen::BasicCalculatorContributionInfo();
}

TRENTINO_DLLEXPORT void TRENTINO_CDECL Trentino::Gen::BasicCalculatorGen::BasicCalculatorContributionInfo::loadModel( Trentino::Core::SCAModelLoader* modelLoader )
   {

   assert(modelLoader != nullptr);

   Trentino::Core::SCAModelLoader::SCAModelFactory& factory = modelLoader->scaModelFactory();

   Trentino::SCA::Model::Composite* const BasicCalculatorCompositeWrapper_BasicCalculatorComposite= factory.createComposite();


   Trentino::SCA::Model::Component* const BasicCalculatorComposite_CalculatorImpl= factory.createComponent();
   Trentino::SCA::Model::CPPImplementation* const CalculatorImpl_CalculatorImplImplementation= factory.createCPPImplementation();
   CalculatorImpl_CalculatorImplImplementation->setAllowsPassByReference(false);
   CalculatorImpl_CalculatorImplImplementation->setClazz("Trentino::Example::BasicCalculator::CalculatorImpl");
   CalculatorImpl_CalculatorImplImplementation->setEagerInit(true);
   CalculatorImpl_CalculatorImplImplementation->setHeader("TrentinoExampleBasicCalculatorCalculatorImpl.h");
   CalculatorImpl_CalculatorImplImplementation->setLibrary("BasicCalculator");
   Trentino::SCA::Model::CPPImplementationScope* const CalculatorImplImplementation_CalculatorImplImplementationScope= factory.createCPPImplementationScope("Composite");



   CalculatorImpl_CalculatorImplImplementation->setScope(CalculatorImplImplementation_CalculatorImplImplementationScope);



   BasicCalculatorComposite_CalculatorImpl->setImplementation(CalculatorImpl_CalculatorImplImplementation);


   Trentino::SCA::Model::ComponentReference* const CalculatorImpl_Divider= factory.createComponentReference();
   CalculatorImpl_Divider->setAutowire(false);
   CalculatorImpl_Divider->setMultiplicity("1..1");
   CalculatorImpl_Divider->setNonOverridable(false);

   CalculatorImpl_Divider->addTarget("DividerImpl/Divider");
   CalculatorImpl_Divider->setWiredByImpl(false);
   Trentino::SCA::Model::CPPInterface* const Divider_TrentinoExampleBasicCalculatorDividerhInterface= factory.createCPPInterface();
   Divider_TrentinoExampleBasicCalculatorDividerhInterface->setClazz("Trentino::Example::BasicCalculator::Divider");
   Divider_TrentinoExampleBasicCalculatorDividerhInterface->setHeader("./services/TrentinoExampleBasicCalculatorDivider.h");
   Divider_TrentinoExampleBasicCalculatorDividerhInterface->setRemotable(false);



   CalculatorImpl_Divider->setInterface(Divider_TrentinoExampleBasicCalculatorDividerhInterface);
   CalculatorImpl_Divider->setName("Divider");


   BasicCalculatorComposite_CalculatorImpl->addReferenceElement(CalculatorImpl_Divider);


   Trentino::SCA::Model::ComponentService* const CalculatorImpl_Calculator= factory.createComponentService();
   Trentino::SCA::Model::CPPInterface* const Calculator_TrentinoExampleBasicCalculatorCalculatorhInterface= factory.createCPPInterface();
   Calculator_TrentinoExampleBasicCalculatorCalculatorhInterface->setClazz("Trentino::Example::BasicCalculator::Calculator");
   Calculator_TrentinoExampleBasicCalculatorCalculatorhInterface->setHeader("services/TrentinoExampleBasicCalculatorCalculator.h");
   Calculator_TrentinoExampleBasicCalculatorCalculatorhInterface->setRemotable(false);



   CalculatorImpl_Calculator->setInterface(Calculator_TrentinoExampleBasicCalculatorCalculatorhInterface);
   CalculatorImpl_Calculator->setName("Calculator");


   BasicCalculatorComposite_CalculatorImpl->addServiceElement(CalculatorImpl_Calculator);
   BasicCalculatorComposite_CalculatorImpl->setAutowire(false);
   BasicCalculatorComposite_CalculatorImpl->setName("CalculatorImpl");


   BasicCalculatorCompositeWrapper_BasicCalculatorComposite->addComponentElement(BasicCalculatorComposite_CalculatorImpl);
   Trentino::SCA::Model::Component* const BasicCalculatorComposite_DividerImpl= factory.createComponent();
   Trentino::SCA::Model::CPPImplementation* const DividerImpl_DividerImplImplementation= factory.createCPPImplementation();
   DividerImpl_DividerImplImplementation->setAllowsPassByReference(false);
   DividerImpl_DividerImplImplementation->setClazz("Trentino::Example::BasicCalculator::DividerImpl");
   DividerImpl_DividerImplImplementation->setEagerInit(true);
   DividerImpl_DividerImplImplementation->setHeader("TrentinoExampleBasicCalculatorDividerImpl.h");
   DividerImpl_DividerImplImplementation->setLibrary("BasicCalculator");
   Trentino::SCA::Model::CPPImplementationScope* const DividerImplImplementation_DividerImplImplementationScope= factory.createCPPImplementationScope("Composite");



   DividerImpl_DividerImplImplementation->setScope(DividerImplImplementation_DividerImplImplementationScope);



   BasicCalculatorComposite_DividerImpl->setImplementation(DividerImpl_DividerImplImplementation);


   Trentino::SCA::Model::ComponentService* const DividerImpl_Divider3= factory.createComponentService();
   Trentino::SCA::Model::CPPInterface* const Divider3_TrentinoExampleBasicCalculatorDividerhInterface3= factory.createCPPInterface();
   Divider3_TrentinoExampleBasicCalculatorDividerhInterface3->setClazz("Trentino::Example::BasicCalculator::Divider");
   Divider3_TrentinoExampleBasicCalculatorDividerhInterface3->setHeader("./services/TrentinoExampleBasicCalculatorDivider.h");
   Divider3_TrentinoExampleBasicCalculatorDividerhInterface3->setRemotable(false);



   DividerImpl_Divider3->setInterface(Divider3_TrentinoExampleBasicCalculatorDividerhInterface3);
   DividerImpl_Divider3->setName("Divider");


   BasicCalculatorComposite_DividerImpl->addServiceElement(DividerImpl_Divider3);
   BasicCalculatorComposite_DividerImpl->setAutowire(false);
   BasicCalculatorComposite_DividerImpl->setName("DividerImpl");


   BasicCalculatorCompositeWrapper_BasicCalculatorComposite->addComponentElement(BasicCalculatorComposite_DividerImpl);
   BasicCalculatorCompositeWrapper_BasicCalculatorComposite->setAutowire(false);
   BasicCalculatorCompositeWrapper_BasicCalculatorComposite->setLocal(false);
   BasicCalculatorCompositeWrapper_BasicCalculatorComposite->setName("BasicCalculatorComposite");
   BasicCalculatorCompositeWrapper_BasicCalculatorComposite->setTargetNamespace("BasicCalculatorNamespace");






   Trentino::SCA::Model::ComponentType* const CalculatorImplCompType= factory.createComponentType();
   Trentino::SCA::Model::ComponentTypeReference* const CalculatorImplCompType_Divider2= factory.createComponentTypeReference();
   CalculatorImplCompType_Divider2->setAutowire(false);
   CalculatorImplCompType_Divider2->setMultiplicity("1..1");
   CalculatorImplCompType_Divider2->setNonOverridable(false);
   CalculatorImplCompType_Divider2->addTarget("DividerImpl/Divider");
   CalculatorImplCompType_Divider2->setWiredByImpl(false);

   Trentino::SCA::Model::CPPInterface* const Divider2_TrentinoExampleBasicCalculatorDividerhInterface2= factory.createCPPInterface();
   Divider2_TrentinoExampleBasicCalculatorDividerhInterface2->setClazz("Trentino::Example::BasicCalculator::Divider");
   Divider2_TrentinoExampleBasicCalculatorDividerhInterface2->setHeader("services/TrentinoExampleBasicCalculatorDivider.h");
   Divider2_TrentinoExampleBasicCalculatorDividerhInterface2->setRemotable(false);

   CalculatorImplCompType_Divider2->setInterface(Divider2_TrentinoExampleBasicCalculatorDividerhInterface2);
   CalculatorImplCompType_Divider2->setName("Divider");

   CalculatorImplCompType->addReferenceElement(CalculatorImplCompType_Divider2);
   Trentino::SCA::Model::ComponentService* const CalculatorImplCompType_Calculator2= factory.createComponentService();

   Trentino::SCA::Model::CPPInterface* const Calculator2_TrentinoExampleBasicCalculatorCalculatorhInterface2= factory.createCPPInterface();
   Calculator2_TrentinoExampleBasicCalculatorCalculatorhInterface2->setClazz("Trentino::Example::BasicCalculator::Calculator");
   Calculator2_TrentinoExampleBasicCalculatorCalculatorhInterface2->setHeader("services/TrentinoExampleBasicCalculatorCalculator.h");
   Calculator2_TrentinoExampleBasicCalculatorCalculatorhInterface2->setRemotable(false);

   CalculatorImplCompType_Calculator2->setInterface(Calculator2_TrentinoExampleBasicCalculatorCalculatorhInterface2);
   CalculatorImplCompType_Calculator2->setName("Calculator");

   CalculatorImplCompType->addServiceElement(CalculatorImplCompType_Calculator2);

   Trentino::SCA::Model::ComponentType* const DividerImplCompType= factory.createComponentType();
   Trentino::SCA::Model::ComponentService* const DividerImplCompType_Divider4= factory.createComponentService();

   Trentino::SCA::Model::CPPInterface* const Divider4_TrentinoExampleBasicCalculatorDividerhInterface4= factory.createCPPInterface();
   Divider4_TrentinoExampleBasicCalculatorDividerhInterface4->setClazz("Trentino::Example::BasicCalculator::Divider");
   Divider4_TrentinoExampleBasicCalculatorDividerhInterface4->setHeader("services/TrentinoExampleBasicCalculatorDivider.h");
   Divider4_TrentinoExampleBasicCalculatorDividerhInterface4->setRemotable(false);

   DividerImplCompType_Divider4->setInterface(Divider4_TrentinoExampleBasicCalculatorDividerhInterface4);
   DividerImplCompType_Divider4->setName("Divider");

   DividerImplCompType->addServiceElement(DividerImplCompType_Divider4);


   Trentino::SCA::Model::ContributionType* const Trentino_Contribution= factory.createContributionType();
   Trentino::SCA::Model::DeployableType* const Contribution_Deployable= factory.createDeployableType();
   Trentino::XML::Schema::QName* Contribution_Deployable_CompositeQName = factory.createQName("BasicCalculatorComposite", "BasicCalculatorNamespace", "sample");
   Contribution_Deployable->setComposite(Contribution_Deployable_CompositeQName);

   Trentino_Contribution->addDeployableElement(Contribution_Deployable);

   modelLoader->associate(BasicCalculatorComposite_CalculatorImpl , CalculatorImplCompType); 
   modelLoader->associate(BasicCalculatorComposite_DividerImpl , DividerImplCompType); 

   }

TRENTINO_DLLEXPORT  Trentino::Invocation::ServiceInvocationWrapperBase* TRENTINO_CDECL Trentino::Gen::BasicCalculatorGen::BasicCalculatorContributionInfo::getServiceInvocationWrapperByClassName( const std::string& className )
   {
   if(className == std::string("Trentino::Example::BasicCalculator::Calculator")){
       return new Trentino::Gen::BasicCalculatorGen::Trentino_Example_BasicCalculator_CalculatorWrapper();
      }

   if(className == std::string("Trentino::Example::BasicCalculator::Divider")){
      return new Trentino::Gen::BasicCalculatorGen::Trentino_Example_BasicCalculator_DividerWrapper();
      }
   return nullptr;
   }

Trentino::Gen::BasicCalculatorGen::BasicCalculatorContributionInfo::BasicCalculatorContributionInfo()
   {

   }

Trentino::Gen::BasicCalculatorGen::BasicCalculatorContributionInfo::~BasicCalculatorContributionInfo()
   {

   }

TRENTINO_DLLEXPORT  Trentino::Binding::BindingHelperBase* TRENTINO_CDECL Trentino::Gen::BasicCalculatorGen::BasicCalculatorContributionInfo::getBindingHelperByBindingIdAndClassName( const std::string& /*bindingId*/,const std::string& /*className*/ )
   {
   return nullptr;
   }

 
