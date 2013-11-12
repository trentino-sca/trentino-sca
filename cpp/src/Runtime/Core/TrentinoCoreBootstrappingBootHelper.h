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

#ifndef TrentinoCoreBootstrappingBootHelperH
#define TrentinoCoreBootstrappingBootHelperH

//standard
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>

//specific
#include "TrentinoCoreBootstrappingRuntimeBootstrapper.h"

namespace Trentino{
namespace Core{
namespace Bootstrapping
{
   class RuntimeConfiguration;
   //forward declarations
   class BootstrapperBase;

   template <typename TYPE> class BootHelper
   {
      //additional
   public:
      typedef boost::shared_ptr<TYPE> BootPtr;
      //services
   public:
      BootPtr boot(const RuntimeBootstrapper::RuntimeConfigurationConstPtr& configuration = 
         boost::make_shared<RuntimeConfiguration>());

      void shutdown(BootPtr& app);
   }; //template class BootHelper

   #include "TrentinoCoreBootstrappingBootHelper.inl"

}//namespace Bootstrapping
}//namespace Core
}//namespace Trentino

#endif//TrentinoCoreBootstrappingBootHelperH
