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

import java.util.Collection;
import java.util.Iterator;

import org.trentino.trengen.sca.model.Reference;

/**
 * @author z002ttbb
 */
public class TIterable<T> implements Iterable<T> {

	private Class<T>	clazz;
	private Collection	collection;

	public TIterable (Collection collection, Class<T> clazz) {
		if(clazz == null)
		{
			throw new IllegalArgumentException("Class is null");
		}
		if(collection == null)
		{
			throw new IllegalArgumentException("Collection is null");
		}
		this.clazz = clazz;
		this.collection = collection;
	}
	
	public static <T> TIterable<T> iterable(Collection col, Class<T> cl){
		return new TIterable<T>(col, cl);
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Iterable#iterator()
	 */
	@Override
	public Iterator<T> iterator() {
		return new ObjectIterator();
	}

	class ObjectIterator implements Iterator<T> {
		Iterator		iter;
		Object		    next	= null;
		private boolean	hasNextCalled;

		ObjectIterator () {
			iter = collection.iterator();
		}

		/*
		 * (non-Javadoc)
		 * @see java.util.Iterator#hasNext()
		 */
		@Override
		public boolean hasNext() {
			hasNextCalled = true;
			if(!iter.hasNext())
			{
				return false;
			}
			next = iter.next();

			// handle null elements
			while (next == null && iter.hasNext())
			{
				next = iter.next();
			}
			if(next == null)
			{
				return false;
			}

			// filter type
			if(clazz.isAssignableFrom(next.getClass()))
			{
				return true;
			}
			return hasNext();
		}

		/*
		 * (non-Javadoc)
		 * @see java.util.Iterator#next()
		 */
		@Override
		public T next() {
			try
			{
				if(hasNextCalled)
				{
					return (T) next;
				}
				if(!hasNext())
				{
					throw new IllegalStateException("No such element");
				}
				return (T) next;
			} finally
			{
				hasNextCalled = false;
			}

		}

		/*
		 * (non-Javadoc)
		 * @see java.util.Iterator#remove()
		 */
		@Override
		public void remove() {
			throw new IllegalStateException("Cannot remote");

		}

	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
	    return collection.toString();
	}

}
