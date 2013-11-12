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

#ifndef TrentinoReflectionHelpersVariantH
#define TrentinoReflectionHelpersVariantH

#ifdef WIN32
   #ifdef REFLECTIONRUNTIME_EXPORTS
      #define VARIANT_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define VARIANT_IMPORT_EXPORT __declspec(dllimport)       
   #endif //REFLECTIONRUNTIME_EXPORTS
#else
   #define VARIANT_IMPORT_EXPORT
#endif //WIN32


//standard
#include <memory>

//specific
#include "./../../Global/TrentinoGlobal.h"
#include "TrentinoReflectionHelpersListType.h"

namespace Trentino{
namespace Reflection{      
namespace Helpers
{
   //class declaration
   //**********************************************************************************************
   //                              Variant                               
   //**********************************************************************************************
   //! \ingroup ReflectionHelpers.
   //! \brief Container to store values of different types.
   //**********************************************************************************************
   class Variant
   {
   // additional
   public:
      //! Type of variant
      enum Type
      {
         Invalid = 0,            //! Type not defined
         SignedChar = 1,         //! Signed char type
         UnsignedChar = 2,       //! Unsigned char type
         Short = 3,              //! Short type
         UnsignedShort = 4,      //! Unsigned short type
         Bool = 5,               //! Bool type
         Int = 6,                //! Int type
         UnsignedInt = 7,        //! Unsigned type
         Long = 8,               //! Long type
         UnsignedLong = 9,       //! Unsigned long type
         Float = 10,             //! Float type
         Double = 11,            //! Double type
         LongLong = 12,          //! Long long type
         UnsignedLongLong = 13,  //! Unsigned long long type
         VoidPtr = 14,           //! Void ptr type
         ConstCharPtr = 15,      //! Const char ptr type
         List = 16,
         Count                   //! Number of elements
      }; //enum Type

      //! Data container of each type
      union Data
      {
         signed char valueChar;               //! Interpreted as a char
         unsigned char valueUChar;            //! Interpreted as an unsigned char
         short valueShort;                    //! Interpreted as a short
         unsigned short valueUShort;          //! Interpreted as an unsigned short
         bool valueBool;                      //! Interpreted as a bool
         int valueInt;                        //! Interpreted as an int
         unsigned int valueUInt;              //! Interpreted as an unsigned int
         long valueLong;                      //! Interpreted as a long
         unsigned long valueULong;            //! Interpreted as an unsigned long
         float valueFloat;                    //! Interpreted as a float
         double valueDouble;                  //! Interpreted as a double
         long long valueLongLong;             //! Interpreted as a long long
         unsigned long long valueULongLong;   //! Interpreted as an unsigned long long
         void* valuePtr;                      //! Interpreted as a void pointer
         const char* valueConstCharPtr;       //! Interpreted as const char* pointer
         ListType* valueListType;
      }; //union Data

      //construction
   public:
      //*******************************************************************************************
      //                              Variant(signed char)
      //*******************************************************************************************
      //! Constructs Variant with a signed char type.
      //! \param[in] Signed char value to set.
      //*******************************************************************************************
      explicit Variant(signed char val);

      //*******************************************************************************************
      //                              Variant(unsigned char)
      //*******************************************************************************************
      //! Constructs Variant with an unsigned char type.
      //! \param[in] Unsigned char value to set.
      //*******************************************************************************************
      explicit Variant(unsigned char val);

      //*******************************************************************************************
      //                              Variant(short)
      //*******************************************************************************************
      //! Constructs Variant with a short type.
      //! \param[in] Short value to set.
      //*******************************************************************************************
      explicit Variant(short val);

      //*******************************************************************************************
      //                              Variant(unsigned short)
      //*******************************************************************************************
      //! Constructs Variant with an unsigned short type.
      //! \param[in] Unsigned short value to set
      //*******************************************************************************************
      explicit Variant(unsigned short val);

      //*******************************************************************************************
      //                              Variant(bool)
      //*******************************************************************************************
      //! Constructs Variant with a bool type.
      //! \param[in] Bool value to set.
      //*******************************************************************************************
      explicit Variant(bool val);

      //*******************************************************************************************
      //                              Variant(int)
      //*******************************************************************************************
      //! Constructs Variant with an int type.
      //! \param[in] Int value to set.
      //*******************************************************************************************
      explicit Variant(int val);

      //*******************************************************************************************
      //                              Variant(unsigned int)
      //*******************************************************************************************
      //! Constructs Variant with an unsigned int type.
      //! \param[in] Unsigned int value to set.
      //*******************************************************************************************
      explicit Variant(unsigned int val);

      //*******************************************************************************************
      //                              Variant(long)
      //*******************************************************************************************
      //! Constructs Variant with a long type.
      //! \param[in] Long value to set.
      //*******************************************************************************************
      explicit Variant(long val);

      //*******************************************************************************************
      //                              Variant(unsigned long)
      //*******************************************************************************************
      //! Constructs Variant with an unsigned long type.
      //! \param[in] Unsigned long value to set.
      //*******************************************************************************************
      explicit Variant(unsigned long val);

      //*******************************************************************************************
      //                              Variant(float)
      //*******************************************************************************************
      //! Constructs Variant with a float type.
      //! \param[in] Float value to set.
      //*******************************************************************************************
      explicit Variant(float val);

      //*******************************************************************************************
      //                              Variant(double)
      //*******************************************************************************************
      //! Constructs Variant with a double type.
      //! \param[in] Double value to set.
      //*******************************************************************************************
      explicit Variant(double val);

      //*******************************************************************************************
      //                              Variant(long long)
      //*******************************************************************************************
      //! Constructs Variant with a long long type.
      //! \param[in] Long long value to set.
      //*******************************************************************************************
      explicit Variant(long long val);

      //*******************************************************************************************
      //                              Variant(unsigned long long)
      //*******************************************************************************************
      //! Constructs Variant with an unsigned long long type.
      //! \param[in] Unsigned long long value to set.
      //*******************************************************************************************
      explicit Variant(unsigned long long  val);

      //*******************************************************************************************
      //                              Variant(void*)
      //*******************************************************************************************
      //! Constructs Variant with an void*.
      //! \param[in] Void* value to set.
      //*******************************************************************************************
      explicit Variant(void* val);

      //*******************************************************************************************
      //                              Variant(void*)
      //*******************************************************************************************
      //! Constructs Variant with an void*.
      //! \param[in] Void* value to set.
      //*******************************************************************************************
      explicit Variant(const ListTypePtr& val);

      //*******************************************************************************************
      //                              Variant(const char*)
      //*******************************************************************************************
      //! Constructs Variant with an const char*.
      //! \param[in] Const char* value to set.
      //*******************************************************************************************
      explicit Variant(const char* val);

      //*******************************************************************************************
      //                              Variant()
      //*******************************************************************************************
      //! Default constructor.
      //*******************************************************************************************
      Variant();

      //*******************************************************************************************
      //                              Variant(const Variant&)
      //*******************************************************************************************
      //! Copy constructor.
      //! \param[in] Parameter to copy from.
      //*******************************************************************************************
      Variant(const Variant& source);

      //*******************************************************************************************
      //                              ~Variant()
      //*******************************************************************************************
      //! Destructor
      //*******************************************************************************************
      ~Variant() {}

      //operators
   public:
      //*******************************************************************************************
      //                              operator=
      //*******************************************************************************************
      //! Assignment operator
      //! \param[in] parameter to copy from.
      //*******************************************************************************************
      Variant& operator=(const Variant& source);

      //*******************************************************************************************
      //                              operator==
      //*******************************************************************************************
      //! Compare operator
      //! \param[in] Parameter to compare with.
      //*******************************************************************************************
      bool operator==(const Variant& compare) const;

      //services
   public:
      //*******************************************************************************************
      //                              fromSignedChar()
      //*******************************************************************************************
      //! Constructs and sets value and type from signed char value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromSignedChar(signed char val);

