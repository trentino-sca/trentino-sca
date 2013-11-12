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

#ifndef TrentinoCoreComponentPropertyManagerH
#define TrentinoCoreComponentPropertyManagerH

//standard
#include <iterator>

//specific
#include "TrentinoCore.h"
#include "../RuntimeModel/TrentinoRuntimeModel.h"
#include "../RuntimeModel/TrentinoRuntimeModelProperty.h"

namespace Trentino{
namespace Core
{
   //**********************************************************************************************
   //                               ComponentPropertyManager
   //**********************************************************************************************
   //! \ingroup Core
   //! \brief Responsible for handling SCA properties specified for components.
   //!
   //! The responsibility includes the following:
   //! - interpretation of the property related parts of the SCA Model 
   //! - assigning correct property values to the corresponding runtime model objects
   //! - casting the string representation of the values into correct numeric, string, pointer 
   //!   and list types
   //! - injecting the casted values into the business logic
   //**********************************************************************************************
   class CORE_IMPORT_EXPORT ComponentPropertyManager
   {
      //additional
   public:
      enum Error
      {
         //! Issued in case a component doesn't specify a value for a (component type) property
         //! with \c \@mustSuply="false" but without a default value.         
         NoDefaultPropertyValuesError,
         //! Issued in case the given property value source doesn't provide a value. Currently 
         //! only if the \c \@source attribute points to a composite property with no value.
         NoPropertyValuesError,
         //! Issued in case the given property value cannot be casted to the target type.
         //! Holds for cases in which the cast cannot be performed at all (e.g. casting \c "xyz" 
         //! or \c "" to \c xsd:int) as well as for range validations (e.g. casting \c "1234"
         //! to \c xsd:byte).
         PropertyValueCastError,
         //! Issued in cases the property file cannot be read, e.g. because it doesn't exist. 
         PropertyFileReadingError,
         //! Issued if the property file doesn't have the expected format (as described in 
         //! Assembly Spec, chapter 4.4.2)
         PropertyFileIllFormedError
      };
   
      //*******************************************************************************************
      //                                     PropertyFile
      //*******************************************************************************************
      //! \brief Represents a property file (as described in Assembly Spec, chapter 4.4.2)
      //!
      //! Offers functionality for reading property values specified in the given file. 
      //! \todo
      //! \attention This class doesn't replace an %XML parser and is not able to report all the 
      //!            possible %XML format violations. 
      //*******************************************************************************************
      class CORE_IMPORT_EXPORT PropertyFile
      {
         //additional
      public:
         class iterator;
         friend class iterator;         
         
         //****************************************************************************************
         //                                      iterator
         //****************************************************************************************
         //! \brief STL style input iterator used to iterate over the content of the \c \<value\>  
         //!        elements in a property file.
         //****************************************************************************************
         class CORE_IMPORT_EXPORT iterator : 
            public std::iterator<std::input_iterator_tag, Trentino::RuntimeModel::Property::Value>
         {
            //construction
         public:  
            //*************************************************************************************
            //                                      iterator
            //*************************************************************************************
            //! \brief Constructs an iterator referring to the content of a \c \<value\> element
            //!        with the given start position inside the content of the given property file.
            //! \param[in] propertyFile Pointer to a PropertyFile the iterator works on. 
            //! \param[in] openingTagStart Index inside of <tt>propertyFile->mContent</tt> 
            //!            of the first character of "<value>".
            //! \par Example:
            //! Given <tt>propertyFile->mContent == "someContent<value>xyz</value>", a valid
            //! value for \c openingTagStart is \c 11.
            //*************************************************************************************
            iterator(const PropertyFile* propertyFile, size_t openingTagStart);            

            //services
         public:
            //*************************************************************************************
            //                                      operator++()
            //*************************************************************************************
            //! \brief Preincrement. Makes the iterator refer to the content of the next 
            //!        \c \<value\> element.
            //! \return Reference to itself.
            //! \throw Trentino::Core::Exception<ComponentPropertyManager> with \c data() set to
            //!        \c PropertyFileIllFormedError if no closing \c\</value\> tag could be found.
            //*************************************************************************************
            iterator& operator++();

            //*************************************************************************************
            //                                   operator++(int)
            //*************************************************************************************
            //! \brief Postincrement. Makes the iterator refer to the content of the next 
            //!        \c \<value\> element.
            //! \return A copy of the non-incremented iterator.
            //! \throw Trentino::Core::Exception<ComponentPropertyManager> with \c data() set to
            //!        \c PropertyFileIllFormedError if no closing \c\</value\> tag could be found.
            //*************************************************************************************
            iterator operator++(int); 

            //*************************************************************************************
            //                                     operator==()
            //*************************************************************************************
            //! \brief Equality operator.
            //! \param[in] rhs Iterator to compare with.
            //! \return \c true if the current iterator refers to the same element in the property
            //!         file as the iterator specified via \c rhs, otherwise \c false.
            //*************************************************************************************
            bool operator==(const iterator& rhs) const;

            //*************************************************************************************
            //                                     operator==()
            //*************************************************************************************
            //! \brief Inequality operator.
            //! \param[in] rhs Iterator to compare with.
            //! \return \c false if the current iterator refers to the same element in the property
            //!         file as the iterator specified via \c rhs, otherwise \c true.
            //*************************************************************************************
            bool operator!=(const iterator& rhs) const;

            //*************************************************************************************
            //                                     operator*()
            //*************************************************************************************
            //! \brief Returns the content of the element the iterator is referring to. 
            //! \return A reference to the content of the current \c \<value\> element.
            //*************************************************************************************
            const Trentino::RuntimeModel::Property::Value& operator*() const;

            //management
         private:
            //*************************************************************************************
            //                                    readValue()
            //*************************************************************************************
            //! \brief Reads the content of the \c \<value\> element specified via the given index
            //!        and assigns it \c mCurrentValue. 
            //! \param[in] openingTagStart Index inside of <tt>propertyFile->mContent</tt> of the
            //!            first character of "<value>".
            //! \return A reference to the content of the current \c \<value\> element.
            //! \throw Trentino::Core::Exception<ComponentPropertyManager> with \c data() set to
            //!        \c PropertyFileIllFormedError if no closing \c\</value\> tag could be found.
            //! \sa iterator()
            //*************************************************************************************
            void readValue(size_t openingTagStart);

            //data
         private:
            //! Pointer to the PropertyFile the iterator works on
            const PropertyFile* mPropertyFile;
            //! Index inside of <tt>propertyFile->mContent</tt> of the first character 
            //! of "<value>" of the current element.          
            size_t mCurrentOpeningTagStart;
            //! The content of the current element the iterator refers to.
            Trentino::RuntimeModel::Property::Value mCurrentValue;
         }; //class iterator

         //construction
      public:
         //****************************************************************************************
         //                                    PropertyFile()
         //****************************************************************************************
         //! \brief Constructs a PropertyFile object representing the file at the given path.
         //!
         //! Opens the file at the given path, reads its content and performs certain consistency
         //! checks.
         //! \param[in] filePath Path to the property file.
         //! \throw Trentino::Core::Exception<ComponentPropertyManager> with \c data() set to
         //!        \c PropertyFileReadingError in case any error occurred in reading the file.       
         //! \throw Trentino::Core::Exception<ComponentPropertyManager> with \c data() set to
         //!        \c PropertyFileIllFormedError if the opening or closing root tag 
         //!        (\c \<values\>, \c \</values\>) is missing.
         //! \throw Trentino::Core::Exception<ComponentPropertyManager> with \c data() set to
         //!        \c PropertyFileIllFormedError if no \c \</value\> elements could be found in
         //!        the file.
         //****************************************************************************************
         explicit PropertyFile(const std::string& filePath);
         
         //****************************************************************************************
         //                                    ~PropertyFile()
         //****************************************************************************************
         //! \brief Empty destructor.
         //****************************************************************************************
         ~PropertyFile();
      private:
         //****************************************************************************************
         //                             PropertyFile(const PropertyFile&)
         //****************************************************************************************
         //! \brief Disallow inadvertent copying. 
         //****************************************************************************************
         PropertyFile(const PropertyFile&);

         //operators
      private:
         //****************************************************************************************
         //                              operator=(const PropertyFile&)
         //****************************************************************************************
         //! \brief Disallow inadvertent assignment. 
         //****************************************************************************************
         void operator=(const PropertyFile&);

         //services
      public:
         //****************************************************************************************
         //                                       begin()
         //****************************************************************************************
         //! \brief Returns iterator to beginning.
         //! \return An input iterator referring to the content of the first \c \</value\> element
         //!         in the property file.
         //****************************************************************************************
         iterator begin() const;

         //****************************************************************************************
         //                                        end()
         //****************************************************************************************
         //! \brief Returns iterator to end.
         //! \return An input iterator referring to the \e past-the-end element.
         //****************************************************************************************
         iterator end() const;

         //data
      private:
         //! constant representing the opening root tag for a value element
         static const std::string OpeningTag;
         //! constant representing the closing root tag for a value element
         static const std::string ClosingTag;
         //! path to the represented property file 
         std::string mFilePath;
         //! the complete content of the property file
         std::string mContent;
         //! position in mContent identifying the start of the first \<value\> tag
         size_t mStartOfFirstValueTag;
      }; //class PropertyFile

      //construction
   public:
      //*******************************************************************************************
      //                               ComponentPropertyManager()
      //*******************************************************************************************
      //! \brief Empty constructor.      
      //*******************************************************************************************
      ComponentPropertyManager();

      //*******************************************************************************************
      //                               ComponentPropertyManager()
      //*******************************************************************************************
      //! \brief Empty destructor.      
      //*******************************************************************************************
      ~ComponentPropertyManager();
   private:
      //*******************************************************************************************
      //                   ComponentPropertyManager(const ComponentPropertyManager&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copying.     
      //*******************************************************************************************
      ComponentPropertyManager(const ComponentPropertyManager&);

