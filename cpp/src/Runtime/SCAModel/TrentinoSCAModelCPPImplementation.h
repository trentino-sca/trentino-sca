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

#ifndef TrentinoSCAModelCPPImplementationH
#define TrentinoSCAModelCPPImplementationH
//baseclass
#include "TrentinoSCAModelImplementation.h"
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class CPPImplementation : public Implementation
   {
      //construction
   public:
      CPPImplementation();
   private:
      CPPImplementation(const CPPImplementation&);
      void operator=(const CPPImplementation&);

      //services
   public:



      //element accessors  
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addContentElement(const char* aContent);
     const std::vector<std::string>& contentElements() const;
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addFunctionElement(CPPImplementationFunction* aFunction);
     const std::vector<CPPImplementationFunctionPtr>& functionElements() const;


      //attribute accessors
      bool isAllowsPassByReference() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setAllowsPassByReference(bool isAllowsPassByReference);
      const Trentino::XML::Schema::Name& clazz() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setClazz(const char* aClazz);
      const std::string& componentType() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setComponentType(const char* aComponentType);
      bool isEagerInit() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setEagerInit(bool isEagerInit);
      const std::string& header() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setHeader(const char* aHeader);
      const Trentino::XML::Schema::NCName& library() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setLibrary(const char* aLibrary);
      const std::string& path() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setPath(const char* aPath);
      CPPImplementationScopePtr scope() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setScope(CPPImplementationScope* aScope);


      //data
   protected:
      //elements
      std::vector<std::string> mContentElements;
      std::vector<CPPImplementationFunctionPtr> mFunctionElements;
 
      //attributes
      bool mIsAllowsPassByReference;
      Trentino::XML::Schema::Name mClazz;   
      std::string mComponentType;
      bool mIsEagerInit;
      std::string mHeader;
      Trentino::XML::Schema::NCName mLibrary;   
      std::string mPath;
      CPPImplementationScopePtr mScope;
   }; //class  CPPImplementation

   #include "TrentinoSCAModelCPPImplementation.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelCPPImplementationH
