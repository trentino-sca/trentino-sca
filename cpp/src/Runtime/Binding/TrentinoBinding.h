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
#ifndef TrentinoBindingH
#define  TrentinoBindingH


//standard
#include <boost/shared_ptr.hpp>


#include <string>
#include <map>
#include "../../Global/TrentinoGlobal.h"


#ifdef WIN32
#ifdef BINDING_EXPORTS
#define BINDING_IMPORT_EXPORT __declspec(dllexport)
#else
#define BINDING_IMPORT_EXPORT __declspec(dllimport)
#endif //BINDING_EXPORTS
#else
#define BINDING_IMPORT_EXPORT
#endif //WIN32

namespace Trentino{
namespace Binding{


      class TrentinoBinding;
      
      //class declaration
      //**********************************************************************************************
      //                             ContextAttribute                             
      //**********************************************************************************************
      //! \ingroup TrentinoBinding
      //! \brief Ligthweight object that hold attributes read from the central Binding Configuration
      //! The central configuration file is the main place wheres differents bindings integrated to 
      //! the framework are configured.
      //**********************************************************************************************
      typedef std::string ContextAttribute;
      class BindingFactory;
      class BindingManagerBase;



      
      typedef boost::shared_ptr<BindingFactory> BindingFactoryPtr;
      typedef boost::shared_ptr<TrentinoBinding> TrentinoBindingPtr;
      //typedef boost::shared_ptr<ContextAttribute> ContextAttributePtr;
      typedef boost::shared_ptr<BindingManagerBase> BindingManagerBasePtr;
      typedef void (TRENTINO_CDECL *GetBindingFactory)  (Trentino::Binding::BindingFactory* factory,const char* bindindId);


}//namespace Binding
}//namespace Trentino

#endif  //TrentinoBindingH