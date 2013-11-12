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

#ifndef TrentinoSCAModelCommonExtensionBaseH
#define TrentinoSCAModelCommonExtensionBaseH
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class CommonExtensionBase
   {
      //construction
   public:
      CommonExtensionBase();
   private:
      CommonExtensionBase(const CommonExtensionBase&);
      void operator=(const CommonExtensionBase&);

      //services
   public:



      //element accessors  
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addDocumentationElement(Documentation* aDocumentation);
     const std::vector<DocumentationPtr>& documentationElements() const;




      //data
   protected:
      //elements
      std::vector<DocumentationPtr> mDocumentationElements;
 
   }; //class  CommonExtensionBase

   #include "TrentinoSCAModelCommonExtensionBase.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelCommonExtensionBaseH
