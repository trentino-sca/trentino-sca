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

#ifndef TrentinoRuntimeModelVisitorH
#define TrentinoRuntimeModelVisitorH

//specific
#include "TrentinoRuntimeModel.h"


namespace Trentino{
namespace RuntimeModel
{
  
     //****************************************************************************************************
     //                                         Visitor
     //****************************************************************************************************
     //! \brief a visitor is used by clients of the runtime model to iterate over all objects 
     //! inside the model.
     //! The default visitor does nothing. Client should subclass this Visitor to add their behaviour 
     //****************************************************************************************************
   
   class Visitor
   {

   public:
     //****************************************************************************************************
     //                                         visitComposite()
     //****************************************************************************************************
     //! \brief visit a composite.  The default implementation does nothing 
     //! \param const CompositePtr & composite
     //! \return void
     //****************************************************************************************************
     virtual bool visitComposite(const CompositePtr& /*entity*/){return true;}
     //****************************************************************************************************
     //                                         visitComponent()
     //****************************************************************************************************
     //! \brief visit a Component.  The default implementation does nothing 
     //! \param const ComponentPtr & component
     //! \return void
     //****************************************************************************************************
     virtual bool visitComponent(const ComponentPtr& /*entity*/){return true;}

         //****************************************************************************************************
     //                                         visiteService()
     //****************************************************************************************************
     //! \brief visit a Servcice.  The default implementation does nothing 
     //! \param const ServiceBasePtr& service
     //! \return void
     //****************************************************************************************************
    
     virtual bool visiteService (const ServiceBasePtr& /*entity*/){return true;}

     //****************************************************************************************************
     //                                         visiteReference()
     //****************************************************************************************************
     //! \brief visit a reference
     //! \param const ReferenceBasePtr & reference
     //! \return void
     //****************************************************************************************************
     virtual bool visiteReference (const ReferenceBasePtr& /*entity*/){return true;}
      
   }; //class Visitor

} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelVisitorH

