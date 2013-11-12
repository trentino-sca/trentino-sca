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
#include "TrentinoUtilsSCAWiringUri.h"

using namespace std;
using namespace Trentino::Utils;

const string ServiceName = "service";
const string ReferenceName = "reference";

SCAWiringUri::SCAWiringUri(const std::string& uri) : mUriHelper(uri)
{
}

SCAWiringUri::SCAWiringUri(const SCAWiringUri& source) : mUriHelper(source.mUriHelper)
{
}

SCAWiringUri::SCAWiringUri(const UriHelper& uriHelper) : mUriHelper(uriHelper)
{
}

const SCAWiringUri& SCAWiringUri::operator=(const SCAWiringUri& source)
{
   mUriHelper = source.mUriHelper;
   return (*this);
}

std::string SCAWiringUri::componentName() const
{
   if(mUriHelper.path().empty() == false)
   {
      UriHelper::UriPaths paths;
      mUriHelper.splitPath(paths, false);
      if(paths.size() >= 1)
      {
         return paths[0];
      }
   }
   return string();
}

string SCAWiringUri::serviceOrReferenceName() const
{
   if(mUriHelper.path().empty() == false)
   {
      UriHelper::UriPaths paths;
      mUriHelper.splitPath(paths, false);
      if(paths.size() >= 2)
      {
         string srvRefName;
         for(size_t i = 1; i < paths.size(); i++)
         {
            if(i > 1)
               srvRefName += "/" + paths[i];
            else
               srvRefName = paths[i];

         }
         return srvRefName;
      }
   }

   return string();
}

bool SCAWiringUri::hasServiceOrReferenceName() const
{
   if(mUriHelper.path().empty() == false)
   {
      UriHelper::UriPaths paths;
      mUriHelper.splitPath(paths, false);
      if(paths.size() >= 2)
         return true;
   }
   return false;
}

SCAWiringUri SCAWiringUri::parent() const
{
   return SCAWiringUri(mUriHelper.parent());
}

string SCAWiringUri::name() const
{
   //! \todo refactor: move to urihelper
   /*
   if(mUriHelper.hasFragment() == true)
      return mUriHelper.fragment();
   if(mUriHelper.hasQuery() == true)
      return mUriHelper.query();
   */
   if(mUriHelper.path().empty() == false)
   {
      UriHelper::UriPaths paths;
      mUriHelper.splitPath(paths, false);
      if(paths.size() > 0)
         return paths[paths.size() - 1];
   }

   /*
   if(mUriHelper.hasAuthority() == true)
      return mUriHelper.authority();

   return mUriHelper.scheme();
   */
   return string();
}
