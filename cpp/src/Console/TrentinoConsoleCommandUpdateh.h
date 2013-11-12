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

#ifndef TrentinoConsoleCommandUpdatelH
#define TrentinoConsoleCommandUpdatelH

//baseclass
#include "TrentinoConsoleContextAccessingCommand.h"

//standard
#include <string>

namespace Trentino {
namespace Console
{
   class ContextAccessor;

   //**********************************************************************************************
   //                                      CommandUpdate
   //**********************************************************************************************
   //! \class CommandUpdate
   //! \brief Update command class declaration
   //!
   //! This command performs the update of an existing contribution into the runtime.
   //**********************************************************************************************
   class CommandUpdate : public ContextAccessingCommand
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
      //! \var pathToContribution Path to the new contribution to be updated
      //! \var contributionBaseURI = uri of the contribution to be changed
      //*******************************************************************************************
      struct CommandArgs
      {
         //contruction
         CommandArgs()        
         {}

         //data
         std::string pathToContribution;
         std::string contributionBaseURI;
      }; //struct CommandArgs

      //construction
   public:
      CommandUpdate(const CommandArgs& commandArgs, const ContextAccessor& contextAccessor);

      //inherited services, see description in the parent class declaration
   public:
      void execute();
      void acceptOutputVisitor(OutputVisitor& v);

      //services
   public:
      //*******************************************************************************************
      //                                  commandParameters()
      //*******************************************************************************************
      //! \brief Return command arguments passed by the user in a prompt
      //! \return Filled structure with parameters
      //*******************************************************************************************
      CommandArgs commandArgs() const
         {
         return mCommandArgs;
         }

      //*******************************************************************************************
      //                                      deployStatus()
      //*******************************************************************************************
      //! \brief Get the status of performed deployment
      //! \return String with the status
      //*******************************************************************************************
      std::string updateStatus() const
         {
         return mUpdateStatus;
         }

      //modifiers
   private:
      //*******************************************************************************************
      //                                     setDeployStatus()
      //*******************************************************************************************
      //! \brief Store the status of the perfomed deployment
      //! \param status String with the status
      //*******************************************************************************************
      void setUpdateStatus(const std::string& status)
         {
         mUpdateStatus = status;
         }
           

      //data
   private:
      //*******************************************************************************************
      //                                    mCommandParameters
      //*******************************************************************************************
      //! \brief Structure to store filled CommandArgs one
      //*******************************************************************************************
      CommandArgs mCommandArgs;

      //*******************************************************************************************
      //                                     mDeployStatus
      //*******************************************************************************************
      //! \brief The output from the deploy iteration of the ManagementInterface
      //*******************************************************************************************
      std::string mUpdateStatus;

   }; //class CommandExit

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleCommandUpdatelH