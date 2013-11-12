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
#ifndef TrentinoBindingBindingManagerBaseH
#define TrentinoBindingBindingManagerBaseH

//specific
#include <string>
#include "TrentinoBindingTrentinoBinding.h"
#include "../RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../SCAModel/TrentinoSCAModelMetadata.h"

using namespace Trentino::SCA::Model;
using namespace std;

namespace Trentino{
   namespace Binding{
      //class declaration
      //**********************************************************************************************
      //                             BindingManagerBase                             
      //**********************************************************************************************
      //! \ingroup TrentinoBinding
      //! \brief The BindingmanagerBase is the central services that manages bindings
      //! it can load bindings, start and stp them. It can read binding configurations.
      //! it is supposed to be unique and therefore Thread safe
      //**********************************************************************************************
      class BindingManagerBase 
      { 
      //services
      public:
         // virtual TrentinoBindingrPtr& getBindingById(const std::string& bindingId) = 0;
         // virtual void removeBinding(const std::string& bindingId)= 0;


         //*******************************************************************************************
         //                              createBinding()
         //*******************************************************************************************
         //! \brief tell the BindingManager to create the service with the given Id
         //! The binding manager separate the steps for creating a Binding and starting it
         //*******************************************************************************************
         virtual void createBinding( const std::string& bindingId) = 0;

         //*******************************************************************************************
         //                              startBinding()
         //*******************************************************************************************
         //! \brief start a given Binding
         //*******************************************************************************************
         virtual void startBinding( const std::string& bindingId) =0;

         //*******************************************************************************************
         //                              loadDefaultBindingContext()
         //*******************************************************************************************
         //! \brief load the default Binding Context
         //*******************************************************************************************
         virtual const TrentinoBindingContextPtr& loadDefaultBindingContext( const std::string& bindingId ) =0;

         //****************************************************************************************************
         //                                         onDeploy()
         //****************************************************************************************************
         //! \brief called when a contribution is being deployed by the Contribution loader.
         //! \param const RuntimeModel::ContributionPtr & contribution: the contribution 
         //! \return bool: return true if no errors occured during the hanlding process
         //****************************************************************************************************
         virtual bool onDeploy(const Trentino::RuntimeModel::ContributionPtr& contribution) =0;

         //****************************************************************************************************
         //                                         stop()
         //****************************************************************************************************
         //! \brief stop the binding layer
         //****************************************************************************************************
         virtual void stop()=0;
         
         //****************************************************************************************************
         //                                         getServiceMetadata()
         //****************************************************************************************************
         //! \brief Returns binding-specific metadata for a service.
         //! \param string bindingId: binding identifier, if left empty all bindings are assumed
         //! \param Trentino::RuntimeModel::ServiceBasePtr service: pointer to a service (services may have
         //!  different metadata values within a binding)
         //! \return boost::shared_ptr<Metadata>: service metadata as a collection of key - value pairs
         //****************************************************************************************************
         virtual boost::shared_ptr<Metadata> getServiceMetadata(string bindingId, Trentino::RuntimeModel::ServiceBasePtr service) =0;

         //****************************************************************************************************
         //                                         getServiceUri()
         //****************************************************************************************************
         //! \brief Returns URI of a service from given metadata.
         //! \param string bindingId: binding identifier, if left empty default binding (binding.sca) is assumed
         //! \param metadata: set of metadata holding values for URI construction
         //! \return string service URI for given binding, empty string in case of error
         //****************************************************************************************************
         virtual std::string getServiceUri(string bindingId, Metadata & metadata) = 0;

         }; //class BindingManagerBase

      static const char* fakeDiscoveryURI = "tcp://localhost:1234//dontUseThisName_FakeTarget";
      //****************************************************************************************************
      //                                         isFakeUri()
      //****************************************************************************************************
      //! \brief Returns if the given URI is a fake (meaning that there is no URI and discovery
      //! shall be triggered)
      //****************************************************************************************************
      inline bool isFakeUri(const char* uri)
      {
         if (!strcmp(uri, fakeDiscoveryURI))
         {
            return true;
         }
         else
         {
            return false;
         }

   }//namespace Binding
}//namespace Trentino



}

#endif  //TrentinoBindingBindingManagerBaseH
