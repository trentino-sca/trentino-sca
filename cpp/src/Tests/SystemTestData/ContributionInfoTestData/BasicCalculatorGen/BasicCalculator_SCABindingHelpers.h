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
#ifndef BasicCalculator_SCABindingHelpersH
#define BasicCalculator_SCABindingHelpersH
#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif

#include <Binding/SCA/TrentinoBindingSCASCABindingHelper.h>


namespace Trentino{
   namespace Gen{
      namespace BasicCalculatorGen{
         class CalculatorSCABindingHelper: public Trentino::Binding::SCA::SCABindingHelper{

            //construction
         public:
            CalculatorSCABindingHelper();
            virtual ~CalculatorSCABindingHelper();

            //services
         public:
            virtual const Trentino::Binding::SCA::FaultDetailBuilderPtr getFaultBuilder() const =0;
            virtual void serializeResponse( const Trentino::Invocation::InvocationDataPtr& invocationDataPtr, trentino::bindingsca::csoap::Soap& response, Trentino::RuntimeModel::ErrorCode& ec )const =0;
            virtual void deserializeRequest( const Trentino::Invocation::InvocationDataPtr& invocationDataPtr, 
               trentino::bindingsca::csoap::Soap& request, Trentino::RuntimeModel::ErrorCode& ec) const =0;
            virtual bool isOneWay( Trentino::Invocation::InvocationDataPtr& invocationDataPtr ) const=0;

            }; //class CalculatorSCABindingHelper

         }//namespace Gen
      }//namespace Trentino
   }//namespace BasicCalculatorGen

#endif //BasicCalculator_SCABindingHelpersH

