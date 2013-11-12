#ifndef TrentinoBindingSCAClientProxyDelegateImplH
#define TrentinoBindingSCAClientProxyDelegateImplH

#include <string>
#include <Binding/CompactSoap/BindingCompactSoapProtobufMessages.h>
#include <zmq.hpp>
#include <boost/thread/tss.hpp>


//typedef boost::shared_ptr<BindingProxyDelegate> BindingProxyDelegatePtr;

namespace Trentino{
   namespace Binding{
      namespace SCA{
         namespace Client{
            typedef boost::thread_specific_ptr<zmq::socket_t> ZMQSocketPtr;
            class  BindingProxyDelegateImpl
               {

               //construction
               public:
                  BindingProxyDelegateImpl(const char* host);
                  ~BindingProxyDelegateImpl();

               public:
                  void send(const ::google::protobuf::MessageLite* message, trentino::bindingsca::csoap::Soap* soap, const char* action, const char* from );

               private:
                  std::string mHost;
                  std::string mFulldestination;
                  zmq::context_t* mContext;
                  ZMQSocketPtr mSocket;
               };

            } //namespace Client
         } //namespace SCA
      } //namespace Binding
   } //namespace Trentino
#endif //TrentinoBindingSCAClientProxyDelegateImplH

