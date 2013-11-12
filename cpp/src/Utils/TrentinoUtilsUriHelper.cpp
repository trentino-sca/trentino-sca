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
#include "TrentinoUtilsUriHelper.h"

//standard
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#pragma warning(push)
#pragma warning(disable:4100 4512)
   #include <boost/foreach.hpp>
#pragma warning(pop)


using namespace std;
using namespace Trentino::Utils;


void UriHelper::copyFrom(const UriHelper& source)
{
   mUriString = source.mUriString;
   mScheme = source.mScheme;
   mAuthority = source.mAuthority;
   mPath = source.mPath;
   mQuery = source.mQuery;
   mFragment = source.mFragment;
}

void UriHelper::parseUriString(const string& uriText)
{
   if(uriText.empty() == true)
   {
      invalidate();
   }
   else
   {
      mUriString = uriText;

      //find ":" schema
      string::const_iterator schemeEndIt = std::find(mUriString.begin(), mUriString.end(), ':');
      if(schemeEndIt != mUriString.end())
      {
         string::const_iterator beginStringIt = mUriString.begin();
         mScheme.assign(beginStringIt, schemeEndIt);
      }
      else
         mScheme.clear();

      //query
      string::const_iterator queryStartIt = std::find(mUriString.begin(), mUriString.end(), '?');
      //fragment
      string::const_iterator fragmentStartIt = std::find(mUriString.begin(), mUriString.end(), '#');

      string::const_iterator pathEndIt;
      if(fragmentStartIt < queryStartIt)
         pathEndIt = fragmentStartIt;
      else
         pathEndIt = queryStartIt;

      if (queryStartIt != mUriString.end()) 
         queryStartIt++; // skip '?'
      if (fragmentStartIt != mUriString.end()) 
         fragmentStartIt++; // skip '#'

      string::const_iterator pathStartIt = mUriString.begin();
      string::const_iterator authorityBeginIt = mUriString.begin();
      
      mAuthority.clear();
      string::const_iterator foundAuthorityIt = std::find(pathStartIt, pathEndIt, L'/');
      if(foundAuthorityIt != mUriString.end())
      {
         ++foundAuthorityIt;
         //authority?
         if(*(foundAuthorityIt) == '/')
         {
            ++foundAuthorityIt;
            string::const_iterator authorityEndIt = std::find(foundAuthorityIt, pathEndIt, '/');
            mAuthority.assign(foundAuthorityIt, authorityEndIt);
            pathStartIt = authorityEndIt;
         }
         else
         {
            pathStartIt = std::find(pathStartIt, pathEndIt, ':');
         }
         if(pathStartIt != mUriString.end())
            ++pathStartIt;
      }

      //ok it is malformed, so start from beginning or cap path...
      if(pathStartIt == mUriString.end() && mScheme.empty() == true)
         pathStartIt = mUriString.begin();
      else
         if(pathStartIt == mUriString.begin() && mScheme.empty() == false)
            pathStartIt = mUriString.end();

      mPath.assign(pathStartIt, pathEndIt);

      if(fragmentStartIt != mUriString.end())
      {
         string::const_iterator endStringIt = mUriString.end();
         mFragment.assign(fragmentStartIt, endStringIt);
         --fragmentStartIt;
      }
      else
         mFragment.clear();

      if(queryStartIt != mUriString.end())
         mQuery.assign(queryStartIt, fragmentStartIt);
      else
         mQuery.clear();
   }
}

void UriHelper::invalidate()
{
   mUriString.clear();
   mScheme.clear();
   mAuthority.clear();
   mPath.clear();
   mQuery.clear();
   mFragment.clear();
}

void UriHelper::splitPath(UriHelper::UriPaths& uriPaths, bool skipEmptyPath) const
{
   uriPaths.clear();
   if(mPath.empty() == false)
   {
      UriHelper::UriPaths newPaths;
      boost::split(newPaths, mPath, boost::is_any_of("/"));
      if(skipEmptyPath == false)
      {
         uriPaths = newPaths;         
      }
      else
      {
         if(newPaths.size() != 0)
         {
            uriPaths.reserve(newPaths.size());
            BOOST_FOREACH(const string& path, newPaths)
            {
               if(path.empty() == false)
                  uriPaths.push_back(path);
            }
         }
      }
   }
}

void UriHelper::composeUri( const std::string& scheme,const std::string& authority
                        ,const std::string& path, const std::string& query
                        ,const std::string& fragment)
{
   invalidate();
   string newUri;
   if(scheme.empty() == false)
      newUri = scheme + ":";
   if(authority.empty() == false)
   {
      newUri += "//" + authority;
      if(path.empty() == false)
         newUri += "/";
   }

   newUri += path;
   if(query.empty() == false)
      newUri += "?" + query;
   if(fragment.empty() == false)
      newUri += "#" + fragment;
   
   if(newUri.empty() == false)
      parseUriString(newUri);
}

UriHelper UriHelper::parent() const
{
   string elements[5];
   elements[0] = mScheme;
   elements[1] = mAuthority;
   elements[2] = mPath;
   elements[3] = mQuery;
   elements[4] = mFragment;
   int i = 5;
   while(i--)
   {
      if(elements[i].empty() == false)
      {
         //path
         if(i == 2)
         {
            UriHelper::UriPaths paths;
            splitPath(paths);
            string newPath;
            for(int j = 0; j < (int)paths.size() - 1; j++)
            {
               if(newPath.empty())
                  newPath += paths[j];
               else
                  newPath += "/" + paths[j];
            }
            elements[i] = newPath;
         }
         else
            elements[i].clear();
         break;
      }
   }

   UriHelper result;
   result.composeUri(elements[0], elements[1], elements[2], elements[3], elements[4]);

   return result;
}
