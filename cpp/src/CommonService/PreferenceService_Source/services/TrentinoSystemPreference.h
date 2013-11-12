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
#ifndef TrentinoSystemPreferenceH
#define TrentinoSystemPreferenceH

//standard
#include <string>
#include <vector>
#include <map>

using namespace std;

//specific
#include "TrentinoSystem.h"

//use the trentino variant class to store the preference

namespace Trentino{
	namespace System
	{
		class Preference
		{
			//services
		public:
			//*******************************************************************************************
			//                                       absolutePath()
			//*******************************************************************************************      
			//! \brief get this node's absolute path name. Note that:
			//  Root node - The path name of the root node is "/".
			//  Slash at end - Path names other than that of the root node may not end in slash ('/').
			//  Unusual names -"." and ".." have no special significance in path names.
			//  Illegal names - The only illegal path names are those that contain multiple 
			//  consecutive slashes, or that end in slash and are not the root.
			//! \return node's absolute path name. 
			//! \sa 
			//*******************************************************************************************
			virtual  string& absolutePath() = 0;

			//*******************************************************************************************
			//                                       childrenNames()
			//*******************************************************************************************      
			//! \brief Returns the names of the children of this node.
			//! \return the names of the children of this nod. 
			//! \sa 
			//*******************************************************************************************
			virtual vector<string> childrenNames() = 0;

			//*******************************************************************************************
			//                                       clear()
			//*******************************************************************************************      
			//! \brief Removes all of the properties (key-value associations) in this node.
			//! \return void.
			//*******************************************************************************************
			virtual void clear() = 0;

			//*******************************************************************************************
			//                                       flush()
			//*******************************************************************************************      
			//! \brief Forces any changes in the contents of this node and its descendants to the persistent store.
			//! \return void.
			//! \sa sync()
			//*******************************************************************************************
			virtual void flush() = 0;

			//*******************************************************************************************
			//                                       getString
			//*******************************************************************************************      
			//! \brief Returns the value associated with the specified string key in this node. 
			//         Returns the specified default if there is no value associated with the key, 
			//         or the backing store is inaccessible.
			//! \param[in] key - key whose associated value is to be returned.
			//             def - the value to be returned in the event that this node has no value associated 
			//                   with key or the backing store is inaccessible.
			//! \return the value associated with key, or def if no value is associated with key.
			//*******************************************************************************************
			virtual std::string getString(string key, std::string def) = 0;
			
			//*******************************************************************************************
			//                                       putString
			//*******************************************************************************************      
			//! \brief Associates the specified string value with the specified key in this node.
			//! \return void. 
			//! \sa 
			//*******************************************************************************************
			virtual void putString(string key, string value) = 0;

			//*******************************************************************************************
			//                                       keys()
			//*******************************************************************************************      
			//! \brief Returns all of the keys that have an associated value in this node.
			//! \return all of the keys that have an associated value in this node. 
			//! \sa 
			//*******************************************************************************************
			virtual vector<string> keys() = 0;

			//*******************************************************************************************
			//                                       name()
			//*******************************************************************************************      
			//! \brief Returns this node's name, relative to its parent.
			//! \return this node's name, relative to its parent. 
			//! \sa 
			//*******************************************************************************************
			virtual string& name() = 0;

			//*******************************************************************************************
			//                                       parent()
			//*******************************************************************************************      
			//! \brief Returns the parent of this node, or null if this is the root.
			//! \return PreferenceService object. 
			//! \sa 
			//*******************************************************************************************
			virtual Preference* parent() = 0;

			//*******************************************************************************************
			//                                       remove()
			//*******************************************************************************************      
			//! \brief  Removes the value associated with the specified key in this node, if any.
			//! \param[in] key - key whose mapping is to be removed from this node.
			//! \return void. 
			//! \sa 
			//*******************************************************************************************
			virtual void remove(string& key) = 0;

			//*******************************************************************************************
			//                                       removeNode()
			//*******************************************************************************************      
			//! \brief Removes this node and all of its descendants, invalidating any properties contained in the removed nodes.
			//! \return void. 
			//! \sa 
			//*******************************************************************************************
			virtual void removeNode() = 0;

			//*******************************************************************************************
			//                                       sync()
			//*******************************************************************************************      
			//! \brief Ensures that future reads from this node and its descendants reflect any changes that 
			//   were committed to the persistent store (from any VM) prior to the sync invocation.
			//! \return void. 
			//! \sa flush()
			//*******************************************************************************************
			virtual void sync() = 0;

			//*******************************************************************************************
			//                                       setSQLParams()
			//*******************************************************************************************      
			//! \brief set the sqlite connection parameters.
			//! \return void. 
			//! \sa flush()
			//*******************************************************************************************
			virtual void setSQLParams(string type, string dbPath) = 0;

			//*******************************************************************************************
			//                                       setAsRootNode()
			//*******************************************************************************************      
			//! \brief set the current node as a root node
			//! \return void. 
			//! \sa 
			//*******************************************************************************************
			virtual void setAsRootNode() = 0;

			//*******************************************************************************************
			//                                       IsRootNode()
			//*******************************************************************************************      
			//! \brief returns true if it is a root node.
			//! \return void. 
			//! \sa 
			//*******************************************************************************************
			virtual bool IsRootNode() = 0;
			//*******************************************************************************************
			//                                       node()
			//*******************************************************************************************      
			//! \brief Returns a named Preferences object (node), creating it and any of its ancestors if they do not already exist.
			//! \param[in] pathName - the path name of the Preferences object to return.
			//! \return PreferenceService object. 
			//! \sa 
			//*******************************************************************************************
			virtual Preference* node(string pathName) = 0;

			//*******************************************************************************************
			//                                       nodeExists()
			//*******************************************************************************************      
			//! \brief Returns true if the specified node exists.
			//! \param[in] pathName - the path name of the node whose existence is to be checked.
			//! \return bool. 
			//! \sa 
			//*******************************************************************************************
			virtual bool nodeExists(string pathName) = 0;

			//*******************************************************************************************
			//                                       get<T>()
			//*******************************************************************************************      
			//! \brief Returns the value associated with the specified key in this node. 
			//         Returns the specified default if there is no value associated with the key, 
			//         or the backing store is inaccessible.
			//! \param[in] key - key whose associated value is to be returned.
			//             def - the value to be returned in the event that this node has no value associated 
			//                   with key or the backing store is inaccessible.
			//! \return the value associated with key, or def if no value is associated with key.
			//*******************************************************************************************
			virtual int getInt(string key, int def) = 0;
			virtual float getFloat(string key, float def) = 0;
			virtual double getDouble(string key, double def) = 0;
			virtual long getLong(string key, long def) = 0;

			//*******************************************************************************************
			//                                       put<T>()
			//*******************************************************************************************      
			//! \brief Associates the specified value with the specified key in this node.
			//! \return void. 
			//! \sa 
			//*******************************************************************************************
			virtual void putInt(string key, int value) = 0;
			virtual void putFloat(string key, float value) = 0;
			virtual void putDouble(string key, double value) = 0;
			virtual void putLong(string key, long value) = 0;
		};
	} //namespace System
} //namespace Trentino

#endif //TrentinoSystemPreferenceH
