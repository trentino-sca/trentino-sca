#include "ChannelServiceImpl.h"

using namespace siemens::bt::channel;

//!Constructors
  ChannelServiceImpl::ChannelServiceImpl()
  {
    //TODO auto generated
  }
  
  ChannelServiceImpl::~ChannelServiceImpl()
  {
    //TODO auto generated
  }
  
 //!Services
  void ChannelServiceImpl::getInterfaceVersion( std::string& _return)
  {
   
  }
  
  bool ChannelServiceImpl::isAvailable()
  {
   return false;
  }
  
  void ChannelServiceImpl::getBusStatus( BusStatus& _return, const std::string& authToken)
  {
   
  }
  
  void ChannelServiceImpl::getBusOverview( OverviewData& _return, const std::string& authToken)
  {
   
  }
  
  bool ChannelServiceImpl::reset( const std::string& authToken)
  {
   return false;
  }
  
  bool ChannelServiceImpl::stop( const std::string& authToken)
  {
   return false;
  }
  
  bool ChannelServiceImpl::start( const std::string& authToken)
  {
   return false;
  }
  
  void ChannelServiceImpl::getDevices( std::vector<Device>& _return, const std::string& authToken)
  {
   
  }
  
  void ChannelServiceImpl::getDevice( Device& _return, const std::string& authToken, const int32_t devKey)
  {
   
  }
  
  int32_t ChannelServiceImpl::countConnectedDevices( const std::string& authToken)
  {
   return 1;
  }
  
  int32_t ChannelServiceImpl::countConfiguredDevices( const std::string& authToken)
  {
   return 1;
  }
  
  void ChannelServiceImpl::getDeviceListStatus( BusStatus& _return, const std::string& authToken)
  {
   
  }
  
  void ChannelServiceImpl::readOrphanList( std::vector<std::string>& _return, const std::string& authToken)
  {
   
  }
  
  void ChannelServiceImpl::getTests( std::vector<PointTest>& _return, const std::string& authToken)
  {
   
  }
  
  int32_t ChannelServiceImpl::releaseOverwrite( const std::string& authToken)
  {
   return 1;
  }
  
  void ChannelServiceImpl::incrementValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  void ChannelServiceImpl::decrementValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  void ChannelServiceImpl::setTestValue( std::string& _return, const std::string& authToken, const int32_t key, const double value)
  {
   
  }
  
  void ChannelServiceImpl::getTestValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  int32_t ChannelServiceImpl::setState( const std::string& authToken, const int32_t key, const int32_t state)
  {
   return 1;
  }
  
  void ChannelServiceImpl::setComment( std::string& _return, const std::string& authToken, const int32_t key, const std::string& value)
  {
   
  }
  
