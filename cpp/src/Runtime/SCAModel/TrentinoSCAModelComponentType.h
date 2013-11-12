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

#ifndef TrentinoSCAModelComponentTypeH
#define TrentinoSCAModelComponentTypeH
//baseclass
#include "TrentinoSCAModelCommonExtensionBase.h"
//standard
#include <vector>

//specific
#include "TrentinoSCAModel.h"
 
namespace Trentino{
namespace SCA{
namespace Model
{
   class ComponentType : public CommonExtensionBase
   {
      //construction
   public:
      ComponentType();
   private:
      ComponentType(const ComponentType&);
      void operator=(const ComponentType&);

      //services
   public:



      //element accessors  
      ExtensionsPtr extensionsElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setExtensions(Extensions* aExtensions);
      ImplementationPtr implementationElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setImplementation(Implementation* aImplementation);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addPropertyElement(Property* aProperty);
     const std::vector<PropertyPtr>& propertyElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addReferenceElement(ComponentTypeReference* aReference);
     const std::vector<ComponentTypeReferencePtr>& referenceElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addServiceElement(ComponentService* aService);
     const std::vector<ComponentServicePtr>& serviceElements() const;




      //data
   protected:
      //elements
      ExtensionsPtr mExtensionsElement;
      ImplementationPtr mImplementationElement;
      std::vector<PropertyPtr> mPropertyElements;
      std::vector<ComponentTypeReferencePtr> mReferenceElements;
      std::vector<ComponentServicePtr> mServiceElements;
 
   }; //class  ComponentType

   #include "TrentinoSCAModelComponentType.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelComponentTypeH
