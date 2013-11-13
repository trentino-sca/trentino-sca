// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "DaliService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::siemens::bt::dali;

class DaliServiceHandler : virtual public DaliServiceIf {
 public:
  DaliServiceHandler() {
    // Your initialization goes here
  }

  bool isBusy(const std::string& authToken) {
    // Your implementation goes here
    printf("isBusy\n");
  }

  bool lightsOn(const std::string& authToken) {
    // Your implementation goes here
    printf("lightsOn\n");
  }

  bool lightsOff(const std::string& authToken) {
    // Your implementation goes here
    printf("lightsOff\n");
  }

  bool lightsBlink(const std::string& authToken) {
    // Your implementation goes here
    printf("lightsBlink\n");
  }

  bool autoassignDevices(const std::string& authToken) {
    // Your implementation goes here
    printf("autoassignDevices\n");
  }

  void getOrphans(std::vector< ::siemens::bt::channel::Orphan> & _return, const std::string& authToken) {
    // Your implementation goes here
    printf("getOrphans\n");
  }

  bool blinkOrphan(const std::string& authToken, const int32_t networkAddress) {
    // Your implementation goes here
    printf("blinkOrphan\n");
  }

  bool blinkPDO(const std::string& authToken, const int32_t deviceLogical) {
    // Your implementation goes here
    printf("blinkPDO\n");
  }

  int32_t identifyDevice(const std::string& authToken, const int32_t devKey, const int32_t deviceLogical, const int32_t networkAddress, const bool reset) {
    // Your implementation goes here
    printf("identifyDevice\n");
  }

  void resetDevice( ::siemens::bt::channel::Device& _return, const std::string& authToken, const int32_t devKey) {
    // Your implementation goes here
    printf("resetDevice\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<DaliServiceHandler> handler(new DaliServiceHandler());
  shared_ptr<TProcessor> processor(new DaliServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

