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
#include "TrentinoBindingSCADataHandler.h"

namespace Trentino{
namespace Binding {
namespace SCA{
	
	typedef boost::shared_ptr<Worker> WorkerPtr;
	typedef  zmq::socket_t Socket;
	typedef  std::vector<boost::thread> WorkerThreads;
	typedef boost::shared_ptr<ZeroMqServer> ZeroMqServerPtr;
	typedef boost::program_options::variables_map Options;
	typedef trentino::bindingsca::csoap::Soap Soap;
	typedef boost::shared_ptr<Soap> SoapPtr;

	class ZeroMqServer : public boost::enable_shared_from_this<ZeroMqServer>
	{
	//connstruction
	public:
	ZeroMqServer(const Options options, const DataHandlerPtr& handler);
	~ZeroMqServer();
	
	//services
	public:
	void start();
	
	//data
	private:
	Options mOptions;
	const DataHandlerPtr mHandler;
	bool mStarted;
	WorkerThreads mWorkerThreads;
	Socket mClients;
	Socket mWorkersSocket;
	zmq::context_t mContext;
	
}; //ZeroMqServer
} //namespace SCA
} //namespace Binding
} // namespace Trentino
#endif //TrentinoBindingSCAZeroMqServerH

