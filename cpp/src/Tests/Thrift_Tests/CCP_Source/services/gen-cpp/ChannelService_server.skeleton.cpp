// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "ChannelService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::siemens::bt::channel;

class ChannelServiceHandler : virtual public ChannelServiceIf {
 public:
  ChannelServiceHandler() {
    // Your initialization goes here
  }

  void getInterfaceVersion(std::string& _return) {
    // Your implementation goes here
    printf("getInterfaceVersion\n");
  }

  bool isAvailable() {
    // Your implementation goes here
    printf("isAvailable\n");
  }

  void getBusStatus(BusStatus& _return, const std::string& authToken) {
    // Your implementation goes here
    printf("getBusStatus\n");
  }

  void getBusOverview(OverviewData& _return, const std::string& authToken) {
    // Your implementation goes here
    printf("getBusOverview\n");
  }

  bool reset(const std::string& authToken) {
    // Your implementation goes here
    printf("reset\n");
  }

  bool stop(const std::string& authToken) {
    // Your implementation goes here
    printf("stop\n");
  }

  bool start(const std::string& authToken) {
    // Your implementation goes here
    printf("start\n");
  }

  void getDevices(std::vector<Device> & _return, const std::string& authToken) {
    // Your implementation goes here
    printf("getDevices\n");
  }

  void getDevice(Device& _return, const std::string& authToken, const int32_t devKey) {
    // Your implementation goes here
    printf("getDevice\n");
  }

  int32_t countConnectedDevices(const std::string& authToken) {
    // Your implementation goes here
    printf("countConnectedDevices\n");
  }

  int32_t countConfiguredDevices(const std::string& authToken) {
    // Your implementation goes here
    printf("countConfiguredDevices\n");
  }

  void getDeviceListStatus(BusStatus& _return, const std::string& authToken) {
    // Your implementation goes here
    printf("getDeviceListStatus\n");
  }

  void readOrphanList(std::vector<std::string> & _return, const std::string& authToken) {
    // Your implementation goes here
    printf("readOrphanList\n");
  }

  void getTests(std::vector<PointTest> & _return, const std::string& authToken) {
    // Your implementation goes here
    printf("getTests\n");
  }

  int32_t releaseOverwrite(const std::string& authToken) {
    // Your implementation goes here
    printf("releaseOverwrite\n");
  }

  void incrementValue(std::string& _return, const std::string& authToken, const int32_t key) {
    // Your implementation goes here
    printf("incrementValue\n");
  }

  void decrementValue(std::string& _return, const std::string& authToken, const int32_t key) {
    // Your implementation goes here
    printf("decrementValue\n");
  }

  void setTestValue(std::string& _return, const std::string& authToken, const int32_t key, const double value) {
    // Your implementation goes here
    printf("setTestValue\n");
  }

  void getTestValue(std::string& _return, const std::string& authToken, const int32_t key) {
    // Your implementation goes here
    printf("getTestValue\n");
  }

  int32_t setState(const std::string& authToken, const int32_t key, const int32_t state) {
    // Your implementation goes here
    printf("setState\n");
  }

  void setComment(std::string& _return, const std::string& authToken, const int32_t key, const std::string& value) {
    // Your implementation goes here
    printf("setComment\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<ChannelServiceHandler> handler(new ChannelServiceHandler());
  shared_ptr<TProcessor> processor(new ChannelServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

