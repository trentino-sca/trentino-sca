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

#ifndef TrentinoCoreContributionLoadingH
#define TrentinoCoreContributionLoadingH

//standard
#include <boost/shared_ptr.hpp>

//specific
#include "TrentinoCoreException.h"
#include "../XML/TrentinoXMLSchemaQName.h"

namespace Trentino{
namespace Core{
//! \defgroup ContributionLoading
namespace ContributionLoading
{
   //constants
   extern const Trentino::XML::Schema::QName XSDTypeImplementationComposite/*(
      "SCAImplementation", "http://docs.oasis-open.org/ns/opencsa/sca/200912")*/;
   extern const Trentino::XML::Schema::QName XSDTypeImplementationCPP/*(
      "CPPImplementation", "http://docs.oasis-open.org/ns/opencsa/sca/200912")*/;
   extern const Trentino::XML::Schema::QName XSDTypeInterfaceCPP/*(
      "CPPInterface", "http://docs.oasis-open.org/ns/opencsa/sca/200912")*/;

   //enums
   enum Error 
   { 
      ComponentNotFoundError,
      ServiceNotFoundError,
      ServiceIncombatibleError,
      AmbigousServicesError,
      ReferenceNotFoundError,
      AmbigousReferencesError,
      NoCompatibleServicesError,
      ComponentUnresolvedError,
      CyclicDependencyError,
      CompositeNotFoundError,
      ComponentTypeNotFoundError,
      //! \todo RuntimeModel::CPPImplementation should be refactored to throw a custom 
      //!       exception containing the ReflectObjectNotFoundError error code (and maybe
      //!       some more) because methods of CPPImplementation also must signalize errors
      //!       about non existent reflection objects. Now it happens via std::runtime_error 
      //!       without that the catcher can identify the cause of the error. Moreover, this 
      //!       makes the error handling (and testing) for ContributionLoader less consistent.
      ReflectObjectNotFoundError,
      ProxyInstanceNotCreatedError,
      CompositeNotDeployedError,
      CompositeNotRunError        
   };

   enum Warning
   {
      CompositeNotFoundWarning
   };

   //typedefs
   typedef Trentino::Core::Exception<Error> ErrorException;

   class ErrorHandlerBase;
   class ContributionLoader;
   typedef boost::shared_ptr<ContributionLoader> ContributionLoaderPtr;
   typedef boost::shared_ptr<ErrorHandlerBase> ErrorHandlerBasePtr;
   typedef boost::shared_ptr<const ErrorHandlerBase> ConstErrorHandlerBasePtr;

} //namespace ContributionLoading
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreContributionLoadingH
