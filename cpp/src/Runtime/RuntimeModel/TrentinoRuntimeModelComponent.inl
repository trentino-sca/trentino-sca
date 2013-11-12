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

//class Component
   //services
inline Trentino::SCA::Model::ComponentPtr Component::scaComponent() const
{
   return mSCAComponent;
}

inline CompositeWeakPtr Component::composite() const
{
   return mComposite;
}

inline const ServiceBases& Component::services() const
{
   return mServices;
}

inline void Component::addService(const ServiceBasePtr& service)
{
   mServices.push_back(service);   
}

inline void Component::addReference(const ReferenceBasePtr& reference)
{
   mReferences.push_back(reference);   
}

inline void Component::addProperty(const PropertyPtr& property)
{
   mProperties.push_back(property);
}

inline ImplementationPtr Component::implementation() const
{
   return mImplementation;
}

inline const ReferenceBases& Component::references() const
{
   return mReferences;
}

inline const Properties& Component::properties() const
{
  return mProperties;
}

inline Component::State Component::state() const
{
   return mState;
}

inline void Component::setState(Component::State state)
{
   mState = state;
}

inline boost::recursive_mutex& Component::mutex() const
{
   return mRecursiveMutex;
}


inline const std::string& Component::name() const
{
   return mSCAComponent->name();   
}