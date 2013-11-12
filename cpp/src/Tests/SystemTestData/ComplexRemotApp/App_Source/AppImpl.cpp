
#include "AppImpl.h"

using namespace App;

	 void  archiveInverterDodo (const std::string& RockName,const tint32_t RockId,const std::string& timestamp,const App::AppService1::MasterRockDodo& RockDodo,const App::AppService1::InverterDodo& inverterDodo){}
	 void  archiveGridDodo (const std::string& informatique,const App::AppService1::GridCmdDodo& gridDodo){}
	 void  archiveAssetProtectDodo (const std::string& informatique,const tint32_t RockId,const App::AppService1::Succette& assetProtectDodo){}
	 void  archiveGridControllerConfigurationDodo (const App::AppService1::GridControllerConfigurationDodo& gridControllerConfigurationDodo){}
	 void  archiveCmdDispatchingDodo (const std::string& informatique,const App::AppService1::CmdDispatchingDodo& dispatchingCommadResult){}
	 
	 void setAppService2(App.AppService2* service2){
	    mService2 = service2;
	  }