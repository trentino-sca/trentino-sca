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

#ifndef TrentinoCoreContributionLoadingSCAModelLoaderH
#define TrentinoCoreContributionLoadingSCAModelLoaderH

//standard
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

//specific
#include "TrentinoCore.h"
#include "./../../Global/TrentinoGlobal.h"
#include "./../SCAModel/TrentinoSCAModel.h"
#include "./../SCAModel/TrentinoSCAModelFactory.h"

namespace Trentino{
namespace SCA{
namespace Model
{
   class ModelDescriptor;         

} //namespace Model
} //namespace SCA
} //namespace Trentino

namespace Trentino {
namespace Core {
namespace ContributionLoading
{
   //**********************************************************************************************
   //                                      SCAModelLoader
   //**********************************************************************************************
   //! \ingroup ContributionLoading
   //! \brief  Offers an interface to instantiate and access SCAModel classes.
   //!
   //! SCAModelLoader offers two semantically  different interfaces: one interface is meant to be 
   //! used by the generated code to trigger SCAModel class instantiation, the other interface is 
   //! used within the runtime itself to access the constructed SCAModel class structure. 
   //! 
   //! An instance of the SCAModeLoader class is supposed to be passed to the generate code which 
   //! is responsible for the instantiation of the SCAModel classes. Therefore, SCAModelLoader 
   //! offers a factory that should be used for the creation of the corresponding classes. On 
   //! completion of the instantiation process, the runtime can use the ModelDescriptor passed to 
   //! SCAModelLoader to retrieve the created SCAModel classes.
   //!
   //! One of the central ideas of the SCAModelLoader is to free the generated code from the
   //! necessity of being concerned with data structures to be used for storing SCA Model class
   //! instances etc. The generated code is only concerned with creating the necessary classes
   //! and providing them with information by calling the corresponding setter methods of the 
   //! classes. The decision where to store all the information and how to present it to further 
   //! clients is made by the SCAModelLoader, for example by overloading certain create*() methods
   //! of the SCA::Model::Factory to store the created instances in internal data structures. 
   //**********************************************************************************************
   class SCAModelLoader
   {
      //additional
   public:
      //*******************************************************************************************
      //                                      SCAModelFactory
      //*******************************************************************************************      
      //! \brief Factory for creating SCAModel class instances.
      //! 
      //! SCAModelLoader needs to override certain create*() methods of the original SCAModel 
      //! factory to intercept creations in order to save the needed class instances inside of 
      //! internal data structures. This is for example the way how the information stored in the
      //! ModelDescriptor is collected. 
      //!
      //! This interception functionality is outsourced into a nested class that is a friend of
      //! SCAModelLoader.
      //*******************************************************************************************
      class SCAModelFactory : public Trentino::SCA::Model::Factory 
      {
         //construction
      public:
         //****************************************************************************************
         //                                      SCAModelFactory()
         //****************************************************************************************
         //! \brief Constructs a SCAModelFactory and stores its parent SCAModelLoader.
         //!         
         //! An SCAModelFactory instance is supposed to be created by SCAModelLoader which passes a 
         //! reference to itself to the SCAModelFactory. 
         //
         //! \param[in] A reference to the SCAModelLoader that is associated with the factory. The 
         //!            passed reference is guaranteed to not being accessed during the 
         //!            construction of the object. Therefore, it's safe to pass a reference to 
         //!            \c this inside of a member initializer list.         
         //****************************************************************************************
         explicit SCAModelFactory(SCAModelLoader& modelLoader);
         ~SCAModelFactory();

         //operators
      private:
         void operator=(const SCAModelFactory&);

         //services
      public:
         //****************************************************************************************
         //                                      createComposite()
         //****************************************************************************************
         //! \brief Creates a composite.
         //!         
         //! \return A raw pointer to the composite.
         //****************************************************************************************
         CORE_IMPORT_EXPORT Trentino::SCA::Model::Composite* 
            TRENTINO_STDCALL createComposite();

         //****************************************************************************************
         //                                      createContributionType()
         //****************************************************************************************
         //! \brief Creates a ContributionType and stores a shared pointer to in the associated
         //!        SCAModelLoader instance;
         //!         
         //! createContributionType() is allowed to be called only once on an instance of  
         //! SCAModelLoader because only one contribution model can be loaded simultaneously by an 
         //! instance of SCAModelLoader. Throwing an exception in case createContributionType() is 
         //! called more than once would be appropriate under normal circumstances. But since  
         //! createControbutionType() is supposed to be called from the generated code, throwing an 
         //! exception could lead to binary incompatibilities. Therefore the default behavior is  
         //! just to return nullptr in case of subsequent calls.
         //! 
         //! \return A raw pointer to the newly created ContributionType or nullptr if the methods  
         //!         is called more than once. \n
         //!         \par Example: 
         //!         \code
         //!         SCAModelLoader modelLoader;
         //!         SCAModelLoader::SCAModelFactory& factory = modelLoader.scaModelFactory();
         //!         ContributionType* c = factory.createContributionType();
         //!         assert(c != nullptr);
         //!         assert(modelLoader.contribution().get() == c);                  
         //!         assert(factory.createContributionType() == nullptr);
         //!         assert(modelLoader.contribution().get() == c);                   
         //!         \endcode        
         //****************************************************************************************
         CORE_IMPORT_EXPORT Trentino::SCA::Model::ContributionType* 
            TRENTINO_STDCALL createContributionType();

         //data
      private:
         SCAModelLoader& mSCAModelLoader;
      
      }; //class SCAModelFactory     

      friend class SCAModelFactory;

   private:
      typedef std::vector<Trentino::SCA::Model::Composite*> SCACompositesRaw;

      //construction
   public:
       //*******************************************************************************************
      //                                        SCAModelLoader()
      //*******************************************************************************************
      //! \brief Construction an SCAModelLoader instance with the given ModelDescriptor.
      //! \param[in] modelDescriptor Reference to the ModelDescriptor to pupulate with the loaded
      //!            information.
      //*******************************************************************************************
      CORE_IMPORT_EXPORT SCAModelLoader(Trentino::SCA::Model::ModelDescriptor& modelDescriptor);
      CORE_IMPORT_EXPORT ~SCAModelLoader();
   private:
      SCAModelLoader(const SCAModelLoader&);

      //operators
   private:
        void operator=(const SCAModelLoader&);

      //services
   public: 
      //*******************************************************************************************
      //                              interface to the generated code
      //*******************************************************************************************
      //! @name interface to the generated code
      //! Only the following methods should be used by the generated code.          
      //*******************************************************************************************
      //!@{

      //*******************************************************************************************
      //                                     scaModelFactory()
      //*******************************************************************************************
      //! \brief Returns a factory that is to be used for the instantiation of the SCAModel classes.
      //! \return Reference to the SCAModelFactory.   
      //! 
      //! \remark Here it's absolutely necessary to return a reference to the derived class (i.e.
      //! SCAModelFactory) and not a reference to the base class (Trentino::SCA::Model::Factory)
      //! because for reasons of binary compatibility no virtual methods are allowed in the class
      //! hierarchy. Therefore, to ensure that the derived class (and not the base class) versions 
      //! of the overriden methods are called, a reference to the derived class is returned.       
      //*******************************************************************************************
      CORE_IMPORT_EXPORT SCAModelFactory& TRENTINO_STDCALL scaModelFactory();

      //*******************************************************************************************
      //                                        associate()
      //*******************************************************************************************
      //! \brief Associates a component with its componentType.
      //!
      //! Because there are no means for associating a component with its componentType within the
      //! SCAModel itself, associate() provides the necessary logic. 
      //! \param[in] component A raw pointer to the component that is to be associated with the 
      //!            given componentType.
      //! \param[in] componentType A raw pointer to the componentType that is to be associated with
      //!            the given component.     
      //!
      //! \attention The componentType raw pointer passed as second argument is getting wrapped 
      //!            within a shared pointer before it's stored in an internal data structure. 
      //!            Therefore it \c must be ensured that the corresponding pointer isn't wrapped
      //!            within a further shared pointer during the lifecycle of the referenced object. 
      //*******************************************************************************************
      CORE_IMPORT_EXPORT void TRENTINO_STDCALL associate( 
         Trentino::SCA::Model::Component* component ,
         Trentino::SCA::Model::ComponentType* componentType);   
      //!@}
      
      //data   
   private:
      //! factory to be used for the creation of the SCAModel class instances
      SCAModelFactory mSCAModelFactory;      
      //! reference to the model descriptor that is populated by SCAModelLoader 
      Trentino::SCA::Model::ModelDescriptor& mModelDescriptor;                                                   
   }; //class SCAModelLoader  
} // namespace ContributionLoading
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreContributionLoadingSCAModelLoaderH
