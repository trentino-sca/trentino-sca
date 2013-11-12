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
#include "TrentinoTestsUtilsUriParser.h"

//standard
#include <string>

//specific
#include "./../../Utils/TrentinoUtilsUriHelper.h"
#include "./../../Utils/TrentinoUtilsStructuralUri.h"
#include "./../../Utils/TrentinoUtilsSCAWiringUri.h"


using namespace std;
using namespace Trentino::Tests::Utils;
using namespace Trentino::Utils;


const string myPath1 = "myPath1";
const string myPath2 = "myPath2";
const string myPath3 = "myPath3";
const string mySchemeName = "myScheme";
const string myAuthorityName = "myAuthority";
const string myPathName = myPath1 + "/" + myPath2;
const string myPathNameEx = myPath1 + "/" + myPath2 + "/" + myPath3;
const string myQueryName = "myQueryName=myValue";
const string myFragmentName = "myFragmentName";

const string myURIFull0 = 
   mySchemeName + ":" + "//" + myAuthorityName + "/" + myPathNameEx + "?" + myQueryName + 
   "#" + myFragmentName;

const string myURIFull1 = 
   mySchemeName + ":" + "//" + myAuthorityName + "/" + myPathName + "?" + myQueryName + "#" + 
   myFragmentName;

const string myURIFull2 = 
   mySchemeName + ":" + "//" + myAuthorityName + "/" + myPathName + "?" + myQueryName;

const string myURIFull3 = 
   mySchemeName + ":" + "//" + myAuthorityName + "/" + myPathName;

const string myURIFull4 = 
   mySchemeName + ":" + "//" + myAuthorityName + "/" + myPathName + "#" + myFragmentName;

const string myURIFull5 = 
   mySchemeName + ":" + "/" + myPathName + "?" + myQueryName + "#" + myFragmentName;

const string myURIFull6 = 
   mySchemeName + ":" + myPathName + "?" + myQueryName + "#" + myFragmentName;

const string myURIFull7 = 
   mySchemeName + ":" + myPathName + "?" + myQueryName;

const string myURIFull8 = 
   mySchemeName + ":" + myPathName + "#" + myFragmentName;

const string myURIFull9 = 
   mySchemeName + ":" + myPathName;

const string myURIFull10 = 
   myPathName;

const string myURIFull11 = 
   mySchemeName + ":";

const string myURIFull12 = 
   myPathName;

const string myURIPropertyName = myURIFull3 + "#property(foo)";
const string myURIServiceBindingName = myURIFull3 + "#service-binding(foo)";
const string myURIServiceName = myURIFull3 + "#service(foo)";
const string myURIReferenceBindingName = myURIFull3 + "#reference-binding(foo)";
const string myURIReferenceName = myURIFull3 + "#reference(foo)";
const string mURISCAWiringServiceName = "component/serviceName";
const string mURISCAWiringServiceName2 = "/component/serviceName";
const string mURISCAWiringNoRefSvcName2 = "component";


#define ASSERT_STREQ2(str1, str2)\
   ASSERT_STREQ(str1.c_str(), str2.c_str());\

TEST(UriParserTest, testSCAWirtingUri)
{
   SCAWiringUri uriService(mURISCAWiringServiceName);
   ASSERT_EQ(uriService.hasServiceOrReferenceName(), true);
   ASSERT_STREQ(uriService.serviceOrReferenceName().c_str(), "serviceName");
   ASSERT_STREQ(uriService.componentName().c_str(), "component");
   SCAWiringUri uriService2(mURISCAWiringServiceName2);
   ASSERT_EQ(uriService2.hasServiceOrReferenceName(), true);
   ASSERT_STREQ(uriService2.serviceOrReferenceName().c_str(), "component/serviceName");
   ASSERT_STREQ2(uriService2.componentName(), string());
   SCAWiringUri uriNonRefSvc2(mURISCAWiringNoRefSvcName2);
   ASSERT_EQ(uriNonRefSvc2.hasServiceOrReferenceName(), false);
   ASSERT_STREQ2(uriNonRefSvc2.serviceOrReferenceName(), string());
   ASSERT_STREQ(uriNonRefSvc2.componentName().c_str(), "component");
}

//class UriParserTest
TEST(UriParserTest, testStructuralUri)
{ 
   StructuralUri uriProperty(myURIPropertyName);
   ASSERT_EQ(uriProperty.isPropertyUri(), true);
   ASSERT_EQ(uriProperty.isServiceBindingUri(), false);
   ASSERT_EQ(uriProperty.isServiceUri(), false);
   ASSERT_EQ(uriProperty.isReferenceUri(), false);
   ASSERT_EQ(uriProperty.isReferenceBindingUri(), false);
   ASSERT_EQ(uriProperty.name(), string("foo"));

   StructuralUri uriServiceBinding(myURIServiceBindingName);
   ASSERT_EQ(uriServiceBinding.isPropertyUri(), false);
   ASSERT_EQ(uriServiceBinding.isServiceBindingUri(), true);
   ASSERT_EQ(uriServiceBinding.isServiceUri(), false);
   ASSERT_EQ(uriServiceBinding.isReferenceUri(), false);
   ASSERT_EQ(uriServiceBinding.isReferenceBindingUri(), false);

   StructuralUri uriService(myURIServiceName);
   ASSERT_EQ(uriService.isPropertyUri(), false);
   ASSERT_EQ(uriService.isServiceBindingUri(), false);
   ASSERT_EQ(uriService.isServiceUri(), true);
   ASSERT_EQ(uriService.isReferenceUri(), false);
   ASSERT_EQ(uriService.isReferenceBindingUri(), false);

   StructuralUri uriReferenceBinding(myURIReferenceBindingName);
   ASSERT_EQ(uriReferenceBinding.isPropertyUri(), false);
   ASSERT_EQ(uriReferenceBinding.isServiceBindingUri(), false);
   ASSERT_EQ(uriReferenceBinding.isServiceUri(), false);
   ASSERT_EQ(uriReferenceBinding.isReferenceUri(), false);
   ASSERT_EQ(uriReferenceBinding.isReferenceBindingUri(), true);

   StructuralUri uriReference(myURIReferenceName);
   ASSERT_EQ(uriReference.isPropertyUri(), false);
   ASSERT_EQ(uriReference.isServiceBindingUri(), false);
   ASSERT_EQ(uriReference.isServiceUri(), false);
   ASSERT_EQ(uriReference.isReferenceUri(), true);
   ASSERT_EQ(uriReference.isReferenceBindingUri(), false);

   StructuralUri uriIsComponentTest(myURIFull3);
   ASSERT_EQ(uriIsComponentTest.isComponentUri(), true);
   StructuralUri uriIsNotComponentTest(myURIFull8);
   ASSERT_EQ(uriIsNotComponentTest.isComponentUri(), false);

   // test name
   StructuralUri uriNameTest(myURIFull1);
   ASSERT_STREQ(uriNameTest.name().c_str(), myFragmentName.c_str());
   ASSERT_STREQ(uriNameTest.parent().name().c_str(), myQueryName.c_str());
   ASSERT_STREQ(uriNameTest.parent().parent().name().c_str(), myPath2.c_str());
   ASSERT_STREQ(uriNameTest.parent().parent().parent().name().c_str(), myPath1.c_str());
   ASSERT_STREQ(uriNameTest.parent().parent().parent().parent().name().c_str(), myAuthorityName.c_str());
   ASSERT_STREQ(uriNameTest.parent().parent().parent().parent().parent().name().c_str(), mySchemeName.c_str());
}


