#ifndef BaServiceImpl_H
#define BaServiceImpl_H

#include <BaService.h>

namespace siemens { namespace bt { namespace ba { 
class BaServiceImpl : public BaServiceIf {
public:
  BaServiceImpl();
  
  ~BaServiceImpl();
  
  void getInterfaceVersion( std::string& _return);
  
  void getLocalDeviceInst( siemens::bt::type::Object_Id& _return);
  
  void readPropertyString( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type);
  
  void readPropertyStringArray( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const int32_t array_index);
  
  void readPropertyStringList( std::vector<std::string>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type);
  
  double readPropertyReal( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type);
  
  double readPropertyRealArray( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const int32_t array_index);
  
  int32_t readPropertyInt( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type);
  
  int32_t readPropertyIntArray( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const int32_t array_index);
  
  void writePropertyString( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const std::string& value);
  
  double writePropertyReal( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const double value);
  
  int32_t writePropertyInt( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const int32_t value);
  
  void readObjectList( std::vector<siemens::bt::type::Object_Id>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type);
  
  bool releasePresentValue( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Write_Priority::type writePriority);
  
  void readProperty( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type);
  
  void writeProperty( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const std::string& value);
  
  void getPropertyDescription( siemens::bt::type::Property_Info& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type);
  
  void getProperties( std::vector<siemens::bt::type::Property_Type::type>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id);
  
  void getPropertyUnit( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type);
  
  void getPropertiesWithDescription( std::vector<siemens::bt::type::PropertyDesc_Info>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id);
  
  void getPropertiesWithText( std::map<siemens::bt::type::Property_Type::type,std::string>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id);
  
  void getPropertyEnum( std::map<int32_t,std::string>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type);
  
  void getRemoteDeviceList( std::vector<siemens::bt::type::Object_Id>& _return);
  
}; //class BaServiceImpl

}}}  //namespace
#endif //BaServiceImpl_H