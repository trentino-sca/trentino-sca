package org.trentino.trengen.tools.bindingsca;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import javax.lang.model.element.TypeElement;

import org.trentino.trengen.tools.trengen.Util;

public class TIDLInterfaceModel extends TIDLNamedElement implements TIDLTypeContainer{

	private String	                qualifiedName;
	private List<TIDLFunctionModel>	functions	= new ArrayList<TIDLFunctionModel>();
	
	private TIDLTypeContainerSupport tIDLTypeContainerSupport = new TIDLTypeContainerSupport();

	public List<TIDLFunctionModel> getFunctions() {
		return functions;
	}

	public void setFunctions(List<TIDLFunctionModel> functions) {
		this.functions = functions;
	}

	private TypeElement	         typeElement;
	private TreeSet<TIDLType>	 declaredTypes;
	private Map<String, Boolean>	useType	= new HashMap<String, Boolean>();
	private Set<TIDLType> nonEnclosedClasses;

	public String getQualifiedName() {
		return qualifiedName;
	}

	public String getNamespace() {
		if(qualifiedName == null)
		{
			return null;
		}
		return qualifiedName.substring(0, qualifiedName.lastIndexOf("."));
	}

	public List<String> getNameSpacePartsUpperCase() {
		List<String> parts = getNameSpaceParts();
		List<String> partsUpperCase = new ArrayList<String>();
		for (String part : parts)
		{
			String upperPartName = "";
			for (int i = 0; i < part.length(); i++)
			{
				upperPartName += Util.toUpper(part.charAt(i));
			}
			partsUpperCase.add(upperPartName);
		}
		return partsUpperCase;
	}

	/**
	 * used in Template file
	 * @return
	 */
	public List<String> getNameSpaceParts() {
		String namespace = getNamespace();
		if(namespace == null)
		{
			return new ArrayList<String>();
		}
		String[] partsV = namespace.split("\\.");
		List<String> ret = new ArrayList<String>(Arrays.asList(partsV));
		return ret;
	}

	/**
	 * @param string
	 */
	public void setQualifiedName(String string) {
		qualifiedName = string;
	}

	/**
	 * @param elem
	 */
	public void setTypeElement(TypeElement elem) {
		this.typeElement = elem;
	}

	public TypeElement getTypeElement() {
		return typeElement;
	}




	public Boolean useType(String typeAlias) {
		if(useType.get(typeAlias) != null)
		{
			return useType.get(typeAlias);
		}
		for (TIDLFunctionModel function : functions)
		{
			// get the arguments
			for (TIDLParameterModel param : function.getArguments())
			{
				TIDLType type = param.getType();
				if(type.isType(typeAlias))
				{
					useType.put(typeAlias, Boolean.TRUE);
					return true;
				}
				else if(type.useType(typeAlias))
				{
					useType.put(typeAlias, Boolean.TRUE);
					return true;
				}

			}
			TIDLType returnType = function.getReturnType();
			if(returnType.isType(typeAlias))
			{
				useType.put(typeAlias, Boolean.TRUE);
				return true;
			}
			else if(returnType.useType(typeAlias))
			{
				useType.put(typeAlias, Boolean.TRUE);
				return true;
			}

		}
		useType.put(typeAlias, Boolean.FALSE);
		return false;
	}

	static class ClassDependenciesComparator implements Comparator<TIDLType> {

		/*
		 * (non-Javadoc)
		 * @see java.util.Comparator#compare(java.lang.Object, java.lang.Object)
		 */
		@Override
		public int compare(TIDLType t1, TIDLType t2) {
			if(t1 == t2)
			{
				return 0;
			}
			if(t1 != null && t1.equals(t2))
			{
				return 0;
			}
//			if(t1 != null && t1.getDeclaredTypes().contains(t2))
//			{
//				return 1;
//			}
//			if(t2 != null && t2.getDeclaredTypes().contains(t1))
//			{
//				return -1;
//			}
			if(t1 != null)
			{
				return t1.compareTo(t2);
			}
			return -t2.compareTo(t1);

		}
	}

