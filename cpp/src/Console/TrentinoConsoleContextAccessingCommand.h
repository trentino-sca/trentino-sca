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

#ifndef TrentinoConsoleContextAccessingCommandH
#define TrentinoConsoleContextAccessingCommandH

//baseclass
#include "TrentinoConsoleCommand.h"

namespace Trentino {
namespace Console
{ 
   class ContextAccessor;

   //**********************************************************************************************
   //                                      ContextAccessingCommand
   //********************************************************************************************** 
   //! \brief Base class for commands that need only non-modifying access to a context.
   //**********************************************************************************************
   class ContextAccessingCommand : public Command
   {
      //construction
   public:
      //*******************************************************************************************
      //                                   ContextAccessingCommand()
      //******************************************************************************************* 
      //! \brief Constructs a ConextAccessingCommand with the given ContextAccessor.
      //! \param[in] A reference to a ContextAccessor. 
      //*******************************************************************************************
      ContextAccessingCommand(const ContextAccessor& contextAccessor); 

      //operators
   private:
      //*******************************************************************************************
      //                            operator=(const ContextAccessingCommand&)
      //*******************************************************************************************
      //! \brief Explicitely disallow assignment (because of reference members).    
      //*******************************************************************************************
      void operator=(const ContextAccessingCommand&);

      //management
   protected:
      //*******************************************************************************************
      //                                     contextAccessor()
      //******************************************************************************************* 
      //! \brief Allows derived classes to access the ContextAccesor instance.
      //! \return Reference to a ContextAccessor.
      //*******************************************************************************************
      const ContextAccessor& contextAccessor() const;
      
      //data
   private:   
      //! Holds the ContextAccessor the ContextAccessingCommand is associated with.
      const ContextAccessor& mContextAccessor;

   }; //class ContextAccessingCommand

   //management
   inline const ContextAccessor& ContextAccessingCommand::contextAccessor() const
   {
      return mContextAccessor;
   }

} //namespace Console
} //namespace Trentino

#endif //TrentinoConsoleContextAccessingCommandH