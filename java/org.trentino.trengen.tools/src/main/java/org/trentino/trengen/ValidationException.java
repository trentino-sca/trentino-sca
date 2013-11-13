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
package org.trentino.trengen;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;

/**
 * @author z002ttbb
 */
public class ValidationException extends IllegalStateException {

	/**
     * 
     */
	private static final long	    serialVersionUID	= 1L;
	private String	                conformanceItem;
	private Deque<Object>	        entityQueue	     = new LinkedList<Object>();
	private Object	                contributionTypeWrapper;
	List<String>	                messages	     = new ArrayList<String>();
	Collection<ValidationException>	exceptions	     = new ArrayList<ValidationException>();

	/**
	 * @param string
	 */
	public ValidationException (String message) {
		super();
		getMessages().add(message);
	}

	public ValidationException (String message, Object... objects) {
		this(message);
		if(objects == null)
		{
			return;
		}
		for (Object obj : objects)
		{
			setLastEntity(obj);
		}
	}

	/**
     * 
     */
	public ValidationException () {
		super();
	}

	/**
	 * @param exp
	 */
	public ValidationException(Exception exp) {
		super(exp);
	}

	public String getConformanceItem() {
		return conformanceItem;
	}

	public void setConformanceItem(String conformanceItem) {
		this.conformanceItem = conformanceItem;
	}

	/**
	 * @param reference
	 */
	public void setLastEntity(Object reference) {
		if(!entityQueue.contains(reference))
		{
			entityQueue.offer(reference);
		}
	}

	public Deque<Object> getEntityQueue() {
		return entityQueue;
	}

	public Object getContributionTypeWrapper() {
		return contributionTypeWrapper;
	}

	public void setContributionTypeWrapper(Object contributionTypeWrapper) {
		this.contributionTypeWrapper = contributionTypeWrapper;
	}

	public List<String> getMessages() {
		return messages;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Throwable#getMessage()
	 */
	@Override
	public String getMessage() {
		if(messages.isEmpty())
		{
			return "";
		}
		return messages.get(0);
	}

	/**
	 * @param msg
	 */
	public void addMessage(String msg) {
		messages.add(msg);
	}

	/**
	 * @param execptions
	 */
	public void addExceptions(Collection<ValidationException> execptions) {
		this.exceptions.addAll(execptions);

	}

	public Collection<ValidationException> getExceptions() {
		return exceptions;
	}

}
