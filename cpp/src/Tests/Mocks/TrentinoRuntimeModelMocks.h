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
#ifndef TrentinoRuntimeModelMocksH
#define TrentinoRuntimeModelMocksH

#include <gmock/gmock.h>
#include "../../Runtime/Invocation/TrentinoInvocation.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModel.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelServiceBase.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelReferenceBase.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelWireBase.h"
#include "../../Runtime/Binding/TrentinoBindingBindingHelperBase.h"

namespace Trentino{
namespace RuntimeModel{
namespace Tests{

class MockServiceBase : public Trentino::RuntimeModel::ServiceBase{
public:
   MOCK_CONST_METHOD0(scaServiceType,
      Trentino::SCA::Model::ComponentServicePtr());
   MOCK_CONST_METHOD0(scaService, Trentino::SCA::Model::ComponentServicePtr());
   MOCK_CONST_METHOD0(component,
      ComponentWeakPtr());
   MOCK_CONST_METHOD0(serviceInvocationWrapper,
      Trentino::Invocation::ServiceInvocationWrapperBasePtr());
   MOCK_METHOD1(setServiceInvocationWrapper,
      void(const Trentino::Invocation::ServiceInvocationWrapperBasePtr&));
   MOCK_CONST_METHOD0(state,
      ServiceBase::State());
   MOCK_METHOD1(bindingHelperByBindingId,
      Trentino::Binding::BindingHelperBasePtr(const std::string& bindingId));
   MOCK_CONST_METHOD0(name,
      const Trentino::XML::Schema::NCName&());
   MOCK_CONST_METHOD0(isRemotable,bool());
   MOCK_CONST_METHOD0(promotedTo,
      Trentino::RuntimeModel::ServiceBaseWeakPtr());
   MOCK_METHOD1(setPromotedTo,
      void(const Trentino::RuntimeModel::ServiceBasePtr&));
   MOCK_CONST_METHOD0(promotedBy,
      Trentino::RuntimeModel::WeakServiceBases&());
   MOCK_METHOD1(addPromotedBy,
      void(const Trentino::RuntimeModel::ServiceBasePtr&));
   MOCK_METHOD0(wireableSupport,
      Trentino::RuntimeModel::Wireable&());
   MOCK_CONST_METHOD0(mutex,
      boost::recursive_mutex&());
   MOCK_CONST_METHOD0(bindings,
      const std::set<std::string>());
   MOCK_CONST_METHOD0(metaData,const Trentino::SCA::Model::MetadataPtr());

   MOCK_CONST_METHOD0(discoveryId, const std::string());

   //MOCK_METHOD1(setDiscoveryId, void(std::string));
   void setDiscoveryId(const std::string id)
   {

   }
   
};


class MockReferenceBase : public Trentino::RuntimeModel::ReferenceBase {
public:
   MOCK_CONST_METHOD0(scaReferenceType,
      Trentino::SCA::Model::ComponentTypeReferencePtr());
   MOCK_CONST_METHOD0(scaReference,
      Trentino::SCA::Model::ComponentReferencePtr());
   MOCK_METHOD1(setSCAReference,
      void(const Trentino::SCA::Model::ComponentReferencePtr&));
   MOCK_CONST_METHOD0(component,
      ComponentWeakPtr());
   MOCK_CONST_METHOD0(state,
      ReferenceBase::State());
   MOCK_METHOD1(setState,
      void(ReferenceBase::State));
   MOCK_METHOD1(setSetterMethod,
      void(const Trentino::Reflection::ReflectMethodPtr&));
   MOCK_METHOD1(setProxyReflectObject,
      void(const Trentino::Reflection::ReflectObjectPtr&));
   MOCK_CONST_METHOD0(name,
      const Trentino::XML::Schema::NCName&());
   MOCK_CONST_METHOD0(getTargetServices,
      const ServiceBases());
   MOCK_CONST_METHOD0(promotedTo,
      const WeakReferenceBases&());
   MOCK_METHOD1(addPromotedTo,
      void(const WeakReferenceBases&));
   MOCK_CONST_METHOD0(promotedBy,
      const WeakReferenceBases&());
   MOCK_METHOD1(addPromotedBy,
      void(const WeakReferenceBases&));
   MOCK_METHOD0(wireableSupport,
      Wireable&());
   MOCK_CONST_METHOD0(wireableSupport,
      const Wireable&());
   MOCK_CONST_METHOD2(invokeSetter,
      void(void*, void*));
   MOCK_CONST_METHOD2(invokeSetter,
      void(void*, const ReferenceBase::VoidPtrList&));
   MOCK_CONST_METHOD0(proxyReflectObject,
      Trentino::Reflection::ReflectObjectPtr());
   };


class MockWireBase : public Trentino::RuntimeModel::WireBase {
   public:
      MOCK_METHOD0(wire,
         void());
      MOCK_METHOD0(unwire,
         void());
      MOCK_METHOD0(unwireService,
         void());
      MOCK_CONST_METHOD0(reference,
         ReferenceBaseWeakPtr());
      MOCK_CONST_METHOD0(service,
         const std::string&());
      MOCK_CONST_METHOD0(originalService,
         ServiceBaseWeakPtr());
      MOCK_CONST_METHOD0(invocationContext,
         Trentino::Invocation::InvocationContextPtr());
      MOCK_METHOD1(setInvocationContext,
         void(const Trentino::Invocation::InvocationContextPtr&));
      MOCK_CONST_METHOD0(proxy,
         ProxyPtr());
      MOCK_METHOD1(setProxy,
         void(const ProxyPtr&));

   };


}  // namespace Mocks
}  // namespace RuntimeModel
}  // namespace Trentino

#endif //TrentinoRuntimeModelMocksH