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

#ifndef TrentinoSCADomainContextH
#define TrentinoSCADomainContextH

//standard
#include <string>

//specific
#include "./../../Global/TrentinoGlobal.h"
#include "./../Oasis/sca/DomainContext.h"
#include "./../Oasis/sca/ServiceProxy.h"
#include "TrentinoCoreDomain.h"

namespace Trentino{
namespace Core
{
   class SCADomainContext : public oasis::sca::DomainContext
   {
      //services
   public:
      virtual oasis::sca::ServiceProxyPtr getService(const std::string& serviceURI) const;
   }; //class SCADomainContext


} //namespace Core
} //namespace Trentino


#endif //TrentinoSCADomainContextH