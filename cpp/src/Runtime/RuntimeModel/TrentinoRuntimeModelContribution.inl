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

inline Trentino::SCA::Model::ModelDescriptorPtr Contribution::scaModelDescriptor() const
{
   return mSCAModelDescriptor;
}

inline const Trentino::Utils::URI& Contribution::baseURI() const
{
   return mBaseURI;
}

inline void Contribution::setContributionLibrary(const Trentino::Utils::DynamicLibraryPtr& lib)
{
   mContributionLibrary = lib;
}

inline void Contribution::setBusinessLibraries(
   const std::vector<Trentino::Utils::DynamicLibraryPtr>& libraries)
{
   mBusinessLibraries = libraries;
}


inline const Composites& Contribution::composites() const
{
   return mComposites;   
}

inline void Contribution::addComposite(const CompositePtr& composite)
{
   mComposites.push_back(composite);
}

inline void Contribution::disposeComposites()
{
   mComposites.clear();
}

inline Contribution::State Contribution::state() const
{
   return mState;
}

inline void Contribution::setState(Contribution::State state)
{
   mState = state;
}

inline void Trentino::RuntimeModel::Contribution::setContributionInfo( const Trentino::Core::TrentinoContributionInfoPtr& contributionInfo )
{
   mContributionInfo = contributionInfo;
}

inline Trentino::Core::TrentinoContributionInfoPtr Trentino::RuntimeModel::Contribution::contributionInfo()const
{
   return mContributionInfo;
}

inline const std::string& Contribution::localPath() const
{
   return mLocalPath;
}

inline void Contribution::setVersion(std::string& nVersion)
{
 mVersion = nVersion;
}

inline const std::string& Contribution::version() const
{
 return mVersion;
}
