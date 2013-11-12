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

inline const std::string& InvocationData::operation()  const 
   {
   return mOperation;
   }

inline void InvocationData::setOperation(const std::string& operation)
   {
   mOperation = operation;
   }

inline const InvocationData::Parameters& InvocationData::parameters() const
   {
   return mParameters;
   }

inline void InvocationData::setParameters(const InvocationData::Parameters& params)
   {
   mParameters = params;
   }

inline const std::string& InvocationData::targetService() const 
   {

   return mTargetService;
   }

inline void InvocationData::setTargetService(const std::string& targetService)
   {
   mTargetService = targetService;
   }


inline   const std::string& InvocationData::targetComponent() const
   {
   return mTargetComponent;
   }


inline  void InvocationData::setTargetComponent(const std::string& componentName)
   {
   mTargetComponent = componentName;
   }
