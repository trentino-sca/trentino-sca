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

//baseclass
#include "TrentinoTestsCoreContributionLoaderBaseTest.h"

//standard
#include <string>
#include <ostream>

namespace Trentino{
namespace Tests{
namespace Core
{
   struct ContributionLoaderErrorsTestParams
   {
      std::string contributionName;
      Trentino::Core::ContributionLoading::Error expectedError;
      unsigned int expectedErrorCount;
   };

   struct ContributionLoader2ContribErrorsTestParams 
   {
      std::string contribution1Name;
      std::string contribution2Name;
      Trentino::Core::ContributionLoading::Error expectedError;
      unsigned int expectedErrorCount;
   };

   struct ContributionLoaderWireElementsTestParams
   {
      std::string wireSource;      
      Trentino::Core::ContributionLoading::Error expectedError;
   };

   std::ostream& operator<<(std::ostream& os, const ContributionLoaderErrorsTestParams& params)
   {
      return os << "{contributionName='" << params.contributionName 
                << "', expectedError="  << static_cast<int>(params.expectedError) 
                << ", expectedErrorCount=" << params.expectedErrorCount << "}";
   }

   std::ostream& operator<<( std::ostream& os
                           , const ContributionLoader2ContribErrorsTestParams& params)
   {
      return os << "{contribution1Name='" << params.contribution1Name 
                << "', contribution2Name='" << params.contribution2Name
                << "', expectedError="  << static_cast<int>(params.expectedError) 
                << ", expectedErrorCount=" << params.expectedErrorCount << "}";
   }

   std::ostream& operator<<( std::ostream& os
                           , const ContributionLoaderWireElementsTestParams& params)
   {
      return os << "{wireSource='" << params.wireSource                
                << "', expectedError="  << static_cast<int>(params.expectedError) << "}";
      
   }

   class ContributionLoaderDeploymentCriticalErrorsTest :
      public ContributionLoaderBaseTest,
      public ::testing::WithParamInterface<ContributionLoaderErrorsTestParams>
   {      
   }; //class ContributionLoaderDeploymentCriticalErrorsTest

   class ContributionLoaderWiringErrorsTest1 :
      public ContributionLoaderBaseTest,
      public ::testing::WithParamInterface<ContributionLoaderErrorsTestParams>
   {
   }; //class ContributionLoaderWiringErrorsTest

   class ContributionLoaderWiringErrorsTest2 :
      public ContributionLoaderBaseTest,
      public ::testing::WithParamInterface<ContributionLoader2ContribErrorsTestParams>
   {
   }; //class ContributionLoaderWiringErrorsTest2

   class ContributionLoaderWireElementsWiringErrorsTest :
      public ContributionLoaderBaseTest,
      public ::testing::WithParamInterface<ContributionLoaderWireElementsTestParams>
   {
   }; //class ContributionLoaderWireElementsWiringErrorsTest

} //namespace Trentino
} //namespace Tests
} //namespace Core