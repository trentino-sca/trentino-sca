#ifndef TrentinoBindingSCAZeroMqServerH
#define TrentinoBindingSCAZeroMqServerH

//standard
#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include <boost/thread.hpp>
#pragma warning(push)
#pragma warning(disable:4512)
#include <boost/program_options.hpp>
#pragma warning(pop)

//specific
#include "TrentinoBindingSCAZeroMqDataHandler.h"
#include <zmq.hpp>
#include "TrentinoBindingSCAImportExport.h"

namespace Trentino{
   namespace Binding {
      namespace SCA{

         class ZeroMqServer;
         class Worker;
         typedef  zmq::socket_t Socket;
         typedef boost::shared_ptr<Socket> SocketPtr;
         typedef boost::shared_ptr<boost::thread> ThreadPtr;
         typedef  std::vector<SocketPtr> Sockets;
         typedef  std::vector<ThreadPtr> WorkerThreads;
         typedef boost::shared_ptr<ZeroMqServer> ZeroMqServerPtr;
         typedef boost::program_options::variables_map Options;

         class BINDINGSCA_IMPORT_EXPORT ZeroMqServer : public boost::enable_shared_from_this<ZeroMqServer>
            {
            //construction
            public:
               ZeroMqServer(zmq::context_t& context, const Options options, const ZeroMqDataHandlerPtr& handler);
               ~ZeroMqServer();

               //services
            public:
               void start();
               void stop();
               bool isStarted();

               //data
            private:
               Options mOptions;
               const ZeroMqDataHandlerPtr mHandler;
               zmq::context_t& mContext;
               bool mStarted;
               bool mStoped;
               WorkerThreads mWorkerThreads;
               Socket mClients;
               Socket mDealer;
               Sockets mWorkerSockets;
               int mThreadNumber;
               friend class Worker;
            }; //ZeroMqServer
         } //namespace SCA
      } //namespace Binding
   } // namespace Trentino
#endif //TrentinoBindingSCAZeroMqServerH

