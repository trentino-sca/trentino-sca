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

#ifndef TrentinoBindingSCAClientDefsH
#define TrentinoBindingSCAClientDefsH

//standard
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/cstdint.hpp>
#include <vector>
#pragma warning(push)
#pragma warning(disable:4512 4244 4127)
#include "google/protobuf/io/zero_copy_stream_impl_lite.h"
#pragma warning(pop)


namespace Trentino {
   namespace Binding {
      namespace SCA {
         namespace Client {



            typedef boost::uint8_t DataBlock;
            typedef boost::shared_array<DataBlock> DataBlockArray;
            typedef google::protobuf::io::ArrayInputStream ArrayInputStream;
            typedef google::protobuf::io::ArrayOutputStream ArrayOutputStream;
            typedef boost::shared_ptr<ArrayInputStream> ArrayInputStreamPtr;
            typedef boost::shared_ptr<ArrayOutputStream> ArrayOutputStreamPtr;
            

            } //namespace Client
         }// namespace SCA
      } // namespace Binding
   }// namespace Trentino


#endif //TrentinoBindingSCAImplH
