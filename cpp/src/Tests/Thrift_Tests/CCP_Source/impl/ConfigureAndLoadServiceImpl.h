#ifndef ConfigureAndLoadServiceImpl_H
#define ConfigureAndLoadServiceImpl_H

#include <ConfigureAndLoadService.h>

namespace siemens { namespace bt { namespace configureandload { 
class ConfigureAndLoadServiceImpl : public ConfigureAndLoadServiceIf {
public:
  ConfigureAndLoadServiceImpl();
  
  ~ConfigureAndLoadServiceImpl();
  
  void getInterfaceVersion( std::string& _return);
  
  void readConfiguration( ConfigureData& _return, const std::string& authenticationToken);
  
  void writeConfiguration( const std::string& authenticationToken, const ConfigureData& config);
  
  void setNwConfig( const std::string& authenticationToken, const std::vector<dicp::NwItf>& nwItf);
  
  void getNwConfig( std::vector<dicp::NwItf>& _return, const std::string& authenticationToken);
  
  void setBaDevConfig( const std::string& authenticationToken, const dicp::BaDev& dev, const dicp::BaPar& apdu);
  
  void getBaDevConfig( dicp::BaDev& _return, const std::string& authenticationToken);
  
  void getBaParConfig( dicp::BaPar& _return, const std::string& authenticationToken);
  
  void setBaNwConfig( const std::string& authenticationToken, const dicp::BaNw& network, const std::vector<dicp::BaPort>& ports);
  
  void getBaNwConfig( dicp::BaNw& _return, const std::string& authenticationToken);
  
  void getBaPortConfig( std::vector<dicp::BaPort>& _return, const std::string& authenticationToken);
  
  void setUTCTime( const std::string& authenticationToken, const int64_t utctime);
  
  int64_t getUTCTime( const std::string& authenticationToken);
  
  bool processPackAndGo( const std::string& authenticationToken, const std::string& path);
  
  int32_t getPackAndGoStatus( const std::string& authenticationToken);
  
  bool createBackup( const std::string& authenticationToken, const std::string& path);
  
  int32_t getBackupStatus( const std::string& authenticationToken);
  
  void activateConfigData( const std::string& authenticationToken, const bool activate);
  
  void setDeviceConfigParameter( const std::string& authenticationToken, const DeviceConfigParameter& devConfig);
  
  void getDeviceConfigParameter( DeviceConfigParameter& _return, const std::string& authenticationToken);
  
  void setTimeZone( const std::string& authenticationToken, const dicp::TimeSet& tz);
  
  void getTimeZone( dicp::TimeSet& _return, const std::string& authenticationToken);
  
  void addIPPort( dicp::IPport& _return, const std::string& authenticationToken, const dicp::Lan& lanNwItf);
  
  void addLONPort( dicp::LONport& _return, const std::string& authenticationToken, const dicp::Eia709& eia709NwItf);
  
  void addMSTPPort( dicp::MSTPport& _return, const std::string& authenticationToken, const dicp::Rs485& rs485NwItf);
  
  void addLanItf( dicp::Lan& _return, const std::string& authenticationToken);
  
  void addEia709Itf( dicp::Eia709& _return, const std::string& authenticationToken);
  
  void addRs485Itf( dicp::Rs485& _return, const std::string& authenticationToken);
  
  int32_t IsMSTPSupported( const std::string& authenticationToken);
  
  int32_t IsLONSupported( const std::string& authenticationToken);
  
  bool getStateSSH( const std::string& authenticationToken);
  
  bool startSSH( const std::string& authenticationToken);
  
  bool stopSSH( const std::string& authenticationToken);
  
}; //class ConfigureAndLoadServiceImpl

}}}  //namespace
#endif //ConfigureAndLoadServiceImpl_H