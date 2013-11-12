<#-- for each implementation a class should be generated within the reflection code-->

<#macro init >
static const Trentino::Reflection::Data::Method::Param trentino_internal_invoke_cpp_componentParam[] ={{"void *"},
		    {"const Trentino::XML::Schema::Name&"},
		    {"const Trentino::Invocation::InvocationData&"},
		    {"const Trentino::Invocation::InvocationContext&"},
		    {"void *"}};
</#macro>
<#macro traceReflectionObjectList reflectionObjectList>
<#assign i=1>
<#foreach reflectionObj in reflectionObjectList>
<@createClass reflectionObj = reflectionObj> </@createClass>
<#assign i= i + 1>
</#foreach>
</#macro>

<#-- this is the class to create a class for each impl -->
<#macro createClass reflectionObj>
<#assign implementationClassWithNameSpace = reflectionObj.implClassAsNamespace>
	//*************************************************************************************************
	// class declaration
	// Initializer${reflectionObj.implClass}Rflx
	//*************************************************************************************************	    
   	class Initializer${reflectionObj.implClass}Rflx
  	 {
  	 
		//! This is the new callback to create component, retVal is a pointer of pointer which contains
		//! the address of object
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void* /*params*/[])
		{
			*reinterpret_cast<${reflectionObj.implClassAsNamespace}**>(retVal) = 
			new ${reflectionObj.implClassAsNamespace}();
		}
		
		//! you need only thisPtr and a simple static_cast to destroy object by default delete
		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void* /*params*/[])
		{
			${reflectionObj.implClassAsNamespace}* p = 
			static_cast<${reflectionObj.implClassAsNamespace}*>(thisPtr);
			delete p;
		}
		
		static void TRENTINO_STDCALL impl_cpp_invoke(void* thisPtr,void* /*retVal*/, void* params[]){
         Trentino::XML::Schema::Name& serviceId = *static_cast<Trentino::XML::Schema::Name*>(params[0]);
         const char* serviceIdChar = serviceId.c_str();
         const Trentino::Invocation::InvocationData& data = *static_cast<const Trentino::Invocation::InvocationData*>(params[1]);
         const Trentino::Invocation::InvocationContext& ctx =*static_cast<const Trentino::Invocation::InvocationContext*>(params[2]);
		${reflectionObj.implClassAsNamespace}* p = static_cast<${reflectionObj.implClassAsNamespace}*>(thisPtr);
		void * retVal = params[3];	
		<#foreach service in reflectionObj.listServices>
		  <#assign itfName = service.serviceInterfaceClass >
		   if(strcmp(serviceIdChar, "${itfName}") == 0)
			{
			 ${itfName?replace("::","_")}Wrapper_invoke(data, ctx, dynamic_cast<${itfName}*>(p), retVal);
			 return;
			}
		</#foreach>

		
		}
		
		//a setter method is needed for each reference of the componentType
	<#foreach ref in reflectionObj.listReferences>
		static void TRENTINO_STDCALL set${ref.referenceName}Method(void* thisPtr, void* /*retVal*/, void* params[])
		{
			${implementationClassWithNameSpace}* p = 
			static_cast<${implementationClassWithNameSpace}*>(thisPtr);
		<#if ref.multiplictyBiggerThanOne>
			std::list<${ref.interfaceClassNamespacesSemicolonSeperated}*> param0;
			expandToList(param0, *(*reinterpret_cast<Trentino::Reflection::Helpers::ListType**>(params[0])));
			p->set${ref.referenceName?cap_first}(param0);
		<#else>
			<#--comment: all parameters are pointers pointers which must be dereferenced to a normal pointer to object-->
			p->set${ref.referenceName?cap_first}(*reinterpret_cast<${ref.interfaceClassNamespacesSemicolonSeperated}**>(params[0]));
		</#if>
		}
	</#foreach>
	<#foreach cppFunction in reflectionObj.listCPPImplementationFunction>
	    <#if reflectionObj.isInitMethod(cppFunction)>
		static void TRENTINO_STDCALL reflx_cppImplementation_Lifecycle_Init_Method(void* thisPtr, void* /*retVal*/, void* /*params*/[])
		{
			${implementationClassWithNameSpace}* p = 
			static_cast<${implementationClassWithNameSpace}*>(thisPtr);
		    p->${cppFunction.name}();
		}
	    <#elseif reflectionObj.isDestroyMethod(cppFunction)>
		static void TRENTINO_STDCALL reflx_cppImplementation_Lifecycle_Destroy_Method(void* thisPtr, void* /*retVal*/, void* /*params*/[])
		{
			${implementationClassWithNameSpace}* p = 
			static_cast<${implementationClassWithNameSpace}*>(thisPtr);
		    p->${cppFunction.name}();
		}
	    <#elseif cppFunction.name?trim?starts_with("set_root_path.")>
		static void TRENTINO_STDCALL reflx_cppImplementation_Lifecycle_SetContributionDir_Method(void* thisPtr, void* /*retVal*/, void* params [])
		{
			${implementationClassWithNameSpace}* p = 
			static_cast<${implementationClassWithNameSpace}*>(thisPtr);
			std::string* param = (std::string*)params[0];
		    p->${cppFunction.name?substring(14)}(*param);
		}
	    </#if>
	    
	</#foreach>
	 
	 	 	//a setter method is needed for each property of the componentType
	<#foreach property in reflectionObj.listProperties>
		<#assign pType = property.type>
		<#if property.many || pType=="ENTITIES" ||  pType=="NMTOKENS" ||pType == "IDREFS">
		<#assign PropType = mapper.getMatchingType2(property.type)>
		static void TRENTINO_STDCALL set${property.propertyName}Method(void* thisPtr, void* /*retVal*/, void* params[])
		{
			${implementationClassWithNameSpace}* p = static_cast<${implementationClassWithNameSpace}*>(thisPtr);
			<#if pType=="ENTITIES" ||  pType=="NMTOKENS" ||pType == "IDREFS">
			<#if !property.many>
			<#assign PropType = mapper.getMatchingType1(property.type)>
			</#if>
			</#if>
			std::list<${PropType} >param0;
	   		expandToList(param0, *(*reinterpret_cast<Trentino::Reflection::Helpers::ListType**>(params[0])));
	  		p->set${property.propertyName?cap_first}(param0);
		}
		<#else>
		<#assign PropType = mapper.getMatchingType1(property.type)>
		static void TRENTINO_STDCALL set${property.propertyName}Method(void* thisPtr, void* /*retVal*/, void* params[])
		{
			${implementationClassWithNameSpace}* p = static_cast<${implementationClassWithNameSpace}*>(thisPtr);
			p->set${property.propertyName?cap_first}(*reinterpret_cast<${PropType}*>(params[0]));
		}
		</#if>
	</#foreach>
		//For every class with more than one base class, a corresponding castCall() function must be generated 
		//and registered in the reflection class.   This also applies to the class if any of its predecessors 
		//have more than one base class or even there are more than one base classes in the whole inheritance 
		//hierarchy since this causes the same kind of problem as with direct inheritance.  As as a robust 
		//solution can be considered the generation of cast function for all classes disregarding the actual 
		//number of base classes.		
		static void* TRENTINO_STDCALL castCallMyComponent (void* thisPtr, const char* <#if reflectionObj.listServices?has_content>castInto <#else> /*castInto*/ </#if>)
		{
			
			<#--comment:ok by string compare, we must first cast basic void* into derived class pointer and cast it into specified baseclass to get correct offset of class pointer-->
			<#foreach service in reflectionObj.listServices>
			if(strcmp(castInto, "${service.serviceInterfaceClass}") == 0)
			{
				return static_cast<${service.serviceInterfaceClass}*>
				(static_cast<${implementationClassWithNameSpace}*>(thisPtr));
			}
			</#foreach>
			
			<#--comment: no conversion found, pass through -->
			return thisPtr;
		}
		
		//construction
		
		public:
		Initializer${reflectionObj.implClass}Rflx()
		{

			//struct is necessary to find correct parameterlist by runtime
			static const Trentino::Reflection::Data::Method::Param deleteParamMyComponent[] = {{"${implementationClassWithNameSpace} *"}};
			<#--comment:We have to set the parameters for each reference of compType-->
		<#foreach ref in reflectionObj.listReferences>
		<#if ref.multiplictyBiggerThanOne>
			static const Trentino::Reflection::Data::Method::Param set${ref.nameGen}MethodParams[] = {{"std::list<${ref.referenceInterfaceClass} *>" }};<#--comment:content of the reference/interface.cpp/@class-->
		<#else>
			static const Trentino::Reflection::Data::Method::Param set${ref.nameGen}MethodParams[] = {{"${ref.interfaceClassNamespacesSemicolonSeperated} *" }};<#--comment:content of the reference/interface.cpp/@class-->
         </#if>
		</#foreach>
		<#foreach cppFunction in reflectionObj.listCPPImplementationFunction>
			<#if cppFunction.name?trim?starts_with("set_root_path.")>
			 //set root dir lifecycle method
			 static const Trentino::Reflection::Data::Method::Param reflx_cppImplementation_Lifecycle_SetContributionDir_Method_Param[] = {{"const std::string&"}};
			</#if>		    
	   </#foreach>
			<#--comment:We have to set the XXXX for each property of compType-->
		<#foreach property in reflectionObj.listProperties>
			<#assign PropType = mapper.getMatchingType2(property.type)>
			<#assign pType = property.type>
			<#if property.many || pType=="ENTITIES" ||  pType=="NMTOKENS" ||pType == "IDREFS">
				<#if pType=="ENTITIES" ||  pType=="NMTOKENS" ||pType == "IDREFS">
				<#if !property.many>
					<#assign PropType = mapper.getMatchingType1(property.type)>
				</#if>
				</#if>	
			static const Trentino::Reflection::Data::Method::Param set${property.propertyName}MethodParams[] = {{"std::list<${PropType} >"}};
			<#else>
			static const Trentino::Reflection::Data::Method::Param set${property.propertyName}MethodParams[] = {{"${PropType}" }};<#--comment:content of the reference/interface.cpp/@class-->
			</#if>
		</#foreach>
			//define all "public" functions seen by reflection runtime
			static Trentino::Reflection::Data::Method::MetaData mdmMyComponent[] = {
			 <#--comment: for each reference of componentType we need an entry here -->
			 <#foreach ref in reflectionObj.listReferences>
			{ "set${ref.referenceName}", nullptr, set${ref.nameGen}MethodParams, COUNT_OF(set${ref.nameGen}MethodParams), set${ref.referenceName}Method },
            </#foreach>
			<#foreach cppFunction in reflectionObj.listCPPImplementationFunction>
			    <#if reflectionObj.isInitMethod(cppFunction)>
			/*init lifecycle method*/
			{ "${cppFunction.name}", nullptr, nullptr, 0, reflx_cppImplementation_Lifecycle_Init_Method },
			    <#elseif reflectionObj.isDestroyMethod(cppFunction)>
			/*destroy lifecycle method*/
			{ "${cppFunction.name}", nullptr, nullptr, 0, reflx_cppImplementation_Lifecycle_Destroy_Method },
			    <#elseif cppFunction.name?trim?starts_with("set_root_path.")>
			 //set root dir lifecycle method
			 { "${cppFunction.name?substring(14)}", nullptr, reflx_cppImplementation_Lifecycle_SetContributionDir_Method_Param, COUNT_OF(reflx_cppImplementation_Lifecycle_SetContributionDir_Method_Param), reflx_cppImplementation_Lifecycle_SetContributionDir_Method },
			    </#if>		    
			</#foreach>
            <#--comment: for each property of componentType we need an entry here -->
               <#foreach property in reflectionObj.listProperties>
             <#assign propName = property.propertyName>
			{"set${propName}", nullptr, set${propName}MethodParams, COUNT_OF(set${propName}MethodParams), set${propName}Method},
            </#foreach>
            //word "new" is reserved and can be overloaded with parameter constructors, will be
			//called by ReflectObject::newInstance
			{ "new", "${implementationClassWithNameSpace}*", nullptr, 0, newObjectNoParam },
			//word "delete" is reserved for destroying object and will be called by 
			//ReflectObject::deleteInstance or ReflectObject::deleteRegisteredInstance
			{ "delete", nullptr, deleteParamMyComponent, COUNT_OF(deleteParamMyComponent), deleteObject },
			{"trentino_internal_impl_cpp_invoke_do_not_use_this_name",nullptr,trentino_internal_invoke_cpp_componentParam,COUNT_OF(trentino_internal_invoke_cpp_componentParam),impl_cpp_invoke},
         };

         //register whole object
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "${implementationClassWithNameSpace}", <#--comment:content of @header of the implementation.cpp-->
            nullptr, //passing a pointer to the generated cast call function
            <#--castCallMyComponent,  //cast call function callback-->
            mdmMyComponent, //ok register here my methodlist, incl. new and delete functions
            COUNT_OF(mdmMyComponent), //number of functions
         };

         // store it in initializer class to unregister it by destructor
         mmdoHandle = &mdo;

         //register class in reflection runtime
         Trentino::Reflection::Registration::registerMetaData(GenContributionInfo::getDataRegistry(),*mmdoHandle);
      }

      ~Initializer${reflectionObj.implClass}Rflx()
      {
         //Important: don´t forget to unregister, rflx dlls can be unloaded!
         Trentino::Reflection::Registration::unregisterMetaData(GenContributionInfo::getDataRegistry(),*mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   };//class Initializer${reflectionObj.implClass}Rflx
   static Initializer${reflectionObj.implClass}Rflx mInitializer${reflectionObj.implClass}Rflx${i};
</#macro>
