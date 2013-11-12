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

#ifndef TrentinoGlobalH
#define TrentinoGlobalH
#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif

#if( defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR < 5)) || \
     defined _MSC_VER && (_MSC_VER < 1600))
  //! defines nullptr, use this expression instead of 0 or NULL
   #ifndef nullptr
      #define nullptr 0
   #endif //nullptr   

   #include <boost/cstdint.hpp>
   using boost::int8_t;
   using boost::int16_t;
   using boost::int32_t;
   using boost::int64_t;
   using boost::int_fast8_t;
   using boost::int_fast16_t;
   using boost::int_fast32_t;
   using boost::int_fast64_t;
   using boost::int_least8_t;
   using boost::int_least16_t;
   using boost::int_least32_t;
   using boost::int_least64_t;
   using boost::intmax_t;   
   using boost::uint8_t;
   using boost::uint16_t;
   using boost::uint32_t;
   using boost::uint64_t;   
   using boost::uint_fast8_t;
   using boost::uint_fast16_t;
   using boost::uint_fast32_t;
   using boost::uint_fast64_t;
   using boost::uint_least8_t;
   using boost::uint_least16_t;
   using boost::uint_least32_t;
   using boost::uint_least64_t;
   using boost::uintmax_t;
#elif(defined __GNUC__ || defined _MSC_VER )
    #include <cstdint>  
#else
   //unsupported platform
   COMPILETIME_ASSERT(false);
#endif

//*******************************************************************************************
//                                     COUNT_OF()                               
//*******************************************************************************************
//! \brief Counts elements of array
//! \param[in] Elementname/array to count
//*******************************************************************************************
#define COUNT_OF(ELEMENT) (sizeof(ELEMENT) / sizeof(ELEMENT[0]))

//*******************************************************************************************
//                                     COMPILETIME_ASSERT()                               
//*******************************************************************************************
//! \brief Throws a compiletime assert
//! \param[in] expression to show
//*******************************************************************************************
#define COMPILETIME_ASSERT(expression) typedef char __C_ASSERT__[(expression) ? 1 : -1];

//*******************************************************************************************
//                                  WINDOWS SPECIFIC DEFINITIONS                               
//*******************************************************************************************
#ifdef WIN32
   #define TRENTINO_STDCALL __stdcall 
   #define TRENTINO_CDECL __cdecl
   #define TRENTINO_DLLEXPORT __declspec(dllexport)
#else
   #define TRENTINO_STDCALL
   #define TRENTINO_CDECL 
   #define TRENTINO_DLLEXPORT
#endif

#ifdef __GNUC__
   #define sprintf_s(buffer, bufferSize, stringBuffer, ...)(sprintf(buffer, stringBuffer, __VA_ARGS__))
   //! \todo gcc variant of strerror_s? strerror_r ?
   #define strerror_s(buffer, bufferSize, errNum) strerror(errNum)
   #define strcpy_s(source, bufferSize, dest) strcpy(source, dest)
#endif

#endif //TrentinoGlobalH
