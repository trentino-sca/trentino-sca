#ifndef DICPServiceImpl_H
#define DICPServiceImpl_H

#include <DICPService.h>

namespace dicp { 
class DICPServiceImpl : public DICPServiceIf {
public:
  DICPServiceImpl();
  
  ~DICPServiceImpl();
  
  void discover( const DiscoverServiceData& data);
  
  void wink( const WinkServiceData& data);
  
  void configure( const ConfigureServiceData& data);
  
  void unconfigure( const UnconfigureServiceData& data);
  
  void settime( const SetTimeServiceData& data);
  
  void setpassword( const SetPasswordServiceData& data);
  
}; //class DICPServiceImpl

}  //namespace
#endif //DICPServiceImpl_H