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

template < typename TYPE >
inline TYPE DefaultValue< TYPE >::value()
{
   return (TYPE) nullptr;
}

template <>
inline signed char DefaultValue<signed char>::value()
{
   return static_cast<signed char>(0);
}

template <>
inline unsigned char DefaultValue<unsigned char>::value()
{
   return static_cast<unsigned char>(0);
}

template <>
inline short DefaultValue<short>::value()
{
   return static_cast<short>(0);
}

template <>
inline unsigned short DefaultValue<unsigned short>::value()
{
   return static_cast<unsigned short>(0);
}

template <>
inline bool DefaultValue<bool>::value()
{
   return static_cast<bool>(false);
}

template <>
inline int DefaultValue<int>::value()
{
   return static_cast<int>(0);
}

template <>
inline unsigned int DefaultValue<unsigned int>::value()
{
   return static_cast<unsigned int>(0);
}

template <>
inline long DefaultValue<long>::value()
{
   return static_cast<long>(0);
}

template <>
inline unsigned long DefaultValue<unsigned long>::value()
{
   return static_cast<unsigned long>(0);
}

template <>
inline float DefaultValue<float>::value()
{
   return 0.0f;
}

template <>
inline double DefaultValue<double>::value()
{
   return 0.0;
}

template <>
inline long long DefaultValue<long long>::value()
{
   return static_cast<long long>(0);
}

template <>
inline unsigned long long DefaultValue<unsigned long long>::value()
{
   return static_cast<unsigned long long>(0);
}

template <>
inline const char* DefaultValue<const char*>::value()
{
   return static_cast<const char*>(nullptr);
}

template <>
inline ListTypePtr DefaultValue<ListTypePtr>::value()
{
   return ListTypePtr();
}
