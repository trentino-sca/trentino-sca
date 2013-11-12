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

<#--#ifdef WIN32
#ifdef ${applicationName}GEN_EXPORTS
#undef ${applicationName}GEN_IMPORT_EXPORT
#define ${applicationName}GEN_IMPORT_EXPORT __declspec(dllexport)
#else
#undef ${applicationName}GEN_IMPORT_EXPORT
#define ${applicationName}GEN_IMPORT_EXPORT __declspec(dllimport)       
#endif //${applicationName}GEN_EXPORTS
#else
#define ${applicationName}GEN_IMPORT_EXPORT
#endif //WIN32-->

<#-- all composites are given in a list so the template traces 
that list and calls createMirrorObject for each composite in the list-->
<#macro traceCompositeList mirrorObjectList>
<#foreach mirrorObject in mirrorObjectList>
<@createMirrorObject mirrorObject = mirrorObject parentFieldName = "Trentino"> </@createMirrorObject>
</#foreach>
</#macro>

<#-- each composite(mirrorObject) is a inherits from mirror class so has a getFields function-->
<#macro createMirrorObject mirrorObject parentFieldName>
	<#assign isUsed = true>
	<#assign fullClassName = "Trentino::SCA::Model::" + mirrorObject.className>
	<#assign fullClassNameWithPtr = fullClassName + "*">
	<#assign mirrorObjname = parentFieldName + "_" + mirrorObject.nameGen>
		<#if fullClassName != "Trentino::SCA::Model::CompositeWrapper">
			<#if !(mirrorObject.className == "CPPImplementationScope" || mirrorObject.className == "CreateResource" || mirrorObject.className == "InteractionOrImplementation" || mirrorObject.className == "OverrideOptions")>
				${fullClassNameWithPtr} const ${mirrorObjname}= factory.create${mirrorObject.className}();
			</#if>
		</#if>
		<#foreach field in mirrorObject.fields>
		<#if field.simple== true><#-- for simple types -->
			<#assign parentObjName = parentFieldName + "_" + mirrorObject.nameGen>
			<#if field.argument != "NameGen">
				<#if !(mirrorObject.className == "CPPImplementationScope" || mirrorObject.className == "CreateResource" || mirrorObject.className == "InteractionOrImplementation" || mirrorObject.className == "OverrideOptions" )>
					<#assign i = field.value?index_of("#")>
					<#if i != -1><#-- with QName value-->
					  	<#assign value1 = field.value?substring(0,i)>
						<#assign temp = field.value?substring(i+1)>
						<#assign i = temp?index_of("#")>
						<#if i != -1>
						<#assign value2 = temp?substring(0,i)>
						<#assign value3 = temp?substring(i+1)>
						Trentino::XML::Schema::QName* ${parentObjName}_${field.argument}QName = factory.createQName("${value1}", "${value2}", "${value3}");
		 				${parentObjName}->set${field.argument}(${parentObjName}_${field.argument}QName);
						<#else>
						log : error about Qname parsing
						</#if>
					<#else><#-- without QName value-->
						${parentObjName}->set${field.argument}(${field.value});
					</#if>
				<#else><#-- for enum types-->
					${fullClassNameWithPtr} const ${mirrorObjname}= factory.create${mirrorObject.className}(${field.value});
				</#if>
			</#if>
		<#elseif field.list== true> <#-- for list types -->
			<#if field.type == "class java.lang.String"><#-- for string list fields like promote and property content we need to parse the value of list-->
				<#assign mirrorObjname2 = parentFieldName + "_" + mirrorObject.nameGen>
				<#list field.listItems as x> ${mirrorObjname2}->${field.accessor}("${x}");
				</#list>
			<#else> <#-- if not use the name gen-->
				<#foreach subMirrorObject in field.listItems><#-- if the list is a string directly put the value-->
					<#assign pFieldName = field.name>
					<@createMirrorObject mirrorObject = subMirrorObject parentFieldName= pFieldName> </@createMirrorObject>
					<#assign pFieldName = field.name>
					<#assign mirrorObjname2 = parentFieldName + "_" + mirrorObject.nameGen>
					<#assign subMirrorObjNameGen = field.name + "_" + subMirrorObject.nameGen >
					${mirrorObjname2}->${field.accessor}(${subMirrorObjNameGen});
				</#foreach>
			</#if>
		<#else><#-- for complex types first recursively createMirrorObject for the  complex type field -->
				<#assign mirrorObjname3 = parentFieldName + "_" + mirrorObject.nameGen>
				<#assign isUsed = false>
				<@createMirrorObject mirrorObject = field.mirrorObject parentFieldName= mirrorObject.nameGen> </@createMirrorObject>
				<#assign parentObjName = parentFieldName + "_" + mirrorObject.nameGen>
				<#if field.argument != "NameGen"> <#-- since name gen is artificially added by Trengen for naming variables omit it in generate code-->
					<#if !parentObjName?string?ends_with("Wrapper")><#-- for Wrapper don't set antyting(TODO omit wrapper) for rest set the created complex type-->
						<#if isUsed == true && field.argument=="Metadata">
							${parentObjName}->set${field.argument}(${mirrorObjname2});
							<#assign isUsed = false>
						<#elseif isUsed == true>
							${parentObjName}->set${field.argument}(${mirrorObjname});
							<#assign isUsed = false>
						<#else>
							${parentObjName}->set${field.argument}(${mirrorObjname3});
						</#if>
					</#if>
				</#if>
		</#if>
		</#foreach>
	
</#macro>
<#-- begin - Creation of componentTypeLoader -------------------------------------------------------------------->
<#-- all componentTypes are given in a list so the template traces 
that list and calls createMirrorComponentType for each componentType in the list-->
<#macro traceComponentTypeList mirrorComponentTypeList>
<#foreach mirrorComponentType in mirrorComponentTypeList>
<@createMirrorComponentType mirrorCompType = mirrorComponentType parentFieldName = "Trentino" > </@createMirrorComponentType>
</#foreach>
</#macro>

<#-- each componentType(mirrorObject) is a inherits from mirror class so has a getFields function-->
<#macro createMirrorComponentType mirrorCompType parentFieldName>
	<#assign isUsed = true>
	<#assign fullClassName = "Trentino::SCA::Model::" + mirrorCompType.className>
	<#assign fullClassNameWithPtr = fullClassName + "*">
	<#if mirrorCompType.className != "ComponentType">
	<#assign mirrorObjname = parentFieldName + "_" + mirrorCompType.nameGen>
	<#else>
	<#assign mirrorObjname = mirrorCompType.nameGen>
	</#if>
			${fullClassNameWithPtr} const ${mirrorObjname}= factory.create${mirrorCompType.className}();
		<#foreach field in mirrorCompType.fields>
		<#if field.simple== true>
			<#assign parentObjName = parentFieldName + "_" + mirrorCompType.nameGen>
			<#if field.argument != "NameGen">
				<#if !(mirrorCompType.className == "CPPImplementationScope" || mirrorCompType.className == "CreateResource" || mirrorCompType.className == "InteractionOrImplementation" || mirrorCompType.className == "OverrideOptions")>
					<#assign i = field.value?index_of("#")>
					<#if i != -1>
						<#assign value1 = field.value?substring(0,i)>
						<#assign temp = field.value?substring(i+1)>
						<#assign i = temp?index_of("#")>
						<#assign value2 = temp?substring(0,i)>
						<#assign value3 = temp?substring(i+1)>
					
						
						Trentino::XML::Schema::QName* ${parentObjName}_${field.argument}QName = factory.createQName("${value1}", "${value2}", "${value3}");
		 				${parentObjName}->set${field.argument}(${parentObjName}_${field.argument}QName);
		 			<#else>
					${parentObjName}->set${field.argument}(${field.value});
					</#if>
				<#else>
					${fullClassNameWithPtr} const ${mirrorObjname}= factory.create${mirrorCompType.className}(${field.value});
				</#if>
			</#if>
		<#elseif field.list== true><#-- for list types -->
			
				<#if field.type == "class java.lang.String">
					<#assign mirrorObjname2 = parentFieldName + "_" + mirrorCompType.nameGen>
					<#list field.listItems as x> ${mirrorObjname2}->${field.accessor}("${x}");
					</#list>
				<#else><#-- if not use the name gen-->
				<#foreach subMirrorCompType in field.listItems>
					<#assign pFieldName = field.name>
					<@createMirrorComponentType mirrorCompType = subMirrorCompType parentFieldName= pFieldName> </@createMirrorComponentType>
					<#assign pFieldName = field.name>
					<#if mirrorCompType.className != "ComponentType">
					<#assign mirrorObjname2 = parentFieldName + "_" + mirrorCompType.nameGen>
					<#else>
					<#assign mirrorObjname2 = mirrorCompType.nameGen>
					</#if>
					<#assign subMirrorObjNameGen = field.name + "_" + subMirrorCompType.nameGen >
					${mirrorObjname2}->${field.accessor}(${subMirrorObjNameGen});
					</#foreach>
				</#if>
			
		<#else>
				<#assign mirrorObjname3 = parentFieldName + "_" + mirrorCompType.nameGen>
				<#assign isUsed = false>
				
				<@createMirrorComponentType mirrorCompType = field.mirrorObject parentFieldName= mirrorCompType.nameGen> </@createMirrorComponentType>
				<#assign parentObjName = parentFieldName + "_" + mirrorCompType.nameGen>
				<#if field.argument != "NameGen">
					<#if !parentObjName?string?ends_with("Wrapper")>
						<#if isUsed == true && field.argument=="Metadata">
							${parentObjName}->set${field.argument}(${mirrorObjname2});
							<#assign isUsed = false>
						<#elseif isUsed == true >
							${parentObjName}->set${field.argument}(${mirrorObjname});
							<#assign isUsed = false>
						<#else>
							${parentObjName}->set${field.argument}(${mirrorObjname3});
						</#if>
					</#if>
				</#if>
		</#if>
		</#foreach>
