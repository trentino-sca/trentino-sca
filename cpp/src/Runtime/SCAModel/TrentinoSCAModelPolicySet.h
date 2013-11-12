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

#ifndef TrentinoSCAModelPolicySetH
#define TrentinoSCAModelPolicySetH
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class PolicySet
   {
      //construction
   public:
      PolicySet();
   private:
      PolicySet(const PolicySet&);
      void operator=(const PolicySet&);

      //services
   public:



      //element accessors  
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addIntentMapElement(IntentMap* aIntentMap);
     const std::vector<IntentMapPtr>& intentMapElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPolicySetReferenceElement(PolicySetReference* aPolicySetReference);
     const std::vector<PolicySetReferencePtr>& policySetReferenceElements() const;


      //attribute accessors
      const std::string& appliesTo() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setAppliesTo(const char* aAppliesTo);
      const std::string& attachTo() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setAttachTo(const char* aAttachTo);
      const Trentino::XML::Schema::NCName& name() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setName(const char* aName);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addProvides(Trentino::XML::Schema::QName* aProvides);
     const std::vector<QNamePtr>& provides() const;



      //data
   protected:
      //elements
      std::vector<IntentMapPtr> mIntentMapElements;
      std::vector<PolicySetReferencePtr> mPolicySetReferenceElements;
 
      //attributes
      std::string mAppliesTo;
      std::string mAttachTo;
      Trentino::XML::Schema::NCName mName;   
      std::vector<QNamePtr> mProvides;
   }; //class  PolicySet

   #include "TrentinoSCAModelPolicySet.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelPolicySetH
