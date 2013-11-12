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
#include "TrentinoCoreContributionLoadingErrorMessageHelpers.h"

//standard
#include <sstream>

//specific
#include "../RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../RuntimeModel/TrentinoRuntimeModelReferenceBase.h"
#include "../SCAModel/TrentinoSCAModelComposite.h"
#include "../SCAModel/TrentinoSCAModelComponent.h"
#include "../SCAModel/TrentinoSCAModelComponentReference.h"
#include "../../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"

using namespace std;
using namespace Trentino;
namespace ContributionLoading = Trentino::Core::ContributionLoading;

string ContributionLoading::errorMessageComponent( const string& componentName
                                                 , const string& cause)
{   
   HLOGGER();   
   HLOGGER_INFO(componentName.c_str());

   return "'" + cause + "' error for <component> with @name='" + componentName + "'.";   
}

string ContributionLoading::errorMessageService( const string& componentName
                                               , const string& serviceName
                                               , const string& cause)
{
   HLOGGER();   
   HLOGGER_INFO(serviceName.c_str());

   return "'" + cause + "' error for <service> with @name='" + serviceName 
              + "' in <component> with @name='" + componentName + "'.";
}

string ContributionLoading::errorMessageReferencedInReference( 
   const RuntimeModel::ConstReferenceBasePtr& reference,
   const string& attribute)
{
   HLOGGER();   
   HLOGGER_INFO(reference->name().c_str());

   const RuntimeModel::ConstComponentPtr component = reference->component().lock();
   assert(component);
   const RuntimeModel::ConstCompositePtr composite = component->composite().lock();
   assert(composite);

   ostringstream errorMsg;
   errorMsg << "Referenced in " << attribute << " at <reference> with @name='" 
            << reference->name() << "' "
            << "in <component> with @name='" << component->scaComponent()->name() 
            << "' in <composite> with @name='" << composite->scaComposite()->name() << "'";
   return errorMsg.str();
}

string ContributionLoading::errorMessageReferencedInWire( 
   const string& attribute,
   const RuntimeModel::ConstCompositePtr& parentComposite)
{   
   HLOGGER();   
   HLOGGER_INFO(parentComposite->scaComposite()->name().c_str());

   ostringstream errorMsg;
   errorMsg << "Referenced in @" << attribute << " at <wire> "       
            << "in <composite> with @name= '" << parentComposite->scaComposite()->name() << "'";

   return errorMsg.str();
}