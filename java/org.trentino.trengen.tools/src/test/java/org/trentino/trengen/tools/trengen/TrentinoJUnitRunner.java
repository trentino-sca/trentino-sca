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
package org.trentino.trengen.tools.trengen;

import java.lang.reflect.InvocationTargetException;

import org.junit.Ignore;
import org.junit.Test;
import org.junit.Test.None;
import org.junit.internal.AssumptionViolatedException;
import org.junit.internal.runners.model.EachTestNotifier;
import org.junit.internal.runners.statements.ExpectException;
import org.junit.runner.Description;
import org.junit.runner.notification.RunNotifier;
import org.junit.runners.BlockJUnit4ClassRunner;
import org.junit.runners.model.FrameworkMethod;
import org.junit.runners.model.InitializationError;
import org.junit.runners.model.Statement;

/**
 * @author z002ttbb
 */
public class TrentinoJUnitRunner extends BlockJUnit4ClassRunner {

	/**
     * @param klass
     * @throws InitializationError
     */
    public TrentinoJUnitRunner (Class<?> klass) throws InitializationError {
	    super(klass);
    }

	@Override
	protected void runChild(FrameworkMethod method, RunNotifier notifier) {
		EachTestNotifier eachNotifier = makeNotifier(method, notifier);
		if(method.getAnnotation(Ignore.class) != null)
		{
			eachNotifier.fireTestIgnored();
			return;
		}

		eachNotifier.fireTestStarted();
		try
		{
			doEvaluate(method);
		} catch (AssumptionViolatedException e)
		{
			eachNotifier.addFailedAssumption(e);
		} catch (Throwable e)
		{
			eachNotifier.addFailure(e);
		} finally
		{
			eachNotifier.fireTestFinished();
		}
	}

	private void doEvaluate(FrameworkMethod method) throws Throwable {
		try
		{
			methodBlock(method).evaluate();
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

	private EachTestNotifier makeNotifier(FrameworkMethod method, RunNotifier notifier) {
		Description description = describeChild(method);
		return new EachTestNotifier(notifier, description);
	}
	
	protected Statement possiblyExpectingExceptions(FrameworkMethod method,
			Object test, Statement next) {
		Test annotation= method.getAnnotation(Test.class);
		return expectsException(annotation) ? new TrentinoExpectException(next,
				getExpectedException(annotation)) : next;
	}
	
	private boolean expectsException(Test annotation) {
		return getExpectedException(annotation) != null;
	}
	
	private Class<? extends Throwable> getExpectedException(Test annotation) {
		if (annotation == null || annotation.expected() == None.class)
			return null;
		else
			return annotation.expected();
	}
}
