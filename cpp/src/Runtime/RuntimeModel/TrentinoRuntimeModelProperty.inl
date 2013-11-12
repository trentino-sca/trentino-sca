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

//class Property
   //services
inline Trentino::SCA::Model::PropertyPtr Property::scaPropertyType() const
{
   return mSCAPropertyType;
}

inline Trentino::RuntimeModel::ComponentWeakPtr Property::component() const
{
   return mComponent;
}

inline Trentino::SCA::Model::PropertyValuePtr Property::scaProperty() const
{
   return mSCAProperty;
}    

inline void Property::setSCAProperty(const Trentino::SCA::Model::PropertyValuePtr& scaProperty)
{
   mSCAProperty = scaProperty;
}

inline Trentino::Reflection::ReflectMethodPtr Property::setterMethod() const
{
   return mSetter;
}

inline void Property::setSetterMethod(const Trentino::Reflection::ReflectMethodPtr& setter)
{
   mSetter = setter;
}

inline const Property::Values& Property::values() const
{
   return mValues;
}

inline const Trentino::XML::Schema::NCName& Property::name() const
{
   assert(mSCAPropertyType);
   return mSCAPropertyType->name();
}

inline bool Property::isMany() const
{
   assert(mSCAPropertyType);
   return mSCAProperty ? mSCAProperty->isMany() : mSCAPropertyType->isMany();
}

inline std::string Property::type() const
{
   assert(mSCAPropertyType);
   return (mSCAProperty && mSCAProperty->type()) ? mSCAProperty->type()->localPart() : mSCAPropertyType->type()->localPart();
}
      
