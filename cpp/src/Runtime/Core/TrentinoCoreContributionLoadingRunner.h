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


#ifndef TrentinoCoreContributionLoadingRunnerH
#define TrentinoCoreContributionLoadingRunnerH

//baseclass
#include "TrentinoCoreContributionLoadingErrorReporter.h"

//specific
#include "../RuntimeModel/TrentinoRuntimeModel.h"

namespace Trentino{
namespace Core{
namespace ContributionLoading
{
   //**********************************************************************************************
   //                                       Runner 
   //**********************************************************************************************
   //! \ingroup ContributionLoading
   //! \brief Responsible for putting a contribution into the 
   //!        RuntimeModel::Contribution::Running state. 
   //!
   //! For clients, it's not necessary no use the Runner class directly, instead its  
   //! functionality is provided through the facade class ContributionLoader.  
   //**********************************************************************************************
   class Runner : public ErrorReporter
   {
      //construction
   public:
      //*******************************************************************************************
      //                                      Runner()
      //*******************************************************************************************
      //! \brief Empty constructor.      
      //*******************************************************************************************
      Runner();

      //*******************************************************************************************
      //                                      -Runner()
      //*******************************************************************************************
      //! \brief Empty destructor.      
      //*******************************************************************************************
      ~Runner();
   private:
      //*******************************************************************************************
      //                               Runner(const Runner&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copying.      
      //*******************************************************************************************
      Runner(const Runner&);

      //operators
   private:
      //*******************************************************************************************
      //                                      operator=()
      //*******************************************************************************************
      //! \brief Disallow inadvertent assignment.      
      //*******************************************************************************************
      void operator=(const Runner&);

      //services
   public:
      //*******************************************************************************************
      //                                         run()
      //*******************************************************************************************
      //! \brief Instantiates all the \c \@eagerInit="true" component implementations in the 
      //!        contribution.
      //!
      //! run() iterates over all the deployable composites in the contribution and tries to 
      //! instantiate all of the contained \c \@eagerInit="true" component implementations. If
      //! no error occurs, the corresponding composite is assigned the 
      //! RuntimeModel::Composite::Running state. If a component is implemented by a composite,
      //! run() first tries to run the implementing composite, thus performing a recursive descent.
      //! If at <em>least one</em> of the deployable composites could be run, the whole  
      //! contribution is assigned the RuntimeModel::Contribution::Running state. 
      //! 
      //! As soon as a component implementation (\c \<implementation.cpp\> is instantiated, 
      //! dependency injection is performed on that instance: property values and dependent
      //! service instances are injected. 
      //!
      //! \param[in] contribution Shared pointer to the contribution to run. 
      //! \throw std::invalid_argument In case the given contribution is not in the 
      //!        RuntimeModel::Contribution::Deployed state.
      //! \throw std::runtime_error In case none of the deployable composites in the contribution
      //!        could be run.
      //*******************************************************************************************
      void run(const Trentino::RuntimeModel::ContributionPtr& contribution);

      //*******************************************************************************************
      //                                         stop()
      //*******************************************************************************************
      //! \brief Destroys all the currently available component implementation instances in the 
      //!        contribution.
      //! 
      //! stop() iterates over all the deployable composites in the contribution and destroyes
      //! all of the currently available component implementation instances. After all components
      //! in a composite have been processed, the corresponding composite is assigned the 
      //! RuntimeModel::Composite::Deployed state. If a component is implemented by a composite,
      //! stop() first processes the implementing composite, thus performing a recursive descent.
      //! While the implementation instances of a component are destroyed, the component is 
      //! assigned the temporary RuntimeModel::Component::Stopping state. Once the destruction is
      //! finished the previous state of the component is restored. Finally, the contribution is
      //! assigned the RuntimeModel::Contribution::Deployed state.
      //!
      //! \param[in] contribution Shared pointer to the contribution to stop. 
      //! \throw std::invalid_argument In case the given contribution is not in the 
      //!        RuntimeModel::Contribution::Running state.
      //!
      //! \attention stop() blocks until all of the component implementation instances currently
      //!            in use have been released. An instance is regularly released only if a 
      //!            service invocation targeting this instance regularly returns, what in turn
      //!            happens only if the corresponding business logic service method returns. 
      //!            In other words: stop() relies on a cooperative behavior of the business 
      //!            logic and could hang forever if a service implementation hangs. See also
      //!            Trentino::Core::ComponentCPPImplementationManager::onRemove().
      //*******************************************************************************************
      void stop(const Trentino::RuntimeModel::ContributionPtr& contribution);

   }; //class Runner

} //namespace ContributionLoading
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreContributionLoadingRunnerH