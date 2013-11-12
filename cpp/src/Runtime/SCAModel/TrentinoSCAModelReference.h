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

#ifndef TrentinoSCAModelReferenceH
#define TrentinoSCAModelReferenceH
//baseclass
#include "TrentinoSCAModelContract.h"
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class Reference : public Contract
   {
      //construction
   public:
      Reference();
   private:
      Reference(const Reference&);
      void operator=(const Reference&);

      //services
   public:



      //attribute accessors
      const std::string& multiplicity() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setMultiplicity(const char* aMultiplicity);
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPromote(const char* aPromote);
     const std::vector<std::string>& promotes() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addTarget(const char* aTarget);
     const std::vector<std::string>& targets() const;
      bool isWiredByImpl() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setWiredByImpl(bool isWiredByImpl);


      //data
   protected:
 
      //attributes
      std::string mMultiplicity;
      std::vector<std::string> mPromotes;
      std::vector<std::string> mTargets;
      bool mIsWiredByImpl;
   }; //class  Reference

   #include "TrentinoSCAModelReference.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelReferenceH
