#ifndef PllinkServiceImpl_H
#define PllinkServiceImpl_H

#include <PllinkService.h>

namespace siemens { namespace bt { namespace pllink { 
class PllinkServiceImpl : public PllinkServiceIf {
public:
  PllinkServiceImpl();
  
  ~PllinkServiceImpl();
  
  int32_t identifyDevice( const std::string& authToken, const int32_t devKey);
  
  void resetDevice( siemens::bt::channel::Device& _return, const std::string& authToken, const int32_t devKey);
  
  void getInterfaceVersion( std::string& _return);
  
  bool isAvailable();
  
  void getBusStatus( BusStatus& _return, const std::string& authToken);
  
  void getBusOverview( OverviewData& _return, const std::string& authToken);
  
  bool reset( const std::string& authToken);
  
  bool stop( const std::string& authToken);
  
  bool start( const std::string& authToken);
  
  void getDevices( std::vector<Device>& _return, const std::string& authToken);
  
  void getDevice( Device& _return, const std::string& authToken, const int32_t devKey);
  
  int32_t countConnectedDevices( const std::string& authToken);
  
  int32_t countConfiguredDevices( const std::string& authToken);
  
  void getDeviceListStatus( BusStatus& _return, const std::string& authToken);
  
  void readOrphanList( std::vector<std::string>& _return, const std::string& authToken);
  
  void getTests( std::vector<PointTest>& _return, const std::string& authToken);
  
  int32_t releaseOverwrite( const std::string& authToken);
  
  void incrementValue( std::string& _return, const std::string& authToken, const int32_t key);
  
  void decrementValue( std::string& _return, const std::string& authToken, const int32_t key);
  
  void setTestValue( std::string& _return, const std::string& authToken, const int32_t key, const double value);
  
  void getTestValue( std::string& _return, const std::string& authToken, const int32_t key);
  
  int32_t setState( const std::string& authToken, const int32_t key, const int32_t state);
  
  void setComment( std::string& _return, const std::string& authToken, const int32_t key, const std::string& value);
  
}; //class PllinkServiceImpl

}}}  //namespace
#endif //PllinkServiceImpl_H