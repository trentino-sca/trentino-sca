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

#ifndef TrentinoRuntimeModelContributionH
#define TrentinoRuntimeModelContributionH

//standard
#include <string>

//specific
#include "TrentinoRuntimeModel.h"
#include "./../SCAModel/TrentinoSCAModel.h"
#include "./../Core/TrentinoCore.h"
#include "./../../Utils/TrentinoUtils.h"
#include "./../../Utils/TrentinoUtilsURI.h"
#include "./../XML/TrentinoXMLSchemaQName.h"
#include "../Core/TrentinoCoreContributionInfo.h"

namespace Trentino{
namespace RuntimeModel
{
   //**********************************************************************************************
   //                                       Contribution
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief Represents an SCA contribution at runtime.
   //!
   //! The RuntimeModel::Contribution class points to the corresponding 
   //! SCA::Model::ContributionType class and provides additional information associated with a 
   //! contribution. Examples for such additional information are: 
   //! - the contribution's base URI 
   //! - a collection of RuntimeModel::Composite instances contained within the contribution    
   //**********************************************************************************************
   class RUNTIMEMODEL_IMPORT_EXPORT Contribution
   {
      //additional
   public:
      enum State{ None //!< represents an invalid state
                , Installed
                , Deployed
                , Running };

      //construction
   public:
      //*******************************************************************************************
      //                                     Contribution()
      //*******************************************************************************************
      //! \brief Constructs a contribution with the given base URI and associates it with the given
      //!        SCA::Model::ModelDescriptor.
      //! \param[in] scaModelDescriptor A shared pointer to the SCA::Model::ModelDescriptor instance
      //!            the contribution should be associated with.
      //! \param[in] baseURI The base URI of the contribution. 
      //! \sa scaModelDescriptor(), baseURI()
      //*******************************************************************************************
      Contribution( const Trentino::SCA::Model::ModelDescriptorPtr& scaModelDescriptor
                  , const Trentino::Utils::URI& baseURI);

      //*******************************************************************************************
      //                                     ~Contribution()
      //*******************************************************************************************
      //! \brief Destructor.
      //*******************************************************************************************
      ~Contribution();
   private:
      //*******************************************************************************************
      //                           Contribution(const Contribution&)
      //*******************************************************************************************
      //! \brief Disallow copy construction.    
      //*******************************************************************************************
      Contribution(const Contribution&);

      //operators
   private:
      //*******************************************************************************************
      //                                       operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.
      //*******************************************************************************************
      void operator=(const Contribution&);

      //services
   public:      
      //*******************************************************************************************
      //                                    scaModelDescriptor()
      //*******************************************************************************************
      //! \brief Returns the ModelDescriptor representing the contribution's sca model. 
      //! \return A shared pointer to the ModelDescriptor for the contribution.
      //! \sa Contribution()
      //*******************************************************************************************
      Trentino::SCA::Model::ModelDescriptorPtr scaModelDescriptor() const;

      //*******************************************************************************************
      //                                        baseURI()
      //*******************************************************************************************
      //! \brief Returns the base URI for the contribution.
      //! \return A const reference to the base URI for the contribution.
      //! \sa Contribution()
      //*******************************************************************************************
      const Trentino::Utils::URI& baseURI() const;

      //*******************************************************************************************
      //                                      composites()
      //*******************************************************************************************
      //! \brief Returns a collection of composites contained in the contribution.
      //!
      //! The returned collection contains \all the c that are part of the contribution
      //! (and not only the deployable composites).
      //! \return A const reference to the collection of composites contained in the contribution.
      //*******************************************************************************************
      const Composites& composites() const;

      //*******************************************************************************************
      //                                      addComposite()
      //*******************************************************************************************
      //! \brief Adds a composite to the contribution.
      //!
      //! \param[in] composite A shared pointer to the composite to add.
      //! \sa composites(), removeComposite(), disposeComposites()
      //*******************************************************************************************
      void addComposite(const CompositePtr& composite);

      //*******************************************************************************************
      //                                      removeComposite()
      //*******************************************************************************************
      //! \brief Removes the given composite from the contribution. 
      //!
      //! In case the given composite isn't contained in the contribution the method has no effect.
      //! \param[in] composite A shared pointer to the composite to be removed.
      //! \sa composites(), addComposite(), disposeComposites()
      //*******************************************************************************************
      void removeComposite(const ConstCompositePtr& composite);

