//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, vJAXB 2.1.10 in JDK 6 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2012.10.20 at 11:07:21 AM MESZ 
//


package org.trentino.trengen.sca.model;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlSeeAlso;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ComponentReference complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ComponentReference">
 *   &lt;complexContent>
 *     &lt;extension base="{http://docs.oasis-open.org/ns/opencsa/sca/200912}Contract">
 *       &lt;attribute name="autowire" type="{http://www.w3.org/2001/XMLSchema}boolean" />
 *       &lt;attribute name="target" type="{http://docs.oasis-open.org/ns/opencsa/sca/200912}listOfAnyURIs" />
 *       &lt;attribute name="wiredByImpl" type="{http://www.w3.org/2001/XMLSchema}boolean" default="false" />
 *       &lt;attribute name="multiplicity" type="{http://docs.oasis-open.org/ns/opencsa/sca/200912}Multiplicity" default="1..1" />
 *       &lt;attribute name="nonOverridable" type="{http://www.w3.org/2001/XMLSchema}boolean" default="false" />
 *       &lt;anyAttribute processContents='lax' namespace='##other'/>
 *     &lt;/extension>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ComponentReference")
@XmlSeeAlso({
    ComponentTypeReference.class
})
public class ComponentReference
    extends Contract
{

    @XmlAttribute
    protected Boolean autowire;
    @XmlAttribute
    protected List<String> target;
    @XmlAttribute
    protected Boolean wiredByImpl;
    @XmlAttribute
    protected String multiplicity;
    @XmlAttribute
    protected Boolean nonOverridable;

    /**
     * Gets the value of the autowire property.
     * 
     * @return
     *     possible object is
     *     {@link Boolean }
     *     
     */
    public Boolean isAutowire() {
        return autowire;
    }

    /**
     * Sets the value of the autowire property.
     * 
     * @param value
     *     allowed object is
     *     {@link Boolean }
     *     
     */
    public void setAutowire(Boolean value) {
        this.autowire = value;
    }

    /**
     * Gets the value of the target property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the target property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getTarget().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link String }
     * 
     * 
     */
    public List<String> getTarget() {
        if (target == null) {
            target = new ArrayList<String>();
        }
        return this.target;
    }

    /**
     * Gets the value of the wiredByImpl property.
     * 
     * @return
     *     possible object is
     *     {@link Boolean }
     *     
     */
    public boolean isWiredByImpl() {
        if (wiredByImpl == null) {
            return false;
        } else {
            return wiredByImpl;
        }
    }

    /**
     * Sets the value of the wiredByImpl property.
     * 
     * @param value
     *     allowed object is
     *     {@link Boolean }
     *     
     */
    public void setWiredByImpl(Boolean value) {
        this.wiredByImpl = value;
    }

    /**
     * Gets the value of the multiplicity property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getMultiplicity() {
        if (multiplicity == null) {
            return "1..1";
        } else {
            return multiplicity;
        }
    }

    /**
     * Sets the value of the multiplicity property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setMultiplicity(String value) {
        this.multiplicity = value;
    }

    /**
     * Gets the value of the nonOverridable property.
     * 
     * @return
     *     possible object is
     *     {@link Boolean }
     *     
     */
    public boolean isNonOverridable() {
        if (nonOverridable == null) {
            return false;
        } else {
            return nonOverridable;
        }
    }

    /**
     * Sets the value of the nonOverridable property.
     * 
     * @param value
     *     allowed object is
     *     {@link Boolean }
     *     
     */
    public void setNonOverridable(Boolean value) {
        this.nonOverridable = value;
    }

}
