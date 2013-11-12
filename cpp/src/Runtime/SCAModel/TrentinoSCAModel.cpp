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
#include <cassert>
#include <utility>
#include <stdexcept>

//header
#include "TrentinoSCAModelAppliesTo.h"
#include "TrentinoSCAModelAttributedQNameType.h"
#include "TrentinoSCAModelAttributedURIType.h"
#include "TrentinoSCAModelAttributedUnsignedLongType.h"
#include "TrentinoSCAModelBinding.h"
#include "TrentinoSCAModelBindingType.h"
#include "TrentinoSCAModelCPPExport.h"
#include "TrentinoSCAModelCPPFunction.h"
#include "TrentinoSCAModelCPPImplementation.h"
#include "TrentinoSCAModelCPPImplementationFunction.h"
#include "TrentinoSCAModelCPPImplementationScope.h"
#include "TrentinoSCAModelCPPImport.h"
#include "TrentinoSCAModelCPPInterface.h"
#include "TrentinoSCAModelCallback.h"
#include "TrentinoSCAModelCommonExtensionBase.h"
#include "TrentinoSCAModelComponent.h"
#include "TrentinoSCAModelComponentReference.h"
#include "TrentinoSCAModelComponentService.h"
#include "TrentinoSCAModelComponentType.h"
#include "TrentinoSCAModelComponentTypeReference.h"
#include "TrentinoSCAModelComposite.h"
#include "TrentinoSCAModelContract.h"
#include "TrentinoSCAModelContributionType.h"
#include "TrentinoSCAModelCreateResource.h"
#include "TrentinoSCAModelDeployableType.h"
#include "TrentinoSCAModelDocumentation.h"
#include "TrentinoSCAModelEndpointReferenceType.h"
#include "TrentinoSCAModelExport.h"
#include "TrentinoSCAModelExportType.h"
#include "TrentinoSCAModelExtensions.h"
#include "TrentinoSCAModelExternalAttachment.h"
#include "TrentinoSCAModelIPCBinding.h"
#include "TrentinoSCAModelImplementation.h"
#include "TrentinoSCAModelImplementationType.h"
#include "TrentinoSCAModelImport.h"
#include "TrentinoSCAModelImportType.h"
#include "TrentinoSCAModelInclude.h"
#include "TrentinoSCAModelIntent.h"
#include "TrentinoSCAModelIntentMap.h"
#include "TrentinoSCAModelIntentQualifier.h"
#include "TrentinoSCAModelInteractionOrImplementation.h"
#include "TrentinoSCAModelInterface.h"
#include "TrentinoSCAModelMetadata.h"
#include "TrentinoSCAModelMetadataStringAttribute.h"
#include "TrentinoSCAModelMetadataType.h"
#include "TrentinoSCAModelObject.h"
#include "TrentinoSCAModelOperationSelectorType.h"
#include "TrentinoSCAModelOperatorContentType.h"
#include "TrentinoSCAModelOverrideOptions.h"
#include "TrentinoSCAModelPolicy.h"
#include "TrentinoSCAModelPolicyAttachment.h"
#include "TrentinoSCAModelPolicyReference.h"
#include "TrentinoSCAModelPolicySet.h"
#include "TrentinoSCAModelPolicySetAttachment.h"
#include "TrentinoSCAModelPolicySetReference.h"
#include "TrentinoSCAModelProblemActionType.h"
#include "TrentinoSCAModelProperty.h"
#include "TrentinoSCAModelPropertyValue.h"
#include "TrentinoSCAModelQualifier.h"
#include "TrentinoSCAModelReference.h"
#include "TrentinoSCAModelReferenceParametersType.h"
#include "TrentinoSCAModelRelatesToType.h"
#include "TrentinoSCAModelRequires.h"
#include "TrentinoSCAModelSCABinding.h"
#include "TrentinoSCAModelSCAImplementation.h"
#include "TrentinoSCAModelSCAPropertyBase.h"
#include "TrentinoSCAModelService.h"
#include "TrentinoSCAModelTDefinitions.h"
#include "TrentinoSCAModelURI.h"
#include "TrentinoSCAModelValueType.h"
#include "TrentinoSCAModelWSCallback.h"
#include "TrentinoSCAModelWire.h"
#include "TrentinoSCAModelWireFormatType.h"

using namespace Trentino::SCA::Model;
using Trentino::XML::Schema::QName;
using namespace std;

//!brief deleter for class IPCBinding
void deleterIPCBinding(Binding* aBinding)
{
   IPCBinding* const myIPCBinding = static_cast<IPCBinding*>(aBinding);
   delete myIPCBinding;
}

//!brief deleter for class SCABinding
void deleterSCABinding(Binding* aBinding)
{
   SCABinding* const mySCABinding = static_cast<SCABinding*>(aBinding);
   delete mySCABinding;
}


//!brief deleter for class SCAImplementation
void deleterSCAImplementation(Implementation* aImplementation)
{
   SCAImplementation* const mySCAImplementation = static_cast<SCAImplementation*>(aImplementation);
   delete mySCAImplementation;
}

//!brief deleter for class CPPImplementation
void deleterCPPImplementation(Implementation* aImplementation)
{
   CPPImplementation* const myCPPImplementation = static_cast<CPPImplementation*>(aImplementation);
   delete myCPPImplementation;
}


//!brief deleter for class ImportType
void deleterImportType(Import* aImport)
{
   ImportType* const myImportType = static_cast<ImportType*>(aImport);
   delete myImportType;
}

//!brief deleter for class CPPImport
void deleterCPPImport(Import* aImport)
{
   CPPImport* const myCPPImport = static_cast<CPPImport*>(aImport);
   delete myCPPImport;
}


//!brief deleter for class CPPInterface
void deleterCPPInterface(Interface* aInterface)
{
   CPPInterface* const myCPPInterface = static_cast<CPPInterface*>(aInterface);
   delete myCPPInterface;
}



//Class implementation
//************************************************************************************************************
//                                    AppliesTo
//************************************************************************************************************
   //construction
AppliesTo::AppliesTo()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  AppliesTo::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }




//Class implementation
//************************************************************************************************************
//                                    AttributedQNameType
//************************************************************************************************************
   //construction
AttributedQNameType::AttributedQNameType()
      {
      }

   //services

      //element accessors  
	 void TRENTINO_STDCALL  AttributedQNameType::setValue(Trentino::XML::Schema::QName* aValue){
		   mValueElement =QNamePtr(aValue);
		}




//Class implementation
//************************************************************************************************************
//                                    AttributedURIType
//************************************************************************************************************
   //construction
AttributedURIType::AttributedURIType()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  AttributedURIType::setValue(const char* aValue){
            mValueElement = aValue;
       }
       




//Class implementation
//************************************************************************************************************
//                                    AttributedUnsignedLongType
//************************************************************************************************************
   //construction
AttributedUnsignedLongType::AttributedUnsignedLongType()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  AttributedUnsignedLongType::setValue(int64_t aValue){
        mValueElement = aValue;
      } 




//Class implementation
//************************************************************************************************************
//                                    Binding
//************************************************************************************************************
   //construction
Binding::Binding()
      {
	       mXSDType.reset(new QName("Binding", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
      }

   //services

      //element accessors  
     void  TRENTINO_STDCALL  Binding::setOperationSelector(OperationSelectorType* aOperationSelector){
          mOperationSelectorElement = OperationSelectorTypePtr(aOperationSelector);
       }

       void TRENTINO_STDCALL  Binding::addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment){
         mPolicySetAttachmentElements.push_back(PolicySetAttachmentPtr(aPolicySetAttachment));
       }

       void TRENTINO_STDCALL  Binding::addScaRequiresElement(Requires* aScaRequires){
         mScaRequiresElements.push_back(RequiresPtr(aScaRequires));
       }

     void  TRENTINO_STDCALL  Binding::setWireFormat(WireFormatType* aWireFormat){
          mWireFormatElement = WireFormatTypePtr(aWireFormat);
       }


      //attribute accessors
       void TRENTINO_STDCALL  Binding::setName(const char* aName){
            mName = aName;
       }
       

       void TRENTINO_STDCALL  Binding::addPolicySets(Trentino::XML::Schema::QName* aPolicySets){
         mPolicySets.push_back(QNamePtr(aPolicySets));
       }

       void TRENTINO_STDCALL  Binding::addRequires(Trentino::XML::Schema::QName* aRequires){
         mRequires.push_back(QNamePtr(aRequires));
       }

       void TRENTINO_STDCALL  Binding::setUri(const char* aUri){
            mUri = aUri;
       }
       



//Class implementation
//************************************************************************************************************
//                                    BindingType
//************************************************************************************************************
   //construction
BindingType::BindingType()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  BindingType::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
       void TRENTINO_STDCALL  BindingType::addAlwaysProvides(Trentino::XML::Schema::QName* aAlwaysProvides){
         mAlwaysProvides.push_back(QNamePtr(aAlwaysProvides));
       }

       void TRENTINO_STDCALL  BindingType::addMayProvide(Trentino::XML::Schema::QName* aMayProvide){
         mMayProvides.push_back(QNamePtr(aMayProvide));
       }

	 void TRENTINO_STDCALL  BindingType::setType(Trentino::XML::Schema::QName* aType){
		   mType =QNamePtr(aType);
		}



//Class implementation
//************************************************************************************************************
//                                    CPPExport
//************************************************************************************************************
   //construction
CPPExport::CPPExport()
      {
      }

   //services


      //attribute accessors
	 void TRENTINO_STDCALL  CPPExport::setName(Trentino::XML::Schema::QName* aName){
		   mName =QNamePtr(aName);
		}

       void TRENTINO_STDCALL  CPPExport::setPath(const char* aPath){
         mPath = aPath;
      }
      

       void TRENTINO_STDCALL  CPPExport::setVersion(const char* aVersion){
         mVersion = aVersion;
      }
      



//Class implementation
//************************************************************************************************************
//                                    CPPFunction
//************************************************************************************************************
   //construction
CPPFunction::CPPFunction()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  CPPFunction::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }

       void TRENTINO_STDCALL  CPPFunction::addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment){
         mPolicySetAttachmentElements.push_back(PolicySetAttachmentPtr(aPolicySetAttachment));
       }

       void TRENTINO_STDCALL  CPPFunction::addRequiresElement(Requires* aRequires){
         mRequiresElements.push_back(RequiresPtr(aRequires));
       }


      //attribute accessors
       void TRENTINO_STDCALL  CPPFunction::setExclude(bool isExclude){
         mIsExclude = isExclude;
      }
      

       void TRENTINO_STDCALL  CPPFunction::setName(const char* aName){
            mName = aName;
       }
       

       void TRENTINO_STDCALL  CPPFunction::setOneWay(bool isOneWay){
         mIsOneWay = isOneWay;
      }
      

       void TRENTINO_STDCALL  CPPFunction::addPolicySets(Trentino::XML::Schema::QName* aPolicySets){
         mPolicySets.push_back(QNamePtr(aPolicySets));
       }



//Class implementation
//************************************************************************************************************
//                                    CPPImplementation
//************************************************************************************************************
   //construction
CPPImplementation::CPPImplementation()
      {
	       mXSDType.reset(new QName("CPPImplementation", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  CPPImplementation::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }

       void TRENTINO_STDCALL  CPPImplementation::addFunctionElement(CPPImplementationFunction* aFunction){
         mFunctionElements.push_back(CPPImplementationFunctionPtr(aFunction));
       }


      //attribute accessors
       void TRENTINO_STDCALL  CPPImplementation::setAllowsPassByReference(bool isAllowsPassByReference){
         mIsAllowsPassByReference = isAllowsPassByReference;
      }
      

       void TRENTINO_STDCALL  CPPImplementation::setClazz(const char* aClazz){
            mClazz = aClazz;
       }
       

       void TRENTINO_STDCALL  CPPImplementation::setComponentType(const char* aComponentType){
         mComponentType = aComponentType;
      }
      

       void TRENTINO_STDCALL  CPPImplementation::setEagerInit(bool isEagerInit){
         mIsEagerInit = isEagerInit;
      }
      

       void TRENTINO_STDCALL  CPPImplementation::setHeader(const char* aHeader){
         mHeader = aHeader;
      }
      

       void TRENTINO_STDCALL  CPPImplementation::setLibrary(const char* aLibrary){
            mLibrary = aLibrary;
       }
       

       void TRENTINO_STDCALL  CPPImplementation::setPath(const char* aPath){
         mPath = aPath;
      }
      

     void  TRENTINO_STDCALL  CPPImplementation::setScope(CPPImplementationScope* aScope){
          mScope = CPPImplementationScopePtr(aScope);
       }



//Class implementation
//************************************************************************************************************
//                                    CPPImplementationFunction
//************************************************************************************************************
   //construction
CPPImplementationFunction::CPPImplementationFunction()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  CPPImplementationFunction::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }

       void TRENTINO_STDCALL  CPPImplementationFunction::addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment){
         mPolicySetAttachmentElements.push_back(PolicySetAttachmentPtr(aPolicySetAttachment));
       }

       void TRENTINO_STDCALL  CPPImplementationFunction::addRequiresElement(Requires* aRequires){
         mRequiresElements.push_back(RequiresPtr(aRequires));
       }


      //attribute accessors
       void TRENTINO_STDCALL  CPPImplementationFunction::setAllowsPassByReference(bool isAllowsPassByReference){
         mIsAllowsPassByReference = isAllowsPassByReference;
      }
      

       void TRENTINO_STDCALL  CPPImplementationFunction::setDestroy(bool isDestroy){
         mIsDestroy = isDestroy;
      }
      

       void TRENTINO_STDCALL  CPPImplementationFunction::setInit(bool isInit){
         mIsInit = isInit;
      }
      

       void TRENTINO_STDCALL  CPPImplementationFunction::setName(const char* aName){
            mName = aName;
       }
       

       void TRENTINO_STDCALL  CPPImplementationFunction::addPolicySets(Trentino::XML::Schema::QName* aPolicySets){
         mPolicySets.push_back(QNamePtr(aPolicySets));
       }



