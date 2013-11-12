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
package org.trentino.trengen.tools.generation.bindingsca;

// import java.awt.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.trentino.tidl.TBool;
import org.trentino.tidl.TDouble;
import org.trentino.tidl.TFloat;
import org.trentino.tidl.TInt;
import org.trentino.tidl.TLong;
import org.trentino.tidl.TString;
import org.trentino.tidl.TUInt;
import org.trentino.tidl.TULong;
import org.trentino.trengen.tools.bindingsca.TIDLFieldModel;
import org.trentino.trengen.tools.bindingsca.TIDLType;

/**
 * @author z002ttbb
 */
public class CppTypeMapper extends AbstractNameMapper {

	static final Map<String, String>	primitiveTypes	= new HashMap<String, String>();

	// this list keeps the list of all cpp primitive types
	static final List<String>	     cppPrimitiveTypes	= new ArrayList<String>();

	static
	{
		primitiveTypes.put(TUInt.class.getName(), "tuint32_t"); // in order not
		                                                        // to be
		                                                        // connected to
		                                                        // boost, we
		                                                        // changed it.
		                                                        // it was
		                                                        // "boost::uint32_t"
		primitiveTypes.put(TInt.class.getName(), "tint32_t");
		primitiveTypes.put(TLong.class.getName(), "tint64_t");
		primitiveTypes.put(TULong.class.getName(), "tuint64_t");
		primitiveTypes.put(TDouble.class.getName(), "double");
		primitiveTypes.put(TFloat.class.getName(), "float");
		primitiveTypes.put(TString.class.getName(), "std::string");
		primitiveTypes.put(TBool.class.getName(), "bool");

		cppPrimitiveTypes.add("tuint32_t");
		cppPrimitiveTypes.add("tint32_t");
		cppPrimitiveTypes.add("tint64_t");
		cppPrimitiveTypes.add("tuint64_t");
		cppPrimitiveTypes.add("double");
		cppPrimitiveTypes.add("float");
		cppPrimitiveTypes.add("std::string");
		cppPrimitiveTypes.add("bool");
		cppPrimitiveTypes.add("void");
	}

	public String name(TIDLType type) {
		if(type.isComplexType())
		{
			// work around
			return type.getNamespace()+"::"+ type.getTypeElement().getSimpleName().toString();
		}
		if(type.isVoid())
		{
			return "void";
		}
		if(type.isPrimitive())
		{
			String value = primitiveTypes.get(type.getQualifiedName());
			return value;
		}
		throw new IllegalArgumentException("Cannot map type" + type);
	}

	public boolean isPrimitive(TIDLType type) {
		return type.isPrimitive();
	}

	public boolean isComplexType(TIDLType type) {
		return type.isComplexType();
	}

	public boolean isCppPrimitive(String type) {
		return cppPrimitiveTypes.contains(type);
	}
	
	public String defaultValue(TIDLFieldModel model){
		TIDLType type = model.getType();
		if(TString.class.getName().equals(type.getQualifiedName())){
			return String.format("std::string (%s)",model.getDefaultValueAsString());
		}
		return model.getDefaultValueAsString();
	}

}
