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

//standard
#include <cstring>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <gtest/gtest.h>

//specific
#include "../../Runtime/Core/TrentinoCoreBootstrappingBootstrapperBase.h"
#include "../../Runtime/Core/TrentinoCoreBootstrappingModuleBase.h"

using namespace std;
using namespace Trentino::Core::Bootstrapping;
//using namespace Trentino::Tests::Core;

//class declarations
class Module1 : public ModuleBase
{
public:
   //construction
   Module1() : mStartUp(false), mShutdown(false), mInitialize(false), mDeinitialize(false) {}
   //service
public:
      virtual void startUp()
      {
         mStartUp = true;
      }

      virtual void shutdown()
      {
         mShutdown = true;
      }

      virtual void initialize()
      {
         mInitialize = true;
      }

      virtual void deinitialize()
      {
         mDeinitialize = true;
      }

      bool isInitialized() const
      {
         return (mInitialize == true && mDeinitialize == false);
      }

      virtual bool isStartUp() const
      {
         return (mStartUp == true && mShutdown == false);
      }

      //data
public:
   bool mStartUp;
   bool mShutdown;
   bool mInitialize;
   bool mDeinitialize;
}; //class Module1


TEST(BootstrapperTest, testBootstapper)
{
   BootstrapperBase bts;

   boost::intrusive_ptr<Module1> newMod1(new Module1);

   bts.registerNewModule(newMod1);
   ASSERT_EQ(false, newMod1->mStartUp);
   ASSERT_EQ(false, newMod1->mShutdown);
   ASSERT_EQ(false, newMod1->mInitialize);
   ASSERT_EQ(false, newMod1->mDeinitialize);

   // startup
   bts.startUp();
   ASSERT_EQ(true, newMod1->mStartUp);
   ASSERT_EQ(false, newMod1->mShutdown);
   ASSERT_EQ(false, newMod1->mInitialize);
   ASSERT_EQ(false, newMod1->mDeinitialize);

   // initialize
   bts.initialize();
   ASSERT_EQ(true, newMod1->mStartUp);
   ASSERT_EQ(true, newMod1->mInitialize);
   ASSERT_EQ(false, newMod1->mDeinitialize);
   ASSERT_EQ(false, newMod1->mShutdown);

   //register new module with autoregistration
   boost::intrusive_ptr<Module1> newMod2(new Module1);
   ASSERT_EQ(false, newMod2->mStartUp);
   ASSERT_EQ(false, newMod2->mShutdown);
   ASSERT_EQ(false, newMod2->mInitialize);
   ASSERT_EQ(false, newMod2->mDeinitialize);
   bts.registerNewModule(newMod2,true);
   ASSERT_EQ(true, newMod2->mStartUp);
   ASSERT_EQ(true, newMod2->mInitialize);
   ASSERT_EQ(false, newMod2->mDeinitialize);
   ASSERT_EQ(false, newMod2->mShutdown);

   //unregister module with autoregistration
   bts.unregisterNewModule(newMod1, true);
   ASSERT_EQ(true, newMod1->mStartUp);
   ASSERT_EQ(true, newMod1->mShutdown);
   ASSERT_EQ(true, newMod1->mInitialize);
   ASSERT_EQ(true, newMod1->mDeinitialize);

   bts.deinitialize();
   ASSERT_EQ(true, newMod2->mStartUp);
   ASSERT_EQ(true, newMod2->mInitialize);
   ASSERT_EQ(true, newMod2->mDeinitialize);
   ASSERT_EQ(false, newMod2->mShutdown);

   bts.shutdown();
   ASSERT_EQ(true, newMod2->mStartUp);
   ASSERT_EQ(true, newMod2->mInitialize);
   ASSERT_EQ(true, newMod2->mDeinitialize);
   ASSERT_EQ(true, newMod2->mShutdown);
}
