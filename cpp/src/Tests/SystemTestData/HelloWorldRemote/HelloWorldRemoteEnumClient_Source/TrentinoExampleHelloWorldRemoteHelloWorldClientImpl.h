#ifndef TrentinoExampleHelloWorldRemoteHelloWorldImplH
#define TrentinoExampleHelloWorldRemoteHelloWorldImplH
#ifdef WIN32
   #ifdef HELLOWORLDREMOTECLIENT_EXPORTS
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
class HELLOWORLDREMOTE_IMPORT_EXPORT HelloWorldClientImpl{
  //construction
public:
 HelloWorldClientImpl();
 virtual ~HelloWorldClientImpl();
  //dependencies injection
  public:
  void setHelloWorld(HelloWorld* helloWorld);
  //services
public:
	void callHello ();
	
  //data	
private:
 HelloWorld* mHelloWorld;
  
}; //class HelloWorld
} //namespace Trentino
} //namespace Example
} //namespace HelloWorldRemote

#endif //TrentinoExampleHelloWorldRemoteHelloWorldImplH