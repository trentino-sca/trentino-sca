// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2011 by Siemens AG. All rights reserved.
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

#ifndef PersonH
#define PersonH

#ifdef WIN32
   #ifdef PROPERTIES_EXPORTS
      #define PROPERTIES_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define PROPERTIES_IMPORT_EXPORT __declspec(dllimport)
   #endif
#else 
   #define PROPERTIES_IMPORT_EXPORT
#endif

#include <string>
#include <list>

namespace Trentino{
namespace Tests{
namespace Core{
namespace Properties
{
	class PROPERTIES_IMPORT_EXPORT Component
	{
	public:	 
	   void setPropertyWithSingleDefaultValue(const std::string& value);
      void setPropertyWithUselesseDefaultValue(const std::string& value);
      void setPropertyWithManyDefaultValues(const std::list<std::string>& values);
      void setPropertyWithNoDefaultValue(const std::string& values);	   
	}; //class Component
} //namespace Trentino
} //namespace Tests
} //namespace Core
} //namespace Properties

#endif
