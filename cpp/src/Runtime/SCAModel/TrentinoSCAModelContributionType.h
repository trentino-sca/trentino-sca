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

#ifndef TrentinoSCAModelContributionTypeH
#define TrentinoSCAModelContributionTypeH
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
   class ContributionType : public CommonExtensionBase
   {
      //construction
   public:
      ContributionType();
   private:
      ContributionType(const ContributionType&);
      void operator=(const ContributionType&);

      //services
   public:



      //element accessors  
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addDeployableElement(DeployableType* aDeployable);
     const std::vector<DeployableTypePtr>& deployableElements() const;

     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addExportBaseElement(Export* aExportBase);
     const std::vector<ExportPtr>& exportBaseElements() const;

      ExtensionsPtr extensionsElement() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setExtensions(Extensions* aExtensions);
     SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  addImportBaseElement(Import* aImportBase);
     const std::vector<ImportPtr>& importBaseElements() const;


      //attribute accessors
      const std::string& version() const;
      SCAMODEL_IMPORT_EXPORT void TRENTINO_STDCALL  setVersion(const char* aVersion);


      //data
   protected:
      //elements
      std::vector<DeployableTypePtr> mDeployableElements;
      std::vector<ExportPtr> mExportBaseElements;
      ExtensionsPtr mExtensionsElement;
      std::vector<ImportPtr> mImportBaseElements;
 
      //attributes
      std::string mVersion;
   }; //class  ContributionType

   #include "TrentinoSCAModelContributionType.inl"   

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelContributionTypeH
