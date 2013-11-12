#ifndef TrentinoBindingIpcClientBindingTransportH
#define TrentinoBindingIpcClientBindingTransportH


//standard
#include <string>
#include <boost/shared_ptr.hpp>
//standart
#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/interprocess/sync/named_mutex.hpp> 
#include <boost/interprocess/sync/named_condition.hpp> 


#include "../BindingIpcServer/TrentinoBindingIpcSoapMsg.h"
#include "../BindingIpcServer/TrentinoBindingIpcMemoryMapObj.h"
#include "TrentinoBindingIpcClientImportExport.h"


namespace Trentino{
namespace Binding{
namespace IPC{
namespace Client
{
      
   class BINDINGIPCCLIENT_IMPORT_EXPORT BindingIpcClientTransport
   {
      //construction
   public:
      BindingIpcClientTransport(const char* host);
      ~BindingIpcClientTransport();

      //services
   public:
      void send(Trentino::Binding::IPC::IpcMemoryMapObj* memMappedObj, const char* action, const char* from );

      //data
   private:
      static std::string mFulldestination;
      boost::interprocess::managed_shared_memory mManaged_shm;
      boost::interprocess::named_condition mConditionClientData; 
      boost::interprocess::named_mutex mNamed_mtx; 
      boost::interprocess::named_condition mConditionServerData; 
      boost::interprocess::scoped_lock<boost::interprocess::named_mutex> mLock;

   };

} //namespace Client
} //namespace IPC
} //namespace Binding
} //namespace Trentino
#endif //TrentinoBindingIpcClientBindingTransportH

