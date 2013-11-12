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

#ifndef TrentinoRuntimeModelWireableH
#define TrentinoRuntimeModelWireableH

//specific
#include "TrentinoRuntimeModel.h"

namespace Trentino{
namespace RuntimeModel
{  
   //class declaration
   //**********************************************************************************************
   //                             Wireable
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief All elements which are wireable use this class as support
   //**********************************************************************************************
   class Wireable 
   {
      friend class Wire;

      //construction
   public:
      //*******************************************************************************************
      //                            Wireable()
      //*******************************************************************************************
      //! Default constructor.
      //! Does nothing here.
      //*******************************************************************************************
      Wireable();

      //*******************************************************************************************
      //                                         wires()
      //*******************************************************************************************
      //! \brief Returns all the wires attached to the wireable object.
      //! \return A const reference to the collection of wires.
      //*******************************************************************************************
      RUNTIMEMODEL_IMPORT_EXPORT const Trentino::RuntimeModel::WireBases& wires() const;

      //management
   public:      
      //*******************************************************************************************
      //                          attachWire()
      //*******************************************************************************************
      //! \brief Attaches a wire.
      //! \param[in] Shared pointer of wire to attach.
      //*******************************************************************************************
      void attatchWire(const WireBasePtr& wire);

      //*******************************************************************************************
      //                          detatchWire()
      //*******************************************************************************************
      //! \brief Detaches a wire.
      //! \param[in] Shared pointer of wire to detach.
      //*******************************************************************************************
      void detatchWire(const WireBasePtr& wire);
      
      //data
   private:
      //! Set of wires.
      WireBases mWires;

   }; //class Wireable

} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelWireableH
