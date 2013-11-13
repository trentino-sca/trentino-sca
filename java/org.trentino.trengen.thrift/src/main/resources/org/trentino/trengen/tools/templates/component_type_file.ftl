<?xml version="1.0" encoding="utf-8"?>
<componentType xmlns="http://docs.oasis-open.org/ns/opencsa/sca/200912">
    <service name="${serviceName}" >
      <interface.cpp class="${service.fullQualifiedClassName}" header="services:${serviceHeaderFileName}" remotable="true"/>
      <binding.thrift uri="tcp://localhost:7911"/>
    </service>
</componentType>