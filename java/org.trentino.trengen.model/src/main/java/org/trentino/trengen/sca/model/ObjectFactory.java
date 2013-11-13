//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, vJAXB 2.1.10 in JDK 6 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2013.07.04 at 11:39:49 AM MESZ 
//


package org.trentino.trengen.sca.model;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the org.trentino.trengen.sca.model package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

    private final static QName _ImportCpp_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "import.cpp");
    private final static QName _OperationSelector_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "operationSelector");
    private final static QName _All_QNAME = new QName("http://www.w3.org/ns/ws-policy", "All");
    private final static QName _Import_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "import");
    private final static QName _Value_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "value");
    private final static QName _Contribution_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "contribution");
    private final static QName _Metadata_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "metadata");
    private final static QName _ImplementationType_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "implementationType");
    private final static QName _ImportBase_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "importBase");
    private final static QName _ImplementationComposite_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "implementation.composite");
    private final static QName _ExportBase_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "exportBase");
    private final static QName _Definitions_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "definitions");
    private final static QName _Include_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "include");
    private final static QName _ExportCpp_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "export.cpp");
    private final static QName _Composite_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "composite");
    private final static QName _ComponentType_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "componentType");
    private final static QName _BindingSca_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "binding.sca");
    private final static QName _Intent_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "intent");
    private final static QName _Interface_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "interface");
    private final static QName _BindingIpc_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "binding.ipc");
    private final static QName _BindingThrift_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "binding.thrift");
    private final static QName _Export_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "export");
    private final static QName _InterfaceCpp_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "interface.cpp");
    private final static QName _BindingType_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "bindingType");
    private final static QName _ImplementationCpp_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "implementation.cpp");
    private final static QName _PolicySet_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "policySet");
    private final static QName _WireFormat_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "wireFormat");
    private final static QName _Binding_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "binding");
    private final static QName _Callback_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "callback");
    private final static QName _Documentation_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "documentation");
    private final static QName _ExactlyOne_QNAME = new QName("http://www.w3.org/ns/ws-policy", "ExactlyOne");
    private final static QName _Implementation_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "implementation");
    private final static QName _IntentMapQualifier_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "qualifier");
    private final static QName _PolicySetIntentMap_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "intentMap");
    private final static QName _PolicySetPolicySetReference_QNAME = new QName("http://docs.oasis-open.org/ns/opencsa/sca/200912", "policySetReference");

    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: org.trentino.trengen.sca.model
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link OperatorContentType }
     * 
     */
    public OperatorContentType createOperatorContentType() {
        return new OperatorContentType();
    }

    /**
     * Create an instance of {@link ComponentService }
     * 
     */
    public ComponentService createComponentService() {
        return new ComponentService();
    }

    /**
     * Create an instance of {@link IPCBinding }
     * 
     */
    public IPCBinding createIPCBinding() {
        return new IPCBinding();
    }
    
    /**
     * Create an instance of {@link ThriftBinding }
     * 
     */
    public ThriftBinding createThriftBinding() {
        return new ThriftBinding();
    }

    /**
     * Create an instance of {@link PolicyAttachment }
     * 
     */
    public PolicyAttachment createPolicyAttachment() {
        return new PolicyAttachment();
    }

    /**
     * Create an instance of {@link Policy }
     * 
     */
    public Policy createPolicy() {
        return new Policy();
    }

    /**
     * Create an instance of {@link ExportType }
     * 
     */
    public ExportType createExportType() {
        return new ExportType();
    }

    /**
     * Create an instance of {@link CPPFunction }
     * 
     */
    public CPPFunction createCPPFunction() {
        return new CPPFunction();
    }

    /**
     * Create an instance of {@link Component }
     * 
     */
    public Component createComponent() {
        return new Component();
    }

    /**
     * Create an instance of {@link IntentMap }
     * 
     */
    public IntentMap createIntentMap() {
        return new IntentMap();
    }

    /**
     * Create an instance of {@link Wire }
     * 
     */
    public Wire createWire() {
        return new Wire();
    }

    /**
     * Create an instance of {@link CPPImplementation }
     * 
     */
    public CPPImplementation createCPPImplementation() {
        return new CPPImplementation();
    }

    /**
     * Create an instance of {@link TDefinitions }
     * 
     */
    public TDefinitions createTDefinitions() {
        return new TDefinitions();
    }

    /**
     * Create an instance of {@link SCAPropertyBase }
     * 
     */
    public SCAPropertyBase createSCAPropertyBase() {
        return new SCAPropertyBase();
    }

    /**
     * Create an instance of {@link WSCallback }
     * 
     */
    public WSCallback createWSCallback() {
        return new WSCallback();
    }

    /**
     * Create an instance of {@link BindingType }
     * 
     */
    public BindingType createBindingType() {
        return new BindingType();
    }

    /**
     * Create an instance of {@link CPPImport }
     * 
     */
    public CPPImport createCPPImport() {
        return new CPPImport();
    }

    /**
     * Create an instance of {@link Documentation }
     * 
     */
    public Documentation createDocumentation() {
        return new Documentation();
    }

    /**
     * Create an instance of {@link CPPInterface }
     * 
     */
    public CPPInterface createCPPInterface() {
        return new CPPInterface();
    }

    /**
     * Create an instance of {@link ComponentType }
     * 
     */
    public ComponentType createComponentType() {
        return new ComponentType();
    }

    /**
     * Create an instance of {@link Reference }
     * 
     */
    public Reference createReference() {
        return new Reference();
    }

    /**
     * Create an instance of {@link ComponentTypeReference }
     * 
     */
    public ComponentTypeReference createComponentTypeReference() {
        return new ComponentTypeReference();
    }

    /**
     * Create an instance of {@link ComponentReference }
     * 
     */
    public ComponentReference createComponentReference() {
        return new ComponentReference();
    }

    /**
     * Create an instance of {@link Metadata }
     * 
     */
    public Metadata createMetadata() {
        return new Metadata();
    }

    /**
     * Create an instance of {@link AppliesTo }
     * 
     */
    public AppliesTo createAppliesTo() {
        return new AppliesTo();
    }

    /**
     * Create an instance of {@link Qualifier }
     * 
     */
    public Qualifier createQualifier() {
        return new Qualifier();
    }

    /**
     * Create an instance of {@link PolicySet }
     * 
     */
    public PolicySet createPolicySet() {
        return new PolicySet();
    }

    /**
     * Create an instance of {@link CPPExport }
     * 
     */
    public CPPExport createCPPExport() {
        return new CPPExport();
    }

    /**
     * Create an instance of {@link CPPImplementationFunction }
     * 
     */
    public CPPImplementationFunction createCPPImplementationFunction() {
        return new CPPImplementationFunction();
    }

    /**
     * Create an instance of {@link ExternalAttachment }
     * 
     */
    public ExternalAttachment createExternalAttachment() {
        return new ExternalAttachment();
    }

    /**
     * Create an instance of {@link PolicySetReference }
     * 
     */
    public PolicySetReference createPolicySetReference() {
        return new PolicySetReference();
    }

    /**
     * Create an instance of {@link ImplementationType }
     * 
     */
    public ImplementationType createImplementationType() {
        return new ImplementationType();
    }

    /**
     * Create an instance of {@link Service }
     * 
     */
    public Service createService() {
        return new Service();
    }

    /**
     * Create an instance of {@link ImportType }
     * 
     */
    public ImportType createImportType() {
        return new ImportType();
    }

    /**
     * Create an instance of {@link SCABinding }
     * 
     */
    public SCABinding createSCABinding() {
        return new SCABinding();
    }

    /**
     * Create an instance of {@link PropertyValue }
     * 
     */
    public PropertyValue createPropertyValue() {
        return new PropertyValue();
    }

    /**
     * Create an instance of {@link Callback }
     * 
     */
    public Callback createCallback() {
        return new Callback();
    }

    /**
     * Create an instance of {@link Extensions }
     * 
     */
    public Extensions createExtensions() {
        return new Extensions();
    }

    /**
     * Create an instance of {@link PolicySetAttachment }
     * 
     */
    public PolicySetAttachment createPolicySetAttachment() {
        return new PolicySetAttachment();
    }

    /**
     * Create an instance of {@link MetadataStringAttribute }
     * 
     */
    public MetadataStringAttribute createMetadataStringAttribute() {
        return new MetadataStringAttribute();
    }

    /**
     * Create an instance of {@link URI }
     * 
     */
    public URI createURI() {
        return new URI();
    }

    /**
     * Create an instance of {@link PolicyReference }
     * 
     */
    public PolicyReference createPolicyReference() {
        return new PolicyReference();
    }

    /**
     * Create an instance of {@link SCAImplementation }
     * 
     */
    public SCAImplementation createSCAImplementation() {
        return new SCAImplementation();
    }

    /**
     * Create an instance of {@link Requires }
     * 
     */
    public Requires createRequires() {
        return new Requires();
    }

    /**
     * Create an instance of {@link Composite }
     * 
     */
    public Composite createComposite() {
        return new Composite();
    }

    /**
     * Create an instance of {@link ValueType }
     * 
     */
    public ValueType createValueType() {
        return new ValueType();
    }

    /**
     * Create an instance of {@link CommonExtensionBase }
     * 
     */
    public CommonExtensionBase createCommonExtensionBase() {
        return new CommonExtensionBase();
    }

    /**
     * Create an instance of {@link Include }
     * 
     */
    public Include createInclude() {
        return new Include();
    }

    /**
     * Create an instance of {@link Property }
     * 
     */
    public Property createProperty() {
        return new Property();
    }

    /**
     * Create an instance of {@link DeployableType }
     * 
     */
    public DeployableType createDeployableType() {
        return new DeployableType();
    }

    /**
     * Create an instance of {@link IntentQualifier }
     * 
     */
    public IntentQualifier createIntentQualifier() {
        return new IntentQualifier();
    }

    /**
     * Create an instance of {@link ContributionType }
     * 
     */
    public ContributionType createContributionType() {
        return new ContributionType();
    }

    /**
     * Create an instance of {@link Intent }
     * 
     */
    public Intent createIntent() {
        return new Intent();
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link CPPImport }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "import.cpp", substitutionHeadNamespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", substitutionHeadName = "importBase")
    public JAXBElement<CPPImport> createImportCpp(CPPImport value) {
        return new JAXBElement<CPPImport>(_ImportCpp_QNAME, CPPImport.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link OperationSelectorType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "operationSelector")
    public JAXBElement<OperationSelectorType> createOperationSelector(OperationSelectorType value) {
        return new JAXBElement<OperationSelectorType>(_OperationSelector_QNAME, OperationSelectorType.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link OperatorContentType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://www.w3.org/ns/ws-policy", name = "All")
    public JAXBElement<OperatorContentType> createAll(OperatorContentType value) {
        return new JAXBElement<OperatorContentType>(_All_QNAME, OperatorContentType.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ImportType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "import", substitutionHeadNamespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", substitutionHeadName = "importBase")
    public JAXBElement<ImportType> createImport(ImportType value) {
        return new JAXBElement<ImportType>(_Import_QNAME, ImportType.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ValueType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "value")
    public JAXBElement<ValueType> createValue(ValueType value) {
        return new JAXBElement<ValueType>(_Value_QNAME, ValueType.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ContributionType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "contribution")
    public JAXBElement<ContributionType> createContribution(ContributionType value) {
        return new JAXBElement<ContributionType>(_Contribution_QNAME, ContributionType.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Metadata }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "metadata")
    public JAXBElement<Metadata> createMetadata(Metadata value) {
        return new JAXBElement<Metadata>(_Metadata_QNAME, Metadata.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ImplementationType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "implementationType")
    public JAXBElement<ImplementationType> createImplementationType(ImplementationType value) {
        return new JAXBElement<ImplementationType>(_ImplementationType_QNAME, ImplementationType.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Import }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "importBase")
    public JAXBElement<Import> createImportBase(Import value) {
        return new JAXBElement<Import>(_ImportBase_QNAME, Import.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link SCAImplementation }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "implementation.composite", substitutionHeadNamespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", substitutionHeadName = "implementation")
    public JAXBElement<SCAImplementation> createImplementationComposite(SCAImplementation value) {
        return new JAXBElement<SCAImplementation>(_ImplementationComposite_QNAME, SCAImplementation.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Export }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "exportBase")
    public JAXBElement<Export> createExportBase(Export value) {
        return new JAXBElement<Export>(_ExportBase_QNAME, Export.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link TDefinitions }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "definitions")
    public JAXBElement<TDefinitions> createDefinitions(TDefinitions value) {
        return new JAXBElement<TDefinitions>(_Definitions_QNAME, TDefinitions.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Include }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "include")
    public JAXBElement<Include> createInclude(Include value) {
        return new JAXBElement<Include>(_Include_QNAME, Include.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link CPPExport }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "export.cpp", substitutionHeadNamespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", substitutionHeadName = "exportBase")
    public JAXBElement<CPPExport> createExportCpp(CPPExport value) {
        return new JAXBElement<CPPExport>(_ExportCpp_QNAME, CPPExport.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Composite }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "composite")
    public JAXBElement<Composite> createComposite(Composite value) {
        return new JAXBElement<Composite>(_Composite_QNAME, Composite.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ComponentType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "componentType")
    public JAXBElement<ComponentType> createComponentType(ComponentType value) {
        return new JAXBElement<ComponentType>(_ComponentType_QNAME, ComponentType.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link SCABinding }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "binding.sca", substitutionHeadNamespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", substitutionHeadName = "binding")
    public JAXBElement<SCABinding> createBindingSca(SCABinding value) {
        return new JAXBElement<SCABinding>(_BindingSca_QNAME, SCABinding.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Intent }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "intent")
    public JAXBElement<Intent> createIntent(Intent value) {
        return new JAXBElement<Intent>(_Intent_QNAME, Intent.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Interface }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "interface")
    public JAXBElement<Interface> createInterface(Interface value) {
        return new JAXBElement<Interface>(_Interface_QNAME, Interface.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link IPCBinding }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "binding.ipc", substitutionHeadNamespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", substitutionHeadName = "binding")
    public JAXBElement<IPCBinding> createBindingIpc(IPCBinding value) {
        return new JAXBElement<IPCBinding>(_BindingIpc_QNAME, IPCBinding.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ThriftBinding }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "binding.thrift", substitutionHeadNamespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", substitutionHeadName = "binding")
    public JAXBElement<ThriftBinding> createBindingIpc(ThriftBinding value) {
        return new JAXBElement<ThriftBinding>(_BindingThrift_QNAME, ThriftBinding.class, null, value);
    }
    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ExportType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "export", substitutionHeadNamespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", substitutionHeadName = "exportBase")
    public JAXBElement<ExportType> createExport(ExportType value) {
        return new JAXBElement<ExportType>(_Export_QNAME, ExportType.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link CPPInterface }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "interface.cpp", substitutionHeadNamespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", substitutionHeadName = "interface")
    public JAXBElement<CPPInterface> createInterfaceCpp(CPPInterface value) {
        return new JAXBElement<CPPInterface>(_InterfaceCpp_QNAME, CPPInterface.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link BindingType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "bindingType")
    public JAXBElement<BindingType> createBindingType(BindingType value) {
        return new JAXBElement<BindingType>(_BindingType_QNAME, BindingType.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link CPPImplementation }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "implementation.cpp", substitutionHeadNamespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", substitutionHeadName = "implementation")
    public JAXBElement<CPPImplementation> createImplementationCpp(CPPImplementation value) {
        return new JAXBElement<CPPImplementation>(_ImplementationCpp_QNAME, CPPImplementation.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link PolicySet }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "policySet")
    public JAXBElement<PolicySet> createPolicySet(PolicySet value) {
        return new JAXBElement<PolicySet>(_PolicySet_QNAME, PolicySet.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link WireFormatType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "wireFormat")
    public JAXBElement<WireFormatType> createWireFormat(WireFormatType value) {
        return new JAXBElement<WireFormatType>(_WireFormat_QNAME, WireFormatType.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Binding }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "binding")
    public JAXBElement<Binding> createBinding(Binding value) {
        return new JAXBElement<Binding>(_Binding_QNAME, Binding.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Callback }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "callback")
    public JAXBElement<Callback> createCallback(Callback value) {
        return new JAXBElement<Callback>(_Callback_QNAME, Callback.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Documentation }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "documentation")
    public JAXBElement<Documentation> createDocumentation(Documentation value) {
        return new JAXBElement<Documentation>(_Documentation_QNAME, Documentation.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link OperatorContentType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://www.w3.org/ns/ws-policy", name = "ExactlyOne")
    public JAXBElement<OperatorContentType> createExactlyOne(OperatorContentType value) {
        return new JAXBElement<OperatorContentType>(_ExactlyOne_QNAME, OperatorContentType.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Implementation }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "implementation")
    public JAXBElement<Implementation> createImplementation(Implementation value) {
        return new JAXBElement<Implementation>(_Implementation_QNAME, Implementation.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Qualifier }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "qualifier", scope = IntentMap.class)
    public JAXBElement<Qualifier> createIntentMapQualifier(Qualifier value) {
        return new JAXBElement<Qualifier>(_IntentMapQualifier_QNAME, Qualifier.class, IntentMap.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link IntentMap }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "intentMap", scope = PolicySet.class)
    public JAXBElement<IntentMap> createPolicySetIntentMap(IntentMap value) {
        return new JAXBElement<IntentMap>(_PolicySetIntentMap_QNAME, IntentMap.class, PolicySet.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link PolicySetReference }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", name = "policySetReference", scope = PolicySet.class)
    public JAXBElement<PolicySetReference> createPolicySetPolicySetReference(PolicySetReference value) {
        return new JAXBElement<PolicySetReference>(_PolicySetPolicySetReference_QNAME, PolicySetReference.class, PolicySet.class, value);
    }

}
