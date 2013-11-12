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
#include "services/TrentinoSystemSQLitePreferenceImpl.h"
using namespace  Trentino::System;

#include <boost/algorithm/string.hpp>

#include <Poco/Data/Common.h>
#include <Poco/Data/SQLite/Connector.h>

using namespace Poco::Data;

SQLilePreferenceImpl::SQLilePreferenceImpl()
{
	mDBType = ""; 
	mDBPath = "";
}

SQLilePreferenceImpl::~SQLilePreferenceImpl()
{
}
SQLilePreferenceImpl::SQLilePreferenceImpl(int iNodeId, string dbType, string dbPath)
{
	try{
		typedef Poco::Tuple<int, std::string, std::string> NodeData;
		typedef std::vector<NodeData> Params;
		NodeData _data;
		Params _params;
		mDBType = dbType;
		mDBPath = dbPath;
		SQLite::Connector::registerConnector();
		Session session(mDBType, mDBPath);
		//select << "SELECT count(*) from NodeInfo where NodeId = :nodeid"
#ifndef DB_DELFLAG
		session << "SELECT NodeParentId, NodeName, NodePath FROM NodeInfo where NodeId = :nodeid and DelFlag = 0", 
			into(_data), use(iNodeId), now;
#else
		session << "SELECT NodeParentId, NodeName, NodePath FROM NodeInfo where NodeId = :nodeid", 
			into(_data), use(iNodeId), now;
#endif

		mNodeId = iNodeId;
		mParentNodeId = _data.get<0>();
		mNodeName = _data.get<1>();
		mNodePathName = _data.get<2>();

		SQLite::Connector::unregisterConnector();
	}
	catch(Poco::OpenFileException& ex)
	{
		//cout<< "OpenFileException exception.\n";
		throw "OpenFileException!";
	}
	catch(std::exception& ex)
	{
		//cout<< "Common exception.\n";
		throw "exception!";
	}
}
SQLilePreferenceImpl::SQLilePreferenceImpl(const SQLilePreferenceImpl& pf)
{
	mNodePathName = pf.mNodePathName;
	mNodeName = pf.mNodeName;
	mPreference = pf.mPreference;
	mNodeId = pf.mNodeId;

	mDBType = pf.mDBType;
	mDBPath = pf.mDBPath;
}

void SQLilePreferenceImpl::operator=(const SQLilePreferenceImpl& pf)
{
	mNodePathName = pf.mNodePathName;
	mNodeName = pf.mNodeName;
	mPreference = pf.mPreference;
	mNodeId = pf.mNodeId;

	mDBType = pf.mDBType;
	mDBPath = pf.mDBPath;
}

string& SQLilePreferenceImpl::absolutePath()
{
	return mNodePathName;
}

vector<string> SQLilePreferenceImpl::childrenNames()
{
	vector<string> vecChild;
	try{
		SQLite::Connector::registerConnector();
		Session session(mDBType, mDBPath);
		if(mIsRootNode)//root node returns all the nodes' name
		{
#ifndef DB_DELFLAG
			session << "SELECT NodeName FROM NodeInfo where DelFlag = 0", 
				into(vecChild), now;
#else
			session << "SELECT NodeName FROM NodeInfo", into(vecChild), now;
#endif
		}
		else
		{
#ifndef DB_DELFLAG
			session << "SELECT NodeName FROM NodeInfo where NodeParentId = :nodeid and DelFlag = 0", 
				into(vecChild), use(mNodeId), now;
#else
			session << "SELECT NodeName FROM NodeInfo where NodeParentId = :nodeid", 
				into(vecChild), use(mNodeId), now;
#endif
		}
		SQLite::Connector::unregisterConnector();
	}
	catch(std::exception& ex)
	{
		//cout<< "Common exception.\n";
		throw "exception!";
	}
	return vecChild;
}

void SQLilePreferenceImpl::clear()
{
	try{
		SQLite::Connector::registerConnector();
		Session session(mDBType, mDBPath);
#ifndef DB_DELFLAG
		session << "update NodeParams set DelFlag = 1 where NodeId = :nodeid", use(mNodeId), now;
#else
		session << "DELETE FROM NodeParams where NodeId = :nodeid", use(mNodeId), now;
#endif
		SQLite::Connector::unregisterConnector();
	}
	catch(std::exception& ex)
	{
		//cout<< "Common exception.\n";
		throw "exception!";
	}
}

void SQLilePreferenceImpl::flush()
{
	try{
		SQLite::Connector::registerConnector();
		Session session(mDBType, mDBPath);
		session << "BEGIN TRANSACTION", now;
		for(VecNodeParams::iterator iter = mPreference.begin(); iter != mPreference.end(); iter++)
		{
			NodeParam _param = *iter;
			int iCnt = 0;
			std::string sValue;
#ifndef DB_DELFLAG
			session << "SELECT count(*) FROM NodeParams where NodeId = :nodeid and key = :key and DelFlag = 0", 
				into(iCnt), use(mNodeId), use(_param.sKey), now;
			if(iCnt > 0)
			{
				//update
				session << "update NodeParams set value = :value where NodeId = :nodeid and key = :key",
					use(_param.sValue), use(mNodeId), use(_param.sKey), now;
			}
			else
			{
				//insert
				session << "INSERT INTO NodeParams VALUES(NULL, :nodeid, :key, :value, :valuetype, 0)",
					use(mNodeId), use(_param.sKey), use(_param.sValue), use(_param.iType), now; 
			}
#else
			session << "SELECT count(*) FROM NodeParams where NodeId = :nodeid and key = :key", 
				into(iCnt), use(mNodeId), use(_param.sKey), now;
			if(iCnt > 0)
			{
				//update
				session << "update NodeParams set value = :value where NodeId = :nodeid and key = :key",
					use(_param.sValue), use(mNodeId), use(_param.sKey), now;
			}
			else
			{
				//insert
				session << "INSERT INTO NodeParams VALUES(NULL, :nodeid, :key, :value, :valuetype)",
					use(mNodeId), use(_param.sKey), use(_param.sValue), use(_param.iType), now; 
			}
#endif
		}
		session << "COMMIT TRANSACTION", now;

		mPreference.empty();
		SQLite::Connector::unregisterConnector();
	}
	catch(std::exception& ex)
	{
		//cout<< "Common exception.\n";
		throw "exception!";
	}
}

std::string SQLilePreferenceImpl::getString(string key, std::string def)
{
	std::string rev = def;
	try{
		SQLite::Connector::registerConnector();
		Session session(mDBType, mDBPath);
		int iCnt = 0;

#ifndef DB_DELFLAG
		session << "SELECT count(*) FROM NodeParams where NodeId = :nodeid and key = :key and valueType = :type and DelFlag = 0", 
			into(iCnt), use(mNodeId), use(key), use(15), now;
#else
		session << "SELECT count(*) FROM NodeParams where NodeId = :nodeid and key = :key and valueType = :type", 
			into(iCnt), use(mNodeId), use(key), use(15), now;
#endif
		if(iCnt > 0)
		{
#ifndef DB_DELFLAG
			session << "SELECT value FROM NodeParams where NodeId = :nodeid and key = :key and valueType = :type and DelFlag = 0", 
				into(rev), use(mNodeId), use(key), use(15), now;
#else
			session << "SELECT value FROM NodeParams where NodeId = :nodeid and key = :key and valueType = :type", 
				into(rev), use(mNodeId), use(key), use(15), now;
#endif
		}
	}
	catch(std::exception& ex)
	{
		//cout<< "Common exception.\n";
		throw "exception!";
	}
	return rev;
}

