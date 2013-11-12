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
//class CPPInterface
   //services 

inline const Trentino::XML::Schema::Name& CPPInterface::callbackClass() const
{
   return mCallbackClass;
}

inline const std::vector<CPPFunctionPtr>& CPPInterface::callbackFunctionElements() const
{
  return mCallbackFunctionElements;
}


inline const std::string& CPPInterface::callbackHeader() const
{
   return mCallbackHeader;
}


inline const Trentino::XML::Schema::Name& CPPInterface::clazz() const
{
   return mClazz;
}


inline const std::vector<std::string>& CPPInterface::contentElements() const
{
  return mContentElements;
}
inline const std::vector<CPPFunctionPtr>& CPPInterface::functionElements() const
{
  return mFunctionElements;
}


inline const std::string& CPPInterface::header() const
{
   return mHeader;
}


//for metadata and metadataStringAttribute

