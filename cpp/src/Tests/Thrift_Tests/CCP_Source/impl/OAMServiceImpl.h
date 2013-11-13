#ifndef OAMServiceImpl_H
#define OAMServiceImpl_H

#include <OAMService.h>

namespace siemens { namespace bt { namespace oam { 
class OAMServiceImpl : public OAMServiceIf {
public:
  OAMServiceImpl();
  
  ~OAMServiceImpl();
  
  void serviceCall( siemens::bt::type::ServiceResult& _return, const std::string& authenticationToken, const std::string& viewState, const siemens::bt::type::ServiceCommand& command);
  
  void prepareBackgroundImage( ImageResult& _return, const std::string& authToken, const std::string& viewId, const int32_t pageId, const std::string& imageDestPath);
  
}; //class OAMServiceImpl

}}}  //namespace
#endif //OAMServiceImpl_H