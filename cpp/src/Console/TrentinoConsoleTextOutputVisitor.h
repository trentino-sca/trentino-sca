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

#ifndef TrentinoConsoleTextOutputVisitorH
#define TrentinoConsoleTextOutputVisitorH

//baseclass
#include "TrentinoConsoleOutputVisitor.h"

//specific
#include "TrentinoConsoleCommandInfo.h"


//standard
#include <string>

namespace Trentino {
namespace Console
{

   //*********************************************************************************************
   //                                   TextOutputVisitor
   //*********************************************************************************************
   //! \class TextOutputVisitor
   //! \brief Console output visitor
   //!   This class represents a console output sub-system. It's responsible for every message
   //! printed on the screen. Each user command should have a method here, which displays
   //! execution result.
   //*********************************************************************************************
   class TextOutputVisitor : public OutputVisitor
   {
      //construction
   public:
      TextOutputVisitor();

      //inherited services
   public:
      void visitCommandBoot(CommandBoot* cmdBoot);
      void visitCommandShutdown(CommandShutdown* cmdBoot);
      void visitCommandInfo(CommandInfo* cmdInfo);
      void visitCommandInstall(CommandInstall* cmdInstall);
      void visitCommandUpdate(CommandUpdate* cmdUpdate);
      void visitCommandQuit(CommandQuit* cmdQuit);
      void visitCommandRemove(CommandRemove* cmdRemove);
      void visitCommandRewire(CommandRewire* cmdRewire);
      void visitCommandService(CommandService* cmdService);
      void visitCommandSetProperty(CommandSetProperty* cmdSet);

      //services
   public:
      //*****************************************************************************************
      //                                printIntro()
      //*****************************************************************************************
      //! \brief Display a greeting message
      //!   This method should print the first introductory message if console is chosen as
      //! output sub-system.
      //*****************************************************************************************
      void printIntro() const;

      //*****************************************************************************************
      //                                printError()
      //*****************************************************************************************
      //! \brief Unified interface to print an error message
      //! \param errMessage Error message to be printed
      //*****************************************************************************************
      void printError(const std::string& errMessage) const;

      //*****************************************************************************************
      //                                printPrompt()
      //*****************************************************************************************
      //! \brief Display a command prompt
      //*****************************************************************************************
      void printPrompt() const;

      //*****************************************************************************************
      //                                  printUsage()
      //*****************************************************************************************
      //! \brief Display a list of available commands and brief description for them
      //*****************************************************************************************
      void printUsage() const;

      //friend std::ostream& operator<< (std::ostream& oStream, TextOutputVisitor& visitor);

      const TextOutputVisitor& operator<< (const char* text) const;
      const TextOutputVisitor& operator<< (const std::string& text) const;

      //management
   private:
      void print(const char* text) const;

      void printContribution(const Trentino::ManagementInterface::ContributionDatas data);
      void printAttributes( const CommandInfo::Attributes& attrs
                           ,const std::string& extraIndent);

      void printProperties( const CommandInfo::SCAComponent& component
                           ,const std::string& extraIndent);
      void printReferences( const CommandInfo::SCAComponent& component
                           ,const std::string& extraIndent);
      void printServices( const CommandInfo::SCAComponent& component
                         ,const std::string& extraIndent);


   }; //class TextOutputVisitor

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleTextOutputVisitorH