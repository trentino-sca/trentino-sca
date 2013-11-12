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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
// **********************************************************************************
package org.trentino.trengen.tools.scavalidation;

/**
 * This class has String constants for Conformance-items in SCA and CPP Spec
 */
public class ConformanceManagerConstants {
	public static String	CI_ASM40001_VIOLATED	= "[ASM40001- The extension of a componentType side "
	                                                      + "file name MUST be .componentType.] is violated.";
	public static String	CI_ASM50001_VIOLATED	= "[ASM50001- The @name attribute of a <component/> "
	                                                      + "child element of a <composite/> MUST be unique amongst the component elements of that "
	                                                      + "<composite/>.] is violated.";
	public static String	CI_ASM60001_VIOLATED	= "[ASM60001- A composite @name attribute value MUST "
	                                                      + "be unique within the namespace of the composite.] is violated.";
	public static String	CI_ASM60041_VIOLATED	= "[ASM60041- If the included composite has the value "
	                                                      + "true for the attribute @local then the including composite MUST have the same value for "
	                                                      + "the @local attribute, else it is an error.] is violated.";
	public static String	CI_ASM60042_VIOLATED	= "[ASM60042- The @name attribute of an include element "
	                                                      + "MUST be the QName of a composite in the SCA Domain.] is violated.";
	public static String	CI_ASM60031_VIOLATED	= "[ASM60031- The SCA runtime MUST raise an error if the"
	                                                      + " composite resulting from the inclusion of one composite into another is invalid.] is violated.";
	public static String	CI_ASM12027_VIOLATED	= "[ASM12027- An SCA runtime MUST reject files that do "
	                                                      + "not conform to the schema declared in sca-contribution.xsd.] is violated.";
	public static String	CI_ASM13001_VIOLATED	= "[ASM13001- An SCA runtime MUST reject a composite "
	                                                      + "file that does not conform to the sca-core.xsd, sca-interface-wsdl.xsd, "
	                                                      + "scaimplementation-composite.xsd and sca-binding-sca.xsd schema.] is violated.";

	public static String	CI_CPP110001_VIOLATED	= "[CPP110001- An SCA implementation MUST reject a"
	                                                      + " composite file that does not conform to http://docs.oasis-open.org/opencsa/sca/200912/sca-interface-cpp-1.1.xsd "
	                                                      + "or http://docs.oasis-open.org/opencsa/sca/200912/sca-implementation-cpp-1.1.xsd.] is violated.";
	public static String	CI_CPP110002_VIOLATED	= "[CPP110002- a componentType  does not conform to xsd schema http://docs.oasis-open.org/opencsa/sca/200912/sca-interface-cpp-1.1.xsd.]";
	public static String	CI_CPP110003_VIOLATED	= "[CPP110003- An SCA implementation MUST reject a contribution "
	                                                      + "file that does not conform to http://docs.oasis-open.org/opencsa/sca/200912/sca-contribution-cpp-1.1.xsd.] is violated.";

	public static String	CI_CPP20007_VIOLATED	= "[CPP20007- The @name attribute of a <function/> child element"
	                                                      + " of a <interface.cpp/> MUST be unique amongst the <function/> elements of that <interface.cpp/>.] is violated.";
	public static String	CI_CPP20008_VIOLATED	= "[CPP20008- The @name attribute of a <callbackFunction/> "
	                                                      + "child element of a <interface.cpp/> MUST be unique amongst the <callbackFunction/> elements of that <interface.cpp/>.] is violated.";
	public static String	CI_CPP20009_VIOLATED	= "[CPP20009- The name of the componentType file for a C++"
	                                                      + " implementation MUST match the class name (excluding any namespace definition) of the "
	                                                      + "implementations as defined by the @class attribute of the <implementation.cpp/> element.] is violated.";
	public static String	CI_CPP20010_VIOLATED	= "[CPP20010- The @name attribute of a <function/> child "
	                                                      + "element of a <implementation.cpp/> MUST be unique amongst the <function/> elements of that <implementation.cpp/>.] is violated.";

	// Property@ComponentType
	public static String	CI_ASM40005_VIOLATED	= "[ASM40005- The @name attribute of a <property/> child element "
	                                                      + "of a <componentType/> MUST be unique amongst the property elements of that <componentType/>.] is violated.";
	public static String	CI_ASM40007_VIOLATED	= "[ASM40007- The value of the property @type attribute MUST be the"
	                                                      + " QName of an XML schema type.] is violated.";
	public static String	CI_ASM40010_VIOLATED	= "[ASM40010- A single property element MUST NOT contain both a @type "
	                                                      + "attribute and an @element attribute.] is violated.";
	public static String	CI_ASM40011_VIOLATED	= "[ASM40011- When the componentType has @mustSupply='true' for a "
	                                                      + "property element, a component using the implementation MUST supply a value for the property since the "
	                                                      + "implementation has no default value for the property.] is violated.";
	// Property@Component

