package org.trentino.trengen.tools.scavalidation;

import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.JAXBElement;

import org.apache.log4j.Logger;
import org.trentino.trengen.sca.model.Binding;
import org.trentino.trengen.sca.model.Contract;
import org.trentino.trengen.sca.model.SCABinding;

/**
 * this class is for specifying target services for a reference 
 * @author tr1t6321
 *
 */
public class ReferenceTarget {
	protected static final Logger logger = Logger.getLogger(ReferenceTarget.class);

	private String referenceName; 
	private String parentComponentName; 
	private String parentCompositeName; 

	private List<String> targetsInTargetAttribute;
	private List<String> urisInUriAttribute;
	private List<String> otherBindingRelatedValues;
	private Boolean autoWire;
	private boolean wiredByImpl;
	private List<String> wireSources;
	private boolean hasJustDefaultBinding;
	private boolean hasSCAbinding;

	ReferenceTarget(String refName, String parentCompName, String parentcompositeName )
	{
		targetsInTargetAttribute = new ArrayList<String>();
		urisInUriAttribute = new ArrayList<String>();
		otherBindingRelatedValues =  new ArrayList<String>();
		autoWire = null;
		wiredByImpl = false;
		wireSources =  new ArrayList<String>();
		hasJustDefaultBinding = false;

		this.referenceName = refName;
		this.parentComponentName = parentCompName;
		this.parentCompositeName = parentcompositeName;
	}

	public boolean isHasJustDefaultBinding() {
		return hasJustDefaultBinding;
	}

	public void setHasJustDefaultBinding(boolean hasJustDefaultBinding) {
		this.hasJustDefaultBinding = hasJustDefaultBinding;
	}

	public boolean isHasSCAbinding() {
		return hasSCAbinding;
	}

	public void setSCAbinding(boolean hasSCAbinding) {
		this.hasSCAbinding = hasSCAbinding;
	}

	public List<String> getTargetsInTargetAttribute() {
		return targetsInTargetAttribute;
	}

	public void setTargetsInTargetAttribute(
			List<String> targetsInTargetAttribute) {
		this.targetsInTargetAttribute = targetsInTargetAttribute;
	}

	public List<String> getUrisInUriAttribute() {
		return urisInUriAttribute;
	}

	public void setUrisInUriAttribute(List<String> urisInUriAttribute) {
		this.urisInUriAttribute = urisInUriAttribute;
	}

	public List<String> getOtherBindingRelatedValues() {
		return otherBindingRelatedValues;
	}

	public void setOtherBindingRelatedValues(List<String> otherBindingRelatedValues) {
		this.otherBindingRelatedValues = otherBindingRelatedValues;
	}

	public Boolean isAutoWire() {
		return autoWire;
	}

	public void setAutoWire(Boolean autoWire) {
		this.autoWire = autoWire;
	}

	public boolean isWiredByImpl() {
		return wiredByImpl;
	}

	public void setWiredByImpl(boolean wiredByImpl) {
		this.wiredByImpl = wiredByImpl;
	}

	public List<String> getWireSources() {
		return wireSources;
	}

	public void setWireSources(List<String> wireSources) {
		this.wireSources = wireSources;
	}

	/**
	 * 
	 * According to ASM40006 and ASM50013; if @wiredByImpl is true, other targets should not be counted.
	 * Else if @autowire is set to true, other targets should not be counted...
	 */
	public int returnNumberOfTargets(Contract r)
	{
		int count = 0;
		if (this.wiredByImpl== true)
			count +=1; // target is defined is @wiredByOmpl
		else if (this.autoWire!= null && this.autoWire.booleanValue() == true)
			count +=1; // target is defined in @autoWire
		else
		{
			count += this.urisInUriAttribute.size(); // targets in the @uri of bindings
			count += this.otherBindingRelatedValues.size(); // targets in the other binding-related attributes. NOT SUPPORTED YET
			// targets in the @target of references
			count += this.targetsInTargetAttribute.size();
			count += this.wireSources.size(); // targets in the @target of wires
			if (count==0)
			{
				hasSCAbinding = true;
				count += 1;
		
				/*
				 * In order to handle default binding.sca without uri (for service discovery), we added this
				 * fake target.
				 * TODO: Instead we could change the binding code to survive without uri.
				 * We did not want to disturb the whole binding code structure.
				 */
				List<JAXBElement<? extends Binding>> bindings = r.getBinding();
				if (bindings.size()==1)
				{
					if(bindings.get(0).getValue() instanceof SCABinding  )
					{
						SCABinding scaBinding = (SCABinding)bindings.get(0).getValue();
						if (scaBinding.getUri() == null)
							scaBinding.setUri("tcp://localhost:1234//dontUseThisName_FakeTarget");
							
					}
				}	
			}
		
			if (count==1 && hasSCAbinding)
				hasJustDefaultBinding = true;
		}			
		return count;
	}
	
