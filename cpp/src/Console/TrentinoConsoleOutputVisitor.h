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

#ifndef TrentinoConsoleOutputVisitorH
#define TrentinoConsoleOutputVisitorH

namespace Trentino {
namespace Console
{
   //forward-declared classes
   class CommandBoot;
   class CommandShutdown;
   class CommandInfo;
   class CommandInstall;
   class CommandUpdate;
   class CommandQuit;
   class CommandRemove;
   class CommandRewire;
   class CommandService;
   class CommandSetProperty;

   //*********************************************************************************************
   //                                    OutputVisitor
   //*********************************************************************************************
   //! \class OutputVisitor
   //! \brief A base class for every output sub-system
   //!   This class is the base class for every output sub-system. Each command-set must have a
   //! visitor instance for all the possible outputs.
   //*********************************************************************************************
   class OutputVisitor
   {
      //construction
   public:
      virtual ~OutputVisitor() {};

      //services
   public:
      //*****************************************************************************************
      //                                  visitCommandBoot()
      //*****************************************************************************************
      //! \brief A visitor entry point for the command 'boot'.
      //! \param[in] cmdBoot A pointer to CommandBoot.
      //*****************************************************************************************
      virtual void visitCommandBoot(CommandBoot* cmdBoot) = 0;

      //*****************************************************************************************
      //                                  visitCommandBoot()
      //*****************************************************************************************
      //! \brief A visitor entry point for the command 'shutdown'.
      //! \param[in] cmdShutdown A pointer to CommandShutdown.
      //*****************************************************************************************
      virtual void visitCommandShutdown(CommandShutdown* cmdShutdown) = 0;

      //*****************************************************************************************
      //                                  visitCommandInfo()
      //*****************************************************************************************
      //! \brief A visitor entry point for the command 'info'
      //! \param cmdInfo A pointer to the command structure
      //*****************************************************************************************
      virtual void visitCommandInfo(CommandInfo* cmdInfo) = 0;

      //*****************************************************************************************
      //                                  visitCommandInstall()
      //*****************************************************************************************
      //! \brief A visitor entry point for the command 'install'
      //! \param cmdInstall A pointer to the command structure
      //*****************************************************************************************
      virtual void visitCommandInstall(CommandInstall* cmdInstall) = 0;

      
      //*****************************************************************************************
      //                                  visitCommandUpdate()
      //*****************************************************************************************
      //! \brief A visitor entry point for the command 'update'
      //! \param cmdUpdate A pointer to the command structure
      //*****************************************************************************************
      virtual void visitCommandUpdate(CommandUpdate* cmdUpdate) = 0;

      //*****************************************************************************************
      //                                    visitCommandQuit()
      //*****************************************************************************************
      //! \brief A visitor entry point for the command 'quit'
      //! \param cmdQuit A pointer to the command structure
      //*****************************************************************************************
      virtual void visitCommandQuit(CommandQuit* cmdQuit) = 0;

      //*****************************************************************************************
      //                                  visitCommandRemove()
      //*****************************************************************************************
      //! \brief A visitor entry point for the command 'remove'
      //! \param cmdRemove A pointer to the command structure
      //*****************************************************************************************
      virtual void visitCommandRemove(CommandRemove* cmdRemove) = 0;

      //*****************************************************************************************
      //                                  visitCommandRewire()
      //*****************************************************************************************
      //! \brief A visitor entry point for the command 'rewire'
      //! \param cmdRewire A pointer to the command structure
      //*****************************************************************************************
      virtual void visitCommandRewire(CommandRewire* cmdRewire) = 0;

      //*****************************************************************************************
      //                                  visitCommandService()
      //*****************************************************************************************
      //! \brief A visitor entry point for the command 'service'
      //! \param cmdService A pointer to the command structure
      //*****************************************************************************************
      virtual void visitCommandService(CommandService* cmdService) = 0;

      //*****************************************************************************************
      //                                    visitCommandSet()
      //*****************************************************************************************
      //! \brief A visitor entry point for the command 'set'
      //! \param cmdSet A pointer to the command structure
      //*****************************************************************************************
      virtual void visitCommandSetProperty(CommandSetProperty* cmdSet) = 0;

   }; //class OutputVisitor

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleOutputVisitorH