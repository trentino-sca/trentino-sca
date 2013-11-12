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

#ifndef TrentinoBindingSCABindingFactoryH
#define  TrentinoBindingSCABindingFactoryH

//specific
#include "TrentinoBinding.h"
#include "../../Global/TrentinoGlobal.h"
#include "../../Utils/TrentinoUtils.h"


namespace Trentino{
   namespace Binding{
       typedef  std::string   (TRENTINO_CDECL *GetBinding)(void* implementor);
       typedef  TrentinoBinding* (TRENTINO_CDECL *CreateBinding)(void* implementor);

      //class declaration
      //**********************************************************************************************
      //                             BindingFactory                             
      //**********************************************************************************************
      //! \ingroup TrentinoBinding
      //! A factory class used by Binding provider to register a new Binding to the Binding Framework
      //! a Factory actually describes the binding to be created by giving its ID
      //! A Factory can create a new Binding based on the binding context 
      //! the Binding context is provided by the Binding framework
      //! The framework read context from a central configuration file of trentino
      //*******************************************************************************************
      class BINDING_IMPORT_EXPORT BindingFactory 
      {
       //construction
      public:
         BindingFactory(){}
         ~BindingFactory(){
            mDynamicLibrary.reset();
            }
      private:
         BindingFactory& operator=(const BindingFactory &rhs);

      //services
      public:
         //****************************************************************************************
         //                                getBindingId()
         //****************************************************************************************
         //! \brief get the Binding ID
         //! \return the Binding ID
         //****************************************************************************************
         std::string getBindingId(){
            return mGetBinding(mImplementor);
            }

         //****************************************************************************************
         //                                createBinding()
         //****************************************************************************************
         //! \brief create a Binding given the binding Context
         //! \return A sharep pointer to the created Binding
         //****************************************************************************************
         TrentinoBindingPtr createBinding(){
            return TrentinoBindingPtr(mCreateBinding(mImplementor));
            }

         void setGetBinding(Trentino::Binding::GetBinding val) { mGetBinding = val; }
         void setCreateBinding(Trentino::Binding::CreateBinding val) { mCreateBinding = val; }
         void setImplementor(void * val) { mImplementor = val; }

         void setDynamicLibrary(const Trentino::Utils::DynamicLibraryPtr& dll ) 
         {
	         mDynamicLibrary=dll;
         }


         private:
         void * mImplementor;
         Trentino::Utils::DynamicLibraryPtr mDynamicLibrary;
         GetBinding mGetBinding;
         CreateBinding mCreateBinding;

         }; //class BindingFactory

   }//namespace Binding
}//namespace Trentino
#endif //TrentinoBindingSCABindingFactoryH
