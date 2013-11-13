#ifndef ${componentName}_H
#define ${componentName}_H

#include <${serviceHeaderFileName}>

<#foreach nspart in service.namespaceparts>namespace ${nspart} { </#foreach>
class ${componentName} : public ${service.className} {
public:
  ${componentName}();
  
  ~${componentName}();
  
<#foreach method in service.methods>
  ${method.returnType} ${method.name}(<#list method.arguments as x> ${x.type} ${x.name}<#if x_has_next>,</#if></#list>);
  
</#foreach>
}; //class ${componentName}

<#foreach nspart in service.namespaceparts>}</#foreach>  //namespace
#endif //${componentName}_H