      //*******************************************************************************************
      //                              fromUnsignedChar()
      //*******************************************************************************************
      //! Constructs and sets value and type from unsigned char value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromUnsignedChar(unsigned char val);

      //*******************************************************************************************
      //                              fromShort()
      //*******************************************************************************************
      //! Constructs and sets value and type from short value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromShort(short val);

      //*******************************************************************************************
      //                              fromUnsignedShort()
      //*******************************************************************************************
      //! Constructs and sets value and type from unsigned short value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromUnsignedShort(unsigned short val);

      //*******************************************************************************************
      //                              fromBool()
      //*******************************************************************************************
      //! Constructs and sets value and type from bool value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromBool(bool val);

      //*******************************************************************************************
      //                              fromInt()
      //*******************************************************************************************
      //! Constructs and sets value and type from int value.
      //! \param[in] Value to set
      //*******************************************************************************************
      void fromInt(int val);

      //*******************************************************************************************
      //                              fromUnsignedInt()
      //*******************************************************************************************
      //! Constructs and sets value and type from unsigned int value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromUnsignedInt(unsigned int val);

      //*******************************************************************************************
      //                              fromLong()
      //*******************************************************************************************
      //! Constructs and sets value and type from long value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromLong(long val);

      //*******************************************************************************************
      //                              fromUnsignedLong()
      //*******************************************************************************************
      //! Constructs and sets value and type from unsigned long value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromUnsignedLong(unsigned long val);

      //*******************************************************************************************
      //                              fromFloat()
      //*******************************************************************************************
      //! Constructs and sets value and type from float value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromFloat(float val);

      //*******************************************************************************************
      //                              fromDouble()
      //*******************************************************************************************
      //! Constructs and sets value and type from double value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromDouble(double val);

      //*******************************************************************************************
      //                              fromLongLong()
      //*******************************************************************************************
      //! Constructs and sets value and type from long long value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromLongLong(long long val);

      //*******************************************************************************************
      //                              fromUnsignedLongLong()
      //*******************************************************************************************
      //! Constructs and sets value and type from unsigned long long value.
      //! \param[in] Value to set
      //*******************************************************************************************
      void fromUnsignedLongLong(unsigned long long val);

      //*******************************************************************************************
      //                              fromVoidPtr()
      //*******************************************************************************************
      //! Constructs and sets value and type from void ptr value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromVoidPtr(void* val);

      //*******************************************************************************************
      //                              fromConstCharPtr()
      //*******************************************************************************************
      //! Constructs and sets value and type from const char ptr value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromConstCharPtr(const char* val);

      //*******************************************************************************************
      //                              fromListType()
      //*******************************************************************************************
      //! Constructs and sets value and type from ListType value.
      //! \param[in] Value to set.
      //*******************************************************************************************
      void fromListType(const ListTypePtr& val);

      //*******************************************************************************************
      //                              fromList()
      //*******************************************************************************************
      //! Constructs and sets value and type from \sa std::list templat.
      //! \param[in] Value to set.
      //*******************************************************************************************
      template<typename LIST>
      static inline Variant fromList(const LIST& list);

      //*******************************************************************************************
      //                              toSignedChar()
      //*******************************************************************************************
      //! Returns the variant value as a signed char. 
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      signed char toSignedChar() const;

      //*******************************************************************************************
      //                              toUnsignedChar()
      //*******************************************************************************************
      //! Returns the variant value as an unsigned char. 
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      unsigned char toUnsignedChar() const;

      //*******************************************************************************************
      //                              toShort()
      //*******************************************************************************************
      //! Returns the variant value as a short. 
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      short toShort() const;

      //*******************************************************************************************
      //                              toUnsignedShort()
      //*******************************************************************************************
      //! Returns the variant value as an unsigned short. 
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      unsigned short toUnsignedShort() const;

      //*******************************************************************************************
      //                              toBool()
      //*******************************************************************************************
      //! Returns the variant value as a bool. 
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      bool toBool() const;

