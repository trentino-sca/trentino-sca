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
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElements;
import javax.xml.bind.annotation.XmlSeeAlso;
import javax.xml.bind.annotation.XmlType;
import javax.xml.namespace.QName;


/**
 * <p>Java class for Interface complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="Interface">
 *   &lt;complexContent>
 *     &lt;extension base="{http://docs.oasis-open.org/ns/opencsa/sca/200912}CommonExtensionBase">
 *       &lt;choice maxOccurs="unbounded" minOccurs="0">
 *         &lt;element ref="{http://docs.oasis-open.org/ns/opencsa/sca/200912}requires"/>
 *         &lt;element ref="{http://docs.oasis-open.org/ns/opencsa/sca/200912}policySetAttachment"/>
 *       &lt;/choice>
 *       &lt;attribute name="remotable" type="{http://www.w3.org/2001/XMLSchema}boolean" />
 *       &lt;attribute name="requires" type="{http://docs.oasis-open.org/ns/opencsa/sca/200912}listOfQNames" />
 *       &lt;attribute name="policySets" type="{http://docs.oasis-open.org/ns/opencsa/sca/200912}listOfQNames" />
 *       &lt;anyAttribute processContents='lax' namespace='##other'/>
 *     &lt;/extension>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "Interface", propOrder = {
    "requiresOrPolicySetAttachment"
})
@XmlSeeAlso({
    CPPInterface.class
})
public abstract class Interface
    extends CommonExtensionBase
{

    @XmlElements({
        @XmlElement(name = "requires", type = Requires.class),
        @XmlElement(name = "policySetAttachment", type = PolicySetAttachment.class)
    })
    protected List<Object> requiresOrPolicySetAttachment;
    @XmlAttribute
    protected Boolean remotable;
    @XmlAttribute
    protected List<QName> requires;
    @XmlAttribute
    protected List<QName> policySets;

    /**
     * Gets the value of the requiresOrPolicySetAttachment property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the requiresOrPolicySetAttachment property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getRequiresOrPolicySetAttachment().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link Requires }
     * {@link PolicySetAttachment }
     * 
     * 
     */
    public List<Object> getRequiresOrPolicySetAttachment() {
        if (requiresOrPolicySetAttachment == null) {
            requiresOrPolicySetAttachment = new ArrayList<Object>();
        }
        return this.requiresOrPolicySetAttachment;
    }

    /**
     * Gets the value of the remotable property.
     * 
     * @return
     *     possible object is
     *     {@link Boolean }
     *     
     */
    public Boolean isRemotable() {
        return remotable;
    }

    /**
     * Sets the value of the remotable property.
     * 
     * @param value
     *     allowed object is
     *     {@link Boolean }
     *     
     */
    public void setRemotable(Boolean value) {
        this.remotable = value;
    }

    /**
     * Gets the value of the requires property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the requires property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getRequires().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link QName }
     * 
     * 
     */
    public List<QName> getRequires() {
        if (requires == null) {
            requires = new ArrayList<QName>();
        }
        return this.requires;
    }

    /**
     * Gets the value of the policySets property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the policySets property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getPolicySets().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link QName }
     * 
     * 
     */
    public List<QName> getPolicySets() {
        if (policySets == null) {
            policySets = new ArrayList<QName>();
        }
        return this.policySets;
    }

}
