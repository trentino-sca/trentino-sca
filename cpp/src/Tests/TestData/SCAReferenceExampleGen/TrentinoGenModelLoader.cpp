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

//standard
#include <Global/TrentinoGlobal.h>
#include <Runtime/Core/TrentinoCoreSCAModelLoader.h>

#include <Runtime/SCAModel/TrentinoSCAModelContributionType.h>
#include <Runtime/SCAModel/TrentinoSCAModelDeployableType.h>
#include <Runtime/SCAModel/TrentinoSCAModelComposite.h>
#include <Runtime/SCAModel/TrentinoSCAModelComponent.h>
#include <Runtime/SCAModel/TrentinoSCAModelComponentService.h>
#include <Runtime/SCAModel/TrentinoSCAModelComponentReference.h>
#include <Runtime/SCAModel/TrentinoSCAModelCPPImplementation.h>
#include <Runtime/SCAModel/TrentinoSCAModelCPPImplementationScope.h>
#include <Runtime/SCAModel/TrentinoSCAModelCPPInterface.h>

#ifdef WIN32
#ifdef SCAREFERENCEEXAMPLEGEN_EXPORTS
#undef SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT
#define SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT __declspec(dllexport)
#else
#undef SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT
#define SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT __declspec(dllimport)       
#endif //SCAREFERENCEEXAMPLEGEN_EXPORTS
#else
#define SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT
#endif //WIN32


// This is an example of an exported function.
extern "C" SCAREFERENCEEXAMPLEGEN_IMPORT_EXPORT void TRENTINO_CDECL loadModels(Trentino::Core::SCAModelLoader* modelLoader)
{
   assert(modelLoader != nullptr);

   Trentino::Core::SCAModelLoader::SCAModelFactory& factory = modelLoader->scaModelFactory();
   

   //Composite
   Trentino::SCA::Model::Composite* const composite = factory.createComposite();
   composite->setName("ServiceDummy");
   composite->setTargetNamespace("ServiceDummyNamespace");

   Trentino::XML::Schema::QName* compositeQName = 
      factory.createQName("ServiceDummyComposite", "ServiceDummyNamespace");

   Trentino::SCA::Model::DeployableType* const deployable = factory.createDeployableType();
   deployable->setComposite(compositeQName);
   
   //Contribution
   Trentino::SCA::Model::ContributionType* const contribution = factory.createContributionType();
   contribution->addDeployableElement(deployable);
}
