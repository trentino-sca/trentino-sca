package protobuf.${context.tidlInterfaceModel.qualifiedName};
option optimize_for = LITE_RUNTIME;
<#macro printTypd typeDesc margin>
<#if typeDesc.enumeration >

${margin}enum PB_${typeDesc.name}{
<#assign i=1/>
<#foreach field in typeDesc.fields>
<#assign name=tmapper.name(field.getType())/>
${margin}	${field.name}=${i};
<#assign i=i+1/>
</#foreach>
${margin}} //enum ${typeDesc.name}

<#else>

${margin}message PB_${typeDesc.name}{
<#foreach t in typeDesc.getEnclosedClasses()>
<#assign nmargin=margin+"	">
<@printTypd typeDesc=t margin=nmargin />
</#foreach>
<#assign i=1/>
<#foreach field in typeDesc.fields>
<#assign name=tmapper.name(field.getType())/>
${margin}	optional ${name} ${field.name}=${i};
<#assign i=i+1/>
</#foreach>
${margin}} //message ${typeDesc.name}

</#if>
</#macro>
<#foreach typeDesc in context.tidlInterfaceModel.nonEnclosedClasses>
<#if !typeDesc.enclosed >
<@printTypd typeDesc=typeDesc margin="" />
</#if>
</#foreach>
<#foreach typeDesc in context.tidlInterfaceModel.enclosedClasses>
<#if typeDesc.enclosed >
<@printTypd typeDesc=typeDesc margin="		" />
</#if>
</#foreach> 