#ifndef TxioServiceImpl_H
#define TxioServiceImpl_H

#include <TxioService.h>

namespace siemens { namespace bt { namespace txio { 
class TxioServiceImpl : public TxioServiceIf {
public:
  TxioServiceImpl();
  
  ~TxioServiceImpl();
  
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
  
}; //class TxioServiceImpl

}}}  //namespace
#endif //TxioServiceImpl_H