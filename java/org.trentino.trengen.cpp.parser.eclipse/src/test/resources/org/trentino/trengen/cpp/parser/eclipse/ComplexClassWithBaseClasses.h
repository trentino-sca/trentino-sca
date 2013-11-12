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




namespace Test{
    namespace Application {
        namespace System2{

            class  Facade : public Test::Application::System::IService ,
                                       public Test::Application::System::IStorageRackCommandService
            {

            };
        }
    }
}
