// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************

#ifndef TrentinoBindingSCAClientImportExportH
#define TrentinoBindingSCAClientImportExportH

#ifdef WIN32
   #ifdef BINDINGSCACLIENT_EXPORTS
      #define BINDINGSCACLIENT_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define BINDINGSCACLIENT_IMPORT_EXPORT __declspec(dllimport)
   #endif //BINDINGSCACLIENT_EXPORTS
   #else
      #define BINDINGSCACLIENT_IMPORT_EXPORT
#endif //WIN32

#endif //TrentinoBindingSCAClientImportExportH
