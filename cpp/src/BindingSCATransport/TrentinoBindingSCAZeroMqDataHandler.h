#ifndef TrentinoBindingSCADataHandlerH
#define TrentinoBindingSCADataHandlerH

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
    class DataHandler;

	typedef boost::shared_ptr<DataHandler> DataHandlerPtr;
	
	class DataHandler {
	public:
	 virtual void handle(const SoapPtr request, SoapPtr& response) const =0;
	}; //datahandler
	
} //namespace SCA
} //namespace Binding
} // namespace Trentino
#endif //TrentinoBindingSCADataHandlerH