</#macro>
<#-- end - Creation of componentTypeLoader -------------------------------------------------------------------->

<#macro createMirrorContribution mirrorContribution parentFieldName>
	<#assign fullClassName = "Trentino::SCA::Model::" + mirrorContribution.className>
	<#assign fullClassNameWithPtr = fullClassName + "*">
	<#assign mirrorObjname = parentFieldName + "_" + mirrorContribution.nameGen>
	<#if fullClassNameWithPtr != "Trentino::SCA::Model::CompositeWrapper*">	
	<#assign isAlone = true>
	<#list mirrorContribution.fields as field>
	<#if field.argument != "NameGen">
	<#assign isAlone = false>
	</#if>
	</#list>
		<#if isAlone == false>
		${fullClassNameWithPtr} const ${mirrorObjname}= factory.create${mirrorContribution.className}();
		</#if>
		<#foreach field in mirrorContribution.fields>
		<#if field.simple>
			<#assign parentObjName = parentFieldName + "_" + mirrorContribution.nameGen>
			<#if field.argument != "NameGen">
				<#assign i = field.value?index_of("#")>
				<#if i!= -1>
				<#assign value1 = field.value?substring(0,i)>
				<#assign temp = field.value?substring(i+1)>
				<#assign i = temp?index_of("#")>
				<#assign value2 = temp?substring(0,i)>
				<#assign value3 = temp?substring(i+1)>
				Trentino::XML::Schema::QName* ${parentObjName}_${field.argument}QName = factory.createQName("${value1}", "${value2}", "${value3}");
 				${parentObjName}->set${field.argument}(${parentObjName}_${field.argument}QName);
 				<#else>
				${parentObjName}->set${field.argument}(${field.value});
				</#if>
			</#if>
		<#elseif field.list>
			<#foreach subMirrorObject in field.listItems>
				<#if field.type == "class java.lang.String">
				<#assign mirrorObjname = parentFieldName + "_" + mirrorContribution.nameGen>
				<#--assign subMirrorObjNameGen = field.name + "_" + subMirrorObject.nameGen-->
				${mirrorObjname}->${field.accessor}(${field.value});
				<#else>
				<#assign pFieldName = field.name>
				<#assign mirrorObjname = parentFieldName + "_" + mirrorContribution.nameGen>
				<@createMirrorContribution mirrorContribution = subMirrorObject parentFieldName= pFieldName> </@createMirrorContribution>
				<#assign pFieldName = field.name>
				<#assign mirrorObjname = parentFieldName + "_" + mirrorContribution.nameGen>
				<#assign subMirrorObjNameGen = field.name + "_" + subMirrorObject.nameGen >
				${mirrorObjname}->${field.accessor}(${subMirrorObjNameGen});
				</#if>
			</#foreach>
			<#else>
				<@createMirrorContribution mirrorContribution = field.mirrorContribution parentFieldName= pFieldName> </@createMirrorContribution>
				<#assign parentObjName = parentFieldName + "_" + mirrorContribution.nameGen>
				<#if field.argument != "NameGen">
					${parentObjName}->set${field.argument}(${mirrorObjname});
			</#if>
		</#if>
	</#foreach>
	<#else>
	<#foreach field in mirrorContribution.fields>
		<#if field.simple>
			<#if field.argument != "NameGen">
				${parentFieldName}->set${field.argument}(${field.value});
			</#if>
		<#elseif field.list>
			<#foreach subMirrorObject in field.listItems>
				<#assign pFieldName = field.name>
				<#assign mirrorObjname = parentFieldName + "_" + mirrorContribution.nameGen>
				<@createMirrorContribution mirrorContribution = subMirrorObject parentFieldName= pFieldName> </@createMirrorContribution>
				<#assign pFieldName = field.name>
				<#assign mirrorObjname = parentFieldName + "_" + mirrorContribution.nameGen>
				<#assign subMirrorObjNameGen = field.name + "_" + subMirrorObject.nameGen >
				${parentFieldName}->${field.accessor}(${subMirrorObjNameGen});
			</#foreach>
			<#else>
				<@createMirrorContribution mirrorContribution = field.mirrorContribution parentFieldName= field.name> </@createMirrorContribution>
				<#assign parentObjName = parentFieldName + "_" + mirrorContribution.nameGen>
				<#if field.argument != "NameGen">
					<#--${parentFieldName}->set${field.argument}(${mirrorObjname});-->
			</#if>
		</#if>
	</#foreach>
	</#if>
