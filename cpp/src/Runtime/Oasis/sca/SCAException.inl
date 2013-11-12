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

inline
SCAException::SCAException() : mLineNumber (0) 
{
}

inline
SCAException::SCAException(const char* eClassName, const char* messageText, 
                           const char* fileName, unsigned long lineNumber,
                           const char* functionName) 
                           : mEClassName(eClassName), mMessageText(messageText),
                             mLineNumber(lineNumber)

{
   if(fileName != nullptr)
   {
      mFileName = fileName;
   }

   if(functionName != nullptr)
   {
      mFunctionName = functionName;
   }
}

inline
const char* SCAException::getEClassName() const
{
   return mEClassName.c_str();
}

inline
const char* SCAException::getMessageText() const
{
   return mMessageText.c_str();
}

inline
const char* SCAException::getFileName() const
{
   return mFileName.c_str();
}

inline
unsigned long SCAException::getLineNumber() const
{
   return mLineNumber;
}

inline
const char* SCAException::getFunctionName() const
{
   return mFunctionName.c_str();
}
