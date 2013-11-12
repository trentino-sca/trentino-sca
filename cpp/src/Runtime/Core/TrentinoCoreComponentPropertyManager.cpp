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
#include "TrentinoCoreComponentPropertyManager.h"

//standard
#include <cstring>
#include <list>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/algorithm/string.hpp>

//specific
#include "../../Global/TrentinoGlobal.h"
#include "TrentinoCoreException.h"
#include "../RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../SCAModel/TrentinoSCAModelProperty.h"
#include "../SCAModel/TrentinoSCAModelPropertyValue.h"
#include "../SCAModel/TrentinoSCAModelComponent.h"
#include "../SCAModel/TrentinoSCAModelComposite.h"
#include "../ReflectionRuntime/TrentinoReflectionReflectMethod.h"
#include "../ReflectionRuntime/TrentinoReflectionHelpersListWrapper.h"

using namespace std;
using Trentino::Core::ComponentPropertyManager;
using Trentino::Core::Exception;
namespace RuntimeModel = Trentino::RuntimeModel;
namespace SCAModel = Trentino::SCA::Model;

namespace
{
   void handleSourceAttribute(const RuntimeModel::PropertyPtr& property)
   {
      const SCAModel::PropertyValuePtr scaProperty = property->scaProperty();
      assert(scaProperty);

      //this should have been validated at generation time
      assert( scaProperty->source()[0] == '$');

      const string compositePropertyName = scaProperty->source().substr(1);

      const RuntimeModel::ConstComponentPtr component = property->component().lock();
      assert(component);
      const RuntimeModel::CompositePtr composite = component->composite().lock();            
      assert(composite);
      if(composite->isDeployable())
      {  
         //find the composite property element referenced by the @source attribute
         const SCAModel::CompositePtr scaComposite = composite->scaComposite();
         assert(scaComposite);
         const vector<SCAModel::PropertyPtr>::const_iterator it = 
            find_if( scaComposite->propertyElements().begin()
                   , scaComposite->propertyElements().end()
                   , boost::bind(&SCAModel::Property::name, _1) == 
                        compositePropertyName );
               
         //this should have been validated at generation time
         assert(it != scaComposite->propertyElements().end());

         const SCAModel::PropertyPtr scaCompositeProperty  = *it;
         assert(scaCompositeProperty);

         if(scaCompositeProperty->contentElements().empty())
         {
               ostringstream errorMessage;
               errorMessage << "No values specified for composite <property> with @name = '" 
                            << scaCompositeProperty->name() 
                            << "'. Specified in <composite> with QName '"  
                            << composite->qName().toString() 
                            << "'. Referenced in <property> with @name = '" << scaProperty->name()
                            << "' in <component> with @name = '" 
                            << component->scaComponent()->name() << "'.";
               throw Exception<ComponentPropertyManager::Error>(
                  ComponentPropertyManager::NoPropertyValuesError, errorMessage.str() );                  
         }

         property->setValues(scaCompositeProperty->contentElements());
      }
      else
      {         
         assert(composite);
         const RuntimeModel::ComponentPtr parentComponent = composite->component().lock();
               
         assert(parentComponent);               
         const RuntimeModel::Properties::const_iterator it = 
            find_if( parentComponent->properties().begin()
                   , parentComponent->properties().end()
                   , boost::bind(&RuntimeModel::Property::name, _1) == 
                        compositePropertyName );
               
         assert(it != parentComponent->properties().end());
         const RuntimeModel::PropertyPtr parentComponentProperty = *it;
         property->setValues( parentComponentProperty->values() );
      } //if(composite->isDeployable()){...}else{...}
   } //void handlSourceAttribute(const RuntimeModel::PropertyPtr& property)

