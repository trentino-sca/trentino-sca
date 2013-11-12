//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, vJAXB 2.1.10 in JDK 6 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2012.10.20 at 11:07:21 AM MESZ 
//


package org.trentino.trengen.sca.model;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlElements;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ComponentType complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ComponentType">
 *   &lt;complexContent>
 *     &lt;extension base="{http://docs.oasis-open.org/ns/opencsa/sca/200912}CommonExtensionBase">
 *       &lt;sequence>
 *         &lt;element ref="{http://docs.oasis-open.org/ns/opencsa/sca/200912}implementation" minOccurs="0"/>
 *         &lt;choice maxOccurs="unbounded" minOccurs="0">
 *           &lt;element name="service" type="{http://docs.oasis-open.org/ns/opencsa/sca/200912}ComponentService"/>
 *           &lt;element name="reference" type="{http://docs.oasis-open.org/ns/opencsa/sca/200912}ComponentTypeReference"/>
 *           &lt;element name="property" type="{http://docs.oasis-open.org/ns/opencsa/sca/200912}Property"/>
 *         &lt;/choice>
 *         &lt;element ref="{http://docs.oasis-open.org/ns/opencsa/sca/200912}extensions" minOccurs="0"/>
 *       &lt;/sequence>
 *       &lt;anyAttribute processContents='lax' namespace='##other'/>
 *     &lt;/extension>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ComponentType", propOrder = {
    "implementation",
    "serviceOrReferenceOrProperty",
    "extensions"
})
public class ComponentType
    extends CommonExtensionBase
{

    @XmlElementRef(name = "implementation", namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", type = JAXBElement.class)
    protected JAXBElement<? extends Implementation> implementation;
    @XmlElements({
        @XmlElement(name = "property", type = Property.class),
        @XmlElement(name = "service", type = ComponentService.class),
        @XmlElement(name = "reference", type = ComponentTypeReference.class)
    })
    protected List<Object> serviceOrReferenceOrProperty;
    protected Extensions extensions;

    /**
     * Gets the value of the implementation property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link SCAImplementation }{@code >}
     *     {@link JAXBElement }{@code <}{@link Implementation }{@code >}
     *     {@link JAXBElement }{@code <}{@link CPPImplementation }{@code >}
     *     
     */
    public JAXBElement<? extends Implementation> getImplementation() {
        return implementation;
    }

    /**
     * Sets the value of the implementation property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link SCAImplementation }{@code >}
     *     {@link JAXBElement }{@code <}{@link Implementation }{@code >}
     *     {@link JAXBElement }{@code <}{@link CPPImplementation }{@code >}
     *     
     */
    public void setImplementation(JAXBElement<? extends Implementation> value) {
        this.implementation = ((JAXBElement<? extends Implementation> ) value);
    }

    /**
     * Gets the value of the serviceOrReferenceOrProperty property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the serviceOrReferenceOrProperty property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getServiceOrReferenceOrProperty().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link Property }
     * {@link ComponentService }
     * {@link ComponentTypeReference }
     * 
     * 
     */
    public List<Object> getServiceOrReferenceOrProperty() {
        if (serviceOrReferenceOrProperty == null) {
            serviceOrReferenceOrProperty = new ArrayList<Object>();
        }
        return this.serviceOrReferenceOrProperty;
    }

    /**
     * Gets the value of the extensions property.
     * 
     * @return
     *     possible object is
     *     {@link Extensions }
     *     
     */
    public Extensions getExtensions() {
        return extensions;
    }

    /**
     * Sets the value of the extensions property.
     * 
     * @param value
     *     allowed object is
     *     {@link Extensions }
     *     
     */
    public void setExtensions(Extensions value) {
        this.extensions = value;
    }

}