//Class implementation
//************************************************************************************************************
//                                    CPPImplementationScope
//************************************************************************************************************
	//static member initialization
	CPPImplementationScope::ValueMap CPPImplementationScope::mValueMap = CPPImplementationScope::createValueMap();

  
   //construction
	CPPImplementationScope::CPPImplementationScope(const string& valueStr): mValue(mValueMap[valueStr]){}

    //services
	string CPPImplementationScope::toString() const
	{   
	   for( ValueMap::const_iterator it = mValueMap.begin();
	        it != mValueMap.end(); ++it)
		   {
		      if(it->second == mValue)
		         return it->first;
		   }
	
	      assert(false);
	      return "";
	 }

     //management
	 CPPImplementationScope::ValueMap CPPImplementationScope::createValueMap()
	 {
		   ValueMap valueMap;
		   valueMap.insert(make_pair("composite", Composite));
		   valueMap.insert(make_pair("stateless", Stateless));
		   return valueMap;
	  }


//Class implementation
//************************************************************************************************************
//                                    CPPImport
//************************************************************************************************************
   //construction
CPPImport::CPPImport()
      {
	       mXSDType.reset(new QName("CPPImport", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
      }

   //services


      //attribute accessors
       void TRENTINO_STDCALL  CPPImport::setLocation(const char* aLocation){
         mLocation = aLocation;
      }
      

	 void TRENTINO_STDCALL  CPPImport::setName(Trentino::XML::Schema::QName* aName){
		   mName =QNamePtr(aName);
		}

       void TRENTINO_STDCALL  CPPImport::setVersion(const char* aVersion){
         mVersion = aVersion;
      }
      



//Class implementation
//************************************************************************************************************
//                                    CPPInterface
//************************************************************************************************************
   //construction
CPPInterface::CPPInterface()
      {
	       mXSDType.reset(new QName("CPPInterface", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  CPPInterface::addCallbackFunctionElement(CPPFunction* aCallbackFunction){
         mCallbackFunctionElements.push_back(CPPFunctionPtr(aCallbackFunction));
       }

       void TRENTINO_STDCALL  CPPInterface::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }

       void TRENTINO_STDCALL  CPPInterface::addFunctionElement(CPPFunction* aFunction){
         mFunctionElements.push_back(CPPFunctionPtr(aFunction));
       }


      //attribute accessors
       void TRENTINO_STDCALL  CPPInterface::setCallbackClass(const char* aCallbackClass){
            mCallbackClass = aCallbackClass;
       }
       

       void TRENTINO_STDCALL  CPPInterface::setCallbackHeader(const char* aCallbackHeader){
         mCallbackHeader = aCallbackHeader;
      }
      

       void TRENTINO_STDCALL  CPPInterface::setClazz(const char* aClazz){
            mClazz = aClazz;
       }
       

       void TRENTINO_STDCALL  CPPInterface::setHeader(const char* aHeader){
         mHeader = aHeader;
      }
      



//Class implementation
//************************************************************************************************************
//                                    Callback
//************************************************************************************************************
   //construction
Callback::Callback()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Callback::addBindingElement(Binding* aBinding){
         mBindingElements.push_back(BindingPtr(aBinding));
       }

       void TRENTINO_STDCALL  Callback::addExtensionsElement(Extensions* aExtensions){
         mExtensionsElements.push_back(ExtensionsPtr(aExtensions));
       }

       void TRENTINO_STDCALL  Callback::addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment){
         mPolicySetAttachmentElements.push_back(PolicySetAttachmentPtr(aPolicySetAttachment));
       }

       void TRENTINO_STDCALL  Callback::addRequiresElement(Requires* aRequires){
         mRequiresElements.push_back(RequiresPtr(aRequires));
       }


      //attribute accessors
       void TRENTINO_STDCALL  Callback::addPolicySets(Trentino::XML::Schema::QName* aPolicySets){
         mPolicySets.push_back(QNamePtr(aPolicySets));
       }



//Class implementation
//************************************************************************************************************
//                                    CommonExtensionBase
//************************************************************************************************************
   //construction
CommonExtensionBase::CommonExtensionBase()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  CommonExtensionBase::addDocumentationElement(Documentation* aDocumentation){
         mDocumentationElements.push_back(DocumentationPtr(aDocumentation));
       }




//Class implementation
//************************************************************************************************************
//                                    Component
//************************************************************************************************************
   //construction
Component::Component()
      {
      }

   //services

      //element accessors  
     void  TRENTINO_STDCALL  Component::setExtensions(Extensions* aExtensions){
          mExtensionsElement = ExtensionsPtr(aExtensions);
       }

     void  TRENTINO_STDCALL  Component::setImplementation(Implementation* aImplementation){
       if(aImplementation->xsdType().localPart() == "SCAImplementation")
       {
          mImplementationElement = ImplementationPtr(aImplementation,deleterSCAImplementation);
          return;
       }	
       if(aImplementation->xsdType().localPart() == "CPPImplementation")
       {
          mImplementationElement = ImplementationPtr(aImplementation,deleterCPPImplementation);
          return;
       }	
        throw std::runtime_error("unknown type of implementation!");
       }

       void TRENTINO_STDCALL  Component::addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment){
         mPolicySetAttachmentElements.push_back(PolicySetAttachmentPtr(aPolicySetAttachment));
       }

       void TRENTINO_STDCALL  Component::addPropertyElement(PropertyValue* aProperty){
         mPropertyElements.push_back(PropertyValuePtr(aProperty));
       }

       void TRENTINO_STDCALL  Component::addReferenceElement(ComponentReference* aReference){
         mReferenceElements.push_back(ComponentReferencePtr(aReference));
       }

       void TRENTINO_STDCALL  Component::addRequiresElement(Requires* aRequires){
         mRequiresElements.push_back(RequiresPtr(aRequires));
       }

       void TRENTINO_STDCALL  Component::addServiceElement(ComponentService* aService){
         mServiceElements.push_back(ComponentServicePtr(aService));
       }


      //attribute accessors
       void TRENTINO_STDCALL  Component::setAutowire(bool isAutowire){
         mIsAutowire = isAutowire;
      }
      

       void TRENTINO_STDCALL  Component::setName(const char* aName){
            mName = aName;
       }
       

       void TRENTINO_STDCALL  Component::addPolicySets(Trentino::XML::Schema::QName* aPolicySets){
         mPolicySets.push_back(QNamePtr(aPolicySets));
       }



//Class implementation
//************************************************************************************************************
//                                    ComponentReference
//************************************************************************************************************
   //construction
ComponentReference::ComponentReference()
      {
      }

   //services


      //attribute accessors
       void TRENTINO_STDCALL  ComponentReference::setAutowire(bool isAutowire){
         mIsAutowire = isAutowire;
      }
      

       void TRENTINO_STDCALL  ComponentReference::setMultiplicity(const char* aMultiplicity){
         mMultiplicity = aMultiplicity;
      }
      

       void TRENTINO_STDCALL  ComponentReference::setNonOverridable(bool isNonOverridable){
         mIsNonOverridable = isNonOverridable;
      }
      

       void TRENTINO_STDCALL  ComponentReference::addTarget(const char* aTarget){
           //std::vector<std::string> mTargets;
           mTargets.push_back(aTarget);
       }

       void TRENTINO_STDCALL  ComponentReference::setWiredByImpl(bool isWiredByImpl){
         mIsWiredByImpl = isWiredByImpl;
      }
      



//Class implementation
//************************************************************************************************************
//                                    ComponentService
//************************************************************************************************************
   //construction
ComponentService::ComponentService()
      {
      }

   //services


      //attribute accessors
       void TRENTINO_STDCALL  ComponentService::setRemote(bool isRemote){
         mIsRemote = isRemote;
      }
      



//Class implementation
//************************************************************************************************************
//                                    ComponentType
//************************************************************************************************************
   //construction
ComponentType::ComponentType()
      {
      }

   //services

      //element accessors  
     void  TRENTINO_STDCALL  ComponentType::setExtensions(Extensions* aExtensions){
          mExtensionsElement = ExtensionsPtr(aExtensions);
       }

     void  TRENTINO_STDCALL  ComponentType::setImplementation(Implementation* aImplementation){
       if(aImplementation->xsdType().localPart() == "SCAImplementation")
       {
          mImplementationElement = ImplementationPtr(aImplementation,deleterSCAImplementation);
          return;
       }	
       if(aImplementation->xsdType().localPart() == "CPPImplementation")
       {
          mImplementationElement = ImplementationPtr(aImplementation,deleterCPPImplementation);
          return;
       }	
        throw std::runtime_error("unknown type of implementation!");
       }

       void TRENTINO_STDCALL  ComponentType::addPropertyElement(Property* aProperty){
         mPropertyElements.push_back(PropertyPtr(aProperty));
       }

       void TRENTINO_STDCALL  ComponentType::addReferenceElement(ComponentTypeReference* aReference){
         mReferenceElements.push_back(ComponentTypeReferencePtr(aReference));
       }

       void TRENTINO_STDCALL  ComponentType::addServiceElement(ComponentService* aService){
         mServiceElements.push_back(ComponentServicePtr(aService));
       }




//Class implementation
//************************************************************************************************************
//                                    ComponentTypeReference
//************************************************************************************************************
   //construction
ComponentTypeReference::ComponentTypeReference()
      {
      }

   //services




//Class implementation
//************************************************************************************************************
//                                    Composite
//************************************************************************************************************
   //construction
Composite::Composite()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Composite::addComponentElement(Component* aComponent){
         mComponentElements.push_back(ComponentPtr(aComponent));
       }

       void TRENTINO_STDCALL  Composite::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }

       void TRENTINO_STDCALL  Composite::addIncludeElement(Include* aInclude){
         mIncludeElements.push_back(IncludePtr(aInclude));
       }

       void TRENTINO_STDCALL  Composite::addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment){
         mPolicySetAttachmentElements.push_back(PolicySetAttachmentPtr(aPolicySetAttachment));
       }

       void TRENTINO_STDCALL  Composite::addPropertyElement(Property* aProperty){
         mPropertyElements.push_back(PropertyPtr(aProperty));
       }

       void TRENTINO_STDCALL  Composite::addReferenceElement(Reference* aReference){
         mReferenceElements.push_back(ReferencePtr(aReference));
       }

       void TRENTINO_STDCALL  Composite::addRequiresElement(Requires* aRequires){
         mRequiresElements.push_back(RequiresPtr(aRequires));
       }

       void TRENTINO_STDCALL  Composite::addServiceElement(Service* aService){
         mServiceElements.push_back(ServicePtr(aService));
       }

       void TRENTINO_STDCALL  Composite::addWireElement(Wire* aWire){
         mWireElements.push_back(WirePtr(aWire));
       }


      //attribute accessors
       void TRENTINO_STDCALL  Composite::setAutowire(bool isAutowire){
         mIsAutowire = isAutowire;
      }
      

       void TRENTINO_STDCALL  Composite::setLocal(bool isLocal){
         mIsLocal = isLocal;
      }
      

       void TRENTINO_STDCALL  Composite::setName(const char* aName){
            mName = aName;
       }
       

       void TRENTINO_STDCALL  Composite::addPolicySets(Trentino::XML::Schema::QName* aPolicySets){
         mPolicySets.push_back(QNamePtr(aPolicySets));
       }

       void TRENTINO_STDCALL  Composite::setTargetNamespace(const char* aTargetNamespace){
            mTargetNamespace = aTargetNamespace;
       }
       



//Class implementation
//************************************************************************************************************
//                                    Contract
//************************************************************************************************************
   //construction
Contract::Contract()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Contract::addBindingElement(Binding* aBinding){
         mBindingElements.push_back(BindingPtr(aBinding));
       }

     void  TRENTINO_STDCALL  Contract::setCallback(Callback* aCallback){
          mCallbackElement = CallbackPtr(aCallback);
       }

     void  TRENTINO_STDCALL  Contract::setExtensions(Extensions* aExtensions){
          mExtensionsElement = ExtensionsPtr(aExtensions);
       }

     void  TRENTINO_STDCALL  Contract::setInterface(Interface* aInterface){
       if(aInterface->xsdType().localPart() == "CPPInterface")
       {
          mInterfaceElement = InterfacePtr(aInterface,deleterCPPInterface);
          return;
       }	
        throw std::runtime_error("unknown type of implementation!");
       }

     void  TRENTINO_STDCALL  Contract::setMetadata(Metadata* aMetadata){
          mMetadataElement = MetadataPtr(aMetadata);
       }

       void TRENTINO_STDCALL  Contract::addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment){
         mPolicySetAttachmentElements.push_back(PolicySetAttachmentPtr(aPolicySetAttachment));
       }

       void TRENTINO_STDCALL  Contract::addScaRequiresElement(Requires* aScaRequires){
         mScaRequiresElements.push_back(RequiresPtr(aScaRequires));
       }


      //attribute accessors
       void TRENTINO_STDCALL  Contract::setName(const char* aName){
            mName = aName;
       }
       

       void TRENTINO_STDCALL  Contract::addPolicySets(Trentino::XML::Schema::QName* aPolicySets){
         mPolicySets.push_back(QNamePtr(aPolicySets));
       }

       void TRENTINO_STDCALL  Contract::addRequires(Trentino::XML::Schema::QName* aRequires){
         mRequires.push_back(QNamePtr(aRequires));
       }



