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

//header
#include "TrentinoRuntimeModelReference.h"

//specific
#include "../SCAModel/TrentinoSCAModel.h"
#include "../SCAModel/TrentinoSCAModelMetadata.h"
#include "../SCAModel/TrentinoSCAModelMetadataStringAttribute.h"
#include "TrentinoRuntimeModelComponent.h"
#include "TrentinoRuntimeModelWire.h"
#include "../SCAModel/TrentinoSCAModelComponentTypeReference.h"
#include "../ReflectionRuntime/TrentinoReflectionReflectMethod.h"
#include "../ReflectionRuntime/TrentinoReflectionHelpersListWrapper.h"

using namespace std;
using Trentino::RuntimeModel::Reference;
namespace RuntimeModel = Trentino::RuntimeModel;

namespace
   {
   std::vector<std::string> gEmptyStringVector;
   }

//class Reference
//construction
Reference::Reference( const Trentino::SCA::Model::ComponentTypeReferencePtr& scaReferenceType                    
                    , const RuntimeModel::ComponentPtr& component)
: mSCAReferenceType(scaReferenceType)
, mComponent(component)
, mState(ReferenceBase::Initial)
{
   // Metadata shall be joined from both scaReference and scaReferenceType
   mMetaData.reset(new Trentino::SCA::Model::Metadata);
   // Copy metadata from ReferenceType first, since only it is available at construction
   if(mSCAReferenceType.get() != nullptr )
   {
      if(mSCAReferenceType->metadataElement() != nullptr)
      {
         for(size_t i = 0; i < mSCAReferenceType->metadataElement()->stringAttributesElements().size(); i++)
         {
            Trentino::SCA::Model::MetadataStringAttribute *attr = new Trentino::SCA::Model::MetadataStringAttribute();
            attr->setName(mSCAReferenceType->metadataElement()->stringAttributesElements()[i]->name().c_str());
            attr->setValue(mSCAReferenceType->metadataElement()->stringAttributesElements()[i]->value().c_str());
            mMetaData->addStringAttributesElement(attr);
         }
      }
   }
}

//services
Trentino::SCA::Model::ComponentTypeReferencePtr Reference::scaReferenceType() const
   {
   return mSCAReferenceType;
   }

Trentino::SCA::Model::ComponentReferencePtr Reference::scaReference() const
   {
   return mSCAReference; 
   }

void Reference::setSCAReference(const Trentino::SCA::Model::ComponentReferencePtr& scaReference)
   {
   mSCAReference = scaReference;

   // Now merge the metadata
   // then goes metadata from ServiceType, but only those attributes not overridden in Service
   if (mSCAReference.get() != nullptr)
   {
      if(mSCAReference->metadataElement() != nullptr)
      {
         for(size_t i = 0; i < mSCAReference->metadataElement()->stringAttributesElements().size(); i++)
          {
             bool already_exist = false;
             Trentino::SCA::Model::MetadataStringAttributePtr found_attribute;
             for(size_t j = 0; j < mMetaData->stringAttributesElements().size(); j++)
             {
                if(mMetaData->stringAttributesElements()[j]->name() ==
                      mSCAReference->metadataElement()->stringAttributesElements()[i]->name())
                {
                   already_exist = true;
                   found_attribute = mMetaData->stringAttributesElements()[j];
                   break;
                }
             }
             if(! already_exist)
             {
                Trentino::SCA::Model::MetadataStringAttribute *attr = new Trentino::SCA::Model::MetadataStringAttribute();
                attr->setName(mSCAReference->metadataElement()->stringAttributesElements()[i]->name().c_str());
                attr->setValue(mSCAReference->metadataElement()->stringAttributesElements()[i]->value().c_str());
                mMetaData->addStringAttributesElement(attr);
             }
             else
             {
                found_attribute->setValue(mSCAReference->metadataElement()->stringAttributesElements()[i]->value().c_str());
             }
          }
       }
   }
} 

Trentino::RuntimeModel::ComponentWeakPtr Trentino::RuntimeModel::Reference::component() const
   {
   return mComponent;
   }

Reference::State Reference::state() const
   {
   return mState;
   }  

void Reference::setState(Reference::State state)
   {
   mState = state;
   }


