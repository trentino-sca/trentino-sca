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

// std::copy issues C4996 warning when it is used with raw pointers, because when used incorrectly,
// it can result in buffer overflows. Lets just disable it for one following boost::split call.
#pragma warning(push)
#pragma warning(disable:4996)

//header
#include "TrentinoConsoleParser.h"

//standard
#include <exception>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <boost/foreach.hpp>
#include <stdexcept>

#pragma warning(pop) //C4996 warning

//specific
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLoggerWriter.h"
#include "./../Runtime/TrentinoManagementInterface.h"
#include "TrentinoConsole.h"
#include "TrentinoConsoleOutputVisitor.h"
#include "TrentinoConsoleCommandBoot.h"
#include "TrentinoConsoleCommandShutdown.h"
#include <boost/thread.hpp>

using namespace Trentino::Console;
using namespace std;

extern Context context;
extern boost::condition_variable gConditionExit;
extern boost::mutex gMutexExit;

Context& Trentino::Console::Parser::mContext = context;
bool Trentino::Console::Parser::mDoExit = false;

static void checkArgsRange(const int min, const int max, const int size)
   {
   if ((size == 0) && (min > 0))
      {
      throw runtime_error(Errors::NoArgs);
      }

   if (size < min)
      {
      throw runtime_error(Errors::TooFewArgs);
      }

   if (size > max)
      {
      throw runtime_error(Errors::TooManyArgs);
      }

   }

//class Parser
//construction
Parser::Parser(Context& contextManager)
   : 
mHelp(false)   
{
   contextManager;
}

//services
CommandInfo::CommandArgs Parser::parseCommandInfoArgs(const CommandArgs& tokens)
   {
   checkArgsRange(1, 4, tokens.size());

   CommandInfo::CommandArgs args;
   BOOST_FOREACH(const string& token, tokens)
      {
      //argument begins with '-d'
      if (!token.find("-d"))
         {
         const string value = token.substr(2, token.npos);
         stringstream ss(value);

         int i =-1;


         if (((ss >> i).fail()) || i < args.searchDepth)
            {
            throw runtime_error("invalid depth value, try -h option for more information");
            }
         }
      //argument begins with '-q'
      else if (!token.find("-q"))
         {
         const string values = token.substr(2, token.npos);
         if (values.empty())
            throw runtime_error("no empty query allowed, try -h option for more information");

         BOOST_FOREACH(const char& sym, values)
            {
            switch (sym)
               {
            case 'b':
               args.getContributions = true;
               break;
            case 'c': 
               args.getComponents = true;
               break;           
               /*case 'a':
               args.getAttributes = true;
               break;*/
            case 'p':
               args.getProperties = true;
               break;
            case 'r':
               args.getReferences = true;
               break;
            case 's':
               args.getServices = true;
               break;
            default:
               throw runtime_error("bad query specifier, try -h option for more information");
               break;
               }
            }
         }
      else if (token == "-s")
         {
         args.getContributionState = true;
         args.getComponentState = true;
         args.getReferenceState = true;
         args.getServiceState = true;
         args.getReferenceTargets = true;
         }
      else if(!token.find("-")){
         //any other argument was given but is unknown. Error
         throw runtime_error(Errors::UnknownArgs);
         }
      else
         {
         if (args.URI.empty())
            args.URI = token;
         else
            throw runtime_error(Errors::TooManyArgs);
         }
      }

   if (args.URI.empty() && !(args.getContributions || args.getComponents))
      {
      throw runtime_error("no URI was specified, try -h option for more information");
      }

   return args;
   }

