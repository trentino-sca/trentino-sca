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

#ifndef SCAReferenceExampleImplH
#define SCAReferenceExampleImplH

//specific
#include "services\SCAReferenceExample.h"

#ifdef WIN32
#ifdef SCAREFERENCEEXAMPLE_EXPORTS
#undef SCAREFERENCEEXAMPLEIMPL_IMPORT_EXPORT
#define SCAREFERENCEEXAMPLEIMPL_IMPORT_EXPORT __declspec(dllexport)
#else
#undef SCAREFERENCEEXAMPLEIMPL_IMPORT_EXPORT
#define SCAREFERENCEEXAMPLEIMPL_IMPORT_EXPORT __declspec(dllimport)       
#endif //SCAREFERENCEEXAMPLE_EXPORTS
#else
#define SCAREFERENCEEXAMPLEIMPL_IMPORT_EXPORT
#endif //WIN32

namespace TrentinoNamespace
{
   //forward declaration
   class SCAServiceToAttach;

   class SCAREFERENCEEXAMPLEIMPL_IMPORT_EXPORT SCAReferenceExampleImpl : public SCAReferenceExample
   {
      //services
   public:
      //Property1
      virtual const int Property1() const;
      virtual void setProperty1(const int value);

      //Property2
      virtual const std::string& Property2() const;
      virtual void setProperty2(const std::string& value);

      //Property3
      virtual const bool Property3() const;
      virtual void setProperty3(const bool value);

      //MultiProperty
      virtual const std::list<std::string>& MultiProperty() const;
      virtual void setMultiProperty(const std::list<std::string>& values);

      //ValueFileProperty
      virtual const int ValueFileProperty() const;
      virtual void setValueFileProperty(const int value);

      //SCAServiceToAttachRef
      virtual void setSCAServiceToAttachRef(SCAServiceToAttach* value);

      //SCAServicesToAttachRef
      virtual void setSCAServicesToAttachRef(const std::list<SCAServiceToAttach*>& values);

   private:
      //@Reference(service="SCAServiceToAttach")
      SCAServiceToAttach* mSCAServiceToAttach;

      std::list<SCAServiceToAttach*> mSCAServicesToAttach;

      int mProperty1;
      std::string mProperty2;
      bool mProperty3;
      std::list<std::string> mMultiProperty;
      int mValueProperty;

   };//class SCAReferenceExampleImpl

}//namespace TrentinoNamespace


#endif//SCAReferenceExampleImplH