	/* (non-Javadoc)
     * @see org.trentino.trengen.tools.bindingsca.TIDLTypeContainer#getEnclosedClasses()
     */
    @Override
    public Set<TIDLType> getEnclosedClasses() {
	    // TODO Auto-generated method stub
	    return tIDLTypeContainerSupport.getEnclosedClasses();
    }
    
    /* (non-Javadoc)
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        return getQualifiedName();
    }

	/**
     * @return
     */
    public boolean isUseComplexTypes() {
	    if(getEnclosedClasses().size() >0){
	    	return true;
	    }
	    for(TIDLFunctionModel f : functions){
	    	if(f.isUseComplexTypes()){
	    		return true;
	    	}
	    }
	    return false;
    }

	/**
     * @return
     */
    public Set<TIDLType> getNonEnclosedClasses() {
		if(nonEnclosedClasses == null)
		{
			String ns = getNamespace();
			nonEnclosedClasses = new TreeSet<TIDLType>(new ClassDependenciesComparator());

			for (TIDLFunctionModel function : functions)
			{
				// get the arguments
				for (TIDLParameterModel param : function.getArguments())
				{
					TIDLType type = param.getType();
					getNonEnclosedClasses(ns, type);

				}
				// get the return type
				TIDLType returnType = function.getReturnType();
				getNonEnclosedClasses(ns, returnType);
				
				// get the exceptions
				List<TIDLExceptionModel> functionExceptions = function.getExceptions();
				for (TIDLExceptionModel exc : functionExceptions)
				{
					TIDLType type = exc.getType();
					getNonEnclosedClasses(ns, type);
				}
			}
		}
		return nonEnclosedClasses;
    }

	private void getNonEnclosedClasses(String ns, TIDLType type) {
		if(!type.isComplexType()){
			return;
		}
	    if(type.isComplexType() && !nonEnclosedClasses.contains(type))
	    {
	    	if(!type.isEnclosedIn(ns)){
	        	nonEnclosedClasses.add(type);
	    	}
	
	    }
	    if(type.isEnumeration()){
	    	return;
	    }
	    for(TIDLType t : type.getEnclosedClasses()){
	    	getNonEnclosedClasses(ns,t);
	    }
	    
	    for(TIDLFieldModel field: type.getFields()){
	    	TIDLType ft = field.getType();
	    	if(ft.equals(type)){
	    		continue;
	    	}
	    	getNonEnclosedClasses(ns,ft);
	    }
    }
    
    public List<TIDLType> getAllComplexTypes(){
    	List<TIDLType> res = new ArrayList<TIDLType>();
    	for(TIDLType t : getEnclosedClasses()){
    		addToList(res, t);
    		expandAllComplexTypes(t, res);
    	}
    	for(TIDLType t : getNonEnclosedClasses()){
    		addToList(res, t);
    		expandAllComplexTypes(t, res);
    	}
    	return res;
    }

	private void addToList(List<TIDLType> res, TIDLType t) {
		if(res.contains(t)){
			return;
		}
	    res.add(t);
    }

	/**
     * @param t
     * @param res
     */
    private void expandAllComplexTypes(TIDLType aType, List<TIDLType> res) {
    	for(TIDLType t : aType.getEnclosedClasses()){
    		addToList(res, t);
    		expandAllComplexTypes(t, res);
    	}
    }
    
    /* (non-Javadoc)
     * @see java.lang.Object#equals(java.lang.Object)
     */
    @Override
    public boolean equals(Object obj) {
        if(!(obj instanceof TIDLInterfaceModel)){
        	return false;
        }
        TIDLInterfaceModel other =(TIDLInterfaceModel) obj;
        return qualifiedName.equals(other.qualifiedName);
    }

}
