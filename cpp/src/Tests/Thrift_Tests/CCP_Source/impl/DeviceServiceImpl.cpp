#include "DeviceServiceImpl.h"

using namespace siemens::bt::device;

//!Constructors
  DeviceServiceImpl::DeviceServiceImpl()
  {
    //TODO auto generated
  }
  
  DeviceServiceImpl::~DeviceServiceImpl()
  {
    //TODO auto generated
  }
  
 //!Services
  void DeviceServiceImpl::getInterfaceVersion( std::string& _return)
  {
   
  }
  
  bool DeviceServiceImpl::setControlProgramState( const std::string& authenticationToken, const siemens::bt::type::ControlProgramState::type ctrlState)
  {
   return false;
  }
  
  siemens::bt::type::ControlProgramState::type DeviceServiceImpl::getControlProgramState( const std::string& authenticationToken)
  {
   // return value goes here
  }
  
  void DeviceServiceImpl::getASN( std::string& _return, const std::string& authenticationToken)
  {
   
  }
  
  void DeviceServiceImpl::authenticate( siemens::bt::type::AuthenticationResult& _return, const std::string& authenticationToken)
  {
   
  }
  
  void DeviceServiceImpl::authorize( siemens::bt::type::AuthenticationResult& _return, const std::string& authenticationToken)
  {
   
  }
  
  void DeviceServiceImpl::authenticateUser( siemens::bt::type::AuthenticationResult& _return, const std::string& formerToken, const std::string& username, const std::string& passwordHash)
  {
   
  }
  
  void DeviceServiceImpl::updateUserProfile( const std::string& authenticationToken, const siemens::bt::type::User& user)
  {
   
  }
  
  bool DeviceServiceImpl::changePassword( const std::string& authenticationToken, const std::string& passwordMd5Hash)
  {
   return false;
  }
  
  void DeviceServiceImpl::logoutUser( siemens::bt::type::AuthenticationResult& _return, const std::string& authenticationToken)
  {
   
  }
  
  void DeviceServiceImpl::updateSession( const std::string& authenticationToken)
  {
   
  }
  
  bool DeviceServiceImpl::Authenticated( const std::string& dicpAuthToken)
  {
   return false;
  }
  
  void DeviceServiceImpl::getName( std::string& _return, const std::string& authenticationToken)
  {
   
  }
  
  int32_t DeviceServiceImpl::getLocalDeviceInst()
  {
   return 1;
  }
  
  void DeviceServiceImpl::getFirmwareRevision( std::string& _return)
  {
   
  }
  
  void DeviceServiceImpl::createRestorePoint( const std::string& authenticationToken, const bool logoutUser)
  {
   
  }
  
  void DeviceServiceImpl::updateData( Data& _return, const std::string& authenticationToken, const Data& clientData)
  {
   
  }
  
  bool DeviceServiceImpl::setDeviceState( const std::string& authenticationToken, const siemens::bt::type::DeviceState::type state)
  {
   return false;
  }
  
  void DeviceServiceImpl::restartDevice( const std::string& authenticationToken, const bool createRestorePoint, const bool logoutUser)
  {
   
  }
  
