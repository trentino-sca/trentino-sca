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

#ifndef TrentinoConsoleParserH
#define TrentinoConsoleParserH

//specific
#include "TrentinoConsoleCommandInfo.h"
#include "TrentinoConsoleCommandInstall.h"
#include "TrentinoConsoleCommandUpdateh.h"
#include "TrentinoConsoleCommandQuit.h"
#include "TrentinoConsoleCommandRemove.h"
#include "TrentinoConsoleCommandRewire.h"
#include "TrentinoConsoleCommandService.h"
#include "TrentinoConsoleCommandSetProperty.h"

namespace Trentino {
namespace Console
{
   class ContextManager;

   //**********************************************************************************************
   //                                       Parser
   //**********************************************************************************************
   //! \class ConsoleParser
   //! \brief A parser for the user input.
   //!
   //! This class represents a set of methods intended to parse commands typed by the user. The
   //! outcome from the parser is a command class. Depending on the type of the command, the Parser
   //! provides the created commands with the necessary information, such as the command 
   //! arguments, the current Context (for a ContextAccessingCommand) or the ContextManager 
   //! (for a ContextManagingCommand). 
   //**********************************************************************************************
   class Parser
   {
      //additional
   public:
      typedef std::vector<std::string> CommandArgs;

      //construnction
   public:
      //*******************************************************************************************
      //                                       Parser()
      //*******************************************************************************************   
      //! \brief Constructs a Parser with the given ContextManager.
      //! \param[in] Reference to a ContextManager.      
      //*******************************************************************************************
      Parser(Context& contextManager);
   private:
      Parser(const Parser&);

      //operators
   private:
      void operator=(const Parser&);

      //services
   public:
      //*******************************************************************************************
      //                                    parse()
      //*******************************************************************************************
      //! \brief Parse the line obtained from the console prompt
      //! \param commandLine line which contains command and, possibly arguments
      //! \return appropriate command class casted to the base class
      //*******************************************************************************************
      Command::CommandSharedPtr parse(const std::string& commandLine);

      //*******************************************************************************************
      //                                     doExit()
      //*******************************************************************************************
      //! \brief Return exit trigger state 
      //*******************************************************************************************
      bool doExit() const;

      //*******************************************************************************************
      //                                     showHelp()
      //*******************************************************************************************
      //! \brief Show the list of commands available with brief description
      //*******************************************************************************************
      bool showHelp();

      //*******************************************************************************************
      //                                     scheduleExceptionAction()
      //*******************************************************************************************
      //! \brief This function is passed as a callback to management interface to be called once
      //! an hardware exception occurs during service invocation
      //! Accordingly the owner process (TrentinoConsole) takes the action it desires
      //! Currently shut down of console is triggered
      //*******************************************************************************************
      static void scheduleExceptionAction();

      //*******************************************************************************************
      //                                     executeShutDown()
      //*******************************************************************************************
      //! \brief This is the function called by scheduleExceptionAction() in case of a hw exception
      //! during safe invocation.
      //*******************************************************************************************
      static void executeShutDown();

   private:
      //*******************************************************************************************
      //                                 parseCommandInfoArgs()
      //*******************************************************************************************
      //! \brief Parse info command specific arguments
      //!   Parse arguments passed by a user for the info command and fill appropriate data
      //! structure to pass it directly to the command.
      //!
      //! \param commandArgs Vector with arguments passed by a user
      //! \return Filled CommandArgs data structure
      //*******************************************************************************************
      CommandInfo::CommandArgs parseCommandInfoArgs(const CommandArgs& tokens);

      //*******************************************************************************************
      //                                 parseCommandInstallArgs()
      //*******************************************************************************************
      //! \brief Parse install command specific arguments
      //!   Parse arguments passed by a user for the install command and fill appropriate data
      //! structure to pass it directly to the command.
      //!
      //! \param commandArgs Vector with arguments passed by a user
      //! \return Filled CommandArgs data structure
      //*******************************************************************************************
      CommandInstall::CommandArgs parseCommandInstallArgs(const CommandArgs& tokens);

      //*******************************************************************************************
      //                                 parseCommandUpdateArgs()
      //*******************************************************************************************
      //! \brief Parse update command specific arguments
      //!   Parse arguments passed by a user for the update command and fill appropriate data
      //! structure to pass it directly to the command.
      //!
      //! \param commandArgs Vector with arguments passed by a user
      //! \return Filled CommandArgs data structure
      //*******************************************************************************************
      CommandUpdate::CommandArgs parseCommandUpdateArgs(const CommandArgs& tokens);

      //*******************************************************************************************
      //                                 parseCommandRemoveArgs()
      //*******************************************************************************************
      //! \brief Parse remove command specific arguments
      //!   Parse arguments passed by a user for the remove command and fill appropriate data
      //! structure to pass it directly to the command.
      //!
      //! \param commandArgs Vector with arguments passed by a user
      //! \return Filled CommandArgs data structure
      //*******************************************************************************************
      CommandRemove::CommandArgs parseCommandRemoveArgs(const CommandArgs& tokens);

      //*******************************************************************************************
      //                                 parseCommandRewireArgs()
      //*******************************************************************************************
      //! \brief Parse rewire command specific arguments
      //!   Parse arguments passed by a user for the rewire command and fill appropriate data
      //! structure to pass it directly to the command.
      //!
      //! \param commandArgs Vector with arguments passed by a user
      //! \return Filled CommandArgs data structure
      //*******************************************************************************************
      CommandRewire::CommandArgs parseCommandRewireArgs(const CommandArgs& tokens);

      //*******************************************************************************************
      //                                 parseCommandServiceArgs()
      //*******************************************************************************************
      //! \brief Parse service command specific arguments
      //!   Parse arguments passed by a user for the service command and fill appropriate data
      //! structure to pass it directly to the command.
      //!
      //! \param commandArgs Vector with arguments passed by a user
      //! \return Filled CommandArgs data structure
      //*******************************************************************************************
      CommandService::CommandArgs parseCommandServiceArgs(const CommandArgs& tokens);

      //*******************************************************************************************
      //                                parseCommandSetPropertyArgs()
      //*******************************************************************************************
      //! \brief Parse setproperty command specific arguments
      //!   Parse arguments passed by a user for the rewire command and fill appropriate data
      //! structure to pass it directly to the command.
      //!
      //! \param commandArgs Vector with arguments passed by a user
      //! \return Filled CommandArgs data structure
      //*******************************************************************************************
      CommandSetProperty::CommandArgs parseCommandSetPropertyArgs(const CommandArgs& tokens);

      //modifiers
   private:
      //*******************************************************************************************
      //                                    setExit()
      //*******************************************************************************************
      //! \brief Indicate that exit command was executed
      //*******************************************************************************************
      static void setExit();

      //*******************************************************************************************
      //                                    setHelp()
      //*******************************************************************************************
      //! \brief Indicate that help message was executed
      //*******************************************************************************************
      void setHelp();

      //data
   private:
      //*******************************************************************************************
      //                                    mContextManager
      //*******************************************************************************************
      //! \brief Holds a reference to a ContextManager.
      //*******************************************************************************************
      static Context& mContext;

      //*******************************************************************************************
      //                                      mDoExit
      //*******************************************************************************************
      //! \brief Exit trigger
      //*******************************************************************************************
      static bool mDoExit;

      //*******************************************************************************************
      //                                       mHelp
      //*******************************************************************************************
      //! \brief Help message trigger
      //!   The full commands list and short description will be shown if set
      //*******************************************************************************************
      bool mHelp;

   }; //class Parser

#include "TrentinoConsoleParser.inl"

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleParserH