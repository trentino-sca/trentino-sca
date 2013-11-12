#ifndef TrentinoBindingIpcClientBindingHelperH
#define TrentinoBindingIpcClientBindingHelperH


//standard
#include <string>
#include <boost/shared_ptr.hpp>

#include "../BindingIpcServer/TrentinoBindingIpcSoapMsg.h"
#include "../BindingIpcServer/TrentinoBindingIpcMemoryMapObj.h"
#include "TrentinoBindingIpcClientDefs.h"

namespace Trentino{
namespace Binding{
namespace IPC{
namespace Client
{
      
   class BINDINGIPCCLIENT_IMPORT_EXPORT IpcClientBindingHelper
   {
      //services
   public:
      static SoapMsgPtr prepareIpcSoap(Trentino::Binding::IPC::IpcMemoryMapObj* message, const char* action, const char* from );
   private:
      static void createHeader(SoapMsgPtr soapMsg, const char* action, const char* from,const std::string& fullDestination);
      static void convertHostToFullDestination(const char* host);
      static bool hasEnding (std::string const &fullString, std::string const &ending);
      //data
   private:
      static std::string mFulldestination;

   };

} //namespace Client
} //namespace IPC
} //namespace Binding
} //namespace Trentino
#endif //TrentinoBindingIpcClientBindingHelperH

