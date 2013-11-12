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

#ifndef TrentinoBindingSCAImplH
#define TrentinoBindingSCAImplH

//standard
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/cstdint.hpp>
#include <vector>
#pragma warning(push)
#pragma warning(disable:4512 4244 4127)
#include "google/protobuf/io/zero_copy_stream_impl_lite.h"
#pragma warning(pop)
#include <TrentinoBindingSCA.h>

namespace Trentino {
   namespace Binding {
      namespace SCA {
         typedef boost::uint8_t DataBlock;
         typedef boost::shared_array<DataBlock> DataBlockArray;
         typedef google::protobuf::io::ArrayInputStream ArrayInputStream;
         typedef google::protobuf::io::ArrayOutputStream ArrayOutputStream;
         typedef boost::shared_ptr<ArrayInputStream> ArrayInputStreamPtr;
         typedef boost::shared_ptr<ArrayOutputStream> ArrayOutputStreamPtr;
      }// namespace SCA
   } // namespace Binding
}// namespace Trentino


#endif //TrentinoBindingSCAImplH
