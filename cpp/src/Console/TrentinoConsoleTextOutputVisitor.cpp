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
#include <algorithm>
#include <boost/bind.hpp>

//header
#include "TrentinoConsoleTextOutputVisitor.h"

//standard
#include <boost/foreach.hpp>

//specific
#include "./../Utils/TrentinoUtilsLogging.h"
#include "TrentinoConsoleCommandBoot.h"
#include "TrentinoConsoleCommandShutdown.h"
#include "TrentinoConsoleCommandInfo.h"
#include "TrentinoConsoleCommandInstall.h"
#include "TrentinoConsoleCommandUpdateh.h"
#include "TrentinoConsoleCommandQuit.h"
#include "TrentinoConsoleCommandRemove.h"
#include "TrentinoConsoleCommandRewire.h"
#include "TrentinoConsoleCommandService.h"
#include "TrentinoConsoleCommandSetProperty.h"

#ifdef LOG4PLUS_LOGGERNAME
   #undef LOG4PLUS_LOGGERNAME
   #define LOG4PLUS_LOGGERNAME "Console"
#endif//LOG4PLUS_LOGGERNAME

using Trentino::Console::TextOutputVisitor;
using namespace Trentino::Console;
using namespace std;

const string ProgramName = "TrentinoConsole";
const string Line = "----------------------------------------------------------------------";
const string Prompt = "Trentino> "; 
const string ErrorString = "Error: ";

const string Indent0x = "";
const string Indent = "    ";
const string lnfd = "\n";
const string Indent2x = Indent + Indent;
const string Indent3x = Indent + Indent + Indent;
const string Indent4x = Indent + Indent + Indent + Indent;

//construction
TextOutputVisitor::TextOutputVisitor()
{
   
}

//*************************************************************************************************
// aids functions for the visitCommandInfo()
//*************************************************************************************************
void TextOutputVisitor::printContribution(const Trentino::ManagementInterface::ContributionDatas data)
{
const char* space ="    ";
Trentino::ManagementInterface::ContributionDatas::const_iterator iter;
for(iter = data.begin(); iter!=data.end();++iter){
   const Trentino::ManagementInterface::ContributionData aData = *iter;
   std::string& uri = aData.getString("baseURI");
   *this <<"-----------------------------------------------------------------------"<<lnfd;
   *this << "[contribution]: " << uri << " "<<lnfd;
   int state =  aData.getInt("state");
   std::string strState("None");
   switch (state)
      {
      case 1:
         strState="Installed";
      case 2:
         strState="Deployed";
      case 3:
         strState="Running";
      default:
         break;
      }
     *this << space << "State: "<< strState << lnfd;
     *this << space << "Version: "<< aData.getString("version") << lnfd;
     *this <<"-----------------------------------------------------------------------"<<lnfd;

   }


}

void TextOutputVisitor::printAttributes(const CommandInfo::Attributes& attrs, 
   const string& extraIndent)
{
   *this << extraIndent << "[attributes]:" << lnfd;

   CommandInfo::Attributes::const_iterator it;
   for (it = attrs.begin(); it != attrs.end(); ++it)
   {
      *this << extraIndent << Indent << it->first << " = " << it->second << lnfd;
   }
}

void TextOutputVisitor::printProperties(const CommandInfo::SCAComponent& component, 
   const string& extraIndent)
{
   *this << extraIndent << "[properties]:" << lnfd;

   BOOST_FOREACH(const string& prop, component.properties)
   {
      *this << extraIndent << Indent << prop;

      const CommandInfo::PropertiesValues& propertyValues = component.propValues;
      CommandInfo::PropertiesValues::const_iterator values = propertyValues.find(prop);
      if ((values != propertyValues.end()) && (!values->second.empty()))
      {
         *this << " ( ";
         BOOST_FOREACH(const string& value, values->second)
         {
            *this << "'" << value << "' ";
         }
         *this << ")";
      }
      *this << lnfd;

      const CommandInfo::GroupAttributes& groupAttrs = component.propAttrs;
      CommandInfo::GroupAttributes::const_iterator attrs = groupAttrs.find(prop);
      if ((attrs != groupAttrs.end()) && (!attrs->second.empty()))
      {
         printAttributes(attrs->second, extraIndent + Indent2x);
      }
   }
}

void TextOutputVisitor::printReferences(const CommandInfo::SCAComponent& component, 
   const string& extraIndent)
{
   *this << extraIndent << "[references]:" << lnfd;

   BOOST_FOREACH(const string& reference, component.references)
   {
      *this << extraIndent << Indent << reference;

      const CommandInfo::States& referencesStates = component.referencesStates;
      CommandInfo::States::const_iterator state = referencesStates.find(reference);
      if ((state != referencesStates.end()) && (!state->second.empty()))
         *this << " (" << state->second << ")";

      const CommandInfo::Targets& referencesTargets = component.referencesTargets;
      CommandInfo::Targets::const_iterator targets = referencesTargets.find(reference);
      if ((targets != referencesTargets.end()) && (!targets->second.empty()))
      {
         *this << " ->";

         BOOST_FOREACH(const string& target, targets->second)
         {
            *this << " " << target;
         }
      }
      *this << lnfd;

      const CommandInfo::GroupAttributes& groupAttrs = component.referencesAttrs;
      CommandInfo::GroupAttributes::const_iterator attrs = groupAttrs.find(reference);
      if ((attrs != groupAttrs.end()) && (!attrs->second.empty()))
      {
         printAttributes(attrs->second, extraIndent + Indent2x);
      }
   }
}

void TextOutputVisitor::printServices(const CommandInfo::SCAComponent& component, const string& extraIndent)
{
   *this << extraIndent << "[services]:" << lnfd;

   BOOST_FOREACH(const string& service, component.services)
   {
      *this << extraIndent << Indent << service;

      const CommandInfo::States& servicesStates = component.servicesStates;
      CommandInfo::States::const_iterator state = servicesStates.find(service);
      if (state != servicesStates.end())
         *this << " (" << state->second << ")";

      *this << lnfd;

      const CommandInfo::GroupAttributes& groupAttrs = component.servicesAttrs;
      CommandInfo::GroupAttributes::const_iterator attrs = groupAttrs.find(service);
      if ((attrs != groupAttrs.end()) && (!attrs->second.empty()))
      {
         printAttributes(attrs->second, extraIndent + Indent2x);
      }
   }
}
//*************************************************************************************************

//class TextOutputVisitor
//services
void TextOutputVisitor::printIntro() const
{
   *this << Line << lnfd
        << "** " << ProgramName << ", TRENTINO's deployment console" << lnfd
        << "** " << "Copyright (C) Siemens AG, 2012. All rights reserved." << lnfd
        << "** " << "TRENTINO is released under the LGPL License." << lnfd 
        << Line << lnfd;
}

void TextOutputVisitor::printPrompt() const
{
   //*this << Prompt;
   (*this) << Prompt;
}

void TextOutputVisitor::printError(const string& errMessage) const
{
#ifdef TRENTINO_LOGGING
   logError(errMessage.c_str());
#else
   *this << ErrorString << errMessage.c_str() << lnfd;
#endif//TRENTINO_LOGGING
}

void TextOutputVisitor::printUsage() const
{
   *this << "Commands available in this console:" << lnfd
        << Indent << "boot       " 
                  << "- boot the Trentino runtime into the current process" << lnfd
        << Indent << "shutdown   " 
                  << "- unload the Trentino runtime from the current process" << lnfd
        << Indent << "install    " 
                  << "- install, deploy and run a contribution" << lnfd
        << Indent << "update    " 
                  << "- update, update existing contribution to a new version" << lnfd
        << Indent << "remove     " 
                  << "- remove an installed, deployed or running contribution" << lnfd
        << Indent << "info       " 
                  << "- retrieve information about installed entities from the runtime" << lnfd  
        << Indent << "quit, exit " 
                  << "- quit from this console" << lnfd
        << lnfd << "Try commands above with '-h' option for more information" << lnfd;
        
        /*<< Indent << "rewire     " << "- change wiring for a reference" << lnfd
        << Indent << "service    " << "- manage Runtime Windows service state" << lnfd
        << Indent << "set        " << "- set new values for a property" << lnfd
        
        << lnfd*/        
}

