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

#ifndef TrentinoCoreExceptionH
#define TrentinoCoreExceptionH

//baseclass
#include <stdexcept>

namespace Trentino{
namespace Core
{
   template<class T>
   class Exception : public std::runtime_error
   {
      //construction
   public:
      virtual ~Exception() throw();
      Exception( const T& data, const std::string& what);      

      //operators
   private:
      void operator=(const Exception&);

      //services
   public:
      const T& data() const;
      
      //data
   private:
      const T mData;
   }; //class Exception

   #include "TrentinoCoreException.inl" 

} //namespace Core
} //namespace Trentino 

#endif //TrentinoCoreExceptionH

