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


#include "TrentinoExampleHelloWorldRemoteHelloWorldImpl.h"


using namespace Trentino::Example::HelloWorldRemote;

//class HelloWorldImpl

HelloWorldImpl::HelloWorldImpl()
{
}
HelloWorldImpl::~HelloWorldImpl()
{
}

std::string HelloWorldImpl::hello (const std::string& name, const HelloWorld::MessageType& messageType)
{
  std::string result("");
  switch (messageType){
  case HelloWorld::MessageType::GOOD_MORNING:
  result+="GOOD_MORNING ";
  case HelloWorld::MessageType::GOOD_AFTERNOON:
  result+="GOOD_AFTERNOON";
  case HelloWorld::MessageType::GOOD_EVENING:
  result+="GOOD_EVENING ";
  }
  result+=name;
  return result;
}