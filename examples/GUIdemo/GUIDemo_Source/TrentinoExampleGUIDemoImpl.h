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

#ifndef TrentinoExampleGUIDemoImplH
#define TrentinoExampleGUIDemoImplH

//standard
//#include <oasis\sca\ComponentContext.h>

//specific
#include "services/TrentinoExampleGUIDemo.h"
#include "services/TrentinoExampleGUIDemoLCD.h"

#include "..\GUIDemo_Source\GuiStart.h"

#include <list>

#ifndef nullptr
   #define nullptr 0
#endif

#ifdef WIN32
   #ifdef GUIDEMO_EXPORTS
      #undef GUIDEMO_IMPORT_EXPORT
      #define GUIDEMO_IMPORT_EXPORT __declspec(dllexport)
   #else
      #undef GUIDEMO_IMPORT_EXPORT
      #define GUIDEMO_IMPORT_EXPORT __declspec(dllimport)       
   #endif //GUIDEMO_EXPORTS
   #else
      #define GUIDEMO_IMPORT_EXPORT
#endif //WIN32

namespace oasis{
namespace sca
{
   class ComponentContext;
} //namespace sca
} //namespace oasis

namespace Trentino{
namespace Example{
namespace GUIDemo
{
   //class declaration
   //**********************************************************************************************
   //                             GUIDemoImpl
   //**********************************************************************************************
   //! GUIDemo implementation testcode
   //**********************************************************************************************
   class GUIDEMO_IMPORT_EXPORT GUIDemoImpl : public GUI
   {
   public:
      GUIDemoImpl();
      virtual ~GUIDemoImpl();

      /*virtual int add(int a, int b);
      virtual int div(int a, int b);*/

	  virtual int start(int a){
		
		  return a;

	  };

      void setGUIDemoLCD(std::list<Trentino::Example::GUIDemo::GUIDemoLCD*> lcd);

	  void setGUIDemoName(std::string name);
	    

   private :

      
      //GUIDemoLCD* mLCD;

	  //@Reference(service="GUIDemoName")
	  std::string name;

	  //@Reference(service="GUIDemoLCD")
	  std::list<GUIDemoLCD*> mLCD;

	  MyControl *gc;
	  
	  
   };//class Calculator

	#include "TrentinoExampleGUIDemoImpl.inl" 

}//namespace BasicCalculator
}//namespace Example
}//namespace Trentino



#endif //TrentinoExampleGUIDemoImplH