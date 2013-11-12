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
#ifndef TrentinoCoreMocksH
#define TrentinoCoreMocksH
//tests
#include <gmock/gmock.h>

//specific
#include "../../Runtime/Core/TrentinoCoreComponentImplementationManagerBase.h"


namespace Trentino{
namespace Core{
namespace Tests{

		class MockComponentImplementationManagerBase : public ComponentImplementationManagerBase {
		 public:
		  MOCK_METHOD1(onInit,
			  void(const Trentino::RuntimeModel::ConstComponentPtr& component));
		  MOCK_METHOD1(getInstance,
			  void*(const Trentino::RuntimeModel::ConstComponentPtr& component));
		  MOCK_METHOD1(getInstance,
			  void*(const Trentino::RuntimeModel::ConstServiceBasePtr& service));
		  MOCK_METHOD2(releaseInstance,
			  void(void* instance , const Trentino::RuntimeModel::ConstServiceBasePtr& service));
		  MOCK_METHOD1(onRemove,
			  void(const Trentino::RuntimeModel::ConstComponentPtr& component));
		};
      }  // namespace Tests
   }  // namespace RuntimeModel
}  // namespace Trentino

#endif //TrentinoCoreMocksH