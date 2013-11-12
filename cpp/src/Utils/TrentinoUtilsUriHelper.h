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

#ifndef TrentinoUtilsUriHelperH
#define TrentinoUtilsUriHelperH

//standard
#include <string>
#include <vector>

#ifdef WIN32
#ifdef UTILS_EXPORTS
#define URIUTIL_IMPORT_EXPORT __declspec(dllexport)
#else
#define URIUTIL_IMPORT_EXPORT __declspec(dllimport)       
#endif //UTILS_EXPORTS
#else
#define URIUTIL_IMPORT_EXPORT
#endif //WIN32


namespace Trentino{
namespace Utils
{
   class UriHelper
   {
      //additional
   public:
      typedef std::vector<std::string> UriPaths;
      //construction
   public:
      UriHelper();
      explicit UriHelper(const std::string& uri);
      UriHelper(const UriHelper& source);
      UriHelper( const std::string& scheme
                ,const std::string& authority
                ,const std::string& path
                ,const std::string& query
                ,const std::string& fragment);

      //operators
   public:
      const UriHelper& operator=(const UriHelper& source);
      const UriHelper& operator=(const std::string uri);

      //services
   public:
      void URIUTIL_IMPORT_EXPORT copyFrom(const UriHelper& source);
      void URIUTIL_IMPORT_EXPORT setFromString(const std::string& uri);

      const std::string& scheme() const;
      bool hasAuthority() const;
      const std::string& authority() const;
      bool hasQuery() const;
      const std::string query() const;
      bool hasFragment() const;
      const std::string fragment() const;
      const std::string& path() const;
      const std::string toString() const;

      void URIUTIL_IMPORT_EXPORT splitPath(UriPaths& uriPaths, 
                                           bool skipEmptyPath = true) const;
      void URIUTIL_IMPORT_EXPORT composeUri(
                 const std::string& scheme
                ,const std::string& authority
                ,const std::string& path
                ,const std::string& query
                ,const std::string& fragment);

      UriHelper URIUTIL_IMPORT_EXPORT parent() const;
      //management
   private:
      void URIUTIL_IMPORT_EXPORT parseUriString(const std::string& uriText);
      void URIUTIL_IMPORT_EXPORT invalidate();

      //data
   private:
      std::string mUriString;
      std::string mScheme;
      std::string mAuthority;
      std::string mPath;

      //! \todo split?
      std::string mQuery;
      std::string mFragment;
   }; //class UriHelper

   #include "TrentinoUtilsUriHelper.inl"

} //namespace Utils
} //namespace Trentino

#endif//TrentinoUtilsUriHelperH

