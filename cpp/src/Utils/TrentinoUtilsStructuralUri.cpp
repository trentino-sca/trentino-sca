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
#include "TrentinoUtilsStructuralUri.h"

//standard
#include <vector>

using namespace std;
using namespace Trentino::Utils;


const string PropertyName = "property";
const string ServiceBindingName = "service-binding";
const string ServiceName = "service";
const string ReferenceBindingName = "reference-binding";
const string ReferenceName = "reference";

//construction
StructuralUri:: StructuralUri(const std::string& uri) : mUriHelper(uri)
{
}

StructuralUri::StructuralUri(const StructuralUri& source) : mUriHelper(source.mUriHelper)
{
}

StructuralUri::StructuralUri(const UriHelper& uriHelper) : mUriHelper(uriHelper)
{
}

StructuralUri::StructuralUri()
{
   //does nothing here
}

//operators
const StructuralUri& StructuralUri::operator=(const StructuralUri& source)
{
   mUriHelper = source.mUriHelper;
   return (*this);
}

bool StructuralUri::isReferenceBindingUri() const
{
   if(mUriHelper.hasFragment() == true)
   {
      string::size_type foundEntity = mUriHelper.fragment().find(ReferenceBindingName);
      return (foundEntity != string::npos);
   }
   return false;
}

bool StructuralUri::isReferenceUri() const
{
   if(mUriHelper.hasFragment() == true && isReferenceBindingUri() == false)
   {
      string::size_type foundEntity = mUriHelper.fragment().find(ReferenceName);
      return (foundEntity != string::npos);
   }
   return false;
}

bool StructuralUri::isPropertyUri() const
{
   if(mUriHelper.hasFragment() == true)
   {
      string::size_type foundEntity = mUriHelper.fragment().find(PropertyName);
      return (foundEntity != string::npos);
   }
   return false;
}

bool StructuralUri::isServiceUri() const
{
   if(mUriHelper.hasFragment() == true && isServiceBindingUri() == false)
   {
      string::size_type foundEntity = mUriHelper.fragment().find(ServiceName);
      return (foundEntity != string::npos);
   }
   return false;
}

bool StructuralUri::isServiceBindingUri() const
{
   if(mUriHelper.hasFragment() == true)
   {
      string::size_type foundEntity = mUriHelper.fragment().find(ServiceBindingName);
      return (foundEntity != string::npos);
   }
   return false;
}

bool StructuralUri::isComponentUri() const
{
   if(mUriHelper.hasFragment() == false && mUriHelper.hasQuery() == false)   
   {
      return true;
   }
   
   return false;
}

StructuralUri StructuralUri::parent() const
{
   return StructuralUri(mUriHelper.parent());
}

std::string StructuralUri::toString() const
{
   return mUriHelper.toString();
}

std::string StructuralUri::name() const
{
   //! \todo refactor: move to urihelper
   if(mUriHelper.hasFragment() == true)
   {
      return trimFragment(mUriHelper.fragment());
   }
   if(mUriHelper.hasQuery() == true)
      return mUriHelper.query();
   
   if(mUriHelper.path().empty() == false)
   {
      UriHelper::UriPaths paths;
      mUriHelper.splitPath(paths);
      if(paths.size() > 0)
         return paths[paths.size() - 1];
   }

   if(mUriHelper.hasAuthority() == true)
      return mUriHelper.authority();

   return mUriHelper.scheme();
}

string StructuralUri::trimFragment(const string& element) const
{
   string::size_type foundBracketOpen = element.find('(');
   if(foundBracketOpen != string::npos)
   {
      string::size_type foundBracketClose = element.find(')');
      if(foundBracketClose != string::npos)
      {
         if((foundBracketOpen + 1) >= (foundBracketClose - 1))
            return string();
         return element.substr((foundBracketOpen + 1), (foundBracketClose - foundBracketOpen) - 1);
      }
   }

   return element;
}

