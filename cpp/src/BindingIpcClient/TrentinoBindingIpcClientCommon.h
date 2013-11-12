#ifndef TrentinoBindingIpcClientCommonH
#define TrentinoBindingIpcClientCommonH

#include <string>
#include "../Utils/TrentinoUtilsConfiguration.h"

namespace Trentino{
namespace Binding{
namespace IPC{
namespace Client
{

   class TrentinoBindingIpcClientCommon
   {
   public:
      static TrentinoBindingIpcClientCommon& getInstance(void);
      int getTimeOutPeriod();
      int getSharedMemorySize();
   private:
      TrentinoBindingIpcClientCommon(void);
      ~TrentinoBindingIpcClientCommon(void);
      TrentinoBindingIpcClientCommon(const TrentinoBindingIpcClientCommon&);
      TrentinoBindingIpcClientCommon& operator=(const TrentinoBindingIpcClientCommon&){ return mInstance; }; //mInstance???

      std::string configFilePath() const;

      static TrentinoBindingIpcClientCommon mInstance;

      int mTimeOutPeriod;
      int mSharedMemorySize;
      //! Object providing the logic for parsing options from config files (and the cmd line)
      Trentino::Utils::Configuration mConfiguration;

   };
} //namespace Client
} //namespace IPC
} //namespace Binding
} //namespace Trentino
#endif //TrentinoBindingIpcClientCommonH