	public static String	CI_ASM50027_VIOLATED	= "[ASM50027- If the @value attribute of a component property element "
	                                                      + "is declared, the type of the property MUST be an XML Schema simple type and the @value attribute MUST "
	                                                      + "contain a single value of that type.] is violated.";
	public static String	CI_ASM50028_VIOLATED	= "[ASM50028- If the value subelement of a component property is specified, "
	                                                      + "the type of the property MUST be an XML Schema simple type or an XML schema complex type.] is violated.";
	public static String	CI_ASM50029_VIOLATED	= "[ASM50029- If a component property value is declared using a child "
	                                                      + "element of the <property/> element, the type of the property MUST be an XML Schema global element and the "
	                                                      + "declared child element MUST be an instance of that global element.] is violated.";
	public static String	CI_ASM50031_VIOLATED	= "[ASM50031- The @name attribute of a property element of a <component/> "
	                                                      + "MUST be unique amongst the property elements of that <component/>.] is violated.";
	public static String	CI_ASM50036_VIOLATED	= "[ASM50036- The property type specified for the property element of a "
	                                                      + "component MUST be compatible with the type of the property with the same @name declared in the component "
	                                                      + "type of the implementation used by the component. If no type is declared in the component property element,"
	                                                      + " the type of the property declared in the componentType of the implementation MUST be used.] is violated.";
	public static String	CI_ASM50037_VIOLATED	= "[ASM50037- The @name attribute of a property element of a <component/> "
	                                                      + "MUST match the @name attribute of a property element of the componentType of the <implementation/> child "
	                                                      + "element of the component.] is violated.";
	public static String	CI_ASM50038_VIOLATED	= "[ASM50038- In these cases where the types of two property elements are "
	                                                      + "matched, the types declared for the two <property/> elements MUST be compatible] is violated.";
	public static String	CI_ASM50035_VIOLATED	= "[ASM50035- A single property element MUST NOT contain both a @type attribute "
	                                                      + "and an @element attribute.] is violated.";
	public static String	CI_ASM50045_VIOLATED	= "[ASM50045- The value of the component property @file attribute MUST be a "
	                                                      + "dereferencable URI to a file containing the value for the property.] is violated.";
	public static String	CI_ASM50032_VIOLATED	= "[ASM50032- If a property is single-valued, the <value/> subelement MUST NOT"
	                                                      + " occur more than once.] is violated.";
	public static String	CI_ASM50033_VIOLATED	= "[ASM50033- A property <value/> subelement MUST NOT be used when the @value "
	                                                      + "attribute is used to specify the value for that property.] is violated.";

	// Property@Composite
	public static String	CI_ASM60014_VIOLATED	= "[ASM60014- The @name attribute of a composite property MUST be unique amongst"
	                                                      + " the properties of the same composite.] is violated.";
	public static String	CI_ASM60040_VIOLATED	= "[ASM60040- A single property element MUST NOT contain both a @type attribute"
	                                                      + " and an @element attribute.] is violated.";

