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
#include "TrentinoRuntimeModelCommonFuncs.h"

//specific
#include "TrentinoRuntimeModelComponent.h"
#include "TrentinoRuntimeModelComposite.h"
#include "TrentinoRuntimeModelReference.h"
#include "../SCAModel/TrentinoSCAModelComponent.h"
#include "../SCAModel/TrentinoSCAModelComponentService.h"

using namespace Trentino::RuntimeModel;
using namespace std;

//global funcs
string CommonFuncs::toString(Trentino::RuntimeModel::Contribution::State contributionState)
{
   switch(contributionState)
   {
      case Contribution::None:      return "None";
      case Contribution::Installed: return "Installed";
      case Contribution::Deployed:  return "Deployed";
      case Contribution::Running:   return "Running";
      default:                      return "UnknownState";
   };
}

string CommonFuncs::toString(Trentino::RuntimeModel::ServiceBase::State serviceState)
{
   switch(serviceState)
   {
      case ServiceBase::Available:   return "Available";
      case ServiceBase::Unavailable: return "Unavailable";
      default:                       return "UnknownState";
   };
}

string Trentino::RuntimeModel::CommonFuncs::toString( 
   Trentino::RuntimeModel::ReferenceBase::State referenceState )
{
   switch(referenceState)
   {
      case ReferenceBase::Initial:              return "Initial";
      case ReferenceBase::Resolving:            return "Resolving";
      case ReferenceBase::Resolved:             return "Resolved";
      case ReferenceBase::Unresolved:           return "Unresolved";
      case ReferenceBase::OptionalUnresolved:   return "OptionalUnresolved";
      case ReferenceBase::Unresolving:          return "Unresolving";
      default:                                  return "UnknownState";
   };
}

string Trentino::RuntimeModel::CommonFuncs::toString( 
   Trentino::RuntimeModel::Component::State componentState )
{
   switch(componentState)
   {
      case Component::Initial:              return "Initial";
      case Component::Resolving:            return "Resolving";
      case Component::Resolved:             return "Resolved";
      case Component::Unresolved:           return "Unresolved";
      case Component::OptionalUnresolved:   return "OptionalUnresolved";
      case Component::Stopping:             return "Stopping";
      default:                              return "UnknownState";
   };
}

void CommonFuncs::parseSCAWiringURI( const Trentino::XML::Schema::AnyURI& uri
                                   , std::string& componentName
                                   , std::string& serviceOrReferenceName)
{  
   const size_t slashPosition = uri.find_first_of('/');
   
   //only component name is specified
   if(slashPosition == string::npos)
   {
      componentName = uri;
      serviceOrReferenceName.clear();
   }
   else
   {  
      componentName = uri.substr(0, slashPosition);
      serviceOrReferenceName = uri.substr(slashPosition + 1);
   }
}
