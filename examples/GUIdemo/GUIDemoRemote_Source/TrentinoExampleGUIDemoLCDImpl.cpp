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

//header
#include "TrentinoExampleGUIDemoLCDImpl.h"
#include <iostream>
using namespace Trentino::Example::GUIDemo;


//class GUIDemoLCD

//construction

GUIDemoLCDImpl::GUIDemoLCDImpl()
{
	
	void *app_ptr;

	app_ptr = startGuiThreaded();

	gc2 = new Gui_Control(GLCD);

	showWidget(app_ptr, gc2);

}

GUIDemoLCDImpl::~GUIDemoLCDImpl()
{
	std::cout << "LCD dead!!" << std::endl;

	void *ptr;

	ptr = startGuiThreaded();

	if (ptr !=  NULL)
		stopGuiThreaded(ptr);

}

//methods

void GUIDemoLCDImpl::showLCDNum (const tint32_t val)
{
	//std::cout << "GUIDemoLCDImpl::showLCDNum param - " << a << std::endl;
    
	gc2->setLCDVal(val);

}

void GUIDemoLCDImpl::setGUIDemoLCDName(const std::string& name)
{
	gc2->setWindowTitle(name);
}
