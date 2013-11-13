#include "TxioServiceImpl.h"

using namespace siemens::bt::txio;

//!Constructors
  TxioServiceImpl::TxioServiceImpl()
  {
    //TODO auto generated
  }
  
  TxioServiceImpl::~TxioServiceImpl()
  {
    //TODO auto generated
  }
  
 //!Services
  void TxioServiceImpl::getInterfaceVersion( std::string& _return)
  {
   
  }
  
  bool TxioServiceImpl::isAvailable()
  {
   return false;
  }
  
  void TxioServiceImpl::getBusStatus( BusStatus& _return, const std::string& authToken)
  {
   
  }
  
  void TxioServiceImpl::getBusOverview( OverviewData& _return, const std::string& authToken)
  {
   
  }
  
  bool TxioServiceImpl::reset( const std::string& authToken)
  {
   return false;
  }
  
  bool TxioServiceImpl::stop( const std::string& authToken)
  {
   return false;
  }
  
  bool TxioServiceImpl::start( const std::string& authToken)
  {
   return false;
  }
  
  void TxioServiceImpl::getDevices( std::vector<Device>& _return, const std::string& authToken)
  {
   
  }
  
  void TxioServiceImpl::getDevice( Device& _return, const std::string& authToken, const int32_t devKey)
  {
   
  }
  
  int32_t TxioServiceImpl::countConnectedDevices( const std::string& authToken)
  {
   return 1;
  }
  
  int32_t TxioServiceImpl::countConfiguredDevices( const std::string& authToken)
  {
   return 1;
  }
  
  void TxioServiceImpl::getDeviceListStatus( BusStatus& _return, const std::string& authToken)
  {
   
  }
  
  void TxioServiceImpl::readOrphanList( std::vector<std::string>& _return, const std::string& authToken)
  {
   
  }
  
  void TxioServiceImpl::getTests( std::vector<PointTest>& _return, const std::string& authToken)
  {
   
  }
  
  int32_t TxioServiceImpl::releaseOverwrite( const std::string& authToken)
  {
   return 1;
  }
  
  void TxioServiceImpl::incrementValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  void TxioServiceImpl::decrementValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  void TxioServiceImpl::setTestValue( std::string& _return, const std::string& authToken, const int32_t key, const double value)
  {
   
  }
  
  void TxioServiceImpl::getTestValue( std::string& _return, const std::string& authToken, const int32_t key)
  {
   
  }
  
  int32_t TxioServiceImpl::setState( const std::string& authToken, const int32_t key, const int32_t state)
  {
   return 1;
  }
  
  void TxioServiceImpl::setComment( std::string& _return, const std::string& authToken, const int32_t key, const std::string& value)
  {
   
  }
  
