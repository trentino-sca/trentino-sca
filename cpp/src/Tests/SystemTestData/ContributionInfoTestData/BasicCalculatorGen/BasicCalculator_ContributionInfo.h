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
#ifndef BasicCalculator_ContributionInfoH
#define BasicCalculator_ContributionInfoH
#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif

#include <Runtime/Core/TrentinoCoreContributionInfo.h>


namespace Trentino{
namespace Gen{
namespace BasicCalculatorGen{
  class BasicCalculatorContributionInfo: public Trentino::Core::TrentinoContributionInfo {
  
  //construction
  public:
  BasicCalculatorContributionInfo();
  virtual ~BasicCalculatorContributionInfo();
  
  //services
  public:
     virtual TRENTINO_DLLEXPORT void TRENTINO_CDECL loadModel(Trentino::Core::SCAModelLoader* modelLoader);
     virtual TRENTINO_DLLEXPORT  Trentino::Invocation::ServiceInvocationWrapperBase* TRENTINO_CDECL getServiceInvocationWrapperByClassName(const std::string& className );
     virtual TRENTINO_DLLEXPORT  Trentino::Binding::BindingHelperBase* TRENTINO_CDECL getBindingHelperByBindingIdAndClassName(const std::string& biningId,const std::string& className );

     }; //class BasicCalculatorContributionInfo

}//namespace Gen
}//namespace Trentino
}//namespace BasicCalculatorGen

#endif //TrentinoGenProxiesWrappersH

