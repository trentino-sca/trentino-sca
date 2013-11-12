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

//header
#include "TrentinoRuntimeModelContribution.h"

//standard
#include <algorithm>
#include <boost/filesystem.hpp>

//specific
#include "../SCAModel/TrentinoSCAModelModelDescriptor.h"
#include "TrentinoRuntimeModelComposite.h"
#include "TrentinoRuntimeModelVisitor.h"

using namespace Trentino::RuntimeModel;
using Trentino::RuntimeModel::Contribution;

//class Contribution
   //construction
Contribution::Contribution( const Trentino::SCA::Model::ModelDescriptorPtr& scaModelDescriptor
                          , const Trentino::Utils::URI& baseURI)
: mSCAModelDescriptor(scaModelDescriptor)
, mBaseURI(baseURI)
, mState(Contribution::None)
{}

Contribution::~Contribution()
{
   //should be manually done before the contribution library is unloaded
  disposeComposites();
}

   //services
void Contribution::removeComposite(const ConstCompositePtr& composite)
{
   const Composites::iterator it = 
      find(mComposites.begin(), mComposites.end(), composite);
   
   if(it != mComposites.end())
      mComposites.erase(it);
}

void Contribution::setLocalPath(const std::string& localPath)
{
   mLocalPath = boost::filesystem::absolute(localPath).string();
}


bool Trentino::RuntimeModel::Contribution::visit(VisitorPtr& visitor )
{
   Composites::const_iterator it;
   for(it = mComposites.begin();it!=mComposites.end();++it){
      const CompositePtr comp = *it;
      if(! visitor->visitComposite(comp)){
         return false;
         }
      if(!comp->visit(visitor)){
         return false;
         }
      }
   return true;
}

