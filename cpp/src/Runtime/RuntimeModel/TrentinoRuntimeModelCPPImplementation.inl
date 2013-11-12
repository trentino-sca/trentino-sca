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
inline Trentino::SCA::Model::CPPImplementationPtr CPPImplementation::scaCPPImplementation() const
{
   return mSCACPPImplementation;
}

inline Trentino::Reflection::ReflectMethodPtr CPPImplementation::destroyLifeCycleMethod() const
{  
   return mDestroyMethod;
}

inline Trentino::Reflection::ReflectMethodPtr CPPImplementation::initLifeCycleMethod() const
{ 
  return mInitMethod;
}
inline Trentino::Reflection::ReflectObjectPtr CPPImplementation::instanceReflectObject() const
{ 
  return mClass; 
}

inline Trentino::Reflection::ReflectMethodPtr CPPImplementation::setContributionDirLifeCycleMethod() const
{ 
   return mSetContributionDirMethod;
}