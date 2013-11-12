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

//header
#include "TrentinoBindingIpcBindingFactory.h"

//specific
#include "TrentinoBindingIpcBinding.h"


using namespace Trentino::Binding;
using namespace Trentino::Binding::IPC;

Trentino::Binding::TrentinoBinding* 

BindingFactoryIpc::doCreateBinding()
{
   return new BindingIpc(doGetBindingId());
}

std::string BindingFactoryIpc::doGetBindingId()
{
   return mBindingId;
}

BindingFactoryIpc::BindingFactoryIpc()
   :mBindingId("binding.ipc")
{

}

TRENTINO_DLLEXPORT std::string TRENTINO_CDECL Trentino::Binding::IPC::BindingFactoryIpc::getBinding( void* objPtr )
{
   BindingFactoryIpc* myself =(BindingFactoryIpc*) objPtr;
   return myself->doGetBindingId();
}

TRENTINO_DLLEXPORT Trentino::Binding::TrentinoBinding* TRENTINO_CDECL Trentino::Binding::IPC::BindingFactoryIpc::createBinding( void* objPtr )
{
   BindingFactoryIpc* myself =(BindingFactoryIpc*) objPtr;
   return myself->doCreateBinding();
}

//****************************************************************************************************
//                                         getBindingFactory()
//****************************************************************************************************
//! \brief main entry point for a Binding. Return a Binding Factory used to instantiate Bindings
//! \return extern "C" TRENTINO_DLLEXPORT Trentino::Binding::BindingFactory* TRENTINO_CDECL
//****************************************************************************************************
extern "C" TRENTINO_DLLEXPORT void TRENTINO_CDECL getBindingFactory(Trentino::Binding::BindingFactory * factory, const char * /*bindingId*/)
{
   BindingFactoryIpc* implementation= new Trentino::Binding::IPC::BindingFactoryIpc();
   factory->setImplementor(implementation);
   factory->setGetBinding(&Trentino::Binding::IPC::BindingFactoryIpc::getBinding);
   factory->setCreateBinding(&Trentino::Binding::IPC::BindingFactoryIpc::createBinding);
}
