// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
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

#ifndef SCAReferenceExampleH
#define SCAReferenceExampleH

//standard
#include <string>
#include <list>

namespace TrentinoNamespace
{
   //forward declaration
   class SCAServiceToAttach;

   //class declaration
   class SCAReferenceExample 
   {
      //services
   public:
      //Property1
      virtual const int Property1() const = 0;
      virtual void setProperty1(const int value) = 0;

      //Property2
      virtual const std::string& Property2() const = 0;
      virtual void setProperty2(const std::string& value) = 0;

      //Property3
      virtual const bool Property3() const = 0;
      virtual void setProperty3(const bool value) = 0;

      //MultiProperty
      virtual const std::list<std::string>& MultiProperty() const = 0;
      virtual void setMultiProperty(const std::list<std::string>& values) = 0;

      //ValueFileProperty
      virtual const int ValueFileProperty() const = 0;
      virtual void setValueFileProperty(const int value) = 0;

      //SCAServiceToAttachRef
      virtual void setSCAServiceToAttachRef(SCAServiceToAttach* value) = 0;
      
      //SCAServicesToAttachRef
      virtual void setSCAServicesToAttachRef(const std::list<SCAServiceToAttach*>& values) = 0;
   };
}//namespace TrentinoNamespace


#endif//SCAReferenceExampleH