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

#ifndef TrentinoCoreContributionLoadingRuntimeModelCreatorH
#define TrentinoCoreContributionLoadingRuntimeModelCreatorH

//specific
#include "../RuntimeModel/TrentinoRuntimeModel.h"
#include "../SCAModel/TrentinoSCAModel.h"
#include "../../Utils/TrentinoUtils.h"
#include "../../Utils/TrentinoUtilsURI.h"

//standard
#include <string>
#include <vector>

namespace Trentino{
namespace Core
{
   class TrentinoContributionInfo;
} //namespace Core
} //namespace Trentino

namespace Trentino{
namespace Core{
namespace ContributionLoading
{
   //**********************************************************************************************
   //                                     RuntimeModelCreator 
   //**********************************************************************************************
   //! \ingroup ContributionLoading
   //! \brief Responsible for creating RuntimeModel objects corresponding to the SCA::Model object
   //!        graph. 
   //**********************************************************************************************
   class RuntimeModelCreator
   {
      //additional
   public:
      typedef std::vector<Trentino::Utils::DynamicLibraryPtr> DLLs;

      //construction
   private:
      //*******************************************************************************************
      //                                  RuntimeModelCreator()
      //*******************************************************************************************
      //! \brief Disallow construction (class has only static methods and no data).      
      //*******************************************************************************************
      RuntimeModelCreator();

      //*******************************************************************************************
      //                                  ~RuntimeModelCreator()
      //*******************************************************************************************
      //! \brief Disallow destruction (class has only static members and no data).   
      //*******************************************************************************************
      ~RuntimeModelCreator();

      //*******************************************************************************************
      //                       RuntimeModelCreator(const RuntimeModelCreator&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copying.      
      //*******************************************************************************************
      RuntimeModelCreator(const RuntimeModelCreator&);

      //operators
   private:
      //*******************************************************************************************
      //                                        operator=()
      //*******************************************************************************************
      //! \brief Disallow inadvertent assignment.      
      //*******************************************************************************************
      void operator=(const RuntimeModelCreator&);

      //services
   public:
      //*******************************************************************************************
      //                                     createContribution()
      //*******************************************************************************************
      //! \brief Creates a RuntimeModel::Contribution object with the given parameters. 
      //!
      //! \param[in] scaModelDescriptor A shared pointer to an SCA::Model::ModelDescriptor object
      //!            providing access to the in-memory SCDL representation constituting the 
      //!            contribution.
      //! \param[in] baseURI Base URI to be assigned to the contribution.
      //! \param[in] localPath Path to the contribution's root directory. 
      //! \param[in] contributionDLL A shared pointer to an Utils::DynamicLibrary object 
      //!            representing the contribution's dynamic library. 
      //! \param[in] businessDlls Collection of shared pointers to Utils::DynamicLibrary objects 
      //!            representing the business logic libraries contained in the contribution.
      //! \param[in] contributionInfo Raw pointer to the Core::ContributionInfo* object containting  
      //!            further information to be associated with the contribution.
      //! \return A shared pointer to the newly created RuntimeModel::Contribution object.
      //*******************************************************************************************
      static Trentino::RuntimeModel::ContributionPtr createContribution( 
         const Trentino::SCA::Model::ModelDescriptorPtr& scaModelDescriptor,
         const Trentino::Utils::URI& baseURI, 
         const std::string& localPath,
         const Trentino::Utils::DynamicLibraryPtr& contributionDLL,
         const DLLs businessDlls,
         Trentino::Core::TrentinoContributionInfo* contributionInfo);   
      
      
      //*******************************************************************************************
      //                                     createComposite()
      //*******************************************************************************************
      //! \brief Creates a RuntimeModel::Composite object based on the given SCA::Model::Composite
      //!        object.
      //!      
      //! \param[in] scaComposite A shared pointer to an SCA::Model::Composite object that will be 
      //!            used as "information source" for creating the RuntimeModel::Composite.
      //! \param[in] contribution A shared pointer to the parent contribution of the to be created
      //!            composite. 
      //! \return A shared pointer to the newly created RuntimeModel::Composite object. 
      //!
      //! In particular the following steps are performed:
      //! -# A RuntimeModel::Composite object is created and associated with the passed 
      //!    SCA::Model::Composite and the given parent contribution.
      //! -# For each component contained in \c scaComposite a corresponding 
      //!    RuntimeModel::Component object is created and added to the RuntimeModel::Composite 
      //!    created in the first step. Altogether, this steps consists in a chain of (indirect)
      //!    recursive function calls, each of which is responsible for creating certain 
      //!    RuntimeModel objects representing certain SCDL entities (such as \c \<component\>,
      //!    \<service\>, \c \<reference\>, \c \<property\> and \c \<implementation\> elements). 
      //!    The recursive character of the creation process directly corresponds to the 
      //!    hierarchical nature of %SCA: composites contain (point to) components, that in turn 
      //!    might point to composites (as their implementation: \c \<implementation.composite\>) 
      //!    which in turn contain components etc. When this step completes, the created 
      //!    RuntimeModel::Composite object can be regarded as a root of a consistent object graph
      //!    representing all the information associated with a composite and it's children. 
      //! -# The created RuntimeModel::Composite is added to its parent contribution.      
      //*******************************************************************************************
      static Trentino::RuntimeModel::CompositePtr createComposite( 
         const Trentino::SCA::Model::CompositePtr& scaComposite, 
         const Trentino::RuntimeModel::ContributionPtr& contribution);

   }; //class RuntimeModelCreator

} //namespace ContributionLoading
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreContributionLoadingRuntimeModelCreatorH