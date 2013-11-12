// ****************************************************************************
// Generated by Trengen. Do not modify
// **************************************************************************** 

//header
#include "ContributionInfo.h"

#include "TrentinoGenProxiesWrappers.h"


using namespace Trentino::Gen::ValidContribution1Gen;

extern "C" TRENTINO_DLLEXPORT Trentino::Core::TrentinoContributionInfo* TRENTINO_CDECL getContributionInfo()
{
 return new Trentino::Gen::ValidContribution1Gen::ValidContribution1ContributionInfo();
}


//constructor and destructor implementation
CONTRIBUTIONINFO_CPP_CDTOR(ValidContribution1);

TRENTINO_DLLEXPORT  Trentino::Invocation::ServiceInvocationWrapperBase* TRENTINO_CDECL ValidContribution1ContributionInfo::getServiceInvocationWrapperByClassName( const std::string& className )
{
   if(className == std::string("Trentino::Example::ValidContribution1::Logger"))
      {
       return new Trentino_Example_ValidContribution1_LoggerWrapper();
      }
   if(className == std::string("Trentino::Example::ValidContribution1::Build"))
      {
       return new Trentino_Example_ValidContribution1_BuildWrapper();
      }
   return nullptr;
}
   
static BindingHelperFactoryList bindingHelperFactories;
  
TRENTINO_DLLEXPORT  Trentino::Binding::BindingHelperBase* TRENTINO_CDECL ValidContribution1ContributionInfo::getBindingHelperByBindingIdAndClassName( const std::string& bindingId,const std::string& className )
 {
 BindingHelperFactoryList::iterator it ;
 for(it = bindingHelperFactories.begin();it !=bindingHelperFactories.end();++it){
    BindingHelperFactory factory = *it;
    if(factory.mBindingId == bindingId && factory.mClassName == className){
       return factory.getBindingHelper();
       }
    }
  return nullptr;
 } 
 
  TRENTINO_DLLEXPORT  const char* TRENTINO_CDECL ValidContribution1ContributionInfo::getAllDeclaredBindings() const
 {
 	
    return "";
 }