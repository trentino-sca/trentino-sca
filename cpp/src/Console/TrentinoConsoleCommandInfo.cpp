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
#include "TrentinoConsoleCommandInfo.h"

//standard
#include <boost/foreach.hpp>

//specific
#include "../Runtime/TrentinoManagementInterface.h"
#include "TrentinoConsole.h"
#include "TrentinoConsoleContextAccessor.h"
#include "TrentinoConsoleOutputVisitor.h"

using Trentino::Console::CommandInfo;
using Trentino::Console::ContextAccessor;
using Trentino::Console::ContextAccessingCommand;
using namespace std;

//class CommandInfo
//construction
CommandInfo::CommandInfo(const CommandArgs& commandArgs, const ContextAccessor& contextAccessor)
: ContextAccessingCommand(contextAccessor)
, mCommandArgs(commandArgs)
{}

//services
void CommandInfo::acceptOutputVisitor(Trentino::Console::OutputVisitor& visitor)
{
   visitor.visitCommandInfo(this);
}

void CommandInfo::execute()
{  
   Trentino::ManagementInterface* const iface =
      contextAccessor().managementInterface();
   if(!iface)
   {
      setErrorMessage(Trentino::Console::Errors::ManagementInterfaceNotAvailable);
      return;
   }

   SCAComponent newComponent;
   const string& uri = commandArgs().URI;   

   if(commandArgs().getContributions)
   {
      if(uri.empty()) //get information about all contributions
      {
         mOutput.contributionDatas = iface->getContributions();
         mOutput.availableOutput = Output::ContributionDatas;     
      }
      else //get information about the contribution with the given URI
      {
         //The only retrievable information about a contribution so far, is its state.
         //So even if commandArgs().getContributionState is not specified, retrieve the
         //state nevertheless.
      Trentino::ManagementInterface::ContributionData data =iface->getContribution(commandArgs().URI);
         if(data.empty())
         {
            setErrorMessage("Contribution with the base URI '" + commandArgs().URI + "' not found");
            return;
         }
         mOutput.contributionDatas.push_back(data);
         mOutput.availableOutput = Output::ContributionData;         
      }

      return;
   }
   else if (commandArgs().getComponents) //Request components list
   {  
      vector<string> componentURIs;
      if(uri.empty())
      {
         componentURIs = iface->getDomainLevelComponents();
      }
      else
      {
         //here uri represents a contribution base uri
         
         //! \todo This is a bad way to determine whether a contribution with the given URIs exists
         //!       Unfortunately the return value of ManagementInterface::getComponents() is not
         //!       able to report an error.
         if(iface->getContribution(uri).empty())
         {
            setErrorMessage("Contribution with the base URI '" + uri + "' not found");
            return;
         }
         componentURIs = iface->getComponents(uri);
      }
      
      BOOST_FOREACH(string componentURI, componentURIs)
      {
         newComponent.uri = componentURI;
         if(commandArgs().getComponentState)
         {
            //! \todo introduce a getComponentStates() method to get component states at onece
            newComponent.state = iface->getComponentState(componentURI);
         }

         mOutput.components.push_back(newComponent);
      }
      
      mOutput.availableOutput = Output::Components;
      
      //We've already filled output vector, so return here to avoid push_back in the end of function
      return;
   }
   else if (uri.find("#service") != uri.npos)
   {      
      //! \todo This is a bad way to determine whether a service with the given URIs exists.
      //!       Unfortunately there is not way in the ManagementInterface to retrieve information
      //!       or error messages about the existence of a service
      const string serviceState = iface->getServiceState(uri);
      if(serviceState.empty())
      {     
         setErrorMessage("Service with URI '" + uri + "' not found");
         return;
      }
      
      size_t pos = uri.find_last_of("(");
      string name = uri.substr(pos + 1);
      pos = name.find_last_of(")");
      name = name.substr(0, pos);
      newComponent.services.push_back(name);

      //get attributes
      if (commandArgs().getAttributes)
         newComponent.servicesAttrs[name] = iface->getAttributes(uri);

      //get state
      if (commandArgs().getServiceState)
         newComponent.servicesStates[name] = serviceState;
   }
   else if (uri.find("#reference") != uri.npos)
   {
      //! \todo This is a bad way to determine whether a reference with the given URIs exists.
      //!       Unfortunately there is not way in the ManagementInterface to retrieve information
      //!       or error messages about the existence of a reference.
      const string referenceState = iface->getReferenceState(uri);
      if(referenceState.empty())
      {     
         setErrorMessage("Reference with URI '" + uri + "' not found");
         return;
      }
      size_t pos = uri.find_last_of("(");
      string name = uri.substr(pos + 1);
      pos = name.find_last_of(")");
      name = name.substr(0, pos);
      newComponent.references.push_back(name);

      //get attributes
      if (commandArgs().getAttributes)
         newComponent.referencesAttrs[name] = iface->getAttributes(uri);

      //get state
      if (commandArgs().getReferenceState)
         newComponent.referencesStates[name] = iface->getReferenceState(uri);

      //get targets
      if (commandArgs().getReferenceTargets)
         newComponent.referencesTargets[name] = iface->getReferenceTargets(uri);
   }
   else if(uri.find("#property") != uri.npos)
   {
      size_t pos = uri.find_last_of("(");
      string propertyName = uri.substr(pos + 1);
      pos = propertyName.find_last_of(")");
      propertyName = propertyName.substr(0, pos);
      newComponent.properties.push_back(propertyName);
      
      //! \todo This is a bad way to determine whether a property with the given URIs exists.
      //!       Unfortunately there is not way in the ManagementInterface to retrieve information
      //!       or error messages about the existence of properties.
      //-------
      string componentUri = uri;
      componentUri.erase(uri.find_last_of("#"));

      const ManagementInterface::PropertiesNames propertiesNames = 
         iface->getPropertiesNames(componentUri);     

      if( find(propertiesNames.begin(), propertiesNames.end(), propertyName) ==
            propertiesNames.end() )
      {
         setErrorMessage("Property with URI '" + uri + "' not found");
         return;
      }
      //-------

      //get properties values
      newComponent.propValues[propertyName] = iface->getPropertyValues(uri);

      //get properties attributes
      if (commandArgs().getAttributes && (commandArgs().searchDepth > 1))
         newComponent.propAttrs[propertyName] = iface->getAttributes(uri);      
   }
   else // it's a component
   {  
      //! \todo This is a bad way to determine whether a component with the given URIs exists
      //!       Unfortunately there is not way in the ManagementInterface to retrieve information
      //!       or error messages about the existence of a component
      const string componentState = iface->getComponentState(uri);
      if(componentState.empty())
      {     
         setErrorMessage("Component with URI '" + uri + "' not found");
         return;
      }

      newComponent.uri = uri;

      if(commandArgs().getComponentState)
      {
         newComponent.state = componentState;
      }

      //get attributes
      if (commandArgs().getAttributes)
         newComponent.attributes = iface->getAttributes(uri);

      //get references
      if (commandArgs().getReferences)
      {
         newComponent.references = iface->getReferences(uri);

         BOOST_FOREACH(const string& reference, newComponent.references)
         {
            //get references attributes
            if (commandArgs().getAttributes && (commandArgs().searchDepth > 1))
               newComponent.referencesAttrs[reference] = iface->getAttributes(uri + "#reference(" + reference + ")");

            //get references states
            if (commandArgs().getReferenceState)
               newComponent.referencesStates[reference] = iface->getReferenceState(uri + "#reference(" + reference + ")");

            //get references targets
            if (commandArgs().getReferenceTargets)
               newComponent.referencesTargets[reference] = iface->getReferenceTargets(uri + "#reference(" + reference + ")");
         }
      }

      //get services
      if (commandArgs().getServices)
      {
         newComponent.services = iface->getServices(uri);

         BOOST_FOREACH(const string& service, newComponent.services)
         {
            //get services attributes
            if (commandArgs().getAttributes && (commandArgs().searchDepth > 1))
               newComponent.servicesAttrs[service] = iface->getAttributes(uri + "#service(" + service + ")");

            //get services states
            if (commandArgs().getServiceState)
               newComponent.servicesStates[service] = iface->getServiceState(uri + "#service(" + service + ")");
         }
      }

      //get properties
      if (commandArgs().getProperties)
      {
         newComponent.properties = iface->getPropertiesNames(uri);

         BOOST_FOREACH(const string& prop, newComponent.properties)
         {
            //get properties values
            newComponent.propValues[prop] = iface->getPropertyValues(uri + "#property(" + prop + ")");

            //get properties attributes
            if (commandArgs().getAttributes && (commandArgs().searchDepth > 1))
               newComponent.propAttrs[prop] = iface->getAttributes(uri + "#property(" + prop + ")");
         }
      }
   }

   mOutput.components.push_back(newComponent);
   mOutput.availableOutput = Output::Components;
}