   void handleFileAttribute(const RuntimeModel::PropertyPtr& property)
   {
      const SCAModel::PropertyValuePtr scaProperty = property->scaProperty();
      assert(scaProperty);
      const RuntimeModel::ConstComponentPtr component = property->component().lock();
      assert(component);
      const RuntimeModel::CompositePtr composite = component->composite().lock();
      assert(composite);

      //to be used in error messages
      ostringstream fileReferencedIn;
      fileReferencedIn << "Referenced in <property> with @name = '" << scaProperty->name()
                       << "' in <component> with @name = '"  << component->scaComponent()->name()
                       << "' in <composite> with QName '" << composite->qName().toString() << "'";     

      const boost::filesystem::path pathInFileAttribute(scaProperty->file());
      string propertyFilePath;
      if( pathInFileAttribute.is_complete() )
      {
         propertyFilePath = scaProperty->file();
      }
      else
      {  
         const RuntimeModel::ContributionPtr contribution = composite->contribution().lock();
               
         assert(contribution);
         propertyFilePath = 
            ( boost::filesystem::path(contribution->localPath()) / pathInFileAttribute ).string();
      }

      try
      {
         ComponentPropertyManager::PropertyFile propertyFile(propertyFilePath);
         for_each( propertyFile.begin()
                 , propertyFile.end()
                 , boost::bind(&RuntimeModel::Property::addValue, property, _1) );
      }
      catch(Exception<ComponentPropertyManager::Error>& e)
      {
         const string what = string(e.what()) + "." + fileReferencedIn.str();
         throw Exception<ComponentPropertyManager::Error>(e.data(), what);
      } 
   } //void handleFileAttribute(const RuntimeModel::PropertyPtr& property) 

   template<typename T>
   T castString(const string& value)
   {
      return boost::lexical_cast<T>(value);
   }

   //for the reasons why int8_t and uint8_t cannot be directly casted by lexical_cast see
   //the FAQ for lexical_cast on the boost homepage 
   template<>
   int8_t castString<int8_t>(const string& value)
   {
      return boost::numeric_cast<int8_t>(boost::lexical_cast<int>(value));
   }

   template<>
   uint8_t castString<uint8_t>(const string& value)
   {
      return boost::numeric_cast<uint8_t>(boost::lexical_cast<int>(value));
   }

   //**********************************************************************************************
   //                                       isStringType()
   //**********************************************************************************************
   //! \brief Checks whether the given XSD data type has a C++ \c std::string as representation. 
   //!   
   //! \param[in] xsdType Name of an XSD data type without any XML namespace prefixes.
   //! \return \c true in case the C++ representation of the given XSD data type is \c std::string,
   //!         otherwise \c false. 
   //**********************************************************************************************
   bool isStringType(const string& xsdType)
   {
      static const char* stringTypes[] = 
         { "anySimpleType", "anyURI", "date", "dateTime", "decimal", "duration",
           "ENTITY", "gDay", "gMonth", "gMonthDay", "gYear", "gYearMonth", "ID",  
           "IDREF", "integer", "language", "Name", "NCName", "negativeInteger", "NMTOKEN", 
           "nonNegativeInteger", "nonPositiveInteger", "normalizedString", "NOTATION", 
           "positiveInteger", "QName", "string", "time", "token" };     
      static const set<string> stringTypesSet( stringTypes, stringTypes + COUNT_OF(stringTypes) );

      return stringTypesSet.find(xsdType) != stringTypesSet.end();
   }

   //**********************************************************************************************
   //                                     isTreatedAsMany()
   //**********************************************************************************************
   //! \brief Checks whether the given XSD data type is treated as a multi-valued property even
   //!        for \c \@many="false".
   //!   
   //! As a consequence, such types are mapped ond a \c std::list\<T\> even though they are defined
   //! as single-valued in SCDL (see also %SCA CPP Spec, chapter 9.3.1, table 9-1).
   //! \param[in] xsdType Name of an XSD data type without any XML namespace prefixes.
   //! \return \c true in case the given XSD data type should be treated as multi-valued, otherwise
   //!         \ false.
   //**********************************************************************************************
   bool isTreatedAsMany(const string& xsdType)
   {
      static const char* treatedAsManyTypes[] = { "ENTITIES", "IDREFS", "NMTOKENS" };     
      static const set<string> treatedAsManyTypesSet
         ( treatedAsManyTypes, treatedAsManyTypes + COUNT_OF(treatedAsManyTypes) );

      return treatedAsManyTypesSet.find(xsdType) != treatedAsManyTypesSet.end();
   }

