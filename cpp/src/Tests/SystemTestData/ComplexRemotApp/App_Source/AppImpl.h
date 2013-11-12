// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2012 by Siemens AG. All rights reserved.
// http://trentino.sourceforge.net/
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
// **********************************************************************************

#ifndef TrentinoExampleBasicCalculatorCalculatorH
#define TrentinoExampleBasicCalculatorCalculatorH


//specific
#include "AppService1.h"
#include "AppService2.h"


namespace App{

   //class declaration
   //**********************************************************************************************
   //                             CalculatorImpl
   //**********************************************************************************************
   //! CalculatorImpl implementation testcode
   //**********************************************************************************************
   class  AppImpl : public App::AppService1
   {
   public:
      AppImpl();
      virtual ~AppImpl();
       
	  void setAppService2(App::AppService2* service2);
	  
	  	public:
	 void  archiveInverterDodo (const std::string& RockName,const tint32_t RockId,const std::string& timestamp,const App::AppService1::MasterRockDodo& RockDodo,const App::AppService1::InverterDodo& inverterDodo);
	 void  archiveGridDodo (const std::string& informatique,const App::AppService1::GridCmdDodo& gridDodo);
	 void  archiveAssetProtectDodo (const std::string& informatique,const tint32_t RockId,const App::AppService1::Succette& assetProtectDodo);
	 void  archiveGridControllerConfigurationDodo (const App::AppService1::GridControllerConfigurationDodo& gridControllerConfigurationDodo);
	 void  archiveCmdDispatchingDodo (const std::string& informatique,const App::AppService1::CmdDispatchingDodo& dispatchingCommadResult);
  
	  
	  private:
	  App::AppService2* mService2;
	  

   };//class Calculator
}//namespace Trentino



#endif //TrentinoExampleBasicCalculatorCalculatorH