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

#ifndef TrentinoSCAModelProblemActionTypeH
#define TrentinoSCAModelProblemActionTypeH

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class ProblemActionType
   {
      //construction
   public:
      ProblemActionType();
   private:
      ProblemActionType(const ProblemActionType&);
      void operator=(const ProblemActionType&);

      //services
   public:



      //element accessors  
      AttributedURITypePtr actionElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setAction(AttributedURIType* aAction);
      const Trentino::XML::Schema::AnyURI& soapActionElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setSoapAction(const char* aSoapAction);



      //data
   protected:
      //elements
      AttributedURITypePtr mActionElement;
      Trentino::XML::Schema::AnyURI mSoapActionElement;   
 
   }; //class  ProblemActionType

   #include "TrentinoSCAModelProblemActionType.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelProblemActionTypeH
