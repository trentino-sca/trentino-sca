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

#ifndef TrentinoSCAModelIntentH
#define TrentinoSCAModelIntentH
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class Intent
   {
      //construction
   public:
      Intent();
   private:
      Intent(const Intent&);
      void operator=(const Intent&);

      //services
   public:



      //element accessors  
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addContentElement(const char* aContent);
     const std::vector<std::string>& contentElements() const;
      const std::string& descriptionElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setDescription(const char* aDescription);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addQualifierElement(IntentQualifier* aQualifier);
     const std::vector<IntentQualifierPtr>& qualifierElements() const;


      //attribute accessors
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addConstrains(Trentino::XML::Schema::QName* aConstrains);
     const std::vector<QNamePtr>& constrains() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addExcludes(Trentino::XML::Schema::QName* aExcludes);
     const std::vector<QNamePtr>& excludes() const;

      InteractionOrImplementationPtr intentType() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setIntentType(InteractionOrImplementation* aIntentType);
      bool isMutuallyExclusive() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setMutuallyExclusive(bool isMutuallyExclusive);
      const Trentino::XML::Schema::NCName& name() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setName(const char* aName);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addRequires(Trentino::XML::Schema::QName* aRequires);
     const std::vector<QNamePtr>& requires() const;



      //data
   protected:
      //elements
      std::vector<std::string> mContentElements;
      std::string mDescriptionElement;
      std::vector<IntentQualifierPtr> mQualifierElements;
 
      //attributes
      std::vector<QNamePtr> mConstrains;
      std::vector<QNamePtr> mExcludes;
      InteractionOrImplementationPtr mIntentType;
      bool mIsMutuallyExclusive;
      Trentino::XML::Schema::NCName mName;   
      std::vector<QNamePtr> mRequires;
   }; //class  Intent

   #include "TrentinoSCAModelIntent.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelIntentH
