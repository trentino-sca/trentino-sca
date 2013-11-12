#include <TrentinoGenBindingProxy.h>

using namespace Trentino::Gen;
using namespace Trentino::Binding::SCA::Client;

int main(int argc, char* argv[])
   {
   if (argc <1)
      {
      argv[0];
      }

   Trentino_Example_BasicCalculatorRemoteClient_BasicCalculatorBindingProxy proxy;
   proxy.set_Trentino_internal_adress_property_do_not_use_this_name_("tcp://localhost:5342/BasicCalculatorImpl/BasicCalculator/");
   int y = proxy.addSimple(3,4);
   assert(7 ==y);
   return 0;
}