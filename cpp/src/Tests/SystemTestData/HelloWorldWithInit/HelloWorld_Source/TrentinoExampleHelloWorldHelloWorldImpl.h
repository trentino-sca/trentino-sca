#ifndef TrentinoExampleHelloWorldRemoteHelloWorldImplH
#define TrentinoExampleHelloWorldRemoteHelloWorldImplH
#ifdef WIN32
   #ifdef HELLOWORLD_EXPORTS
      #define HELLOWORLD_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define HELLOWORLD_IMPORT_EXPORT __declspec(dllimport)
   #endif //HELLOWORLD_EXPORTS
   #else
      #define HELLOWORLD_IMPORT_EXPORT
#endif //WIN32
//baseclass
#include "TrentinoExampleHelloWorldHelloWorld.h"


namespace Trentino{
namespace Example{
namespace HelloWorld{

//forward declaration


 //****************************************************************************************************
 //                                         HelloWorld
 //****************************************************************************************************
 //! \brief implementation of helloword servcie
 //****************************************************************************************************
class HELLOWORLD_IMPORT_EXPORT HelloWorldImpl : public HelloWorld{
  //construction
public:
 HelloWorldImpl();
 virtual ~HelloWorldImpl();
  //services
public:
	virtual std::string hello (const std::string& name);
	void init();
  
}; //class HelloWorld
} //namespace Trentino
} //namespace Example
} //namespace HelloWorld

#endif //TrentinoExampleHelloWorldHelloWorldImplH