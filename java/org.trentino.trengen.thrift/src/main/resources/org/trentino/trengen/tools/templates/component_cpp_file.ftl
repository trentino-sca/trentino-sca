#include "${componentName}.h"

using namespace ${service.namespace};

//!Constructors
  ${componentName}::${componentName}()
  {
    //TODO auto generated
  }
  
  ${componentName}::~${componentName}()
  {
    //TODO auto generated
  }
  
 //!Services
<#foreach method in service.methods>
  ${method.returnType} ${componentName}::${method.name}(<#list method.arguments as x> ${x.type} ${x.name}<#if x_has_next>,</#if></#list>)
  {
   <#assign retValue=context.getReturn(method) />
   ${retValue}
  }
  
</#foreach>
