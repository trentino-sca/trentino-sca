#ifndef TrentinoExampleHelloWorldRemoteHelloWorldImplH
#define TrentinoExampleHelloWorldRemoteHelloWorldImplH
#ifdef WIN32
   #ifdef HELLOWORLDREMOTE_EXPORTS
      #define HELLOWORLDREMOTE_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define HELLOWORLDREMOTE_IMPORT_EXPORT __declspec(dllimport)
   #endif //HELLOWORLDREMOTE_EXPORTS
   #else
      #define HELLOWORLDREMOTE_IMPORT_EXPORT
#endif //WIN32
//baseclass
#include "TrentinoExampleHelloWorldRemoteHelloWorld.h"


namespace Trentino{
namespace Example{
namespace HelloWorldRemote{

//forward declaration


 //****************************************************************************************************
 //                                         HelloWorld
 //****************************************************************************************************
 //! \brief implementation of helloword servcie
 //****************************************************************************************************
class HELLOWORLDREMOTE_IMPORT_EXPORT HelloWorldImpl : public HelloWorld{
  //construction
public:
 HelloWorldImpl();
 virtual ~HelloWorldImpl();
  //services
public:
	virtual std::string hello (const std::string& name);
  
}; //class HelloWorld
} //namespace Trentino
} //namespace Example
} //namespace HelloWorldRemote

#endif //TrentinoExampleHelloWorldRemoteHelloWorldImplH