// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2012 by Siemens AG. All rights reserved.
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

#ifndef TrentinoExampleBuilderLoggerFileH
#define TrentinoExampleBuilderLoggerFileH
#include <string>

namespace Trentino{
namespace Example{
namespace ValidContribution1
{
   //class declaration
   //**********************************************************************************************
   //                             LogFile
   //**********************************************************************************************
   //! LogFile interface testcode
   //**********************************************************************************************
   class LoggerFile
   {
		public:
			virtual void writeFile(std::string logMsg) = 0;

	};//class LogFile

}//namespace ValidContribution1
}//namespace Example
}//namespace Trentino

#endif //TrentinoExampleBuilderLoggerFileH