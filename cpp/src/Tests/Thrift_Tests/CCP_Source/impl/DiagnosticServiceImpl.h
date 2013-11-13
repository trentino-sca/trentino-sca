#ifndef DiagnosticServiceImpl_H
#define DiagnosticServiceImpl_H

#include <DiagnosticService.h>

namespace siemens { namespace bt { namespace diagnostic { 
class DiagnosticServiceImpl : public DiagnosticServiceIf {
public:
  DiagnosticServiceImpl();
  
  ~DiagnosticServiceImpl();
  
  void getInterfaceVersion( std::string& _return);
  
  void getFacilities( std::vector<std::string>& _return, const std::string& authenticationToken);
  
  void getSeverities( std::vector<std::string>& _return, const std::string& authenticationToken);
  
  void getStatByFacility( std::vector<StatLog>& _return, const std::string& authenticationToken, const std::string& facility);
  
  void getAllStatistics( std::vector<StatLog>& _return, const std::string& authenticationToken);
  
  void getDiagByFacility( std::vector<DiagLog>& _return, const std::string& authenticationToken, const std::string& facility);
  
  void getDiagBySeverity( std::vector<DiagLog>& _return, const std::string& authenticationToken, const std::string& severity);
  
  void getAllDiagnostics( std::vector<DiagLog>& _return, const std::string& authenticationToken);
  
}; //class DiagnosticServiceImpl

}}}  //namespace
#endif //DiagnosticServiceImpl_H