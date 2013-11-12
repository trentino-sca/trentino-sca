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

//standard
#include <oasis/sca/ComponentContext.h>

//specific
#include "SCAReferenceExampleImpl.h"



const int TrentinoNamespace::SCAReferenceExampleImpl::Property1() const
{
   return mProperty1;
}

void TrentinoNamespace::SCAReferenceExampleImpl::setProperty1( const int value )
{
   mProperty1 = value;
}

const std::string& TrentinoNamespace::SCAReferenceExampleImpl::Property2() const
{
   return mProperty2;
}

void TrentinoNamespace::SCAReferenceExampleImpl::setProperty2( const std::string& value )
{
   mProperty2 = value;
}

const bool TrentinoNamespace::SCAReferenceExampleImpl::Property3() const
{
   return mProperty3;
}

void TrentinoNamespace::SCAReferenceExampleImpl::setProperty3( const bool value )
{
   mProperty3 = value;
}

const std::list<std::string>& TrentinoNamespace::SCAReferenceExampleImpl::MultiProperty() const
{
   return mMultiProperty;
}

void TrentinoNamespace::SCAReferenceExampleImpl::setMultiProperty( const std::list<std::string>& values )
{
   mMultiProperty = values;
}

const int TrentinoNamespace::SCAReferenceExampleImpl::ValueFileProperty() const
{
   return mValueProperty;
}

void TrentinoNamespace::SCAReferenceExampleImpl::setValueFileProperty( const int value )
{
   mValueProperty = value;
}

void TrentinoNamespace::SCAReferenceExampleImpl::setSCAServiceToAttachRef( SCAServiceToAttach* value )
{
   mSCAServiceToAttach = value;
}

void TrentinoNamespace::SCAReferenceExampleImpl::setSCAServicesToAttachRef( const std::list<SCAServiceToAttach*>& values )
{
   mSCAServicesToAttach = values;
}
