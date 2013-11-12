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
#include "TrentinoRuntimeModelComposite.h"

//standard
#include <string>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <boost/bind.hpp>

//specific
#include "TrentinoRuntimeModelComponent.h"
#include "TrentinoRuntimeModelServiceBase.h"
#include "TrentinoRuntimeModelCommonFuncs.h"
#include "../SCAModel/TrentinoSCAModelComposite.h"
#include "../SCAModel/TrentinoSCAModelComponent.h"
#include "../SCAModel/TrentinoSCAModelService.h"
#include "../SCAModel/TrentinoSCAModelReference.h"
#include "../Invocation/TrentinoInvocation.h"
#include "TrentinoRuntimeModelVisitor.h"

using namespace std;
using Trentino::RuntimeModel::Composite;
namespace RuntimeModel = Trentino::RuntimeModel;
namespace SCAModel = Trentino::SCA::Model;

//class Component
   //construction
Composite::Composite( const Trentino::SCA::Model::CompositePtr& scaComposite
                    , const RuntimeModel::ContributionPtr& contribution)
: mSCAComposite(scaComposite)
, mQName(scaComposite->name(), scaComposite->targetNamespace())
, mContribution(contribution)
, mState(Composite::None)
, mIsDeployable(false)
{}

   //services
Trentino::Reflection::ReflectMethodPtr Composite::querySetterMethod(
   const RuntimeModel::ConstReferenceBasePtr& /*reference*/)
{  
   return Trentino::Reflection::ReflectMethodPtr();
}

Trentino::Reflection::ReflectMethodPtr Composite::queryPropertySetterMethod(
   const RuntimeModel::ConstPropertyPtr& /*property*/)
{  
   return Trentino::Reflection::ReflectMethodPtr();
}

RuntimeModel::ComponentPtr Composite::findComponentByName(const string& name) const
{   
   for( RuntimeModel::Components::const_iterator it = mComponents.begin()
      ; it != mComponents.end()
      ; ++it)
   {
      if((*it)->scaComponent()->name() == name)
      {
         return *it;
      }
   }
   
   return RuntimeModel::ComponentPtr();   
}

bool Trentino::RuntimeModel::Composite::visit( VisitorPtr& visitor )
   {
   Components::const_iterator it;
   for(it = mComponents.begin();it!=mComponents.end();++it){
      const ComponentPtr comp = *it;
      if(!visitor->visitComponent(comp)){
         return false;
         }
      if(!comp->visit(visitor)){
         return false;
         }
      }
   return true;
   }
