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
inline Trentino::SCA::Model::CompositePtr Composite::scaComposite() const
{
   return mSCAComposite;
}

inline const Trentino::XML::Schema::QName& Composite::qName() const
{
   return mQName;
}

inline ContributionWeakPtr Composite::contribution() const
{
   return mContribution;
}

inline const Components& Composite::components() const
{
 return mComponents;
}

inline void Composite::addComponent(const ComponentPtr& component)
{
   mComponents.push_back(component);
}

inline Composite::State Composite::state() const
{
   return mState;
}
inline void Composite::setState(Composite::State state)
{
   mState = state;
}

inline bool Composite::isDeployable() const
{
   return mIsDeployable;
}

inline void Composite::setDeployable(bool isDeployable)
{
   mIsDeployable = isDeployable;
}
