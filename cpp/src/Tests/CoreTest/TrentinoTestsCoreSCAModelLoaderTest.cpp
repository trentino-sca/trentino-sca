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

//standard
#include <gtest/gtest.h>

//specific
#include "../../Global/TrentinoGlobal.h"
#include "../../Runtime/Core/TrentinoCoreContributionLoadingSCAModelLoader.h"
#include "../../Runtime/SCAModel/TrentinoSCAModel.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelComponent.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelComposite.h"
#include "../../Runtime/SCAModel/TrentinoSCAModelModelDescriptor.h"
#include "../../Runtime/XML/TrentinoXMLSchemaQName.h"

using namespace std;
using Trentino::Core::ContributionLoading::SCAModelLoader;
using Trentino::XML::Schema::QName;
namespace SCAModel = Trentino::SCA::Model;


TEST(SCAModelLoaderTest, testConstruction)
{
   SCAModel::ModelDescriptor modelDescriptor;
   SCAModelLoader modelLoader(modelDescriptor);

   ASSERT_TRUE(modelDescriptor.contribution() == SCAModel::ContributionTypePtr());   
}

TEST(SCAModelLoaderTest, testCreateContributionType)
{
   SCAModel::ModelDescriptor modelDescriptor;
   SCAModelLoader modelLoader(modelDescriptor);
   SCAModelLoader::SCAModelFactory& factory = modelLoader.scaModelFactory();

   SCAModel::ContributionType* const contribution1 = factory.createContributionType();
   ASSERT_TRUE(contribution1 != nullptr);
   ASSERT_TRUE(modelDescriptor.contribution().get() == contribution1);
   ASSERT_TRUE(factory.createContributionType() == nullptr);
   ASSERT_TRUE(factory.createContributionType() == nullptr);
   ASSERT_TRUE(modelDescriptor.contribution().get() == contribution1);   
}

TEST(SCAModelLoaderTest, testCreateComposite)
{
   SCAModel::ModelDescriptor modelDescriptor;
   SCAModelLoader modelLoader(modelDescriptor);
   SCAModelLoader::SCAModelFactory& factory = modelLoader.scaModelFactory();

   SCAModel::Composite* const composite1 = factory.createComposite(); 
   ASSERT_TRUE(composite1 != nullptr);
   const QName qName1("SomeName1", "SomeNamespace");
   composite1->setName(qName1.localPart().c_str());
   composite1->setTargetNamespace(qName1.namespaceName().c_str());
   ASSERT_TRUE( modelDescriptor.findCompositeByQName(qName1).get() == composite1 );   

   SCAModel::Composite* const composite2 = factory.createComposite();
   ASSERT_TRUE(composite2 != nullptr);
   const QName qName2("SomeName2", "SomeNamespace");
   composite2->setName(qName2.localPart().c_str());
   composite2->setTargetNamespace(qName2.namespaceName().c_str());   
   ASSERT_TRUE( modelDescriptor.findCompositeByQName(qName1).get() == composite1 );   
   ASSERT_TRUE( modelDescriptor.findCompositeByQName(qName2).get() == composite2 );   
   
   SCAModel::Composite* const composite3 = factory.createComposite();
   ASSERT_TRUE(composite2 != nullptr);   
   composite2->setName(qName2.localPart().c_str()); //use the same QName
   composite2->setTargetNamespace(qName2.namespaceName().c_str()); ////use the same QName  
   ASSERT_TRUE( modelDescriptor.findCompositeByQName(qName1).get() == composite1 );   
   ASSERT_TRUE(    modelDescriptor.findCompositeByQName(qName2).get() == composite2 
                   || modelDescriptor.findCompositeByQName(qName2).get() == composite3 );
}                    

TEST(SCAModelLoaderTest, testAssociate)
{
   SCAModel::ModelDescriptor modelDescriptor;
   SCAModelLoader modelLoader(modelDescriptor);
   SCAModelLoader::SCAModelFactory& factory = modelLoader.scaModelFactory();

   const SCAModel::ComponentPtr component1(factory.createComponent());
   SCAModel::ComponentType* const componentType1 = factory.createComponentType();
   ASSERT_TRUE(component1.get() != nullptr);
   ASSERT_TRUE(componentType1 != nullptr);
   ASSERT_TRUE(modelDescriptor.findComponentType(component1).get() == nullptr);
   modelLoader.associate(component1.get(), componentType1);
   ASSERT_TRUE(modelDescriptor.findComponentType(component1).get() == componentType1);

   const SCAModel::ComponentPtr component2(factory.createComponent());
   SCAModel::ComponentType* const componentType2 = factory.createComponentType();
   ASSERT_TRUE(component2.get() != nullptr);
   ASSERT_TRUE(componentType2 != nullptr);
   ASSERT_TRUE(modelDescriptor.findComponentType(component2).get() == nullptr);
   modelLoader.associate(component2.get(), componentType2);
   ASSERT_TRUE(modelDescriptor.findComponentType(component1).get() == componentType1);
   ASSERT_TRUE(modelDescriptor.findComponentType(component2).get() == componentType2);
   
}

TEST(SCAModelLoaderTest, testSharedPointers)
{
   SCAModel::ContributionTypePtr contributionTypePtr;
   SCAModel::ComponentTypePtr componentTypePtr;

   {
      SCAModel::ModelDescriptor modelDescriptor;
      SCAModelLoader modelLoader(modelDescriptor);
      SCAModelLoader::SCAModelFactory& factory = modelLoader.scaModelFactory();

      factory.createContributionType();
      contributionTypePtr = modelDescriptor.contribution();
      ASSERT_TRUE(contributionTypePtr.use_count() == 2);

      const SCAModel::ComponentPtr component(factory.createComponent());
      SCAModel::ComponentType* const componentType = factory.createComponentType();
      ASSERT_TRUE(component != nullptr);
      ASSERT_TRUE(componentType != nullptr);
      modelLoader.associate(component.get(), componentType);
      componentTypePtr = modelDescriptor.findComponentType(component);
      ASSERT_TRUE(componentTypePtr.use_count() == 2);
   }
   
   ASSERT_TRUE(contributionTypePtr.use_count() == 1);
   ASSERT_TRUE(componentTypePtr.use_count() == 1);
}