//Class implementation
//************************************************************************************************************
//                                    ContributionType
//************************************************************************************************************
   //construction
ContributionType::ContributionType()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  ContributionType::addDeployableElement(DeployableType* aDeployable){
         mDeployableElements.push_back(DeployableTypePtr(aDeployable));
       }

       void TRENTINO_STDCALL  ContributionType::addExportBaseElement(Export* aExportBase){
         mExportBaseElements.push_back(ExportPtr(aExportBase));
       }

     void  TRENTINO_STDCALL  ContributionType::setExtensions(Extensions* aExtensions){
          mExtensionsElement = ExtensionsPtr(aExtensions);
       }

       void TRENTINO_STDCALL  ContributionType::addImportBaseElement(Import* aImportBase){
         mImportBaseElements.push_back(ImportPtr(aImportBase));
       }


      //attribute accessors
       void TRENTINO_STDCALL  ContributionType::setVersion(const char* aVersion){
         mVersion = aVersion;
      }
      



//Class implementation
//************************************************************************************************************
//                                    CreateResource
//************************************************************************************************************
	//static member initialization
	CreateResource::ValueMap CreateResource::mValueMap = CreateResource::createValueMap();

  
   //construction
	CreateResource::CreateResource(const string& valueStr): mValue(mValueMap[valueStr]){}

    //services
	string CreateResource::toString() const
	{   
	   for( ValueMap::const_iterator it = mValueMap.begin();
	        it != mValueMap.end(); ++it)
		   {
		      if(it->second == mValue)
		         return it->first;
		   }
	
	      assert(false);
	      return "";
	 }

     //management
	 CreateResource::ValueMap CreateResource::createValueMap()
	 {
		   ValueMap valueMap;
		   valueMap.insert(make_pair("always", Always));
		   valueMap.insert(make_pair("ifnotexist", Ifnotexist));
		   valueMap.insert(make_pair("never", Never));
		   return valueMap;
	  }


//Class implementation
//************************************************************************************************************
//                                    DeployableType
//************************************************************************************************************
   //construction
DeployableType::DeployableType()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  DeployableType::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
	 void TRENTINO_STDCALL  DeployableType::setComposite(Trentino::XML::Schema::QName* aComposite){
		   mComposite =QNamePtr(aComposite);
		}



//Class implementation
//************************************************************************************************************
//                                    Documentation
//************************************************************************************************************
   //construction
Documentation::Documentation()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Documentation::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
       void TRENTINO_STDCALL  Documentation::setLang(const char* aLang){
         mLang = aLang;
      }
      



//Class implementation
//************************************************************************************************************
//                                    EndpointReferenceType
//************************************************************************************************************
   //construction
EndpointReferenceType::EndpointReferenceType()
      {
      }

   //services

      //element accessors  
     void  TRENTINO_STDCALL  EndpointReferenceType::setAddress(AttributedURIType* aAddress){
          mAddressElement = AttributedURITypePtr(aAddress);
       }

       void TRENTINO_STDCALL  EndpointReferenceType::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }

     void  TRENTINO_STDCALL  EndpointReferenceType::setMetadata(MetadataType* aMetadata){
          mMetadataElement = MetadataTypePtr(aMetadata);
       }

     void  TRENTINO_STDCALL  EndpointReferenceType::setReferenceParameters(ReferenceParametersType* aReferenceParameters){
          mReferenceParametersElement = ReferenceParametersTypePtr(aReferenceParameters);
       }




//Class implementation
//************************************************************************************************************
//                                    Export
//************************************************************************************************************
   //construction
Export::Export()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Export::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }




//Class implementation
//************************************************************************************************************
//                                    ExportType
//************************************************************************************************************
   //construction
ExportType::ExportType()
      {
      }

   //services


      //attribute accessors
       void TRENTINO_STDCALL  ExportType::setNamespace_(const char* aNamespace_){
         mNamespace_ = aNamespace_;
      }
      



//Class implementation
//************************************************************************************************************
//                                    Extensions
//************************************************************************************************************
   //construction
Extensions::Extensions()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Extensions::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }




//Class implementation
//************************************************************************************************************
//                                    ExternalAttachment
//************************************************************************************************************
   //construction
ExternalAttachment::ExternalAttachment()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  ExternalAttachment::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
       void TRENTINO_STDCALL  ExternalAttachment::setAttachTo(const char* aAttachTo){
         mAttachTo = aAttachTo;
      }
      

       void TRENTINO_STDCALL  ExternalAttachment::addIntents(Trentino::XML::Schema::QName* aIntents){
         mIntents.push_back(QNamePtr(aIntents));
       }

       void TRENTINO_STDCALL  ExternalAttachment::addPolicySets(Trentino::XML::Schema::QName* aPolicySets){
         mPolicySets.push_back(QNamePtr(aPolicySets));
       }



//Class implementation
//************************************************************************************************************
//                                    IPCBinding
//************************************************************************************************************
   //construction
