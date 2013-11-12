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

inline void  CalculatorImpl::setDivider(Divider* divider)
{
	mDivider = divider;
	int& deneme = mDivider->divide(8,4);
	
}

inline void  CalculatorImpl::setSubtractor(Subtractor* subtractor)
{
	std::cout << "setting the service of  Subtractor reference of CalculatorImpl " << std::endl;
	mSubtractor = subtractor;
	std::cout << "From the setter of  Subtractor reference of CalculatorImpl we subtract service is triggered a: " << 9<< " b: " << 4 << std::endl;
	int returnVAl = mSubtractor->subtract(9,4);
	std::cout << "Result of subtractor service is : " << returnVAl << std::endl;
	
}

inline void CalculatorImpl::setComponentContext(oasis::sca::ComponentContext* componentContext)
{
	mComponentContext = componentContext;
}