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

#ifndef TrentinoSCAModelFactoryH
#define TrentinoSCAModelFactoryH

//specific
#include "TrentinoSCAModel.h"
#include "TrentinoSCAModelMetadata.h"
#include "TrentinoSCAModelMetadataStringAttribute.h"

namespace Trentino{
namespace SCA{
namespace Model
{

   const char* const DefaultNamespaceNameCStr = Trentino::XML::Schema::defaultNamespaceName().c_str();
   const char* const DefaultNamespacePrefixCStr = Trentino::XML::Schema::defaultNamespacePrefix().c_str();


   class SCAMODEL_IMPORT_EXPORT Factory
   {
   public:
	  Trentino::XML::Schema::QName* createQName( const char* localPart = ""
											   , const char* namespaceName = DefaultNamespaceNameCStr
											   , const char* prefix = DefaultNamespacePrefixCStr);
      
<#foreach classInfo in classes>
<#if classInfo.isAbstractClass()==false>
 <#if classInfo.isEnum()==true >
	  ${classInfo.name}* TRENTINO_STDCALL create${classInfo.name}(const char* valueStr);
 <#else>
	  ${classInfo.name}* TRENTINO_STDCALL create${classInfo.name}();
</#if>      
</#if>   
</#foreach>  
   }; //class Factory 

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelFactoryH