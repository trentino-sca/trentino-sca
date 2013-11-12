//standard
#pragma warning(push)
#pragma warning(disable:4512 4244 4127)

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#pragma warning(pop)

int main(int /*argc*/, char** /*argv*/)
{
char *option[] ={ const_cast<char*>("dummy.exe"), //it doesn't have meaning, just dummy
   const_cast<char*>("--gtest_output=xml:report/XMLTestReport.xml") };
int argc2 = 2;
::testing::InitGoogleMock(&argc2, option);
return RUN_ALL_TESTS();   
}
