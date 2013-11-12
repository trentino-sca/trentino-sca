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

#ifndef TrentinoBindingSCAClientTestH
#define TrentinoBindingSCAClientTestH

//standard
#include <boost/shared_ptr.hpp>

//tests
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../../BindingSCAClient/TrentinoBindingSCAClientProxyDelegate.h"

//specific

namespace Trentino{
   namespace Binding{
      namespace SCA{
         namespace Tests{
            class TrentinoBindingSCAITTest :public ::testing::Test{

               //services
            public:
               TrentinoBindingSCAITTest(): mDelegate("localhost","5342"){}
            protected:
               //data
            protected:
               Trentino::Binding::SCA::Client::BindingProxyDelegate mDelegate;
               }; //class TrentinoBindingSCATest

            class TrentinoBindingSCAITTestHelper {
               //construction
            public:
               TrentinoBindingSCAITTestHelper();


               };

            } //namespace Tests
         }//namespace SCA
      }//namespace TBinding
   }//namepsace Trentino

#endif //TrentinoBindingSCAClientTestH