TEST(UriParserTest, testHelperUri)
{
   UriHelper uriHlp;   
   uriHlp = myURIFull1;

   ASSERT_STREQ(uriHlp.scheme().c_str(), mySchemeName.c_str());
   ASSERT_STREQ(uriHlp.authority().c_str(), myAuthorityName.c_str());
   ASSERT_EQ(uriHlp.hasAuthority(), true);
   ASSERT_STREQ(uriHlp.path().c_str(), myPathName.c_str());
   ASSERT_EQ(uriHlp.hasQuery(), true);
   ASSERT_STREQ(uriHlp.query().c_str(), myQueryName.c_str());
   ASSERT_EQ(uriHlp.hasFragment(), true);
   ASSERT_STREQ(uriHlp.fragment().c_str(), myFragmentName.c_str());

   UriHelper::UriPaths uriPaths;
   uriHlp.splitPath(uriPaths);
   ASSERT_EQ(uriPaths.size(), 2U);
   ASSERT_STREQ(uriPaths[0].c_str(), myPath1.c_str());
   ASSERT_STREQ(uriPaths[1].c_str(), myPath2.c_str());

   uriHlp = myURIFull2;
   ASSERT_STREQ(uriHlp.scheme().c_str(), mySchemeName.c_str());
   ASSERT_STREQ(uriHlp.authority().c_str(), myAuthorityName.c_str());
   ASSERT_STREQ(uriHlp.path().c_str(), myPathName.c_str());
   ASSERT_EQ(uriHlp.hasQuery(), true);
   ASSERT_STREQ2(uriHlp.query(), myQueryName);
   ASSERT_EQ(uriHlp.hasFragment(), false);

   uriHlp = myURIFull3;
   ASSERT_STREQ2(uriHlp.scheme(), mySchemeName);
   ASSERT_STREQ2(uriHlp.authority(), myAuthorityName);
   ASSERT_STREQ2(uriHlp.path(), myPathName);
   ASSERT_EQ(uriHlp.hasQuery(), false);
   ASSERT_EQ(uriHlp.hasFragment(), false);

   uriHlp = myURIFull4;
   ASSERT_STREQ2(uriHlp.scheme(), mySchemeName);
   ASSERT_STREQ2(uriHlp.authority(), myAuthorityName);
   ASSERT_STREQ2(uriHlp.path(), myPathName);
   ASSERT_EQ(uriHlp.hasFragment(), true);
   ASSERT_STREQ2(uriHlp.fragment(), myFragmentName);
   ASSERT_EQ(uriHlp.hasQuery(), false);

   uriHlp = myURIFull5;
   ASSERT_STREQ2(uriHlp.scheme(), mySchemeName);
   ASSERT_EQ(uriHlp.hasAuthority(), false);
   const string extraPathName = "/" + myPathName;
   ASSERT_STREQ2(uriHlp.path(), extraPathName);
   ASSERT_EQ(uriHlp.hasQuery(), true);
   ASSERT_STREQ2(uriHlp.query(), myQueryName);
   ASSERT_EQ(uriHlp.hasFragment(), true);
   ASSERT_STREQ2(uriHlp.fragment(), myFragmentName);

   uriHlp = myURIFull6;
   ASSERT_STREQ2(uriHlp.scheme(), mySchemeName);
   ASSERT_EQ(uriHlp.hasAuthority(), false);
   ASSERT_STREQ2(uriHlp.path(), myPathName);
   ASSERT_EQ(uriHlp.hasQuery(), true);
   ASSERT_STREQ2(uriHlp.query(), myQueryName);
   ASSERT_EQ(uriHlp.hasFragment(), true);
   ASSERT_STREQ2(uriHlp.fragment(), myFragmentName);

   uriHlp = myURIFull7;
   ASSERT_STREQ2(uriHlp.scheme(), mySchemeName);
   ASSERT_EQ(uriHlp.hasAuthority(), false);
   ASSERT_STREQ2(uriHlp.path(), myPathName);
   ASSERT_EQ(uriHlp.hasQuery(), true);
   ASSERT_STREQ2(uriHlp.query(), myQueryName);
   ASSERT_EQ(uriHlp.hasFragment(), false);

   uriHlp = myURIFull8;
   ASSERT_STREQ2(uriHlp.scheme(), mySchemeName);
   ASSERT_EQ(uriHlp.hasAuthority(), false);
   ASSERT_STREQ2(uriHlp.path(), myPathName);
   ASSERT_EQ(uriHlp.hasQuery(), false);
   ASSERT_EQ(uriHlp.hasFragment(), true);
   ASSERT_STREQ2(uriHlp.fragment(), myFragmentName);

   uriHlp = myURIFull9;
   ASSERT_STREQ2(uriHlp.scheme(), mySchemeName);
   ASSERT_EQ(uriHlp.hasAuthority(), false);
   ASSERT_STREQ2(uriHlp.path(), myPathName);
   ASSERT_EQ(uriHlp.hasQuery(), false);
   ASSERT_EQ(uriHlp.hasFragment(), false);

   //malformed but works
   uriHlp = myURIFull10;
   ASSERT_TRUE(uriHlp.scheme().empty() == true);
   ASSERT_EQ(uriHlp.hasAuthority(), false);
   ASSERT_STREQ2(uriHlp.path(), myPathName);
   ASSERT_EQ(uriHlp.hasQuery(), false);
   ASSERT_EQ(uriHlp.hasFragment(), false);

   //malformed but works
   uriHlp = myURIFull11;
   ASSERT_STREQ2(uriHlp.scheme(), mySchemeName);
   ASSERT_TRUE(uriHlp.path().empty() == true);
   ASSERT_EQ(uriHlp.hasAuthority(), false);
   ASSERT_EQ(uriHlp.hasQuery(), false);
   ASSERT_EQ(uriHlp.hasFragment(), false);

   //malformed but works, returns full uri in path()
   uriHlp = myURIFull12;
   ASSERT_TRUE(uriHlp.scheme().empty() == true);
   ASSERT_STREQ2(uriHlp.path(), myURIFull12);
   ASSERT_EQ(uriHlp.hasAuthority(), false);
   ASSERT_EQ(uriHlp.hasQuery(), false);
   ASSERT_EQ(uriHlp.hasFragment(), false);

   // check parent
   uriHlp = myURIFull0;
   // remove fragment
   UriHelper uriCopy1 = uriHlp.parent();
   ASSERT_STREQ2(uriCopy1.scheme(), mySchemeName);
   ASSERT_STREQ2(uriCopy1.authority(), myAuthorityName);
   ASSERT_EQ(uriCopy1.hasAuthority(), true);
   ASSERT_STREQ2(uriCopy1.path(), myPathNameEx);
   ASSERT_EQ(uriCopy1.hasQuery(), true);
   ASSERT_STREQ2(uriCopy1.query(), myQueryName);
   ASSERT_EQ(uriCopy1.hasFragment(), false);

   // remove query
   UriHelper uriCopy2 = uriCopy1.parent();
   ASSERT_STREQ2(uriCopy2.scheme(), mySchemeName);
   ASSERT_STREQ2(uriCopy2.authority(), myAuthorityName);
   ASSERT_EQ(uriCopy2.hasAuthority(), true);
   ASSERT_STREQ2(uriCopy2.path(), myPathNameEx);
   ASSERT_EQ(uriCopy2.hasQuery(), false);
   ASSERT_EQ(uriCopy2.hasFragment(), false);

   // remove path3
   UriHelper uriCopy3 = uriCopy2.parent();
   ASSERT_STREQ2(uriCopy3.scheme(), mySchemeName);
   ASSERT_STREQ2(uriCopy3.authority(), myAuthorityName);
   ASSERT_EQ(uriCopy3.hasAuthority(), true);
   ASSERT_STREQ2(uriCopy3.path(), myPathName);
   ASSERT_EQ(uriCopy3.hasQuery(), false);
   ASSERT_EQ(uriCopy3.hasFragment(), false);

   // remove path2
   UriHelper uriCopy4 = uriCopy3.parent();
   ASSERT_STREQ2(uriCopy4.scheme(), mySchemeName);
   ASSERT_STREQ2(uriCopy4.authority(), myAuthorityName);
   ASSERT_EQ(uriCopy4.hasAuthority(), true);
   ASSERT_STREQ2(uriCopy4.path(), myPath1);
   ASSERT_EQ(uriCopy4.hasQuery(), false);
   ASSERT_EQ(uriCopy4.hasFragment(), false);

   // remove path1
   UriHelper uriCopy5 = uriCopy4.parent();
   ASSERT_STREQ2(uriCopy5.scheme(), mySchemeName);
   ASSERT_STREQ2(uriCopy5.authority(), myAuthorityName);
   ASSERT_EQ(uriCopy5.hasAuthority(), true);
   ASSERT_TRUE(uriCopy5.path().empty() == true);
   ASSERT_EQ(uriCopy5.hasQuery(), false);
   ASSERT_EQ(uriCopy5.hasFragment(), false);

   // remove authority
   UriHelper uriCopy6 = uriCopy5.parent();
   ASSERT_STREQ2(uriCopy6.scheme(), mySchemeName);
   ASSERT_EQ(uriCopy6.hasAuthority(), false);
   ASSERT_TRUE(uriCopy6.path().empty() == true);
   ASSERT_EQ(uriCopy6.hasQuery(), false);
   ASSERT_EQ(uriCopy6.hasFragment(), false);

   // remove all
   UriHelper uriCopy7 = uriCopy6.parent();
   ASSERT_TRUE(uriCopy7.scheme().empty() == true);
   ASSERT_EQ(uriCopy7.hasAuthority(), false);
   ASSERT_TRUE(uriCopy7.path().empty() == true);
   ASSERT_EQ(uriCopy7.hasQuery(), false);
   ASSERT_EQ(uriCopy7.hasFragment(), false);

}
