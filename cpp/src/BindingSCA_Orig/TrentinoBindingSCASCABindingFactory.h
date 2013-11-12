// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************


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
