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
#include "TrentinoBindingSCASCABindingFactory.h"

//specific
#include "../Runtime/Binding/TrentinoBinding.h"
#include "TrentinoBindingSCATrentinoBindingSCA.h"


using namespace Trentino::Binding;
using namespace Trentino::Binding::SCA;

Trentino::Binding::TrentinoBinding* 
   SCABindingFactory::doCreateBinding()
{
   return new TrentinoBindingSCA(doGetBindingId());
}

std::string SCABindingFactory::doGetBindingId()
{
   return mBindingId;
}

SCABindingFactory::SCABindingFactory():mBindingId("binding.sca"){}

TRENTINO_DLLEXPORT std::string TRENTINO_CDECL Trentino::Binding::SCA::SCABindingFactory::getBinding( void* objPtr )
   {
   SCABindingFactory* myself =(SCABindingFactory*) objPtr;
   return myself->doGetBindingId();
   }

TRENTINO_DLLEXPORT Trentino::Binding::TrentinoBinding* TRENTINO_CDECL Trentino::Binding::SCA::SCABindingFactory::createBinding( void* objPtr )
   {
   SCABindingFactory* myself =(SCABindingFactory*) objPtr;
   return myself->doCreateBinding();
   }
