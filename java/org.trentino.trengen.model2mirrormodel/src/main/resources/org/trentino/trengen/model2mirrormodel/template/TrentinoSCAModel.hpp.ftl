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

#ifndef TrentinoSCAModelH
#define TrentinoSCAModelH

//standard 
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

//specific
#include "../../Global/TrentinoGlobal.h"
#include "../XML/TrentinoXMLSchema.h"
#include "../XML/TrentinoXMLSchemaQName.h"

namespace Trentino{
namespace SCA{
namespace Model
{
<#foreach classInfo in classes>
   class ${classInfo.name};
</#foreach>

   typedef boost::shared_ptr<Trentino::XML::Schema::QName> QNamePtr;  
<#foreach classInfo in classes>
   typedef boost::shared_ptr<${classInfo.name}> ${classInfo.name}Ptr;
</#foreach>
   
} //namespace Model
} //namespace SCA
} //namespace Trentino

#include "TrentinoSCAModelFixed.h"

#endif //TrentinoSCAModelH