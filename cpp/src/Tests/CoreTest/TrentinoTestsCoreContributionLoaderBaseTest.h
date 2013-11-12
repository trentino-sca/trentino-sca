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
#include <list>
#include <string>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

//specific
#include "TrentinoTestsCore.h"
#include "../../Runtime/Core/TrentinoCore.h"
#include "../../Runtime/Core/TrentinoCoreBootstrappingBootHelper.h"
#include "../../Runtime/Core/TrentinoCoreContributionLoadingContributionLoader.h"
#include "../../Runtime/Core/TrentinoCoreContributionLoadingErrorHandlerBase.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModel.h"

namespace Trentino{
namespace Tests{
namespace Core
{
   class ContributionLoaderBaseTest : public testing::Test
   {
      //additional
   protected:
      class CollectingErrorHandler : public Trentino::Core::ContributionLoading::ErrorHandlerBase
      {
         //additional
      private:
         typedef std::list<Trentino::Core::ContributionLoading::Error> ErrorList;
         typedef std::list<Trentino::Core::ContributionLoading::Warning> WarningList;

         //services
      public:         
         virtual void issueError( Trentino::Core::ContributionLoading::Error error
                                 , const std::string&);
         virtual void issueWarning( Trentino::Core::ContributionLoading::Warning warning
                                  , const std::string&);
         unsigned int countErrorIssued(Trentino::Core::ContributionLoading::Error error) const;
         unsigned int countWarningIssued(Trentino::Core::ContributionLoading::Warning warning) const;     

         //data
      private:
         ErrorList mErrorHistory;
         WarningList mWarningHistory;
      }; //class CollectingErrorHandler  

      //services
   public:
      static void SetUpTestCase();
      static void TearDownTestCase();

      //management
   protected:      
      virtual void SetUp();
      virtual void TearDown(); 
      
   protected:
      //*******************************************************************************************
      //! \name helper functions
      //! @{
      //*******************************************************************************************

      //*******************************************************************************************
      //                                   deployedCompositesCount()
      //*******************************************************************************************
      //! \brief Returns the number of composites having the Composite::Deployed state in the
      //!        given contribution.
      //!
      //! The function counts also composites that are used as implementation.
      //! \param[in] contribution A shared pointer to the contribution. 
      //! \return The total number of composites having the Composite::Deployed state.
      //*******************************************************************************************
      static unsigned int deployedCompositesCount(
         const Trentino::RuntimeModel::ConstContributionPtr& contribution);

      //*******************************************************************************************
      //                              deployableDeployedCompositesCount()
      //*******************************************************************************************
      //! \brief Returns the number of \b deployable composites that were put in the 
      //!        Composite::Deployed state;
      //!
      //! Contrary to deployedCompositesCount(), this function doesn't count composites used as 
      //! implementation. 
      //! \param[in] contribution A shared pointer to the contribution. 
      //! \return The number of deployable composites having the Composite::Deployed state.
      //*******************************************************************************************
      static unsigned int deployableDeployedCompositesCount(
         const Trentino::RuntimeModel::ConstContributionPtr& contribution);

      //*******************************************************************************************
      //                                 deployableCompositesCount()
      //*******************************************************************************************
      //! \brief Returns the number of deployable composites in the given contribution.
      //!      
      //! \param[in] contribution A shared pointer to the contribution. 
      //! \return The numnber of deployable composites;
      //*******************************************************************************************
      static unsigned int deployableCompositesCount(
         const Trentino::RuntimeModel::ConstContributionPtr& contribution);      
      //! @}

      //data
   protected:
      Booter mBooter;
      Booter::BootPtr mApp;
      Trentino::Core::ContributionLoading::ContributionLoaderPtr mContributionLoader;
      boost::shared_ptr<CollectingErrorHandler> mCollectingErrorHandler;
   }; // class ContributionLoaderBaseTest

} //namespace Trentino
} //namespace Tests
} //namespace Core
