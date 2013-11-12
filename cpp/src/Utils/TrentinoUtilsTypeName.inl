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

//! static member assignment
template <typename TYPE> const char* TypeName<TYPE>::mTypeName = TypeName<TYPE>::name();


//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'char' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<char>::name()
{
   static const char* name = "char";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'signed char' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<signed char>::name()
{
   static const char* name = "char";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'unsigned char' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<unsigned char>::name()
{
   static const char* name = "unsigned char";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'short' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<short>::name()
{
   static const char* name = "short";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'unsigned short' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<unsigned short>::name()
{
   static const char* name = "unsigned short";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'int' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<int>::name()
{
   static const char* name = "int";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'unsigned int' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<unsigned int>::name()
{
   static const char* name = "unsigned int";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'long' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<long>::name()
{
   static const char* name = "long";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'unsigned long' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<unsigned long>::name()
{
   static const char* name = "unsigned long";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'long long' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<long long>::name()
{
   static const char* name = "long long";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'unsigned long long' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<unsigned long long>::name()
{
   static const char* name = "unsigned long long";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'void*' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<void*>::name()
{
   static const char* name = "void *";
   return name;
}

template <>
inline const char* TypeName<const void*>::name()
{
   static const char* name = "const void *";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::string' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName<std::string>::name()
{
   static const char* name = "std::string";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<std::string>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<std::string> >::name()
{
   static const char* name = "std::list<std::string>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list< std::list<std::string> >' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list< std::list<std::string> > >::name()
{
   static const char* name = "std::list<std::list<std::string>>";
   return name;
}


//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<signed char>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<signed char> >::name()
{
   static const char* name = "std::list<signed char>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<unsigned char>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<unsigned char> >::name()
{
   static const char* name = "std::list<unsigned char>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<char>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<char> >::name()
{
   static const char* name = "std::list<char>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<short>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<short> >::name()
{
   static const char* name = "std::list<short>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<unsigned short>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<unsigned short> >::name()
{
   static const char* name = "std::list<unsigned short>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<bool>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<bool> >::name()
{
   static const char* name = "std::list<bool>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<int>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<int> >::name()
{
   static const char* name = "std::list<int>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<unsigned int>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<unsigned int> >::name()
{
   static const char* name = "std::list<unsigned int>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<long>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<long> >::name()
{
   static const char* name = "std::list<long>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<unsigned long>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<unsigned long> >::name()
{
   static const char* name = "std::list<unsigned long>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<float>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<float> >::name()
{
   static const char* name = "std::list<float>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<double>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<double> >::name()
{
   static const char* name = "std::list<double>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<long long>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<long long> >::name()
{
   static const char* name = "std::list<long long>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<unsigned long long>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<unsigned long long> >::name()
{
   static const char* name = "std::list<unsigned long long>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<unsigned long long>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<void*> >::name()
{
   static const char* name = "std::list<void*>";
   return name;
}

//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns 'std::list<const char*>' typename specialization as a string
//! \return typename as a const char* string
//****************************************************************************************************
template <>
inline const char* TypeName< std::list<const char*> >::name()
{
   static const char* name = "std::list<const char*>";
   return name;
}


//****************************************************************************************************
//                                     name()                               
//****************************************************************************************************
//! \brief Returns default typename as a string using RTTI
//! \return typename as a const char* string
//****************************************************************************************************
template < typename TYPE >
inline const char* TypeName< TYPE >::name()
{
   static const char* name = unMangle(typeid(TYPE).name());
   return name;
}

