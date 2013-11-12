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

#ifndef TrentinoExampleGUIDemoLCDImplH
#define TrentinoExampleGUIDemoLCDImplH

#include <boost/cstdint.hpp>
#include <string>
/*
typedef  boost::int32_t  tint32_t;
typedef  boost::uint32_t  tuint32_t;
typedef  boost::int64_t  tint64_t;
typedef  boost::uint64_t  tuint64_t;
*/
//specific
#include "services/TrentinoExampleGUIDemoLCD.h"

#include "..\GUIDemoRemote_Source\GuiStart.h"


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


namespace Trentino{
namespace Example{
namespace GUIDemo
{
   //class declaration
   //**********************************************************************************************
   //                             GUIDemoLCDImpl
   //**********************************************************************************************
   //! GUIDemoLCDImpl implementation testcode
   //**********************************************************************************************
   class GUIDEMO_IMPORT_EXPORT GUIDemoLCDImpl : public GUIDemoLCD
   {
      //construction
   public :
      GUIDemoLCDImpl();
      virtual ~GUIDemoLCDImpl();

      //services
   public :
      void  showLCDNum (const tint32_t val);

      void  setGUIDemoLCDName (const std::string& name);

   private:
	   //@Reference(service="GUIDemoLCDName")
	  //std::string name;

	  Gui_Control *gc2;
	  
   };//class GUIDemoLCD

}//namespace GUIDemo
}//namespace Example
}//namespace Trentino



#endif //TrentinoExampleGUIDemoLCDImplH