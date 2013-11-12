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

#ifndef TrentinoBindingSCATrentinoBindingSCATestH
#define TrentinoBindingSCATrentinoBindingSCATestH

//standard
#include <boost/shared_ptr.hpp>

//tests
#include <gmock/gmock.h>
#include <gtest/gtest.h>

//specific
#include "../../BindingSCA/TrentinoBindingSCA.h"
#include "../../BindingSCA/TrentinoBindingSCATrentinoBindingSCA.h"


namespace Trentino{
   namespace Binding{
      namespace SCA{
         namespace Tests{

            //****************************************************************************************************
            //                                         Worker
            //****************************************************************************************************
            //! \brief helper class to start the server as a Thread
            //****************************************************************************************************
            class Worker  
               {  
               public:   

                  //****************************************************************************************************
                  //                                         Worker()
                  //****************************************************************************************************
                  //! \brief Construct the worker Thread based on a given BindingSAc Object
                  //! \param Trentino::Binding::SCA::TrentinoBindingSCAPtr bindingSCA
                  //! \return 
                  //****************************************************************************************************
                  Worker(Trentino::Binding::SCA::TrentinoBindingSCAPtr bindingSCA);

                  virtual ~Worker();

                  //****************************************************************************************************
                  //                                         operator()()
                  //****************************************************************************************************
                  //! \brief contains the code to be executed by the WorkerThread: actually start the Binding
                  //! \return void
                  //****************************************************************************************************
                  void operator()();  

               private:  
                  Trentino::Binding::SCA::TrentinoBindingSCAPtr mBindingSCA;
               };



            class TrentinoBindingSCATest :public ::testing::Test{

               //services
            protected:

               //****************************************************************************************************
               //                                         SetUp()
               //****************************************************************************************************
               //! \brief Test Fixtute Setup will create a new Instance of mBindingSCA
               //! \return void
               //****************************************************************************************************
               virtual void SetUp(){
                  using namespace Trentino::Binding::SCA;
                  //context = new TrentinoBindingContext;
                  //context->["binding.sca.port"]=1234;
                  //mBindingSCA = TrentinoBindingSCAPtr (new TrentinoBindingSCA("binding.sca",*context));
                  }


               //data
            protected:
              // Trentino::Binding::SCA::TrentinoBindingSCAPtr mBindingSCA;
              // TrentinoBindingContext* context;

               }; //class TrentinoBindingSCATest

            } //namespace Tests
         }//namespace SCA
      }//namespace TBinding
   }//namepsace Trentino

#endif //TrentinoBindingSCATrentinoBindingSCATestH

