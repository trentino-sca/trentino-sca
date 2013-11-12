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

inline std::string DynamicLibrary::filePath() const
{
   return mFilePath;
}

//idea from: 
//http://wcqtff.willcodejoomlaforfood.de/stl-boost/dll-loader-loadlibrary-getprocaddress-freelibrary.html
//(23.03.11)
template<typename Func>
Func DynamicLibrary::functionAddress(const std::string& funcName) const
{
   // Old code, to-be-removed after test
   // Func func = reinterpret_cast<Func>(getProcAddress(funcName));

   union
   {
      Func funcPtr;
      void* objPtr;
   } u;

   u.objPtr = getProcAddress(funcName);
   u.funcPtr = reinterpret_cast<Func>(u.funcPtr);

   return u.funcPtr;
}
