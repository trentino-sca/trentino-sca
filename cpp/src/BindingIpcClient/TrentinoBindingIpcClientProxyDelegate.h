#ifndef TrentinoBindingIPCClientProxyDelegateH
#define TrentinoBindingIPCClientProxyDelegateH

#include "TrentinoBindingIPCClientImportExport.h"
#include "../BindingIpcServer/TrentinoBindingIpcMemoryMapObj.h"
#include <boost/shared_ptr.hpp>

#include <string>

//typedef boost::shared_ptr<BindingProxyDelegate> BindingProxyDelegatePtr;

namespace Trentino{
namespace Binding{
namespace IPC{
namespace Client
{
   class BindingIpcClientTransport;
   class IpcMemoryMapObj;

   class  BINDINGIPCCLIENT_IMPORT_EXPORT BindingProxyDelegateIPC
   {
   public:
      BindingProxyDelegateIPC(const char * host);
      ~BindingProxyDelegateIPC();
      //void send(/*const Trentino::Binding::IPC::IpcMemoryMapObj message,*/const char* action, const char* from ) const;

      void send(Trentino::Binding::IPC::IpcMemoryMapObj* memMappedObj, const char* action, const char* from) const;
      void setHost(const char * host);
   private:
      boost::shared_ptr<BindingIpcClientTransport>  mTransport;
   };

} //namespace Client
} //namespace IPC
} //namespace Binding
} //namespace Trentino
#endif //TrentinoBindingIPCClientProxyDelegateH

