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

//construction
inline
UriHelper::UriHelper()
{
}

inline
UriHelper::UriHelper(const std::string& uri)
{
   setFromString(uri);
}

inline
UriHelper::UriHelper( const std::string& scheme
   ,const std::string& authority
   ,const std::string& path
   ,const std::string& query
   ,const std::string& fragment)
{
   composeUri(scheme, authority, path, query, fragment);
}

inline
UriHelper::UriHelper(const UriHelper& source)
{
   copyFrom(source);
}

//operators
inline
const UriHelper& UriHelper::operator=(const UriHelper& source)
{
   copyFrom(source);

   return (*this);
}

inline
const UriHelper& UriHelper::operator=(const std::string uri)
{
   setFromString(uri);

   return (*this);
}

inline
void UriHelper::setFromString(const std::string& uri)
{
   parseUriString(uri);
}

inline
const std::string& UriHelper::scheme() const
{
   return mScheme;
}

inline
bool UriHelper::hasAuthority() const
{
   return (!mAuthority.empty());
}

inline
const std::string& UriHelper::authority() const
{
   return mAuthority;
}

inline
bool UriHelper::hasQuery() const
{
   return (!mQuery.empty());
}

inline
const std::string UriHelper::query() const
{
   return mQuery;
}

inline
bool UriHelper::hasFragment() const
{
   return (!mFragment.empty());
}

inline
const std::string UriHelper::fragment() const
{
   return mFragment;
}

inline
const std::string& UriHelper::path() const
{
   return mPath;
}

inline
const std::string UriHelper::toString() const
{
   return mUriString;
}

