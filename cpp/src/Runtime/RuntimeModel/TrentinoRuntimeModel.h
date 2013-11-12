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

#ifndef TrentinoRuntimeModelH
#define TrentinoRuntimeModelH

//standard
#include <vector>
#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#ifdef WIN32
   #ifdef RUNTIMEMODEL_EXPORTS
      #define RUNTIMEMODEL_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define RUNTIMEMODEL_IMPORT_EXPORT __declspec(dllimport)       
   #endif //RUNTIMEMODEL_EXPORTS
#else
   #define RUNTIMEMODEL_IMPORT_EXPORT
#endif //WIN32


namespace Trentino{
namespace XML{
namespace Schema
{
   class QName;
} //namespace Schema
} //namespace XML
} //namespace Trentino

namespace Trentino{
//! \defgroup RuntimeModel
namespace RuntimeModel
{
   //forward declarations
   class ServiceBase;
   class Contribution;
   class Composite;
   class Component;
   class Service;
   class Reference;
   class ReferenceBase;
   class Property;
   class Implementation;   
   class CPPImplementation;
   class Wireable;
   class WireBase;
   class Wire;

   class ErrorCode;
   class Visitor;



   //shared pointers
   typedef boost::shared_ptr<Contribution> ContributionPtr;
   typedef boost::shared_ptr<const Contribution> ConstContributionPtr;
   typedef boost::shared_ptr<Composite> CompositePtr;
   typedef boost::shared_ptr<const Composite> ConstCompositePtr;
   typedef boost::shared_ptr<Component> ComponentPtr;
   typedef boost::shared_ptr<const Component> ConstComponentPtr;
   typedef boost::shared_ptr<ServiceBase> ServiceBasePtr;
   typedef boost::shared_ptr<const ServiceBase> ConstServiceBasePtr;
   typedef boost::shared_ptr<ReferenceBase> ReferenceBasePtr;  
   typedef boost::shared_ptr<const ReferenceBase> ConstReferenceBasePtr; 
   typedef boost::shared_ptr<Property> PropertyPtr;
   typedef boost::shared_ptr<const Property> ConstPropertyPtr;
   typedef boost::shared_ptr<Implementation> ImplementationPtr;
   typedef boost::shared_ptr<const Implementation> ConstImplementationPtr;
   typedef boost::shared_ptr<CPPImplementation> CPPImplementationPtr;
   typedef boost::shared_ptr<const CPPImplementation> ConstCPPImplementationPtr;
   typedef boost::shared_ptr<WireBase> WireBasePtr;
   typedef boost::shared_ptr<const WireBase> ConstWireBasePtr;
   typedef boost::shared_ptr<Wire> WirePtr;
   typedef boost::shared_ptr<const Trentino::XML::Schema::QName> ConstQNamePtr;      
   typedef boost::shared_ptr<void> ProxyPtr;
   typedef boost::shared_ptr<Visitor> VisitorPtr;
   

   //weak pointers
   typedef boost::weak_ptr<Contribution> ContributionWeakPtr;  
   typedef boost::weak_ptr<Composite> CompositeWeakPtr;  
   typedef boost::weak_ptr<Component> ComponentWeakPtr;
   typedef boost::weak_ptr<ServiceBase> ServiceBaseWeakPtr;
   typedef boost::weak_ptr<ReferenceBase> ReferenceBaseWeakPtr;

   //collections
   typedef std::vector<CompositePtr> Composites;
   typedef std::vector<ComponentPtr> Components;
   typedef std::vector<ServiceBasePtr> ServiceBases;   
   typedef std::vector<ServiceBaseWeakPtr> WeakServiceBases;
   typedef std::vector<ReferenceBasePtr> ReferenceBases;
   typedef std::vector<ReferenceBaseWeakPtr> WeakReferenceBases;
   typedef std::vector<PropertyPtr> Properties;
   typedef std::set<WireBasePtr> WireBases;


} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelH
