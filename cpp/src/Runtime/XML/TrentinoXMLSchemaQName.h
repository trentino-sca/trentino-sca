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

#ifndef TrentinoXMLSchemaQNameH
#define TrentinoXMLSchemaQNameH

//standard
#include <string>
#include <boost/shared_ptr.hpp>

//specific
#include "TrentinoXMLSchema.h"

#ifdef WIN32
   #ifdef XML_EXPORTS
      #define QNAME_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define QNAME_IMPORT_EXPORT __declspec(dllimport)       
   #endif //XML_EXPORTS
#else
   #define QNAME_IMPORT_EXPORT
#endif //WIN32

namespace Trentino{
namespace XML{
namespace Schema
{
   //**********************************************************************************************
   // G++ requires that all the operators must be decalred in this namespace, so forward
   // declaration is needed.
   //**********************************************************************************************
   class QName;
   QNAME_IMPORT_EXPORT bool operator!=(const QName& lhs, const QName& rhs);
   QNAME_IMPORT_EXPORT bool operator==(const QName& lhs, const QName& rhs);

   //**********************************************************************************************
   //                                          QName
   //**********************************************************************************************
   //! \brief Represents XML qualified names as defined in the XML specification: 
   //!        <a href="http://www.w3.org/TR/xmlschema-2/#QName"> 
   //!        XML Schema Part 2: Datatypes Second Edition<a/>            
   //**********************************************************************************************
   class QName
   {
      //construction
   public:
      //*******************************************************************************************
      //                                          QName()
      //*******************************************************************************************
      //! \brief Constructs a QName with the given local part, namespace name and the 
      //!        corresponding prefix.
      //! \param[in] localPart The local part of the QName. 
      //! \param[in] namespaceName The namespace name of the QName. In case no namespace name is 
      //!            provided, an empty namespace name is assumed.  
      //! \param[in] prefix The prefix of the QName. In case no prefix is provided, an empty prefix
      //!            is assumed. It's not allowed to pass a non-empty prefix if the namespaceName
      //!            is empty; in this case the \c std::invalid_argument exceptino is thrown.  
      //! \exception std::invalid_argument Thrown if an empty \c namespaceName and a non-empty 
      //!            \c prefix are passed.       
      //*******************************************************************************************
      QNAME_IMPORT_EXPORT explicit QName( const NCName& localPart = NCName()
                                        , const AnyURI& namespaceName = defaultNamespaceName()
                                        , const NCName& prefix = defaultNamespacePrefix());
      
      //operators
   public:

      //*******************************************************************************************
      //                                       equality operators
      //*******************************************************************************************
      //!@name equality operators 
      //!Two QName instances are consider to be equal iff their namespace names as well as the
      //! local parts are equal. The prefix is not taken into account. 
      //! \param[in] lsh The left-hand side QName object
      //! \param[in] rhs The right-hand side QName object          
      //*******************************************************************************************
      //!@{
      
      //*******************************************************************************************
      //                                       operator==()
      //*******************************************************************************************
      //! \brief %Tests QName instances for equality      
      //! 
      //! \return \c true if the passed objects are equal, otherwise \c false.
      //*******************************************************************************************
      QNAME_IMPORT_EXPORT friend bool operator==(const QName& lhs, const QName& rhs);

       //*******************************************************************************************
      //                                       operator==()
      //*******************************************************************************************
      //! \brief %Tests QName instances for inequality      
      //! 
      //! \return \c true if the passed objects are unequal, otherwise \c false.
      //*******************************************************************************************
      QNAME_IMPORT_EXPORT friend bool operator!=(const QName& lhs, const QName& rhs);
      //!@}

   private:
      //*******************************************************************************************
      //                                       operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment
      //*******************************************************************************************
      void operator=(const QName&);

      //services
   public:
      //*******************************************************************************************
      //                                          fromString()
      //*******************************************************************************************
      //! \brief Creates a QName from a string representation
      //! \param[in] qNameAsString string representation of the QName. The expected format is as
      //!            follows: <tt>"{" + namespace name + "}" + local part</tt> 
      //!            (see  http://jclark.com/xml/xmlns.htm). If the namespace name is empty,
      //!            only the local part should be provided, otherwise the \c std::invalid_argument
      //!            exception is thrown.
      //! \return QName corresponding to the provided string
      //! \exception std::invalid_argument Thrown if an empty \c namespaceName is provided 
      //!            (e.g. <tt>"{}xyz"</tt>) or the passed doesn't conform to the expected format. 
      //! \sa toString()
      //*******************************************************************************************
      QNAME_IMPORT_EXPORT static QName fromString(const std::string& qNameAsString);

      //*******************************************************************************************
      //                                          localPart()
      //*******************************************************************************************
      //! \brief Returns the local part of the QName
      //! \return local part of the QName
      //*******************************************************************************************
      const NCName& localPart() const;
     
      //*******************************************************************************************
      //                                          localPart()
      //*******************************************************************************************
      //! \brief Returns the namespace name of the QName
      //! \return namespace name of the QName
      //*******************************************************************************************
      const AnyURI& namespaceName() const;

      //*******************************************************************************************
      //                                          prefix()
      //*******************************************************************************************
      //! \brief Returns the prefix of the QName
      //! \return prefix  of the QName
      //*******************************************************************************************
      const NCName& prefix() const;      
      
      //*******************************************************************************************
      //                                          toString()
      //*******************************************************************************************
      //! \brief Returns the string representation of the QName. 
      //!
      //! The string format is as follows: <tt>"{" + namespace name + "}" + local part</tt>
      //! (see also http://jclark.com/xml/xmlns.htm). If the namespace name is empty, only the local
      //! part is returned. Note that the prefix is <b>NOT</b> returned a part of the string 
      //! representation. 
      //! 
      //! \return string representation of the QName
      //! \remark toString() uses lazy initialization: the string representation is created only 
      //!         once when the user requests it for the first time and is then saved as a member.
      //! \attention toString() is \b NOT tread safe.       
      //! \sa QName(const std::string&) 
      //*******************************************************************************************
      QNAME_IMPORT_EXPORT const std::string& toString() const;

      //data
   private:
      //! namespace name of the QName
      const AnyURI mNamespaceName;
      //! local part of the QName
      const NCName mLocalPart;
      //! prefix of the QName
      const NCName mPrefix;
      //! \brief string representation of the QName
      //!
      //! \remark Here we use lazy initialization: the string representation is created only once
      //!         when the user requests it for the first time and is then saved as a member. 
      mutable boost::shared_ptr<std::string> mQNameAsString;
   
   }; //class QName

   #include "TrentinoXMLSchemaQName.inl"

} //namespace Schema
} //namespace XML
} //namespace Trentino


#endif //TrentinoXMLSchemaQNameH