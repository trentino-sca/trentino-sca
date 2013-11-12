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

#ifndef TrentinoConsoleCommandSetPropertyH
#define TrentinoConsoleCommandSetPropertyH

//baseclass
#include "TrentinoConsoleContextAccessingCommand.h"

//standard
#include <vector>

namespace Trentino {
namespace Console
{
   class ContextAccessor;

   //**********************************************************************************************
   //                                    CommandSetProperty
   //**********************************************************************************************
   //! \class CommandSetProperty
   //! \brief SetProperty command class declaration
   //!
   //! This command intended to assign new values to property elements
   //**********************************************************************************************
   class CommandSetProperty : public ContextAccessingCommand
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
      //! \var propertyURI A URI-style property identifier
      //! \var values A set of a new values
      //*******************************************************************************************
      struct CommandArgs
      {
         //construction
         CommandArgs()            
         {}

         //data         
         std::string propertyURI;
         std::vector<std::string> values;
      }; //struct CommandArgs

      //construction
   public:
      CommandSetProperty( const CommandArgs& commandParameters
                        , const ContextAccessor& contextAccessor);

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
      //! \return String with parameters
      //*******************************************************************************************
      CommandArgs commandArgs() const;

      //data
   private:
      //*******************************************************************************************
      //                                    mCommandParameters
      //*******************************************************************************************
      //! \brief Return a filled CommandArgs structure
      //*******************************************************************************************
      CommandArgs mCommandArgs;

   }; //class CommandSetProperty

   inline CommandSetProperty::CommandArgs CommandSetProperty::commandArgs() const
   {
      return mCommandArgs;
   }

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleCommandSetPropertyH