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
#include "TrentinoBindingSCACompactSoapDataHandler.h"
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
         typedef boost::shared_ptr<Worker> WorkerPtr;
         typedef  std::vector<Worker*> Workers;
         typedef boost::shared_ptr<ZeroMqServer> ZeroMqServerPtr;
         typedef boost::program_options::variables_map Options;

         class Worker:private boost::noncopyable {
            //construction
         public:
            Worker(CompactSoapDataHandlerPtr handler,zmq::context_t& context);
               //data
         public:
            bool mStop;
            CompactSoapDataHandlerPtr mHandler;
            zmq::context_t& mContext;
            };//class Worker

         class BINDINGSCA_IMPORT_EXPORT ZeroMqServer : public boost::enable_shared_from_this<ZeroMqServer>
            {
            //construction
            public:
               ZeroMqServer(zmq::context_t& context, const Options options, const CompactSoapDataHandlerPtr& handler);
               ~ZeroMqServer();

               //services
            public:
               void start();
               void stop();
               bool isStarted();

               //data
            private:
               Options mOptions;
               CompactSoapDataHandlerPtr mHandler;
               bool mStarted;
               bool mStoped;
               zmq::context_t& mContext;
               Workers mWorkers;
               Socket mClients;
               Socket mDealer;
               int mThreadNumber;
            }; //ZeroMqServer
         } //namespace SCA
      } //namespace Binding
   } // namespace Trentino
#endif //TrentinoBindingSCAZeroMqServerH

