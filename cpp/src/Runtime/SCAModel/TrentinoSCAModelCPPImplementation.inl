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
//class CPPImplementation
   //services 

inline bool CPPImplementation::isAllowsPassByReference() const
{
   return mIsAllowsPassByReference;
}


inline const Trentino::XML::Schema::Name& CPPImplementation::clazz() const
{
   return mClazz;
}


inline const std::string& CPPImplementation::componentType() const
{
   return mComponentType;
}


inline const std::vector<std::string>& CPPImplementation::contentElements() const
{
  return mContentElements;
}

inline bool CPPImplementation::isEagerInit() const
{
   return mIsEagerInit;
}

inline const std::vector<CPPImplementationFunctionPtr>& CPPImplementation::functionElements() const
{
  return mFunctionElements;
}


inline const std::string& CPPImplementation::header() const
{
   return mHeader;
}


inline const Trentino::XML::Schema::NCName& CPPImplementation::library() const
{
   return mLibrary;
}


inline const std::string& CPPImplementation::path() const
{
   return mPath;
}


inline CPPImplementationScopePtr CPPImplementation::scope() const
{
   return mScope;
}

//for metadata and metadataStringAttribute

