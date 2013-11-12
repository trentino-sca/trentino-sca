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

#ifndef TrentinoUtilsDataObjectH
#define TrentinoUtilsDataObjectH

//standard
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#ifdef WIN32
   #ifdef UTILS_EXPORTS
      #define DATAOBJECTS_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define DATAOBJECTS_IMPORT_EXPORT __declspec(dllimport)       
   #endif //UTILS_EXPORTS
#else
   #define DATAOBJECTS_IMPORT_EXPORT
#endif //WIN32

namespace Trentino{
   namespace Utils
      {

      class DataObjectImpl;
      typedef const char* Property;
      class DATAOBJECTS_IMPORT_EXPORT DataObject{
      public:
         //construction
      private:
         DataObject();
      public:
         ~DataObject();
         static DataObject newInstance(Property name);
         //services
      public:
         Property name() const;
         DataObject& createDataObject( Property propertyName);
         void setInt( Property propertyName,int& value);
         void setFloat( Property propertyName,float& value);
         void setString( Property propertyName,std::string& value);
         void setBool( Property propertyName, bool value);
         const bool hasValue( Property propertyName, const std::string& type);
         void properties(std::vector<std::string>& result);

         int& getInt( Property propertyName) const;
         float& getFloat( Property propertyName) const;
         std::string& getString( Property propertyName) const;
         bool getBool( Property propertyName) const;
         DataObject& get( Property propertyName) const;
         bool empty() const;
         friend class DataObjectImpl;
         friend struct DataObjectWrapper;
      private:
         boost::shared_ptr<DataObjectImpl> impl;
         }; //class DataObject

      } //namespace RuntimeModel
   } //namespace Trentino

#endif //TrentinoUtilsDataObjectH