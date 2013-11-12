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

#ifndef TrentinoInvocationSystemExceptionDataH
#define TrentinoInvocationSystemExceptionDataH

namespace Trentino {
namespace Invocation 
{
   //**********************************************************************************************
   //                             InvocationSystemExceptionData 
   //**********************************************************************************************
   //! \ingroup Invocation
   //! \brief data to be thrown if HW exception happened
   //**********************************************************************************************
   class InvocationSystemExceptionData 
   {
      //contruction
   public:
      InvocationSystemExceptionData(unsigned int id)
      : exceptionID(id) {};

      ~InvocationSystemExceptionData() {};

   public:
      //**********************************************************************************************
      //                                     getID 
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief get the ID of current exception
      //**********************************************************************************************
      inline unsigned int getID() const;

   private:
      //**********************************************************************************************
      //                                    exceptionID 
      //**********************************************************************************************
      //! \ingroup Invocation
      //! \brief system ID of the hardware exception
      //**********************************************************************************************
      unsigned int exceptionID;
   }; //class InvocationSystemExceptionData
	
   inline unsigned int InvocationSystemExceptionData::getID() const
   {
      return exceptionID;   
   }

}//namespace Invocation
}//namespace Trentino


#endif //TrentinoInvocationSystemExceptionDataH
