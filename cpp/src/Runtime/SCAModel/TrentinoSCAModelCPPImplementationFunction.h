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

#ifndef TrentinoSCAModelCPPImplementationFunctionH
#define TrentinoSCAModelCPPImplementationFunctionH
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class CPPImplementationFunction
   {
      //construction
   public:
      CPPImplementationFunction();
   private:
      CPPImplementationFunction(const CPPImplementationFunction&);
      void operator=(const CPPImplementationFunction&);

      //services
   public:



      //element accessors  
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addContentElement(const char* aContent);
     const std::vector<std::string>& contentElements() const;
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment);
     const std::vector<PolicySetAttachmentPtr>& policySetAttachmentElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addRequiresElement(Requires* aRequires);
     const std::vector<RequiresPtr>& requiresElements() const;


      //attribute accessors
      bool isAllowsPassByReference() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setAllowsPassByReference(bool isAllowsPassByReference);
      bool isDestroy() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setDestroy(bool isDestroy);
      bool isInit() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setInit(bool isInit);
      const Trentino::XML::Schema::NCName& name() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setName(const char* aName);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySets(Trentino::XML::Schema::QName* aPolicySets);
     const std::vector<QNamePtr>& policySets() const;



      //data
   protected:
      //elements
      std::vector<std::string> mContentElements;
      std::vector<PolicySetAttachmentPtr> mPolicySetAttachmentElements;
      std::vector<RequiresPtr> mRequiresElements;
 
      //attributes
      bool mIsAllowsPassByReference;
      bool mIsDestroy;
      bool mIsInit;
      Trentino::XML::Schema::NCName mName;   
      std::vector<QNamePtr> mPolicySets;
   }; //class  CPPImplementationFunction

   #include "TrentinoSCAModelCPPImplementationFunction.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelCPPImplementationFunctionH
