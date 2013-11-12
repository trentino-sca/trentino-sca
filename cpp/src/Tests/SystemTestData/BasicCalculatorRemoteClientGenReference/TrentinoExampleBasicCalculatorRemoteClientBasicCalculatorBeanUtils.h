#ifndef TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorBeanUtilsH
#define TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorBeanUtilsH

#include "TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorResponse.pb.h"
#include "TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorRequest.pb.h"
#include "TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorTypes.pb.h"
#include "TrentinoExampleBasicCalculatorRemoteClientBasicCalculator.h"


namespace Trentino{
namespace Example{
namespace BasicCalculatorRemoteClient{

class BasicCalculatorBeanUtils {
  //construction
	public:
	BasicCalculatorBeanUtils();
	virtual ~BasicCalculatorBeanUtils();
	//services
	public:
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address& pb_Address, Trentino::Example::BasicCalculatorRemoteClient::Address& argAddress);
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address* pb_Address, Trentino::Example::BasicCalculatorRemoteClient::Address* argAddress);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Address& argAddress, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address& pb_Address);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Address* argAddress, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address* pb_Address);
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber& pb_ComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber& argComplexNumber);
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber* pb_ComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* argComplexNumber);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber& argComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber& pb_ComplexNumber);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* argComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber* pb_ComplexNumber);
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone& pb_Phone, Trentino::Example::BasicCalculatorRemoteClient::Phone& argPhone);
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone* pb_Phone, Trentino::Example::BasicCalculatorRemoteClient::Phone* argPhone);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Phone& argPhone, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone& pb_Phone);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Phone* argPhone, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone* pb_Phone);
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person& pb_Person, Trentino::Example::BasicCalculatorRemoteClient::Person& argPerson);
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person* pb_Person, Trentino::Example::BasicCalculatorRemoteClient::Person* argPerson);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Person& argPerson, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person& pb_Person);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Person* argPerson, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person* pb_Person);
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_TupleComplexNumber& pb_TupleComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::TupleComplexNumber& argTupleComplexNumber);
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_TupleComplexNumber* pb_TupleComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::TupleComplexNumber* argTupleComplexNumber);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::TupleComplexNumber& argTupleComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_TupleComplexNumber& pb_TupleComplexNumber);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::TupleComplexNumber* argTupleComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_TupleComplexNumber* pb_TupleComplexNumber);
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ValidationException& pb_ValidationException, Trentino::Example::BasicCalculatorRemoteClient::ValidationException& argValidationException);
	static void copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ValidationException* pb_ValidationException, Trentino::Example::BasicCalculatorRemoteClient::ValidationException* argValidationException);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::ValidationException& argValidationException, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ValidationException& pb_ValidationException);
	static void copyProperties(Trentino::Example::BasicCalculatorRemoteClient::ValidationException* argValidationException, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ValidationException* pb_ValidationException);

};//class BasicCalculatorBeanUtils

} //namespace Trentino
} //namespace Example
} //namespace BasicCalculatorRemoteClient
#endif TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorBeanUtilsH