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
#include "TrentinoUtilsDataObject.h"

//standrad
#include <map>

//class DataObject

namespace Trentino{
   namespace Utils
      {

      template <typename M, typename V> 
      void mapToVect( const  M & m, V & v )
         {
         for( typename M::const_iterator it = m.begin(); it != m.end(); ++it )
            {
            v.push_back( it->first);
            }
         }

      template<typename T>
      T& find(std::map<Property,T>& map, Property property)
         {
         std::map<Property,T>::iterator iter;
         for(iter = map.begin();iter!=map.end();++iter)
            {
            if(strcmp(iter->first, property)==0)
               {
               return iter->second;
               }
            }
         throw std::runtime_error("Out of bound");
         }

      struct DataObjectWrapper
         {
         DataObject object;
         };

      class DataObjectImpl {
      public:
         DataObjectImpl():mEmpty(true){}
         ~DataObjectImpl(){}
         static DataObject newInstance(Property name);
      public:
         Property name() const;
         DataObject& createDataObject(Property propertyName);
         void setInt(Property propertyName,int& value);
         void setFloat(Property propertyName,float& value);
         void setString(Property propertyName,std::string& value);
         void setBool(Property propertyName, bool value);
         const bool hasValue(Property propertyName, const std::string& type);
         void properties(std::vector<std::string>& result);

         int& getInt(Property propertyName);
         float& getFloat(Property propertyName);
         std::string& getString(Property propertyName);
         bool getBool(Property propertyName);
         DataObject& get(Property propertyName);
         bool empty() const;

      private:
         std::map<Property,DataObjectWrapper> mDataObjects;
         std::map<Property,int> mInts;
         std::map<Property,float> mFloats;
         std::map<Property,std::string> mStrings;
         std::map<Property,bool> mBools;
         Property mName;
         bool mEmpty;
         };

      DataObject DataObjectImpl::newInstance(Property name)
         {
         DataObject obj;
         obj.impl->mName = name;
         return obj;
         }

      Property  DataObjectImpl::name() const
         {
         return mName;
         }

      DataObject& DataObjectImpl::createDataObject(Property propertyName)
         {
         DataObject obj = newInstance(propertyName);
         DataObjectWrapper wrapper={obj};
         mDataObjects.insert(std::pair<Property,DataObjectWrapper>(propertyName,wrapper));
         mEmpty = false;
         return mDataObjects.find(propertyName)->second.object;
         }

      void DataObjectImpl::setInt(Property propertyName,int& value)
         {
         int v = value;
         std::pair<Property,int> val(propertyName,v);
         mInts.insert(val);
         mEmpty = false;
         }

      void DataObjectImpl::setFloat(Property propertyName,float& value)
         {
         mFloats.insert(std::pair<Property,float>(propertyName,value));
         mEmpty = false;
         }

      void DataObjectImpl::setString(Property propertyName,std::string& value)
         {
         mStrings.insert(std::pair<Property,std::string>(propertyName,value));
         mEmpty = false;
         }

      void DataObjectImpl::setBool(Property propertyName, bool value)
         {
         mBools.insert(std::pair<Property,bool>(propertyName,value));
         mEmpty = false;
         }

      const bool DataObjectImpl::hasValue(Property propertyName, const std::string& type)
         {
         if(type == "int")
            {
            return mInts.find(propertyName)!= mInts.end();
            }
         if(type == "float")
            {
            return mFloats.find(propertyName)!= mFloats.end();
            }
         if(type == "string")
            {
            return mStrings.find(propertyName)!= mStrings.end();
            }
         if(type == "bool")
            {
            return mBools.find(propertyName)!= mBools.end();
            }
         if(type == "dataObject")
            {
            return mDataObjects.find(propertyName)!= mDataObjects.end();
            }
         return false;
         }

      void DataObjectImpl::properties(std::vector<std::string>& result){
         mapToVect(mInts,result);
         mapToVect(mFloats,result);
         mapToVect(mStrings,result);
         mapToVect(mBools,result);
         mapToVect(mDataObjects,result);
         }

      int& DataObjectImpl::getInt(Property propertyName) 
         {
         return find(mInts,propertyName);
         }

      float& DataObjectImpl::getFloat(Property propertyName) 
         {
         return find(mFloats,propertyName);
         }

      std::string& DataObjectImpl::getString(Property propertyName) 
         {
         return find(mStrings,propertyName);
         }

      bool DataObjectImpl::getBool(Property propertyName) 
         {
         return find(mBools,propertyName);
         }

      DataObject& DataObjectImpl::get(Property propertyName) 
         {
         return find(mDataObjects,propertyName).object;
         }

      bool DataObjectImpl::empty() const
         {
         return mEmpty;
         }


      //DATAOBJECT

      DataObject::DataObject():impl(new DataObjectImpl())
         {
         }

      DataObject::~DataObject()
         {
          impl.reset();
         }

      DataObject DataObject::newInstance(Property name)
         {
         return DataObjectImpl::newInstance(name);
         }

      //services
      Property DataObject::name() const
         {
         return impl->name();
         }

      DataObject& DataObject::createDataObject(Property propertyName)
         {
         return impl->createDataObject(propertyName);
         }

      void DataObject::setInt(Property propertyName,int& value)
         {
         impl->setInt(propertyName,value);
         }

      void DataObject::setFloat(Property propertyName,float& value)
         {
         impl->setFloat(propertyName,value);
         }

      void DataObject::setString(Property propertyName,std::string& value)
         {
         impl->setString(propertyName,value);
         }

      void DataObject::setBool(Property propertyName, bool value)
         {
         impl->setBool(propertyName,value);
         }

      const bool DataObject::hasValue(Property propertyName,const std::string& type)
         {
         return impl->hasValue(propertyName,type);
         }


      void DataObject::properties(std::vector<std::string>& result){
         impl->properties(result);
         }

      int& DataObject::getInt(Property propertyName) const
         {
         return impl->getInt(propertyName);
         }

      float& DataObject::getFloat(Property propertyName) const
         {
         return impl->getFloat(propertyName);
         }

      std::string& DataObject::getString(Property propertyName) const
         {
         return impl->getString(propertyName);
         }

      bool DataObject::getBool(Property propertyName) const
         {
         return impl->getBool(propertyName);
         }

      DataObject& DataObject::get(Property propertyName) const
         {
         return impl->get(propertyName);
         }

      bool DataObject::empty() const
         {
         return impl->empty();
         }
      }
   }

