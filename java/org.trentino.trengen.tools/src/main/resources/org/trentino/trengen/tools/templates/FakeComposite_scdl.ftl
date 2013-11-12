<?xml version="1.0" encoding="utf-8"?>
<composite name="TrengenGeneratedComposite" xmlns="http://docs.oasis-open.org/ns/opencsa/sca/200912" targetNamespace="BasicCalculatorNamespace">
<#foreach fakeComponent in fakeComponents>
  <component name="${fakeComponent.name}">
    <implementation.cpp
        class="${fakeComponent.implClass}"
		header="TrentinoGenBindingProxy.h"
        scope="composite" 
        library = "BasicCalculatorRemoteClient"/>
	<service name="BasicCalculator" >
      <interface.cpp class="${fakeComponent.interfaceClazz}" header="${fakeComponent.interfaceHeader}" remotable="true"/>
    </service>
  </component>
  </#foreach>
</composite>