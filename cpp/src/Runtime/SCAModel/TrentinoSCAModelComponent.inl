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

inline bool Component::isAutowire() const
{
   return mIsAutowire;
}


inline ExtensionsPtr Component::extensionsElement() const
{
   return mExtensionsElement;
}

inline ImplementationPtr Component::implementationElement() const
{
   return mImplementationElement;
}

inline const Trentino::XML::Schema::NCName& Component::name() const
{
   return mName;
}

inline const std::vector<PolicySetAttachmentPtr>& Component::policySetAttachmentElements() const
{
  return mPolicySetAttachmentElements;
}

inline const std::vector<QNamePtr>& Component::policySets() const
{
  return mPolicySets;
}

inline const std::vector<PropertyValuePtr>& Component::propertyElements() const
{
  return mPropertyElements;
}

inline const std::vector<ComponentReferencePtr>& Component::referenceElements() const
{
  return mReferenceElements;
}

inline const std::vector<RequiresPtr>& Component::requiresElements() const
{
  return mRequiresElements;
}

inline const std::vector<ComponentServicePtr>& Component::serviceElements() const
{
  return mServiceElements;
}


//for metadata and metadataStringAttribute

