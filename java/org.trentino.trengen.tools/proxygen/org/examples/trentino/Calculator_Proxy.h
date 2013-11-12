#ifndef Calculator_Proxy_h
#define Calculator_Proxy_h


#ifdef WIN32 
   #define DLL_EXPORT __declspec(dllexport)
#else
   #define DLL_EXPORT
#endif

#include "Calculator.h"
#include "org/trentino/core/ServiceWrapper.h"

class Calculator_Proxy : public Calculator
{
public:
    Calculator_Proxy(org::trentino::core::ServiceWrapper*);
    virtual ~Calculator_Proxy();
    virtual int foo ();
    virtual std::string bar ( float arg0, float arg1, float arg2);
private:
    org::trentino::core::ServiceWrapper* target;
};

#endif //Calculator_Proxy_h