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


inline void Variant::fromSignedChar(signed char val)
{
   mType = SignedChar;
   mData.valueULongLong = 0; //clear
   mData.valueChar = val;
}

inline void Variant::fromUnsignedChar(unsigned char val)
{
   mType = UnsignedChar;
   mData.valueULongLong = 0; //clear
   mData.valueUChar = val;
}

inline void Variant::fromShort(short val)
{
   mType = Short;
   mData.valueULongLong = 0; //clear
   mData.valueShort = val;
}

inline void Variant::fromUnsignedShort(unsigned short val)
{
   mType = UnsignedShort;
   mData.valueULongLong = 0; //clear
   mData.valueUShort = val;
}

inline void Variant::fromBool(bool val)
{
   mType = Bool;
   mData.valueULongLong = 0; //clear
   mData.valueBool = val;
}

inline void Variant::fromInt(int val)
{
   mType = Int;
   mData.valueULongLong = 0; //clear
   mData.valueInt = val;
}

inline void Variant::fromUnsignedInt(unsigned int val)
{
   mType = UnsignedInt;
   mData.valueULongLong = 0; //clear
   mData.valueUInt = val;
}

inline void Variant::fromLong(long val)
{
   mType = Long;
   mData.valueULongLong = 0; //clear
   mData.valueLong = val;
}

inline void Variant::fromUnsignedLong(unsigned long val)
{
   mType = UnsignedLong;
   mData.valueULongLong = 0; //clear
   mData.valueULong = val;
}

inline void Variant::fromFloat(float val)
{
   mType = Float;
   mData.valueULongLong = 0; //clear
   mData.valueFloat = val;
}

inline void Variant::fromDouble(double val)
{
   mType = Double;
   mData.valueDouble = val;
}

inline void Variant::fromLongLong(long long val)
{
   mType = LongLong;
   mData.valueLongLong = val;
}

inline void Variant::fromUnsignedLongLong(unsigned long long val)
{
   mType = UnsignedLongLong;
   mData.valueULongLong = val;
}

inline void Variant::fromVoidPtr(void* val)
{
   mType = VoidPtr;
   mData.valueULongLong = 0; //clear, 64bit env not neccessary
   mData.valuePtr = val;
}

inline void Variant::fromConstCharPtr(const char* val)
{
   mType = ConstCharPtr;
   mData.valueULongLong = 0; //clear, 64bit env not neccessary
   mData.valueConstCharPtr = val;
}

inline void Variant::fromListType(const ListTypePtr& val)
{
   mListType = val;
   mType = List;
   mData.valueULongLong = 0; //clear, 64bit env not neccessary

   // should be safe, we store an extra shared pointer here for reference
   mData.valueListType = val.get();
}

template<typename LIST>
inline Variant Variant::fromList(const LIST& list)
{
   Variant variant(ListWrapper<LIST>(list).listType());
   return variant;
}

inline signed char Variant::toSignedChar() const
{
   return mData.valueChar;
}

inline unsigned char Variant::toUnsignedChar() const
{
   return mData.valueUChar;
}

inline short Variant::toShort() const
{
   return mData.valueShort;
}

inline unsigned short Variant::toUnsignedShort() const
{
   return mData.valueUShort;
}

inline bool Variant::toBool() const
{
   return mData.valueBool;
}

inline int Variant::toInt() const
{
   return mData.valueInt;
}

inline unsigned int Variant::toUnsignedInt() const
{
   return mData.valueUInt;
}

inline long Variant::toLong() const
{
   return mData.valueLong;
}

inline unsigned long Variant::toUnsignedLong() const
{
   return mData.valueULong;
}

inline float Variant::toFloat() const
{
   return mData.valueFloat;
}

inline double Variant::toDouble() const
{
   return mData.valueDouble;
}

inline long long Variant::toLongLong() const
{
   return mData.valueLongLong;
}

inline unsigned long long Variant::toUnsignedLongLong(void)
{
   return mData.valueULongLong;
}

inline void* Variant::toVoidPtr() const
{
   return mData.valuePtr;
}

inline const char* Variant::toConstCharPtr() const
{
   return mData.valueConstCharPtr;
}

inline const ListTypePtr& Variant::toListType() const
{
   return mListType;
}

inline void Variant::copyFrom(const Variant& source)
{
   if(mType != List)
   {
      memcpy(&mData, &source.mData, sizeof(mData));
      mListType.reset();
   }
   
   if(source.type() == List)
   {
      mListType = source.mListType;
      mData.valueListType = mListType.get();
   }

   mType = source.mType;
}

inline Variant& Variant::operator=(const Variant& source)
{
   copyFrom(source);
   return *this;
}

inline Variant::Variant()
{
   invalidate();
}

inline Variant::Variant(const Variant& source)
{
   invalidate();
   copyFrom(source);
}

inline const Variant::Data& Variant::data() const
{
   return mData;
}

inline const Variant::Data* Variant::dataPtr() const
{
   return &mData;
}

inline Variant::Type Variant::type() const
{
   return mType;
}


inline Variant::Variant(signed char val)
{
   fromSignedChar(val);
}

inline Variant::Variant(unsigned char val)
{
   fromUnsignedChar(val);
}

inline Variant::Variant(short val)
{
   fromShort(val);
}

inline Variant::Variant(unsigned short val)
{
   fromUnsignedShort(val);
}

inline Variant::Variant(bool val)
{
   fromBool(val);
}

inline Variant::Variant(int val)
{
   fromInt(val);
}

inline Variant::Variant(unsigned int val)
{
   fromUnsignedInt(val);
}

inline Variant::Variant(long val)
{
   fromLong(val);
}

inline Variant::Variant(unsigned long val)
{
   fromUnsignedLong(val);
}

inline Variant::Variant(float val)
{
   fromFloat(val);
}

inline Variant::Variant(double val)
{
   fromDouble(val);
}

inline Variant::Variant(long long val)
{
   fromLongLong(val);
}

inline Variant::Variant(unsigned long long  val)
{
   fromUnsignedLongLong(val);
}

inline Variant::Variant(void* val)
{
   fromVoidPtr(val);
}

inline Variant::Variant(const char* val)
{
   fromConstCharPtr(val);
}

inline Variant::Variant(const ListTypePtr& val)
{
   fromListType(val);
}

inline void Variant::invalidate()
{
   mData.valueULongLong = 0;
   mType = Invalid;
}

//operators
inline bool Variant::operator==(const Variant& compare) const
{
   if(mType == compare.mType)
   {
      if(mType != ConstCharPtr)
      {
         return (memcmp(&mData, &compare.mData, sizeof(mData)) == 0);
      }
      else
      {
         return (strcmp(mData.valueConstCharPtr, compare.mData.valueConstCharPtr) == 0);
      }
   }
   return false;
}

