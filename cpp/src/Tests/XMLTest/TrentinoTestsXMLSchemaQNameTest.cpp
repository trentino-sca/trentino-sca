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
#include "TrentinoTestsXMLSchemaQNameTest.h"

//standard
#include <stdexcept>


#pragma warning(push)
#pragma warning(disable:4127)

//specific
#include "../../Runtime/XML/TrentinoXMLSchemaQName.h"

using Trentino::Tests::XML::Schema::QNameTest;
using Trentino::XML::Schema::QName;


//class QNameTest 
   //services
TEST_F(QNameTest, testConstruction)
{
   EXPECT_THROW( QName("localPart", Trentino::XML::Schema::defaultNamespaceName(), "prefix")
                       , std::invalid_argument);
   EXPECT_THROW( QName("", Trentino::XML::Schema::defaultNamespaceName(), "prefix")
                       , std::invalid_argument);
}

TEST_F(QNameTest, testGetter)
{ 
   const QName qName1;
   ASSERT_TRUE( qName1.localPart() == "" );
   ASSERT_TRUE( qName1.namespaceName() == Trentino::XML::Schema::defaultNamespaceName() );
   ASSERT_TRUE( qName1.prefix() == Trentino::XML::Schema::defaultNamespacePrefix() );
   
   const QName qName2("localPart");
   ASSERT_TRUE( qName2.localPart() == "localPart");
   ASSERT_TRUE( qName2.namespaceName() == Trentino::XML::Schema::defaultNamespaceName() );
   ASSERT_TRUE( qName2.prefix() == Trentino::XML::Schema::defaultNamespacePrefix() );

   const QName qName3("localPart", "namespaceName");
   ASSERT_TRUE( qName3.localPart() == "localPart" );
   ASSERT_TRUE( qName3.namespaceName() == "namespaceName" );
   ASSERT_TRUE( qName3.prefix() == Trentino::XML::Schema::defaultNamespacePrefix() );

   const QName qName4("localPart", "namespaceName", "prefix");
   ASSERT_TRUE( qName4.localPart() == "localPart" );
   ASSERT_TRUE( qName4.namespaceName() == "namespaceName" );
   ASSERT_TRUE( qName4.prefix() == "prefix" );   
}

TEST_F(QNameTest, testStringConversion)
{     
   ASSERT_TRUE( QName().toString().empty() );   
   ASSERT_TRUE( QName("localPart").toString() == "localPart" );
   ASSERT_TRUE( QName("localPart", "namespaceName").toString() == 
                   "{namespaceName}localPart" );
   ASSERT_TRUE( QName("localPart", "namespaceName", "prefix").toString() == 
                  "{namespaceName}localPart" );

   const QName qName1 = QName::fromString("");
   ASSERT_TRUE( qName1.localPart() == "" );
   ASSERT_TRUE( qName1.namespaceName() == Trentino::XML::Schema::defaultNamespaceName() );
   ASSERT_TRUE( qName1.prefix() == Trentino::XML::Schema::defaultNamespacePrefix() ); 

   const QName qName2 = QName::fromString("localPart");
   ASSERT_TRUE( qName2.localPart() == "localPart");
   ASSERT_TRUE( qName2.namespaceName() == Trentino::XML::Schema::defaultNamespaceName() );
   ASSERT_TRUE( qName2.prefix() == Trentino::XML::Schema::defaultNamespacePrefix() );

   const QName qName3 = QName::fromString("{namespaceName}localPart");
   ASSERT_TRUE( qName3.localPart() == "localPart" );
   ASSERT_TRUE( qName3.namespaceName() == "namespaceName" );
   ASSERT_TRUE( qName3.prefix() == Trentino::XML::Schema::defaultNamespacePrefix() );

   EXPECT_THROW( QName::fromString("{}localPart"), std::invalid_argument );
   EXPECT_THROW( QName::fromString("{localPart"), std::invalid_argument );
}

TEST_F(QNameTest, testEquality)
{
   ASSERT_TRUE( QName() == QName() );
   ASSERT_TRUE( QName("localPart") == QName("localPart") );
   ASSERT_TRUE( QName("localPart1") != QName("localPart2") );
   ASSERT_TRUE( QName() != QName("localPart") );
   ASSERT_TRUE( QName("localPart", "namespaceName") == 
                   QName("localPart", "namespaceName") );
   ASSERT_TRUE( QName("localPart1", "namespaceName") != 
                   QName("localPart2", "namespaceName") );
   ASSERT_TRUE( QName("localPart", "namespaceName1") != 
                   QName("localPart", "namespaceName2") );
   ASSERT_TRUE( QName("localPart", "namespaceName", "prefix1") == 
                   QName("localPart", "namespaceName", "prefix2") );
   ASSERT_TRUE( QName("localPart", "namespaceName", "prefix1") == 
                   QName("localPart", "namespaceName") );
}

#pragma warning(pop)