CommandInstall::CommandArgs Parser::parseCommandInstallArgs(const CommandArgs& tokens)
   {
   // ToDo: Set the range (2, 3) when '-i' option will be implemented
   checkArgsRange(2, 2, tokens.size());

   CommandInstall::CommandArgs args;

   // Currently 'install' command deploys contribution automatically, so '-i' option isn't used yet
   //   if(tokens[0] ==  "-i")
   //   {
   //      if(tokens.size() != 3)
   //      {
   //         throw runtime_error("no base URI was specified, try -h option for more information");     
   //      }
   //
   //      args.doDeploy = false;
   //      args.pathToContribution = tokens[1];
   //      args.contributionBaseURI = tokens[2];
   //   }
   //   else
   if (Trentino::Utils::constantExpression<bool>(true))
      {
      args.doDeploy = true;
      args.pathToContribution = tokens[0];
      args.contributionBaseURI = tokens[1];
      }

   return args;
   }


CommandUpdate::CommandArgs Parser::parseCommandUpdateArgs(const CommandArgs& tokens)
   {
   // ToDo: Set the range (2, 3) when '-i' option will be implemented
   checkArgsRange(2, 2, tokens.size());

   CommandUpdate::CommandArgs args;

   if (Trentino::Utils::constantExpression<bool>(true))
      {
      args.pathToContribution = tokens[0];
      args.contributionBaseURI = tokens[1];
      }

   return args;
   }

CommandRemove::CommandArgs Parser::parseCommandRemoveArgs(const CommandArgs& tokens)
   {
   // ToDo: Set the range (1, 2) when component-remove will be added
   checkArgsRange(1, 1, tokens.size());

   CommandRemove::CommandArgs args;
   BOOST_FOREACH(const string& token, tokens)
      {

      // Component remove isn't supported yet
      //      if (token == "-c")
      //      {
      //         args.removeComponent = true;
      //      }
      //      else
      if (Trentino::Utils::constantExpression<bool>(true))
         {
         args.identifier = token;
         }
      }

   if (args.identifier.empty())
      {
      throw runtime_error("no identifier was specified, try -h option for more information");
      }

   return args;
   }

CommandRewire::CommandArgs Parser::parseCommandRewireArgs(const CommandArgs& tokens)
   {
   checkArgsRange(2, 3, tokens.size());

   CommandRewire::CommandArgs args;
   args.referenceURI = tokens[0];
   args.target = tokens[1];

   if (tokens.size() == 3)
      args.bindingType = tokens[2];

   return args;
   }

CommandService::CommandArgs Parser::parseCommandServiceArgs(const CommandArgs& tokens)
   {
   checkArgsRange(1, 1, tokens.size());

   CommandService::CommandArgs args;

   if ((tokens[0] != "start") && (tokens[0] != "stop"))
      throw runtime_error("invalid command, try -h option for more information");

   args.command = tokens[0];

   return args;
   }

CommandSetProperty::CommandArgs Parser::parseCommandSetPropertyArgs(const CommandArgs& tokens)
   {
   checkArgsRange(2, tokens.max_size(), tokens.size());

   CommandSetProperty::CommandArgs args;
   args.propertyURI = tokens[0];

   args.values = tokens;
   args.values.erase(args.values.begin());

   return args;
   }

