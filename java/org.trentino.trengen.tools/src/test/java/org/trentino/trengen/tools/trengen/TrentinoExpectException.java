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
package org.trentino.trengen.tools.trengen;

import java.lang.reflect.InvocationTargetException;

import org.junit.internal.runners.statements.ExpectException;
import org.junit.runners.model.Statement;

/**
 * @author z002ttbb
 *
 */
public class TrentinoExpectException extends Statement{

	private Statement fNext;
	private final Class<? extends Throwable> fExpected;
	
	public TrentinoExpectException(Statement next, Class<? extends Throwable> expected) {
		fNext= next;
		fExpected= expected;
	}
	
	@Override
	public void evaluate() throws Exception {
		boolean complete = false;
		try {
			doEvaluate();
			complete = true;
		} catch (Throwable e) {
			if (!fExpected.isAssignableFrom(e.getClass())) {
				String message= "Unexpected exception, expected<"
							+ fExpected.getName() + "> but was<"
							+ e.getClass().getName() + ">";
				throw new Exception(message, e);
			}
		}
		if (complete)
			throw new AssertionError("Expected exception: "
					+ fExpected.getName());
	}

	private void doEvaluate() throws Throwable {
		try
		{
		    fNext.evaluate();
		} catch (InvocationTargetException e)
		{

			Throwable target = e.getTargetException();
			if(target == null)
			{
				throw e;
			}
			Throwable lastTarget = target;
			while (target != null && (target instanceof InvocationTargetException))
			{
				lastTarget = target;
				target = ((InvocationTargetException) target).getTargetException();
				if(target == lastTarget)
				{
					break;
				}
				if(target == null)
				{
					target = lastTarget;
					break;
				}
			}
			throw target;
		}

    }

}
