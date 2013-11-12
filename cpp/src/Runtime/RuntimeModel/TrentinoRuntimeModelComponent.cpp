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
#include "TrentinoRuntimeModelComponent.h"

//standard
#include <algorithm>
#include <boost/bind.hpp>


//specific
#include "TrentinoRuntimeModelServiceBase.h"
#include "TrentinoRuntimeModelReferenceBase.h"
#include "TrentinoRuntimeModelComposite.h"
#include "TrentinoRuntimeModelContribution.h"
#include "TrentinoRuntimeModelProperty.h"
//#include "TrentinoRuntimeModelCommonFuncs.h"
#include "../SCAModel/TrentinoSCAModelComponentService.h"
#include "../SCAModel/TrentinoSCAModelComponent.h"
#include "../SCAModel/TrentinoSCAModelImplementation.h"
#include "TrentinoRuntimeModelVisitor.h"

using namespace std;
using Trentino::RuntimeModel::Component;
namespace RuntimeModel = Trentino::RuntimeModel;

//class Component
   //construction
Component::Component( const Trentino::SCA::Model::ComponentPtr& scaComponent                    
                    , const RuntimeModel::CompositePtr& composite
                    , const RuntimeModel::ImplementationPtr& implementation)
: mSCAComponent(scaComponent)
, mComposite(composite)
, mImplementation(implementation)
, mState(Component::Initial)
{}

   //services
const Trentino::Utils::URI& Component::uri() const
{
   //lazy initialization
   //! \todo This is not thread safe. Better refactor the relations between Component and 
   //!       Implementation so that the URI can be set by ContributionLoader. Currently it's not
   //!       possible because computeStructuralURI() assumes that all the component's parent
   //!       components are set when the URI is computed but this is not the case if the URI is
   //!       computed inside of ContributionLoader::createRuntimeComponent().  
   if(mURI.empty())
   {
      mURI = computeStructuralURI();         
   }
   
   return mURI;
}

RuntimeModel::ServiceBasePtr Component::findServiceByName(const string& name) const
{   
   const RuntimeModel::ServiceBases::const_iterator it = 
      find_if( mServices.begin()
             , mServices.end()
             , boost::bind(&RuntimeModel::ServiceBase::name, _1) == name );

   return it != mServices.end() ? *it : RuntimeModel::ServiceBasePtr();
}

RuntimeModel::ReferenceBasePtr Component::findReferenceByName(const string& name) const
{
   const RuntimeModel::ReferenceBases::const_iterator it = 
      find_if( mReferences.begin()
             , mReferences.end()
             , boost::bind(&RuntimeModel::ReferenceBase::name, _1) == name );

   return it != mReferences.end() ? *it : RuntimeModel::ReferenceBasePtr();
}


RuntimeModel::PropertyPtr Component::findPropertyByName(const string& name) const
{
   const RuntimeModel::Properties::const_iterator it = 
      find_if( mProperties.begin()
             , mProperties.end()
             , boost::bind(&RuntimeModel::Property::name, _1) == name );

   return it != mProperties.end() ? *it : RuntimeModel::PropertyPtr();
}


const Trentino::XML::Schema::QName& Trentino::RuntimeModel::Component::getImplementationType() const
{
   assert(mSCAComponent->implementationElement());   
   return  mSCAComponent->implementationElement()->xsdType();
}

   //management
Trentino::Utils::URI Component::computeStructuralURI() const
{
   string uriStr = mSCAComponent->name();   
   
   const RuntimeModel::ConstCompositePtr parentComposite = mComposite.lock();
   assert(parentComposite);
   ConstComponentPtr parentComponent = parentComposite->component().lock();   
   
   while(parentComponent)
   {
      uriStr.insert(0, parentComponent->scaComponent()->name() + "/");
      const RuntimeModel::ConstCompositePtr parentComposite = parentComponent->composite().lock();
      assert(parentComposite);
      parentComponent = parentComposite->component().lock();
   }

   return uriStr;   
}


bool Trentino::RuntimeModel::Component::visit( VisitorPtr& visitor )
{
   for(ServiceBases::const_iterator it = mServices.begin();it!=mServices.end();++it){
      const ServiceBasePtr comp = *it;
      if(!visitor->visiteService(comp)){
         return false;
         }
      }

   for(ReferenceBases::const_iterator it = mReferences.begin();it!=mReferences.end();++it){
      const ReferenceBasePtr comp = *it;
      if(!visitor->visiteReference(comp)){
         return false;
         }
      }
   return true;
}

 Trentino::Reflection::DataRegistry& Trentino::RuntimeModel::Component::dataRegistry()const
{
 const RuntimeModel::ConstCompositePtr parentComposite = mComposite.lock();
 const RuntimeModel::ConstContributionPtr contribution= parentComposite->contribution().lock();
 return contribution->contributionInfo()->dataRegistry();
}
