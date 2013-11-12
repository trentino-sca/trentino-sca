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

#ifndef TrentinoSCAModelModelDescriptorH
#define TrentinoSCAModelModelDescriptorH

//specific
#include "TrentinoSCAModel.h"

namespace Trentino{
namespace Core {
namespace ContributionLoading {
   class SCAModelLoader;
} //namespace ContributionLoading
} //namespace Core
} //namespace Trentino

namespace Trentino{
namespace SCA{
namespace Model
{
   class Component;

   //**********************************************************************************************
   //                                        ModelDescriptor
   //**********************************************************************************************
   //! \brief Aggregates the necessary information to access all the SCAModel parts.
   //!
   //! An instance of ModelDescriptor may be considered as a root of a loaded SCAModel object tree.
   //! A ModelDescriptor enables the client to access all the objects contained in the model. 
   //! The purpose of ModelDescriptor's interface is to allow access to those parts of the model
   //! that are not directly referenced by its other parts. 
   //!
   //! It is, for example, not necessary to maintain a list of all the components since Component 
   //! instances are referenced by their corresponding parent composites. On the other hand,
   //! ModelDescriptor offers access to all the composites contained within a contribution because
   //! the ContributionType class doesn't reference these composites directly.
   //!
   //! \attention ModelDescriptor offers only getter methods because it is supposed to be populated
   //!            by the Trentino::Core::ContributionLoading::SCAModelLoader friend class. 
   //**********************************************************************************************
   class ModelDescriptor
   {
      friend class Trentino::Core::ContributionLoading::SCAModelLoader;

      //services
   public:
      //*******************************************************************************************
      //                                        contribution()
      //*******************************************************************************************
      //! \brief Returns the ContributionType representing the model.
      //! \return A shared pointer to the ContributionType representing the model.    
      //*******************************************************************************************
      ContributionTypePtr contribution() const;

      //*******************************************************************************************
      //                                      findCompositeByQName()
      //*******************************************************************************************
      //! \brief Searches for a composite with the given QName.
      //! \param[in] Composite's QName to search for. 
      //! \return A shared pointer to the found Composite or an empty shared pointer in case a 
      //!         composite with the given QName couldn't be found in the model.  
      //! \attention In case there is more than one composite with the same QName, which one is
      //!            returned, is undefined.   
      //*******************************************************************************************
      SCAMODEL_IMPORT_EXPORT CompositePtr findCompositeByQName(
         const Trentino::XML::Schema::QName& qName) const;      

      //*******************************************************************************************
      //                                        findComponentType()
      //*******************************************************************************************
      //! \brief Returns the componentType associated with the given component.
      //! \param[in] component A shared pointer to the component for which the componentType is to 
      //!            be retrieved. 
      //! \return A shared pointer to the componentType associated with the given component or an
      //!         empty shared pointer if the componentType couldn't be found. 
      //! \sa addComponentType()
      //*******************************************************************************************
      SCAMODEL_IMPORT_EXPORT ComponentTypePtr findComponentType(
         const ComponentPtr& component) const;

      //*******************************************************************************************
      //                                         composites()
      //*******************************************************************************************
      //! \brief get all the composites inside this contribution
      //! \return SCAMODEL_IMPORT_EXPORT Composites
      //*******************************************************************************************
      SCAMODEL_IMPORT_EXPORT Composites composites() const;

      //data
   private:
      //! Shared pointer to the contribution
      ContributionTypePtr mContribution;
      //! Associates components and their corresponding component types
      ComponentTypeMap mComponentTypeMap;
      //! Collection of all the composites contained in the contribution
      Composites mComposites;
   
   }; //class ModelDescriptor

   //services
   inline ContributionTypePtr ModelDescriptor::contribution() const
   {
      return mContribution;
   }

} //namespace Model
} //namespace SCA
} //namespace Trentino

#endif //TrentinoSCAModelModelDescriptorH