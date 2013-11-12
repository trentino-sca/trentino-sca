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

#ifndef TrentinoSCAModelCPPInterfaceH
#define TrentinoSCAModelCPPInterfaceH
//baseclass
#include "TrentinoSCAModelInterface.h"
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class CPPInterface : public Interface
   {
      //construction
   public:
      CPPInterface();
   private:
      CPPInterface(const CPPInterface&);
      void operator=(const CPPInterface&);

      //services
   public:



      //element accessors  
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addCallbackFunctionElement(CPPFunction* aCallbackFunction);
     const std::vector<CPPFunctionPtr>& callbackFunctionElements() const;

      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addContentElement(const char* aContent);
     const std::vector<std::string>& contentElements() const;
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addFunctionElement(CPPFunction* aFunction);
     const std::vector<CPPFunctionPtr>& functionElements() const;


      //attribute accessors
      const Trentino::XML::Schema::Name& callbackClass() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setCallbackClass(const char* aCallbackClass);
      const std::string& callbackHeader() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setCallbackHeader(const char* aCallbackHeader);
      const Trentino::XML::Schema::Name& clazz() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setClazz(const char* aClazz);
      const std::string& header() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setHeader(const char* aHeader);


      //data
   protected:
      //elements
      std::vector<CPPFunctionPtr> mCallbackFunctionElements;
      std::vector<std::string> mContentElements;
      std::vector<CPPFunctionPtr> mFunctionElements;
 
      //attributes
      Trentino::XML::Schema::Name mCallbackClass;   
      std::string mCallbackHeader;
      Trentino::XML::Schema::Name mClazz;   
      std::string mHeader;
   }; //class  CPPInterface

   #include "TrentinoSCAModelCPPInterface.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelCPPInterfaceH
