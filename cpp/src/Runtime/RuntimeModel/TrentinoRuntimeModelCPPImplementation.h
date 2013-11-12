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

#ifndef TrentinoRuntimeModelCPPImplementationH
#define TrentinoRuntimeModelCPPImplementationH

//baseclass
#include "TrentinoRuntimeModelImplementation.h"

//standard
#include <string>

//specific
#include "TrentinoRuntimeModel.h"
#include "../SCAModel/TrentinoSCAModel.h"
#include "../ReflectionRuntime/TrentinoReflectionReflectObject.h"
#include "../ReflectionRuntime/TrentinoReflectionReflectMethod.h"
#include "./../Invocation/TrentinoInvocation.h"

namespace Trentino{
namespace RuntimeModel
{
   //**********************************************************************************************
   //                                    CPPImplementation
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief Represents an SCA CPPImplementation at runtime.
   //!
   //! The RuntimeModel::CPPImplementation class points to the corresponding 
   //! SCA::Model::CPPImplementation class and provides additional information associated with a 
   //! cpp implementation. Examples for such additional information are: 
   //! - reflection code for the corresponding C++ implementation class (necessary to create and
   //!   delete instances of the implementation)
   //! - reflection code for lifecycle methods (init and destroy)  
   //! - etc.   
   //**********************************************************************************************
   class RUNTIMEMODEL_IMPORT_EXPORT CPPImplementation : public Implementation
   {  
      //construction
   public:
      //*******************************************************************************************
      //                                   CPPImplementation()
      //*******************************************************************************************
      //! \brief Constructs a CPPImplementation with the given lifecycle methods names and 
      //! associates it with the given SCA::Model::CPPImplementation.
      //! \param[in] component: the component implemented
      //! \param[in] scaCPPImplementation A shared pointer to the SCA::Model::CPPImplemenataion
      //!             instance this object should be associated with.
      //! \throw std::runtime_error If there is no reflection object associated with the 
      //!        implementation class ( \c scaCPPImplementation->clazz() ).
      //*******************************************************************************************
      explicit CPPImplementation( Trentino::Reflection::DataRegistry& registry,
         const Trentino::SCA::Model::CPPImplementationPtr scaCPPImplementation);
   private: 
      //*******************************************************************************************
      //                              Composite(const Composite&)
      //*******************************************************************************************
      //! \brief Disallow copy construction.      
      //*******************************************************************************************
      CPPImplementation(const CPPImplementation&);

      //operators
   private:
      //*******************************************************************************************
      //                                       operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.
      //*******************************************************************************************
      void operator=(const CPPImplementation&);

      //services
   public:

      int scope() const;
      //*******************************************************************************************
      //                                    querySetterMethod()
      //*******************************************************************************************
      //override from Implementation  (see documentation in Implementation)    
      //! \copydoc RuntimeModel::Implementation::querySetterMethod()
      //! \throw std::runtime_error If the reflection object for the reference's setter method
      //!        cannot be found.
      //! \throw std::runtime_error If more than one (=ambigous) reflection object for the 
      //!        reference's setter method is found. This can happen in case of overloading, if 
      //!        there is more than one setter method with the same name defined in the 
      //!        implementation class. This case is currently not supported.
      //! \todo Support overloading of setter methods. 
      //*******************************************************************************************
      Trentino::Reflection::ReflectMethodPtr querySetterMethod(
         const ConstReferenceBasePtr& reference);
	
	  //*******************************************************************************************
      //                                 queryPropertySetterMethod()
      //*******************************************************************************************
      //override from Implementation  (see documentation in Implementation)    
      //! \copydoc RuntimeModel::Implementation::queryPropertySetterMethod()
      //! \throw std::runtime_error If the reflection object for the property's setter method
      //!        cannot be found.
      //! \throw std::runtime_error If more than one (=ambigous) reflection object for the 
      //!        property's setter method is found. This can happen in case of overloading, if 
      //!        there is more than one setter method with the same name defined in the 
      //!        implementation class. This case is currently not supported.
      //! \todo Support overloading of property setter methods. 
      //*******************************************************************************************
      virtual Trentino::Reflection::ReflectMethodPtr queryPropertySetterMethod(
         const ConstPropertyPtr& property); 
      
      //*******************************************************************************************
      //                                         destroyLifeCycleMethod()
      //*******************************************************************************************
      //! \brief return the instance of the lifecycle destroy method
      //! \return Trentino::Reflection::ReflectMethodPtr
      //*******************************************************************************************
      Trentino::Reflection::ReflectMethodPtr destroyLifeCycleMethod() const;

      //*******************************************************************************************
      //                                         initLifeCycleMethod()
      //*******************************************************************************************
      //! \brief return the instance of the lifecycle init method
      //! \return Trentino::Reflection::ReflectMethodPtr
      Trentino::Reflection::ReflectMethodPtr initLifeCycleMethod() const;


      //*******************************************************************************************
      //                                         setContributionDirLifeCycleMethod()
      //*******************************************************************************************
      //! \brief return the instance of the lifecycle set contributionDir method
      //! \return Trentino::Reflection::ReflectMethodPtr
      Trentino::Reflection::ReflectMethodPtr setContributionDirLifeCycleMethod() const;

      //*******************************************************************************************
      //                                         instanceReflectObject()
      //*******************************************************************************************
      //! \brief get the reflect object instance used to manage instances 
      //! \return Trentino::Reflection::ReflectObjectPtr
      //*******************************************************************************************
      Trentino::Reflection::ReflectObjectPtr instanceReflectObject() const;

      //*******************************************************************************************
      //                                  scaCPPImplementation()
      //*******************************************************************************************
      //! \brief Returns the SCA::Model::CPPImplementation associated with the CPPImplementation.
      //! \return A shared pointer to SCA::Model::CPPImplementation instance this object is 
      //!         associated with.
      //! \sa CPPImplementation()        
      //*******************************************************************************************
      Trentino::SCA::Model::CPPImplementationPtr scaCPPImplementation() const; 


   public:
      //*******************************************************************************************
      //                                       queryMethod()
      //*******************************************************************************************
      //! \brief Returns the reflection object for the method with the given name. 
      //! \param[in] methodName Name of the method to retrieve the reflect object for. 
      //! \return A shared pointer to the reflection object for the method with the given name.
      //! \throw std::runtime_error If the reflection object for the method with the given name
      //!        cannot be found.
      //! \throw std::runtime_error If more than one (=ambigous) reflection object for the 
      //!        method with the given name is found. 
      //*******************************************************************************************
      Trentino::Reflection::ReflectMethodPtr queryMethod(const std::string& methodName) const;

      //data
   private:      
      //! the SCA::Model::CPPImplementation associated with this object
      const Trentino::SCA::Model::CPPImplementationPtr mSCACPPImplementation;   
      //! object to access reflection code for the C++ class representing this implementation 
      Trentino::Reflection::ReflectObjectPtr mClass;
      //! object to access reflection code for the "init" method of this implementation
      Trentino::Reflection::ReflectMethodPtr mInitMethod;
      //! object to access reflection code for the "destroy" method of this implementation
      Trentino::Reflection::ReflectMethodPtr mDestroyMethod;

      //! object to access reflection code for the "setcontributiondir" method of this implementation
      Trentino::Reflection::ReflectMethodPtr mSetContributionDirMethod;
   
   }; //class CPPImplementation   

   #include "TrentinoRuntimeModelCPPImplementation.inl"

} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelCPPImplementationH
