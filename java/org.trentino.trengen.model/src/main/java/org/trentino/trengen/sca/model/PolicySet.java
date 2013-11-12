//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, vJAXB 2.1.10 in JDK 6 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2013.07.04 at 11:39:49 AM MESZ 
//


package org.trentino.trengen.sca.model;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAnyAttribute;
import javax.xml.bind.annotation.XmlAnyElement;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlElementRefs;
import javax.xml.bind.annotation.XmlSchemaType;
import javax.xml.bind.annotation.XmlType;
import javax.xml.bind.annotation.adapters.CollapsedStringAdapter;
import javax.xml.bind.annotation.adapters.XmlJavaTypeAdapter;
import javax.xml.namespace.QName;
import org.w3c.dom.Element;


/**
 * <p>Java class for PolicySet complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="PolicySet">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;choice maxOccurs="unbounded" minOccurs="0">
 *         &lt;element name="policySetReference" type="{http://docs.oasis-open.org/ns/opencsa/sca/200912}PolicySetReference"/>
 *         &lt;element name="intentMap" type="{http://docs.oasis-open.org/ns/opencsa/sca/200912}IntentMap"/>
 *         &lt;any processContents='lax' namespace='##other'/>
 *       &lt;/choice>
 *       &lt;attribute name="name" use="required" type="{http://www.w3.org/2001/XMLSchema}NCName" />
 *       &lt;attribute name="provides" type="{http://docs.oasis-open.org/ns/opencsa/sca/200912}listOfQNames" />
 *       &lt;attribute name="appliesTo" type="{http://www.w3.org/2001/XMLSchema}string" />
 *       &lt;attribute name="attachTo" type="{http://www.w3.org/2001/XMLSchema}string" />
 *       &lt;anyAttribute processContents='lax' namespace='##other'/>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "PolicySet", propOrder = {
    "policySetReferenceOrIntentMapOrAny"
})
public class PolicySet {

    @XmlElementRefs({
        @XmlElementRef(name = "intentMap", namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", type = JAXBElement.class),
        @XmlElementRef(name = "policySetReference", namespace = "http://docs.oasis-open.org/ns/opencsa/sca/200912", type = JAXBElement.class)
    })
    @XmlAnyElement(lax = true)
    protected List<Object> policySetReferenceOrIntentMapOrAny;
    @XmlAttribute(required = true)
    @XmlJavaTypeAdapter(CollapsedStringAdapter.class)
    @XmlSchemaType(name = "NCName")
    protected String name;
    @XmlAttribute
    protected List<QName> provides;
    @XmlAttribute
    protected String appliesTo;
    @XmlAttribute
    protected String attachTo;
    @XmlAnyAttribute
    private Map<QName, String> otherAttributes = new HashMap<QName, String>();

    /**
     * Gets the value of the policySetReferenceOrIntentMapOrAny property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the policySetReferenceOrIntentMapOrAny property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getPolicySetReferenceOrIntentMapOrAny().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link JAXBElement }{@code <}{@link IntentMap }{@code >}
     * {@link JAXBElement }{@code <}{@link PolicySetReference }{@code >}
     * {@link Object }
     * {@link Element }
     * 
     * 
     */
    public List<Object> getPolicySetReferenceOrIntentMapOrAny() {
        if (policySetReferenceOrIntentMapOrAny == null) {
            policySetReferenceOrIntentMapOrAny = new ArrayList<Object>();
        }
        return this.policySetReferenceOrIntentMapOrAny;
    }

    /**
     * Gets the value of the name property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getName() {
        return name;
    }

    /**
     * Sets the value of the name property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setName(String value) {
        this.name = value;
    }

    /**
     * Gets the value of the provides property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the provides property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getProvides().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link QName }
     * 
     * 
     */
    public List<QName> getProvides() {
        if (provides == null) {
            provides = new ArrayList<QName>();
        }
        return this.provides;
    }

    /**
     * Gets the value of the appliesTo property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getAppliesTo() {
        return appliesTo;
    }

    /**
     * Sets the value of the appliesTo property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setAppliesTo(String value) {
        this.appliesTo = value;
    }

    /**
     * Gets the value of the attachTo property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getAttachTo() {
        return attachTo;
    }

    /**
     * Sets the value of the attachTo property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setAttachTo(String value) {
        this.attachTo = value;
    }

    /**
     * Gets a map that contains attributes that aren't bound to any typed property on this class.
     * 
     * <p>
     * the map is keyed by the name of the attribute and 
     * the value is the string value of the attribute.
     * 
     * the map returned by this method is live, and you can add new attribute
     * by updating the map directly. Because of this design, there's no setter.
     * 
     * 
     * @return
     *     always non-null
     */
    public Map<QName, String> getOtherAttributes() {
        return otherAttributes;
    }

}
