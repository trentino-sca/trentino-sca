<?xml version="1.0" encoding="utf-8"?>
<composite name="${ApplicationName}" xmlns="http://docs.oasis-open.org/ns/opencsa/sca/200912" targetNamespace="${ApplicationName}Namespace">

<#foreach service in services>
 <#assign header=context.getComponentHeaderFileName(service) />
  <component name="${header}Comp">

    <implementation.cpp
        class="${service.namespace}::${header}"
		header="types:${header}.h"
        scope="composite"
		library="${ApplicationName}" 
		eagerInit="true"/>
  </component>
   
</#foreach>

</composite>