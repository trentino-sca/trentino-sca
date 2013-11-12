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
#include <string>
#include <vector>
#include <map>
#include <gtest/gtest.h>

//specific
#include "TrentinoTestsCore.h"
#include "../../Runtime/Core/TrentinoCoreComponentPropertyManager.h"
#include "../../Runtime/Core/TrentinoCore.h"
#include "../../Runtime/Core/TrentinoCoreBootstrappingBootHelper.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModel.h"

namespace Trentino{
namespace Tests{
namespace Core
{
   struct ComponentPropertyManagerValueAssignmentTestParams
   {
      //additional
      typedef std::map< std::string, std::vector<std::string> >  PropertyValuesMap;

      //construction
      ComponentPropertyManagerValueAssignmentTestParams( const std::string& componentURI_
                                        , const PropertyValuesMap& expectedPropertyValues_)
      : componentURI(componentURI_)
      , expectedPropertyValues(expectedPropertyValues_)
      { }

      //data
      std::string componentURI;
      PropertyValuesMap expectedPropertyValues;
   }; //struct ComponentPropertyManagerValueAssignmentTestParams

   std::ostream& operator<<(
      std::ostream& os, const ComponentPropertyManagerValueAssignmentTestParams& params);

   class ComponentPropertyManagerValueAssignmentTest : 
      public testing::TestWithParam<ComponentPropertyManagerValueAssignmentTestParams>
   {
      //services
   public:
      static void SetUpTestCase();
      static void TearDownTestCase();

      //data
   protected:      
      static Booter::BootPtr mApp;
      static Trentino::RuntimeModel::ContributionPtr mContribution;     
   }; // class ComponentPropertyManagerValueAssignmentTest 

   struct ComponentPropertyManagerErrorsTestParams
   {
      //data
      std::string componentURI;
      std::string propertyName;
      char attribute; //'v' - @value, 's' - @source, 'f' - @file
      std::string attributeValue;
      Trentino::Core::ComponentPropertyManager::Error expectedError;
   }; //struct ComponentPropertyManagerValueAssignmentTestParams

   std::ostream& operator<<(
      std::ostream& os, const ComponentPropertyManagerErrorsTestParams& params);

   class ComponentPropertyManagerErrorsTest : 
      public testing::TestWithParam<ComponentPropertyManagerErrorsTestParams>
   {
      //services
   public:
      static void SetUpTestCase();
      static void TearDownTestCase();

      //data
   protected:      
      static Booter::BootPtr mApp;
      static Trentino::RuntimeModel::ContributionPtr mContribution;     
   }; // class ComponentPropertyManagerValueAssignmentTest 

} //namespace Core
} //namespace Tests
} //namespace Trentino
