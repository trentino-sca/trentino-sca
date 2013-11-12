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

#ifndef TrentinoConsoleCommandRemoveH
#define TrentinoConsoleCommandRemoveH

//baseclass
#include "TrentinoConsoleContextAccessingCommand.h"

namespace Trentino {
namespace Console
{
   class ContextAcessor;

   //**********************************************************************************************
   //                                      CommandRemove
   //**********************************************************************************************
   //! \class CommandRemove
   //! \brief Remove command class declaration
   //!
   //! This command removes a specific component or a whole contribution.
   //**********************************************************************************************
   class CommandRemove : public ContextAccessingCommand
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
      //! \var removeComponent Indicate that component is going to be removed      
      //! \var identifier Unique identifier for the artifact to be removed
      //*******************************************************************************************
      struct CommandArgs
      {
         //construction
         CommandArgs()
            : removeComponent(false)            
         {}

         //data
         bool removeComponent;         
         std::string identifier;
      };

      //construction
   public:
      CommandRemove(const CommandArgs& commandArgs, const ContextAccessor& contextAccessor);

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

   }; //class CommandRemove

   inline CommandRemove::CommandArgs CommandRemove::commandArgs() const
   {
      return mCommandArgs;
   }

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleCommandRemoveH