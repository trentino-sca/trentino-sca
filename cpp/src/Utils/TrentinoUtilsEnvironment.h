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

#ifndef TrentinoUtilsEnvironmentH
#define TrentinoUtilsEnvironmentH

//standard
#include <string>

#ifdef WIN32
   #ifdef UTILS_EXPORTS
      #define ENVIRONMENT_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define ENVIRONMENT_IMPORT_EXPORT __declspec(dllimport)       
   #endif
#else
   #define ENVIRONMENT_IMPORT_EXPORT 
#endif

namespace Trentino{
namespace Utils{
//*************************************************************************************************
//                                     namespace Environment
//*************************************************************************************************
//! \ingorup Utils
//*************************************************************************************************
namespace Environment
{
   //**********************************************************************************************
   //                                     makeDLLName()
   //**********************************************************************************************
   //! \brief Converts a dynamic or shared library base (root) name to a platform specific 
   //!        representation.
   //!
   //! \return 
   //!  - on windows: <tt><baseName>.dll</tt>
   //!  - on other platforms: <tt>lib<baseName>.so</tt>
   //**********************************************************************************************
   std::string makeDLLName(const std::string& baseName);

   //**********************************************************************************************
   //                                     executablePath()
   //**********************************************************************************************  
   //! \brief Returns the physical path to the current executable.
   //!
   //! \return Physical path to the current executable.
   //! \throw std::runtime_error If an error occures.
   //! \note The returned path is not the working directory of the current executable but the 
   //!       physical path to the location of the executable file.      
   //**********************************************************************************************
   ENVIRONMENT_IMPORT_EXPORT std::string executablePath();
   
   inline std::string makeDLLName(const std::string& baseName)
   {
      #ifdef WIN32
         return baseName + ".dll";
      #else
         return "lib" + baseName + ".so";
      #endif 
   }

} //namespace Environment
} //namespace Utils
} //namespace Trentino

#endif //TrentinoUtilsEnvironmentH