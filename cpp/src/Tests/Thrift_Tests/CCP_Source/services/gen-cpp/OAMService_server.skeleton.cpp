// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "OAMService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::siemens::bt::oam;

class OAMServiceHandler : virtual public OAMServiceIf {
 public:
  OAMServiceHandler() {
    // Your initialization goes here
  }

  void serviceCall( ::siemens::bt::type::ServiceResult& _return, const std::string& authenticationToken, const std::string& viewState, const  ::siemens::bt::type::ServiceCommand& command) {
    // Your implementation goes here
    printf("serviceCall\n");
  }

  void prepareBackgroundImage(ImageResult& _return, const std::string& authToken, const std::string& viewId, const int32_t pageId, const std::string& imageDestPath) {
    // Your implementation goes here
    printf("prepareBackgroundImage\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<OAMServiceHandler> handler(new OAMServiceHandler());
  shared_ptr<TProcessor> processor(new OAMServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

