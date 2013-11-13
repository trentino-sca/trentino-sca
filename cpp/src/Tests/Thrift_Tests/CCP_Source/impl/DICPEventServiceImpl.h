#ifndef DICPEventServiceImpl_H
#define DICPEventServiceImpl_H

#include <DICPEventService.h>

namespace dicp { 
class DICPEventServiceImpl : public DICPEventServiceIf {
public:
  DICPEventServiceImpl();
  
  ~DICPEventServiceImpl();
  
  void identification( const IdentificationServiceData& data, const std::string& ifversion);
  
}; //class DICPEventServiceImpl

}  //namespace
#endif //DICPEventServiceImpl_H