

namespace Trentino{
namespace Example{
namespace BasicCalculator
{
   //class declaration
   //**********************************************************************************************
   //                             Divider
   //**********************************************************************************************
   //! Divider interface testcode
   //**********************************************************************************************
   class Divider 
   {
      public:

       virtual void doit(const Irene::Application::StorageSystem::IStorageRackCommandService::StorageRackCommand&  command,
                               const std::map<std::string, boost::shared_ptr<Irene::Application::StorageSystem::IStorageRackCommandService::StorageRackData>>& racksData,
                               std::vector<boost::shared_ptr<Irene::Application::StorageSystemController::RackCommandData>>& rackCommands) = 0;


   };//class Divider
}//namespace BasicCalculator
}//namespace Example
}//namespace Trentino
