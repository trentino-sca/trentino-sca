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

#ifndef TrentinoBindingIpcImportExportH
#define TrentinoBindingIpcImportExportH

#ifdef WIN32
   #ifdef BINDINGIPCSERVER_EXPORTS
      #define BINDINGIPC_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define BINDINGIPC_IMPORT_EXPORT __declspec(dllimport)
   #endif //BINDINGIPC_EXPORTS
   #else
      #define BINDINGIPC_IMPORT_EXPORT
#endif //WIN32

#endif //TrentinoBindingIPCImportExportH
