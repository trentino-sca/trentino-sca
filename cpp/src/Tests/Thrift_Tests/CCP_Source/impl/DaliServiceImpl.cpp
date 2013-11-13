#include "DaliServiceImpl.h"

using namespace siemens::bt::dali;

//!Constructors
  DaliServiceImpl::DaliServiceImpl()
  {
    //TODO auto generated
  }
  
  DaliServiceImpl::~DaliServiceImpl()
  {
    //TODO auto generated
  }
  
 //!Services
  bool DaliServiceImpl::isBusy( const std::string& authToken)
  {
   return false;
  }
  
  bool DaliServiceImpl::lightsOn( const std::string& authToken)
  {
   return false;
  }
  
  bool DaliServiceImpl::lightsOff( const std::string& authToken)
  {
   return false;
  }
  
  bool DaliServiceImpl::lightsBlink( const std::string& authToken)
  {
   return false;
  }
  
  bool DaliServiceImpl::autoassignDevices( const std::string& authToken)
  {
   return false;
  }
  
  void DaliServiceImpl::getOrphans( std::vector<siemens::bt::channel::Orphan>& _return, const std::string& authToken)
  {
   
  }
  
  bool DaliServiceImpl::blinkOrphan( const std::string& authToken, const int32_t networkAddress)
  {
   return false;
  }
  
  bool DaliServiceImpl::blinkPDO( const std::string& authToken, const int32_t deviceLogical)
  {
   return false;
  }
  
  int32_t DaliServiceImpl::identifyDevice( const std::string& authToken, const int32_t devKey, const int32_t deviceLogical, const int32_t networkAddress, const bool reset)
  {
   return 1;
  }
  
  void DaliServiceImpl::resetDevice( siemens::bt::channel::Device& _return, const std::string& authToken, const int32_t devKey)
  {
   
  }
  
  void DaliServiceImpl::getInterfaceVersion( std::string& _return)
  {
   
  }
  
  bool DaliServiceImpl::isAvailable()
  {
   return false;
  }
  
  void DaliServiceImpl::getBusStatus( BusStatus& _return, const std::string& authToken)
  {
   
  }
  
  void DaliServiceImpl::getBusOverview( OverviewData& _return, const std::string& authToken)
  {
   
  }
  
  bool DaliServiceImpl::reset( const std::string& authToken)
  {
   return false;
  }
  
  bool DaliServiceImpl::stop( const std::string& authToken)
  {
   return false;
  }
  
  bool DaliServiceImpl::start( const std::string& authToken)
  {
   return false;
  }
  
  void DaliServiceImpl::getDevices( std::vector<Device>& _return, const std::string& authToken)
  {
   
  }
  
  void DaliServiceImpl::getDevice( Device& _return, const std::string& authToken, const int32_t devKey)
  {
   
  }
  
  int32_t DaliServiceImpl::countConnectedDevices( const std::string& authToken)
  {
   return 1;
  }
  
  int32_t DaliServiceImpl::countConfiguredDevices( const std::string& authToken)
  {
   return 1;
  }
  
  void DaliServiceImpl::getDeviceListStatus( BusStatus& _return, const std::string& authToken)
  {
   
  }
  
  void DaliServiceImpl::readOrphanList( std::vector<std::string>& _return, const std::string& authToken)
  {
   
  }
  
  void DaliServiceImpl::getTests( std::vector<PointTest>& _return, const std::string& authToken)
  {
   
  }
  
  int32_t DaliServiceImpl::releaseOverwrite( const std::string& authToken)
  {
   return 1;
  }
  
  void DaliServiceImpl::incrementValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  void DaliServiceImpl::decrementValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  void DaliServiceImpl::setTestValue( std::string& _return, const std::string& authToken, const int32_t key, const double value)
  {
   
  }
  
  void DaliServiceImpl::getTestValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  int32_t DaliServiceImpl::setState( const std::string& authToken, const int32_t key, const int32_t state)
  {
   return 1;
  }
  
  void DaliServiceImpl::setComment( std::string& _return, const std::string& authToken, const int32_t key, const std::string& value)
  {
   
  }
  
