// Generated by Trentino TDIL CPP interface generator. do not modify

#ifndef DiscoveryTestServerH
#define DiscoveryTestServerH

#include "DiscoveryTestClientGlobal.h"

#include <string>

namespace Trentino{
namespace Example{


	//****************************************************************************************************
	//                                         DiscoveryTestServer
	//****************************************************************************************************
	//! \brief 
	//****************************************************************************************************
	class  DiscoveryTestServer{

  //services
	public:
	virtual void  doTheJob (const std::string& s) =0;
  
	}; //class DiscoveryTestServer



} //namespace Trentino
} //namespace Example



#endif //DiscoveryTestServerH