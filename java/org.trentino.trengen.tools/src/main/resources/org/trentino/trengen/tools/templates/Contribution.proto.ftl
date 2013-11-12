<#function createParamPart method >
<#assign ret ="" >
<#foreach argument in method.arguments>
<#assign ret = ret+" "+argument.type+" "+argument.name+"," >
</#foreach>
<#if ret?ends_with(",")>
<#return ret?substring(0,ret?last_index_of(",")) >
</#if>
<#return ret >
</#function>

<#assign serviceName = context.classModel.className>
<#assign classModel = context.classModel>
#ifndef ${proxyName}_h
#define ${proxyName}_h


#ifdef WIN32 
   #define DLL_EXPORT __declspec(dllexport)
#else
   #define DLL_EXPORT
#endif

#include "${serviceName}.h"
#include "org/trentino/core/ServiceWrapper.h"

class ${proxyName} : public ${serviceName}
{
public:
    ${proxyName}(org::trentino::core::ServiceWrapper*);
    virtual ~${proxyName}();
<#foreach method in classModel.methods>
    virtual ${method.returnType} ${method.name} (${createParamPart(method)});
</#foreach>
private:
    org::trentino::core::ServiceWrapper* target;
};

#endif //${proxyName}_h