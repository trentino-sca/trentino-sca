#ifndef CSMLServiceImpl_H
#define CSMLServiceImpl_H

#include <CSMLService.h>

namespace siemens { namespace bt { namespace csml { 
class CSMLServiceImpl : public CSMLServiceIf {
public:
  CSMLServiceImpl();
  
  ~CSMLServiceImpl();
  
  void getInterfaceVersion( std::string& _return);
  
  void CSMLRequest( std::string& _return, const std::string& p_Request);
  
}; //class CSMLServiceImpl

}}}  //namespace
#endif //CSMLServiceImpl_H