template<class T> 
void convertFromString(T &value, const std::string &s) {
  std::stringstream ss(s);
  ss >> value;
}
template<class T> 
std::string ConvertToString(T value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

void SQLilePreferenceImpl::putString(string key, string value)
{
	NodeParam _param;
	_param.iType = 15;
	_param.sKey = key;
	_param.sValue = value;
	mPreference.push_back(_param);
}

vector<string> SQLilePreferenceImpl::keys()
{
	vector<string> vecKey;
	try{
		SQLite::Connector::registerConnector();
		Session session(mDBType, mDBPath);
#ifndef DB_DELFLAG
		session << "SELECT key FROM NodeParams where NodeId = :nodeid and DelFlag = 0", into(vecKey), use(mNodeId), now;
#else
		session << "SELECT key FROM NodeParams where NodeId = :nodeid", into(vecKey), use(mNodeId), now;
#endif
		SQLite::Connector::unregisterConnector();
	}
	catch(std::exception& ex)
	{
		//cout<< "Common exception.\n";
		throw "exception!";
	}
	return vecKey;
}

string& SQLilePreferenceImpl::name()
{
	return mNodeName;
}

SQLilePreferenceImpl* SQLilePreferenceImpl::parent()
{
	SQLilePreferenceImpl* pSqlPreference = NULL;
	if(mParentNodeId > 0)
	{
		pSqlPreference = new SQLilePreferenceImpl(mParentNodeId, mDBType, mDBPath);
	}
	return pSqlPreference;
}

void SQLilePreferenceImpl::remove(string& key)
{
	try{
		SQLite::Connector::registerConnector();
		Session session(mDBType, mDBPath);
#ifndef DB_DELFLAG
		session << "update NodeParams set DelFlag = 1 where NodeId = :nodeid and key = :key", 
			use(mNodeId), use(key), now;
#else
		session << "DELETE FROM NodeParams where NodeId = :nodeid and key = :key", 
			use(mNodeId), use(key), now;
#endif
		SQLite::Connector::unregisterConnector();
	}
	catch(std::exception& ex)
	{
		//cout<< "Common exception.\n";
		throw "exception!";
	}
}

void SQLilePreferenceImpl::removeChildNode(int iNodeId)
{
	try{
		SQLite::Connector::registerConnector();
		Session session(mDBType, mDBPath);
		session << "BEGIN TRANSACTION", now;

		//remove all children nodes
		std::vector<int> vecid;
#ifndef DB_DELFLAG
		session << "SELECT NodeId, NodeName, NodePath FROM NodeInfo where NodeParentId = :nodeid and DelFlag = 0", 
			into(vecid), use(iNodeId), now;
		for(std::vector<int>::iterator iter = vecid.begin(); iter != vecid.end(); iter++)
		{
			removeChildNode(*iter);
		}
		session << "update NodeParams set DelFlag = 1 where NodeId = :nodeid", use(iNodeId), now;
		session << "update NodeInfo set DelFlag = 1 where NodeId = :nodeid", use(iNodeId), now;
#else
		session << "SELECT NodeId, NodeName, NodePath FROM NodeInfo where NodeParentId = :nodeid", 
			into(vecid), use(iNodeId), now;
		for(std::vector<int>::iterator iter = vecid.begin(); iter != vecid.end(); iter++)
		{
			removeChildNode(*iter);
		}
		session << "DELETE FROM NodeParams where NodeId = :nodeid", use(iNodeId), now;
		session << "DELETE FROM NodeInfo where NodeId = :nodeid", use(iNodeId), now;
#endif

		session << "COMMIT TRANSACTION", now;
		SQLite::Connector::unregisterConnector();
	}
	catch(std::exception& ex)
	{
		//cout<< "Common exception.\n";
		throw "exception!";
	}
}

void SQLilePreferenceImpl::removeNode()
{
	removeChildNode(mNodeId);
}

void SQLilePreferenceImpl::sync()
{
	flush();
}

SQLilePreferenceImpl* SQLilePreferenceImpl::node(string pathName)
{
	int iParentNodeId = 0;
	int iTmpNodeId = -1;
	int iNodeId = -1;
	int iLoopCnt = 0;

	try{
		SQLite::Connector::registerConnector();
		Session session(mDBType, mDBPath);
		session << "BEGIN TRANSACTION", now;
#ifndef DB_DELFLAG
		session << "SELECT NodeId FROM NodeInfo where NodePath = :path and DelFlag = 0", into(iNodeId), use(pathName), now;
#else
		session << "SELECT NodeId FROM NodeInfo where NodePath = :path", into(iNodeId), use(pathName), now;
#endif
		//create the node and all its ancestor nodes if not exist.
		//if nodeid exists, init the Preference object.
		if(iNodeId < 0) 
		{
			//create all ancestor nodes if they don't exist.
			std::vector<std::string> str_list;
			std::string strTmpPathName = pathName;
			int comma_n = 0;
			do
			{
				std::string tmp_s = "";
				comma_n = strTmpPathName.rfind( "/" );
				if( 0 >= comma_n )
				{
					break;
				}
				tmp_s = strTmpPathName.substr( 0, comma_n );
				strTmpPathName.erase( comma_n, strTmpPathName.length() );
				str_list.push_back( tmp_s );
			}while(true);

			for (vector<string>::reverse_iterator iter = str_list.rbegin();
				iter != str_list.rend(); ++iter)
			{
				iTmpNodeId = -1;
#ifndef DB_DELFLAG
		session << "SELECT NodeId FROM NodeInfo where NodePath = :path and DelFlag = 0", into(iTmpNodeId), use(*iter), now;
#else
		session << "SELECT NodeId FROM NodeInfo where NodePath = :path", into(iTmpNodeId), use(*iter), now;
#endif

				while(iTmpNodeId == -1 && iLoopCnt < 3)
				{
					std::string sNodeName = (*iter).substr( (*iter).rfind("/")+1, (*iter).length() );
#ifndef DB_DELFLAG
					session << "INSERT INTO NodeInfo VALUES(NULL, :NodeParentId, :NodeName, :NodePath, 0)", 
						use(iParentNodeId), use(sNodeName), use(*iter), now;
					session << "SELECT NodeId FROM NodeInfo where NodePath = :path and DelFlag = 0", into(iTmpNodeId), use(*iter), now;
#else
					session << "INSERT INTO NodeInfo VALUES(NULL, :NodeParentId, :NodeName, :NodePath)", 
						use(iParentNodeId), use(sNodeName), use(*iter), now;
					session << "SELECT NodeId FROM NodeInfo where NodePath = :path", into(iTmpNodeId), use(*iter), now;
#endif
					iLoopCnt++;
				}
				iParentNodeId = iTmpNodeId;
				assert(iParentNodeId >= 0);
			}

			//create current node if it doesn't exist.
			iLoopCnt = 0;
			//insert 3 times to ensure success or assert(it will be replaced by throwing exception)
			while(iNodeId == -1 && iLoopCnt < 3)
			{
				std::string sNodeName = pathName.substr( pathName.rfind("/")+1, pathName.length() );
#ifndef DB_DELFLAG
				session << "INSERT INTO NodeInfo VALUES(NULL, :NodeParentId, :NodeName, :NodePath, 0)", 
					use(iParentNodeId), use(sNodeName), use(pathName), now;
				session << "SELECT NodeId FROM NodeInfo where NodePath = :path and DelFlag = 0", into(iNodeId), use(pathName), now;
#else
				session << "INSERT INTO NodeInfo VALUES(NULL, :NodeParentId, :NodeName, :NodePath)", 
					use(iParentNodeId), use(sNodeName), use(pathName), now;
				session << "SELECT NodeId FROM NodeInfo where NodePath = :path", into(iNodeId), use(pathName), now;
#endif
				iLoopCnt++;
			}
		}
		session << "COMMIT TRANSACTION", now;
		SQLite::Connector::unregisterConnector();

		assert(iNodeId >= 0);
	}
	catch(Poco::OpenFileException& ex)
	{
		//cout<< "OpenFileException exception.\n";
		throw "OpenFileException!";
	}
	catch(std::exception& ex)
	{
		//cout<< "Common exception.\n";
		throw "exception!";
	}
	SQLilePreferenceImpl* pSqlPreference = new SQLilePreferenceImpl(iNodeId, mDBType, mDBPath);
	return pSqlPreference;
}

bool SQLilePreferenceImpl::nodeExists(string pathName)
{
	int iCnt = 0;
	try{
		SQLite::Connector::registerConnector();

		Session session(mDBType, mDBPath);
#ifndef DB_DELFLAG
		session << "SELECT count(*) FROM NodeInfo where NodePath = :path and DelFlag = 0", into(iCnt), use(pathName), now;
#else
		session << "SELECT count(*) FROM NodeInfo where NodePath = :path", into(iCnt), use(pathName), now;
#endif
		
		SQLite::Connector::unregisterConnector();
	}
	catch(Poco::OpenFileException& ex)
	{
		//cout<< "OpenFileException exception.\n";
		throw "OpenFileException!";
	}
	catch(std::exception& ex)
	{
		//cout<< "Common exception.\n";
		throw "exception!";
	}
	if(iCnt > 0)
		return true;
	else
		return false;
}

template<typename T>
T get(string dbType, string dbPath, int iNodeid, string key, T def)
{
	T rev = def;
	try{
		SQLite::Connector::registerConnector();
		Session session(dbType, dbPath);
		int iCnt = 0;
#ifndef DB_DELFLAG
		session << "SELECT count(*) FROM NodeParams where NodeId = :nodeid and key = :key and DelFlag = 0", 
			into(iCnt), use(iNodeid), use(key), now;
#else
		session << "SELECT count(*) FROM NodeParams where NodeId = :nodeid and key = :key", 
			into(iCnt), use(iNodeid), use(key), now;
#endif

		if(iCnt > 0)
		{
			int iValueType = 0;
			std::string sValue;

#ifndef DB_DELFLAG
			session << "SELECT valueType, value FROM NodeParams where NodeId = :nodeid and key = :key and DelFlag = 0", 
				into(iValueType), into(sValue), use(iNodeid), use(key), now;
#else
			session << "SELECT valueType, value FROM NodeParams where NodeId = :nodeid and key = :key", 
				into(iValueType), into(sValue), use(iNodeid), use(key), now;
#endif

			std::stringstream ss(sValue);
			ss >> rev;
		}

		SQLite::Connector::unregisterConnector();
	}
	catch(std::exception& ex)
	{
		//cout<< "Common exception.\n";
		throw "exception!";
	}
	return rev;
}

template<typename T> 
void put(NodeParam& _param, string key, T value)
{
	std::string sType = typeid(T).name();//"int"
	if(boost::iequals(sType, "int"))
	{
		_param.iType = 6;
		_param.sKey = key;
		_param.sValue = ConvertToString(value);
	}
	else if(boost::iequals(sType, "long"))
	{
		_param.iType = 8;
		_param.sKey = key;
		_param.sValue = ConvertToString(value);
	}
	else if(boost::iequals(sType, "float"))
	{
		_param.iType = 10;
		_param.sKey = key;
		_param.sValue = ConvertToString(value);
	}
	else if(boost::iequals(sType, "double"))
	{
		_param.iType = 11;
		_param.sKey = key;
		_param.sValue = ConvertToString(value);
	}
	else if(boost::iequals(sType, "bool"))
	{
		_param.iType = 5;
		_param.sKey = key;
		_param.sValue = ConvertToString(value);
	}
}

int SQLilePreferenceImpl::getInt(string key, int def)
{
	int rev;
	rev = get<int>(mDBType, mDBPath, mNodeId, key, def);
	return rev;
}

float SQLilePreferenceImpl::getFloat(string key, float def)
{
	float rev;
	rev = get<float>(mDBType, mDBPath, mNodeId, key, def);
	return rev;
}

double SQLilePreferenceImpl::getDouble(string key, double def)
{
	double rev;
	rev = get<double>(mDBType, mDBPath, mNodeId, key, def);
	return rev;
}
long SQLilePreferenceImpl::getLong(string key, long def)
{
	long rev;
	rev = get<long>(mDBType, mDBPath, mNodeId, key, def);
	return rev;
}

void SQLilePreferenceImpl::putInt(string key, int value)
{
	NodeParam _param;
	put<int>(_param, key, value);
	mPreference.push_back(_param);
}

void SQLilePreferenceImpl::putFloat(string key, float value)
{
	NodeParam _param;
	put<float>(_param, key, value);
	mPreference.push_back(_param);
}

void SQLilePreferenceImpl::putDouble(string key, double value)
{
	NodeParam _param;
	put<double>(_param, key, value);
	mPreference.push_back(_param);
}

void SQLilePreferenceImpl::putLong(string key, long value)
{
	NodeParam _param;
	put<long>(_param, key, value);
	mPreference.push_back(_param);
}
