#ifndef DeviceServiceImpl_H
#define DeviceServiceImpl_H

#include <DeviceService.h>

namespace siemens { namespace bt { namespace device { 
class DeviceServiceImpl : public DeviceServiceIf {
public:
  DeviceServiceImpl();
  
  ~DeviceServiceImpl();
  
  void getInterfaceVersion( std::string& _return);
  
  bool setControlProgramState( const std::string& authenticationToken, const siemens::bt::type::ControlProgramState::type ctrlState);
  
  siemens::bt::type::ControlProgramState::type getControlProgramState( const std::string& authenticationToken);
  
  void getASN( std::string& _return, const std::string& authenticationToken);
  
  void authenticate( siemens::bt::type::AuthenticationResult& _return, const std::string& authenticationToken);
  
  void authorize( siemens::bt::type::AuthenticationResult& _return, const std::string& authenticationToken);
  
  void authenticateUser( siemens::bt::type::AuthenticationResult& _return, const std::string& formerToken, const std::string& username, const std::string& passwordHash);
  
  void updateUserProfile( const std::string& authenticationToken, const siemens::bt::type::User& user);
  
  bool changePassword( const std::string& authenticationToken, const std::string& passwordMd5Hash);
  
  void logoutUser( siemens::bt::type::AuthenticationResult& _return, const std::string& authenticationToken);
  
  void updateSession( const std::string& authenticationToken);
  
  bool Authenticated( const std::string& dicpAuthToken);
  
  void getName( std::string& _return, const std::string& authenticationToken);
  
  int32_t getLocalDeviceInst();
  
  void getFirmwareRevision( std::string& _return);
  
  void createRestorePoint( const std::string& authenticationToken, const bool logoutUser);
  
  void updateData( Data& _return, const std::string& authenticationToken, const Data& clientData);
  
  bool setDeviceState( const std::string& authenticationToken, const siemens::bt::type::DeviceState::type state);
  
  void restartDevice( const std::string& authenticationToken, const bool createRestorePoint, const bool logoutUser);
  
}; //class DeviceServiceImpl

}}}  //namespace
#endif //DeviceServiceImpl_H