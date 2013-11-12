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

#ifndef TrentinoSCAModelCPPImportH
#define TrentinoSCAModelCPPImportH
//baseclass
#include "TrentinoSCAModelImport.h"

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class CPPImport : public Import
   {
      //construction
   public:
      CPPImport();
   private:
      CPPImport(const CPPImport&);
      void operator=(const CPPImport&);

      //services
   public:



      //attribute accessors
      const std::string& location() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setLocation(const char* aLocation);
      QNamePtr name() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setName(Trentino::XML::Schema::QName* aName);
      const std::string& version() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setVersion(const char* aVersion);


      //data
   protected:
 
      //attributes
      std::string mLocation;
      QNamePtr mName;
      std::string mVersion;
   }; //class  CPPImport

   #include "TrentinoSCAModelCPPImport.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelCPPImportH
