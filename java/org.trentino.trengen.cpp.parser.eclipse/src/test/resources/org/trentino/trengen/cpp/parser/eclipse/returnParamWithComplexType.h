

namespace Trentino{
namespace Test{
namespace ComplexTypes
{
   //class declaration
   //**********************************************************************************************
   //                             Divider
   //**********************************************************************************************
   //! Divider interface testcode
   //**********************************************************************************************
   class ServiceFactory
   {
      public:
	      virtual Servicereference getServiceReferenceUndefinedType(std::string name);
	      virtual Test::Servicereference getServiceReferenceUndefinedType2(std::string name);
	      virtual const Servicereference getServiceReferenceUndefinedTypeConst(std::string name);
	      virtual const Test::Servicereference getServiceReferenceUndefinedTypeConst2(std::string name);
	      virtual const Servicereference& getServiceReferenceUndefinedTypeConstRef(std::string name);
	      virtual const Test::Servicereference &getServiceReferenceUndefinedTypeConstRef2(std::string name);
	      const Test::Servicereference &getServiceReferenceUndefinedTypeConstRef2NotVirtual(std::string name);
	      Test::Servicereference &getServiceReferenceUndefinedTypeRef2NotVirtual(std::string name);
	      boost::shared_ptr<Test::Servicereference> getServiceReferenceSharedPtr();
	      const boost::shared_ptr<Test::Servicereference> getServiceReferenceSharedPtrConst();
	      boost::shared_ptr<Test::Servicereference>& getServiceReferenceSharedPtrRef();

	      template <class myType>
	      myType GetMax (myType a, myType b) {
	       return (a>b?a:b);
	      }

	      template <class myType>
	      myType& GetMaxRef (myType a, myType b) {
	       return (a>b?a:b);
	      }

	      template <class myType>
	      const myType& GetMaxConstRef (myType a, myType b) {
	       return (a>b?a:b);
	      }

	      template <class myType>
	      const std::vector<myType>& GetMaxConstRefSharedPtr (myType a, myType b);

   };//class Divider
}//namespace BasicCalculator
}//namespace Example
}//namespace Trentino