	// service & reference
	public static String	CI_ASM40003_VIOLATED	= "[ASM40003- The @name attribute of a <service/> child element of a <componentType/>"
	                                                      + " MUST be unique amongst the service elements of that <componentType/>.] is violated.";
	public static String	CI_ASM40004_VIOLATED	= "[ASM40004- The @name attribute of a <reference/> child element of a <componentType/>"
	                                                      + " MUST be unique amongst the reference elements of that <componentType/>.] is violated.";
	public static String	CI_ASM50002_VIOLATED	= "[ASM50002- The @name attribute of a service element of a <component/> MUST be "
	                                                      + "unique amongst the service elements of that <component/>] is violated.";
	public static String	CI_ASM50003_VIOLATED	= "[ASM50003- The @name attribute of a service element of a <component/> "
	                                                      + "MUST match the @name attribute of a service element of the componentType of the <implementation/> child element of "
	                                                      + "the component.] is violated.";
	public static String	CI_ASM50008_VIOLATED	= "[ASM50008- The @name attribute of a reference element of a <component/> MUST "
	                                                      + "match the @name attribute of a reference element of the componentType of the <implementation/> child element of "
	                                                      + "the component.] is violated.";
	public static String	CI_ASM50026_VIOLATED	= "[ASM50026- If a reference has a value specified for one or more target "
	                                                      + "services in its @target attribute, there MUST NOT be any child <binding/> elements declared for that reference.] is violated.";
	public static String	CI_ASM50039_VIOLATED	= "[ASM50039- A reference with multiplicity 0..1 MUST have no more than one "
	                                                      + "target service defined.] is violated.";
	public static String	CI_ASM50040_VIOLATED	= "[ASM50040- A reference with multiplicity 1..1 MUST have exactly one target "
	                                                      + "service defined.] is violated.";
	public static String	CI_ASM50041_VIOLATED	= "[ASM50041- A reference with multiplicity 1..n MUST have at least one "
	                                                      + "target service defined.] is violated.";
	public static String	CI_ASM50042_VIOLATED	= "[ASM50042- If a component reference has @multiplicity 0..1 or 1..1 and"
	                                                      + " @nonOverridable==true, then the component reference MUST NOT be promoted by any composite reference.] is violated.";
	public static String	CI_ASM60003_VIOLATED	= "[ASM60003- The name of a composite <service/> element MUST be unique "
	                                                      + "across all the composite services in the composite.] is violated.";
	public static String	CI_ASM60004_VIOLATED	= "[ASM60004- A composite <service/> element's @promote attribute MUST "
	                                                      + "identify one of the component services within that composite.] is violated.";
	public static String	CI_ASM60006_VIOLATED	= "[ASM60006- The name of a composite <reference/> element MUST be unique "
	                                                      + "across all the composite references in the composite.] is violated.";
	public static String	CI_ASM60007_VIOLATED	= "[ASM60007- Each of the URIs declared by a composite reference's @promote "
	                                                      + "attribute MUST identify a component reference within the composite.] is violated.";
	public static String	CI_ASM60009_VIOLATED	= "[ASM60009- the intents declared on a composite reference and on the component "
	                                                      + "references which it promotes MUST NOT be mutually exclusive.] and [ASM60010- If any intents in the set which apply "
	                                                      + "to a composite reference are mutually exclusive then the SCA runtime MUST raise an error.] is violated.";
	public static String	CI_ASM50011_VIOLATED	= "[ASM50011- If an interface is declared for a component reference, the interface "
	                                                      + "MUST provide a compatible superset of the interface declared for the equivalent reference in the componentType of the "
	                                                      + "implementation.] is violated.";
	public static String	CI_ASM50009_VIOLATED	= "[ASM50009- The value of multiplicity for a component reference MUST only be equal "
	                                                      + "or further restrict any value for the multiplicity of the reference with the same name in the componentType of the "
	                                                      + "implementation, where further restriction means 0..n to 0..1 or 1..n to 1..1.] is violated.";
	public static String	CI_ASM50004_VIOLATED	= "[ASM50004- If an interface is declared for a component service, the interface MUST "
	                                                      + "provide a compatible subset of the interface declared for the equivalent service in the componentType of the "
	                                                      + "implementation] is violated.";
	public static String	CI_ASM60005_VIOLATED	= "[ASM60005- If a composite service interface is specified it MUST be the same "
	                                                      + "or a compatible subset of the interface provided by the promoted component service.] is violated.";
	public static String	CI_ASM60008_VIOLATED	= "[ASM60008- the interfaces of the component references promoted by a composite "
	                                                      + "reference MUST be the same, or if the composite reference itself declares an interface then each of the component "
	                                                      + "reference interfaces MUST be a compatible subset of the composite reference interface.] or [ASM60012- If a composite"
	                                                      + " reference has an interface specified, it MUST provide an interface which is the same or which is a compatible "
	                                                      + "superset of the interface(s) declared by the promoted component reference(s).] is violated.";
	public static String	CI_ASM60012_VIOLATED	= "[ASM60012- If a composite reference has an interface specified, it MUST provide "
	                                                      + "an interface which is the same or which is a compatible superset of the interface(s) declared by the promoted"
	                                                      + " component reference(s).] is violated.";
	public static String	CI_ASM60011_VIOLATED	= "[ASM60011- The multiplicity of a composite reference MUST be equal to or further "
	                                                      + "restrict the multiplicity of each of the component references that it promotes, with the exception that the "
	                                                      + "multiplicity of the composite reference does not have to require a target if there is already a target on the "
	                                                      + "component reference. This means that a component reference with multiplicity 1..1 and a target can be promoted "
	                                                      + "by a composite reference with multiplicity 0..1, and a component reference with multiplicity 1..n and one or more "
	                                                      + "targets can be promoted by a composite reference with multiplicity 0..n or 0..1.] is violated.";
	public static String	CI_ASM50007_VIOLATED	= "[ASM50007- The @name attribute of a service element of a <component/> MUST "
	                                                      + "be unique amongst the service elements of that <component/>] is violated.";
	public static String	CI_ASM60035_VIOLATED	= "[ASM60035- All the component references promoted by a single composite reference "
	                                                      + "MUST have the same value for @wiredByImpl.] is violated.";
	public static String	CI_ASM60036_VIOLATED	= "[ASM60036- If the @wiredByImpl attribute is not specified on the composite "
	                                                      + "reference, the default value is 'true' if all of the promoted component references have a wiredByImpl value of "
	                                                      + "'true', and the default value is 'false' if all the promoted component references have a wiredByImpl value of "
	                                                      + "'false'. If the @wiredByImpl attribute is specified, its value MUST be 'true' if all of the promoted component "
	                                                      + "references have a wiredByImpl value of 'true', and its value MUST be 'false' if all the promoted component references "
	                                                      + "have a wiredByImpl value of 'false'.] is violated.";
	public static String	CI_ASM60043_VIOLATED	= "[ASM60043- The interface declared by the target of a wire MUST be a compatible "
	                                                      + "superset of the interface declared by the source of the wire.] is violated.";
	public static String	CI_ASM60047_VIOLATED	= "[ASM60047- If there is no component service with @name corresponding to "
	                                                      + "<service-name>, the SCA runtime MUST raise an error.] is violated.";
	public static String	CI_ASM60048_VIOLATED	= "[ASM60048- If <service-name> is not present, the target component MUST have "
	                                                      + "one and only one service with an interface that is a compatible superset of the wire sources interface and satisifies "
	                                                      + "the policy requirements of the wire source, and the SCA runtime MUST use this service for the wire.] is violated.";
	public static String	CI_ASM60050_VIOLATED	= "[ASM60050- If there is no <binding/> subelement of the target service with @name "
	                                                      + "corresponding to <binding-name>, the SCA runtime MUST raise an error.] is violated.";
	public static String	CI_ASM90005_VIOLATED	= "[ASM90005- For a binding.sca of a component service, the @uri attribute MUST NOT "
	                                                      + "be present.] is violated.";
	public static String	CI_ASM40006_VIOLATED	= "[ASM40006- If @wiredByImpl is set to 'true', then any reference targets "
	                                                      + "configured for this reference MUST be ignored by the runtime.] is violated.";
	public static String	CI_ASM50010_VIOLATED	= "[ASM50010- If @wiredByImpl='true' is set for a reference, then the reference "
	                                                      + "MUST NOT be wired statically within a composite, but left unwired.] is violated.";
	public static String	CI_CPP80003_VIOLATED	= "[CPP80003] is violated.";
	public static String	CI_ASM50014_VIOLATED	= "[ASM50014- If @autowire='true', the autowire procedure MUST only be used "
	                                                      + "if no target is identified by any of the other ways listed above. It is not an error if @autowire='true' and a "
	                                                      + "target is also defined through some other means, however in this case the autowire procedure MUST NOT be used.] is violated.";
	public static String	CI_ASM90002_VIOLATED	= "[ASM90002- When a service or reference has multiple bindings, all "
	                                                      + "noncallback bindings of the service or reference MUST have unique names, and all callback bindings of "
	                                                      + "the service or reference MUST have unique names.] is violated.";
	public static String	CI_ASM50034_VIOLATED	= "[ASM50034- If any <wire/> element with its @replace attribute set to "
	                                                      + "'true' has a particular reference specified in its @source attribute, the value of the @target attribute "
	                                                      + "for that reference MUST be ignored and MUST NOT be used to define target services for that reference.] is violated.";
	public static String	CI_ASM50013_VIOLATED	= "[ASM50013- If @wiredByImpl='true', other methods of specifying the "
	                                                      + "target service MUST NOT be used.] is violated.";
	public static String	CI_ASM60030_VIOLATED	= "[ASM60030- The @name attribute of an <implementation.composite/> "
	                                                      + "element MUST contain the QName of a composite in the SCA Domain.] is violated.";

	public static String	CI_CPP20001_VIOLATED	= "[CPP20001- A C++ implementation MUST implement all of the operation(s)"
	                                                      + " of the service interface(s) of its componentType.] is violated.";
	public static String	CI_CPP20005_VIOLATED	= "[CPP20005- If the header file identified by the @header attribute of "
	                                                      + "an <interface.cpp/> element contains more than one class, then the @class attribute MUST be specified for the "
	                                                      + "<interface.cpp/> element.] is violated.";

	private ConformanceManagerConstants () {
	}
}
