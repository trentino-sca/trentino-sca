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

#ifndef TrentinoSCAModelFixedH
#define TrentinoSCAModelFixedH

//standard 
#include <map>

//specific
#include "../XML/TrentinoXMLSchemaQName.h"

#ifdef WIN32
   #ifdef SCAMODEL_EXPORTS
      #define SCAMODEL_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define SCAMODEL_IMPORT_EXPORT __declspec(dllimport) 
   #endif //SCAMODEL_EXPORTS
#else
   #define SCAMODEL_IMPORT_EXPORT
#endif //WIN32

namespace Trentino{
namespace SCA{
namespace Model
{
   class ModelDescriptor;

   typedef boost::shared_ptr<ModelDescriptor> ModelDescriptorPtr;
   typedef std::vector<CompositePtr> Composites;
   typedef std::map<const Component*, ComponentTypePtr> ComponentTypeMap; 

   //this is a temporary solution, since for some reason the @multiplicy attribute isn't
   //mapped on enum in the jaxb model (while for example @scop is)
   const std::string ReferenceMultiplicity0to1 = "0..1";
   const std::string ReferenceMultiplicity0toN = "0..n";
   const std::string ReferenceMultiplicity1to1 = "1..1";
   const std::string ReferenceMultiplicity1toN = "1..n";

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelFixedH