////////////////////////////////////////////////////////////////////////////////////////////////////
// Project: Energy Agent Framework-StorageRackController
//
// File   : StorageRackFacade.h
//
// Summary: Declares the storage rack facade class
//
// Copyright (c) Siemens AG 2012 All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "IService.h"
#include <SubFolder/SubSubFolder/IService2.h>

namespace Test{
    namespace Application {
        namespace System2{

            class  Facade : public Test::Application::System::IService ,
                                       public Test::Application::System2::IService2
            {
            public:
            	virtual int method3(Class5 obj5, Class6 obj6);
            };
        }
    }
}
