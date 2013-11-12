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

#ifndef TrentinoConsoleCommandInfoH
#define TrentinoConsoleCommandInfoH

//baseclass
#include "TrentinoConsoleContextAccessingCommand.h"

//standard
#include <map>
#include <vector>

//specific
#include "../Runtime/TrentinoManagementInterface.h"

namespace Trentino {
namespace Console
{
   class ContextAccessor;

   //**********************************************************************************************
   //                                      CommandInfo
   //**********************************************************************************************
   //! \class CommandInfo
   //! \brief Info command class declaration
   //!
   //! This command retrieves an information about installed artifacts
   //**********************************************************************************************
   class CommandInfo : public ContextAccessingCommand
   {
      //additional
   public:
      //*******************************************************************************************
      //                                       CommandArgs
      //*******************************************************************************************
      //! \struct CommandArgs
      //! \brief Data structure to store information about arguments passed to the command
      //!   This structure is filled by parser and later used to manage command control flow.
      //! 
      //! \var getContributions Indicates that information about contributions was requested 
      //! \var getContributionSate Indicates that contribution states were requested
      //! \var getComponents Indicated that information about components was requested
      //! \var getComponent Indicated that information about a single component was requested
      //! \var getComponentState Idicated that component state were requested
      //! \var etServices Indicates that information about services was requested  
      //! \var getReferences Indicares that information about references was requested 
      //! \var getAttributes Indicates that attributes were requested 
      //! \var getServiceState Indicates that service states were requested 
      //! \var getReferenceState Indicates that reference states were requested 
      //! \var getReferenceTargets Indicates that reference targets were requested 
      //! \var getProperties Indicates that properties were requested 
      //! \var searchDepth Depth of nesting of artifacts to be processed
      //! \var path URI-style link to an artifact to be requested
      //*******************************************************************************************
      struct CommandArgs
      {
         //construction
         CommandArgs()            
            : getContributions(false)
            , getContributionState(false)
            , getComponents(false)            
            , getComponentState(false)
            , getServices(false)
            , getReferences(false)
            , getAttributes(false)
            , getServiceState(false)
            , getReferenceState(false)
            , getReferenceTargets(false)
            , getProperties(false)
            , searchDepth(1)
         {}

         //data
         bool getContributions;
         bool getContributionState;
         bool getComponents;         
         bool getComponentState;
         bool getServices;
         bool getReferences;
         bool getAttributes;
         bool getServiceState;
         bool getReferenceState;
         bool getReferenceTargets;
         bool getProperties;
         int searchDepth;
         std::string URI;
      }; //struct CommandArgs

      //! Artifact attributes stored in format: uri -> value
      typedef std::map< std::string, std::string > Attributes;
      //! A set of services of the component
      typedef std::vector<std::string> Services;
      //! A set of references of the component
      typedef std::vector<std::string> References;
      //! \brief States of the group of artifacts (services, references, components) 
      //! stored in format: artifactName -> state
      typedef std::map< std::string, std::string > States;
      //! \brief A set of targets for a group of references stored in format: 
      //! referenceName -> (target1, target2, ...)
      typedef std::map< std::string, std::vector<std::string> > Targets;
      //! A set of property names
      typedef std::vector<std::string> Properties;
      //! \brief A set of values for a group of properties stored in format: 
      //! propertyName -> (value1, value2, value3, ...)
      typedef std::map< std::string, std::vector<std::string> > PropertiesValues;
      //!An attributes for a group of artifacts (services, references, components, properties)
      //! stored in format: artifactName -> attributes
      typedef std::map< std::string, Attributes > GroupAttributes;

      //*******************************************************************************************
      //                                    SCAComponent
      //*******************************************************************************************
      //! \struct SCAComponent
      //! \brief This struct intended to store the SCDL information in string format for a single
      //!   component. Later, after execution is completed, such a struct will be passed to an
      //!   output visitor, which will parse it and send toward the final output.
      //!
      //! \var uri A uri of the component this structure represents
      //! \var attributes A set of attributes for this component
      //!
      //! \var references A names of references in this component
      //! \var referencesStates A states for all the references in this component
      //! \var referencesTargets All the targets for the references in this component
      //! \var referencesAttrs An attributes for the references in this component
      //!
      //! \var services A names of services in this component
      //! \var servicesStates A states for all the services in this component
      //! \var servicesAttrs An attributes for the services in this component
      //!
      //! \var properties A names of properties in this component
      //! \var propValues A values for all the properties in this component
      //! \var propAttrs The attributes for all the properties in this component
      //!
      //! \todo Not all the artifact-types are currently supported
      //*******************************************************************************************
      struct SCAComponent
      {
         //data
         std::string uri;
         std::string state;
         Attributes attributes;

         References references;
         States referencesStates;
         Targets referencesTargets;
         GroupAttributes referencesAttrs;

         Services services;
         States servicesStates;
         GroupAttributes servicesAttrs;

         Properties properties;
         PropertiesValues propValues;
         GroupAttributes propAttrs;
      }; //struct SCAComponent

      
      //*******************************************************************************************
      //                                   Output
      //*******************************************************************************************
      //! \struct Output
      //! \brief Represents the output of the CommandInfo command.
      //!
      //! Only one of the members: components, contributionBaseURIs, contributionState and 
      //! contributionStates is supposed to be set by CommandInfo after execution. Which of the 
      //! mebers contains valid content can be retrievied via the availableOutput member. 
      //*******************************************************************************************
      struct Output
      {
         enum AvailableOutput{ Components
                             , ContributionDatas
                             ,ContributionData};
         
         AvailableOutput availableOutput;
         std::vector<SCAComponent> components;
         Trentino::ManagementInterface::ContributionDatas contributionDatas;
      };

      //construction
   public:
      CommandInfo(const CommandArgs& commandArgs, const ContextAccessor& contextAccessor);

      //inherited services, see description in the parent class declaration
   public:
      void execute();
      void acceptOutputVisitor(OutputVisitor& v);

      //services
   public:
      //*******************************************************************************************
      //                                     getOutput()
      //*******************************************************************************************
      //! \brief Return the information retrieved from the runtime part
      //*******************************************************************************************
      const Output& getOutput() const;
       
      //*******************************************************************************************
      //                                  commandParameters()
      //*******************************************************************************************
      //! \brief Return command arguments passed by the user in a prompt
      //! \return Filled structure with parameters
      //*******************************************************************************************
      CommandArgs commandArgs() const;

      //data
   private:
      //*******************************************************************************************
      //                                    mCommandParameters
      //*******************************************************************************************
      //! \brief Structure to store filled CommandArgs one
      //*******************************************************************************************
      CommandArgs mCommandArgs;

      //*******************************************************************************************
      //                                       mOutput
      //*******************************************************************************************
      //! \brief Datastructre representing the output of the command
      //*******************************************************************************************
      Output mOutput;

   }; //class CommandInfo

   #include  "TrentinoConsoleCommandInfo.inl"

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleCommandInfoH