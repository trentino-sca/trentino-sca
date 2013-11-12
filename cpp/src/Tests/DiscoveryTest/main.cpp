//standard
#pragma warning(push)
#pragma warning(disable:4512 4244 4127)

//#include "TrentinoDiscoveryTestHeader.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "./../../Runtime/Discovery/TrentinoDiscoveryFactory.h"
#include "./../../Runtime/Discovery/TrentinoDiscoveryManagementInterface.h"
#include <boost/thread.hpp>

using namespace boost;
using namespace boost::this_thread;
using namespace Trentino::Discovery;

#pragma warning(pop)

namespace Trentino{
namespace Tests{
namespace Discovery
{

extern Trentino::Discovery::DiscoveryManagementInterface* mManagementInterfacePtr;

void CBStart(bool f, std::string retVal)
{
      f;
      retVal;
}

} // namespace Discovery
} // namespace Tests
} // namespace Trentino

int main(int /*argc*/, char** /*argv*/)
   {
   char *option[] ={ const_cast<char*>("dummy.exe"), //it doesn't have meaning, just dummy
      const_cast<char*>("--gtest_output=xml:report/DiscoveryTestReport.xml") };
   int argc2 = 2;
   ::testing::InitGoogleMock(&argc2, option);

   //start
   Trentino::Tests::Discovery::mManagementInterfacePtr = DiscoveryFactory::getDiscoveryManagementInterface(DiscoveryFactory::SLP);
   Trentino::Tests::Discovery::mManagementInterfacePtr->start(true, 3, 50, &Trentino::Tests::Discovery::CBStart);

   int y = RUN_ALL_TESTS();
   boost::this_thread::sleep(boost::posix_time::millisec(50000));
   Trentino::Tests::Discovery::mManagementInterfacePtr->stop(true);
   return y;   
   }
