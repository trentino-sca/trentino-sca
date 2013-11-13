#include "ConfigureAndLoadServiceImpl.h"

using namespace siemens::bt::configureandload;

//!Constructors
  ConfigureAndLoadServiceImpl::ConfigureAndLoadServiceImpl()
  {
    //TODO auto generated
  }
  
  ConfigureAndLoadServiceImpl::~ConfigureAndLoadServiceImpl()
  {
    //TODO auto generated
  }
  
 //!Services
  void ConfigureAndLoadServiceImpl::getInterfaceVersion( std::string& _return)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::readConfiguration( ConfigureData& _return, const std::string& authenticationToken)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::writeConfiguration( const std::string& authenticationToken, const ConfigureData& config)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::setNwConfig( const std::string& authenticationToken, const std::vector<dicp::NwItf>& nwItf)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::getNwConfig( std::vector<dicp::NwItf>& _return, const std::string& authenticationToken)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::setBaDevConfig( const std::string& authenticationToken, const dicp::BaDev& dev, const dicp::BaPar& apdu)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::getBaDevConfig( dicp::BaDev& _return, const std::string& authenticationToken)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::getBaParConfig( dicp::BaPar& _return, const std::string& authenticationToken)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::setBaNwConfig( const std::string& authenticationToken, const dicp::BaNw& network, const std::vector<dicp::BaPort>& ports)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::getBaNwConfig( dicp::BaNw& _return, const std::string& authenticationToken)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::getBaPortConfig( std::vector<dicp::BaPort>& _return, const std::string& authenticationToken)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::setUTCTime( const std::string& authenticationToken, const int64_t utctime)
  {
   
  }
  
  int64_t ConfigureAndLoadServiceImpl::getUTCTime( const std::string& authenticationToken)
  {
   return 1;
  }
  
  bool ConfigureAndLoadServiceImpl::processPackAndGo( const std::string& authenticationToken, const std::string& path)
  {
   return false;
  }
  
  int32_t ConfigureAndLoadServiceImpl::getPackAndGoStatus( const std::string& authenticationToken)
  {
   return 1;
  }
  
  bool ConfigureAndLoadServiceImpl::createBackup( const std::string& authenticationToken, const std::string& path)
  {
   return false;
  }
  
  int32_t ConfigureAndLoadServiceImpl::getBackupStatus( const std::string& authenticationToken)
  {
   return 1;
  }
  
  void ConfigureAndLoadServiceImpl::activateConfigData( const std::string& authenticationToken, const bool activate)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::setDeviceConfigParameter( const std::string& authenticationToken, const DeviceConfigParameter& devConfig)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::getDeviceConfigParameter( DeviceConfigParameter& _return, const std::string& authenticationToken)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::setTimeZone( const std::string& authenticationToken, const dicp::TimeSet& tz)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::getTimeZone( dicp::TimeSet& _return, const std::string& authenticationToken)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::addIPPort( dicp::IPport& _return, const std::string& authenticationToken, const dicp::Lan& lanNwItf)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::addLONPort( dicp::LONport& _return, const std::string& authenticationToken, const dicp::Eia709& eia709NwItf)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::addMSTPPort( dicp::MSTPport& _return, const std::string& authenticationToken, const dicp::Rs485& rs485NwItf)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::addLanItf( dicp::Lan& _return, const std::string& authenticationToken)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::addEia709Itf( dicp::Eia709& _return, const std::string& authenticationToken)
  {
   
  }
  
  void ConfigureAndLoadServiceImpl::addRs485Itf( dicp::Rs485& _return, const std::string& authenticationToken)
  {
   
  }
  
  int32_t ConfigureAndLoadServiceImpl::IsMSTPSupported( const std::string& authenticationToken)
  {
   return 1;
  }
  
  int32_t ConfigureAndLoadServiceImpl::IsLONSupported( const std::string& authenticationToken)
  {
   return 1;
  }
  
  bool ConfigureAndLoadServiceImpl::getStateSSH( const std::string& authenticationToken)
  {
   return false;
  }
  
  bool ConfigureAndLoadServiceImpl::startSSH( const std::string& authenticationToken)
  {
   return false;
  }
  
  bool ConfigureAndLoadServiceImpl::stopSSH( const std::string& authenticationToken)
  {
   return false;
  }
  
