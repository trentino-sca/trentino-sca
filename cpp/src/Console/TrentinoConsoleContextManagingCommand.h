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

#ifndef TrentinoConsoleContextManagingCommandH
#define TrentinoConsoleContextManagingCommandH

//baseclass
#include "TrentinoConsoleCommand.h"
#include "TrentinoConsoleContext.h"

namespace Trentino {
namespace Console
{ 
   class ContextManager;

   //**********************************************************************************************
   //                                      ContextManagingCommand
   //********************************************************************************************** 
   //! \brief Base class for commands that might modify, create and delete contexts. 
   //**********************************************************************************************
   class ContextManagingCommand : public Command
   {
      //construction
   public:
      //*******************************************************************************************
      //                                   ContextManagingCommand()
      //******************************************************************************************* 
      //! \brief Constructs a ContextManagingCommand with the given CotnextManager.
      //! \param[in] A reference to a ContextManager. 
      //*******************************************************************************************
      ContextManagingCommand(Trentino::Console::Context& context); 

       //operators
   private:
      //*******************************************************************************************
      //                            operator=(const ContextManagingCommand&)
      //*******************************************************************************************
      //! \brief Explicitely disallow assignment (because of reference members).    
      //*******************************************************************************************
      void operator=(const ContextManagingCommand&);

      //management
   protected:
    
      //*******************************************************************************************
      //                                        currentContext()
      //******************************************************************************************* 
      //! \brief Returns the current context.
      //! 
      //! So far only one context is managed by the ContextManager. It is automatically available
      //! after the construction of an ContextManager instance. 
      //! \return Reference to the current context. 
      //*******************************************************************************************
      Context& currentContext();
      
      //data
   private: 
      //! \brief Holds the single context managed by the ContextManager so far. 
      //! 
      //! In future this might turn into a collection of contexts.
      //! \sa currentContext()
      Context& mContext;
   }; //class ContextManagingCommand

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleContextManagingCommandH