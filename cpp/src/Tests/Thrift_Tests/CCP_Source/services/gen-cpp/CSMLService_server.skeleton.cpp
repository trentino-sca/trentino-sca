// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "CSMLService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::siemens::bt::csml;

class CSMLServiceHandler : virtual public CSMLServiceIf {
 public:
  CSMLServiceHandler() {
    // Your initialization goes here
  }

  void getInterfaceVersion(std::string& _return) {
    // Your implementation goes here
    printf("getInterfaceVersion\n");
  }

  void CSMLRequest(std::string& _return, const std::string& p_Request) {
    // Your implementation goes here
    printf("CSMLRequest\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<CSMLServiceHandler> handler(new CSMLServiceHandler());
  shared_ptr<TProcessor> processor(new CSMLServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

