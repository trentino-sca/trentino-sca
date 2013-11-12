// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************
package org.trentino.trengen.cpp.parser.eclipse;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit;

/**
 * @author z002ttbb
 */
public class TranslationUnitCollector {

	private Map<String, IASTTranslationUnit>	translationUnits	= new HashMap<String, IASTTranslationUnit>();

	/**
	 * @param tu
	 */
	public void onTranslationUnitFound(IASTTranslationUnit tu) {
		String path;
        try
        {
	        path = new File(tu.getFilePath()).getCanonicalFile().getPath();
        } catch (IOException e)
        {
	       return;
        }
        if(path !=null && !translationUnits.containsKey(path)){
        	translationUnits.put(path, tu);
        }
        
	}

	public Map<String, IASTTranslationUnit> getTranslationUnits() {
    	return translationUnits;
    }

	/**
     * @param path
     * @return
     */
    public IASTTranslationUnit getTranslationUnit(String path) {
    	IASTTranslationUnit res = translationUnits.get(path);
	    return res;
    }


}