Command::CommandSharedPtr Parser::parse(const string& commandLine)
   {
   HLOGGER();  

   //a small state machine to parse the command line
   //arguments containing spaces must be put in quotes
   vector<string> tokens;   
   string newToken;
   enum State {Init, InToken, InQuotes};
   State state = Init;
   for(unsigned int i = 0; i < commandLine.size(); i++)
      { 
      const char& c = commandLine[i];

      switch(state)
         {
      case Init:            
         assert( newToken.empty() );
         if(c == '"')
            {
            state = InQuotes;
            }
         else if( !isspace(c) )
            {
            newToken.append(1, c);
            state = InToken;               
            }            
         break;
      case InToken:
         if(isspace(c))
            {
            tokens.push_back(newToken);
            newToken.clear();
            state = Init;
            }
         else
            {
            newToken.append(1, c);
            }
         break;
      case InQuotes:
         if(c == '"')
            {
            tokens.push_back(newToken);
            newToken.clear();
            state = Init;
            }
         else
            {
            newToken.append(1, c);
            }
         break;
      default:
         assert(false);
         }
      }

   if(!newToken.empty())
      {
      tokens.push_back(newToken);
      }

   string command;
   if(!tokens.empty())
      {
      command = tokens[0];
      tokens.erase(tokens.begin());
      }

   if((command == "quit") || (command == "exit"))
      {
      setExit();
      gConditionExit.notify_all();
      return Command::CommandSharedPtr(new CommandQuit(mContext));
      }

   bool showUsage = false;
   BOOST_FOREACH(const string& token, tokens)
      {
      if (token == "-h")
         {
         if (tokens.size() == 1)
            showUsage = true;
         else
            throw runtime_error(Errors::TooManyArgs);
         }
      }
   if(command == "boot")
      {
      Command::CommandSharedPtr commandBoot(new CommandBoot(mContext,commandLine));
      commandBoot->setShowUsage(showUsage);

      return commandBoot;
      }
   else if(command == "shutdown")
      {
      Command::CommandSharedPtr commandShutdown(new CommandShutdown(mContext));
      commandShutdown->setShowUsage(showUsage);

      return commandShutdown;
      }
   else if(command == "info")
      {        
      CommandInfo::CommandArgs args = 
         showUsage ? CommandInfo::CommandArgs() : parseCommandInfoArgs(tokens);      

      Command::CommandSharedPtr commandInfo(
         new CommandInfo(args, mContext));
      commandInfo->setShowUsage(showUsage);     

      return commandInfo;
      }
   else if(command == "install")
      {
      CommandInstall::CommandArgs args = 
         showUsage ? CommandInstall::CommandArgs() : parseCommandInstallArgs(tokens);      

      Command::CommandSharedPtr commandInstall(
         new CommandInstall(args, mContext));
      commandInstall->setShowUsage(showUsage);     

      return commandInstall;
      }
   else if (command == "update")
      {
      CommandUpdate::CommandArgs args=
         showUsage?CommandUpdate::CommandArgs(): parseCommandUpdateArgs(tokens);
      Command::CommandSharedPtr commandUpdate(
         new CommandUpdate(args, mContext));
      commandUpdate->setShowUsage(showUsage);
      return commandUpdate;
      }
   else if(command == "remove")
      {
      CommandRemove::CommandArgs args = 
         showUsage ? CommandRemove::CommandArgs() : parseCommandRemoveArgs(tokens);      

      Command::CommandSharedPtr commandRemove(
         new CommandRemove(args, mContext));
      commandRemove->setShowUsage(showUsage);     

      return commandRemove;
      }
   else if(command == "rewire")
      {
      CommandRewire::CommandArgs args = 
         showUsage ? CommandRewire::CommandArgs() : parseCommandRewireArgs(tokens);      

      Command::CommandSharedPtr commandRewire(
         new CommandRewire(args, mContext));
      commandRewire->setShowUsage(showUsage);     

      return commandRewire;
      }
   else if (command == "service")
      {
      CommandService::CommandArgs args = 
         showUsage ? CommandService::CommandArgs() : parseCommandServiceArgs(tokens);      

      Command::CommandSharedPtr commandService(
         new CommandService(args, mContext));
      commandService->setShowUsage(showUsage);     

      return commandService;
      }
   else if (command == "set")
      {
      CommandSetProperty::CommandArgs args = 
         showUsage ? CommandSetProperty::CommandArgs() : parseCommandSetPropertyArgs(tokens);      

      Command::CommandSharedPtr commandSetProperty(
         new CommandSetProperty(args, mContext));
      commandSetProperty->setShowUsage(showUsage);     

      return commandSetProperty;
      }
   else if (command == "help")
      {
      setHelp();
      return Command::CommandSharedPtr();
      }
   else if(command.empty())
      {
      return Command::CommandSharedPtr(); 
      }
   else
      {
      throw runtime_error("invalid command. type help to get help");
      }
   }

void Parser::scheduleExceptionAction()
{
   executeShutDown();
}

void Parser::executeShutDown()
{
   setExit();

   boost::unique_lock<boost::mutex> lock(gMutexExit);
   gConditionExit.notify_all();
}