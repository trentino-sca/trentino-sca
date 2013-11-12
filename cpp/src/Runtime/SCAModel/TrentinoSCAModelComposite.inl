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
//class Composite
   //services 

inline bool Composite::isAutowire() const
{
   return mIsAutowire;
}

inline const std::vector<ComponentPtr>& Composite::componentElements() const
{
  return mComponentElements;
}


inline const std::vector<std::string>& Composite::contentElements() const
{
  return mContentElements;
}
inline const std::vector<IncludePtr>& Composite::includeElements() const
{
  return mIncludeElements;
}


inline bool Composite::isLocal() const
{
   return mIsLocal;
}


inline const Trentino::XML::Schema::NCName& Composite::name() const
{
   return mName;
}

inline const std::vector<PolicySetAttachmentPtr>& Composite::policySetAttachmentElements() const
{
  return mPolicySetAttachmentElements;
}

inline const std::vector<QNamePtr>& Composite::policySets() const
{
  return mPolicySets;
}

inline const std::vector<PropertyPtr>& Composite::propertyElements() const
{
  return mPropertyElements;
}

inline const std::vector<ReferencePtr>& Composite::referenceElements() const
{
  return mReferenceElements;
}

inline const std::vector<RequiresPtr>& Composite::requiresElements() const
{
  return mRequiresElements;
}

inline const std::vector<ServicePtr>& Composite::serviceElements() const
{
  return mServiceElements;
}


inline const Trentino::XML::Schema::AnyURI& Composite::targetNamespace() const
{
   return mTargetNamespace;
}

inline const std::vector<WirePtr>& Composite::wireElements() const
{
  return mWireElements;
}


//for metadata and metadataStringAttribute

