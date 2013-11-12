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

import java.util.HashMap;
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
import org.trentino.trengen.tools.bindingsca.TIDLInterfaceModel;
import org.trentino.trengen.tools.bindingsca.TIDLType;

/**
 * @author z002ttbb
 */
public class ProtobufTypeMapper extends AbstractNameMapper {

	static final Map<String, String>	primitiveTypes	= new HashMap<String, String>();
	static
	{
		primitiveTypes.put(TUInt.class.getName(), "uint32");
		primitiveTypes.put(TInt.class.getName(), "int32");
		primitiveTypes.put(TLong.class.getName(), "int64");
		primitiveTypes.put(TULong.class.getName(), "uint64");
		primitiveTypes.put(TDouble.class.getName(), "double");
		primitiveTypes.put(TFloat.class.getName(), "float");
		primitiveTypes.put(TString.class.getName(), "string");
		primitiveTypes.put(TBool.class.getName(), "bool");
	}

	private TIDLInterfaceModel tidlInterfaceModel;

	/**
     * @param tidlInterfaceModel
     */
    public ProtobufTypeMapper (TIDLInterfaceModel tidlInterfaceModel) {
	   this.tidlInterfaceModel =tidlInterfaceModel; 
    }

	public String name(TIDLType type) {
		if(type.isComplexType())
		{
			return "PB_" + type.getName();
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

	private Map<String, String>	qNames	= new HashMap<String, String>();

	public String qName(TIDLType type) {
		if(type.isPrimitive()){
			return name(type);
		}
		String res = qNames.get(type.getQualifiedName());
		if(res == null)
		{
			res = doGetQName(type);
			qNames.put(type.getQualifiedName(), res);
		}
		return res;
	}

	private String doGetQName(TIDLType type) {
		String tn = "::PB_" + type.getName();
		if(!type.isEnclosed()){
			return "protobuf::" +tidlInterfaceModel.getQualifiedName().replace(".", "::")+tn;
		}
		if(type.isDirectlyEnclosedinModel())
		{
			return "protobuf::" + type.getNamespace() + tn;
		}
		// String[] parts = type.getQualifiedName().split("\\.");
		// if(parts.length == 1)
		// {
		// return "PB_" + type.getName();
		// }
		// String ns = "protobuf::";
		// for (int i = 0; i < parts.length - 2; i++)
		// {
		// ns += parts[i] + "::";
		// }
		// // ns+=parts[parts.length-1];
		//return "protobuf::" + type.getNamespace() + "::PB_" + type.getName();
		TIDLType enclosingClass = type.getEnclosingClass();
		return qName(enclosingClass) + tn;
	}

	public String enumName(TIDLFieldModel field) {

		TIDLType type = field.getType();
		if(type.isDirectlyEnclosedinModel())
		{
			return field.getName();
		}
		String res = "PB_" + type.getName() + "_" + field.getName();
		TIDLType parent = type.getEnclosingClass();
		while (parent != null)
		{
			res = "PB_" + parent.getName() + "_" + res;
			parent = parent.getEnclosingClass();
		}
		return res;
	}

	/**
	 * used for protobuf methods
	 * @param type
	 * @param pbType
	 * @param fName
	 * @return
	 */
	public String trimEnumName(TIDLType type, String pbType, String fName) {
		String ns = pbType;
		if(!type.isDirectlyEnclosedinModel())
		{
			TIDLType parent = type.getEnclosingClass();

			while (parent != null)
			{
				ns = ns.substring(0, ns.lastIndexOf("::"));
				parent = parent.getEnclosingClass();
			}
		}

		 ns = ns.substring(0, ns.lastIndexOf("::"));
		return ns + "::" + fName;
	}

	/**
	 * used for CPP interrface
	 * @param type
	 * @param pbType
	 * @param fName
	 * @return
	 */
	public String trimEnumName2(TIDLType type, String pbType, String fName) {
		String ns = pbType;
		if(type.isEnclosed())
		{
			ns = ns.substring(0, ns.lastIndexOf("::"));
		}
		return ns + "::" + fName;
	}

}
