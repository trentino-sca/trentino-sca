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
#include "TrentinoCoreContributionLoadingRunner.h"

//standard
#include <stdexcept>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>

//specific
#include "TrentinoCoreContributionLoading.h"
#include "TrentinoCoreContributionLoadingErrorHandlerBase.h"
#include "TrentinoCoreComponentImplementationManagerBase.h"
#include "../RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../RuntimeModel/TrentinoRuntimeModelCommonFuncs.h"
#include "../SCAModel/TrentinoSCAModelComponent.h"
#include "../SCAModel/TrentinoSCAModelImplementation.h"
#include "../XML/TrentinoXMLSchemaQName.h"
#include "TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "../../Utils/TrentinoUtilsLogging.h"
#include "../../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"

using namespace std;
using namespace Trentino;
using Trentino::Core::ContributionLoading::Runner;
namespace ContributionLoading = Trentino::Core::ContributionLoading;

namespace
{
   //**********************************************************************************************
   //                                       runComposite()
   //**********************************************************************************************
   //! \brief Instantiates \c \@eagerInit="true" component implementations for all the components 
   //!        in the given composite. 
   //!
   //! If a component is implemented by a composite, runComposite() first tries to process the 
   //! implementing composite, thus performing a recursive descent. If no error occurs, the 
   //! composite is assigned the Trentino::RuntimeModel::Composite::Running state. 
   //! 
   //! \param[in] composite A shared pointer to the composite to be processed. 
   //! \sa Trentino::Core::ContributionLoading::Runner::run()
   //**********************************************************************************************
   void runComposite(const RuntimeModel::CompositePtr& composite)
   {
      HLOGGER();   
      HLOGGER_INFO(composite->qName().toString().c_str());

      assert(composite->state() == RuntimeModel::Composite::Deployed);
      Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
      Trentino::Core::ComponentImplementationManagerBasePtr componentImplementationManager = booter.componentImplementationManager();
   
      BOOST_FOREACH(const RuntimeModel::ConstComponentPtr& component, composite->components())
      {
         if( (component->state() != RuntimeModel::Component::Resolved) && (component->state() != RuntimeModel::Component::OptionalUnresolved)){
            logWarn("Skipping component with unresolved state %s",component->scaComponent()->name().c_str());
            continue;
            }
         if(component->scaComponent()->implementationElement()->xsdType() ==
               ContributionLoading::XSDTypeImplementationComposite)
         {
            const RuntimeModel::CompositePtr implComposite = 
               boost::dynamic_pointer_cast<RuntimeModel::Composite>(component->implementation());
            assert(implComposite);
         
            runComposite(implComposite);         
         }
         else
         {
            //! \todo Might throw: delete the instances instantiated so far
            try
            {
            componentImplementationManager->onInit(component);
            }
            catch(...)
            {
               throw;
            }
         }       
      }

      composite->setState(RuntimeModel::Composite::Running);
   }

   //forward declaration
   void destroyComponentInstances(const RuntimeModel::ComponentPtr& component);
   
   
   //**********************************************************************************************
   //                            destroyComponentInstancesInComposite()
   //**********************************************************************************************
   //! \brief Calls destroyComponentInstances() for each component in the given composite.
   //!
   //! Finally, the composite is assigned the Trentino::RuntimeModel::Composite::Deployed state.   
   //! 
   //! \param[in] composite A shared pointer to the composite to be processed. 
   //! \sa Trentino::Core::ContributionLoading::Runner::stop()
   //**********************************************************************************************
   void destroyComponentInstancesInComposite(const RuntimeModel::CompositePtr& composite)
   {
      for_each( composite->components().begin()
              , composite->components().end()
              , boost::bind(destroyComponentInstances, _1) );

      composite->setState(RuntimeModel::Composite::Deployed);
   }