      //operators
   private:
      //*******************************************************************************************
      //                         operator=(const ComponentPropertyManager&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent assignment.     
      //*******************************************************************************************
      void operator=(const ComponentPropertyManager&);

      //services
   public:
      //*******************************************************************************************
      //                                 assignValuesFromSCAModel()
      //*******************************************************************************************
      //! \brief Processes the SCA Model objects associated with the given runtime model property
      //!        and assigns it a valid value according to the SCA rules. 
      //!
      //! \param[in] property Shared pointer to the property object to assign values to. 
      //! \throw Trentino::Core::Exception<ComponentPropertyManager> with \c data() set to
      //!        \c NoDefaultPropertyValuesError in case a component doesn't specify a value for a 
      //!        (component type) property with \c \@mustSuply="false" but without a default value. 
      //! \throw Trentino::Core::Exception<ComponentPropertyManager> with \c data() set to
      //!        \c NoPropertyValuesError in case the \c \@source attribute points to a composite 
      //!         property with no value.
      //! \throw Trentino::Core::Exception<ComponentPropertyManager> with \c data() set to
      //!        \c PropertyFileReadingError in case any error occurred in reading a property file.  
      //! \throw Trentino::Core::Exception<ComponentPropertyManager> with \c data() set to
      //!        \c PropertyFileIllFormedError if a property file doesn't have the expected format.
      //!         
      //! This method performs the \b first step in injecting values from the SCA Model to the 
      //! business logic. That way it decouples the values in the SCA Model from those finally
      //! being injected into the business logic and thus allows for more flexibility in 
      //! implementing different features, such as property value reinjection. The \b second and
      //! final step in value injection is performed by the injectValues() method. The both methods
      //! can and should be used in conjunction in order to assign property values from SCDL to
      //! the business logic.
      //! \par Example:
      //! \code
      //! assignValuesFromSCAModel(property);
      //! injectValues(property);
      //! \endcode
      //!
      //! \attention
      //! In order to correctly perform value assignment for properties which use the \c \@source
      //! attribute and are additionally attached to components contained in composites used as 
      //! implementations, assignValuesFromSCAModel() must be called for the corresponding "parent
      //! property" \b first. Consider the following example:
      //! \image html AssigningPropertyValuesFromParentComponentExample.png
      //! Given the above constellation, the \c "CompositeProperty" property in the 
      //! \c "ParentComponent" component is considered as the "parent property" of the 
      //! \c "SomeProperty" property because the \c "SomeProperty" property indirectly refers to 
      //! its value through the \c \@source attribute. Given these natural dependencies, before 
      //! assigning the value of the runtime model property object representing the 
      //! \c "SomeProperty" property, the value for the \c "CompositeProperty" object must be
      //! computed first. In other words
      //! \code
      //! RuntimeModel::PropertyPtr compositeProperty = 
      //!      parentComponent->findPropertyByName("CompositeProperty");
      //! RuntimeModel::PropertyPtr someProperty = 
      //!      childComponent->findPropertyByName("SomeProperty"); 
      //! //omitting the following line will cause undesired behavior     
      //! assignValuesFromSCAModel(compositeProperty); 
      //! assignValuesFromSCAModel(someProperty);
      //! \endcode
      //! 
      //! \note Given the dependencies above and additionally considering the recursive character 
      //!       of nested composites in the SCA, the simple strategy for assigning property values  
      //!       in a contribution consists in processing all the components in a composite before
      //!       the components at the lower levels (i.e. in composites referred through 
      //!       \c \<implementation.composite\>. This is exactly the strategy applied by the 
      //!       ContributionLoader. 
      //*******************************************************************************************
      void assignValuesFromSCAModel(const Trentino::RuntimeModel::PropertyPtr& property) const;


      //*******************************************************************************************
      //                                      injectValues()
      //*******************************************************************************************
      //! \brief Casts the string representation of the given property's value to the correct
      //!        target type (numeric, string, list etc.) and injects it into the corresponding
      //!        component implementation. 
      //!
      //! \param[in] property Shared pointer to the property object whose values to inject.  
      //! \param[in] instance Pointer to the instance of a component's implementation in which
      //!            to inject the values. 
      //! \throw Trentino::Core::Exception<ComponentPropertyManager> with \c data() set to
      //!        \c PropertyValueCastError in case the given property value cannot be casted to 
      //!        the target type. Holds for cases in which the cast cannot be performed at all 
      //!        (e.g. casting \c "xyz" or \c "" to \c xsd:int) as well as for range validations 
      //!        (e.g. casting \c "1234" to \c xsd:byte).
      //!      
      //! The casting is performed according to the following table (see also %SCA CPP Spec, 
      //! chapter 9.3.1, table 9-1):
      //! 
      //! \htmlinclude XSDTypeMapping.html
      //! \sa assignValuesFromSCAModel()
      //*******************************************************************************************
      void injectValues( const Trentino::RuntimeModel::ConstPropertyPtr& property
                       , void* instance) const;

   }; //class ComponentPropertyManager

   #include "TrentinoCoreComponentPropertyManager.inl"
    
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreComponentPropertyManagerH