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
#include "TrentinoDiscoveryUtil.h"
//standart

#include <sys/timeb.h>

//#pragma warning(push)
//#pragma warning(disable:4996)
//#include <sstream>
//#include <boost/uuid/uuid.hpp>            // uuid class
//#include <boost/uuid/uuid_generators.hpp> // generators
//#include <boost/uuid/uuid_io.hpp>
//#pragma warning(pop)

using namespace Trentino::Discovery;


int DiscoveryUtil::GetMilliCount()
{
   // Something like GetTickCount but portable
   // It rolls over every ~ 12.1 days (0x100000/24/60/60)
   // Use GetMilliSpan to correct for rollover
   timeb tb;

   ftime( &tb );

   int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;

   return nCount;
}

int DiscoveryUtil::GetMilliSpan(int nTimeStart)
{
   int nSpan = GetMilliCount() - nTimeStart;

   if ( nSpan < 0 )
   {
      nSpan += 0x100000 * 1000;
   }
   return nSpan;
}
