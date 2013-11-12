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

#ifndef TrentinoConsoleCommandBootH
#define TrentinoConsoleCommandBootH

//baseclass
#include "TrentinoConsoleContextManagingCommand.h"

namespace Trentino{
namespace Console 
{
   class ContextManager;

   //**********************************************************************************************
   //                                      CommandBoot
   //**********************************************************************************************   
   //! \brief Boots the Trentino Runtime into the current process. 
   //!
   //! The path to the runtime library to be loaded is computed as follows:
   //! <tt><directory_path_of_the_current_executable>/<value of the Runtime.DLLPath option>/
   //!      Utils::Environment::makeDLLName(<value of the Runtime.DLLName option>)</tt>
   //**********************************************************************************************
   class CommandBoot : public ContextManagingCommand
   {
      //construction
   public:
      CommandBoot(Context& contextManager,const std::string& commandLine);

      //services
   public:
      void execute();
      void acceptOutputVisitor(OutputVisitor& v);

      //data
   private:
      std::string mCommandLine;
   
   }; //class CommandBoot

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleCommandBootH