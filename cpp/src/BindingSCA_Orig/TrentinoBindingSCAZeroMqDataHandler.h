#ifndef TrentinoBindingSCAZeroMqDataHandlerH
#define TrentinoBindingSCAZeroMqDataHandlerH

//standard
#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include <boost/thread.hpp>
#pragma warning(push)
#pragma warning(disable:4512)
#include <boost/program_options.hpp>
#pragma warning(pop)

//specific
#include <Binding/CompactSoap/BindingCompactSoapProtobufMessages.h>

namespace Trentino{
namespace Binding {
namespace SCA{
    class ZeroMqDataHandler;

    typedef trentino::bindingsca::csoap::Soap Soap;
    typedef boost::shared_ptr<Soap> SoapPtr;

	typedef boost::shared_ptr<ZeroMqDataHandler> ZeroMqDataHandlerPtr;
	
	class ZeroMqDataHandler {
	public:
	 virtual void handle(const SoapPtr& request, SoapPtr& response) const =0;
	}; //datahandler
	
} //namespace SCA
} //namespace Binding
} // namespace Trentino
#endif //TrentinoBindingSCAZeroMqDataHandlerH