void TextOutputVisitor::visitCommandBoot(CommandBoot* cmd)
{
   const string& errorMessage = cmd->errorMessage();

   if(!errorMessage.empty())
   {
      printError(errorMessage);
      return;
   }

   if(cmd->showUsage())
   {
      *this << "Boot the Trentino runtime into the current process." << lnfd
           << "Usage:" << lnfd
           << Indent << "boot [-h]" << lnfd
           << lnfd
           << Indent << "-h    " << "show this message" << lnfd;
      return;
   }

   *this << "> Runtime loaded into the current process" << lnfd;
}

void TextOutputVisitor::visitCommandShutdown(CommandShutdown* cmd)
{
   const string& errorMessage = cmd->errorMessage();

   if(!errorMessage.empty())
   {
      printError(errorMessage);
      return;
   }

   if(cmd->showUsage())
   {
      *this << "Shut down and unload the Trentino runtime from the current process" << lnfd
           << "Usage:" << lnfd
           << Indent << "shutdown [-h]" << lnfd
           << lnfd
           << Indent << "-h    " << "show this message" << lnfd;
      return;
   }

   *this << "> Runtime unloaded from the current process" << lnfd;
}


void TextOutputVisitor::visitCommandInfo(CommandInfo* cmd)
{
   const string& errorMessage = cmd->errorMessage();

   if (!errorMessage.empty())
   {
      printError(errorMessage);
      return;
   }

   if (cmd->showUsage())
   {
      *this << "Retrieve information about installed entities from the runtime." << lnfd;
      *this << "Usage:" << lnfd
           //<< Indent << "info [-h] [-dN] [-s] [-q(b|c|aprs)] URI" << lnfd
           << Indent << "info [-h] [-s] [-q(b|c|rsp)] URI" << lnfd
           << lnfd
           << Indent << "-h    " << "show this message" << lnfd
           /*<< Indent << "-dN   " << "depth of artifacts nested in request, default is N=1" << lnfd*/
           << Indent << "-s    " << "show entities status" << lnfd
           << Indent << "-q    " << "perform a request by using the following specifiers:" << lnfd
           << Indent << "  b   " << "retrieve contributions" << lnfd
           << Indent << "  c   " << "retrieve components" << lnfd           
           /*<< Indent << "  a   " << "retrieve attributes" << lnfd*/
           << Indent << "  p   " << "retrieve properties" << lnfd
           << Indent << "  r   " << "retrieve references" << lnfd
           << Indent << "  s   " << "retrieve services" << lnfd
           << lnfd
           << "URI may be one of the following type: contribution base URI, component, " << lnfd  
           << "reference, service, property. To retrieve a list of all the domain-level " << lnfd
           << "components leave the URI empty. To retrieve as list of installed contributions " << lnfd
           << "leave the URI empty." << lnfd;
      return;
   }

   const CommandInfo::Output& output = cmd->getOutput();

   switch(output.availableOutput)
   {
   case CommandInfo::Output::Components:
      BOOST_FOREACH(const CommandInfo::SCAComponent& component, output.components)
      {
         string extraIndent;

         if (!component.uri.empty())
         {
            *this << "[component]: " << component.uri;
            if(!component.state.empty())
            {
               *this << " (" << component.state << ")" << lnfd;
            }
            else
            {
               *this << lnfd;
            }

            extraIndent = Indent;
         }

         //Print attributes if presented
         if (component.attributes.size())
         {
            printAttributes(component.attributes, extraIndent);
         }

         //Print properties if presented
         if (component.properties.size())
         {
            printProperties(component, extraIndent);
         }

         //Print references if presented
         if (component.references.size())
         {
            printReferences(component, extraIndent);
         }

         //Print services if presented
         if (component.services.size())
         {
            printServices(component, extraIndent);
         }
      } //BOOST_FOREACH(const CommandInfo::SCAComponent& component, output)
      break;
   case CommandInfo::Output::ContributionData:
      printContribution(output.contributionDatas);
      break;
   case CommandInfo::Output::ContributionDatas:
      if(!output.contributionDatas.empty())
      {
      printContribution(output.contributionDatas);
      break;
      }
      else
      {
         *this << "No contributions found" << lnfd;
      }
      break;
   default:
      assert(false);
   } //switch(output.availableOutput)
}

