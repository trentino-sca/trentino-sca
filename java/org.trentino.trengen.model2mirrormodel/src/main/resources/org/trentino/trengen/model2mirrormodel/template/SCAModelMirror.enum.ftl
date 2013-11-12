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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
// **********************************************************************************

package ${packageName};
<#assign className = classInfo.name>

import java.util.Map;
import java.util.HashMap;
import org.trentino.trengen.xml.schema.MirrorClass;
import org.trentino.trengen.xml.schema.MirrorField;
import java.util.List;
import org.trentino.trengen.xml.schema.AnyURI;
import org.trentino.trengen.xml.schema.NCName;
import org.trentino.trengen.xml.schema.Name;
import java.lang.reflect.Field;
import java.util.ArrayList;


public class ${className} implements MirrorClass{

	public static enum Enum {
	<#foreach fieldInfo in classInfo.fieldInfos>
	         ${fieldInfo.name?cap_first},
	</#foreach>
	
	}
	
	public Enum mValue;
	public  void setValue(String valueStr)
	{
		mValue = mValueMap.get(valueStr);
    }
    
	public static Map<String,Enum> mValueMap;
	
	static {
	 	mValueMap = createValueMap();
	}
	
	public ${className} (String valueStr){
	   	mValue = mValueMap.get(valueStr);
	}
	
	public static Map<String,Enum> createValueMap(){
	Map<String, Enum> valueMap = new HashMap<String,Enum>();
	<#foreach fieldInfo in classInfo.fieldInfos>
	   valueMap.put("${fieldInfo.name}", Enum.${fieldInfo.name?cap_first});
	</#foreach>
	   return valueMap;
	}
	
	public String mNameGen = "deneme";
	public void setNameGen(String nameGenToSet)
	{
		mNameGen =nameGenToSet;
	}
	public String getNameGen()
	{
		return mNameGen;
	}
	
	public Enum value(){
	  return mValue;
	}
	
	public String getClassName(){
	 return "${className}";
	}
	public List<MirrorField> fields=new ArrayList<MirrorField>();
	
    	@Override
	public List<MirrorField> getFields() {
			MirrorField mfield = new MirrorField();
    		mfield.setSimple(true);
    		mfield.setValue(mValue.toString());
    		mfield.setArgument("mValue");
    		fields.add(mfield);
		return fields;
	}
	
	public String getName() 
	{
	   return "enumName";
	}
		
	private boolean isSimple(Field field) {
		//System.out.println("isSimpleHere1");
		Class<?> fType = field.getType();
		//System.out.println("isSimpleHere2");
		if (fType.isPrimitive()) {
			//System.out.println("isSimpleHere3");
			return true;
		}
		//System.out.println("isSimpleHere4");
		Class[] simpleClasses = { String.class, AnyURI.class, Name.class,
				NCName.class };

		//System.out.println("isSimpleHere5");
		for (Class simple : simpleClasses) {
			if (simple.equals(fType)) {
				return true;
			}
		}
		//System.out.println("isSimpleHere6");
		return false;
	}
	
   public java.lang.Object getFieldValue(Field field) {
		try {
			return field.get(this);
		} catch (Exception e) {
			throw new IllegalStateException(e);
		}
	}
} 