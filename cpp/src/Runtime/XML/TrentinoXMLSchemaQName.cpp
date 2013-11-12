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
#include "TrentinoXMLSchemaQName.h"

//standard
#include <stdexcept>

//specific
#include "../../Global/TrentinoGlobal.h"

using namespace std;
using Trentino::XML::Schema::QName;
using Trentino::XML::Schema::AnyURI;
using Trentino::XML::Schema::NCName;

//class QName
   //construction
QName::QName( const NCName& localPart 
            , const AnyURI& namespaceName 
            , const NCName& prefix )
: mNamespaceName(namespaceName)
, mLocalPart(localPart)
, mPrefix(prefix)
{
   if( (mNamespaceName == Trentino::XML::Schema::defaultNamespaceName()) &&
       (mPrefix != Trentino::XML::Schema::defaultNamespacePrefix()))
   {
      throw invalid_argument("prefix cannot be non-empty if the\
                             namespace name is empty when creating a QName");
   }   
}

   //operators
bool Trentino::XML::Schema::operator==(const QName& lhs, const QName& rhs)
{
   return (lhs.mLocalPart == rhs.mLocalPart) && (lhs.mNamespaceName == rhs.mNamespaceName);
}

bool Trentino::XML::Schema::operator!=(const QName& lhs, const QName& rhs)
{
   return !operator==(lhs, rhs);
}

   //services
QName QName::fromString(const string& qNameAsString)
{  
   //no namespace name is provided => local part only
   if(qNameAsString[0] != '{')
   {
      return QName(qNameAsString);
   }

   const string emptyNamespaceName = "{" + Trentino::XML::Schema::defaultNamespaceName() + "}";
   //if qNameAsString starts with emptyNamespaceName
   if(!qNameAsString.compare(0, emptyNamespaceName.size(), emptyNamespaceName))
   {
      throw invalid_argument(
         "cannot create QName from \"" + qNameAsString + "\", if namespace name equals to \"" +
         Trentino::XML::Schema::defaultNamespaceName() + "\", only the local part should be provided");
               
   }

   const size_t endOfNamespaceName = qNameAsString.find_first_of('}');         
      
   //missing closing '}'
   if(endOfNamespaceName == string::npos)
   {
      throw invalid_argument(
         "cannot create QName from \"" + qNameAsString + "\", missing closing '}'");
   }
  
   //namespace name as well as the local part provided   
   return QName( qNameAsString.substr(endOfNamespaceName + 1)
               , qNameAsString.substr(1, endOfNamespaceName - 1) ); 
}


const string& QName::toString() const
{
   if(!mQNameAsString)
   {
      boost::shared_ptr<string> tmpQNameAsString;
      if(mNamespaceName.empty())
      {
         tmpQNameAsString.reset(new string(mLocalPart));
      }
      else
      {
         tmpQNameAsString.reset(new string());
         tmpQNameAsString->reserve(mNamespaceName.size() + mLocalPart.size() + 2);
         tmpQNameAsString->append("{")
                          .append(mNamespaceName)
                          .append("}")
                          .append(mLocalPart);         
      }

      //exception safety: change the member object only if everything worked 
      mQNameAsString.swap(tmpQNameAsString);
   }

   return *mQNameAsString;
}



