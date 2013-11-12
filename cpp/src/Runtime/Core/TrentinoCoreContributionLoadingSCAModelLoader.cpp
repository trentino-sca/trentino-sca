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
#include "TrentinoCoreContributionLoadingSCAModelLoader.h"

//standard
#include <stdexcept>
#include <boost/foreach.hpp>

//specific
#include "../SCAModel/TrentinoSCAModelModelDescriptor.h"
#include "../SCAModel/TrentinoSCAModelContributionType.h"
#include "../SCAModel/TrentinoSCAModelComposite.h"
#include "../SCAModel/TrentinoSCAModelComponentType.h"


using namespace std;
using Trentino::Core::ContributionLoading::SCAModelLoader;
namespace SCAModel = Trentino::SCA::Model;

//class SCAModelLoader
   //additional
      //class SCAModelFactory
         //construction
SCAModelLoader::SCAModelFactory::SCAModelFactory(SCAModelLoader& scaModelLoader)
: mSCAModelLoader(scaModelLoader)
{}


SCAModelLoader::SCAModelFactory::~SCAModelFactory()
{
}

         //services
SCAModel::Composite* TRENTINO_STDCALL SCAModelLoader::SCAModelFactory::createComposite()
{
   SCAModel::Composite* const composite = SCAModel::Factory::createComposite();
   mSCAModelLoader.mModelDescriptor.mComposites.push_back(SCAModel::CompositePtr(composite));      
   return composite;

}

SCAModel::ContributionType* TRENTINO_STDCALL 
   SCAModelLoader::SCAModelFactory::createContributionType()
{  
   if(mSCAModelLoader.mModelDescriptor.contribution())
      return nullptr;   

   SCA::Model::ContributionType* const contributionType = 
      SCAModel::Factory::createContributionType();

   mSCAModelLoader.mModelDescriptor.mContribution.reset(contributionType);      

   return contributionType;   
}

#pragma warning(push)
#pragma warning(disable:4355)
   //construction
SCAModelLoader::SCAModelLoader(SCAModel::ModelDescriptor& modelDescriptor)
: mSCAModelFactory(*this) //this is OK, SCAModelFactory won't use it during constrution
, mModelDescriptor(modelDescriptor)
{}
#pragma warning(pop)

SCAModelLoader::~SCAModelLoader()
{
   //DON'T EXECUTE ANY CLEAN UP ACTIONS FOR mModelDescriptor HERE
}

   //services
 SCAModelLoader::SCAModelFactory& TRENTINO_STDCALL SCAModelLoader::scaModelFactory()
 {
   return mSCAModelFactory;
 }

void TRENTINO_STDCALL SCAModelLoader::associate( SCAModel::Component* component
                                               , SCAModel::ComponentType* componentType)
{
   //Since N components can be associated with _one_ componentType (N-to-1 relationship)
   //and therefore associate() could be called several times with the same componentType
   //argument (associate(c1, ct1); associate(c2, ct1); etc.) it's necessary to check
   //whether a shared pointer to the passed componentType already exists and if yes
   //just to copy it instead of creating a new shared pointer and thus introducing a bug.  
    
   BOOST_FOREACH( const SCAModel::ComponentTypeMap::value_type& pair
                , mModelDescriptor.mComponentTypeMap)
   {
      if(pair.second.get() == componentType)
      {
         mModelDescriptor.mComponentTypeMap[component] = pair.second;
         return;
      }
   }

   //create a new shared pointer only if it is the first time that associate() is called
   //with this componentType argument 
   mModelDescriptor.mComponentTypeMap[component] = SCAModel::ComponentTypePtr(componentType);
}