void TextOutputVisitor::visitCommandInstall(CommandInstall* cmd)
{
   const string errorMessage = cmd->errorMessage();

   if (!errorMessage.empty())
   {
      printError(errorMessage);
      return;
   }

   if (cmd->showUsage())
   {
      *this << "Install, deploy and run a new contribution in the domain." << lnfd;
      *this << "Usage:" << lnfd
           << Indent << "install [-h] PathToContribution ContributionBaseURI" << lnfd
           << lnfd
           << Indent << "-h    " << "show this message" << lnfd;
      return;
   }

   if(cmd->commandArgs().doDeploy)
   {
      if(cmd->deployStatus().empty())
      {
         *this << "> Contribution installed, deployed and run!" << lnfd;
      }
      else
      {
         *this << "> Contribution installed, but not deployed or run!" << lnfd;
      }
   }
   else
   {
      *this << "> Contribution installed!" << lnfd;
   }
}


void TextOutputVisitor::visitCommandUpdate(CommandUpdate* cmd)
{
   const string errorMessage = cmd->errorMessage();

   if (!errorMessage.empty())
   {
      printError(errorMessage);
      return;
   }

   if (cmd->showUsage())
   {
      *this << "Update, update contribution to a new version" << lnfd;
      *this << "Usage:" << lnfd
           << Indent << "update [-h] PathToNewContribution ContributionBaseURI" << lnfd
           << lnfd
           << Indent << "-h    " << "show this message" << lnfd;
      return;
   }


   if(!cmd->updateStatus().empty())
   {
      *this << "> "<< cmd->updateStatus()<<lnfd;
   }
   else
   {
      *this << "> Contribution installed, but not deployed or run!" << lnfd;
   }

}
   

void TextOutputVisitor::visitCommandQuit(CommandQuit* /*cmd*/) {}

void TextOutputVisitor::visitCommandRemove(CommandRemove* cmd)
{
   const string errorMessage = cmd->errorMessage();

   if (!errorMessage.empty())
   {
      printError(errorMessage);
      return;
   }

   if (cmd->showUsage())
   {
      *this << "Remove an installed, deployed or running contribution" << lnfd
           << "Usage:" << lnfd
           << Indent << "remove [-h] ContributionBaseURI" << lnfd
           << lnfd
           << Indent << "-h    " << "show this message" << lnfd;
      return;
   }

   *this << "> Removed successfully" << lnfd;
}

void TextOutputVisitor::visitCommandRewire(CommandRewire* cmd)
{
   const string errorMessage = cmd->errorMessage();

   if (!errorMessage.empty())
   {
      printError(errorMessage);
      return;
   }

   if (cmd->showUsage())
   {
      *this << "Rewire a specific reference to a new target." << lnfd
           << "Usage:" << lnfd
           << Indent << "rewire [-h] referenceURI  target  [binding]" << lnfd
           << lnfd
           << Indent << "-h    " << "show this message" << lnfd;
   }

   *this << "> Rewiring completed successfully" << lnfd;
}

void TextOutputVisitor::visitCommandService(CommandService* cmd)
{
   const string errorMessage = cmd->errorMessage();

   if (!errorMessage.empty())
   {
      printError(errorMessage);
      return;
   }

   if (cmd->showUsage())
   {
      *this << "Start or stop Runtime Windows service" << lnfd
           << "Usage:" << lnfd
           << Indent << "service [-h] start/stop" << lnfd
           << lnfd
           << Indent << "-h    " << "show this message" << lnfd;
   }
}

void TextOutputVisitor::visitCommandSetProperty(CommandSetProperty* cmd)
{
   const string errorMessage = cmd->errorMessage();

   if (!errorMessage.empty())
   {
      printError(errorMessage);
      return;
   }

   if (cmd->showUsage())
   {
      *this << "Set a new values for a specific property" << lnfd
           << "Usage:" << lnfd
           << Indent << "set [-h] propertyURI value1 [value2 ...]" << lnfd
           << lnfd
           << Indent << "-h    " << "show this message" << lnfd;
   }

   *this << "> Property values updated successfully" << lnfd;
}

const TextOutputVisitor& TextOutputVisitor::operator<< (const char* text) const
{
   print(text);
   return (*this);
}


const TextOutputVisitor& TextOutputVisitor::operator<< (const std::string& text) const
{
   print(text.c_str());
   return (*this);
}

void TextOutputVisitor::print(const char* text) const
{
   //oh: I don´t use Logger here, because solution can be created 
   //    with disabled CMake TRENTINO_LOGGING 
   printf(text);
}
