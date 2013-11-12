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

#ifndef TrentinoConsoleCommandServiceH
#define TrentinoConsoleCommandServiceH

//baseclass
#include "TrentinoConsoleContextAccessingCommand.h"

//standard
#include <string>

namespace Trentino {
namespace Console
{
   class ContextAccessor;

   //**********************************************************************************************
   //                                      CommandService
   //**********************************************************************************************
   //! \class CommandService
   //! \brief Manage Runtime Windows service state
   //!
   //! Manage the Runtime Windows service state: start or stop.
   //**********************************************************************************************
   class CommandService : public ContextAccessingCommand
   {
      //additional
   public:
      //*******************************************************************************************
      //                                     CommandsArgs
      //*******************************************************************************************
      //! \struct CommandArgs
      //! \brief Data structure to store information about arguments passed to the command
      //!   This structure is filled by parser and later used to manage command control flow.
      //!      
      //! \var command Action to be performed to Runtime service
      //*******************************************************************************************
      struct CommandArgs
      {
         //construction
         CommandArgs()         
         {}

         //data         
         std::string command;
      };

      //construction
   public:
      CommandService(const CommandArgs& commandArgs, const ContextAccessor& contextAccessor);

      //inherited services, see description in the parent class declaration
   public:
      void execute();
      void acceptOutputVisitor(OutputVisitor& v);

      //management
   private:
      //*******************************************************************************************
      //                                  commandParameters()
      //*******************************************************************************************
      //! \brief Return command arguments passed by the user in a prompt
      //! \return Filled strucutre with parameters
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
   };

   inline CommandService::CommandArgs CommandService::commandArgs() const
   {
      return mCommandArgs;
   }

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleCommandServiceH