#ifndef DaliServiceImpl_H
#define DaliServiceImpl_H

#include <DaliService.h>

namespace siemens { namespace bt { namespace dali { 
class DaliServiceImpl : public DaliServiceIf {
public:
  DaliServiceImpl();
  
  ~DaliServiceImpl();
  
  bool isBusy( const std::string& authToken);
  
  bool lightsOn( const std::string& authToken);
  
  bool lightsOff( const std::string& authToken);
  
  bool lightsBlink( const std::string& authToken);
  
  bool autoassignDevices( const std::string& authToken);
  
  void getOrphans( std::vector<siemens::bt::channel::Orphan>& _return, const std::string& authToken);
  
  bool blinkOrphan( const std::string& authToken, const int32_t networkAddress);
  
  bool blinkPDO( const std::string& authToken, const int32_t deviceLogical);
  
  int32_t identifyDevice( const std::string& authToken, const int32_t devKey, const int32_t deviceLogical, const int32_t networkAddress, const bool reset);
  
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
  
}; //class DaliServiceImpl

}}}  //namespace
#endif //DaliServiceImpl_H