   //**********************************************************************************************
   //                                destroyComponentInstances()
   //**********************************************************************************************
   //! \brief Destroys all the currently available component implementation instances for the 
   //!        given component.
   //!
   //! If a component is implemented by a composite, the implementing composite is processed first,
   //! thus a recursive descent is performed. While the implementation instances of a component are 
   //! destroyed, the component is assigned the temporary 
   //! Trentino::RuntimeModel::Component::Stopping state. Once the destruction is finished, the 
   //! previous state of the component is restored.   
   //! 
   //! \param[in] component A shared pointer to the component to be processed. 
   //! \sa Trentino::Core::ContributionLoading::Runner::stop()
   //**********************************************************************************************
   void destroyComponentInstances(const RuntimeModel::ComponentPtr& component)
   {
      assert(component);
      assert(component->state() != RuntimeModel::Component::Initial);
      //a component that is currently being resolved MUST NOT be unwired
      assert(component->state() != RuntimeModel::Component::Resolving);   
   
      //save the component's state
      const RuntimeModel::Component::State savedComponentState = 
         component->state();

      //[1] Set the component's state to Stopping in order to prevent new invocations to be
      //    directed to the component's implementation instances. Currently it's not needed for
      //    components implemented by composites, but we do it for state consistency.
      if(component->state() != RuntimeModel::Component::Stopping)
      {  
         boost::lock_guard<boost::recursive_mutex> componentLock(component->mutex());
         component->setState(RuntimeModel::Component::Stopping);
      }

      if( component->scaComponent()->implementationElement()->xsdType() == 
            ContributionLoading::XSDTypeImplementationComposite )
      {
         const RuntimeModel::CompositePtr implComposite = 
               boost::dynamic_pointer_cast<RuntimeModel::Composite>(component->implementation());
         assert(implComposite);
         destroyComponentInstancesInComposite(implComposite);
      }
      else if( component->scaComponent()->implementationElement()->xsdType() == 
               ContributionLoading::XSDTypeImplementationCPP )

      {
         //[2] Wait until all the invocations currently taking place are finished
      Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
      Trentino::Core::ComponentImplementationManagerBasePtr componentImplementationManager = booter.componentImplementationManager();
         //blocks until all the implementation instances are released and destroyed
         componentImplementationManager->onRemove(component); 
      }
      else
      {
         assert(false);
      }

      //restore component's state
      boost::lock_guard<boost::recursive_mutex> componentLock(component->mutex());
      component->setState(savedComponentState);
   }

} //namespace 


//class Runner
   //construction
Runner::Runner()
{}

Runner::~Runner()
{}

   //services
void Runner::run( const RuntimeModel::ContributionPtr& contribution )
{
   logInfo("running contribution '%s'...", contribution->baseURI().c_str() );
   HLOGGER();   
   HLOGGER_INFO(contribution->baseURI().c_str());

   if(contribution->state() != RuntimeModel::Contribution::Deployed)
   {
      throw invalid_argument( 
         "Cannot run a contribution that is not in '" + 
         RuntimeModel::CommonFuncs::toString( RuntimeModel::Contribution::Deployed ) + 
         "' state." );
   }
         
   BOOST_FOREACH(const RuntimeModel::CompositePtr& composite, contribution->composites())
   {
      //process only deployable composites that are also deployed
      if(composite->isDeployable() && composite->state() == RuntimeModel::Composite::Deployed)
      { 
         try
         {
            runComposite(composite);            
         }
         catch(exception& e)
         {
            const string errorMsg = 
               "composite with QName '" + composite->qName().toString() + 
               "' could not be run due to the following error: " + e.what();
            
            assert(errorHandler());
            errorHandler()->issueError(ContributionLoading::CompositeNotRunError, errorMsg);
            HLOGGER_EXCEPTION(e.what());
         }
         catch(...)
         {
            throw;
         }
      }
   }

   const unsigned int runComposites = 
      count_if( contribution->composites().begin()
              , contribution->composites().end()
              , boost::bind(&RuntimeModel::Composite::isDeployable, _1) == true &&
                boost::bind(&RuntimeModel::Composite::state, _1) == 
                  RuntimeModel::Composite::Running);              

   if(runComposites == 0)
   {      
      throw runtime_error(
         "None of the deployable composites in contribution '" + contribution->baseURI() +
         "' could be run");         
   }
   
   contribution->setState(RuntimeModel::Contribution::Running);
   logInfo("contribution '%s' runs!", contribution->baseURI().c_str() );
}

void Runner::stop( const RuntimeModel::ContributionPtr& contribution )
{
   if( contribution->state() != RuntimeModel::Contribution::Running )
   {
      throw invalid_argument( 
         "Cannot stop a contribution that is in '" + 
         RuntimeModel::CommonFuncs::toString( contribution->state() ) + "' state." );
   }

   BOOST_FOREACH(const RuntimeModel::CompositePtr& composite, contribution->composites())
   {
      if(composite->isDeployable())
      {  
         destroyComponentInstancesInComposite(composite);         
      }
   }

   contribution->contributionInfo()->dataRegistry().cleanUp();
   
   contribution->setState(RuntimeModel::Contribution::Deployed);
}