   //! @{
   //**********************************************************************************************
   //                                  invokeSetterSingleValue()
   //**********************************************************************************************
   //! \brief Invokes the setter method for a property with \c \@many="false". 
   //!
   //! The value to be injected is retrieved as \c property->values().front(). 
   //! \param[in] instance Pointer to the instance of a component's implementation to call the
   //!            setter method for. 
   //! \tparam T  Target type to cast the property's value to. For injecting property values
   //!            of type \c xsd::ENTITIES, \c xsd::IDREFS or \c xsd::NMTOKENS the template type 
   //!            must be <tt>std::list\<std::string\></tt>.
   //! \attention Calling this method for a reference with \c \@many="true" will cause 
   //!            undefined behavior.
   //! \attention If there is no setter method associated with the given property, calling this
   //!            method will cause undefined behavior.
   //**********************************************************************************************
   template<typename T>
   void invokeSetterSingleValue( const RuntimeModel::ConstPropertyPtr& property
                               , void* instance) 
   {
      assert(property);
      T targetValue = castString<T>(property->values().front());
      void* setterParams[] = {&targetValue};
      assert(property->setterMethod());
      property->setterMethod()->invoke(instance, setterParams);
   }

   template <>
   void invokeSetterSingleValue<string>( const RuntimeModel::ConstPropertyPtr& property
                                       , void* instance) 
   {
      assert(property);
      const void* voidPtr = property->values().front().c_str();
      void* setterParams[] = {&voidPtr};
      assert(property->setterMethod());
      property->setterMethod()->invoke(instance, setterParams);
   }

   template<>
   void invokeSetterSingleValue<char*>( const RuntimeModel::ConstPropertyPtr& property
   
      , void* instance) 
   {
      assert(property);
      const size_t bufferSize = property->values().front().size() + 1;
      char*  nonConstCopy = new char[bufferSize];
      strcpy_s(nonConstCopy, bufferSize, property->values().front().c_str());
      void* setterParams[] = {&nonConstCopy};
      assert(property->setterMethod());
      property->setterMethod()->invoke(instance, setterParams);
      delete[] nonConstCopy;
   }

   template <>
   void invokeSetterSingleValue< list<string> >( const RuntimeModel::ConstPropertyPtr& property
                                               , void* instance) 
   {
      assert(property);
      list<string> targetValues;
      boost::split(targetValues, property->values().front(), boost::is_space());
      const Trentino::Reflection::Helpers::ListWrapper< list<string> > listWrapper(targetValues);
      const void* voidPtr = listWrapper.listType().get();
      void* setterParams[] = {&voidPtr};
      assert(property->setterMethod());
      property->setterMethod()->invoke(instance, setterParams); 
   }
   //! @}

   //! @{
   //**********************************************************************************************
   //                                  invokeSetterManyValues()
   //**********************************************************************************************
   //! \brief Invokes the setter method for a property with \c \@many="true". 
   //! \param[in] instance Pointer to the instance of a component's implementation to call the
   //!            setter method for. 
   //! \tparam T  Target type to cast the property's values to. The given type will be used as
   //!            the inner type for an \c std::list, i.e. \c std::list\<T\>. For injecting 
   //!            property values of type \c xsd::ENTITIES, \c xsd::IDREFS or \c xsd::NMTOKENS 
   //!            the template type must be <tt>std::list\<std::string\></tt>.
   //! \attention Calling this method for a reference with \c \@many="false" will cause 
   //!            undefined behavior.
   //! \attention If there is no setter method associated with the given property, calling this
   //!            method will cause undefined behavior.
   //**********************************************************************************************
   template<typename T>
   void invokeSetterManyValues( const RuntimeModel::ConstPropertyPtr& property
                              , void* instance) 
   {
      assert(property);
      list<T> targetValues;
      transform( property->values().begin()
               , property->values().end()
               , back_inserter(targetValues)
               , castString<T>);   

      const Trentino::Reflection::Helpers::ListWrapper< list<T> > listWrapper(targetValues);
      const void* voidPtr = listWrapper.listType().get();
      void* setterParams[] = {&voidPtr};
      assert(property->setterMethod());
      property->setterMethod()->invoke(instance, setterParams); 
   }

   template<>
   void invokeSetterManyValues<string>( const RuntimeModel::ConstPropertyPtr& property
                                      , void* instance) 
   {
      assert(property);
      list<string> targetValues(property->values().begin(), property->values().end());
      const Trentino::Reflection::Helpers::ListWrapper< list<string> > listWrapper(targetValues);
      const void* voidPtr = listWrapper.listType().get();
      void* setterParams[] = {&voidPtr};
      assert(property->setterMethod());
      property->setterMethod()->invoke(instance, setterParams);   
   }

   template<>
   void invokeSetterManyValues<char*>( const RuntimeModel::ConstPropertyPtr& property
                                      , void* instance) 
   {
      assert(property);
      list<char*> targetValues;
      BOOST_FOREACH(const RuntimeModel::Property::Value& value, property->values())
      {
         const size_t bufferSize = value.size() + 1;
         char * const nonConstCopy = new char[bufferSize];
         strcpy_s(nonConstCopy, bufferSize, value.c_str());
         targetValues.push_back(nonConstCopy);
      }
  
      const Trentino::Reflection::Helpers::ListWrapper< list<char*> > listWrapper(targetValues);
      const void* voidPtr = listWrapper.listType().get();
      void* setterParams[] = {&voidPtr};
      assert(property->setterMethod());
      property->setterMethod()->invoke(instance, setterParams); 

      for_each( targetValues.begin()
              , targetValues.end()
              , boost::bind(::operator delete[], _1) );
   }

   template<>
   void invokeSetterManyValues< list<string> >( const RuntimeModel::ConstPropertyPtr& property
                                              , void* instance) 
   {
      assert(property);
      list< list<string> > targetValues;         
      BOOST_FOREACH(const string& value, property->values())
      {            
         list<string> listOfSingleValues;
         boost::split(listOfSingleValues, value, boost::is_space());
         targetValues.push_back(listOfSingleValues);            
      }

      const Trentino::Reflection::Helpers::ListWrapper< list< list<string> > > 
         listWrapper(targetValues);
      void* voidPtr = listWrapper.listType().get();
      void* setterParams[] = {&voidPtr};
      assert(property->setterMethod());
      property->setterMethod()->invoke(instance, setterParams);     
   }
   //! @}
} //namespace   

//class ComponentPropertyManager
   //additional
      //class PropertyFile
         //static member initialization
const string ComponentPropertyManager::PropertyFile::OpeningTag = "<value>";
const string ComponentPropertyManager::PropertyFile::ClosingTag = "</value>"; 
         //additional
            //class iterator
               //construction
ComponentPropertyManager::PropertyFile::iterator::iterator(
   const ComponentPropertyManager::PropertyFile* propertyFile, size_t openingTagStart)
: mPropertyFile(propertyFile)
, mCurrentOpeningTagStart(openingTagStart)
{
   readValue(mCurrentOpeningTagStart);    
}
               //services
ComponentPropertyManager::PropertyFile::iterator& 
   ComponentPropertyManager::PropertyFile::iterator::operator++()
{
   assert(mPropertyFile);
   const size_t openingTagSize = ComponentPropertyManager::PropertyFile::OpeningTag.size();
   const size_t closingTagSize = ComponentPropertyManager::PropertyFile::ClosingTag.size();
   const size_t nextOpeningTagStart = mPropertyFile->mContent.find(
      ComponentPropertyManager::PropertyFile::OpeningTag, 
      mCurrentOpeningTagStart + openingTagSize + mCurrentValue.size() + closingTagSize);
      
   readValue(nextOpeningTagStart);

   mCurrentOpeningTagStart = nextOpeningTagStart;

   return *this;
}

ComponentPropertyManager::PropertyFile::iterator
   ComponentPropertyManager::PropertyFile::iterator::operator++(int)
{
   iterator tmp = *this;
   ++*this;
   return tmp;
}
               //management
void ComponentPropertyManager::PropertyFile::iterator::readValue(size_t openingTagStart)
{
   if(openingTagStart == string::npos)
      return;

   assert(mPropertyFile);
   const size_t closingTagStart = mPropertyFile->mContent.find( 
      ComponentPropertyManager::PropertyFile::ClosingTag,
      openingTagStart + ComponentPropertyManager::PropertyFile::OpeningTag.size() );

   if(closingTagStart == string::npos)
   {
      const string errorMessage = 
         "Missing closing tag </value> in property file: " + mPropertyFile->mFilePath;
                      
      throw Exception<ComponentPropertyManager::Error>( 
         ComponentPropertyManager::PropertyFileIllFormedError, errorMessage ); 
   }

   const size_t openingTagSize = ComponentPropertyManager::PropertyFile::OpeningTag.size();
   mCurrentValue = mPropertyFile->mContent.substr( 
                     openingTagStart + openingTagSize,
                     closingTagStart - openingTagStart - openingTagSize );
}
         //construction
ComponentPropertyManager::PropertyFile::PropertyFile(const string& filePath)
: mFilePath(filePath) 
, mStartOfFirstValueTag(string::npos)
{
   ifstream file(mFilePath.c_str(), ios_base::in);  

   if(file.fail() || file.bad())
   {
      char buffer[512] = {0};
      strerror_s(buffer, sizeof(buffer), errno);

      const string errorMessage = "Error reading property file: " + filePath + ". " + buffer;
      throw Exception<ComponentPropertyManager::Error>(
         ComponentPropertyManager::PropertyFileReadingError, errorMessage);                         
   }
   
   file.seekg(0, std::ios::end);
   mContent.resize( static_cast<uint32_t>(file.tellg()) );
   file.seekg(0, std::ios::beg);
   file.read(&mContent[0], mContent.size());
   file.close();        
                        
   const string openingRootTag = "<values>";
   const string closingRootTag = "</values>";

   const size_t openingRootTagStart = mContent.find(openingRootTag);
   const size_t closingRootTagStart = mContent.find(closingRootTag);

   if(openingRootTagStart == string::npos || closingRootTagStart == string::npos)
   {  
      const string errorMessage = 
         "Missing opening or closing <values> root tag in property file: " + filePath + ".";
                      
      throw Exception<ComponentPropertyManager::Error>(
         ComponentPropertyManager::PropertyFileIllFormedError, errorMessage);     
   }    

   mStartOfFirstValueTag = 
      mContent.find(OpeningTag, openingRootTagStart + openingRootTag.size());

   if(mStartOfFirstValueTag == string::npos)
   {
      const string errorMessage = 
         "No <value> elements found in property file: " + filePath + ".";
                      
      throw Exception<ComponentPropertyManager::Error>(
         ComponentPropertyManager::PropertyFileIllFormedError, errorMessage);

   }
}

ComponentPropertyManager::PropertyFile::~PropertyFile()
{}
         //services
ComponentPropertyManager::PropertyFile::iterator 
   ComponentPropertyManager::PropertyFile::begin() const
{
   
   return iterator(this, mStartOfFirstValueTag);
}

ComponentPropertyManager::PropertyFile::iterator 
   ComponentPropertyManager::PropertyFile::end() const
{
   return iterator(this, string::npos);
}

   //construction
ComponentPropertyManager::ComponentPropertyManager()
{}

ComponentPropertyManager::~ComponentPropertyManager()
{}

   //services
void ComponentPropertyManager::assignValuesFromSCAModel( 
   const RuntimeModel::PropertyPtr& property ) const
{
   const SCAModel::PropertyPtr scaPropertyType = property->scaPropertyType();
   const SCAModel::PropertyValuePtr scaProperty = property->scaProperty();

   //if a <property> element is specified for a component, 
   //we will first try to use its values and not the default ones
   bool useDefaultValues = scaProperty.get() == nullptr;
   if(!useDefaultValues)
   {
      assert(scaProperty);

      //"If more than one property value specification is present, the @source attribute 
      // takes precedence then the @file attribute" (Assembly Spec 1.1, line 1080 f.)

      if( !scaProperty->source().empty() ) //(Assembly Spec 1.1, line 1068 f.)
      {
         handleSourceAttribute(property);   
      }
      else if( !scaProperty->file().empty() ) //(Assembly Spec 1.1, line 1077 f.)
      {  
         handleFileAttribute(property);   
      }
      else if( !scaProperty->value().empty() ) //(Assembly Spec 1.1, line 1001 f.)
      {
         //this should have been validated at generation time
         assert(!scaProperty->isMany());

         property->addValue( scaProperty->value() );            
      }
      else if( !scaProperty->contentElements().empty() ) //(Assembly Spec 1.1, line 1009 f.)
      {
         property->setValues(scaProperty->contentElements());               
      }
      else
      {
         //a <property> element is specified but contains no values, so use the default ones 
         useDefaultValues = true;
      }
   }

   if(useDefaultValues)
   {
      assert(scaPropertyType);
      //this should have been validated at generation time
      assert(!scaPropertyType->isMustSupply());

      if(scaPropertyType->contentElements().empty())
      {         
         const RuntimeModel::ConstComponentPtr component = property->component().lock();
         assert(component);
         const RuntimeModel::ConstCompositePtr composite = component->composite().lock();
         assert(composite);
         ostringstream errorMessage;
         errorMessage << "No default values specified for <property> with @name = '" 
                        << scaPropertyType->name() 
                        << "'. Specified in <property> with @name = '" 
                        << scaPropertyType->name() << "' in <component> with @name = '" 
                        << component->scaComponent()->name() << "' in <composite> with QName '" 
                        << composite->qName().toString() << "'."; 
         throw Exception<Error>( NoDefaultPropertyValuesError, errorMessage.str() );         
      }

      property->setValues(scaPropertyType->contentElements());
   }
}

void ComponentPropertyManager::injectValues( const RuntimeModel::ConstPropertyPtr& property
                                           , void* instance ) const
{
   assert(property);

   if(!property->setterMethod())
      return;   
   
   #define INVOKE_SETTER(Type)  property->isMany() ?invokeSetterManyValues<Type>(property, instance)\
      : invokeSetterSingleValue<Type>(property, instance);
   
   const string xsdType = property->type();
   
   try
   {   
      if( isTreatedAsMany(xsdType) )    
      { 
         property->isMany() ? invokeSetterManyValues<list<string> >(property, instance) 
                            : invokeSetterSingleValue<list<string> >(property, instance);  
      }
      else if  (isStringType(xsdType))       { INVOKE_SETTER(string); } 
      else if  (xsdType == "base64Binary")   { INVOKE_SETTER(char*); }
      else if  (xsdType == "hexBinary")      { INVOKE_SETTER(char*); }
      else if  (xsdType == "boolean")        { INVOKE_SETTER(bool); }
      else if  (xsdType == "byte")           { INVOKE_SETTER(int8_t); }
      else if  (xsdType == "double")         { INVOKE_SETTER(double); }      
      else if  (xsdType == "float")          { INVOKE_SETTER(float); }      
      else if  (xsdType == "int")            { INVOKE_SETTER(int32_t); }
      else if  (xsdType == "long")           { INVOKE_SETTER(int64_t); }
      else if  (xsdType == "short")          { INVOKE_SETTER(int16_t); }
      else if  (xsdType == "unsignedByte")   { INVOKE_SETTER(uint8_t); }
      else if  (xsdType == "unsignedInt")    { INVOKE_SETTER(uint32_t); }
      else if  (xsdType == "unsignedLong")   { INVOKE_SETTER(uint64_t); }
      else if  (xsdType == "unsignedShort")  { INVOKE_SETTER(uint16_t); }
      else
      {  
         //this should have been validated at generation time
         assert(false);
      }   
   }
   catch(std::bad_cast& /*e*/)
   {  
      const RuntimeModel::ConstComponentPtr component = property->component().lock();
      assert(component);
      const RuntimeModel::ConstCompositePtr composite = component->composite().lock();
      assert(composite);

      ostringstream errorMessage;
      errorMessage << "Property value couldn't be casted to the target type: '" << property->type() 
                   << "'. Specified in <property> with @name = '" << property->name() 
                   << "' in <component> with @name = '" << component->scaComponent()->name()
                   << "' in <composite> with QName '" << composite->qName().toString() << "'";
      throw Exception<Error>(PropertyValueCastError, errorMessage.str());
   }

}
