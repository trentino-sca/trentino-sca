<#macro generateCppInterfaceImpl context inline>
<#assign nspace="" />
<#foreach part in context.tidlInterfaceModel.nameSpaceParts>
<#assign nspace=nspace+part+"::" /></#foreach>

<#foreach typeDesc in context.tidlInterfaceModel.allComplexTypes>
<#assign completName = typeDesc.namespace+"::"+typeDesc.name>
<#assign tn = typeDesc.name>
<#if !typeDesc.enumeration>

//********************************************************************************************
//!                             Class ${typeDesc.name}
//********************************************************************************************
${inline}${completName}::${tn} (){ 
<#foreach field in typeDesc.fields>
<#assign fn = field.name>
<#if field.hasDefaultValue()>
<#assign defVal = tmapper.defaultValue(field) >
	${fn}_=${defVal};
<#else>
<#assign name=tmapper.name(field.getType())/>
<#assign j = name?index_of("string")>
<#assign i = name?index_of("char*")>
<#if (j!=-1 || i!=-1) || tmapper.isComplexType(field.getType()) >
</#if>
</#if>
</#foreach>
}

${inline}${completName}::~${tn}(){
<#foreach field in typeDesc.fields>
<#assign fn = field.name>
<#assign name=tmapper.name(field.getType())/>
<#assign j = name?index_of("string")>
<#assign i = name?index_of("char*")>
<#if ((j!=-1 || i!=-1) || tmapper.isComplexType(field.getType()))&&!field.type.enumeration >
</#if>
</#foreach>
}
<#foreach field in typeDesc.fields>
<#assign fn = field.name>
<#assign name=tmapper.name(field.getType())/>
<#assign j = name?index_of("string")>
<#assign i = name?index_of("char*")>
<#if j!= -1 || i!=-1 >
${inline}const ${name}& ${completName}::${fn}() const{
	return ${fn}_;
}

${inline}void ${completName}::set_${fn}(const std::string& value){
  	${fn}_=value;
}

${inline}void ${completName}::set_${fn}(const char* value){
  	${fn}_= std::string(value);
}
</#if>

<#if tmapper.isPrimitive(field.getType())==true && j== -1 && i==-1 || field.type.enumeration>
${inline}${name} ${completName}::${fn}() const{
	return ${fn}_;
}

${inline}void ${completName}::set_${fn}(${name} value){
	${fn}_ = value;
}
<#elseif tmapper.isComplexType(field.getType())==true && j== -1 && i==-1>
${inline}bool ${completName}::has_${fn}() const{
        return true;
}


${inline}void ${completName}::set_${fn}(${name}& value){
${fn}_ = value;
}

${inline} const ${name}& ${completName}::${fn}() const {
		return ${fn}_;
}

${inline} ${name}& ${completName}::mutable_${fn}(){
  return ${fn}_;
}
</#if>
	
</#foreach>

</#if>
</#foreach>
</#macro>
