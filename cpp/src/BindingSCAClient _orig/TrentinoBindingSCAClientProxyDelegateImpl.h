#ifndef TrentinoBindingSCAClientProxyDelegateImplH
#define TrentinoBindingSCAClientProxyDelegateImplH

#include <string>
#include <Binding/CompactSoap/BindingCompactSoapProtobufMessages.h>

//typedef boost::shared_ptr<BindingProxyDelegate> BindingProxyDelegatePtr;

namespace Trentino{
   namespace Binding{
      namespace SCA{
         namespace Client{
            class  BindingProxyDelegateImpl
               {
               //construction
               public:
                  BindingProxyDelegateImpl(const char* host);

               public:
                  void send(const ::google::protobuf::MessageLite* message, trentino::bindingsca::csoap::Soap* soap, const char* action, const char* from ) const;

               private:
                  std::string mHost;
                  std::string mFulldestination;
               };

            } //namespace Client
         } //namespace SCA
      } //namespace Binding
   } //namespace Trentino
#endif //TrentinoBindingSCAClientProxyDelegateImplH

