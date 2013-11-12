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

#ifndef TrentinoTestsCoreComponentWith2RefH
#define TrentinoTestsCoreComponentWith2RefH

#ifdef WIN32
   #ifdef SEPARATEWIRES_EXPORTS          
      #undef SEPARATEWIRES_IMPORT_EXPORT
      #define SEPARATEWIRES_IMPORT_EXPORT __declspec(dllexport)
   #else
      #undef SEPARATEWIRES_IMPORT_EXPORT
      #define SEPARATEWIRES_IMPORT_EXPORT __declspec(dllimport)       
   #endif //SEPARATEWIRES_EXPORTS
   #else
      #define SEPARATEWIRES_IMPORT_EXPORT
#endif //WIN32

//standard
#include <list>

namespace Trentino{
namespace Tests{
namespace Core
{  
   class EmptyService;
   class EmptyService2;

   class SEPARATEWIRES_IMPORT_EXPORT ComponentWith2Ref
   {
   public:
      void setEmptyService(std::list<EmptyService*>);
      void setEmptyService2(std::list<EmptyService2*>);
   };//class ComponentWithRef
}//namespace Core
}//namespace Tests
}//namespace Trentino

#endif //TrentinoTestsCoreComponentWith2RefH