	public void printMsg ()
	{
		boolean autoWireStr = this.autoWire==null ? false : this.autoWire;
		String targetsInTargetAttributeStr = "";
		for (String target : this.targetsInTargetAttribute )
		{
			targetsInTargetAttributeStr += target + " , ";
		}
		String urisInUriAttributeStr = "";
		for (String target : this.urisInUriAttribute )
		{
			urisInUriAttributeStr += target + " , ";
		}
		String wireSourcesStr = "";
		for (String target : this.wireSources )
		{
			wireSourcesStr += target + " , ";
		}

		String message= "Here are the defined targets for this reference:" +
				"\n@wiredByImpl attribute       = " + this.wiredByImpl + " , "+
				"\n@autoWire attribute          = " + autoWireStr + " , "+
				"\ntargets in @target attribute = " + targetsInTargetAttributeStr +
				"\nuri's in @uri attribute      = " + urisInUriAttributeStr +
				"\n@source attribute in wire    = " + wireSourcesStr+"\n";
		logger.error(message);
	}

	static public boolean isInList (String variable, List<String> varList)
	{
		for(int i=0;  i<varList.size(); i++)
		{
			if(varList.get(i).equals(variable))
				return true;
		}
		return false;
	}

	private void checkAllExceptWiredByImplAndAutoWire(boolean isWiredByImpl, Boolean isAutowire)
	{
		if (targetsInTargetAttribute.size()>0) 
		{
			logger.warn(isWiredByImpl==true ?ConformanceManagerConstants.CI_ASM40006_VIOLATED :ConformanceManagerConstants.CI_ASM50014_VIOLATED
					+ " for reference:"
					+ referenceName
					+ " in "
					+ parentComponentName
					+ "@"
					+ parentCompositeName
					+ ". Target attribute is specified even though its wiredByImpl is true.");
		}
		if (urisInUriAttribute.size()>0) 
		{
			logger.warn(isWiredByImpl==true ?ConformanceManagerConstants.CI_ASM40006_VIOLATED :ConformanceManagerConstants.CI_ASM50014_VIOLATED
					+ " for reference:"
					+ referenceName
					+ " in "
					+ parentComponentName
					+ "@"
					+ parentCompositeName
					+ ". Uri attribute is specified even though its wiredByImpl is true.");
		}

		if (otherBindingRelatedValues.size()>0) 
		{
			logger.warn(isWiredByImpl==true ?ConformanceManagerConstants.CI_ASM40006_VIOLATED :ConformanceManagerConstants.CI_ASM50014_VIOLATED
					+ " for reference:"
					+ referenceName
					+ " in "
					+ parentComponentName
					+ "@"
					+ parentCompositeName
					+ ". Binding attributes are specified even though its wiredByImpl is true.");
		}

		if (wireSources.size()>0) 
		{
			logger.warn(isWiredByImpl==true ?ConformanceManagerConstants.CI_ASM40006_VIOLATED :ConformanceManagerConstants.CI_ASM50014_VIOLATED
					+ " for reference:"
					+ referenceName
					+ " in "
					+ parentComponentName
					+ "@"
					+ parentCompositeName
					+ ". It defined as source in a wire even though its wiredByImpl is true.");
		}
	}

	/**
	 * [ASM40006] If wiredByImpl is set to "true.", then any reference targets
	 * configured for this reference MUST be ignored by the runtime. Please
	 * refer to SCA-Spec1.1 - section 4.3.1 Specifying the Target Service(s) for
	 * a Reference
	 * 
	 * [ASM50013] If wiredByImpl="true.", other methods of specifying the target
	 * service MUST NOT be used.
	 * 
	 * [ASM50010] If wiredByImpl="true." is set for a reference, then the
	 * reference MUST NOT be wired statically within a composite, but left
	 * unwired. Please refer to SCA-Spec1.1 - section 4.3.1 Specifying the
	 * Target Service(s) for a Reference
	 * 
	 * [ASM50014] If autowire="true.", the autowire procedure MUST only be used
	 * if no target is identified by any of the other ways listed above. It is
	 * not an error if autowire="true." and a target is also defined through
	 * some other means, however in this case the autowire procedure MUST NOT be
	 * used.
	 */
	public void check_ASM50010_ASM50014_ASM40006_ASM50013() 
	{
		if (this.isWiredByImpl()) 
		{
			if ((this.isAutoWire() != null) && this.isAutoWire()) 
			{
				logger.warn(ConformanceManagerConstants.CI_ASM50013_VIOLATED
						+ " for reference:"
						+ referenceName
						+ " in "
						+ parentComponentName
						+ "@"
						+ parentCompositeName
						+ ". Target attribute is specified even though its autowire is true.");
			}
			checkAllExceptWiredByImplAndAutoWire(true, null);

		} else 
		{
			if ((this.isAutoWire() != null) && this.isAutoWire()) 
			{
				checkAllExceptWiredByImplAndAutoWire(false, true);
			}
		}
	}

