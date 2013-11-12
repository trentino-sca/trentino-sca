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
//class Callback
   //services 
inline const std::vector<BindingPtr>& Callback::bindingElements() const
{
  return mBindingElements;
}

inline const std::vector<ExtensionsPtr>& Callback::extensionsElements() const
{
  return mExtensionsElements;
}

inline const std::vector<PolicySetAttachmentPtr>& Callback::policySetAttachmentElements() const
{
  return mPolicySetAttachmentElements;
}

inline const std::vector<QNamePtr>& Callback::policySets() const
{
  return mPolicySets;
}

inline const std::vector<RequiresPtr>& Callback::requiresElements() const
{
  return mRequiresElements;
}


//for metadata and metadataStringAttribute

