// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************
package org.trentino.trengen.cpp.parser.eclipse;

import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.HeaderFile;

/**
 * @author z002ttbb
 * Utility class to get a HeaderFile object
 *
 */
public class HeaderUtil {
	
	static EclipseCPPParser eclipseCPPParser = new EclipseCPPParser(null,null);
	public static HeaderFile getHeaderFile(String path, String... include) {
		if(path == null)
		{
			return null;
		}
		EclipseCPPParser p2 = eclipseCPPParser;
		if(include!=null){
			 p2 = new EclipseCPPParser(null,include);
		}
         
		String fullpath = HeaderLoader.getFile(path);
		return p2.parse(fullpath);
	}
	
	/**
     * @param string
     * @param string2
     * @return
     */
    public static ClassMethod getMethod(HeaderFile file, String qName, String method) {
	    if(qName ==null || method ==null){
	    	return null;
	    }
//	    String namespace ="";
//	    String clazzName = null;
//	    if(qName.contains("::")){
//	    	namespace = qName.substring(0,qName.lastIndexOf("::"));
//	    	clazzName =qName.substring(qName.lastIndexOf("::"), qName.length());
//	    }
	    ClassModel found =null;
	    for(ClassModel clazz : file.getClasses()){
	    	if(clazz ==null){
	    		continue;
	    	}
	    	if(qName.equals(clazz.getFullQualifiedClassName())){
	    		found = clazz;
	    		break;
	    	}
	    }
	    if(found ==null){
	    	return null;
	    }
	    for(ClassMethod meth : found.getMethods()){
	    	if(method.equals(meth.getName())){
	    		return meth;
	    	}
	    }
	    return null;
    }

}
