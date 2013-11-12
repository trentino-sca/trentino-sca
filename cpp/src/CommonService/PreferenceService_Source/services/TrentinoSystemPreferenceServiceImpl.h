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
#ifndef TrentinoSystemPreferenceServiceImplH
#define TrentinoSystemPreferenceServiceImplH

//standard
#include <string>
#include <vector>
#include <map>

using namespace std;

//specific
#include "TrentinoSystem.h"
#include "TrentinoSystemPreferenceService.h"

namespace Trentino{
	namespace System
	{
		class SYSTEM_IMPORT_EXPORT PreferenceServiceImpl : public PreferenceService 
		{
			//construction
		public:
			//*******************************************************************************************
			//                                  PreferenceService()
			//*******************************************************************************************      
			//! \brief Empty constructor. 
			//*******************************************************************************************
			PreferenceServiceImpl();

			//*******************************************************************************************
			//                                  ~PreferenceService()
			//*******************************************************************************************      
			//! \brief Empty destructor.
			//*******************************************************************************************
			~PreferenceServiceImpl();

			//services
		public:

			//*******************************************************************************************
			//                                       getStore()
			//*******************************************************************************************      
			//! \brief Returns a root Preference from a storage unit.
			//! \param[in] pathName - the path name of the storage(sqlite) or connection parameters.
			//! \return Preference*, the caller must free the memory, otherwise there is memory leak. 
			//! \sa 
			//*******************************************************************************************
			virtual Preference* getStore(string pathName);

			//*******************************************************************************************
			//                                       createStore()
			//*******************************************************************************************      
			//! \brief Returns a root Preference from a storage unit.
			//!        create a new store (for SQLIte store, this would create a new database instance with a root PrefereceElement)
			//! \param[in] pathName - the path name of the storage(sqlite) or connection parameters.
			//! \return Preference*. 
			//! \sa 
			//*******************************************************************************************
			virtual Preference* createStore(string PathName);

			//*******************************************************************************************
			//                                       deleteStore()
			//*******************************************************************************************      
			//! \brief delete a store.
			//! \param[in] pathName - the path name of the storage(sqlite) or connection parameters.
			//! \return void. 
			//! \sa 
			//*******************************************************************************************
			virtual void deleteStore(string PathName);

			//*******************************************************************************************
			//                                       setDBType()
			//*******************************************************************************************      
			//! \brief set the database type, sqlite, mysql....
			//! \param[in] iDBType - the type of db. 1-sqlite 2-mysql 3-odbc
			//! \return void. 
			//! \sa 
			//*******************************************************************************************
			virtual void setDBType(int iDBType);
			//data
		private:
			//! define the db type
			int m_iDBType;
		};
	} //namespace System
} //namespace Trentino

#endif //TrentinoSystemPreferenceServiceImplH