	// The composite reference element has the child elements, whatever is not specified is
	//defaulted from the promoted component reference(s).
	/**
	 * 
	 * @param refTarget : referenceTarget object of composite reference
	 * @param refTargetObjSmall: referenceTarget object of promoted reference
	 */
	static public void returnReferenceTargetAfterPromotion (ReferenceTarget refTarget, ReferenceTarget refTargetObjSmall)
	{
		for (int i=0; i<refTargetObjSmall.getTargetsInTargetAttribute().size(); i++)
		{
			if (!ReferenceTarget.isInList(refTargetObjSmall.getTargetsInTargetAttribute().get(i), refTarget.getTargetsInTargetAttribute()))
				refTarget.getTargetsInTargetAttribute().add(refTargetObjSmall.getTargetsInTargetAttribute().get(i));						
		}
		for (int i=0; i<refTargetObjSmall.getUrisInUriAttribute().size(); i++)
		{
			if (!ReferenceTarget.isInList(refTargetObjSmall.getUrisInUriAttribute().get(i), refTarget.getUrisInUriAttribute()))
				refTarget.getUrisInUriAttribute().add(refTargetObjSmall.getUrisInUriAttribute().get(i));						
		}
		for (int i=0; i<refTargetObjSmall.getOtherBindingRelatedValues().size(); i++)
		{
			if (!ReferenceTarget.isInList(refTargetObjSmall.getOtherBindingRelatedValues().get(i), refTarget.getOtherBindingRelatedValues()))
				refTarget.getOtherBindingRelatedValues().add(refTargetObjSmall.getOtherBindingRelatedValues().get(i));						
		}
		for (int i=0; i<refTargetObjSmall.getWireSources().size(); i++)
		{
			if (!ReferenceTarget.isInList(refTargetObjSmall.getWireSources().get(i), refTarget.getWireSources()))
				refTarget.getWireSources().add(refTargetObjSmall.getWireSources().get(i));						
		}
		if (refTarget.isAutoWire()==null)
		{
			if(refTargetObjSmall.isAutoWire()!=null)
				refTarget.setAutoWire(refTargetObjSmall.isAutoWire());
			else
				refTarget.setAutoWire(false);
		}
	}
	/**
	 * 
	 * @param refTargetObjComponent : ReferenceTarget object which is inheriting from the second ReferenceTarget object
	 * @param refTargetObjComponentType : base ReferenceTarget object which is inherited by 1st param.
	 */
	public static void importTargetsFromCorrespondingComponentTypeReference(
			ReferenceTarget refTargetObjComponent,
			ReferenceTarget refTargetObjComponentType) {
		if (refTargetObjComponent.getTargetsInTargetAttribute().size()==0)
		{
			for (int i=0; i<refTargetObjComponentType.getTargetsInTargetAttribute().size(); i++)
			{
				if (!ReferenceTarget.isInList(refTargetObjComponentType.getTargetsInTargetAttribute().get(i), refTargetObjComponent.getTargetsInTargetAttribute()))
					refTargetObjComponent.getTargetsInTargetAttribute().add(refTargetObjComponentType.getTargetsInTargetAttribute().get(i));						
			}
		}
		if (refTargetObjComponent.getUrisInUriAttribute().size()==0)
		{
			for (int i=0; i<refTargetObjComponentType.getUrisInUriAttribute().size(); i++)
			{
				if (!ReferenceTarget.isInList(refTargetObjComponentType.getUrisInUriAttribute().get(i), refTargetObjComponent.getUrisInUriAttribute()))
					refTargetObjComponent.getUrisInUriAttribute().add(refTargetObjComponentType.getUrisInUriAttribute().get(i));						
			}
		}
		if (refTargetObjComponent.getOtherBindingRelatedValues().size()==0)
		{
			for (int i=0; i<refTargetObjComponentType.getOtherBindingRelatedValues().size(); i++)
			{
				if (!ReferenceTarget.isInList(refTargetObjComponentType.getOtherBindingRelatedValues().get(i), refTargetObjComponent.getOtherBindingRelatedValues()))
					refTargetObjComponent.getOtherBindingRelatedValues().add(refTargetObjComponentType.getOtherBindingRelatedValues().get(i));						
			}
		}		
		if (refTargetObjComponent.isAutoWire()==null)
		{
			if(refTargetObjComponentType.isAutoWire()!=null)
				refTargetObjComponent.setAutoWire(refTargetObjComponentType.isAutoWire());
			else
				refTargetObjComponent.setAutoWire(false);
		}

	}

}