const std::vector<std::string>& Reference::targets() const
   {
   if(mSCAReference)
      {
      return mSCAReference->targets();
      }
   if(mSCAReferenceType)
      {
      return mSCAReferenceType->targets();
      }

   return gEmptyStringVector;
   }


const std::string Reference::multiplicity() const
   {
   if(mSCAReference)
      {
      const std::string& res = mSCAReference->multiplicity();
      if(res != "")
         {
         //Multiplicity is set in SCAReference, then use it
         return res;
         }
      }
   if(mSCAReferenceType)
      {
      const std::string& res = mSCAReferenceType->multiplicity();
      if(res != "")
         {
         //Multiplicity is set in mSCAReferenceType, then use it
         return res;
         }
      }

   //No multiplicity set. return the default value that is one to one
   return Trentino::SCA::Model::ReferenceMultiplicity1to1;
   }


const Trentino::SCA::Model::InterfacePtr Reference::interfaceElement() const
   {
      if(mSCAReference)
      {
       return mSCAReference->interfaceElement();
      }

       return mSCAReferenceType->interfaceElement();
   }


const bool Reference::isNonOverridable() const
   {
         if(mSCAReference)
      {
       return mSCAReference->isNonOverridable();
      }

       return mSCAReferenceType->isNonOverridable();
   }

void Reference::setSetterMethod(const Trentino::Reflection::ReflectMethodPtr& setter)
   {
   mSetter = setter;
   }

void Reference::invokeSetter(void* instance, void* value) const
   {
   if(mSetter)
      {
      void* setterParams[] = {&value};
      try
         {
         mSetter->invoke(instance, setterParams);
         }
      catch(...)
         {
         throw;
         }
      }
   }

void Reference::invokeSetter(void* instance, const Reference::VoidPtrList& valueList) const
   {
   const Trentino::Reflection::Helpers::ListWrapper<VoidPtrList> listWrapper(valueList);
   invokeSetter(instance, listWrapper.listType().get());   
   }

Trentino::Reflection::ReflectObjectPtr Reference::proxyReflectObject() const
   {
   return mProxyReflectObject;
   }

void Reference::setProxyReflectObject(
   const Trentino::Reflection::ReflectObjectPtr& proxyReflectObject)
   {
   mProxyReflectObject = proxyReflectObject;
   }

const RuntimeModel::WeakReferenceBases& Reference::promotedTo() const
   {
   return mPromotedTo;
   }

void Reference::addPromotedTo(const RuntimeModel::ReferenceBasePtr& reference)
   {
   mPromotedTo.push_back(reference);
   }

const RuntimeModel::WeakReferenceBases& Reference::promotedBy() const
   {
   return mPromotedBy;
   }

void Reference::addPromotedBy(const RuntimeModel::ReferenceBasePtr& reference)
   {
   mPromotedBy.push_back(reference);
   }

RuntimeModel::Wireable& Reference::wireableSupport()
   {
   return const_cast<Reference*>(this)->mWireableSupport;
   }

const RuntimeModel::Wireable& Reference::wireableSupport() const
   {
   return mWireableSupport;
   }

const Trentino::XML::Schema::NCName& Trentino::RuntimeModel::Reference::name() const
   {
   const Trentino::SCA::Model::ComponentTypeReferencePtr& referenceObj = mSCAReferenceType;
   return referenceObj->name();
   }

const Trentino::RuntimeModel::ServiceBases Trentino::RuntimeModel::Reference::getTargetServices() const
   {
   Trentino::RuntimeModel::ServiceBases result;
   Trentino::RuntimeModel::WireBases::const_iterator wiresIterator;
   Trentino::RuntimeModel::WireBases wires = mWireableSupport.wires();
   for(wiresIterator = wires.begin(); wiresIterator != wires.end(); ++wiresIterator)
      {
      const ConstWireBasePtr wire = *wiresIterator;      
      if(wire && wire->originalService().lock())
         result.push_back(wire->originalService().lock());     
      }
   return result;
   }

Trentino::SCA::Model::MetadataPtr Trentino::RuntimeModel::Reference::metadataElement() const
   {
   if(mSCAReference)
      {
      return mSCAReference->metadataElement();
      }

   return mSCAReferenceType->metadataElement();
   }
const Trentino::SCA::Model::MetadataPtr Trentino::RuntimeModel::Reference::metaData() const
{
   return mMetaData;
}






