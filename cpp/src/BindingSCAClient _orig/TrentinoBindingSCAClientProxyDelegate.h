#ifndef TrentinoBindingSCAClientProxyDelegateH
#define TrentinoBindingSCAClientProxyDelegateH

#include "TrentinoBindingSCAClientImportExport.h"

#include <string>
#include <Binding/CompactSoap/BindingCompactSoapProtobufMessages.h>

//typedef boost::shared_ptr<BindingProxyDelegate> BindingProxyDelegatePtr;

namespace Trentino{
   namespace Binding{
      namespace SCA{
         namespace Client{


            class BindingProxyDelegateImpl;
            
            class  BINDINGSCACLIENT_IMPORT_EXPORT BindingProxyDelegate
               {
               public:
                  BindingProxyDelegate(const char* host);
                  void send(const ::google::protobuf::MessageLite* message, trentino::bindingsca::csoap::Soap* soap, const char* action, const char* from ) const;
               private:
                  typedef boost::shared_ptr<BindingProxyDelegateImpl > InternallHanlderPtr;
                  InternallHanlderPtr mInternalHandler;
               };

            } //namespace Client
         } //namespace SCA
      } //namespace Binding
   } //namespace Trentino
#endif //TrentinoBindingSCAClientProxyDelegateH

