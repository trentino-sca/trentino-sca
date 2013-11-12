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


#ifndef TrentinoBindingSCASCABindingFactoryH
#define TrentinoBindingSCASCABindingFactoryH

//baseclass
#include <Runtime/Binding/TrentinoBindingBindingFactory.h>
#include "TrentinoBindingSCA.h"
//standard
#include <string>

namespace Trentino
{
   namespace Binding {
      namespace SCA 
      {

         //! \ingroup TrentinoBindingSCA
         //! The factory for the Trentino SCA Binding
         class BINDINGSCA_IMPORT_EXPORT SCABindingFactory
         {
            //constructor
         public:
            SCABindingFactory();

         private:
            SCABindingFactory& operator=(const SCABindingFactory&);

            //services
         public:
            std::string doGetBindingId();
            Trentino::Binding::TrentinoBinding* doCreateBinding();
            static std::string TRENTINO_CDECL getBinding(void* objPtr);
            static Trentino::Binding::TrentinoBinding* TRENTINO_CDECL  createBinding(void* objPtr);
            //data
         private:
            std::string mBindingId; 
         };  //factory for the trentino SCA Binding
      }//namespace SCA
   }//namespace TBinding
}//namepsace Trentino

#endif //TrentinoBindingSCASCABindingFactoryH
