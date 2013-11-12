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
#ifndef TrentinoBindingBindingHelperBaseH
#define TrentinoBindingBindingHelperBaseH
//standard
#include <boost/shared_ptr.hpp>

namespace Trentino{
namespace Binding
{

   class BindingHelperBase;
   typedef boost::shared_ptr<BindingHelperBase> BindingHelperBasePtr;
   //*****************************************************************
   //                           BindingHelper
   //*****************************************************************
   //! \brief marker interface for all Binding helper classes
   //*****************************************************************
  class BindingHelperBase {
  public:
     //***************************************************************
     //                 version()
     //***************************************************************
     //! \brief the version of the Binding Helper
     //! The version is a hint for the Binding Implementation
     //! based on this value, it decides if the helper is actually
     //! the one needed
     virtual int version() const =0;

   };
} //namespace Trentino
} //namespace RuntimeModel
#endif //TrentinoBindingBindingHelperBaseH