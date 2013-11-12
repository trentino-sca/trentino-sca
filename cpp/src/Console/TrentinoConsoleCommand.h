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

#ifndef TrentinoConsoleCommandH
#define TrentinoConsoleCommandH

//standard
#include <boost/shared_ptr.hpp>
#include <string>

namespace Trentino {
namespace Console
{
   class OutputVisitor; 

   //**********************************************************************************************
   //                                       Command
   //**********************************************************************************************
   //! \class Command
   //! \brief A base abstract class for all the users commands
   //!
   //! This class represents an interface for every command available to the user.
   //**********************************************************************************************
   class Command
   {
      //additional
   public:
      typedef boost::shared_ptr<Command> CommandSharedPtr;

      //construction
   public:
      Command();
      virtual ~Command() {};
   private:
      Command(const Command&);

      //operators
   private:
      void operator=(const Command&);

      //services
   public:
      //*******************************************************************************************
      //                                       execute()
      //*******************************************************************************************
      //! \brief Executes the command
      //! It's declared abstract because each command must have its own implementation of this 
      //! method.            
      //*******************************************************************************************
      virtual void execute() = 0;

      //*******************************************************************************************
      //                                acceptOutputVisitor()
      //*******************************************************************************************
      //! \brief Accept an output subsytem to print execution results
      //!   The output facilities are designed according to the visitor pattern. So each command
      //! has its own visitor implementation for the specified output type (console, GUI, log).
      //! Executing this method the output system takes control, grabs outcome information from
      //! command private data and sends it toward the final output.
      //!
      //! \param consoleVisitor Link to a visitor object
      //*******************************************************************************************
      virtual void acceptOutputVisitor(OutputVisitor& consoleVisitor) = 0;

      //*******************************************************************************************
      //                                    showUsage()
      //*******************************************************************************************
      //! \brief Check if user hint was requested
      //!   Check on visitor site for if usage hint requested
      //!
      //! \return True of false
      //*******************************************************************************************
      bool showUsage() const;

      //*******************************************************************************************
      //                                    setShowUsage()
      //*******************************************************************************************
      //! \brief Sets whether user hint was requested.      
      //! \param[in] showUsage  Boolean value identifying wheter user hint should be shown. 
      //! \sa showUsage()
      //*******************************************************************************************
      void setShowUsage(bool showUsage);

      //*******************************************************************************************
      //                                    errorMessage()
      //*******************************************************************************************
      //! \brief Get a message about error occured during command execution
      //! \return String with message. If empty-string is returned, command completed
      //! successfully
      //*******************************************************************************************
      std::string errorMessage() const;

      //modifiers
   protected:
      //*******************************************************************************************
      //                                  setErrorMessage()
      //*******************************************************************************************
      //! \brief Store information about error occured during command execution
      //! \param errMsg String with error message
      //*******************************************************************************************
      void setErrorMessage(const std::string& errMsg);

      //data
   private:
      //*******************************************************************************************
      //                                    mErrorMessage
      //*******************************************************************************************
      //! \brief String to store message about error occured during command execution.
      //*******************************************************************************************
      std::string mErrorMessage;

      //*******************************************************************************************
      //                                    mShowUsage
      //*******************************************************************************************
      //! \brief Boolean value to store information about whether the usage of a command should
      //!        be shown. 
      //*******************************************************************************************
      bool mShowUsage;

   }; //class Command

#include "TrentinoConsoleCommand.inl"

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleCommandH