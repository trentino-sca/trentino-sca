#ifndef TrentinoExampleBasicPrinterBeanUtilsH
#define TrentinoExampleBasicPrinterBeanUtilsH

#include "TrentinoExampleBasicPrinterProbobufMessages.h"
#include "TrentinoExampleBasicPrinter.h"


namespace Trentino{
namespace Example{
class BasicPrinterBeanUtils {
  //construction
	public:
	BasicPrinterBeanUtils();
	~BasicPrinterBeanUtils();
	//services
	public:
	static void copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_ValidationException& pbObject, Trentino::Example::BasicPrinter::ValidationException* object);
	static void copyProperties(const Trentino::Example::BasicPrinter::ValidationException& object, protobuf::Trentino::Example::BasicPrinter::PB_ValidationException* pbObject);
	static void copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_Address& pbObject, Trentino::Example::BasicPrinter::Address* object);
	static void copyProperties(const Trentino::Example::BasicPrinter::Address& object, protobuf::Trentino::Example::BasicPrinter::PB_Address* pbObject);
	static void copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_TupleComplexNumber& pbObject, Trentino::Example::BasicPrinter::TupleComplexNumber* object);
	static void copyProperties(const Trentino::Example::BasicPrinter::TupleComplexNumber& object, protobuf::Trentino::Example::BasicPrinter::PB_TupleComplexNumber* pbObject);
	static void copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_Phone& pbObject, Trentino::Example::BasicPrinter::Phone* object);
	static void copyProperties(const Trentino::Example::BasicPrinter::Phone& object, protobuf::Trentino::Example::BasicPrinter::PB_Phone* pbObject);
	static void copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_Person& pbObject, Trentino::Example::BasicPrinter::Person* object);
	static void copyProperties(const Trentino::Example::BasicPrinter::Person& object, protobuf::Trentino::Example::BasicPrinter::PB_Person* pbObject);
	static void copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_ComplexNumber& pbObject, Trentino::Example::BasicPrinter::ComplexNumber* object);
	static void copyProperties(const Trentino::Example::BasicPrinter::ComplexNumber& object, protobuf::Trentino::Example::BasicPrinter::PB_ComplexNumber* pbObject);

};//class BasicPrinterBeanUtils
 
} //namespace Trentino
} //namespace Example
#endif TrentinoExampleBasicPrinterBeanUtilsH