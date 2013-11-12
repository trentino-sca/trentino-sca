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
//class Binding
   //services 

inline const Trentino::XML::Schema::QName& Binding::xsdType() const
{
   return *mXSDType;
}


inline const Trentino::XML::Schema::NCName& Binding::name() const
{
   return mName;
}


inline OperationSelectorTypePtr Binding::operationSelectorElement() const
{
   return mOperationSelectorElement;
}
inline const std::vector<PolicySetAttachmentPtr>& Binding::policySetAttachmentElements() const
{
  return mPolicySetAttachmentElements;
}

inline const std::vector<QNamePtr>& Binding::policySets() const
{
  return mPolicySets;
}

inline const std::vector<QNamePtr>& Binding::requires() const
{
  return mRequires;
}

inline const std::vector<RequiresPtr>& Binding::scaRequiresElements() const
{
  return mScaRequiresElements;
}


inline const Trentino::XML::Schema::AnyURI& Binding::uri() const
{
   return mUri;
}


inline WireFormatTypePtr Binding::wireFormatElement() const
{
   return mWireFormatElement;
}

//for metadata and metadataStringAttribute

