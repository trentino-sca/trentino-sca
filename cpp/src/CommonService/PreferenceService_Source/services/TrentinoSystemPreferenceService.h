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
#ifndef TrentinoSystemPreferenceServiceH
#define TrentinoSystemPreferenceServiceH

//standard
#include <string>
#include <vector>
#include <map>

using namespace std;

//specific
#include "TrentinoSystem.h"
//#include "TrentinoSystemPreference.h"

namespace Trentino{
	namespace System
	{
		class SYSTEM_IMPORT_EXPORT PreferenceService 
		{
			//services
		public:

			//*******************************************************************************************
			//                                       getStore()
			//*******************************************************************************************      
			//! \brief Returns a root Preference from a storage unit.
			//! \param[in] pathName - the path name of the storage.
			//! \return Preference*. 
			//! \sa 
			//*******************************************************************************************
			virtual Preference* getStore(string pathName) = 0;

			//*******************************************************************************************
			//                                       createStore()
			//*******************************************************************************************      
			//! \brief Returns a root Preference from a storage unit.
			//!        create a new store (for SQLIte store, this would create a new database instance with a root PrefereceElement)
			//! \param[in] pathName - the path name of the storage.
			//! \return Preference*. 
			//! \sa 
			//*******************************************************************************************
			virtual Preference* createStore(string PathName) = 0;

			//*******************************************************************************************
			//                                       deleteStore()
			//*******************************************************************************************      
			//! \brief delete a store.
			//! \param[in] pathName - the path name of the storage.
			//! \return void. 
			//! \sa 
			//*******************************************************************************************
			virtual void deleteStore(string PathName) = 0;

			//*******************************************************************************************
			//                                       setDBType()
			//*******************************************************************************************      
			//! \brief set the database type, sqlite, mysql....
			//! \param[in] iDBType - the type of db. 1-sqlite 2-mysql 3-odbc
			//! \return void. 
			//! \sa 
			//*******************************************************************************************
			virtual void setDBType(int iDBType) = 0;
		};
	} //namespace System
} //namespace Trentino

#endif //TrentinoSystemPreferenceServiceH
