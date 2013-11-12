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

// header
#include "services/TrentinoSystemPreferenceServiceImpl.h"
#include "services/TrentinoSystemSQLitePreferenceImpl.h"

using namespace  Trentino::System;
#include "assert.h"
#include <Poco/Data/Common.h>
#include <Poco/Data/SQLite/Connector.h>

using namespace Poco::Data;

PreferenceServiceImpl::PreferenceServiceImpl()
{
	m_iDBType = 1;//sqlite as the default database
}

PreferenceServiceImpl::~PreferenceServiceImpl()
{
}

Preference* PreferenceServiceImpl::getStore(string PathName)
{
	//open the database, read the nodeinfo table, construct the root Preference node	
	Preference* pSqlPreference = NULL;
	try{
		if(m_iDBType == 1)//sqlite
		{
			SQLite::Connector::registerConnector();
			Session ses("SQLite", PathName);
			do{
				//if the nodeinfo and nodeparams tables not exist, return null
				int iCnt = 0;
				ses << "SELECT COUNT(*) FROM sqlite_master where type='table' and name=:name", into(iCnt), use("NodeInfo"), now;
				if(iCnt <= 0)
				{
					break;
				}
				ses << "SELECT COUNT(*) FROM sqlite_master where type='table' and name=:name", into(iCnt), use("NodeParams"), now;
				if(iCnt <= 0)
				{
					break;
				}
				pSqlPreference = new SQLilePreferenceImpl();
				pSqlPreference->setSQLParams("SQLite", PathName);
				pSqlPreference->setAsRootNode();
			}while(false);
			SQLite::Connector::unregisterConnector();
		}
		else if(m_iDBType == 2)//mysql
		{}
		else if(m_iDBType == 3)//odbc
		{}
	}
	catch(std::exception& ex)
	{
		throw "exception";
	}
	return pSqlPreference;
}

Preference* PreferenceServiceImpl::createStore(string PathName)
{
	//create the database, create the nodeinfo and nodeparams table, 
	//insert the root node, construct the root Preference node
	SQLilePreferenceImpl* pSqlPreference = NULL;
	try{
		if(m_iDBType == 1)//sqlite
		{
			SQLite::Connector::registerConnector();
			Session ses("SQLite", PathName);
			do{
				//if the nodeinfo and nodeparams tables exist, return null or throw exception
				int iCnt = 0;
				ses << "SELECT COUNT(*) FROM sqlite_master where type='table' and name=:name", into(iCnt), use("NodeInfo"), now;
				if(iCnt > 0)
				{
					break;
				}
				ses << "SELECT COUNT(*) FROM sqlite_master where type='table' and name=:name", into(iCnt), use("NodeParams"), now;
				if(iCnt > 0)
				{
					break;
				}
				ses << "BEGIN TRANSACTION", now;
				ses << "CREATE TABLE [NodeInfo] ( \
					   [NodeId] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT, \
					   [NodeParentId] INTEGER  NULL, \
					   [NodeName] NVARCHAR(64)  NULL,\
					   [NodePath] NVARCHAR(512)  NULL,\
					   [DelFlag] INTEGER NULL \
					   );", now;

				ses << "CREATE TABLE [NodeParams] (\
					   [id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,\
					   [NodeId] INTEGER  NOT NULL,\
					   [key] NVARCHAR(64)  NULL,\
					   [value] NVARCHAR(128)  NULL,\
					   [valueType] INTEGER  NULL,\
					   [DelFlag] INTEGER NULL\
					   );", now;
				ses << "COMMIT TRANSACTION", now;
				pSqlPreference = new SQLilePreferenceImpl();
				pSqlPreference->setSQLParams("SQLite", PathName);
				pSqlPreference->setAsRootNode();
			}while(false);
			SQLite::Connector::unregisterConnector();
		}
		else if(m_iDBType == 2)//mysql
		{}
		else if(m_iDBType == 3)//odbc
		{}
	}
	catch(std::exception& ex)
	{
		throw "exception";
	}
	return pSqlPreference;
}

void PreferenceServiceImpl::deleteStore(string PathName)
{
	//delete the whole database
	if(m_iDBType == 1)//sqlite
	{
		//here just only change the db file name
		std::string PathBakName = PathName + ".bak";
		rename(PathName.c_str(), PathBakName.c_str());
	}
	else if(m_iDBType == 2)//mysql
	{}
	else if(m_iDBType == 3)//odbc
	{}
}

void PreferenceServiceImpl::setDBType(int iDBType)
{
	m_iDBType = iDBType;
}
