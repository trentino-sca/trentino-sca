

namespace Trentino{
namespace Example{
namespace BasicCalculator
{
   //class declaration
   //**********************************************************************************************
   //                             Divider
   //**********************************************************************************************
   //! Divider interface testcode
   //**********************************************************************************************
   class Divider 
   {
      public:
	      virtual int divideReturnInt(int a, int b);
	      int divideReturnIntNotVirtual(int a, int b);
	      virtual int& divideReturnIntRef(int a, int b) = 0;
	      virtual const int& divideReturnConstIntRef(int a, int b);
	      virtual const int divideReturnConstInt(int a, int b) = 0;

   };//class Divider
}//namespace BasicCalculator
}//namespace Example
}//namespace Trentino