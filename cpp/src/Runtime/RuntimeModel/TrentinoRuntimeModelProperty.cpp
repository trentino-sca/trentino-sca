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
#include "TrentinoRuntimeModelProperty.h"

using namespace std;
using Trentino::RuntimeModel::Property;
namespace RuntimeModel = Trentino::RuntimeModel;

//class Property
   //construction
Property::Property( const Trentino::SCA::Model::PropertyPtr& scaPropertyType
                  , const RuntimeModel::ComponentWeakPtr& component)
: mSCAPropertyType(scaPropertyType)
, mComponent(component)
{}
   //services
const void Property::setValues(const Property::Values& values)
{ 
   const Values::const_iterator endIt = 
      isMany() || values.empty() ? values.end() : values.begin() + 1;

   mValues.assign(values.begin(), endIt);
}

void Property::addValue(const Property::Value& value)
{  
   if(!isMany())
   {
      mValues.clear();
   }
   mValues.push_back(value);
}