IPCBinding::IPCBinding()
      {
	       mXSDType.reset(new QName("IPCBinding", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
      }

   //services




//Class implementation
//************************************************************************************************************
//                                    Implementation
//************************************************************************************************************
   //construction
Implementation::Implementation()
      {
	       mXSDType.reset(new QName("Implementation", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Implementation::addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment){
         mPolicySetAttachmentElements.push_back(PolicySetAttachmentPtr(aPolicySetAttachment));
       }

       void TRENTINO_STDCALL  Implementation::addRequiresElement(Requires* aRequires){
         mRequiresElements.push_back(RequiresPtr(aRequires));
       }


      //attribute accessors
       void TRENTINO_STDCALL  Implementation::addPolicySets(Trentino::XML::Schema::QName* aPolicySets){
         mPolicySets.push_back(QNamePtr(aPolicySets));
       }



//Class implementation
//************************************************************************************************************
//                                    ImplementationType
//************************************************************************************************************
   //construction
ImplementationType::ImplementationType()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  ImplementationType::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
       void TRENTINO_STDCALL  ImplementationType::addAlwaysProvides(Trentino::XML::Schema::QName* aAlwaysProvides){
         mAlwaysProvides.push_back(QNamePtr(aAlwaysProvides));
       }

       void TRENTINO_STDCALL  ImplementationType::addMayProvide(Trentino::XML::Schema::QName* aMayProvide){
         mMayProvides.push_back(QNamePtr(aMayProvide));
       }

	 void TRENTINO_STDCALL  ImplementationType::setType(Trentino::XML::Schema::QName* aType){
		   mType =QNamePtr(aType);
		}



//Class implementation
//************************************************************************************************************
//                                    Import
//************************************************************************************************************
   //construction
Import::Import()
      {
	       mXSDType.reset(new QName("Import", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Import::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }




//Class implementation
//************************************************************************************************************
//                                    ImportType
//************************************************************************************************************
   //construction
ImportType::ImportType()
      {
	       mXSDType.reset(new QName("ImportType", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
      }

   //services


      //attribute accessors
       void TRENTINO_STDCALL  ImportType::setLocation(const char* aLocation){
            mLocation = aLocation;
       }
       

       void TRENTINO_STDCALL  ImportType::setNamespace_(const char* aNamespace_){
         mNamespace_ = aNamespace_;
      }
      



//Class implementation
//************************************************************************************************************
//                                    Include
//************************************************************************************************************
   //construction
Include::Include()
      {
      }

   //services


      //attribute accessors
	 void TRENTINO_STDCALL  Include::setName(Trentino::XML::Schema::QName* aName){
		   mName =QNamePtr(aName);
		}



//Class implementation
//************************************************************************************************************
//                                    Intent
//************************************************************************************************************
   //construction
Intent::Intent()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Intent::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }

       void TRENTINO_STDCALL  Intent::setDescription(const char* aDescription){
         mDescriptionElement = aDescription;
      }
      

       void TRENTINO_STDCALL  Intent::addQualifierElement(IntentQualifier* aQualifier){
         mQualifierElements.push_back(IntentQualifierPtr(aQualifier));
       }


      //attribute accessors
       void TRENTINO_STDCALL  Intent::addConstrains(Trentino::XML::Schema::QName* aConstrains){
         mConstrains.push_back(QNamePtr(aConstrains));
       }

       void TRENTINO_STDCALL  Intent::addExcludes(Trentino::XML::Schema::QName* aExcludes){
         mExcludes.push_back(QNamePtr(aExcludes));
       }

     void  TRENTINO_STDCALL  Intent::setIntentType(InteractionOrImplementation* aIntentType){
          mIntentType = InteractionOrImplementationPtr(aIntentType);
       }

       void TRENTINO_STDCALL  Intent::setMutuallyExclusive(bool isMutuallyExclusive){
         mIsMutuallyExclusive = isMutuallyExclusive;
      }
      

       void TRENTINO_STDCALL  Intent::setName(const char* aName){
            mName = aName;
       }
       

       void TRENTINO_STDCALL  Intent::addRequires(Trentino::XML::Schema::QName* aRequires){
         mRequires.push_back(QNamePtr(aRequires));
       }



//Class implementation
//************************************************************************************************************
//                                    IntentMap
//************************************************************************************************************
   //construction
IntentMap::IntentMap()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  IntentMap::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
	 void TRENTINO_STDCALL  IntentMap::setProvides(Trentino::XML::Schema::QName* aProvides){
		   mProvides =QNamePtr(aProvides);
		}



//Class implementation
//************************************************************************************************************
//                                    IntentQualifier
//************************************************************************************************************
   //construction
IntentQualifier::IntentQualifier()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  IntentQualifier::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }

       void TRENTINO_STDCALL  IntentQualifier::setDescription(const char* aDescription){
         mDescriptionElement = aDescription;
      }
      


      //attribute accessors
       void TRENTINO_STDCALL  IntentQualifier::setDefault(bool isDefault){
         mIsDefault = isDefault;
      }
      

       void TRENTINO_STDCALL  IntentQualifier::setName(const char* aName){
            mName = aName;
       }
       



//Class implementation
//************************************************************************************************************
//                                    InteractionOrImplementation
//************************************************************************************************************
	//static member initialization
	InteractionOrImplementation::ValueMap InteractionOrImplementation::mValueMap = InteractionOrImplementation::createValueMap();

  
   //construction
	InteractionOrImplementation::InteractionOrImplementation(const string& valueStr): mValue(mValueMap[valueStr]){}

    //services
	string InteractionOrImplementation::toString() const
	{   
	   for( ValueMap::const_iterator it = mValueMap.begin();
	        it != mValueMap.end(); ++it)
		   {
		      if(it->second == mValue)
		         return it->first;
		   }
	
	      assert(false);
	      return "";
	 }

     //management
	 InteractionOrImplementation::ValueMap InteractionOrImplementation::createValueMap()
	 {
		   ValueMap valueMap;
		   valueMap.insert(make_pair("implementation", Implementation));
		   valueMap.insert(make_pair("interaction", Interaction));
		   return valueMap;
	  }


//Class implementation
//************************************************************************************************************
//                                    Interface
//************************************************************************************************************
   //construction
Interface::Interface()
      {
	       mXSDType.reset(new QName("Interface", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Interface::addPolicySetAttachmentElement(PolicySetAttachment* aPolicySetAttachment){
         mPolicySetAttachmentElements.push_back(PolicySetAttachmentPtr(aPolicySetAttachment));
       }

       void TRENTINO_STDCALL  Interface::addRequiresElement(Requires* aRequires){
         mRequiresElements.push_back(RequiresPtr(aRequires));
       }


      //attribute accessors
       void TRENTINO_STDCALL  Interface::addPolicySets(Trentino::XML::Schema::QName* aPolicySets){
         mPolicySets.push_back(QNamePtr(aPolicySets));
       }

       void TRENTINO_STDCALL  Interface::setRemotable(bool isRemotable){
         mIsRemotable = isRemotable;
      }
      



//Class implementation
//************************************************************************************************************
//                                    Metadata
//************************************************************************************************************
   //construction
Metadata::Metadata()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Metadata::addStringAttributesElement(MetadataStringAttribute* aStringAttributes){
         mStringAttributesElements.push_back(MetadataStringAttributePtr(aStringAttributes));
       }




//Class implementation
//************************************************************************************************************
//                                    MetadataStringAttribute
//************************************************************************************************************
   //construction
MetadataStringAttribute::MetadataStringAttribute()
      {
      }

   //services


      //attribute accessors
       void TRENTINO_STDCALL  MetadataStringAttribute::setName(const char* aName){
         mName = aName;
      }
      

       void TRENTINO_STDCALL  MetadataStringAttribute::setValue(const char* aValue){
         mValue = aValue;
      }
      



//Class implementation
//************************************************************************************************************
//                                    MetadataType
//************************************************************************************************************
   //construction
MetadataType::MetadataType()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  MetadataType::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }




//Class implementation
//************************************************************************************************************
//                                    Object
//************************************************************************************************************
   //construction
Object::Object()
      {
      }

   //services




//Class implementation
//************************************************************************************************************
//                                    OperationSelectorType
//************************************************************************************************************
   //construction
OperationSelectorType::OperationSelectorType()
      {
      }

   //services




//Class implementation
//************************************************************************************************************
//                                    OperatorContentType
//************************************************************************************************************
   //construction
OperatorContentType::OperatorContentType()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  OperatorContentType::addAllElement(OperatorContentType* aAll){
         mAllElements.push_back(OperatorContentTypePtr(aAll));
       }

       void TRENTINO_STDCALL  OperatorContentType::addExactlyOneElement(OperatorContentType* aExactlyOne){
         mExactlyOneElements.push_back(OperatorContentTypePtr(aExactlyOne));
       }

       void TRENTINO_STDCALL  OperatorContentType::addPolicyElement(Policy* aPolicy){
         mPolicyElements.push_back(PolicyPtr(aPolicy));
       }

       void TRENTINO_STDCALL  OperatorContentType::addPolicyReferenceElement(PolicyReference* aPolicyReference){
         mPolicyReferenceElements.push_back(PolicyReferencePtr(aPolicyReference));
       }




//Class implementation
//************************************************************************************************************
//                                    OverrideOptions
//************************************************************************************************************
	//static member initialization
	OverrideOptions::ValueMap OverrideOptions::mValueMap = OverrideOptions::createValueMap();

  
   //construction
	OverrideOptions::OverrideOptions(const string& valueStr): mValue(mValueMap[valueStr]){}

    //services
	string OverrideOptions::toString() const
	{   
	   for( ValueMap::const_iterator it = mValueMap.begin();
	        it != mValueMap.end(); ++it)
		   {
		      if(it->second == mValue)
		         return it->first;
		   }
	
	      assert(false);
	      return "";
	 }

     //management
	 OverrideOptions::ValueMap OverrideOptions::createValueMap()
	 {
		   ValueMap valueMap;
		   valueMap.insert(make_pair("may", May));
		   valueMap.insert(make_pair("must", Must));
		   valueMap.insert(make_pair("no", No));
		   return valueMap;
	  }


//Class implementation
//************************************************************************************************************
//                                    Policy
//************************************************************************************************************
   //construction
Policy::Policy()
      {
      }

   //services


      //attribute accessors
       void TRENTINO_STDCALL  Policy::setName(const char* aName){
            mName = aName;
       }
       



//Class implementation
//************************************************************************************************************
//                                    PolicyAttachment
//************************************************************************************************************
   //construction
PolicyAttachment::PolicyAttachment()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  PolicyAttachment::addPolicyElement(Policy* aPolicy){
         mPolicyElements.push_back(PolicyPtr(aPolicy));
       }

       void TRENTINO_STDCALL  PolicyAttachment::addPolicyReferenceElement(PolicyReference* aPolicyReference){
         mPolicyReferenceElements.push_back(PolicyReferencePtr(aPolicyReference));
       }

     void  TRENTINO_STDCALL  PolicyAttachment::setAppliesTo(AppliesTo* aAppliesTo){
          mAppliesToElement = AppliesToPtr(aAppliesTo);
       }

       void TRENTINO_STDCALL  PolicyAttachment::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }




//Class implementation
//************************************************************************************************************
//                                    PolicyReference
//************************************************************************************************************
   //construction
PolicyReference::PolicyReference()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  PolicyReference::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
       void TRENTINO_STDCALL  PolicyReference::setDigestAlgorithm(const char* aDigestAlgorithm){
            mDigestAlgorithm = aDigestAlgorithm;
       }
       

       void TRENTINO_STDCALL  PolicyReference::setUri(const char* aUri){
            mUri = aUri;
       }
       



//Class implementation
//************************************************************************************************************
//                                    PolicySet
//************************************************************************************************************
   //construction
PolicySet::PolicySet()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  PolicySet::addIntentMapElement(IntentMap* aIntentMap){
         mIntentMapElements.push_back(IntentMapPtr(aIntentMap));
       }

       void TRENTINO_STDCALL  PolicySet::addPolicySetReferenceElement(PolicySetReference* aPolicySetReference){
         mPolicySetReferenceElements.push_back(PolicySetReferencePtr(aPolicySetReference));
       }


      //attribute accessors
       void TRENTINO_STDCALL  PolicySet::setAppliesTo(const char* aAppliesTo){
         mAppliesTo = aAppliesTo;
      }
      

       void TRENTINO_STDCALL  PolicySet::setAttachTo(const char* aAttachTo){
         mAttachTo = aAttachTo;
      }
      

       void TRENTINO_STDCALL  PolicySet::setName(const char* aName){
            mName = aName;
       }
       

       void TRENTINO_STDCALL  PolicySet::addProvides(Trentino::XML::Schema::QName* aProvides){
         mProvides.push_back(QNamePtr(aProvides));
       }



//Class implementation
//************************************************************************************************************
//                                    PolicySetAttachment
//************************************************************************************************************
   //construction
PolicySetAttachment::PolicySetAttachment()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  PolicySetAttachment::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
	 void TRENTINO_STDCALL  PolicySetAttachment::setName(Trentino::XML::Schema::QName* aName){
		   mName =QNamePtr(aName);
		}



//Class implementation
//************************************************************************************************************
//                                    PolicySetReference
//************************************************************************************************************
   //construction
PolicySetReference::PolicySetReference()
      {
      }

   //services


      //attribute accessors
	 void TRENTINO_STDCALL  PolicySetReference::setName(Trentino::XML::Schema::QName* aName){
		   mName =QNamePtr(aName);
		}



//Class implementation
//************************************************************************************************************
//                                    ProblemActionType
//************************************************************************************************************
   //construction
ProblemActionType::ProblemActionType()
      {
      }

   //services

      //element accessors  
     void  TRENTINO_STDCALL  ProblemActionType::setAction(AttributedURIType* aAction){
          mActionElement = AttributedURITypePtr(aAction);
       }

       void TRENTINO_STDCALL  ProblemActionType::setSoapAction(const char* aSoapAction){
            mSoapActionElement = aSoapAction;
       }
       




//Class implementation
//************************************************************************************************************
//                                    Property
//************************************************************************************************************
   //construction
Property::Property()
      {
      }

   //services


      //attribute accessors
       void TRENTINO_STDCALL  Property::setMustSupply(bool isMustSupply){
         mIsMustSupply = isMustSupply;
      }
      



//Class implementation
//************************************************************************************************************
//                                    PropertyValue
//************************************************************************************************************
   //construction
PropertyValue::PropertyValue()
      {
      }

   //services


      //attribute accessors
       void TRENTINO_STDCALL  PropertyValue::setFile(const char* aFile){
            mFile = aFile;
       }
       

       void TRENTINO_STDCALL  PropertyValue::setSource(const char* aSource){
         mSource = aSource;
      }
      



//Class implementation
//************************************************************************************************************
//                                    Qualifier
//************************************************************************************************************
   //construction
Qualifier::Qualifier()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Qualifier::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
       void TRENTINO_STDCALL  Qualifier::setName(const char* aName){
         mName = aName;
      }
      



//Class implementation
//************************************************************************************************************
//                                    Reference
//************************************************************************************************************
   //construction
Reference::Reference()
      {
      }

   //services


      //attribute accessors
       void TRENTINO_STDCALL  Reference::setMultiplicity(const char* aMultiplicity){
         mMultiplicity = aMultiplicity;
      }
      

       void TRENTINO_STDCALL  Reference::addPromote(const char* aPromote){
           //std::vector<std::string> mPromotes;
           mPromotes.push_back(aPromote);
       }

       void TRENTINO_STDCALL  Reference::addTarget(const char* aTarget){
           //std::vector<std::string> mTargets;
           mTargets.push_back(aTarget);
       }

       void TRENTINO_STDCALL  Reference::setWiredByImpl(bool isWiredByImpl){
         mIsWiredByImpl = isWiredByImpl;
      }
      



//Class implementation
//************************************************************************************************************
//                                    ReferenceParametersType
//************************************************************************************************************
   //construction
ReferenceParametersType::ReferenceParametersType()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  ReferenceParametersType::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }




//Class implementation
//************************************************************************************************************
//                                    RelatesToType
//************************************************************************************************************
   //construction
RelatesToType::RelatesToType()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  RelatesToType::setValue(const char* aValue){
            mValueElement = aValue;
       }
       


      //attribute accessors
       void TRENTINO_STDCALL  RelatesToType::setRelationshipType(const char* aRelationshipType){
         mRelationshipType = aRelationshipType;
      }
      



//Class implementation
//************************************************************************************************************
//                                    Requires
//************************************************************************************************************
   //construction
Requires::Requires()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Requires::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
       void TRENTINO_STDCALL  Requires::addIntents(Trentino::XML::Schema::QName* aIntents){
         mIntents.push_back(QNamePtr(aIntents));
       }



//Class implementation
//************************************************************************************************************
//                                    SCABinding
//************************************************************************************************************
   //construction
SCABinding::SCABinding()
      {
	       mXSDType.reset(new QName("SCABinding", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
      }

   //services




//Class implementation
//************************************************************************************************************
//                                    SCAImplementation
//************************************************************************************************************
   //construction
SCAImplementation::SCAImplementation()
      {
	       mXSDType.reset(new QName("SCAImplementation", "http://docs.oasis-open.org/ns/opencsa/sca/200912"));
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  SCAImplementation::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
	 void TRENTINO_STDCALL  SCAImplementation::setName(Trentino::XML::Schema::QName* aName){
		   mName =QNamePtr(aName);
		}



//Class implementation
//************************************************************************************************************
//                                    SCAPropertyBase
//************************************************************************************************************
   //construction
SCAPropertyBase::SCAPropertyBase()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  SCAPropertyBase::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
	 void TRENTINO_STDCALL  SCAPropertyBase::setElement(Trentino::XML::Schema::QName* aElement){
		   mElement =QNamePtr(aElement);
		}

       void TRENTINO_STDCALL  SCAPropertyBase::setMany(bool isMany){
         mIsMany = isMany;
      }
      

       void TRENTINO_STDCALL  SCAPropertyBase::setName(const char* aName){
            mName = aName;
       }
       

	 void TRENTINO_STDCALL  SCAPropertyBase::setType(Trentino::XML::Schema::QName* aType){
		   mType =QNamePtr(aType);
		}

       void TRENTINO_STDCALL  SCAPropertyBase::setValue(const char* aValue){
         mValue = aValue;
      }
      



//Class implementation
//************************************************************************************************************
//                                    Service
//************************************************************************************************************
   //construction
Service::Service()
      {
      }

   //services


      //attribute accessors
       void TRENTINO_STDCALL  Service::setPromote(const char* aPromote){
            mPromote = aPromote;
       }
       

       void TRENTINO_STDCALL  Service::setRemote(bool isRemote){
         mIsRemote = isRemote;
      }
      



//Class implementation
//************************************************************************************************************
//                                    TDefinitions
//************************************************************************************************************
   //construction
TDefinitions::TDefinitions()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  TDefinitions::addBindingTypeElement(BindingType* aBindingType){
         mBindingTypeElements.push_back(BindingTypePtr(aBindingType));
       }

       void TRENTINO_STDCALL  TDefinitions::addExternalAttachmentElement(ExternalAttachment* aExternalAttachment){
         mExternalAttachmentElements.push_back(ExternalAttachmentPtr(aExternalAttachment));
       }

       void TRENTINO_STDCALL  TDefinitions::addImplementationTypeElement(ImplementationType* aImplementationType){
         mImplementationTypeElements.push_back(ImplementationTypePtr(aImplementationType));
       }

       void TRENTINO_STDCALL  TDefinitions::addIntentElement(Intent* aIntent){
         mIntentElements.push_back(IntentPtr(aIntent));
       }

       void TRENTINO_STDCALL  TDefinitions::addPolicySetElement(PolicySet* aPolicySet){
         mPolicySetElements.push_back(PolicySetPtr(aPolicySet));
       }


      //attribute accessors
       void TRENTINO_STDCALL  TDefinitions::setTargetNamespace(const char* aTargetNamespace){
            mTargetNamespace = aTargetNamespace;
       }
       



//Class implementation
//************************************************************************************************************
//                                    URI
//************************************************************************************************************
   //construction
URI::URI()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  URI::setValue(const char* aValue){
            mValueElement = aValue;
       }
       




//Class implementation
//************************************************************************************************************
//                                    ValueType
//************************************************************************************************************
   //construction
ValueType::ValueType()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  ValueType::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }




//Class implementation
//************************************************************************************************************
//                                    WSCallback
//************************************************************************************************************
   //construction
WSCallback::WSCallback()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  WSCallback::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }




//Class implementation
//************************************************************************************************************
//                                    Wire
//************************************************************************************************************
   //construction
Wire::Wire()
      {
      }

   //services

      //element accessors  
       void TRENTINO_STDCALL  Wire::addContentElement(const char* aContent){
           //std::vector<std::string> mContentElements;
           mContentElements.push_back(aContent);
       }


      //attribute accessors
       void TRENTINO_STDCALL  Wire::setReplace(bool isReplace){
         mIsReplace = isReplace;
      }
      

       void TRENTINO_STDCALL  Wire::setSource(const char* aSource){
            mSource = aSource;
       }
       

       void TRENTINO_STDCALL  Wire::setTarget(const char* aTarget){
            mTarget = aTarget;
       }
       



//Class implementation
//************************************************************************************************************
//                                    WireFormatType
//************************************************************************************************************
   //construction
WireFormatType::WireFormatType()
      {
      }

   //services


