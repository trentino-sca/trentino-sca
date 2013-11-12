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
#include "TrentinoUtilsURI.h"

//standard

#include <string>

//const  std::string Trentino::Utils::URIUtil::mProperty("#property(");
//
//const  std::string Trentino::Utils::URIUtil::mServiceBinding("#service-binding(");
//
//const  std::string Trentino::Utils::URIUtil::mService("#service(");
//
//const  std::string Trentino::Utils::URIUtil::mReferenceBinding("#reference-binding(");
//
//const     std::string Trentino::Utils::URIUtil::mReference("#reference(");

//const char*[] Trentino::Utils::URIUtil::mEntities ={"#property(","#service-binding(","#service(","#reference-binding(","#reference("};


using namespace std;


std::vector<std::string> Trentino::Utils::URIUtil::getNameAndComponentURIByEntityURI( const URI& aURI )
{
   std::vector<std::string>  result;
   const size_t closeBracket = aURI.find_last_of(")");
   if(closeBracket == aURI.npos){
      return result;
   }
   const size_t openBracket = aURI.find_last_of("(",closeBracket);
   if(openBracket == aURI.npos){
      return result;
   }
   size_t lastSharp = aURI.find_last_of("#",openBracket);
   if(lastSharp == aURI.npos){
      return result;
   }
   std::string componentURI = aURI.substr(0,lastSharp);
   std::string entityName = aURI.substr(openBracket + 1, closeBracket-openBracket - 1);

   result.push_back(componentURI);
   result.push_back(entityName);
   //regex expression("(.*)#(property|service-binding|service|reference-binding|reference)\((.*)\)");
   ////first extract the componentURI
   //cmatch what; 
   //if(regex_match(aURI.c_str(), what, expression)){
   //   std::string componentURI;
   //   componentURI.assign(what[1].first,what[1].second);
   //   std::string entityName;
   //   entityName.assign(what[3].first,what[3].second);
   //   result.push_back(componentURI);
   //   result.push_back(entityName);

   //   }
   return result;
}