      //*******************************************************************************************
      //                              toInt()
      //*******************************************************************************************
      //! Returns the variant value as a int. 
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      int toInt() const;

      //*******************************************************************************************
      //                              toUnsignedInt()
      //*******************************************************************************************
      //! Returns the variant value as an unsigned int. 
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      unsigned int toUnsignedInt() const;

      //*******************************************************************************************
      //                              toLong()
      //*******************************************************************************************
      //! Returns the variant value as a long. 
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      long toLong() const;

      //*******************************************************************************************
      //                              toUnsignedLong()
      //*******************************************************************************************
      //! Returns the variant value as an unsigned long. 
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      unsigned long toUnsignedLong() const;

      //*******************************************************************************************
      //                              toFloat()
      //*******************************************************************************************
      //! Returns the variant value as a float
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      float toFloat() const;

      //*******************************************************************************************
      //                              toDouble()
      //*******************************************************************************************
      //! Returns the variant value as a double
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      double toDouble() const;

      //*******************************************************************************************
      //                              toLongLong()
      //*******************************************************************************************
      //! Returns the variant value as a long long
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      long long toLongLong() const;

      //*******************************************************************************************
      //                              toUnsignedLongLong()
      //*******************************************************************************************
      //! Returns the variant value as an unsigned long long
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      unsigned long long toUnsignedLongLong(void);

      //*******************************************************************************************
      //                              toVoidPtr()
      //*******************************************************************************************
      //! Returns the variant value as void pointer
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      void* toVoidPtr() const;

      //*******************************************************************************************
      //                              toConstCharPtr()
      //*******************************************************************************************
      //! Returns the variant value as const char pointer
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      const char* toConstCharPtr() const;

      //*******************************************************************************************
      //                              toListType()
      //*******************************************************************************************
      //! Returns the variant value as ListType shared pointer
      //! Method doesn´t check if correct type is stored, 
      //! no correct type cast conversion is done. 
      //! \return Value to retrieve.
      //*******************************************************************************************
      const ListTypePtr& toListType() const;

      //*******************************************************************************************
      //                              fromTypeName()
      //*******************************************************************************************
      //! Tries to construct correct type from typename
      //! Returns an invalid type if typename could not be determined
      //! Currently not used from external caller. But helper structures should export their
      //! methods.
      //! \param[in] typename to configure the returned variant
      //! \return Value to retrieve.
      //*******************************************************************************************
      VARIANT_IMPORT_EXPORT static Variant fromTypeName(const char* typeName);

      //*******************************************************************************************
      //                              copyFrom()
      //*******************************************************************************************
      //! Copies type and data from a source variant.
      //! \param[in] Variant to copy from.
      //*******************************************************************************************
      void copyFrom(const Variant& source);

      //*******************************************************************************************
      //                              data()
      //*******************************************************************************************
      //! returns A reference of internal variant data representation.
      //! \return Reference of data container.
      //*******************************************************************************************
      const Data& data() const;

      //*******************************************************************************************
      //                              dataPtr()
      //*******************************************************************************************
      //! returns A pointer of internal variant data representation.
      //! \return Pointer of data container.
      //*******************************************************************************************
      const Data* dataPtr() const;

      //*******************************************************************************************
      //                              type()
      //*******************************************************************************************
      //! returns Returns the type of internal variant value type.
      //! \return Type of variant.
      //*******************************************************************************************
      Type type() const;

      //managment
   private:
      //*******************************************************************************************
      //                              invalidate()
      //*******************************************************************************************
      //! Invalidates all internal datamember, used by default constructor.
      //*******************************************************************************************
      void invalidate();

      //data
   private:
      //! Contains data of variant.
      Data mData;
      //! Contains type of variant.
      Type mType;
      //! Contains ListType if available
      ListTypePtr mListType;
   }; //class Variant


   #include "TrentinoReflectionHelpersVariant.inl"

} //namespace Helpers
} //namespace Reflection
} //namespace Helpers


#endif //TrentinoReflectionHelpersVariantH