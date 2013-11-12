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
package org.trentino.trengen.tools.bindingsca;

import javax.lang.model.element.VariableElement;

import org.trentino.tidl.Default;
import org.trentino.tidl.TBool;
import org.trentino.tidl.TString;

/**
 * @author z002ttbb
 */
public class TIDLFieldModel extends TIDLTypedElement<VariableElement> {
	
	private String defaultValueAsString ="";
	Boolean defaultValue = null;
	public boolean hasDefaultValue(){
		if(defaultValue ==null){
			TIDLType type = getType();
			if(type.isComplexType() && !type.isEnumeration()){
				defaultValue = false;
				return false;
			}
			VariableElement field = getTypeElement();
			Default def = field.getAnnotation(Default.class);
			defaultValue = true;
			if(def ==null){
				defaultValue = false;
				return false;
			}
			else if (type.isComplexType() && type.isEnumeration()){
				String dv = def.ev();
				defaultValueAsString = String.valueOf(dv);
			}
			else if(type.isNumber()){
				double nv = def.nv();
				long lv = (long) nv;
				if(lv == nv){
					defaultValueAsString = String.valueOf(lv);
				}else {
					defaultValueAsString = String.valueOf(nv);
				}
				
			}
			else if(TString.class.getName().equals(type.getQualifiedName())){
				defaultValueAsString = String.valueOf("\""+def.sv()+"\"");
			}
			else if(TBool.class.getName().equals(type.getQualifiedName())){
				defaultValueAsString = String.valueOf(def.bv());
			}
		}
		return defaultValue;
		
	}
	
	public String getDefaultValueAsString(){
		return defaultValueAsString;
	}

}
