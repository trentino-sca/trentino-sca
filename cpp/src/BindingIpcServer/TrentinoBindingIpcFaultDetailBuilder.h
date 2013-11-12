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

#ifndef TrentinoBindingIpcFaultDetailBuilderH
#define TrentinoBindingIpcFaultDetailBuilderH

//standard
#include <boost/shared_ptr.hpp>
#include <map>

//specific
#include <Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h>


namespace Trentino{
namespace Binding{
namespace IPC
{

   //********************************************************************************
   //                    SubCodes
   //********************************************************************************
   //! \brief Trentino Fault message sub codes are similar to HTTP Codes
   enum SubCodes {
      C_404_NOT_FOUND = 404,
      C_400_BAD_REQUEST =400,
      C_500_INTERNAL_SERVER_ERROR =500,
      C_501_NOT_IMPLEMENTED=501

   }; //enum Trentino compact soap sub codes

   typedef std::map<SubCodes,std::string>  SubCodeToReasonMap;

   //class declaration
   //********************************************************************
   //                    FaultDetailBuilder
   //********************************************************************
   //! \brief A Fault detail builder is responsible for creation of fault details 
   //! a fault detail contains exceptions details that are passed back to the client
   class FaultDetailBuilder
   {
      //services
      public:
      //****************************************************************************
      //                       createDetail()
      //****************************************************************************
      //! \brief create fault detail for a given error code
      //****************************************************************************
      virtual std::string createDetail(const Trentino::RuntimeModel::ErrorCode& ec) const =0;
      virtual std::string createSubCode(const Trentino::RuntimeModel::ErrorCode& ec ) const =0;
      virtual std::string createReason(const Trentino::RuntimeModel::ErrorCode& ec ) const=0;
      private:
      static SubCodeToReasonMap createValueMap();

      //data
      public:
      static SubCodeToReasonMap mValueMap;
   };//Class FaultDetailBuilder


         class DefaultFaultDetailBuilder;
         typedef boost::shared_ptr<DefaultFaultDetailBuilder>  DefaultFaultDetailBuilderPtr;

   //class declaration
   //***********************************************************************************
   //                                   DefaultFaultDetailBuilder
   //***********************************************************************************
   //! \brief a Fault detail Builder that allways return an empty string.
   //! used as convenience where no detail is needed
   //***********************************************************************************
   class DefaultFaultDetailBuilder : public FaultDetailBuilder 
   {

      public:
      DefaultFaultDetailBuilder( const std::string& defaultDetail
                              ,SubCodes defaultSubCode 
                              ,const std::string& moreReason);
      //! \todo missing inline file
      virtual std::string createDetail(const Trentino::RuntimeModel::ErrorCode& /*ec*/) const 
      {
         return mDefaultDetail;
      }
      virtual std::string createSubCode(const Trentino::RuntimeModel::ErrorCode& ec ) const;

      virtual std::string createReason(const Trentino::RuntimeModel::ErrorCode& ec )const;

      void setDefaultDetail(const std::string& detail);

      private:
      std::string mDefaultDetail;
      SubCodes mDefaultSubCode;
      std::string mMoreReason;
   }; // class DefaultFaultDetailBuilder


}//namespace IPC
} // namespace Binding
}// namespace Trentino

#endif //TrentinoBindingIpcFaultDetailBuilderH
