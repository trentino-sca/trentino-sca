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

#ifndef TrentinoRuntimeModelCommonFuncsH
#define TrentinoRuntimeModelCommonFuncsH

//standard
#include <string>
#pragma warning(push)
#pragma warning(disable:4100)
   #include <boost/algorithm/string/replace.hpp>
#pragma warning(pop)

//specific
#include "TrentinoRuntimeModelContribution.h"
#include "TrentinoRuntimeModelServiceBase.h"
#include "TrentinoRuntimeModelReference.h"
#include "TrentinoRuntimeModelComponent.h"
#include "TrentinoRuntimeModelProperty.h"
#include "../../Utils/TrentinoUtilsURI.h"
#include "../XML/TrentinoXMLSchema.h"

namespace Trentino{
namespace RuntimeModel{
//*************************************************************************************************
//                               namespace CommonFuncs
//*************************************************************************************************
//! \ingroup RuntimeModel
//*************************************************************************************************
namespace CommonFuncs
{
   //**********************************************************************************************
   //                                     proxyName()
   //**********************************************************************************************
   //! \brief Computes the name of the proxy class for the given service class name.
   //!
   //! \param[in] serviceClassName Fully qualified class name.
   //! The proxy class name is built by replacing all the occurrences of the scope operator 
   //! ("::") in \c serviceClassName with underscores and finally appending the "Proxy" suffix.
   //!
   //! \par Example: 
   //! \code
   //! const std::string nameOfProxy = proxyName("MyNamespace1::MyNamespace2::MyClass");
   //! assert(namreOfProxy == "MyNamespace1_MyNamespace2_MyClassProxy");
   //! \endcode
   //! \remark The returned proxy name is the class the runtime expects to be defined in the
   //!         generated code (loaded with a contribution) when searching for a service proxy for 
   //!         a given service. 
   //**********************************************************************************************
   std::string proxyName(const std::string& serviceClassName);

   //**********************************************************************************************
   //                      setterName(const RuntimeModel::ConstReferenceBasePtr&)
   //**********************************************************************************************
   //! \brief Computes the name of the setter method for the given reference.
   //!
   //! \param[in] reference A shared pointer to the reference the setter method should be 
   //!            retrieved for. Passing an empty pointer will cause undefined behavior.
   //!
   //! The setter method name is computed by prepending the reference's name with "set".
   //! 
   //! \par Example:
   //! \code
   //! assert(reference->scaReferenceType()->name() == "MyService");
   //! const std::string nameOfSetter = setterName(reference);
   //! assert(nameOfSetter == "setMyService");
   //! \endcode
   //! \remark The returned setter name is the method the runtime expects to be defined in the
   //!         implementation class of the reference's parent component and for which the runtime
   //!         expects corresponding reflection objects to be present in the generated code 
   //!         (loaded with a contribution).   
   //**********************************************************************************************
   std::string setterName(const Trentino::RuntimeModel::ConstReferenceBasePtr& reference); 

   
   //**********************************************************************************************
   //                      setterName(const RuntimeModel::ConstPropertyPtr&)
   //**********************************************************************************************
   //! \brief Computes the name of the setter method for the given property.
   //!
   //! \param[in] reference A shared pointer to the property the setter method should be 
   //!            retrieved for. Passing an empty pointer will cause undefined behavior.
   //!
   //! The setter method name is computed by prepending the property's name with "set".
   //! 
   //! \par Example:
   //! \code
   //! assert(property->scaPropertyType()->name() == "MyProperty");
   //! const std::string nameOfSetter = setterName(property);
   //! assert(nameOfSetter == "setMyProperty");
   //! \endcode
   //! \remark The returned setter name is the method the runtime expects to be defined in the
   //!         implementation class of the property's parent component and for which the runtime
   //!         expects corresponding reflection objects to be present in the generated code 
   //!         (loaded with a contribution).   
   //**********************************************************************************************
   std::string setterName(const Trentino::RuntimeModel::ConstPropertyPtr& property);

   //**********************************************************************************************
   //! \name String representations      
   //! @{
   //! The functions in this group return string representations for enum values describing states
   //! of different entities available in the RuntimeModel. 
   //! \param[in] Enum value describing a valid state.
   //! \return A string representation for the given enum value or "UnknownState" if an invalid
   //!         value or a value with no defined string representatin is passed.
   //**********************************************************************************************
   std::string toString(Trentino::RuntimeModel::Contribution::State contributionState);
   std::string toString(Trentino::RuntimeModel::ServiceBase::State serviceState);
   std::string toString(Trentino::RuntimeModel::ReferenceBase::State referenceState);
   std::string toString(Trentino::RuntimeModel::Component::State componentState);
   //! @}  
      
   //**********************************************************************************************
   //                               parseSCAWiringURI()
   //**********************************************************************************************
   //! \brief Extracts the component and service or reference names from an URI of the form 
   //!        <component-name>/<service-name> or <component-name>/<reference-name>.
   //!
   //! URIs of such a form are used e.g. in <wire>/@source or <reference>/@target attributes.
   //! \param[in] anyURI Source URI to be parsed.
   //! \param[out] componentName Contains the component name after execution.
   //! \param[out] serviceOrReferenceName Contains the service or reference name after execution 
   //              or an empty string in case uri doesn't contain a "second part" name.
   //**********************************************************************************************
   void parseSCAWiringURI( const Trentino::XML::Schema::AnyURI& uri
                         , std::string& componentName
                         , std::string& serviceOrReferenceName);           

   #include "TrentinoRuntimeModelCommonFuncs.inl"

} //namespace CommonFuncs
} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelCommonFuncsH