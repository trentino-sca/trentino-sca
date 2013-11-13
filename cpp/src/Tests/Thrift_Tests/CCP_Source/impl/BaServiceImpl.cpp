#include "BaServiceImpl.h"

using namespace siemens::bt::ba;

//!Constructors
  BaServiceImpl::BaServiceImpl()
  {
    //TODO auto generated
  }
  
  BaServiceImpl::~BaServiceImpl()
  {
    //TODO auto generated
  }
  
 //!Services
  void BaServiceImpl::getInterfaceVersion( std::string& _return)
  {
   
  }
  
  void BaServiceImpl::getLocalDeviceInst( siemens::bt::type::Object_Id& _return)
  {
   
  }
  
  void BaServiceImpl::readPropertyString( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type)
  {
   
  }
  
  void BaServiceImpl::readPropertyStringArray( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const int32_t array_index)
  {
   
  }
  
  void BaServiceImpl::readPropertyStringList( std::vector<std::string>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type)
  {
   
  }
  
  double BaServiceImpl::readPropertyReal( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type)
  {
   return 1;
  }
  
  double BaServiceImpl::readPropertyRealArray( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const int32_t array_index)
  {
   return 1;
  }
  
  int32_t BaServiceImpl::readPropertyInt( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type)
  {
   return 1;
  }
  
  int32_t BaServiceImpl::readPropertyIntArray( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const int32_t array_index)
  {
   return 1;
  }
  
  void BaServiceImpl::writePropertyString( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const std::string& value)
  {
   
  }
  
  double BaServiceImpl::writePropertyReal( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const double value)
  {
   return 1;
  }
  
  int32_t BaServiceImpl::writePropertyInt( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const int32_t value)
  {
   return 1;
  }
  
  void BaServiceImpl::readObjectList( std::vector<siemens::bt::type::Object_Id>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type)
  {
   
  }
  
  bool BaServiceImpl::releasePresentValue( const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Write_Priority::type writePriority)
  {
   return false;
  }
  
  void BaServiceImpl::readProperty( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type)
  {
   
  }
  
  void BaServiceImpl::writeProperty( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type, const std::string& value)
  {
   
  }
  
  void BaServiceImpl::getPropertyDescription( siemens::bt::type::Property_Info& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type)
  {
   
  }
  
  void BaServiceImpl::getProperties( std::vector<siemens::bt::type::Property_Type::type>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id)
  {
   
  }
  
  void BaServiceImpl::getPropertyUnit( std::string& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type)
  {
   
  }
  
  void BaServiceImpl::getPropertiesWithDescription( std::vector<siemens::bt::type::PropertyDesc_Info>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id)
  {
   
  }
  
  void BaServiceImpl::getPropertiesWithText( std::map<siemens::bt::type::Property_Type::type,std::string>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id)
  {
   
  }
  
  void BaServiceImpl::getPropertyEnum( std::map<int32_t,std::string>& _return, const std::string& authToken, const siemens::bt::type::Object_Id& object_id, const siemens::bt::type::Property_Type::type property_type)
  {
   
  }
  
  void BaServiceImpl::getRemoteDeviceList( std::vector<siemens::bt::type::Object_Id>& _return)
  {
   
  }
  