</#macro>

<#-- association between the componentType and component is kept statically in a
list of association object keeping the variable names as Strings-->
<#macro traceComponentTypeComponentAssocMap componentTypeComponentAssocList>
<#list componentTypeComponentAssocList as association>
 modelLoader->associate(${association.componentGivenName} , ${association.componentTypeGivenName}); 
</#list>
</#macro>

//! the model loader for this contribution
TRENTINO_DLLEXPORT void TRENTINO_CDECL Trentino::Gen::${contributionName}ContributionInfo::loadModel( Trentino::Core::ContributionLoading::SCAModelLoader* modelLoader )
{
   assert(modelLoader != nullptr);

   Trentino::Core::ContributionLoading::SCAModelLoader::SCAModelFactory& factory = modelLoader->scaModelFactory();
   
   	<@traceCompositeList mirrorObjectList = mirrorObjectList> </@traceCompositeList>
	<@traceComponentTypeList mirrorComponentTypeList = mirrorComponentTypeList> </@traceComponentTypeList>
	<@createMirrorContribution mirrorContribution = mirrorContribution parentFieldName = "Trentino"> </@createMirrorContribution>
	<@traceComponentTypeComponentAssocMap componentTypeComponentAssocList = componentTypeComponentAssocList> </@traceComponentTypeComponentAssocMap>
}