      //*******************************************************************************************
      //                                      disposeComposites()
      //*******************************************************************************************
      //! \brief Removes and destroys all the composites contained in the contribution. 
      //! \sa composites(), addComposite(), removeComposite()
      //*******************************************************************************************
      void disposeComposites();

      //*******************************************************************************************
      //                                      setContributionLibrary()
      //*******************************************************************************************
      //! \brief Sets the associated contribution library
      //!
      //! \param[in] Library associated with the contribution.
      //*******************************************************************************************
      void setContributionLibrary(const Trentino::Utils::DynamicLibraryPtr& lib);

      //*******************************************************************************************
      //                                      setBusinessLibraries()
      //*******************************************************************************************
      //! \brief Sets all business libraries
      //!
      //! \param[in] Libraries to set in contribution.
      //*******************************************************************************************
      void setBusinessLibraries(const std::vector<Trentino::Utils::DynamicLibraryPtr>& libraries);

      //*******************************************************************************************
      //                                           state()
      //*******************************************************************************************
      //! \brief Returns the contribution's state.
      //! \return The contribution's state.
      //! \sa setState()
      //*******************************************************************************************
      State state() const;

      //*******************************************************************************************
      //                                         setState()
      //*******************************************************************************************
      //! \brief Sets the contribution's state.
      //! \param[in] The state to set. 
      //! \sa state()
      //*******************************************************************************************
      void setState(State state);

      //****************************************************************************************************
      //                                         setContributionInfo()
      //****************************************************************************************************
      //! \brief set the contribution info used to create this contribution
      //! \param boost::shared_ptr<Trentino::Core::TrentinoContributionInfo> contributionInfo
      //! \return void
      //****************************************************************************************************
      void setContributionInfo(const boost::shared_ptr<Trentino::Core::TrentinoContributionInfo>& contributionInfo );
      //****************************************************************************************************
      //                                         contributionInfo()
      //****************************************************************************************************
      //! \brief get the contribution info
      //! \return boost::shared_ptr<Trentino::Core::TrentinoContributionInfo>
      //****************************************************************************************************
      boost::shared_ptr<Trentino::Core::TrentinoContributionInfo> contributionInfo() const;

      //*******************************************************************************************
      //                                         localPath()
      //*******************************************************************************************
      //! \brief Returns the absolute path to the contribution's root directory.
      //! \return Absolute path to the contribution's root directory on the local machine. 
      //! \sa setLocalPath()
      //*******************************************************************************************
      const std::string& localPath() const;

      //*******************************************************************************************
      //                                        setLocalPath()
      //*******************************************************************************************
      //! \brief Sets the contribution's local path.
      //! \param[in] localPath Path to the contribution's root directory on the local machine. A
      //!            relative path will be converted to an absolute one.     
      //! \sa localPath()
      //*******************************************************************************************
      void setLocalPath(const std::string& localPath);
      

      //****************************************************************************************************
      //                                         visit()
      //****************************************************************************************************
      //! \brief visit this contribution
      //! \param VisitorPtr & visitor
      //! \return void
      //****************************************************************************************************
      bool visit(VisitorPtr& visitor);


      //****************************************************************************************************
      //                                         version()
      //****************************************************************************************************
      //! \brief get the version of the contribution
      //! \return version
      //****************************************************************************************************
      const std::string & version() const;

      //****************************************************************************************************
      //                                         setVersion()
      //****************************************************************************************************
      //! \brief set the version of the contribution
      //! \param[in] version of the contribution
      //! \return void
      //****************************************************************************************************
      void setVersion(std::string& nVersion);

      //management
   private:
      //data
   private:      
      //! ModelDescriptor representing the contribution's sca model
      Trentino::SCA::Model::ModelDescriptorPtr mSCAModelDescriptor;                                               
      //! the base URI for the contribution 
      const Trentino::Utils::URI mBaseURI;       
      //! collection of all the composites contained in the contribution
      Composites mComposites;
      //! dynamic library containing all the generated code for the contribution      
      Trentino::Utils::DynamicLibraryPtr mContributionLibrary;
      //! Loaded business logic libraries
      std::vector<Trentino::Utils::DynamicLibraryPtr> mBusinessLibraries;
      //! the contribution's state 
      State mState;
      //! absolute path to the contribution's root directory on the local machine
      std::string mLocalPath;

      //! the contribution info used to create this contribution
      Trentino::Core::TrentinoContributionInfoPtr mContributionInfo;
      std::string mVersion;
      
   }; //class Contribution

   #include "TrentinoRuntimeModelContribution.inl"
} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelContributionH

