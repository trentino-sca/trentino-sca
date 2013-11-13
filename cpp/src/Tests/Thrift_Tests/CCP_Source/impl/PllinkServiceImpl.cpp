#include "PllinkServiceImpl.h"

using namespace siemens::bt::pllink;

//!Constructors
  PllinkServiceImpl::PllinkServiceImpl()
  {
    //TODO auto generated
  }
  
  PllinkServiceImpl::~PllinkServiceImpl()
  {
    //TODO auto generated
  }
  
 //!Services
  int32_t PllinkServiceImpl::identifyDevice( const std::string& authToken, const int32_t devKey)
  {
   return 1;
  }
  
  void PllinkServiceImpl::resetDevice( siemens::bt::channel::Device& _return, const std::string& authToken, const int32_t devKey)
  {
   
  }
  
  void PllinkServiceImpl::getInterfaceVersion( std::string& _return)
  {
   
  }
  
  bool PllinkServiceImpl::isAvailable()
  {
   return false;
  }
  
  void PllinkServiceImpl::getBusStatus( BusStatus& _return, const std::string& authToken)
  {
   
  }
  
  void PllinkServiceImpl::getBusOverview( OverviewData& _return, const std::string& authToken)
  {
   
  }
  
  bool PllinkServiceImpl::reset( const std::string& authToken)
  {
   return false;
  }
  
  bool PllinkServiceImpl::stop( const std::string& authToken)
  {
   return false;
  }
  
  bool PllinkServiceImpl::start( const std::string& authToken)
  {
   return false;
  }
  
  void PllinkServiceImpl::getDevices( std::vector<Device>& _return, const std::string& authToken)
  {
   
  }
  
  void PllinkServiceImpl::getDevice( Device& _return, const std::string& authToken, const int32_t devKey)
  {
   
  }
  
  int32_t PllinkServiceImpl::countConnectedDevices( const std::string& authToken)
  {
   return 1;
  }
  
  int32_t PllinkServiceImpl::countConfiguredDevices( const std::string& authToken)
  {
   return 1;
  }
  
  void PllinkServiceImpl::getDeviceListStatus( BusStatus& _return, const std::string& authToken)
  {
   
  }
  
  void PllinkServiceImpl::readOrphanList( std::vector<std::string>& _return, const std::string& authToken)
  {
   
  }
  
  void PllinkServiceImpl::getTests( std::vector<PointTest>& _return, const std::string& authToken)
  {
   
  }
  
  int32_t PllinkServiceImpl::releaseOverwrite( const std::string& authToken)
  {
   return 1;
  }
  
  void PllinkServiceImpl::incrementValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  void PllinkServiceImpl::decrementValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  void PllinkServiceImpl::setTestValue( std::string& _return, const std::string& authToken, const int32_t key, const double value)
  {
   
  }
  
  void PllinkServiceImpl::getTestValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  int32_t PllinkServiceImpl::setState( const std::string& authToken, const int32_t key, const int32_t state)
  {
   return 1;
  }
  
  void PllinkServiceImpl::setComment( std::string& _return, const std::string& authToken, const int32_t key, const std::string& value)
  {
   
  }
  
