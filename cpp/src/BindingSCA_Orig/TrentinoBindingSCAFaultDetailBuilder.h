// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************

#ifndef TrentinoBindingSCAFaultDetailBuilderH
#define TrentinoBindingSCAFaultDetailBuilderH

//standard
#include <boost/shared_ptr.hpp>
#include <map>

//specific
#include <Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h>


namespace Trentino{
   namespace Binding {

      namespace SCA {


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
            virtual std::string createDetail(const Trentino::RuntimeModel::ErrorCode& /*ec*/) const {
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


      }//namespace SCA
   } // namespace Binding
}// namespace Trentino

#endif //TrentinoBindingSCAFaultDetailBuilderH
